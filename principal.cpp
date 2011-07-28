#include "principal.h"

//-------------------------------------------------------------------------------
//construo a nave, o engine...
void Principal::ConstroiTudo(void)
{
	video::E_DRIVER_TYPE driverType;

	std::cout << "Escolha o driver de video para renderizar o video:\n" \
		" (a) Direct3D 9.0c\n (b) Direct3D 8.1\n (c) OpenGL 1.5\n"\
		" (d) Software Renderer\n (e) Burning's Software Renderer\n"\
		" (f) NullDevice\n (otherKey) exit\n\n";

	char i;
	bool tela=false;

	std::cin >> i;

	switch(i)
	{
		case 'a': driverType = video::EDT_DIRECT3D9;break;
		case 'b': driverType = video::EDT_DIRECT3D8;break;
		case 'c': driverType = video::EDT_OPENGL;   break;
		case 'd': driverType = video::EDT_SOFTWARE; break;
		case 'e': driverType = video::EDT_BURNINGSVIDEO;break;
		case 'f': driverType = video::EDT_NULL;     break;
		default: return;
	}

	std::cout << "Deseja jogar em tela cheia? (s/n)";
	std::cin >> i;

	if(i=='s') tela=true; else tela=false;

	//a resolução pode ser ecolhida onde está 800, 600 se o
	//primeiro false da segunda linha for trocado por true, roda
	//em tela cheia. no modo SOFTWARE, é capaz que fique sem os
	//efeitos de sombra, o que perde bastante a graça...
	device = createDevice(driverType, dimension2d<s32>(800, 600), 16,
			tela, true, false, 0);
   if (!device) return;

	//pego o timer, para fazer o intervalo entre os ciclos
	timer = device->getTimer();
	
	//crio o device de audio
	soundEngine = irrklang::createIrrKlangDevice();
	soundEngine->setDefault3DSoundMaxDistance(50);
	device->setWindowCaption(L"TDM");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

   //aviso que quero usar joystick
   core::array<SJoystickInfo> joystickInfo;
	device->activateJoysticks(joystickInfo);

	//guienv->addStaticText(L"TDM - um teste",
	//	rect<int>(10,10,160,22), true);

	//aviso que sou eu que devo receber os eventos
	device->setEventReceiver(this);

	input = new Input();
	central = new Central(device, soundEngine);
	nave = new Jogador(central, input);
	central->NovoObjeto((Objeto *) nave);

	//crio a interface
	interface = new Interface(central);

	//crio a fase
	fase = new Fase("fases/castelo.fas", central);
	fase->Comeca();
	central->MudaFase(fase);

	//adiciono a câmera
	camera = new Camera(central);
	central->AdicionaCamera(camera);

	//adiciono uma lâmpada no mesmo lugar que a posição inicial da câmera
	smgr->addLightSceneNode(0, core::vector3df(0, 40.0f,0),
		video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 50.0f);
}

//---------------------------------------------------------------------------------------
//É o loop principal do jogo, onde todos são desenhados e atualizados
void Principal::Roda()
{
   if (device == NULL) return;

   while(device->run())
   {
     if (true) //o pause vai entrar aqui depois
     {
         tempoAnterior = timer->getRealTime();
         //Atualizo o input
         input->Atualiza();
     
         //mando os objetos se atualizarem
         list<void *>::Iterator lista;
         Objeto *temp = (Objeto *) central->PrimeiroObjeto(&lista);
         while (temp != NULL)
         {
	         temp->Atualiza();
	         temp = (Objeto *) central->ProximoObjeto(&lista);
         }
     
         //vejo se houve colisão nos objetos
         list<void *>::Iterator primeiro;
         list<void *>::Iterator segundo;   
         Objeto *um = (Objeto *) central->PrimeiroObjeto(&primeiro);
         while (um != NULL)
         {
            segundo = primeiro;
            Objeto *dois = (Objeto *) central->ProximoObjeto(&segundo);
            while (dois != NULL)
	         {
	            if (um->Bateu(dois))
	            {
		            um->BateuNeste(dois);
		            dois->BateuNeste(um);
	            }
	            dois = (Objeto *) central->ProximoObjeto(&segundo);
	         } 
            um = (Objeto *) central->ProximoObjeto(&primeiro);
         }
         fase->Atualiza();
         interface->Atualiza();
         camera->Atualiza();
     
         //retiro os mortos
         temp = (Objeto *) central->PrimeiroObjeto(&lista);
         while (temp != NULL)
         {
	         if (temp->Morto())
	         {
	            if (temp->Mensagem(QUEM_VOCE, NULL) == INIMIGO) fase->MorreuInimigo();
	            delete temp;
	            temp = (Objeto *) central->ApagaObjeto(&lista); //apaga esse elemento
	         }
	         else temp = (Objeto *) central->ProximoObjeto(&lista);
         }
     
         //atualizo a posição para o som
         central->SoundEngine()->setListenerPosition(camera->Posicao(), camera->OlhandoPara());
     
         device->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));
         device->getSceneManager()->drawAll();
         device->getGUIEnvironment()->drawAll();
         interface->Desenha();
         device->getVideoDriver()->endScene();
      }
      //se ainda não deu o tempo mínimo
      while (timer->getRealTime() - tempoAnterior < TEMPO_CICLO);
   }
   
   list<void *>::Iterator lista;
   Objeto *obj = (Objeto *) central->PrimeiroObjeto(&lista);
   
   while (obj != NULL)
     {
       delete obj;
       obj = (Objeto *) central->ProximoObjeto(&lista);
     }
   
   delete input;
   delete interface;
   delete fase;
   delete central;
   delete camera;
   //soundEngine->drop();
   device->drop();
   
}

//----------------------------------------------------------------------------
//Recebe o eventos (teclado, mouse etc) e repassa para quem for necessário
bool Principal::OnEvent(const SEvent &evento)
{
  if (evento.EventType == EET_KEY_INPUT_EVENT)
    //a tecla ESC mudou de status (pressionada/nao pressionada)
    if (evento.KeyInput.Key == KEY_ESCAPE){
      device->closeDevice(); 
      return true;
  }
 
  return input->OnEvent(evento); //evento.KeyInput.Key, evento.KeyInput.PressedDown);
}

//---------------------------------------------------------------------------------
Principal::Principal(void)
{
  device = NULL;
  tempoAnterior = 0;
}

//---------------------------------------------------------------------------------
Principal::~Principal(void)
{ 
}
