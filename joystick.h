struct Botoes
{
   bool atira, deslizaesq, deslizadir, tras, frente, esquerda, direita;
   int qualCamera;
};

/// \brief Trata dados provenientes do joystick
///
/// recebe eventos do joystick e os manda para a classe Input
class Joystick
{

  /// \brief O joystick
  //SDL_Joystick *stick;
  
  /// \brief um struct de booleanos que contêm o status de cada botão do joystick relacionado ao movimento do jogador
  Botoes botoes;

  /// \brief Atribui false para todos os botões utilizados
  void ZeraBotoes(void);
  
 public:
  
  /// \brief O construtor
  Joystick();
  
  /// \brief O destrutor
  ~Joystick();

  /// \brief Atualiza o joystick
  ///
  /// É chamada a cada vez que ocorre um evento no joystick. Retorna true se foi algo de util 
  void Atualiza(SEvent::SJoystickEvent);

  /// \brief Fornece o status de cada botão para outras classes (no momento só Input recebe isso)
  ///
  /// \return um struct de booleanos contendo o status de cada botão do joystick.
  Botoes PassaBotoes(void);
};
