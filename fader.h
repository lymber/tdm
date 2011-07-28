/// \brief Classe para fazer efeitos de Fade
///
/// Guarda um float com 3 est�gios para Fade: entrando, feito, saindo. Com suas dura��es (em ciclos)
class Fader
{
   int max;
   int min;
   
   /// \brief Qual o tipo do Fade
   ///
   /// Pode ser ESCURO_CLARO_ESCURO, CLARO_ESCURO_CLARO, ESCURO_CLARO, CLARO_ESCURO
   int tipo;
   
   /// \brief Qual o ciclo em que est�
   int atual;
   
   /// \brief Tempo do primeiro est�gio
   int tempo1;
   
   /// \brief Tempo do segundo est�gio
   int tempo2;
   
   /// \brief Tempo do terceiro est�gio
   int tempo3;
   
   public:
      /// \brief Atualiza os contadores e retorna um float para qual o n�vel do fade
      int Atualiza(void);
      
      /// \brief Construtor
      ///
      /// \param tipo Pode ser ESCURO_CLARO_ESCURO, CLARO_ESCURO_CLARO, ESCURO_CLARO, CLARO_ESCURO
      /// \param tempo1 Tempo do estagio 1 (pode ser 0)
      /// \param tempo2 Tempo do estagio 2 (pode ser 0)
      /// \param tempo3 Tempo do estagio 3 (pode ser 0)
      Fader(int tipoAux, int tempo1Aux, int tempo2Aux, int tempo3Aux, int maxAux, int minAux);
};
