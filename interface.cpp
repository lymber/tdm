#include "interface.h"

//------------------------------------------------------------------------------
ITexture * Interface::EscolheLogo(int qual)
{
   switch (qual)
   {
      case TIPO_LASER: return logoLaser;
      case TIPO_MISSIL: return logoMissil;
      case TIPO_MULTIPLO: return logoMultiplo;
   }
}

//---------------------------------------------------------------------------------------
//Converte uma textura para o tamanho da tela, partindo do que seria 800x600
video::ITexture* Interface::LeTexturaConvertida(const c8 *filename)
{
   IImage *temp = central->Device()->getVideoDriver()->createImageFromFile(filename);

   if (temp == NULL) return NULL; //deu pau
   core::dimension2di tamanhoOriginal = temp->getDimension();
      
   //calculo qual deveria ser o tamanho
   core::dimension2di novoTamanho(ConverteX(tamanhoOriginal.Width), ConverteY(tamanhoOriginal.Height));
   ITexture* buf = central->Device()->getVideoDriver()->addTexture(novoTamanho, "Texture"); 
   IImage *nova = central->Device()->getVideoDriver()->createImageFromData(temp->getColorFormat(), novoTamanho, buf->lock());
   buf->unlock();
   temp->copyToScaling(nova);
      
   ITexture *retorno = central->Device()->getVideoDriver()->addTexture(filename, nova);

   nova->drop();
   //free(buffer);
   
   return retorno;   
} 

//--------------------------------------------------------------------------------------
s32 Interface::ConverteY(s32 y)
{
   return (y * tamanhoTela.Height) / 600;
}

//--------------------------------------------------------------------------------------
s32 Interface::ConverteX(s32 x)
{
   return (x  * tamanhoTela.Width) / 800;
}


//-------------------------------------------------------------------------------------
//retorna o retângulo baseado na tela atual (pega as coordenadas como se fossem 800x600)
rect<s32> Interface::Retangulo(s32 x1, s32 y1, s32 x2, s32 y2)
{
   return rect<s32>(ConverteX(x1), ConverteY(y1), ConverteX(x2), ConverteY(y2));
}

//-------------------------------------------------------------------------------------
void Interface::Desenha(void)
{
   if (navePrincipal == NULL) return;

   //mostra o life dos inimigos
   
   list<void *>::Iterator lista;
   Objeto *atual = (Objeto *) central->PrimeiroObjeto(&lista);
   
   while (atual != NULL)
   {
      if (atual->Mensagem(QUEM_VOCE, NULL) == INIMIGO)
      {
         //pego a posição do inimigo na tela
         position2d<s32>  pos = central->Device()->getSceneManager()->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(atual->Posicao());
         central->Device()->getVideoDriver()->draw2DRectangle(SColor(100, 255, 255, 0), Retangulo((s32) (pos.X - (atual->Life() / 2)), (s32) (pos.Y - 30), (s32) (pos.X +(atual->Life() / 2)), (s32) (pos.Y - 20)));
      }
      atual = (Objeto *) central->ProximoObjeto(&lista);
   }
   
   //desenho o cockpit no caso da camera interna
   if (((Camera *) (central->QualCamera()))->QualModo() == DE_DENTRO)
      central->Device()->getVideoDriver()->draw2DImage(cockpit, position2d<s32>(ConverteX(0), ConverteY(0)), rect<s32>(0, 0, 800, 600), NULL, SColor(255, 255, 255, 255), true);
   
   if (transicaoLife == 0)
   {
      delete transparenciaLife;
      transparenciaLife = new Fader(CLARO_ESCURO_CLARO, 100, 100, 100, 100, 255);
   }
   
     
   int life, lifePotencial;

   if (transicaoLife <= (3 * TEMPO_TRANSICAO) / 4) //mostra o life verdadeiro
   {
      life = (int) navePrincipal->Life();
      lifePotencial = (int) navePrincipal->LifePotencial();
   }
   else //faz uma pequena transição
   {
      float t = (TEMPO_TRANSICAO - transicaoLife) / (TEMPO_TRANSICAO / 4);
      life = (int) ((float) (t * lifeAnterior + (1 - t) * navePrincipal->Life()));
      lifePotencial = (int) ((float) (t * lifePotencialAnterior + (1 - t) * navePrincipal->LifePotencial()));
   }
   int tmp = transparenciaLife->Atualiza();
   
   central->Device()->getVideoDriver()->draw2DRectangle(SColor(tmp, 255, 0, 0), Retangulo(10, 10, lifePotencial, 25));
   central->Device()->getVideoDriver()->draw2DRectangle(SColor(tmp, 255, 255, 0), Retangulo(10, 10, life, 25));
   

   //desenho os alvos
   for (int i = 0; i < fase->QuantosInimigosRestam(); i += 2)
   {
      central->Device()->getVideoDriver()->draw2DImage(alvo, position2d<s32>(ConverteX(630), ConverteY(10 + (60 * (i / 2)))), rect<s32>(0, 0, alvo->getOriginalSize().Height, alvo->getOriginalSize().Width), NULL, SColor(120, 255, 255, 255), true);
      
      
      if (i + 1 < fase->QuantosInimigosRestam()) central->Device()->getVideoDriver()->draw2DImage(alvo, position2d<s32>(ConverteX(700), ConverteY(10 + (60 * (i / 2)))), rect<s32>(0, 0, alvo->getOriginalSize().Height, alvo->getOriginalSize().Width), NULL, SColor(120, 255, 255, 255), true);   
   }
   
   // desenho os logos
   // primeiro o básico
   int basico = navePrincipal->QualTipoTiroBasico(); 

   central->Device()->getVideoDriver()->draw2DImage(EscolheLogo(basico), position2d<s32>(ConverteX(10), ConverteY(540)), rect<s32>(0, 0, logoLaser->getOriginalSize().Height, logoLaser->getOriginalSize().Width), NULL, SColor(120 + (135 * navePrincipal->QualTempoBonus(basico) / TEMPO_BONUS), 255, 255, 255), true);
   
   // agora os outros
   int quantosForam = 1;
   for (int i = 0; i < QTD_TIPOS_TIROS; i++)
   {
      if (i != basico && navePrincipal->QualTempoBonus(i) > 0) //desenho esse
      {
         central->Device()->getVideoDriver()->draw2DImage(EscolheLogo(i), position2d<s32>(ConverteX(10 + (60 * quantosForam)), ConverteY(540)), rect<s32>(0, 0, EscolheLogo(i)->getOriginalSize().Height, EscolheLogo(i)->getOriginalSize().Width), NULL, SColor((255 * navePrincipal->QualTempoBonus(i)) / TEMPO_BONUS, 255, 255, 255), true);   
         quantosForam++;
      }
   }   
}


//--------------------------------------------------------------------------------------
void Interface::Atualiza(void)
{
   if (navePrincipal == NULL) return;
   fase = (Fase *) central->Fase();
   tamanhoTela = central->Device()->getVideoDriver()->getScreenSize();
   
   if (transicaoLife == 0) //não está na transição do life
   {
      if (abs((int)(navePrincipal->LifePotencial() - lifePotencialAnterior)) > 1) //houve uma mudança no life da nave
      {
         transicaoLife = TEMPO_TRANSICAO;
      }
   }
   if (transicaoLife > 0) transicaoLife--;
   if (transicaoLife == 0)
   {
      lifeAnterior = navePrincipal->Life();
      lifePotencialAnterior = navePrincipal->LifePotencial();
   }
   
}

//--------------------------------------------------------------------------------------
Interface::Interface(Central *centralAux)
{
   central = centralAux;
   tamanhoTela = central->Device()->getVideoDriver()->getScreenSize();
   
   alvo = LeTexturaConvertida("imagens/alvo.bmp");
   central->Device()->getVideoDriver()->makeColorKeyTexture(alvo,	core::position2d<s32>(0, 0));
	logoLaser = LeTexturaConvertida("imagens/logoLaser.jpg"); 
   logoMissil = LeTexturaConvertida("imagens/logoMissil.jpg");
   logoMultiplo = LeTexturaConvertida("imagens/logoMultiplo.jpg");  
   cockpit = LeTexturaConvertida("cockpit.bmp"); 
   central->Device()->getVideoDriver()->makeColorKeyTexture(cockpit,	core::position2d<s32>(10, 10));
   transicaoLife = 0;
   
   //procuro quem é a nave principal
   list<void *>::Iterator lista;
   navePrincipal = (Objeto *) central->PrimeiroObjeto(&lista);
   
   while (navePrincipal != NULL && navePrincipal->Mensagem(QUEM_VOCE, NULL) != JOGADOR)
   {
      navePrincipal = (Objeto *) central->ProximoObjeto(&lista);
   }
   lifeAnterior = navePrincipal->Life(); 
   lifePotencialAnterior = navePrincipal->LifePotencial();
   transparenciaLife = new Fader(CLARO_ESCURO_CLARO, 100, 100, 100, 100, 255);
}

//---------------------------------------------------------------------------------
Interface::~Interface(void)
{
   delete transparenciaLife;
}
