/// \brief Classe que controla as naves
///
/// Estende a classe Objeto
class Nave : public Objeto
{
 protected:
  /// \brief L� os parametros para a nave a partir de um arquivo
  void LeAtributos(const char *nome);
      
  /// \brief Chamada quando pegou o item do tiro b�sico
  void GanhouTiroBasico(int qual);
      
  /// \brief Chamada quando pegou um item de algum tiro n�o b�sico
  void GanhouTiroNaoBasico(int qual);
      
  virtual void BateuNeste(Objeto *outro);
  virtual void BateramEmVoce(int quantoPerde);
  virtual void NovoTiro(int qual);
      
  virtual int Mensagem(int msg, void *param);
      
  /// \brief Se o comando de tiro est� pressionado
  bool atirando;
      
  /// \brief Para contar quanto falta para poder dar outro tiro
  ///
  /// Vai de 0 a tempoDeRecargaTotal
  int tempoDeRecargaAtual[QTD_TIPOS_TIROS];
      
  /// \brief Marca o tempo para se poder fazer nova jogada de lado
  ///
  /// Se maior que 0, n�o pode fazer ainda. � diminu�do a cada Atualiza
  int tempoAtualJogadaDeLado;
  
  /// \brief Avisa todos os tiros que criou que morreu
  void AvisaTirosPaiMorto(void);
  
  /// \brief Solta o tiro
  void SoltaTiro(void);
      
 public:   

  /// \brief Faz a jogadinha de lado para a esquerda
  ///
  /// \param pressionada booleando que � true se a teclada adequada est� pressionada
  void JogadaDeLadoEsq(bool pressionada);
  
  /// \brief Faz a jogadinha de lado para a direita
  ///
  /// \param pressionada booleando que � true se a teclada adequada est� pressionada
  void JogadaDeLadoDir(bool pressionada);
  
  /// \brief � chamada quando se quer que o objeto atire
  ///
  /// S� atira se o tempo de recarga permitir
  virtual void Atira(bool pressionada){atirando = pressionada;};
  
  /// \brief Atualiza a nave
  virtual void Atualiza(void);
  
  Nave(Central *centralAux, const char *nome);
};
