#include "itemMissil.h"


//--------------------------------------------------------------------------
void ItemMissil::BateuNeste(Objeto *outro)
{
   if (outro->Mensagem(QUEM_VOCE, NULL) == TIRO) return; //n�o bato em tiro
   if (outro->Mensagem(SOLIDO, NULL) == NAO) return; //n�o bato em coisas n�o s�lidas

   if (!outro->Morto()) outro->Mensagem(GANHOU_ITEM_MISSIL, NULL);
   morto = true;
}


//----------------------------------------------------------------------------------
int ItemMissil::Mensagem(int msg, void *param)
{
   switch (msg)
   {
      case QUEM_VOCE: return ITEM;
      case SOLIDO:    return NAO;
   }

   return Objeto::Mensagem(msg, param);
}

//----------------------------------------------------------------------------------
void ItemMissil::Atualiza(void)
{
   ParaEsquerda(true);
   Objeto::Atualiza();
}

//----------------------------------------------------------------------------------------
ItemMissil::ItemMissil(Central *central)
   : Objeto(central, "modelos/itemLaser.3ds")
{
   central->Device()->getSceneManager()->addLightSceneNode(node, core::vector3df(0.0f, 0.0f,0.0f),
		video::SColorf(0.0f, 0.0f, 1.0f, 0.5f), 5.0f);
}
