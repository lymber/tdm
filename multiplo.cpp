#include "multiplo.h"

//--------------------------------------------------------------------------
void Multiplo::BateuNeste(Objeto *outro)
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
void Multiplo::Atualiza(void)
{
   if (criaCopias)
   {
      criaCopias = false;
      Multiplo *copia = new Multiplo(central, pai, -15.0f);
      central->NovoObjeto((Objeto *) copia);
      copia->AdicionaCenario(cenario);
      copia->Mensagem(NAO_CRIE_COPIAS, NULL);
      copia = new Multiplo(central, pai, 15.0f);
      central->NovoObjeto((Objeto *) copia);
      copia->AdicionaCenario(cenario);
      copia->Mensagem(NAO_CRIE_COPIAS, NULL);   
   }
   Objeto::Atualiza();
   if (bateuCenario) morto = true;
}

//---------------------------------------------------------------------------
int Multiplo::Mensagem(int qual, void *param)
{
   switch (qual)
   {
      case NAO_CRIE_COPIAS: criaCopias = false; return NADA;
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
Multiplo::Multiplo(Central *central, Objeto *paiAux, float desvio)
: Objeto(central, "modelos/multiplo.3ds")
{
   criaCopias = true;
   pai = paiAux;
   MudaPosicao(pai->Posicao());
   anguloHorizontal = pai->AnguloHorizontal() + desvio;
   node->setRotation(vector3df(0, anguloHorizontal, 0));
   central->Device()->getSceneManager()->addLightSceneNode(node, core::vector3df(0.0f, 0.0f,0.0f),
		video::SColorf(1.0f, 0.0f, 0.0f, 0.5f), 5.0f);
	//o laser não tem sombra
   node->setMaterialFlag(EMF_LIGHTING, false);
   
   piscando = 0;
   velocidadeMaxima = 0.3f;
   momento = velocidadeMaxima * VetorFrente();
   resistencia = 0.0f; //não tem inércia
   massa = MASSA_TIRO;

   //faz o som
   central->SoundEngine()->play3D("sons/laser.ogg", Posicao());
}
