/// \brief Controla um inimigo corajoso com alguma inteligência artificial
///
/// Controla objetos do tipo corajoso, determinando seus movimentos e tiros. Ele se afasta do jogador se o jogador está "de frente" para ele e se aproxima em caso contrário, sempre atirando.
class Corajoso : public Nave
{

	
public:

	/// \brief Função que recebe mensagens
	///
	/// Esta função é uma extensão da função de mesmo nome na classe
	/// objeto. Aqui ela responde que é um INIMIGO para QUEM_VOCE e
	/// SIM para SOLIDO. Se a pergunta não é uma dessas ela repassa a
	/// pergunta para Objeto.
	/// \param msg um inteiro que indica a pergunta
	/// \param param Não usa.
	/// \return Um inteiro constante que representa a resposta dela ou a resposta
	/// fornecida por Objeto.
	virtual int Mensagem(int msg, void *param);

	/// \brief Faz o inimigo jogar
	///
	/// Escolhe e atualiza instruções de movimento e tiro e chama Objeto::Atualiza
	virtual void Atualiza(void);

	/// \brief The constructor
	///
	/// Inicia as particularidades do objeto como aparência, velocidade, tipo de tiro...
	/// \param central Onde estão todos os objetos do jogo.
	Corajoso(Central *central, const char *qualNave);
};
