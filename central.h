/// \brief Classe que agrupa diversas informações
///
/// Guarda informações que precisam estar disponíveis para todos os objetos. Por exemplo, os engines, a lista de todos os objetos etc. Ela não faz nada com as informções, apenas as manté©m para consultas.

class Central{

  /// \brief Engine 3D
  IrrlichtDevice *device;
   
  /// \brief Engine de som
  irrklang::ISoundEngine* soundEngine;
   
  /// \brief Fase atual
  void *fase;
   
  /// \brief Camera atual
  void *camera;

  /// \brief Lista dos objetos
  ///
  /// Guarda todos os objetos como void*. Atenção, só coloque instâncias que extendam Objeto de forma pública. É acessada da seguinte maneira:
  ///
  /// list<void *>::Iterator lista; //precisa disso para guardar a "posição" na lista
  /// Objeto *temp = (Objeto *) central->PrimeiroObjeto(&lista); -- aqui temp aponta para o primeiro objeto da lista
  /// while (temp != NULL) //temp ganha o valor NULL quando a lista acaba
  /// {
  ///   temp = (Objeto *) central->ProximoObjeto(&lista); //temp passa para o prÃ³ximo objeto
  /// }
   list<void *>listaObjetos;
   
   public:  
      /// \brief Atualiza o valor da fase atual
      ///
      /// \param qual Aponta para a fase atual
      void MudaFase(void *qual){fase = qual;};
      
      /// \brief Adiciona nova câmera
      ///
      /// \param camera aponta para a câmera adicionada
      void *AdicionaCamera(void *qual){camera = qual;};

      /// \brief Qual câmera estou usando
      void *QualCamera(void){return camera;};

      /// \brief Qual a fase atual
      void *Fase(void){return fase;};

      /// \brief Retorna o primeiro objeto da lista
      ///
      /// Retorna o primeiro objeto da lista e deixa o iterador nessa posição
      /// \param atualListaObejtos Um iterador para trabalhar com a lista
      void *PrimeiroObjeto(list<void *>::Iterator *atualListaObjetos);

      /// \brief Delvolve o objeto seguinte da lista
      ///
      /// Faz o iterador ir para a posição seguinte e retorna o obejto de tal posição
      /// \param atualListaObjetos Um iterador para trabalhar com a lista
      void *ProximoObjeto(list<void *>::Iterator *atualListaObjetos);
      
      /// \brief Apaga o objeto atual da lista
      ///
      /// Apaga o objeto atual da lista e o retorna
      void *ApagaObjeto(list<void *>::Iterator *atualListaObjetos);
      
      /// \brief Adiciona um objeto na lista
      ///
      /// \param qual Objeto a ser adicionado
      void NovoObjeto(void *qual);
      
      /// \brief Retorna o valor do Engine 3D
      IrrlichtDevice *Device(void){return device;};
      
      /// \brief Retorna o valor do Engine de Som
      irrklang::ISoundEngine* SoundEngine(void){return soundEngine;};
      
      /// \brief Construtor
      ///
      /// Inicializa alguns valores e cria a lista de objetos vazia
      /// \param deviceAux O engine 3D
      /// \param soundEngineAux O engine de som
      Central(IrrlichtDevice *deviceAux, irrklang::ISoundEngine* soundEngineAux);

      /// \brief Destrutor
      ///
      /// Apaga a lista de objetos (mas não remove as instâncias apontadas por seus elementos. Cada uma delas precisa ser removida externamente)
      ~Central(void);
};
