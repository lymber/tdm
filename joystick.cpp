#include "joystick.h"

//---------------------------------------------------------------------------------

Botoes Joystick::PassaBotoes(void)
{
  return botoes;
}

//---------------------------------------------------------------------------------
void Joystick::Atualiza(SEvent::SJoystickEvent joystickData)
{
   const f32 DEAD_ZONE = 0.1f; //só mexo se "mexer" pelo menos 10%
   
   f32 move = (f32) joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
	
   if (move < -DEAD_ZONE) botoes.esquerda = true;
   else if (move > DEAD_ZONE) botoes.direita = true;
   else
   {
      botoes.esquerda = false;
      botoes.direita = false;        
   }
   
   move = (f32) joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / 32767.f;
   if (move < -DEAD_ZONE) botoes.frente = true;
   else if (move > DEAD_ZONE) botoes.tras = true;
   else
   {
      botoes.frente = false;
      botoes.tras = false;   
   }

   //Check firing
   botoes.atira = joystickData.IsButtonPressed(2);

   //Check sliding
   botoes.deslizaesq = joystickData.IsButtonPressed(6);
   botoes.deslizadir = joystickData.IsButtonPressed(7);

   //Muda câmeras
   if(joystickData.IsButtonPressed(5))
      botoes.qualCamera = PROXIMA;
   else if (joystickData.IsButtonPressed(4))
      botoes.qualCamera = ANTERIOR;
   else botoes.qualCamera = NADA;
      

/*
  //SDL_Event event;
  
  //SDL_PollEvent(&event);

  //Atualiza timer
  if (timertiro > 0) timertiro--;
  if (timercamera > 0) timercamera--;

  //Checa tiro
  if(timertiro == 0){
    botoes.atira = SDL_JoystickGetButton(stick,2)==1;
    timertiro=20;
  }

  //Checa deslizadas
  //botoes.deslizaesq = SDL_JoystickGetButton(stick,6)==1;
  //botoes.deslizadir = SDL_JoystickGetButton(stick,7)==1;

  //Muda câmeras
  if(SDL_JoystickGetButton(stick,5) && timercamera == 0){
      botoes.camProx = true;
      botoes.camAnt = false;
      timercamera = 50;    
  }
  else botoes.camProx = false;
      

  if(SDL_JoystickGetButton(stick,4) && timercamera == 0){
      botoes.camAnt = true;
      botoes.camProx = false;
      timercamera = 50;
  }
  else botoes.camAnt = false;
  

  //Checa movimento no eixo x
  if(abs(SDL_JoystickGetAxis(stick,0)-eixox)>8000)
    {
      if (SDL_JoystickGetAxis(stick,0)<-8000) botoes.esquerda = true;
      else if (SDL_JoystickGetAxis(stick,0)>8000) botoes.direita = true;
      else {
	botoes.esquerda = false;
	botoes.direita = false;
      }
    }

  //Checa movimento eixo y
  if(abs(SDL_JoystickGetAxis(stick,1)-eixoy)>8000)
    {
      if (SDL_JoystickGetAxis(stick,1)<-8000) botoes.frente = true;
      else if (SDL_JoystickGetAxis(stick,1)>8000) botoes.tras = true;
      else {
	botoes.tras = false;
	botoes.frente = false;
      }
    }

  eixox=SDL_JoystickGetAxis(stick,0);
  eixoy=SDL_JoystickGetAxis(stick,1);*/
}

//---------------------------------------------------------------------------------
void Joystick::ZeraBotoes(void)
{
  botoes.atira = false;
  botoes.deslizaesq = false;
  botoes.deslizadir = false;
  botoes.tras = false;
  botoes.frente = false;
  botoes.esquerda = false;
  botoes.direita = false;
  botoes.qualCamera = NADA;
}

//---------------------------------------------------------------------------------

Joystick::Joystick(void)
{
	//stick=NULL;

	/*if( SDL_Init( SDL_INIT_JOYSTICK ) == -1 )
		printf("Joystick indisponivel\n");
	else {
		SDL_JoystickEventState(SDL_ENABLE);
		stick = SDL_JoystickOpen(0);
		if( stick == NULL ) printf("Joystick indisponivel!\n");
		printf("Existem %d joysticks conectados\n",SDL_NumJoysticks());
	}*/

	ZeraBotoes();
}

//---------------------------------------------------------------------------------
Joystick::~Joystick()
{
/*	//Close the joystick
	SDL_JoystickClose(stick);

	//Quit SDL
	SDL_Quit();
*/
}
