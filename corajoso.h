/// \brief Controla um inimigo corajoso com alguma intelig�ncia artificial
///
/// Controla objetos do tipo corajoso, determinando seus movimentos e tiros. Ele se afasta do jogador se o jogador est� "de frente" para ele e se aproxima em caso contr�rio, sempre atirando.
class Corajoso : public Nave
{

	
public:

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
	Corajoso(Central *central, const char *qualNave);
};
