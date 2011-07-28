#include "corajoso.h"

//----------------------------------------------------------------------------------
int Corajoso::Mensagem(int msg, void *param)
{
   switch (msg)
   {
      case QUEM_VOCE: return INIMIGO;
      case SOLIDO:    return SIM;
   }
   
   return Nave::Mensagem(msg, param);
}

//----------------------------------------------------------------------------------
void Corajoso::Atualiza(void)
{
   //procura por quem é a nave principal na central
    
   list<void *>::Iterator lista;
   Objeto *nave = (Objeto *) central->PrimeiroObjeto(&lista);
   
   while (nave != NULL && nave->Mensagem(QUEM_VOCE, NULL) != JOGADOR)
   {
      nave = (Objeto *) central->ProximoObjeto(&lista);
   } 
   if (nave == NULL) return; //por algum motivo, a nave principal não está na central
   
   ZeraComandos();
   
   //tenta se afastar dos outros inimigos
   Objeto *outro = InimigoMaisProximo();
   
   if (outro != NULL && outro->Distancia(Posicao()) < 10)
   {
      if (NaEsquerda(outro->Posicao())) JogadaDeLadoEsq(true);
      if (NaDireita(outro->Posicao())) JogadaDeLadoDir(true);
      if (NaTras(outro->Posicao())) ParaFrente(true);
      if (NaFrente(outro->Posicao())) ParaTras(true);
   }
   
   if (nave->NaFrente(Posicao())) //se eu estou na frente do outro, melhor afastar
   {
      if (NaEsquerda(nave->Posicao())) ParaEsquerda(true);
      else ParaDireita(true);

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
Corajoso::Corajoso(Central *central, const char *qualNave)
   : Nave(central, qualNave)
{
   //tipoTiroBasico = TIPO_LASER;
   //tempoDeRecargaTotal[tipoTiroBasico] = 2 * TEMPO_CURTO;
}
