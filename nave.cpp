#include "nave.h"

//---------------------------------------------------------------------
void Nave::LeAtributos(const char *arquivo)
{
   IrrXMLReader* xml = createIrrXMLReader(arquivo);
   
   while(xml && xml->read())
   {
      switch(xml->getNodeType())
      {     
         case EXN_ELEMENT:  
            if (!strcmp("atributos", xml->getNodeName()))
            {
               Objeto::LeModelo(xml->getAttributeValue("arquivo"));
               velocidadeMaxima = xml->getAttributeValueAsFloat("velocidadeMaxima");
            }
            else if (!strcmp("tiro", xml->getNodeName()))
            {
               if (!strcmp("laser", xml->getAttributeValue("qualBasico"))) tipoTiroBasico = TIPO_LASER;
               else if (!strcmp("missil", xml->getAttributeValue("qualBasico"))) tipoTiroBasico = TIPO_MISSIL;
               if (!strcmp("multiplo", xml->getAttributeValue("qualBasico"))) tipoTiroBasico = TIPO_MULTIPLO;
            }
            else if (!strcmp("recargaLaser", xml->getNodeName()))
            {
               tempoDeRecargaTotal[TIPO_LASER] = xml->getAttributeValueAsInt("tempo");
            }  
            else if (!strcmp("recargaMissil", xml->getNodeName()))
            {
               tempoDeRecargaTotal[TIPO_MISSIL] = xml->getAttributeValueAsInt("tempo");
            }
            else if (!strcmp("recargaMultiplo", xml->getNodeName()))
            {
               tempoDeRecargaTotal[TIPO_MULTIPLO] = xml->getAttributeValueAsInt("tempo");
            }
            break;   
      }
   }   
}

//----------------------------------------------------------------------------
void Nave::GanhouTiroBasico(int qual)
{
   if (tempoBonus[qual] == 0) 
      tempoDeRecargaTotal[qual] = tempoDeRecargaTotal[qual] / 2; 
   tempoBonus[qual] = TEMPO_BONUS;
}

//----------------------------------------------------------------------------
void Nave::GanhouTiroNaoBasico(int qual)
{
   tempoBonus[qual] = TEMPO_BONUS;
}

//----------------------------------------------------------------------------
int Nave::Mensagem(int msg, void *param)
{
   if (msg == GANHOU_ITEM_LASER)
   {
      if (tipoTiroBasico == TIPO_LASER) GanhouTiroBasico(TIPO_LASER);
      else GanhouTiroNaoBasico(TIPO_LASER);
   }   
   if (msg == GANHOU_ITEM_MISSIL)
   {   
      if (tipoTiroBasico == TIPO_MISSIL) GanhouTiroBasico(TIPO_MISSIL);
      else GanhouTiroNaoBasico(TIPO_MISSIL);      
   }
   if (msg == GANHOU_ITEM_MULTIPLO)
   {   
      if (tipoTiroBasico == TIPO_MULTIPLO) GanhouTiroBasico(TIPO_MULTIPLO);
      else GanhouTiroNaoBasico(TIPO_MULTIPLO);      
   }
   else return Objeto::Mensagem(msg, param);
}

//-------------------------------------------------------------------------
//O que fazer se colidiu com outro objeto
void Nave::BateuNeste(Objeto *outro)
{
   if (piscando > 0 || outro->Piscando()) return;
   if (Mensagem(SOLIDO, NULL) == NAO) return; //se eu não sou sólido, deixo passar
   if (Mensagem(QUEM_VOCE, NULL) == TIRO) return; //deixo que o tiro cuida se atingiu alguém
   
   if (outro->Mensagem(SOLIDO, NULL) == SIM) //bateu em algo, dar impacto para os dois
   {
      lifePotencial -= 5;
      life -= 10;
      //piscando = 5;
      vector3df v = Posicao() - outro->Posicao();
      v = (1.0f / v.getLength()) * v;
      AdicionaForca(massa * v);
      outro->AdicionaForca(-massa * v);
      outro->BateramEmVoce(5);
      
   } 
}

//----------------------------------------------------------------------------
void Nave::BateramEmVoce(int quantoPerde)
{
   life -= 2 * quantoPerde;
   lifePotencial -= quantoPerde;
   //piscando = TEMPO_PISCANDO;
   central->SoundEngine()->play3D("sons/batida.ogg", Posicao());
}


//--------------------------------------------------------------------------
//Cria um novo tiro do tipo qual
void Nave::NovoTiro(int qual)
{
   if (qual == TIPO_LASER)
   {
      Laser *laser = new Laser(central, this);
      central->NovoObjeto((Objeto *) laser);
      laser->AdicionaCenario(cenario);
   }
   else if (qual == TIPO_MISSIL)
   {
      Missil *missil = new Missil(central, this);
      central->NovoObjeto((Objeto *) missil);
      missil->AdicionaCenario(cenario);
      if (Mensagem(QUEM_VOCE, NULL) == JOGADOR) missil->Mensagem(PROCURA_INIMIGO, NULL);
      else if (Mensagem(QUEM_VOCE, NULL) == INIMIGO) missil->Mensagem(PROCURA_JOGADOR, NULL);
   }
   else if (qual == TIPO_MULTIPLO)
   {
      Multiplo *multiplo = new Multiplo(central, this);
      central->NovoObjeto((Objeto *) multiplo);
      multiplo->AdicionaCenario(cenario);
   }
}

//----------------------------------------------------------------------------
//Avisa os tiros que o pai morreu
void Nave::AvisaTirosPaiMorto(void)
{
   list<void *>::Iterator lista;
   Objeto *temp = (Objeto *) central->PrimeiroObjeto(&lista);

   while (temp != NULL)
   {
      if (temp->Mensagem(MEU_TIRO, this) == SIM) temp->Mensagem(PAI_MORTO, NULL);
      temp = (Objeto *) central->ProximoObjeto(&lista);
   }
}

//-------------------------------------------------------------------------
//É o que deve ser chamado quando é para soltar realmente o tiro
void Nave::SoltaTiro(void)
{
   for (int i = 0; i < QTD_TIPOS_TIROS; i++)
   {
      if (tipoTiroBasico == i && tempoDeRecargaAtual[i] >= tempoDeRecargaTotal[i])
      //esse é o tiro básico
      {
         NovoTiro(i);
         tempoDeRecargaAtual[i] = 0;   
      }
      else if (tempoBonus[i] > 0 &&  tempoDeRecargaAtual[i] >= tempoDeRecargaTotal[i])
      //outros tiros
      {
         NovoTiro(i);
         tempoDeRecargaAtual[i] = 0;   
      }
   }
}

//-------------------------------------------------------------------------
//faz a desviadinha para esquerda
void Nave::JogadaDeLadoEsq(bool pressionada)
{
   if (tempoAtualJogadaDeLado > 0) return;
   if (pressionada){
     momentoImpacto = momentoImpacto + (0.3f * VetorEsquerda());
     tempoAtualJogadaDeLado = TEMPO_JOGADA_DE_LADO;
   }
}

//-------------------------------------------------------------------------
//faz a desviadinha para direita
void Nave::JogadaDeLadoDir(bool pressionada)
{
   if (tempoAtualJogadaDeLado > 0) return;
   if (pressionada){
     momentoImpacto = momentoImpacto + (0.3f * VetorDireita());
     tempoAtualJogadaDeLado = TEMPO_JOGADA_DE_LADO;
   }
}

//---------------------------------------------------------------------------
//Faz as atualizações necessárias a cada ciclo, com base no input
void Nave::Atualiza(void)
{
   
   if (life <= 0)
   {
      morto = true;
      AvisaTirosPaiMorto();
   }
   Objeto::Atualiza();
   
   //atualizo o tempo da jogada de lado
   if (tempoAtualJogadaDeLado > 0) tempoAtualJogadaDeLado--;  
   
   for (int i = 0; i < QTD_TIPOS_TIROS; i++)
   {
      if (tempoDeRecargaAtual[i] < tempoDeRecargaTotal[i]) tempoDeRecargaAtual[i]++;
      if (i == tipoTiroBasico && tempoBonus[i] == 1) tempoDeRecargaTotal[i] = tempoDeRecargaTotal[i] * 2; 
      if (tempoBonus[i] > 0) tempoBonus[i]--;
      
   }
      
   if (atirando) SoltaTiro();
   
   if (life < lifePotencial) life += 0.01;
   if (life < 0) life = 0;
   if (lifePotencial < 0) lifePotencial = 0;
   
   if (morto)
   {
      if (tipoTiroBasico == TIPO_LASER)
      {
         ItemLaser *tmp = new ItemLaser(central);
         tmp->MudaPosicao(Posicao());
         central->NovoObjeto(tmp);
      }
      else if (tipoTiroBasico == TIPO_MISSIL)
      {
         ItemMissil *tmp = new ItemMissil(central);
         tmp->MudaPosicao(Posicao());
         central->NovoObjeto(tmp);
      }
      else if (tipoTiroBasico == TIPO_MULTIPLO)
      {
         ItemMultiplo *tmp = new ItemMultiplo(central);
         tmp->MudaPosicao(Posicao());
         central->NovoObjeto(tmp);
      }
   }   
}

//---------------------------------------------------------------------------
Nave::Nave(Central *centralAux, const char *nome) : Objeto(centralAux, NULL)
{
   atirando = false;
	for (int i = 0; i < QTD_TIPOS_TIROS; i++)
	{
	   tempoDeRecargaTotal[i] = TEMPO_LONGO * 2;
	   tempoDeRecargaAtual[i] = tempoDeRecargaTotal[i];
	}
	lifeMaximo = 1000;
	lifePotencial = lifeMaximo;
	life = lifeMaximo;
	tempoAtualJogadaDeLado = 0;
	tipoTiroBasico = TIPO_NENHUM;   
   for (int i = 0; i < QTD_TIPOS_TIROS; i++)
	   tempoBonus[i] = 0;
	LeAtributos(nome);
}
