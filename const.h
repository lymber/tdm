#define NADA         0

//inteligencia de inimigos
//ATENÇÃO: precisam ser números consecutivos partindo do 0 até QTD_INIMIGOS - 1
#define MEDROSO      0
#define CORAJOSO     1
#define QTD_INIMIGOS 2 //<-----Atenção com esse!

//tipos de naves
//ATENÇÃO: precisam ser números consecutivos partindo do 0 até QTD_NAVES - 1
#define PITAGORAS 0
#define SOCRATES  1
#define PLATAO    2  
#define QTD_NAVES 3 //<-----Atenção com esse!


//tipos de tiro
//ATENÇÃO: precisam ser números consecutivos partindo do 0 até QTD_TIPOS_TIROS - 1
#define TIPO_NENHUM     -1
#define TIPO_LASER       0
#define TIPO_MISSIL      1
#define TIPO_MULTIPLO    2
#define QTD_TIPOS_TIROS  3 //<----Antenção com esse!


//Tempos
#define TEMPO_PISCANDO         400
#define TEMPO_CURTO             30
#define TEMPO_LONGO            150
#define TEMPO_TRANSICAO        300
#define TEMPO_JOGADA_DE_LADO    90
#define TEMPO_ATRASO_CAMERA     10
#define TEMPO_BONUS           2500
#define TEMPO_CICLO             15

//Mensagens
#define QUEM_VOCE            1000
#define INIMIGO              1001
#define JOGADOR              1002
#define TIRO                 1003
#define MEU_TIRO             1004
#define PAI_MORTO            1005
#define SIM                  1006
#define NAO                  1007
#define SOLIDO               1008
#define ESQUERDA             1009
#define DIREITA              1010
#define ITEM                 1011
#define GANHOU_ITEM_LASER    1012
#define PROCURA_JOGADOR      1013
#define PROCURA_INIMIGO      1014
#define GANHOU_ITEM_MISSIL   1015
#define NAO_CRIE_COPIAS      1016
#define GANHOU_ITEM_MULTIPLO 1017
#define MODO_DE_DENTRO       1018
#define SAIU_MODO_DE_DENTRO  1019

//Modos da câmera
//do not change the first one
#define DE_CIMA         2000
#define DE_LADO         2001
#define DE_TRAS         2002
#define DE_DENTRO       2003
#define QUANTAS_CAMERAS    4 //<---- Attention with this!
#define PROXIMA         2004
#define ANTERIOR        2005

//Tipo de Fade
#define CLARO_ESCURO_CLARO  3000
#define ESCURO_CLARO_ESCURO 3001
#define CLARO_ESCURO        3002
#define ESCURO_CLARO        3003

//Massa dos objetos
#define MASSA_OBJETO 0.2f
#define MASSA_TIRO   0.5f
