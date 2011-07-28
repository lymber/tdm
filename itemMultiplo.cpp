#include "itemMultiplo.h"


//--------------------------------------------------------------------------
void ItemMultiplo::BateuNeste(Objeto *outro)
{
   if (outro->Mensagem(QUEM_VOCE, NULL) == TIRO) return; //não bato em tiro
   if (outro->Mensagem(SOLIDO, NULL) == NAO) return; //não bato em coisas não sólidas

   if (!outro->Morto()) outro->Mensagem(GANHOU_ITEM_MULTIPLO, NULL);
   morto = true;
}


//----------------------------------------------------------------------------------
int ItemMultiplo::Mensagem(int msg, void *param)
{
   switch (msg)
   {
      case QUEM_VOCE: return ITEM;
      case SOLIDO:    return NAO;
   }

   return Objeto::Mensagem(msg, param);
}

//----------------------------------------------------------------------------------
void ItemMultiplo::Atualiza(void)
{
   ParaEsquerda(true);   
   Objeto::Atualiza();
   
}

//----------------------------------------------------------------------------------------
ItemMultiplo::ItemMultiplo(Central *central)
   : Objeto(central, "modelos/itemLaser.3ds")
{
   central->Device()->getSceneManager()->addLightSceneNode(node, core::vector3df(0.0f, 0.0f,0.0f),
		video::SColorf(0.0f, 0.0f, 1.0f, 0.5f), 5.0f);
}
