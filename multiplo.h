/// \brief Controla o tiro multiplo
///
/// Cada inst�ncia dessa classe � um tiro corrente. Quando criado, cria mais duas c�pias em dire��es diagonais.

class Multiplo : public Objeto
{  
  /// \brief Se devo criar outras c�pias
  ///
  /// Depois de criada as c�pias, mudo para false. C�pias n�o criam c�pias (recebem mensagem para isso)
  bool criaCopias;
  
  /// \brief Objeto que lan�ou esse tiro
  ///
  /// Serve para o tiro avisar que atingiu algu�m e tamb�m na hora de fazer com que o tiro n�o atinja a pr�pria nave que o lan�ou  
  Objeto *pai;
   
  /// \brief Avisa o tiro que ele bateu em outro objeto
  ///
  /// Avisa o tiro que ele atingiu outro objeto. Verifico se n�o estou atingindo o meu pai nem se estou atingindo outro tiro (perguntando ao objeto se ele � s�lido). Em ambos os casos, nada fa�o. Nos demais, adiciono for�a no outro objeto, aviso quanto ele deve perder de life, me marco para sair da lista de objetos a aviso meu pai quem eu atingi
  virtual void BateuNeste(Objeto *outro);
  
 public:
  
  /// \brief Loop de atualiza��o do tiro
  ///
  /// Fa�o a atualiza��o via Objeto::Atualiza e me marco para sair da lista de objetos no caso em que tiver batido no cen�rio
  virtual void Atualiza(void);

  /// \brief Fun��o que recebe mensagens
  ///
  /// Esta fun��o � uma extens�o da fun��o de mesmo nome na classe
  /// objeto. Aqui ela responde que � um TIRO para QUEM_VOCE e
  /// SIM para SOLIDO. Responde SIM ou NAO para MEU_PAI, dependendo se param for igual ao pai. Se a mensagem for PAI_MORTO, ent�o deixa o valor de pai = NULL e deixa de verificar coisas relativas a ele. Se a pergunta n�o � uma dessas ela repassa a
  /// pergunta para Objeto.
  /// se recebe NAO_CRIE_COPIAS muda criaCopias para false.
  /// \param msg um inteiro que indica a pergunta
  /// \param param Na mensagem MEU_PAI, deve ter o valor de um ponteiro para o objeto candidato a pai. Nos outros casos, n�o � utilizado
  /// \return Um inteiro constante que representa a resposta dela ou a resposta
  /// fornecida por Objeto.
  virtual int Mensagem(int qual, void *param);
  
  /// \brief O construtor
  ///
  /// Faz o som de que foi solo um tiro, ajeita a posi��o e dire��o para que fiquem iguais ao do pai
  /// \param paiAux Informa quem � o pai do tiro
  Multiplo(Central *central, Objeto *paiAux, float desvio = 0.0f);
};
