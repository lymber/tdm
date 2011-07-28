/// \brief Cuida das informacoes que o usuario vê
///
/// Tudo que aparece na tela que não é "3D" é feito aqui. Mostra os lifes, quantos faltam para morrer etc.
class Interface
{
   /// \brief Escolhe o logotipo baseado no tipo
   ITexture *EscolheLogo(int qual);
   
   /// \brief Cuida da transparência da barra de life
   Fader *transparenciaLife;
   
   /// \brief Imagem do alvo
   ///
   /// Usado para indicar quantos inimigos restam
   ITexture *alvo;
   
   /// \brief Cockpit para a visão interna
   ITexture *cockpit;
   
   /// \brief Simbolozinho do laser
   ITexture *logoLaser;
   
   /// \brief Simbolozinho do míssil
   ITexture *logoMissil;
   
   /// \brief Simbolozinho do tiro múltiplo
   ITexture *logoMultiplo;
   
   /// \brief Guarda as informações de todos os objetos
   Central *central;
   
   /// \brief A nave do jogador
   Objeto *navePrincipal;
   
   /// \brief Resolução da tela
   ///
   /// Vê qual a resolução da tela. Usando as funções internas, pode-se sempre trabalhar como se a tela tivesse resolução 800x600 que a classe faz a conversão
   dimension2d<s32> tamanhoTela;
   
   /// \brief Marca o tempo para a barra de life
   ///
   /// Serve para o fade que acontece quando o jogador é atingido e para a transição entre o life novo e o velho
   int transicaoLife;
   
   /// \brief Life do jogador na rodada anterior
   ///
   /// Serve para fazer a transição entre o life novo e o velho
   float lifeAnterior;
   
   /// \brief Life potencial do jogador na rodada anterior
   ///
   /// Serve para fazer a transição entre o life novo e o velho
   float lifePotencialAnterior;
   
   /// \brief A fase atual
   Fase *fase;
   
   /// \brief Lê uma textura a partir de um arquivo
   ///
   /// Lê a textura e já faz a conversão das suas dimensões para a resolução atual
   /// \param filename nome do arquivo em que está a textura
   video::ITexture* LeTexturaConvertida(const c8 *filename);
   
   /// \brief Converte uma coordenada de tela X baseada na resolução atual
   s32 ConverteX(s32 x);
   
   /// \brief Converte uma coordenada de tela Y baseada na resolução atual
   s32 ConverteY(s32 y);
   
   /// \brief Cria um retângulo com as coordenadas convertidas para a resolução atual
   rect<s32> Retangulo(s32 x1, s32 y1, s32 x2, s32 y2);
   
   public:
      
      /// \brief Desenha os elementos
      /// Precisa ser chamada depois que os elementos 3D forem desenhados, para que não seja sobrescrito na tela
      void Desenha(void);
      
      /// \brief Atualiza os valores que devem ser mostrados
      void Atualiza(void);
      
      /// \brief Construtor
      ///
      /// Acerta variáveis e lê as imagens a partir dos arquivos
      Interface(Central *centralAux);
      
      /// \brief Destrutor
      ///
      ~Interface(void);
};
