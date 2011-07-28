#include "objeto.h"

//-------------------------------------------------------------------------------
void Objeto::LeModelo(const char *nome)
{
   IAnimatedMesh* mesh = central->Device()->getSceneManager()->getMesh(nome);
   node = central->Device()->getSceneManager()->addAnimatedMeshSceneNode(mesh);
}

//---------------------------------------------------------------------------
//Procuro por quem na lista de objetos da central
Objeto *Objeto::Procura(int quem)
{
   list<void *>::Iterator lista;
   Objeto *temp = (Objeto *) central->PrimeiroObjeto(&lista);
   
   while (temp != NULL && temp->Mensagem(QUEM_VOCE, NULL) != quem)
   {
      temp = (Objeto *) central->ProximoObjeto(&lista);
   }
   
   return temp;
}


//-----------------------------------------------------------------------------
//Retorna o inimigo mais próximo
Objeto *Objeto::InimigoMaisProximo(void)
{
   float distancia = -1;
   Objeto *maisProximo;

   list<void *>::Iterator lista;
   Objeto *inimigo = (Objeto *) central->PrimeiroObjeto(&lista);

   while (inimigo != NULL)
   {
      if (inimigo->Mensagem(QUEM_VOCE, NULL) == INIMIGO && !SouEu(inimigo))
      {
         if (distancia == -1 || distancia > inimigo->Distancia(Posicao()))
         {
            maisProximo = inimigo;
            distancia = maisProximo->Distancia(Posicao());
         }
      }
      inimigo = (Objeto *) central->ProximoObjeto(&lista);
   }

   if (distancia != -1) return maisProximo;
   else return NULL;
}

//----------------------------------------------------------------------------
float Objeto::Distancia(vector3df onde)
{
   return Posicao().getDistanceFrom(onde);
}

//----------------------------------------------------------------------------
void Objeto::BateramEmVoce(int quantoPerde)
{
}

//-----------------------------------------------------------------------------
//Diz se o outro objeto sou eu mesmo
bool Objeto::SouEu(Objeto *outro)
{
   return (node == outro->node);
}

//----------------------------------------------------------------------------
//Adiciona a força de algum impacto
void Objeto::AdicionaForca(vector3df v)
{
   momentoImpacto = momentoImpacto + v;
}

//-------------------------------------------------------------------------
//O que fazer se colidiu com outro objeto
void Objeto::BateuNeste(Objeto *outro)
{
}


//------------------------------------------------------------------------
// verifica se este objeto bateu em outro dado
// por enquanto só verifico os bounding box
bool Objeto::Bateu(Objeto *outro)
{
   return (Box().intersectsWithBox(outro->Box()));
   
   //outro->Seletor()->getTriangles(temp, 10, quantos, box, NULL);  
}

//--------------------------------------------------------------------------
void Objeto::ParaFrente(bool pressionada)
{
  parafrente = pressionada;
  if (pressionada) aceleracao = 0.2f * velocidadeMaxima;
  else if (!paratras) aceleracao = 0;
}

//--------------------------------------------------------------------------
void Objeto::ParaTras(bool pressionada)
{
  paratras = pressionada;
   if (pressionada) aceleracao = -0.2f * velocidadeMaxima;
   else if (!parafrente) aceleracao = 0;
}

//----------------------------------------------------------------------------
vector3df Objeto::VetorCimaReal(void)
{
   vector3df v = vector3df(0, 1, 0);
   node->getRelativeTransformation().rotateVect(v);
   return v;
}


//----------------------------------------------------------------------------
vector3df Objeto::VetorFrente(void)
{
   vector3df v = vector3df(0, 0, -1);   
   matrix4 m;
   m.setRotationDegrees(vector3df(0, anguloHorizontal, 0));
   m.rotateVect(v);
   return v;
}

//----------------------------------------------------------------------------
vector3df Objeto::VetorTras(void)
{
   vector3df v = vector3df(0, 0, 1);   
   matrix4 m;
   m.setRotationDegrees(vector3df(0, anguloHorizontal, 0));
   m.rotateVect(v);
   return v;
}

//----------------------------------------------------------------------------
vector3df Objeto::VetorEsquerda(void)
{
   vector3df v = vector3df(1, 0, 0);   
   matrix4 m;
   m.setRotationDegrees(vector3df(0, anguloHorizontal, 0));
   m.rotateVect(v);
   return v;
}

//----------------------------------------------------------------------------
vector3df Objeto::VetorDireita(void)
{
   vector3df v = vector3df(-1, 0, 0);   
   matrix4 m;
   m.setRotationDegrees(vector3df(0, anguloHorizontal, 0));
   m.rotateVect(v);
   return v;
}

//-----------------------------------------------------------------------------
// verifica se outro está na minha frente
bool Objeto::NaFrente(vector3df outro)
{
   vector3df v = outro - Posicao();
   
   return (VetorFrente().dotProduct(v) >= 0);
}

//-----------------------------------------------------------------------------
// verifica se outro está na minha traseira
bool Objeto::NaTras(vector3df outro)
{
   vector3df v = outro - Posicao();
   
   return (VetorFrente().dotProduct(v) < 0);
}

//-----------------------------------------------------------------------------
// verifica se outro está na minha esquerda
bool Objeto::NaEsquerda(vector3df outro)
{
   vector3df v = outro - Posicao();
   
   return (VetorEsquerda().dotProduct(v) >= 0);
}


//-----------------------------------------------------------------------------
// verifica se outro está na minha direita
bool Objeto::NaDireita(vector3df outro)
{
   vector3df v = outro - Posicao();
   
   return (VetorDireita().dotProduct(v) >= 0);
}



//--------------------------------------------------------------------------
// Deixa pronto para interagir com o cenário
void Objeto::AdicionaCenario(ISceneNode *cenarioAux)
{
   cenario = cenarioAux;
   // crio uma elipse em volta da Objeto para facilitar na colisão
   core::aabbox3d<f32> box = node->getBoundingBox();
   core::vector3df radius = box.MaxEdge - box.getCenter();
	      
   // crio um animador que, para este caso só não deixa a Objeto entrar nas paredes do cenário
   scene::ISceneNodeAnimator* anim =  central->Device()->getSceneManager()->createCollisionResponseAnimator(
	   	cenario->getTriangleSelector(), node, radius,
	   	core::vector3df(0,0,0));
	node->addAnimator(anim);
	anim->drop();
}

//------------------------------------------------------------------------
void Objeto::MudaPosicao(vector3df qual)
{
   //keep things on the right plane
   qual = vector3df(qual.X, 0, qual.Z);   
   
   posicaoEstimada = qual;
   node->setPosition(qual);
}

//--------------------------------------------------------------------------
// zera todos os comandos
void Objeto::ZeraComandos(void)
{
   ParaEsquerda(false);
   ParaDireita(false);
   ParaFrente(false);
   ParaTras(false);
}

//---------------------------------------------------------------------------
// Faz as atualizacoes necessarias a cada ciclo, com base no input
void Objeto::Atualiza(void)
{

   // vê se a nave tem que piscar e já diminui o tempo disso
   //ve se a nave tem que piscar e ja diminui o tempo disso
   if (piscando > 0){
      piscando--;
   }
   
   
  
   //node->setMaterialFlag(EMF_WIREFRAME, (piscando % 5) > 3);
   node->setMaterialFlag(EMF_WIREFRAME, piscando  != 0);
   //calculo momento
      
   //ainda não atingiu a velocidade máxima
   if (aceleracao >= 0 &&  momento.dotProduct(VetorFrente()) < velocidadeMaxima) 
         momento = momento + (aceleracao * VetorFrente());
   if (aceleracao < 0 &&  momento.dotProduct(VetorFrente()) > -velocidadeMaxima) 
         momento = momento + (aceleracao * VetorFrente());
   
   //if (momento.getLength() >= 2 * velocidadeMaxima) momento = (1 / momento.getLength()) * momento;
   
   //vejo o que varia com o impacto
   momento = momento + momentoImpacto;
   momentoImpacto = vector3df(0, 0, 0);
   //não deixo o momento ser grande demais
   if (momento.getLength() > 2) momento = (2 / momento.getLength()) * momento;      
   //tiro a resistência (de maneira linear)
   if (momento.getLength() > 0)
   {
      if (momento.getLength() < resistencia) momento = vector3df(0, 0, 0);
      else momento = (1 - resistencia) * momento;
   }
   
   //calculo a translação e verifico se bateu no cenário
   if (!posicaoEstimada.equals(node->getPosition(), 0.1f)) bateuCenario = true;
   else bateuCenario = false;
   posicaoEstimada = node->getPosition() + momento;
   
   
   /*list<void *>::Iterator lista;
   Objeto *outro = (Objeto *) central->PrimeiroObjeto(&lista);
   
   while (outro != NULL)
   {
      if (!SouEu(outro) && Bateu(outro)) BateuNeste(outro);
      outro = (Objeto *) central->ProximoObjeto(&lista);
   }*/ 
   
   
   //node->setPosition(posicaoEstimada);
   MudaPosicao(posicaoEstimada);
   
   if (esq)
   {
      if (quantoVira > -maxVirada) quantoVira -= velocidadeVirada;     
   }
   else
   {
      if (dir)
      {
         if (quantoVira < maxVirada) quantoVira += velocidadeVirada;         
         //anguloHorizontal += 1;
         //inclinacao += 1;
         //if (inclinacao > maxInclinacao) inclinacao = maxInclinacao;
      }
      else{
      	if (quantoVira > 2*velocidadeVirada) quantoVira -= 2*velocidadeVirada;
	else if (quantoVira < -2*velocidadeVirada) quantoVira += 2*velocidadeVirada; 
	else quantoVira = 0;
	if (inclinacao > 0) inclinacao -= 0.5f;
	if (inclinacao < 0) inclinacao += 0.5f;
      }
   }
   anguloHorizontal += quantoVira;
   inclinacao += quantoVira;
   if (inclinacao < -maxInclinacao) inclinacao = -maxInclinacao;
   if (inclinacao > maxInclinacao) inclinacao = maxInclinacao;
      
   //arrumo a rotação da nave
   node->setRotation(vector3df(0, anguloHorizontal, 0));
   matrix4 m;
   m.setRotationDegrees(vector3df(0, 0, inclinacao));
   m = node->getRelativeTransformation() * m;
   node->setRotation(m.getRotationDegrees());
}

//-------------------------------------------------------------------------
//faz a comunicação entre objetos. Como não entendo mensagens por enquanto, 
//retorno NULL
int Objeto::Mensagem(int msg, void *param)
{
   return NADA;
}

//---------------------------------------------------------------------------
Objeto::Objeto(Central *centralAux, char *nome)
{
   central = centralAux;
   ZeraComandos();

   quantoVira = 0.0f;
   morto = false;
   bateuCenario = false;
   resistencia = 0.02f;
   maxInclinacao = 30.0f;
   inclinacao = 0;
   anguloHorizontal = 0;
   velocidadeMaxima = 0.1f;
   aceleracao = 0.0f;
   parafrente = false;
   paratras = false;
   velocidadeVirada = 0.1f;
   maxVirada = 1.0f;
   //carrego o arquivo da Objeto e o adiciono no cenário
   if (nome != NULL)
   {
      LeModelo(nome);
	}
	//seletor = central->Device()->getSceneManager()->createTriangleSelector(mesh->getMesh(0), node);
	//node->setTriangleSelector(seletor);
   //seletor->drop();
	
	piscando = TEMPO_PISCANDO;
	momento = vector3df(0, 0, 0);
	massa = MASSA_OBJETO;
}

//----------------------------------------------------------------------
Objeto::~Objeto(void)
{
   node->remove();
}
