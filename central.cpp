#include "central.h"

//-------------------------------------------------------------------------------
//Retorna o primeiro objeto da lista
void *Central::PrimeiroObjeto(list<void *>::Iterator *atualListaObjetos)
{
   *atualListaObjetos = listaObjetos.begin();
   return *(*atualListaObjetos);
}

//-------------------------------------------------------------------------------
//Retorna o próximo objeto da lista, marcando-o como atual
void *Central::ProximoObjeto(list<void *>::Iterator *atualListaObjetos)
{
   if (*atualListaObjetos == listaObjetos.getLast()) return NULL;

   (*atualListaObjetos)++;
   return *(*atualListaObjetos);
}

//---------------------------------------------------------------------------------
void *Central::ApagaObjeto(list<void *>::Iterator *atualListaObjetos)
{
   bool ultimo = (*atualListaObjetos == listaObjetos.getLast());
   *(*atualListaObjetos) = NULL;
   *atualListaObjetos = listaObjetos.erase(*atualListaObjetos);
   if (ultimo) return NULL;
   else return *(*atualListaObjetos);
}

//-------------------------------------------------------------------------------
//adiciona um novo objeto na lista
void Central::NovoObjeto(void *qual)
{
   listaObjetos.push_front(qual);
}

//------------------------------------------------------------------------------
Central::Central(IrrlichtDevice *deviceAux, irrklang::ISoundEngine* soundEngineAux)
{
  device = deviceAux;
  soundEngine = soundEngineAux;
  listaObjetos.clear();
}

//-----------------------------------------------------------------------------
Central::~Central(void)
{
   listaObjetos.clear();
}

