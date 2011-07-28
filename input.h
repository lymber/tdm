struct Dados
{  
   bool atira, deslizaesq, deslizadir, tras, frente, esquerda, direita;
   int qualCamera;
};

/// \brief Classe que controla o input do jogo
///
/// Trata os dados provenientes do teclado e do joystick
class Input
{
  
  /// \brief struct que cont�m booleandos passados para Jogador indicando o que ele deve fazer.
  ///
  struct Dados dados, teclas, botoes;

  /// \brief Inicializa teclas como n�o pressionadas.
  ///
  void ZeraTudo(void);

  /// \brief O joystick.
  Joystick *stick;

public:

  /// \brief Passa o status de uma dada tecla
  /// 
  /// \param tecla: vari�vel booleana
  /// \return O estado (pressionada ou n�o) de tecla.
  Dados PassaTeclas(void);

  /// \brief Trata eventos vindos do teclado e do joystick para a nave do jogador.
  ///
  /// \param evento: qual evento ocorreu
  /// \param bool: status da tecla (pressionada ou solta)
  /// \return true se � pegou algo utilizado pela nave, e false em
  /// caso contr�rio.
  bool OnEvent(const SEvent &evento);

  /// \brief Atualiza o status do joystick.
  void Atualiza(void);

  /// \brief Construtor
  ///
  Input(void);
  
  /// \brief Destrutor
  ///
  ~Input(void);

};
