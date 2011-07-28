/// \brief Aumenta a velocidade do tiro de laser ou o inclui como "power up".
class ItemLaser : public Objeto
{

public:

  /// \brief Verifica se o par�metro *outro "pegou" o item e o apaga da tela
  ///
  /// \param *outro nave que coletou o item
  virtual void BateuNeste(Objeto *outro);
  
  /// \brief Fun��o que recebe mensagens
  ///
  /// Esta fun��o � uma extens�o da fun��o de mesmo nome na classe
  /// objeto. Aqui ela responde que � um INIMIGO para QUEM_VOCE e
  /// SIM para SOLIDO. Se a pergunta n�o � uma dessas ela repassa a
  /// pergunta para Objeto.
  /// \param msg um inteiro que indica a pergunta
  /// \param param N�o usa.
  /// \return Um inteiro constante que representa a resposta dela ou a resposta
  /// fornecida por Objeto.
  virtual int Mensagem(int msg, void *param);
  
  /// \brief Faz o inimigo jogar
  ///
  /// Escolhe e atualiza instru��es de movimento e tiro e chama Objeto::Atualiza
  virtual void Atualiza(void);
  
  /// \brief The constructor
  ///
  /// Inicia as particularidades do objeto como apar�ncia, velocidade, tipo de tiro...
  /// \param central Onde est�o todos os objetos do jogo.
  ItemLaser(Central *central);
};
