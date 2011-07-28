/// \brief Cuida da nave controlada pelo jogador
///
/// É a classe que controla a nave do jogador. O input é feito pelas funções Objeto::Atira, Objeto::JogadaDeLado{Esq,Dir}, Objeto::ParaFrente, Objeto::ParaTras, Objeto::ParaEsquerda, Objeto::ParaDireita em principal.cpp
class Jogador : public Nave
{     

  /// \brief O input do jogo
  ///
  Input *input;
  
 public:

  /// \brief É o loop de atualização
  ///
  /// Por enquanto deixa morto=false para que a nave nunca seja tirada da lista da central. Informa os dados de entrada tratados pela input e chama a Objeto::Atualiza
  virtual void Atualiza(void);
  
  /// \brief Função que recebe mensagens
  ///
  /// Esta função é uma extensão da função de mesmo nome na classe
  /// objeto. Aqui ela responde que é um JOGADOR para QUEM_VOCE e
  /// SIM para SOLIDO. Se a pergunta não é uma dessas ela repassa a
  /// pergunta para Objeto.q
  /// \param msg um inteiro que indica a pergunta
  /// \param param Não usa.
  /// \return Um inteiro constante que representa a resposta dela ou a resposta
  /// fornecida por Objeto.
  virtual int Mensagem(int qual, void *param);
      
  /// \brief O construtor
  ///
  /// Inicia as particularidades do objeto como aparência, velocidade, tipo de tiro...
  /// \param central Onde estão todos os objetos do jogo.
  Jogador(Central *central, Input *inputAux);
};
