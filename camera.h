///\brief Controla as c�meras
///
/// Controla as propriedades das c�meras: posi��o, dire��o em que olha e, futuramente, a transi��o suave de uma c�mera para outra
///
class Camera
{
   ///\brief Timer do deal with delay between 2 changes in the camera mode
   ///
   int timer;
   
     

   ///\brief Para acessarmos as fun��es da classe Central (vide sua documenta��o)
  /// 
  Central *central;

  ///\brief Indica o modo da c�mera
  ///
  ///Os modos s�o
  ///
  /// DE_CIMA: vista de cima da nave;
  ///
  /// DE_LADO: vista na diagonal da nave;
  ///
  /// DE_TRAS: vista de tr�s da nave;
  ///
  /// DE_DENTRO: vista de dentro da nave.
  int modo;

  ///\brief Zoom da c�mera
  ///
  ///Cont�m a dist�ncia entre a c�mera de cima e a nave
  float zoom;

  ///\brief A c�mera atual
  ///
  ICameraSceneNode* node;

  ///\brief Objeto atual (a nave do jogador)
  ///
  Objeto *nave;

  ///\brief Buffer de posi��es da c�mera.
  ///
  ///Um buffer de posi��es que cont�m as 10 �ltimas posi��es da c�mera para dar o efeito de atraso da c�mera em rela��o � nave quando vista de tr�s.
  vector3df bufferPos[TEMPO_ATRASO_CAMERA];

  ///\brief Buffer de referenciais da c�mera.
  ///
  ///Um buffer de referenciais que cont�m os 10 �ltimos referenciais da c�mera para dar o efeito de atraso da c�mera em rela��o � nave quando vista de tr�s.
  matrix4 bufferRef[TEMPO_ATRASO_CAMERA];

 public:
  /// Diz qual � o modo atual da camera
  int QualModo(void){return modo;};

  /// Devolve a posi��o da c�mera.
  vector3df Posicao(void){return node->getPosition();};

  /// Devolve o "alvo" da c�mera.
  vector3df OlhandoPara(void){return node->getTarget();};
  
  ///\brief Altera o valor do modo da c�mera.
  ///
  /// \param qual: um inteiro que � repassado para a vari�vel modo, al�m de inicializar o buffer de posi��es e referenciais para o modo DE_TRAS.
  void MudaModo(int qual);
  
  ///\brief Atualiza a c�mera.
  ///
  /// Aqui s�o calculadas as posi��es e referenciais das c�mera e processadas as instru��es de mudan�a de modo.
  void Atualiza(void);

  /// O construtor da c�mera
  Camera(Central *centralAux);
};
