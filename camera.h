///\brief Controla as câmeras
///
/// Controla as propriedades das câmeras: posição, direção em que olha e, futuramente, a transição suave de uma câmera para outra
///
class Camera
{
   ///\brief Timer do deal with delay between 2 changes in the camera mode
   ///
   int timer;
   
     

   ///\brief Para acessarmos as funções da classe Central (vide sua documentação)
  /// 
  Central *central;

  ///\brief Indica o modo da câmera
  ///
  ///Os modos são
  ///
  /// DE_CIMA: vista de cima da nave;
  ///
  /// DE_LADO: vista na diagonal da nave;
  ///
  /// DE_TRAS: vista de trás da nave;
  ///
  /// DE_DENTRO: vista de dentro da nave.
  int modo;

  ///\brief Zoom da câmera
  ///
  ///Contém a distância entre a câmera de cima e a nave
  float zoom;

  ///\brief A câmera atual
  ///
  ICameraSceneNode* node;

  ///\brief Objeto atual (a nave do jogador)
  ///
  Objeto *nave;

  ///\brief Buffer de posições da câmera.
  ///
  ///Um buffer de posições que contém as 10 últimas posições da câmera para dar o efeito de atraso da câmera em relação à nave quando vista de trás.
  vector3df bufferPos[TEMPO_ATRASO_CAMERA];

  ///\brief Buffer de referenciais da câmera.
  ///
  ///Um buffer de referenciais que contém os 10 últimos referenciais da câmera para dar o efeito de atraso da câmera em relação à nave quando vista de trás.
  matrix4 bufferRef[TEMPO_ATRASO_CAMERA];

 public:
  /// Diz qual é o modo atual da camera
  int QualModo(void){return modo;};

  /// Devolve a posição da câmera.
  vector3df Posicao(void){return node->getPosition();};

  /// Devolve o "alvo" da câmera.
  vector3df OlhandoPara(void){return node->getTarget();};
  
  ///\brief Altera o valor do modo da câmera.
  ///
  /// \param qual: um inteiro que é repassado para a variável modo, além de inicializar o buffer de posições e referenciais para o modo DE_TRAS.
  void MudaModo(int qual);
  
  ///\brief Atualiza a câmera.
  ///
  /// Aqui são calculadas as posições e referenciais das câmera e processadas as instruções de mudança de modo.
  void Atualiza(void);

  /// O construtor da câmera
  Camera(Central *centralAux);
};
