/// \brief Controla as fases do jogo
///
/// L� a fase a partir de um arquivo xml, controla quantos inimigos podem ficar ativos ao mesmo tempo, quantos v�o participar no total etc.
class Fase
{
   /// \brief Tem todos os objetos
   Central *central;
   
   /// \brief Node do engine para o cen�rio
   ///
   /// Guarda a descri��o geom�trica do cen�rio, sua posi��o etc.
   ISceneNode *node;
   
   /// \brief Total de inimigos para a fase atual
   ///
   /// L� a partir do arquivo
   int totalInimigos;
   
   /// \brief M�ximo de inimigos poss�veis ao mesmo tempo
   ///
   /// L� a partir do arquivo
   int maximoInimigos;
   
   /// \brief Quantos inimigos j� foram feitos nesta fase
   ///
   /// Come�a em 0 e vai at� totalInimigo. 
   int totalFeitos;
   
   /// \brief Quantidade de inimigos atualmente na tela
   ///
   /// Vai de 0 at� maximoInimigos
   int quantosAtual;
   
   /// \brief Quantidade de posi��es iniciais poss�veis para os inimigos
   ///
   /// L� do arquivo
   int quantasPosicoesInimigos;
   
   /// \brief Posi��o inicial do jogador
   ///
   /// L� do arquivo
   vector3df posicaoInicialJogador;

   /// \brief Vetor com as posi��es iniciais poss�veis dos inimigos
   ///
   /// Tem quantasPosicoesInimigos elementos. L� a partir do arquivo 
   vector3df *posicaoInicialInimigos;
   
   /// \brief Quais intelig�ncias para inimigos est�o dispon�veis para esta fase
   ///
   /// Vetor com uma posi��o para cada tipo de inimigo. L� do arquivo.
   bool possiveisIA[QTD_INIMIGOS];
   
   /// \brief Quais naves est�o dispon�veis para esta fase
   ///
   /// Vetor com uma posi��o para cada tipo de inimigo. L� do arquivo.
   bool navesPossiveis[QTD_INIMIGOS];
   
   /// \brief Cria um novo inimigo
   ///
   /// \param qual Qual inimigo a ser criado
   /// \returns Ponteiro para o inimigo criado
   Objeto *NovoInimigo(int qualIA, int qualNave);
   
   /// \brief Diz quantos tipos de inimigos h� para essa fase
   int QuantosPossiveis(void);
   
   /// \brief Diz quantos tipos de naves h� para essa fase
   int QuantasNavesPossiveis(void);
   
   /// \brief Sorteia uma posi��o inicial para um inimigo entre as poss�veis
   vector3df EscolhePosicaoInimigo(void);
   
   /// \brief Sorteia um inimigo entre os poss�veis
   ///
   /// Sorteia e cria um inimigo entre os poss�veis. 
   /// \returns Um ponteiro para o inimigo criado
   Objeto *SorteiaInimigo(void);

   /// \brief L� a descri��o da fase a partir de um arquivo
   ///
   /// \param arquivo Nome do arquivo a ser lido
   void LeArquivo(char *arquivo);
   
   public:
      /// \brief Quantos inimigos ainda precisam ser mortos
      ///
      /// Inclui quantos ainda precisam ser criados e quantos est�o ativos na tela
      int QuantosInimigosRestam(void);
      
      /// \brief Avisa a fase que um inimigo foi morto
      ///
      /// Serve para que a fase possa atualizar as contas de quantos faltam etc.
      void MorreuInimigo(void);
      
      /// \brief Atualiza a fase
      ///
      /// Verifica se precisa ser adicionado um inimigo. Em caso afirmativo, adiciona um inimigo
      void Atualiza(void);
      
      /// \brief Inicializa a fase para come�ar a jogar
      void Comeca(void);
      
      /// \brief Construtor
      ///
      /// \param arquivo Nome do arquivo com a descri��o da fase
      /// \param centralAux Onde est�o os objetos
      Fase(char *arquivo, Central *centralAux);
      
      /// \brief Destrutor
      ~Fase(void);
};
