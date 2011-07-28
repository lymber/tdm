#include "input.h"

//-------------------------------------------------------------------------------
//trata eventos do teclado e do joystick

bool Input::OnEvent(const SEvent &evento)
{
   if (evento.EventType == EET_KEY_INPUT_EVENT) //foi (des)pressionada uma tecla
   {
      switch (evento.KeyInput.Key) 
      {	
         case KEY_KEY_S: teclas.atira = evento.KeyInput.PressedDown; return true;
	      case KEY_KEY_A: teclas.deslizaesq = evento.KeyInput.PressedDown; return true;
	      case KEY_KEY_D: teclas.deslizadir = evento.KeyInput.PressedDown; return true;
	      case KEY_DOWN: teclas.tras = evento.KeyInput.PressedDown; return true;
	      case KEY_UP: teclas.frente = evento.KeyInput.PressedDown; return true;
	      case KEY_LEFT: teclas.esquerda = evento.KeyInput.PressedDown; return true;
	      case KEY_RIGHT: teclas.direita = evento.KeyInput.PressedDown; return true;
	      case KEY_F1: teclas.qualCamera = DE_CIMA; return true;
	      case KEY_F2: teclas.qualCamera = DE_LADO; return true;
         case KEY_F3: teclas.qualCamera = DE_TRAS; return true;
	      case KEY_F4: teclas.qualCamera = DE_DENTRO; return true;
	      
	   }
      return false;
   }
   if (evento.EventType == irr::EET_JOYSTICK_INPUT_EVENT) //algo aconteceu no joystick
   {
      stick->Atualiza(evento.JoystickEvent);
      return true;
   }
   
   return false;

}

//---------------------------------------------------------------------------------
void Input::Atualiza(void)
{
  //Pega status dos botões do joystick

  botoes.atira = stick->PassaBotoes().atira;

  botoes.deslizaesq = stick->PassaBotoes().deslizaesq;
  botoes.deslizadir = stick->PassaBotoes().deslizadir;

  botoes.tras = stick->PassaBotoes().tras;
  botoes.frente = stick->PassaBotoes().frente;
  botoes.esquerda = stick->PassaBotoes().esquerda;
  botoes.direita = stick->PassaBotoes().direita;
  botoes.qualCamera = stick->PassaBotoes().qualCamera;
  

  //Manda o movimento do teclado ou joystick para Jogador.
  
  dados.atira = botoes.atira || teclas.atira;

  dados.deslizaesq = botoes.deslizaesq || teclas.deslizaesq;
  dados.deslizadir = botoes.deslizadir || teclas.deslizadir;

  dados.frente = botoes.frente || teclas.frente;
  dados.tras = botoes.tras || teclas.tras;
  dados.esquerda = botoes.esquerda || teclas.esquerda;
  dados.direita = botoes.direita || teclas.direita;

   dados.qualCamera = teclas.qualCamera;
   if (botoes.qualCamera != NADA) dados.qualCamera = botoes.qualCamera;
}

//---------------------------------------------------------------------------------
Dados Input::PassaTeclas(void)
{
  return dados;
}

//---------------------------------------------------------------------------------
void Input::ZeraTudo(void)
{
  teclas.atira = false;
  teclas.deslizaesq = false;
  teclas.deslizadir = false;
  teclas.tras = false;
  teclas.frente = false;
  teclas.esquerda = false;
  teclas.direita = false;
  teclas.qualCamera = NADA;

  botoes.atira = false;
  botoes.deslizaesq = false;
  botoes.deslizadir = false;
  botoes.tras = false;
  botoes.frente = false;
  botoes.esquerda = false;
  botoes.direita = false;
  botoes.qualCamera = NADA;

  dados.atira = false;
  dados.deslizaesq = false;
  dados.deslizadir = false;
  dados.tras = false;
  dados.frente = false;
  dados.esquerda = false;
  dados.direita = false;
  dados.qualCamera = NADA;
}

//---------------------------------------------------------------------------------
Input::Input(void)
{
  stick = new Joystick();
  ZeraTudo();
}

//---------------------------------------------------------------------------------
Input::~Input(void)
{
  delete stick;
}
