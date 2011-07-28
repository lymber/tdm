#include "missil.h"

//--------------------------------------------------------------------------
void Missil::BateuNeste(Objeto *outro)
{
   if (outro->Mensagem(QUEM_VOCE, NULL) == TIRO) return; //não bato em tiro
   if (outro->Mensagem(SOLIDO, NULL) == NAO) return; //não bato em coisas não sólidas
   if (pai != NULL && pai->SouEu(outro)) return; //não acerto o meu pai

   outro->AdicionaForca(0.5f * momento);
   morto = true;
   outro->BateramEmVoce(10);
   if (pai != NULL) pai->AcertouEste(outro);
}

//--------------------------------------------------------------------------
void Missil::Atualiza(void)
{
   ParaEsquerda(false);
   ParaDireita(false);
   
   Objeto *nave;
   
   if (procuro == JOGADOR) nave = Procura(JOGADOR);
   else if (procuro == INIMIGO) nave = InimigoMaisProximo();
   
   if (nave != NULL)
   {
      if (NaEsquerda(nave->Posicao())) ParaEsquerda(true);      
      if (NaDireita(nave->Posicao())) ParaDireita(true);
   }
   
   Objeto::Atualiza();
   if (bateuCenario) morto = true;
}

//---------------------------------------------------------------------------
int Missil::Mensagem(int qual, void *param)
{
   switch (qual)
   {
      case PROCURA_INIMIGO: procuro = INIMIGO; return NADA;
      case PROCURA_JOGADOR: procuro = JOGADOR; return NADA;
      case SOLIDO: return NAO;
      case QUEM_VOCE: return TIRO;
      case MEU_TIRO: if (pai != NULL && pai->SouEu((Objeto *) param)) return SIM;
                     else return NAO;
	//case ACERTOU: morto = true; 
	//((Objeto *) param)->AdicionaForca(0.05f * VetorFrente());
	//              return NADA;
      case PAI_MORTO: pai = NULL; return NADA;
   }
   
   return Objeto::Mensagem(qual, param);
}

//---------------------------------------------------------------
Missil::Missil(Central *central, Objeto *paiAux)
: Objeto(central, "modelos/missil.3ds")
{
   pai = paiAux;
   MudaPosicao(pai->Posicao());
   anguloHorizontal = pai->AnguloHorizontal();
   node->setRotation(vector3df(0, anguloHorizontal, 0));
   central->Device()->getSceneManager()->addLightSceneNode(node, core::vector3df(0.0f, 0.0f,0.0f),
		video::SColorf(1.0f, 0.9f, 0.0f, 0.5f), 4.0f);
	   
   piscando = 0;
   aceleracao = 0.02f;
   velocidadeMaxima = 0.2f;
   momento = velocidadeMaxima * VetorFrente();
   //resistencia = 0.1f; //não tem inércia
   massa = MASSA_TIRO;
   velocidadeVirada = 0.02f;
   maxVirada = 0.3f;
   //faz o som
   central->SoundEngine()->play3D("sons/laser.ogg", Posicao());
}
