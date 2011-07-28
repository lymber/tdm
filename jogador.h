/// \brief Cuida da nave controlada pelo jogador
///
/// � a classe que controla a nave do jogador. O input � feito pelas fun��es Objeto::Atira, Objeto::JogadaDeLado{Esq,Dir}, Objeto::ParaFrente, Objeto::ParaTras, Objeto::ParaEsquerda, Objeto::ParaDireita em principal.cpp
class Jogador : public Nave
{     

  /// \brief O input do jogo
  ///
  Input *input;
  
 public:

  /// \brief � o loop de atualiza��o
  ///
  /// Por enquanto deixa morto=false para que a nave nunca seja tirada da lista da central. Informa os dados de entrada tratados pela input e chama a Objeto::Atualiza
  virtual void Atualiza(void);
  
  /// \brief Fun��o que recebe mensagens
  ///
  /// Esta fun��o � uma extens�o da fun��o de mesmo nome na classe
  /// objeto. Aqui ela responde que � um JOGADOR para QUEM_VOCE e
  /// SIM para SOLIDO. Se a pergunta n�o � uma dessas ela repassa a
  /// pergunta para Objeto.q
  /// \param msg um inteiro que indica a pergunta
  /// \param param N�o usa.
  /// \return Um inteiro constante que representa a resposta dela ou a resposta
  /// fornecida por Objeto.
  virtual int Mensagem(int qual, void *param);
      
  /// \brief O construtor
  ///
  /// Inicia as particularidades do objeto como apar�ncia, velocidade, tipo de tiro...
  /// \param central Onde est�o todos os objetos do jogo.
  Jogador(Central *central, Input *inputAux);
};
