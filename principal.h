/// \brief Classe que controla todas as outras
///
/// Avisa as outras quando chega um evento, manda todas se atualizarem,
/// � quem controla o loop
class Principal : public IEventReceiver
{

   /// \brief Guarda todas as informa��es do engine 3D
   ///
   /// Pode ser encontrado dentro da central
   IrrlichtDevice *device;
   
   /// \brief Guarda todas as informa��es do engine de som
   ///
   /// Pode ser encontrado dentro da central
   irrklang::ISoundEngine* soundEngine;

   /// Timer para controlar a velocidade do jogo
   ITimer *timer;
   
   /// \brief Quantidade de ms desde o ultimo ciclo. 
   ///
   /// Serve para controlar a velocidade do jogo
   u32 tempoAnterior;
   
   /// \brief Nave do jogador
   ///
   /// Pode ser encontrado na lista ligada de objetos dentro da central
   Jogador *nave;
   
   /// \brief Guarda todas as informa��es que devem ser compartilhadas
   ///
   /// Tem uma lista ligada de todos os objetos do jogo, guarda as informa��es dos engines, a fase atual etc.
   Central *central;

   /// \brief Trata o input do teclado e do joystick
   ///
   Input *input;
   
   /// \brief A c�mera atual
   ///
   /// Ela que controla qual o modo de vis�o atual
   Camera *camera;

   /// \brief D� as informa��es para o usu�rio
   ///
   /// Mostra o life do jogador e dos inimigos, quantos ainda devem ser mortos etc.
   Interface *interface;

   /// \brief Fase atual do jogo
   ///
   /// � quem controla quais e quantos inimigos deve estar presentes, qual o cen�rio, m�sica etc.
   Fase *fase;
     
   public:
   /// \brief Carrega os objetos necess�rios para o loop
   ///
   /// Carrega os engines, escolhe a resolu��o, modo de exibi��o. Cria a fase (s� tem uma, por enquanto), a nave do jogador etc.
   void ConstroiTudo(void);
      
   /// \brief � onde est� o loop principal do jogo
   ///
   /// Durante o loop, manda todos os objetos se atualizarem. Depois manda o engine criar a imagem que deve ser exibida. Manda a interface se atualizar e se desenhar. 
   void Roda(void);

   /// \brief Recebe eventos do sistema
   ///
   /// Recebe eventos do teclado. Encerra o device se for ESC e repassa para Input em caso contr�rio
   virtual bool OnEvent(const SEvent &event);
      
   /// \brief Construtor
   ///
   /// S� deixa tudo ajeitado para a ConstroiTudo
   Principal(void);
   
   /// \brief Destrutor
   ///
   ~Principal(void);

};
