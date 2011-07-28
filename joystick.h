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
  
  /// \brief um struct de booleanos que cont�m o status de cada bot�o do joystick relacionado ao movimento do jogador
  Botoes botoes;

  /// \brief Atribui false para todos os bot�es utilizados
  void ZeraBotoes(void);
  
 public:
  
  /// \brief O construtor
  Joystick();
  
  /// \brief O destrutor
  ~Joystick();

  /// \brief Atualiza o joystick
  ///
  /// � chamada a cada vez que ocorre um evento no joystick. Retorna true se foi algo de util 
  void Atualiza(SEvent::SJoystickEvent);

  /// \brief Fornece o status de cada bot�o para outras classes (no momento s� Input recebe isso)
  ///
  /// \return um struct de booleanos contendo o status de cada bot�o do joystick.
  Botoes PassaBotoes(void);
};
