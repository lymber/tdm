/// \brief Controla as fases do jogo
///
/// Lê a fase a partir de um arquivo xml, controla quantos inimigos podem ficar ativos ao mesmo tempo, quantos vão participar no total etc.
class Fase
{
   /// \brief Tem todos os objetos
   Central *central;
   
   /// \brief Node do engine para o cenário
   ///
   /// Guarda a descrição geométrica do cenário, sua posição etc.
   ISceneNode *node;
   
   /// \brief Total de inimigos para a fase atual
   ///
   /// Lê a partir do arquivo
   int totalInimigos;
   
   /// \brief Máximo de inimigos possíveis ao mesmo tempo
   ///
   /// Lê a partir do arquivo
   int maximoInimigos;
   
   /// \brief Quantos inimigos já foram feitos nesta fase
   ///
   /// Começa em 0 e vai até totalInimigo. 
   int totalFeitos;
   
   /// \brief Quantidade de inimigos atualmente na tela
   ///
   /// Vai de 0 até maximoInimigos
   int quantosAtual;
   
   /// \brief Quantidade de posições iniciais possíveis para os inimigos
   ///
   /// Lê do arquivo
   int quantasPosicoesInimigos;
   
   /// \brief Posição inicial do jogador
   ///
   /// Lê do arquivo
   vector3df posicaoInicialJogador;

   /// \brief Vetor com as posições iniciais possíveis dos inimigos
   ///
   /// Tem quantasPosicoesInimigos elementos. Lê a partir do arquivo 
   vector3df *posicaoInicialInimigos;
   
   /// \brief Quais inteligências para inimigos estão disponíveis para esta fase
   ///
   /// Vetor com uma posição para cada tipo de inimigo. Lê do arquivo.
   bool possiveisIA[QTD_INIMIGOS];
   
   /// \brief Quais naves estão disponíveis para esta fase
   ///
   /// Vetor com uma posição para cada tipo de inimigo. Lê do arquivo.
   bool navesPossiveis[QTD_INIMIGOS];
   
   /// \brief Cria um novo inimigo
   ///
   /// \param qual Qual inimigo a ser criado
   /// \returns Ponteiro para o inimigo criado
   Objeto *NovoInimigo(int qualIA, int qualNave);
   
   /// \brief Diz quantos tipos de inimigos há para essa fase
   int QuantosPossiveis(void);
   
   /// \brief Diz quantos tipos de naves há para essa fase
   int QuantasNavesPossiveis(void);
   
   /// \brief Sorteia uma posição inicial para um inimigo entre as possíveis
   vector3df EscolhePosicaoInimigo(void);
   
   /// \brief Sorteia um inimigo entre os possíveis
   ///
   /// Sorteia e cria um inimigo entre os possíveis. 
   /// \returns Um ponteiro para o inimigo criado
   Objeto *SorteiaInimigo(void);

   /// \brief Lê a descrição da fase a partir de um arquivo
   ///
   /// \param arquivo Nome do arquivo a ser lido
   void LeArquivo(char *arquivo);
   
   public:
      /// \brief Quantos inimigos ainda precisam ser mortos
      ///
      /// Inclui quantos ainda precisam ser criados e quantos estão ativos na tela
      int QuantosInimigosRestam(void);
      
      /// \brief Avisa a fase que um inimigo foi morto
      ///
      /// Serve para que a fase possa atualizar as contas de quantos faltam etc.
      void MorreuInimigo(void);
      
      /// \brief Atualiza a fase
      ///
      /// Verifica se precisa ser adicionado um inimigo. Em caso afirmativo, adiciona um inimigo
      void Atualiza(void);
      
      /// \brief Inicializa a fase para começar a jogar
      void Comeca(void);
      
      /// \brief Construtor
      ///
      /// \param arquivo Nome do arquivo com a descrição da fase
      /// \param centralAux Onde estão os objetos
      Fase(char *arquivo, Central *centralAux);
      
      /// \brief Destrutor
      ~Fase(void);
};
