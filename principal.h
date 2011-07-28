/// \brief Classe que controla todas as outras
///
/// Avisa as outras quando chega um evento, manda todas se atualizarem,
/// é quem controla o loop
class Principal : public IEventReceiver
{

   /// \brief Guarda todas as informações do engine 3D
   ///
   /// Pode ser encontrado dentro da central
   IrrlichtDevice *device;
   
   /// \brief Guarda todas as informações do engine de som
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
   
   /// \brief Guarda todas as informações que devem ser compartilhadas
   ///
   /// Tem uma lista ligada de todos os objetos do jogo, guarda as informações dos engines, a fase atual etc.
   Central *central;

   /// \brief Trata o input do teclado e do joystick
   ///
   Input *input;
   
   /// \brief A câmera atual
   ///
   /// Ela que controla qual o modo de visão atual
   Camera *camera;

   /// \brief Dá as informações para o usuário
   ///
   /// Mostra o life do jogador e dos inimigos, quantos ainda devem ser mortos etc.
   Interface *interface;

   /// \brief Fase atual do jogo
   ///
   /// É quem controla quais e quantos inimigos deve estar presentes, qual o cenário, música etc.
   Fase *fase;
     
   public:
   /// \brief Carrega os objetos necessários para o loop
   ///
   /// Carrega os engines, escolhe a resolução, modo de exibição. Cria a fase (só tem uma, por enquanto), a nave do jogador etc.
   void ConstroiTudo(void);
      
   /// \brief É onde está o loop principal do jogo
   ///
   /// Durante o loop, manda todos os objetos se atualizarem. Depois manda o engine criar a imagem que deve ser exibida. Manda a interface se atualizar e se desenhar. 
   void Roda(void);

   /// \brief Recebe eventos do sistema
   ///
   /// Recebe eventos do teclado. Encerra o device se for ESC e repassa para Input em caso contrário
   virtual bool OnEvent(const SEvent &event);
      
   /// \brief Construtor
   ///
   /// Só deixa tudo ajeitado para a ConstroiTudo
   Principal(void);
   
   /// \brief Destrutor
   ///
   ~Principal(void);

};
