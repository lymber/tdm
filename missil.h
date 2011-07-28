/// \brief Controla o tiro míssil
///
/// Cada instância dessa classe é um tiro corrente

class Missil : public Objeto
{  
  /// \brief Por quem procuro
  ///
  /// Se igual a INIMIGO, sigo o inimigo mais próximo. Se igual a JOGADOR, sigo o jogador. Tem seu valor atualizado via mensagem PROCURA_INIMIGO e PROCURA_JOGADOR
  int procuro;
     
  /// \brief Objeto que lançou esse tiro
  ///
  /// Serve para o tiro avisar que atingiu alguém e também na hora de fazer com que o tiro não atinja a própria nave que o lançou  
  Objeto *pai;
  
  /// \brief Avisa o tiro que ele bateu em outro objeto
  ///
  /// Avisa o míssil que ele atingiu outro objeto. Verifico se não estou atingindo o meu pai nem se estou atingindo outro tiro (perguntando ao objeto se ele é sólido). Em ambos os casos, nada faço. Nos demais, adiciono força no outro objeto, aviso quanto ele deve perder de life, me marco para sair da lista de objetos a aviso meu pai quem eu atingi
  virtual void BateuNeste(Objeto *outro);
  
 public:
  
  /// \brief Loop de atualização do tiro
  ///
  /// Faço a atualização via Objeto::Atualiza e me marco para sair da lista de objetos no caso em que tiver batido no cenário. Viro para o lado da nave do jogador    
  virtual void Atualiza(void);
  
  /// \brief Função que recebe mensagens
  ///
  /// Esta função é uma extensão da função de mesmo nome na classe
  /// Objeto. Aqui ela responde que é um TIRO para QUEM_VOCE e
  /// SIM para SOLIDO. Responde SIM ou NAO para MEU_PAI, dependendo se param for igual ao pai. Se a mensagem for PAI_MORTO, então deixa o valor de pai = NULL e deixa de verificar coisas relativas a ele. Se a pergunta não é uma dessas ela repassa a
  /// pergunta para Objeto.
  /// \param msg um inteiro que indica a pergunta
  /// \param param Na mensagem MEU_PAI, deve ter o valor de um ponteiro para o objeto candidato a pai. Nos outros casos, não é utilizado
  /// \return Um inteiro constante que representa a resposta dela ou a resposta
  /// fornecida por Objeto.
  virtual int Mensagem(int qual, void *param);
  
  /// \brief O construtor
  ///
  /// Faz o som de que foi solto um tiro, ajeita a posição e direção para que fiquem iguais ao do pai
  /// \param paiAux Informa quem é o pai do tiro
  Missil(Central *central, Objeto *paiAux);
};
