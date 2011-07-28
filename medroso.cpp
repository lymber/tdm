#include "medroso.h"

//----------------------------------------------------------------------------------
int Medroso::Mensagem(int msg, void *param)
{
   switch (msg)
   {
      case QUEM_VOCE: return INIMIGO;
      case SOLIDO:    return SIM;
   }

   return Nave::Mensagem(msg, param);
}

//----------------------------------------------------------------------------------
void Medroso::Atualiza(void)
{
   //procura por quem é a nave principal na central
   Objeto *nave = Procura(JOGADOR); 
    
   if (nave == NULL) return; //por algum motivo, a nave principal não está na central
   
   ZeraComandos();
   
   
   //tenta se afastar dos outros inimigos
   Objeto *outro = InimigoMaisProximo();
   
   if (outro != NULL && outro->Distancia(Posicao()) < 10)
   {
      if (NaEsquerda(outro->Posicao())) JogadaDeLadoDir(true);
      if (NaDireita(outro->Posicao())) JogadaDeLadoEsq(true);
      if (NaTras(outro->Posicao())) ParaFrente(true);
      if (NaFrente(outro->Posicao())) ParaTras(true);
   }
   
   if (nave->NaFrente(Posicao())) //se eu estou na frente do outro, melhor fugir
   {
      if (NaEsquerda(nave->Posicao())) ParaDireita(true);
      else ParaEsquerda(true);

      if (NaFrente(nave->Posicao())) ParaTras(true);
      else ParaFrente(true);
   }
   else //se ele está de costas para mim, vamos atacar
   {
     if (NaEsquerda(nave->Posicao())) ParaEsquerda(true);
     else ParaDireita(true);
     if (NaFrente(nave->Posicao()))
     {
         if (Distancia(nave->Posicao()) > 10) ParaFrente(true);
     }
     else ParaTras(true);    
   }
   if (NaFrente(nave->Posicao())) Atira(true);
   else Atira(false);
   
   Nave::Atualiza();
}

//----------------------------------------------------------------------------------------
Medroso::Medroso(Central *central, const char *qualNave)
   : Nave(central, qualNave)
{
   //tipoTiroBasico = TIPO_MISSIL;
   //tempoDeRecargaTotal[tipoTiroBasico] = TEMPO_LONGO + TEMPO_CURTO;
}
