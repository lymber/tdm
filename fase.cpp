#include "fase.h"

//---------------------------------------------------------------------
//retorna um inimigo, baseado na sua constante
Objeto *Fase::NovoInimigo(int qualIA, int qualNave)
{
   char temp[30];

   switch (qualNave)
   {
      case PITAGORAS: strcpy(temp, "naves/pitagoras.nav"); break;
      case PLATAO: strcpy(temp, "naves/platao.nav"); break;
      case SOCRATES: strcpy(temp, "naves/socrates.nav"); break;
   }
   switch (qualIA)
   {
      case CORAJOSO: return (Objeto *) (new Corajoso(central, temp));
      case MEDROSO: return (Objeto *) (new Medroso(central, temp));
   }
}

//-----------------------------------------------------------------------
int Fase::QuantosPossiveis(void)
{
   int quantos = 0;
   for (int i = 0; i < QTD_INIMIGOS; i++)
      if (possiveisIA[i]) quantos++;
   return quantos;
}

//-----------------------------------------------------------------------
int Fase::QuantasNavesPossiveis(void)
{
   int quantos = 0;
   for (int i = 0; i < QTD_NAVES; i++)
      if (navesPossiveis[i]) quantos++;
   return quantos;
}

//-----------------------------------------------------------------------
void Fase::MorreuInimigo(void)
{
   quantosAtual--;
}

//-----------------------------------------------------------------------
vector3df Fase::EscolhePosicaoInimigo(void)
{
   return posicaoInicialInimigos[rand() % quantasPosicoesInimigos];
}

//---------------------------------------------------------------------
Objeto *Fase::SorteiaInimigo(void)
{
   //escolho primeiro a nave
   int temp = rand() % QuantasNavesPossiveis();
   int qualNave = 0, aux = 0;
   while (aux <= temp)
   {
      while(!navesPossiveis[qualNave]) qualNave++;
      if (aux <= temp)
      {
         if (aux < temp) qualNave++;
         aux++;
      }
   }
   //agora escolho a inteligência
   int qualIA = rand() % QuantosPossiveis();
   int atual = 0, quantosForam = 0;
   while (quantosForam <= qualIA)
   {
      while (!possiveisIA[atual]) atual++;
      if (quantosForam == qualIA) return NovoInimigo(atual, qualNave);
      atual++;
      quantosForam++;
   }

   return NULL;
}

//---------------------------------------------------------------------
int Fase::QuantosInimigosRestam(void)
{
   return totalInimigos - totalFeitos + quantosAtual;
}

//---------------------------------------------------------------------
void Fase::Atualiza(void)
{

   //vejo se precisa adicionar um inimigo
   if (quantosAtual < maximoInimigos && totalFeitos < totalInimigos)
   {

      Objeto *temp = SorteiaInimigo();
	   if (temp == NULL)
	      return; //deu algum erro
	   temp->MudaPosicao(EscolhePosicaoInimigo());
	   central->SoundEngine()->play3D("sons/aparece.ogg", temp->Posicao());
	   central->NovoObjeto(temp);
	   temp->AdicionaCenario(node);
	   quantosAtual++;
	   totalFeitos++;
   }
}

//--------------------------------------------------------------------
void Fase::Comeca(void)
{
   list<void *>::Iterator lista;
   Objeto *obj = (Objeto *) central->PrimeiroObjeto(&lista);

   //procuro a nave principal, dou o cenário para ela e a coloco no lugar certo
   while (obj != NULL)
   {
      if (obj->Mensagem(QUEM_VOCE, NULL) == JOGADOR)
      {
         obj->AdicionaCenario(node);
         obj->MudaPosicao(posicaoInicialJogador);
      }
      obj = (Objeto *) central->ProximoObjeto(&lista);
   }
   totalFeitos = 0;
   quantosAtual = 0;
}

//---------------------------------------------------------------------
void Fase::LeArquivo(const char *arquivo)
{
   IrrXMLReader* xml = createIrrXMLReader(arquivo);

   scene::IAnimatedMesh* mesh;

   while(xml && xml->read())
   {
      switch(xml->getNodeType())
      {

         case EXN_ELEMENT:
            if (!strcmp("modelo", xml->getNodeName()))
            {
               mesh = central->Device()->getSceneManager()->getMesh(xml->getAttributeValue("arquivo"));
            }
            else if (!strcmp("localJogador", xml->getNodeName()))
            {
                  posicaoInicialJogador.X = xml->getAttributeValueAsFloat("z");
                  posicaoInicialJogador.Z = xml->getAttributeValueAsFloat("z");
                  posicaoInicialJogador.Y = 0.0f;
            }
            else if (!strcmp("possiveisIA", xml->getNodeName()))
            {
               possiveisIA[CORAJOSO] = !strcmp("true", xml->getAttributeValueSafe("corajoso"));
               possiveisIA[MEDROSO] = !strcmp("true", xml->getAttributeValueSafe("medroso"));

            }
            else if (!strcmp("possiveisNaves", xml->getNodeName()))
            {
               navesPossiveis[PITAGORAS] = !strcmp("true", xml->getAttributeValueSafe("pitagoras"));
               navesPossiveis[SOCRATES] = !strcmp("true", xml->getAttributeValueSafe("socrates"));
               navesPossiveis[PLATAO] = !strcmp("true", xml->getAttributeValueSafe("platao"));

            }
            else if (!strcmp("aleatorio", xml->getNodeName()))
            {
               maximoInimigos = xml->getAttributeValueAsInt("maximoInimigos");
               totalInimigos = xml->getAttributeValueAsInt("totalInimigos");
            }
            else if (!strcmp("localInimigo", xml->getNodeName()))
            {
               vector3df *temp = posicaoInicialInimigos;
               posicaoInicialInimigos = new vector3df[quantasPosicoesInimigos + 1];
               for (int i = 0; i < quantasPosicoesInimigos; i++)
                  posicaoInicialInimigos[i] = temp[i];
               posicaoInicialInimigos[quantasPosicoesInimigos].X = xml->getAttributeValueAsFloat("x");
               posicaoInicialInimigos[quantasPosicoesInimigos].Z = xml->getAttributeValueAsFloat("z");
               posicaoInicialInimigos[quantasPosicoesInimigos].Y = 0.0f;
               quantasPosicoesInimigos++;
               delete temp;
            }
            else if (!strcmp("musica", xml->getNodeName()))
            {
               //toca a música
               central->SoundEngine()->play2D(xml->getAttributeValue("arquivo"), true);
            }
            break;

      }
   }


   //deixo o cenário otimizado para verificação de colisões
   if (mesh)
   {
      node = central->Device()->getSceneManager()->addOctTreeSceneNode(mesh->getMesh(0));
	   if (node)
	   {
	      scene::ITriangleSelector* selector = central->Device()->getSceneManager()->createOctTreeTriangleSelector(mesh->getMesh(0), node, 128);
		   node->setTriangleSelector(selector);
		   selector->drop();
	   }
	}

}

//---------------------------------------------------------------------
Fase::Fase(const char *arquivo, Central *centralAux)
{
   central = centralAux;
   quantasPosicoesInimigos = 0;
   posicaoInicialInimigos = NULL;

   for (int i; i < QTD_INIMIGOS; i++)
      possiveisIA[i] = false;
   for (int i; i < QTD_NAVES; i++)
      navesPossiveis[i] = false;

   LeArquivo(arquivo);
}

//-------------------------------------------------------------------------
Fase::~Fase(void)
{
   delete posicaoInicialInimigos;
}
