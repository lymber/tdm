#include "fader.h"

//-------------------------------------------------------------------
int Fader::Atualiza(void)
{
   if (atual <= tempo1 + tempo2 + tempo3) atual++;
   if (tipo == ESCURO_CLARO_ESCURO)
   {
      if (atual < tempo1) 
      {
         if (tempo1 == 0) return max;
         else return (atual / tempo1);
      }
      else if (atual >= tempo1 && atual - tempo1 < tempo2)
      {
         return max;
      }
      else if (atual >= tempo1 + tempo2 && atual - tempo1 - tempo2 < tempo3)
      {
         if (tempo3 == 0) return min;
         else return min + ((max - min) - (max - min) * ((atual - tempo1 - tempo2) / tempo3));
      }
      return min; 
   }
   else if (tipo == CLARO_ESCURO_CLARO)
   {
      if (atual < tempo1) 
      {
         if (tempo1 == 0) return min;
         else return min + ((max - min) * (tempo1 - atual) / tempo1);
      }
      else if (atual >= tempo1 && atual - tempo1 < tempo2)
      {
         return min;
      }
      else if (atual >= tempo1 + tempo2 && atual - tempo1 - tempo2 < tempo3)
      {
         if (tempo3 == 0) return max;
         else return (min + ((max - min)* (atual - tempo1 - tempo2) / tempo3));
      }
      return max; 
   }
}

//------------------------------------------------------------------
Fader::Fader(int tipoAux, int tempo1Aux, int tempo2Aux, int tempo3Aux, int maxAux, int minAux)
{
   atual = 0;
   tipo = tipoAux;
   tempo1 = tempo1Aux;
   tempo2 = tempo2Aux;
   tempo3 = tempo3Aux;
   max = maxAux;
   min = minAux;
}
