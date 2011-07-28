#include <irrlicht.h>
#include <irrKlang.h>
//#include <SDL/SDL.h>
#include <iostream>

//essas coisas são só para não precisar ficar escrevendo estas palavras na frente de tudo...
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include "const.h"
#include "fader.cpp"
#include "central.cpp"
#include "objeto.cpp"
#include "itemLaser.cpp"
#include "itemMissil.cpp"
#include "itemMultiplo.cpp"
#include "laser.cpp"
#include "missil.cpp"
#include "multiplo.cpp"
#include "nave.cpp"
#include "medroso.cpp"
#include "corajoso.cpp"
#include "joystick.cpp"
#include "input.cpp"
#include "camera.cpp"
#include "jogador.cpp"
#include "fase.cpp"
#include "interface.cpp"
#include "principal.cpp"

#ifdef _IRR_WINDOWS_
#include <windows.h>
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#endif


//********************************************************************************

#ifdef _IRR_WINDOWS_
int WINAPI WinMain (HINSTANCE hInstance, 
                        HINSTANCE hPrevInstance, 
                        PSTR szCmdLine, 
                        int iCmdShow) 
#endif

#ifndef _IRR_WINDOWS_
int main()
#endif
{
   srand(time(0));
   Principal *princ = new Principal();
   princ->ConstroiTudo();
   princ->Roda();
   delete princ;
}
