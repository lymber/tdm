#include "camera.h"

//--------------------------------------------------------------------------------
void Camera::MudaModo(int qual)
{
   if (timer > 0) return; //it has to wait a little more
   else timer = TEMPO_CURTO;   

   if (qual == NADA) return; //it has nothing to do

   if (qual == DE_CIMA || qual == DE_LADO || qual == DE_TRAS || qual == DE_DENTRO)
      modo = qual;

   if (qual == PROXIMA)
   {
      modo++;
      if (modo >= DE_CIMA + QUANTAS_CAMERAS) modo = DE_CIMA;
   }

   if (qual == ANTERIOR)
   {
      modo--;
      if (modo < DE_CIMA) modo = DE_CIMA + QUANTAS_CAMERAS - 1;   
   }   

   for(int i=0; i < TEMPO_ATRASO_CAMERA; i++){
	   bufferPos[i] = nave->Posicao();
	   bufferRef[i] = nave->Referencial();
   }

   if (nave != NULL)
   {
      if (modo == DE_DENTRO) nave->Mensagem(MODO_DE_DENTRO, NULL);
      else nave->Mensagem(SAIU_MODO_DE_DENTRO, NULL);
   }
   return;
}

//--------------------------------------------------------------------------------
// Calcula posição da camera conforme o modo atual
void Camera::Atualiza(void)
{
   vector3df temp;
   float zoomPre = 0;

   if (timer > 0) timer--;   

   switch (modo)
	{
	case DE_CIMA: temp = vector3df(0, 0, -1);
		bufferRef[0].rotateVect(temp);
		node->setUpVector(temp);
		if (nave->InimigoMaisProximo() != NULL){
		zoomPre = (nave->Distancia(nave->InimigoMaisProximo()->Posicao())+5)/tan(PI/5);
		}
		if (fabs(zoom - zoomPre) > 0.1f){
			if (zoom > zoomPre) zoom-=0.1f;
			else zoom+=0.1f;
		}
		if (zoom < 40)
			node->setPosition(bufferPos[0] + vector3df(0, 40, 0));
		else if(zoom>80)
			node->setPosition(bufferPos[0] + vector3df(0, 80, 0));
		else node->setPosition(bufferPos[0] + vector3df(0, zoom, 0));
		node->setTarget(bufferPos[0]);
		break;
	case DE_LADO: node->setTarget(vector3df(0,0,-1));
		node->setUpVector(vector3df(0,1,0));
		node->setPosition(nave->Posicao() + vector3df(-20, 40, 0));
		node->setTarget(nave->Posicao());
		break;
	case DE_TRAS: temp = vector3df(0, 15, 15);
		bufferRef[0].rotateVect(temp);
		node->setPosition(bufferPos[0] + temp);
		node->setTarget(bufferPos[0] + (15 * nave->VetorFrente()));
		temp=vector3df(0,1,0);
		bufferRef[0].rotateVect(temp);
		node->setUpVector(temp);
		break;
	case DE_DENTRO: node->setPosition(nave->Posicao() + nave->VetorCimaReal());
		node->setTarget(nave->Posicao() + (5 * nave->VetorFrente()));
		node->setUpVector(nave->VetorCimaReal());
		break;
	}

// Atualiza o buffer

   for(int i=0; i < TEMPO_ATRASO_CAMERA-1; i++){
	   bufferPos[i] = bufferPos[i+1];
	   bufferRef[i] = bufferRef[i+1];
   }

   bufferPos[TEMPO_ATRASO_CAMERA-1] = nave->Posicao();
   bufferRef[TEMPO_ATRASO_CAMERA-1] = nave->Referencial();
}

//--------------------------------------------------------------------------------
Camera::Camera(Central *centralAux)
{
   central = centralAux;
   node = central->Device()->getSceneManager()->addCameraSceneNode(0, vector3df(0, 40, 0), vector3df(0,0,0));
   modo = DE_CIMA;
   zoom=40;

   list<void *>::Iterator lista;

   timer = 0;   
   nave = (Objeto *) central->PrimeiroObjeto(&lista);

   while (nave != NULL && nave->Mensagem(QUEM_VOCE, NULL) != JOGADOR)
   {
      nave = (Objeto *) central->ProximoObjeto(&lista);
   }
}

