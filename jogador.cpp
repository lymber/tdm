#include "jogador.h"

//--------------------------------------------------------------------
void Jogador::Atualiza(void)
{
  Atira(input->PassaTeclas().atira);
  JogadaDeLadoEsq(input->PassaTeclas().deslizaesq);
  JogadaDeLadoDir(input->PassaTeclas().deslizadir);
  ParaFrente(input->PassaTeclas().frente);
  ParaTras(input->PassaTeclas().tras);
  ParaDireita(input->PassaTeclas().direita);
  ParaEsquerda(input->PassaTeclas().esquerda);
  ((Camera *) (central->QualCamera()))->MudaModo(input->PassaTeclas().qualCamera);

  /*if(input->PassaTeclas().cameracima) ((Camera*)(central->QualCamera()))->MudaModo(DE_CIMA);
  if(input->PassaTeclas().cameralado) ((Camera*)(central->QualCamera()))->MudaModo(DE_LADO);
  if(input->PassaTeclas().cameratras) ((Camera*)(central->QualCamera()))->MudaModo(DE_TRAS);
  if(input->PassaTeclas().cameradentro) ((Camera*)(central->QualCamera()))->MudaModo(DE_DENTRO);*/

  Nave::Atualiza();
  morto = false; //faço isso porque eu controlo se morri ou não por enquanto
}

//-----------------------------------------------------------------
int Jogador::Mensagem(int qual, void *param)
{
   switch (qual)
   {
      case QUEM_VOCE: return JOGADOR;
      case SOLIDO   : return SIM;
      case MODO_DE_DENTRO: node->setVisible(false); return NADA;
      case SAIU_MODO_DE_DENTRO: node->setVisible(true); return NADA;
   }
   
   return Nave::Mensagem(qual, param);
}

//---------------------------------------------------------------
Jogador::Jogador(Central *central, Input *inputAux)
: Nave(central, "naves/pitagoras.nav")
{
   //tipoTiroBasico = TIPO_LASER;
   //tempoDeRecargaTotal[tipoTiroBasico] = 2 * TEMPO_CURTO;
  input = inputAux;
}
