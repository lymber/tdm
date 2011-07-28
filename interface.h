/// \brief Cuida das informacoes que o usuario v�
///
/// Tudo que aparece na tela que n�o � "3D" � feito aqui. Mostra os lifes, quantos faltam para morrer etc.
class Interface
{
   /// \brief Escolhe o logotipo baseado no tipo
   ITexture *EscolheLogo(int qual);
   
   /// \brief Cuida da transpar�ncia da barra de life
   Fader *transparenciaLife;
   
   /// \brief Imagem do alvo
   ///
   /// Usado para indicar quantos inimigos restam
   ITexture *alvo;
   
   /// \brief Cockpit para a vis�o interna
   ITexture *cockpit;
   
   /// \brief Simbolozinho do laser
   ITexture *logoLaser;
   
   /// \brief Simbolozinho do m�ssil
   ITexture *logoMissil;
   
   /// \brief Simbolozinho do tiro m�ltiplo
   ITexture *logoMultiplo;
   
   /// \brief Guarda as informa��es de todos os objetos
   Central *central;
   
   /// \brief A nave do jogador
   Objeto *navePrincipal;
   
   /// \brief Resolu��o da tela
   ///
   /// V� qual a resolu��o da tela. Usando as fun��es internas, pode-se sempre trabalhar como se a tela tivesse resolu��o 800x600 que a classe faz a convers�o
   dimension2d<s32> tamanhoTela;
   
   /// \brief Marca o tempo para a barra de life
   ///
   /// Serve para o fade que acontece quando o jogador � atingido e para a transi��o entre o life novo e o velho
   int transicaoLife;
   
   /// \brief Life do jogador na rodada anterior
   ///
   /// Serve para fazer a transi��o entre o life novo e o velho
   float lifeAnterior;
   
   /// \brief Life potencial do jogador na rodada anterior
   ///
   /// Serve para fazer a transi��o entre o life novo e o velho
   float lifePotencialAnterior;
   
   /// \brief A fase atual
   Fase *fase;
   
   /// \brief L� uma textura a partir de um arquivo
   ///
   /// L� a textura e j� faz a convers�o das suas dimens�es para a resolu��o atual
   /// \param filename nome do arquivo em que est� a textura
   video::ITexture* LeTexturaConvertida(const c8 *filename);
   
   /// \brief Converte uma coordenada de tela X baseada na resolu��o atual
   s32 ConverteX(s32 x);
   
   /// \brief Converte uma coordenada de tela Y baseada na resolu��o atual
   s32 ConverteY(s32 y);
   
   /// \brief Cria um ret�ngulo com as coordenadas convertidas para a resolu��o atual
   rect<s32> Retangulo(s32 x1, s32 y1, s32 x2, s32 y2);
   
   public:
      
      /// \brief Desenha os elementos
      /// Precisa ser chamada depois que os elementos 3D forem desenhados, para que n�o seja sobrescrito na tela
      void Desenha(void);
      
      /// \brief Atualiza os valores que devem ser mostrados
      void Atualiza(void);
      
      /// \brief Construtor
      ///
      /// Acerta vari�veis e l� as imagens a partir dos arquivos
      Interface(Central *centralAux);
      
      /// \brief Destrutor
      ///
      ~Interface(void);
};
