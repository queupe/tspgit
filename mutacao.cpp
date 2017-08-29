/*
*  mutacao.cpp
*
*  Módulo responsável pelo mutação de um indivíduo
*  Autor: Geraldo José Ferreira Chagas Junior - gjr.doc@gmail.com
*
*  PPGI - NCE - UFRJ
*  Data Criação: 14/05/2017
*  Datas de Modificações:
*
*/

#include "mutacao.hpp"
#include <iostream>

//Apenas letura
TMapaGenes *TMutacao::getMapa() { return VP_Mapa; }
TArqLog *TMutacao::getArqLog()  { return VP_ArqSaida; }

TMutacao::TMutacao (TMapaGenes *mapa, TArqLog *arqSaida, int tipoMutacao)
{
   VP_Mapa = mapa;
   VP_ArqSaida = arqSaida;
   VP_mutacao = tipoMutacao;
}

int TMutacao::processa (TIndividuo *individuo)
{
   switch (VP_mutacao)
   {
      case 0:
      {
         return EM(individuo);
         break;
      }
      case 1:
      {
         return SM(individuo);
         break;
      }
      case 2:
      {
         return twoOPT(individuo);
         break;
      }
      case 3:
      {
         return twoOPT2(individuo);
         break;
      }
      case 4:
      {
         return SIM(individuo);
         break;
      }
      case 5:
      {
         return threeOPT(individuo);
         break;
      }
      case 6:
      {
         return threeOPT2(individuo);
         break;
      }
      case 7:
      {
         return DM(individuo);
         break;
      }
      case 8:
      {
         return IVM(individuo);
         break;
      }
      case 9:
      {
         return ISM(individuo);
         break;
      }
      case 10:
      {
         return GSM(individuo);
         break;
      }
      case 11:
      {
         return DBM(individuo);
         break;
      }
      case 12:
      {
         return DBM2(individuo);
         break;
      }
      case 13:
      {
         return SHMO(individuo);
         break;
      }
      default:
      {
         break;
      }
   }

   return 0;
}

int TMutacao::processa(TIndividuo *individuo, TPopulacao *populacao)
{
  return NJ(individuo, populacao);
}
/**
 *
 * Exchange mutation (EM)
 *
 * Banzhaf (1990). The “Molecular” Traveling Salesman. Biological Cybernetics 64: 7–14.
 *
 **/
int TMutacao::EM(TIndividuo *individuo)
{
  double dist = individuo->get_distancia();
  int i = TUtils::rnd(1, individuo->get_qtdeGenes()-1);
  int j = TUtils::rnd(1, individuo->get_qtdeGenes()-1);

  individuo->troca_indice(i , j);

  return (dist == individuo->get_distancia())?0:1;
}

/**
 *
 * Scramble mutation (SM)
 *
 * Syswerda (1991). Schedule Optimization Using Genetic Algorithms. In Davis, L. (ed.)
 * Handbook of Genetic Algorithms, 332–349. New York: Van Nostrand Reinhold.
 *
 **/
int TMutacao::SM(TIndividuo *individuo)
{
  int i1, i2;

  double dist = individuo->get_distancia();

  do
  {
    i1 = TUtils::rnd(1, individuo->get_qtdeGenes()-1);
    i2 = TUtils::rnd(1, individuo->get_qtdeGenes()-1);
  }
  while(i1 == i2);

  individuo->embaralha(i1, i2);

  return (dist == individuo->get_distancia())?0:1;
}

/**
 *
 * 2-opt
 *
 * Croes, G. A. (1958). A Method for Solving Traveling-Salesman
 * Problems. Operations Research, 6(6), 791–812.
 *
 **/
int TMutacao::twoOPT(TIndividuo *individuo)
{
   //O 2-opt não pode ser realizado quando existem
   //menos de 4 vértices
   if (individuo->get_qtdeGenes()<4) return 0;

   double diff;
   double melhor;
   int Ci = -1, Cj = -1;
   melhor = individuo->get_distancia();

   for(int i = 1; i < individuo->get_qtdeGenes(); i++)
   {
      for(int j = i + 2; j < individuo->get_qtdeGenes() - 2; j++)
      {
         diff = individuo->get_dist_sub_reverso_indice(i, j);

         if(diff < melhor)
         {
				melhor = diff;
				Ci = i;
				Cj = j;
			}
		}
	}

   if(Ci != -1 && Cj != -1)
      individuo->inverte_sub_indice(Ci, Cj);
   else
      individuo->inverte_sub_indice(TUtils::rnd(1, individuo->get_qtdeGenes()-1), TUtils::rnd(1, individuo->get_qtdeGenes()-1));

   return (melhor == individuo->get_distancia())?0:1;
}

/**
 *
 * 2-opt(2)
 *
 * Utilizado em nosso primeiro artigo
 *
 **/
int TMutacao::twoOPT2(TIndividuo *individuo)
{
   if (individuo->get_extra()) return 0;

   //O 2-opt não pode ser realizado quando existem
   //menos de 4 vértices
   if (individuo->get_qtdeGenes()<4) return 0;

   double diff;
   double dist = individuo->get_distancia();

   for(int i = 1; i < individuo->get_qtdeGenes()-2; i++)
   {
      for(int j = i + 2; j < individuo->get_qtdeGenes(); j++)
      {
         diff = individuo->get_dist_sub_reverso_indice(i, j);

         if(individuo->get_distancia() > diff)
            individuo->inverte_sub_indice(i, j);
      }
   }

   individuo->set_extra((dist == individuo->get_distancia())?1:0);
   return individuo->get_extra()^1;
}

/**
 *
 * Simple Inversion mutation (SIM)
 *
 * Holland (1975). Adaptation in Natural and Artificial Systems. Ann Arbor:
 * University of Michigan Press.
 *
 * Grefenstette (1987). (Ed). Genetic Algorithms and Their Applications:
 * Proceedings of the Second International Conference. Hillsdale, New Jersey:
 * Lawrence Erlbaum.
 *
 **/
int TMutacao::SIM(TIndividuo *individuo)
{
   int begin, end;
   begin = TUtils::rnd(1, individuo->get_qtdeGenes() - 1);
   end = TUtils::rnd(1, individuo->get_qtdeGenes() - 1);

   //O método inverte_sub_indice realiza a inversão de uma subrota
   //entre duas posições passada como parâmetro.
   individuo->inverte_sub_indice(begin, end);
   return 1;
}

/**
 *
 * 3-opt
 *
 * Croes, G. A. (1958). A Method for Solving Traveling-Salesman
 * Problems. Operations Research, 6(6), 791–812.
 *
 **/
int TMutacao::threeOPT(TIndividuo *individuo)
{
   //O 3-opt não pode ser realizado quando existem
   //menos de 6 vértices
   if (individuo->get_qtdeGenes()<6) return 0;
   
   double gainActual, gainCandidato, diff;
   int Imas1, Jmas1, Kmas1, Ci = -1, Cj = -1, Ck = -1, op = -1;
   double min, valor = individuo->get_distancia();
   int n = individuo->get_qtdeGenes() - 1;
   min = valor;

   for(int i = 0; i < n - 4; i++)
   {
      for(int j = i + 2; j < n - 2; j++)
      {
         for(int K = 0; K < 10; K++)
         {
            int k = TUtils::rnd(j+2, n-1);

            Imas1 = i + 1;
            Jmas1 = j + 1;
            Kmas1 = k + 1;

            TGene *gi = individuo->get_por_indice(i);
            TGene *gj = individuo->get_por_indice(j);
            TGene *gk = individuo->get_por_indice(k);

            TGene *gImas1 = individuo->get_por_indice(Imas1);
            TGene *gJmas1 = individuo->get_por_indice(Jmas1);
            TGene *gKmas1 = individuo->get_por_indice(Kmas1);

            //operação 1
            gainActual = VP_Mapa->get_distancia(gi->ori, gImas1->dest) +
                         VP_Mapa->get_distancia(gj->ori, gJmas1->dest) +
                         VP_Mapa->get_distancia(gk->ori, gKmas1->dest);

            gainCandidato = VP_Mapa->get_distancia(gi->ori, gj->dest) +
                            VP_Mapa->get_distancia(gImas1->ori, gk->dest) +
                            VP_Mapa->get_distancia(gJmas1->ori, gKmas1->dest);

            diff = valor - gainActual + gainCandidato + 
				       this->calcValReverso(gImas1, gj) +
				       this->calcValReverso(gJmas1, gk);

            if(min > diff)
            {
               op = 0;
               Ci = i;
               Cj = j;
               Ck = k;
               min = diff;
            }

            //operação 2
            gainCandidato = VP_Mapa->get_distancia(gi->ori, gJmas1->dest) +
                            VP_Mapa->get_distancia(gk->ori, gImas1->dest) +
                            VP_Mapa->get_distancia(gj->ori, gKmas1->dest);

            diff = valor - gainActual + gainCandidato;

            if(min > diff)
            {
               op = 1;
               Ci = i;
               Cj = j;
               Ck = k;
               min = diff;
            }

            //operação 3
            gainCandidato = VP_Mapa->get_distancia(gi->ori, gk->dest) +
                            VP_Mapa->get_distancia(gJmas1->ori, gImas1->dest) +
                            VP_Mapa->get_distancia(gj->ori, gKmas1->dest);

            diff = valor - gainActual + gainCandidato +
                   this->calcValReverso(gJmas1, gk);

            if(min > diff)
            {
               op = 2;
               Ci = i;
               Cj = j;
               Ck = k;
               min = diff;
            }

            //operação 4
            gainCandidato = VP_Mapa->get_distancia(gi->ori, gJmas1->dest) +
                            VP_Mapa->get_distancia(gk->ori, gj->dest) +
                            VP_Mapa->get_distancia(gImas1->ori, gKmas1->dest);

            diff = valor - gainActual + gainCandidato +
				       this->calcValReverso(gImas1, gj);

            if(min > diff)
            {
               op = 3;
               Ci = i;
               Cj = j;
               Ck = k;
               min = diff;
            }
         }
      }
   }

   // realizando a troca
   if(Ci == -1 || Cj == -1)
   {
		Ci = TUtils::rnd(1, n-4);
      Cj = TUtils::rnd(Ci+2, n-2);
      Ck = TUtils::rnd(Cj+2, n);
      op = TUtils::rnd(0, 3);
   }
   
   switch(op)
   {
		case 0:
      {
			individuo->inverte_sub_indice(Ci+1, Cj);
         individuo->inverte_sub_indice(Cj+1, Ck);
			break;
		}
		case 1:
   	{
			individuo->troca_sub(Ci+1, Cj-Ci, Cj+1, Ck-Cj);
   	   break;
		}
		case 2:
		{
			individuo->inverte_sub_indice(Cj+1, Ck);
			individuo->troca_sub(Ci+1, Cj-Ci, Cj+1, Ck-Cj);						
   	   break;
		}
		case 3:
   	{
			individuo->inverte_sub_indice(Ci+1, Cj);
			individuo->troca_sub(Ci+1, Cj-Ci, Cj+1, Ck-Cj);
   	   break;
		}
		default:
			break;
	}
	
   return (valor == individuo->get_distancia())?0:1;
}

/**
 *
 * 3-opt(2)
 *
 * Utilizado em nossos primeiros testes
 *
 **/
int TMutacao::threeOPT2(TIndividuo *individuo)
{
	if (individuo->get_extra()) return 0;
   //O 3-opt não pode ser realizado quando existem
   //menos de 6 vértices
   if (individuo->get_qtdeGenes()<6) return 0;
   
   double gainActual, gainCandidato, diff;
   int Imas1, Jmas1, Kmas1, min, op = -1;
   double valor;
   double valorInicial = individuo->get_distancia();
   int n = individuo->get_qtdeGenes() - 1;
   
   for(int i = 0; i < n - 4; i++)
   {
      for(int j = i + 2; j < n - 2; j++)
      {
         for(int k = j+2; k < n-1; k++)
         {
				valor = individuo->get_distancia();
				min = valor;
				op = -1;
            Imas1 = i + 1;
            Jmas1 = j + 1;
            Kmas1 = k + 1;

            TGene *gi = individuo->get_por_indice(i);
            TGene *gj = individuo->get_por_indice(j);
            TGene *gk = individuo->get_por_indice(k);

            TGene *gImas1 = individuo->get_por_indice(Imas1);
            TGene *gJmas1 = individuo->get_por_indice(Jmas1);
            TGene *gKmas1 = individuo->get_por_indice(Kmas1);

            //operação 1
            gainActual = VP_Mapa->get_distancia(gi->ori, gImas1->dest) +
                         VP_Mapa->get_distancia(gj->ori, gJmas1->dest) +
                         VP_Mapa->get_distancia(gk->ori, gKmas1->dest);

            gainCandidato = VP_Mapa->get_distancia(gi->ori, gj->dest) +
                            VP_Mapa->get_distancia(gImas1->ori, gk->dest) +
                            VP_Mapa->get_distancia(gJmas1->ori, gKmas1->dest);


            diff = valor - gainActual + gainCandidato + 
			          this->calcValReverso(gImas1, gj) +
				       this->calcValReverso(gJmas1, gk);

            if(min > diff)
            {
               op = 0;
               min = diff;
            }

            //operação 2
            gainCandidato = VP_Mapa->get_distancia(gi->ori, gJmas1->dest) +
                            VP_Mapa->get_distancia(gk->ori, gImas1->dest) +
                            VP_Mapa->get_distancia(gj->ori, gKmas1->dest);

            diff = valor - gainActual + gainCandidato;

            if(min > diff)
            {
               op = 1;
               min = diff;
            }

            //operação 3
            gainCandidato = VP_Mapa->get_distancia(gi->ori, gk->dest) +
                            VP_Mapa->get_distancia(gJmas1->ori, gImas1->dest) +
                            VP_Mapa->get_distancia(gj->ori, gKmas1->dest);

            diff = valor - gainActual + gainCandidato +
                   this->calcValReverso(gJmas1, gk);
				   
            if(min > diff)
            {
               op = 2;
               min = diff;
            }

            //operação 4
            gainCandidato = VP_Mapa->get_distancia(gi->ori, gJmas1->dest) +
                            VP_Mapa->get_distancia(gk->ori, gj->dest) +
                            VP_Mapa->get_distancia(gImas1->ori, gKmas1->dest);

            diff = valor - gainActual + gainCandidato +
                   this->calcValReverso(gImas1, gj);

            if(min > diff)
            {
               op = 3;
               min = diff;
            }

            switch(op)
				{
					case 0:
					{
						individuo->inverte_sub_indice(i+1, j);
                  individuo->inverte_sub_indice(j+1, k);
						break;
					}
					case 1:
					{
						individuo->troca_sub(i+1, j-i, j+1, k-j);
						break;
					}
					case 2:
					{
						individuo->inverte_sub_indice(j+1, k);						
						individuo->troca_sub(i+1, j-i, j+1, k-j);
						break;
					}
					case 3:
					{
						individuo->inverte_sub_indice(i+1, j);						
						individuo->troca_sub(i+1, j-i, j+1, k-j);
						break;
					}
					default:
						break;
				}
			}
		}
	}
   
   individuo->set_extra((valorInicial == individuo->get_distancia())?1:0);
   return individuo->get_extra()^1;
}

/**
  * Mutação DM:
  *   Nessa mutação ele pega um início e um fim randomico, retira esse pedaço do vetor principal,
  *   depois pega uma posição randômica e reinplanta o pedaço.
**/
int TMutacao::DM(TIndividuo *individuo)
{
  int begin=0, end=0, insertpoint, diff;
  int lastindex = individuo->get_qtdeGenes() -1;
  
  begin = TUtils::rnd(1, lastindex -1);
  end = TUtils::rnd(begin+1, lastindex);
  diff = end-begin;
  insertpoint = TUtils::rnd(1, lastindex - diff);
  if(insertpoint > begin) insertpoint+= diff;
  //cout<<begin<<" "<<end<<" "<<diff<<" "<<insertpoint<<endl;
  individuo->troca_sub(insertpoint+1, 0, begin, (end-begin)+1);

  return 1;
}

/**
  * IVM:
  *   Nessa mutação ele pega um início e um fim randomico, retira esse pedaço do vetor principal,
  *   depois pega uma posição randômica e reinplanta o pedaço em ordem invertida.
**/
int TMutacao::IVM(TIndividuo *individuo)
{
  int begin=0, end=0, insertpoint, diff;
  int lastindex = individuo->get_qtdeGenes() -1;
  
  begin = TUtils::rnd(1, lastindex -1);
  end = TUtils::rnd(begin+1, lastindex);
  diff = end-begin;
  insertpoint = TUtils::rnd(1, lastindex - diff);
  if(insertpoint > begin) insertpoint+= diff;
  //cout<<begin<<" "<<end<<" "<<diff<<" "<<insertpoint<<endl;
  individuo->troca_sub(insertpoint+1, 0, begin, -((end-begin)+1));

  return 1;
}

/**
  * ISM:
  *   Tira um gene randômico do indivíduo e coloca em uma posição randômica.
**/
int TMutacao::ISM(TIndividuo *individuo)
{
  int i=0, j=0, lastindex = individuo->get_qtdeGenes();
  i = TUtils::rnd(1, lastindex - 2);
  j = TUtils::rnd(i+1, lastindex - 1);
  cout<<i<<" "<<j<<endl;
  individuo->troca_sub(i, 1, j+1, 0);

  return 1;
}
/**
  * GSM:
  *   Durante um número k<=quantidade de genes, pega-se indices de genes i,j randômicos dentro do
  *   individuo, testa se a troca do genes gera um caminho mais rápido, se for o caso, troca os genes
  *   e quebra o loop.
**/
int TMutacao::GSM(TIndividuo *individuo)
{
  int i=0, j=0, lastindex = individuo->get_qtdeGenes()-1;
  double originaldist=0, changeddist=0;

  for(int k=0; k <= lastindex; k++)
  {
    
    i = TUtils::rnd(1, lastindex - 1);
    j = TUtils::rnd(i+1, lastindex);
    originaldist = individuo->get_distancia();
    individuo->troca_indice(i,j);
    changeddist = individuo->get_distancia();
    //cout<<"i: "<<i<<";j: "<<j<<"; OD: "<<originaldist<<"; CD: "<<changeddist<<endl;
    if(originaldist > changeddist)
    {
      cout<<"loopbreak."<<endl;
      //cout<<individuo->toString()<<endl;
      break;
    }
    else
    {
      individuo->troca_indice(i,j);
    }
  }

  return 1;
}
/**
  *DBM:
  *  O flag no contreras estava inicializado false, mas isso n tem sentido pq o loop fica inútil.
  *  
**/

int TMutacao::DBM(TIndividuo *individuo)
{
  int i, j, k, l, lastindex =  individuo->get_qtdeGenes()-1;
  
  i = TUtils::rnd(1, lastindex - 6);
  j = i+2;
  k = TUtils::rnd(j+2, lastindex - 2);
  l = k+2;
  cout<<"i: "<<i<<"; j: "<<j<<"; k: "<<k<<"; l: "<<l<<endl;
  individuo->troca_indice((i+1), (k+1));
  individuo->troca_indice(j, l);

  return 1;
}

/**
  *DBM2:
  *  Essa me confundiu um pouco, mas depois de ler o código percebi que o que ele faz é pegar quatro
  *  indices em sequencia e depois realizar uma troca de subrotas.
  *  
**/

int TMutacao::DBM2(TIndividuo *individuo)
{
  int i, j, k, l, lastindex = individuo->get_qtdeGenes()-1;

  i = TUtils::rnd(1, lastindex - 6);
  j = TUtils::rnd(i+1, lastindex - 4);
  k = TUtils::rnd(j+1, lastindex - 2);
  l = TUtils::rnd(k+1, lastindex);
  cout<<"i: "<<i<<"; j: "<<j<<"; k: "<<k<<"; l:"<<l<<endl;
  individuo->troca_sub(i+1, (j-i), k+1, (l-k));

  return 1;
}
/**
  *SHMO:
  *  Esse é um método guloso. Dentro desse O(n^2) aí, ele realiza três testes de troca.
  *  Os testes estão descritos abaixo. Não achei modos de simplificar esse n^2.
  *  
**/
int TMutacao::SHMO(TIndividuo *individuo)
{
  int  lastindex = individuo->get_qtdeGenes()-1;
  double value, new_value;

  for(int i=1;i<lastindex-2; i++)
  {
    for(int j=i+2; j<lastindex;j++)
    {
      //Primeira troca: Testa se a inversão entre i+1 e j+1 vale a pena.
      value = individuo->get_distancia();
      new_value = individuo->get_dist_sub_reverso_indice(i+1, j+1);
      if(value>new_value)
      {
        individuo->inverte_sub_indice(i+1, j+1);
      }
      //Segunda troca: Testa se tirando j e colocar antes do i vale a pena.
      value = individuo->get_distancia();
      individuo->troca_sub(i, 0, j, 1);
      new_value = individuo->get_distancia();
      if(new_value > value) individuo->troca_sub(i, 1, j, 0);
      //Terceira troca: Testa se trocar i pelo j vale a pena.
      value = individuo->get_distancia();
      individuo->troca_indice(i,j);
      new_value = individuo->get_distancia();
      if(new_value > value) individuo->troca_indice(i,j);
    }
  }
  return 1;
}
/**
  *Tipo 3:
  *  Metodo no NJ. Nele, pega-se um subcaminho interno que vai do gene c ao cLinha e outro externo
  *  que é o subcaminho que vai do gene depois de cLinha até o anterior de c. Depois, escolhe-se um gene
  *  R e um S, sendo que, quando trocados, tem o maior valor de caminho. Enfim, coloca-se o caminho
  *  interior dentro do caminho exterior depois da posição do R.
  *  
**/
void TMutacao::Tipo3(TIndividuo *opcao, TGene *c, TGene *cLinha)
{
  TGene *InnerPathIni, *InnerPathEnd, *OutPathIni, *OutPathEnd, *R, *S, *InsertionPoint, *sNextGen;
  double ChangedValue, MaxValue = -1 * infinito;

  cout<<"Calculando opcao 3"<<endl;
  if(c->i < cLinha->i)
  {
    cout<<"c<cLinha"<<endl;
    InnerPathIni = c;
    cout<<"InnerPathIni: "<< InnerPathIni->i<<endl;
    InnerPathEnd = cLinha;
    cout<<"InnerPathEnd: "<< InnerPathEnd->i<<endl;
    OutPathIni = cLinha->prox;
    cout<<"OutPathIni: "<< OutPathIni->i<<endl;
    OutPathEnd = c->ant;
    cout<<"OutPathEnd: "<< OutPathEnd->i<<endl;
  }
  else
  {
    cout<<"cLinha<c"<<endl;
    InnerPathIni = cLinha;
    cout<<"InnerPathIni: "<< InnerPathIni->i<<endl;
    InnerPathEnd = c;
    cout<<"InnerPathEnd: "<< InnerPathEnd->i<<endl;
    OutPathIni = c->prox;
    cout<<"OutPathIni: "<< OutPathIni->i<<endl;
    OutPathEnd = cLinha->ant;
    cout<<"OutPathEnd: "<< OutPathEnd->i<<endl;
  }
  cout<<"Escolhendo R e S"<<endl;
  for(TGene *InnerGen = InnerPathIni; InnerGen->i != InnerPathEnd->prox->i; InnerGen = InnerGen->prox)
  {
    for(TGene *OutGen = OutPathIni; OutGen->i != OutPathEnd->prox->i; OutGen = OutGen->prox)
    {
      if(InnerGen->i == 0 || OutGen->i == 0) continue;
      opcao->troca_indice(InnerGen->i, OutGen->i);
      ChangedValue = opcao->get_distancia();
      opcao->troca_indice(InnerGen->i, OutGen->i);
      if(ChangedValue > MaxValue)
      {
        R = InnerGen;
        S = OutGen;
        MaxValue = ChangedValue;
      }
    }
  }
  cout<<"Indice de R e S são "<< R->i<<" "<< S->i <<endl;
  InsertionPoint = sNextGen = S->prox;
  //A posição 0 não pode ser alterada por conversão do autor.
  if(InsertionPoint->i == 0) InsertionPoint = sNextGen = InsertionPoint->prox;
  cout<<"Indice do ponto de inserção "<< InsertionPoint->i<<endl;
  //Basicamente: É pego um gene do caminho a ser transferido e seu sucessor, depois de transferido e seu index alterado no processo, o proximo é 
  //  pego baseado no Nextgen, que serve como ponteiro para o proximo gene da lista. No caso do tipo 3, é a lista de fora do caminho c.....cLinha.
  cout<<"Inserindo caminho de dentro no de fora."<<endl;
  cout<<"Individuo atual: "<< opcao->toString()<<endl;
  for(TGene *NextGen = InnerPathIni->prox, *InnerGen = InnerPathIni;
     InnerGen->i != InnerPathEnd->prox->i; NextGen=NextGen->prox, InnerGen = NextGen->ant)
  {
    cout<<"opcao atual: "<< opcao->toString()<<endl;
    cout<<"indice NextGen: "<< NextGen->i<<" ";
    cout<<"indice InnerGen: "<< InnerGen->i<<" ";
    cout<<"Indice InsertionPoint: "<< InsertionPoint->i<<endl;
    if(InsertionPoint->i == 0 || InnerGen->i == 0) continue;
    else opcao->troca_sub(InsertionPoint->i, 0, InnerGen->i, 1);
    InsertionPoint = InnerGen->prox;
    cout<<"opcao depois: "<< opcao->toString()<<endl;
  }
  cout<<"Novo individuo: "<< opcao->toString()<<endl;
  opcao->troca_sub(R->prox->i, 0, sNextGen->i, 1);
}
/**
  *Tipo 4:
  *  Metodo no NJ. Mesma coisa do tipo 3, só que o gene c e cLinha faz parte do caminho exterior.
  *  
**/
void TMutacao::Tipo4(TIndividuo *opcao, TGene *c, TGene *cLinha)
{
  TGene *InnerPathIni, *InnerPathEnd, *OutPathIni, *OutPathEnd, *R, *S, *sNextGen;
  double ChangedValue, MaxValue = -1 * infinito;

  cout<<"Calculando opcao 4"<<endl;
  if(c->i < cLinha->i)
  {
    cout<<"c<cLinha"<<endl;
    InnerPathIni = c->prox;
    cout<<"InnerPathIni: "<< InnerPathIni->i<<endl;
    InnerPathEnd = cLinha->ant;
    cout<<"InnerPathEnd: "<< InnerPathEnd->i<<endl;
    OutPathIni = cLinha;
    cout<<"OutPathIni: "<< OutPathIni->i<<endl;
    OutPathEnd = c;
    cout<<"OutPathEnd: "<< OutPathEnd->i<<endl;
  }
  else
  {
    cout<<"cLinha<c"<<endl;
    InnerPathIni = cLinha->prox;
    cout<<"InnerPathIni: "<< InnerPathIni->i<<endl;
    InnerPathEnd = c->ant;
    cout<<"InnerPathEnd: "<< InnerPathEnd->i<<endl;
    OutPathIni = c;
    cout<<"OutPathIni: "<< OutPathIni->i<<endl;
    OutPathEnd = cLinha;
    cout<<"OutPathEnd: "<< OutPathEnd->i<<endl;
  }
  cout<<"Escolhendo R e S"<<endl;
  cout<<"Escolhendo R e S"<<endl;
  for(TGene *InnerGen = InnerPathIni; InnerGen->i != InnerPathEnd->prox->i; InnerGen = InnerGen->prox)
  {
    for(TGene *OutGen = OutPathIni; OutGen->i != OutPathEnd->prox->i; OutGen = OutGen->prox)
    {
      if(InnerGen->i == 0 || OutGen->i == 0) continue;
      opcao->troca_indice(InnerGen->i, OutGen->i);
      ChangedValue = opcao->get_distancia();
      opcao->troca_indice(InnerGen->i, OutGen->i);
      if(ChangedValue > MaxValue)
      {
        R = InnerGen;
        S = OutGen;
        MaxValue = ChangedValue;
      }
    }
  }
  cout<<"Indice de R e S são "<< R->i<<" "<< S->i <<endl;
  sNextGen = S->prox;
  //A posição 0 não pode ser alterada por conversão do autor.
  if(sNextGen->i == 0) sNextGen = sNextGen->prox;
  //Basicamente: É pego um gene do caminho a ser transferido e seu sucessor, depois de transferido e seu index alterado no processo, o proximo é 
  //  pego baseado no Nextgen, que serve como ponteiro para o proximo gene da lista. No caso do tipo 3, é a lista de fora do caminho c.....cLinha.
  cout<<"Inserindo caminho de dentro no de fora."<<endl;
  cout<<"opcao velha: "<< opcao->toString()<<endl;
  for(TGene *NextGen = InnerPathIni->prox, *InnerGen = InnerPathIni, *InsertionPoint = S->prox;
      InnerGen->i != InnerPathEnd->prox->i;
      NextGen=NextGen->prox, InnerGen = NextGen->ant
     )
  {
    cout<<"indice NextGen: "<< NextGen->i<<" ";
    cout<<"indice InnerGen: "<< InnerGen->i<<" ";
    cout<<"Indice InsertionPoint: "<< InsertionPoint->i<<endl;
    cout<<"opcao atual:/t"<< opcao->toString()<<endl;
    if(InsertionPoint->i == 0) InsertionPoint = InsertionPoint->prox;
    if(InnerGen->i == 0) InnerGen = InnerGen->prox;
    opcao->troca_sub(InsertionPoint->i, 0, InnerGen->i, 1);
    InsertionPoint = InnerGen->prox;
    cout<<"opcao depois:/t"<< opcao->toString()<<endl;
  }
  cout<<"Nova opcao: "<< opcao->toString()<<endl;
  opcao->troca_sub(R->prox->i, 0, sNextGen->i, 1);
}

int TMutacao::NJ(TIndividuo *individuo, TPopulacao *populacao)
{
  float probabilidade = 0.5;
  TGene *c, *cLinha, *cTemp;
  TIndividuo *indTemp, **opcoes;
  TMapaGenes *mapaGenes = individuo->getMapa();

  int nMaxVizinhos = 3, nMaxInteracoes = 5;
  int rndi=-1, MelhorOpcao=-1;
  double MenorDinstancia = infinito, CurrentDisntance;

  opcoes = (TIndividuo **) malloc(4 * sizeof(TIndividuo*));
  if(opcoes==NULL)
  {
    cout<<"Erro no maloc de opcoes!"<<endl;
    return 0;
  }
  for(int interacao=0; interacao<nMaxInteracoes; interacao++)
  {
    cout<< "Interação " << interacao <<endl;
    //Opções de indivíduos a ser escolhida
    opcoes[0] = individuo->clona();
    opcoes[1] = individuo->clona();
    opcoes[2] = individuo->clona();
    opcoes[3] = individuo->clona();

    cout<< "Distancia 0: "<< opcoes[0]->get_distancia()<<endl;
    cout<< "Distancia 1: "<< opcoes[1]->get_distancia()<<endl;
    cout<< "Distancia 2: "<< opcoes[2]->get_distancia()<<endl;
    cout<< "Distancia 3: "<< opcoes[3]->get_distancia()<<endl;

    //seleciona o gene c.
    cout<< "Selecionando c"<<endl;
    c = individuo->get_por_indice(TUtils::rnd(1, individuo->get_qtdeGenes()-1));
    cout<< "Posicao do c: " << c->i<<endl;

    //seleciona o gene cLinha
    cout<< "Selecionando cLinha"<<endl;
    if(TUtils::flip(probabilidade))
    {
      cout<< "Acertou na probabilidade."<<endl;
      //pega o proximo gene de um indivíduo randomico na populaçao, sendo c != cLinha.
      do
      {
        rndi = TUtils::rnd(0, populacao->get_qtdeIndividuo() -1);
        cout<< "Selecionou individuo randomico na populacao com indice "<< rndi<<endl;
        indTemp = populacao->get_individuo(rndi);
        cTemp = indTemp->get_por_id(c->id)->prox;
        cLinha = individuo->get_por_id(cTemp->id);
      }while (c->id == cLinha->id);
      cout<< "cLinha indice "<<cLinha->i<<endl;
    }
    else
    {
      //Pega no individuo o id do gene que tem a menor distancia possivel com c dentro do mapa.
      cout<<"Errou na probabilidade."<<endl;
      vector< pair<int, double>> distancias;
      cout<<"Montando par de distancias"<<endl;
      for(int i=1; i<individuo->get_qtdeGenes(); i++)
      {
        if(i!=c->id)
        {
          pair<int, double> dist(i, mapaGenes->get_distancia(i, c->id));
          cout<< "Distancia "<< dist.first <<": "<<dist.second<<endl;
          distancias.push_back(dist);
        }
      }
      cout<<"Quantidades de par de distancias: "<< distancias.size()<<endl;
      cout<<"Ordenando distancias"<<endl;
      sort(distancias.begin(), distancias.end(), TUtils::compare_pair_second<int, double, std::less<double>>());
      rndi = TUtils::rnd(0, nMaxVizinhos-1);
      cLinha = individuo->get_por_id(distancias[rndi].first);
      cout<<"cLinha selecionado com indice "<< cLinha->i<<endl;
    }
    //Se são visinhos, pula a interação;
    if(c->prox == cLinha || c->ant == cLinha)
    {
      cout<<"c e cLinha são vizinhos. Pulando a interacao."<<endl;
      continue;
    }
    else
    {
      cout<<"c e cLinha Não são visinhos"<<endl;
      //Opçao 1: o c é fixo.
      cout<<"Calculando tipo 1."<<endl;
      if(c->i < cLinha->i) opcoes[0]->inverte_sub_indice(c->prox->i, cLinha->i);
      else opcoes[0]->inverte_sub_indice(cLinha->i, c->ant->i);
      //Opção 2: o cLinha é fixo.
      cout<<"Calculando tipo 2."<<endl;
      if(c->i < cLinha->i) opcoes[1]->inverte_sub_indice(c->i, cLinha->ant->i);
      else opcoes[1]->inverte_sub_indice(cLinha->prox->i, c->i);
      cout<<"Calculando tipo 3."<<endl;
      Tipo3(opcoes[2], c, cLinha);
      cout<<"Calculando tiṕo 4."<<endl;
      //Tipo4(opcoes[3], c, cLinha);
      cout<<"Pegando menor distancia entre as opcoes."<<endl;
      for(int i=0; i<4; i++)
      {
        CurrentDisntance = opcoes[i]->get_distancia();
        cout<<"Distancia da opcao "<<i<<": "<<CurrentDisntance<<endl;
        if(CurrentDisntance < MenorDinstancia)
        {
          MenorDinstancia = CurrentDisntance;
          MelhorOpcao = i;
        }
      }
      cout<<"A melhor opção é a opcao "<< MelhorOpcao<<endl;
      cout<<"Tamanho do individuo: "<<individuo->get_qtdeGenes()<<endl;
      switch(MelhorOpcao)
      {
        case 0:
          cout<<"Subistituindo individuo por opcao 0"<<endl;
          individuo->novo(opcoes[0]);
          break;
        case 1:
          cout<<"Subistituindo individuo por opcao 1"<<endl;
          individuo->novo(opcoes[1]);
          break;
        case 2:
          cout<<"Subistituindo individuo por opcao 2"<<endl;
          individuo->novo(opcoes[2]);
          break;
        case 3:
          cout<<"Subistituindo individuo por opcao 3"<<endl;
          individuo->novo(opcoes[3]);
          break;
      }
      cout<<"Tamanho do individuo: "<<individuo->get_distancia()<<endl;
    }
  }

  return 1;
}

/*************************
*  Métodos auxiliares
*************************/
double TMutacao::calcValReverso (TGene *g1, TGene *g2)
{
	double resultado = 0;
	for (TGene *aux = g1; aux->id != g2->id; aux = aux->prox)
	{
		resultado -= VP_Mapa->get_distancia(aux->ori, aux->prox->dest);
		resultado += VP_Mapa->get_distancia(aux->prox->ori, aux->dest);
	}
	
	return resultado;
}