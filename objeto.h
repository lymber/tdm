/// \brief Classe que controla os objetos da tela, como naves e tiros
///
/// Praticamente qualquer objeto do jogo estende esta classe
class Objeto
{
   protected:

      /// \brief O tiro b�sico do objeto
      int tipoTiroBasico;

      /// \brief tempo do b�nus de cada arma
      int tempoBonus[QTD_TIPOS_TIROS];

      /// \brief Quantos ciclos s�o necess�rios entre um tiro e outro
      int tempoDeRecargaTotal[QTD_TIPOS_TIROS];

      /// \brief Quanto de life o objeto tem
      ///
      /// Aumenta um pouco a cada ciclo at� lifePotencial
      float life;

      /// \brief Life m�ximo do objeto
      ///
      /// � com quanto ele come�a
      float lifeMaximo;

      /// \brief Life que o objeto pode recuperar
      ///
      /// Veja life
      float lifePotencial;

      /// \brief Velocidade m�xima de virada
      float maxVirada;

      /// \brief Qual a velocidade com que o objeto vira
      float velocidadeVirada;

      /// \brief Procura por um determinado objeto na lista da central
      ///
      /// \param quem Objeto a ser procurado
      /// \return O primeiro objeto que responde quem a pergunta QUEM_VOCE
      Objeto *Procura(int quem);

      /// \brief Aponta para o cen�rio
      ///
      /// Serve para ver se est� se chocando com ele
      ISceneNode *cenario;

      /// \brief Onde est�o todos os objetos
      Central *central;

      /// \brief A descri��o geom�trica do objeto
      IAnimatedMeshSceneNode* node;

      /// \brief Se esquerda est� pressionada
      bool esq;

      /// \brief Se direita est� pressionada
      bool dir;

      /// \brief �ngulo m�ximo que o objeto pode tombar
      float maxInclinacao;

      /// \brief �ngulo do objeto no plano horizontal
      float anguloHorizontal;

      /// \brief �ngulo do "tombamento" do objeto
      float inclinacao;

      /// \brief O quanto o objeto ganha de velocidade por ciclo
      float aceleracao;

      /// \brief Velocidade m�xima que o objeto pode atingir
      float velocidadeMaxima;

      /// \brief Objeto indo para frente ou para tr�s
      bool parafrente, paratras;

      /// \brief O quanto o objeto perde de velocidade por ciclo
      float resistencia;

      /// \brief Diz se o objeto bateu no cen�rio
      /// � calculado no Atualiza, com base no movimento esperado
      bool bateuCenario;

      /// \brief Se o objeto est� morto ou n�o
      ///
      /// Objetos mortos s�o retirados da lista na central
      bool morto;

      /// \brief Quanto que vira a nave
      ///
      /// Para acelerar o giro da nave
      float quantoVira;

      /// \brief A posi��o estimada para o pr�ximo ciclo
      ///
      /// Serve para calcular se o objeto bateu no cen�rio
      vector3df posicaoEstimada;

      /// \brief "Momento" da nave
      ///
      /// � o vetor que � somado a cada ciclo � posi��o do objeto
      vector3df momento;

      /// \brief "Momento" ganho em impactos e tamb�m nas "jogadas de lado"
      ///
      /// � adicionado ao momento durante o Atualiza
      vector3df momentoImpacto;

      /// \brief Se maior que 0, indica que a nave est� invenc�vel
      ///
      /// Descresce a cada ciclo at� o 0
      int piscando;

      /// \brief "Massa" do objeto
      ///
      /// Serve para calcular o momento de impacto quando se choca com outro objeto
      float massa;

      /// \brief L� o arquivo com o modelo do objeto
      void LeModelo(const char *nome);

      /// \brief Para lan�ar o tiro
      virtual void SoltaTiro(void){};

      /// \brief Zera todos os comandos do objeto
      void ZeraComandos(void);


   public:
      /// \brief Chamada quando colidiu com outro objeto
      ///
      /// Verifica se perde life, avisa o outro objeto, adiciona os momentos
      /// \param outro Objeto em que colidiu
      virtual void BateuNeste(Objeto *outro);

      int QualTipoTiroBasico(void){return tipoTiroBasico;};
      int QualTempoBonus(int qual){return tempoBonus[qual];};

      /// \brief Quanto life o objeto tem
      float Life(void){return life;};

      /// \brief Qual o m�ximo de life que o objeto pode ter
      float LifeMaximo(void){return lifeMaximo;};

      /// \brief Quanto life o objeto pode recuperar
      float LifePotencial(void){return lifePotencial;};

      /// \brief Retorna o inimigo mais pr�ximo
      Objeto *InimigoMaisProximo(void);

      /// \brief � chamada por um tiro filho, para avisar o pai que acertou algu�m
      ///
      /// \param outro Objeto atingido
      virtual void AcertouEste(Objeto *outro){};


      /// \brief Se o objeto est� invenc�vel ou n�o
      bool Piscando(void){return (piscando > 0);};

      /// \brief Qual o "momento" atual do objeto
      vector3df Momento(void){return momento;};

      /// \brief Muda o momento do objeto (melhor usar o AdicionaForca)
      void MudaMomento(vector3df qual){momento = qual;};

      /// \brief Qual o �ngulo do objeto no plano horizontal
      float AnguloHorizontal(void){return anguloHorizontal;};

      /// \brief Uma "caixa" em torno do objeto
      ///
      /// Serve, por exemplo, para verificar colis�es
      aabbox3df Box(void){return node->getTransformedBoundingBox();};

      /// \brief Dist�ncia do objeto para um dado ponto
      ///
      /// \param onde O ponto de onde se quer saber a distância
      float Distancia(vector3df onde);

      /// \brief � chamada quando algum objeto o atingiu
      virtual void BateramEmVoce(int quantoPerde);

      /// \brief Verifica se dado objeto � o mesmo dessa classe
      ///
      /// \param outro O objeto com que se quer verificar a igualdade
      bool SouEu(Objeto *outro);

      /// \brief Acrescenta uma for�a de impacto no objeto
      ///
      /// \param v Diz a dire��o e a intensidade da for�a
      void AdicionaForca(vector3df v);

      /// \brief Diz se bateu ou n�o em determinado objeto
      ///
      /// \param outro Com quem se quer verificar a colis�o
      virtual bool Bateu(Objeto *outro);

      /// \brief Diz se o objeto est� morto ou n�o
      virtual bool Morto(void){return morto;};

      /// \brief Vetor que aponta para cima do objeto, levando-se em conta a "tombadinha"
      vector3df VetorCimaReal(void);

      /// \brief Vetor que aponta para a frente do objeto
      vector3df VetorFrente(void);

      /// \brief Vetor que aponta para a trazeira do objeto
      vector3df VetorTras(void);

      /// \brief Vetor que aponta para a esquerda do objeto, sem levar em contar a "tombadinha"
      vector3df VetorEsquerda(void);

      /// \brief Vetor que aponta para a direita do objeto, sem levar em contar a "tombadinha"
      vector3df VetorDireita(void);

      /// \brief Diz se determinada posi��o est� na frente do objeto
      ///
      /// \param outro A posi��o que se quer verificar
      bool NaFrente(vector3df outro);

      /// \brief Diz se determinada posi��o est� na traseira do objeto
      ///
      /// \param outro A posi��o que se quer verificar
      bool NaTras(vector3df outro);

      /// \brief Diz se determinada posi��o est� � esquerda do objeto
      ///
      /// \param outro A posi��o que se quer verificar
      bool NaEsquerda(vector3df outro);

      /// \brief Diz se determinada posi��o est� � direita do objeto
      ///
      /// \param outro A posi��o que se quer verificar
      bool NaDireita(vector3df outro);

      /// \brief Matriz de referencial do objeto
      matrix4 Referencial(void){return node->getRelativeTransformation();}

      /// \brief Avisa qual o cen�rio atual para o objeto
      ///
      /// Deve ser chamado a cada mudan�a de cen�rio, para que o objeto possa verificar se chocou com ele ou n�o
      /// \param cenarioAux Qual o cen�rio atual
      void AdicionaCenario(ISceneNode *cenarioAux);

      /// \brief A posi��o do objeto
      vector3df Posicao(void){return node->getAbsolutePosition();};

      /// \brief Altera a posi��o do objeto
      void MudaPosicao(vector3df qual);

      /// \brief Atualiza o objeto
      ///
      /// Calcula a velocidade do objeto, verifica se se chocou com alguma coisa etc.
      virtual void Atualiza(void);

      /// \brief Avisa se o comando para frente est� pressionado
      void ParaFrente(bool pressionada);

      /// \brief Avisa se o comando para esquerda est� pressionado
      void ParaEsquerda(bool pressionada){esq = pressionada;};

      /// \brief Avisa se o comando para direita est� pressionado
      void ParaDireita(bool pressionada){dir = pressionada;};

      /// \brief Avisa se o comando para tr�s est� pressionado
      void ParaTras(bool pressionada);

      /// \brief Para os objetos de comunicarem entre si
      ///
      /// Objetos que quiserem usar isso, basta estenderem essa fun��o. Aqui, s� retorna NADA para qualquer coisa
      virtual int Mensagem(int msg, void *param);


      /// \brief Construtor
      Objeto(Central *centralAux, const char *nome);

      /// \brief Destrutor
      ~Objeto(void);
};
