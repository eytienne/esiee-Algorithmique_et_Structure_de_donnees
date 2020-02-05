#include <stdio.h>
#include <stdlib.h>
#include "Liste.h"

/*/*--------------- Création d'une liste ---------------*/
ListeDouble * newliste()
{
  ListeDouble * list = (ListeDouble *)malloc(sizeof(ListeDouble));
  if(list==NULL)
  {
    printf("Erreur allocation Liste\n");
    exit(EXIT_FAILURE);
  }
  list->premier = NULL;
  list->dernier = NULL;
  return list;
}

/*--------------- Ajout d'une liste ---------------*/
void ajouterListe(ListeDouble *l, Arbre *arbre)
{
  Element * element = (Element*)malloc(sizeof(Element));

  element->arbre = arbre;
  Element *temp = l->premier;
  if (arbre->occurrence == (char)0)
  {
      while ((temp != NULL) && (temp->arbre->count <= arbre->count))
      {

        temp = temp->suivant;
      }

  }
  else
  {
    while ((temp != NULL) && (temp->arbre->count < arbre->count))
    {

      temp = temp->suivant;
    }

    while ((temp != NULL) && (temp->arbre->count == arbre->count) && (temp->arbre->occurrence < arbre->occurrence))
    {
      temp = temp->suivant;
    }
  }
  element->suivant = temp;
  if (temp != NULL && temp->precedent != NULL)
  {
      temp->precedent->suivant = element;
      element->precedent = temp->precedent;
  }
  else
  {
    element->precedent = NULL;
  }
  if (temp != NULL)
  {
    temp->precedent = element;
  }
  if (temp == l->premier)
  {
    l->premier = element;
  }

  if (temp == NULL) {
    element->precedent = l->dernier;
    l->dernier = element;
  }
}

/*--------------- Affichage de la liste---------------*/


void afficherliste(ListeDouble* list)
{
  Element * test = list->premier;
  printf("Les listes sont : \n");
  while (test != NULL)
  {

    printf("            [%c] -> [%d]\n", test->arbre->occurrence, test->arbre->count);
    if (test->arbre->gauche != NULL || test->arbre->droite != NULL)
    {
      afficheArbre(test->arbre);
    }
    test = test->suivant;
  }
}

/*--------------- Création d'arbre---------------*/

Arbre * newArbre()
{
  Arbre * arbre = (Arbre *)malloc(sizeof(Arbre));
  if (arbre == NULL)
  {
    printf("Erreur d'allocation dynamique arbre.\n");
    exit(EXIT_FAILURE);
  }
  arbre->count = 0;
  arbre->occurrence = 0;
  arbre->gauche = NULL;
  arbre->droite = NULL;
  return arbre;
}

/*--------------- Construction arbre Huffman ---------------*/

void arbreHuffman(ListeDouble *l)
{
  Element * test = l->premier;
  while (test->suivant != NULL)
  {
    Arbre *arbre = creationArbre((char)0, (test->arbre->count + test->suivant->arbre->count));
    arbre->gauche = creationArbre(test->arbre->occurrence, test->arbre->count);
    test = test->suivant;
    arbre->droite = creationArbre(test->arbre->occurrence, test->arbre->count);
    ajouterListe(l, arbre);
    l->premier = test->suivant;
    break;
  }
}

/*--------------- Création arbre pour Huffman ---------------*/
Arbre * creationArbre(char occu, int count)
{
  Arbre * arbre = newArbre();
  arbre->count = count;
  arbre->occurrence = occu;
  return arbre;
}

void afficheArbre(Arbre* arbre)
{

  printf("( [%c] -> [%d] | )", arbre->gauche->occurrence, arbre->gauche->count);
  printf("( [%c] -> [%d] | )\n", arbre->droite->occurrence, arbre->droite->count);

  afficheArbre(arbre->gauche);
  afficheArbre(arbre->droite);

}
