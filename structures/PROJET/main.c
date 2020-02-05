#include <stdio.h>
#include <stdlib.h>
#include "Liste.h"

#define TAILLE_MAX 1000

int main(int argc, char *argv[])
{
  char chaine[TAILLE_MAX];
  int Countletter[255] = {0};
  FILE *fichier = NULL;
  fichier = fopen("text.txt", "r");
  if (fichier != NULL)
  {
    //FIchier ouvert
    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
      int i = 0;
      while (chaine[i] != '\n')
      {
        Countletter[chaine[i]]++;
        i++;
      }
    }
  }
  else
  {
    printf("Impossible d'ouvrir le fichier ");
  }
  fclose(fichier);

  char c;
  ListeDouble *liste = newliste();
  for (int i = 0; i<255;i++)
  {
    if(Countletter[i]>0)
    {
      Arbre * arbre = creationArbre((char)i,Countletter[i]);
      ajouterListe(liste, arbre);
    }
  }

  afficherliste(liste);
  arbreHuffman(liste);
  printf("TEST ARBRE HUFFMAN\n");
  afficherliste(liste);
  return 0;
}
