#ifndef __LISTE2__H_
#define __LISTE2__H_

/*---------------Prototypes Structures ---------------*/

typedef struct Element
{
  struct Arbre *arbre;
  struct Element *suivant;
  struct Element *precedent;
}Element;

typedef struct ListeDouble
{
  struct Element *premier;
  struct Element *dernier;
}ListeDouble;

typedef struct Arbre
{
  int count;
  char occurrence;
  struct Arbre *gauche;
  struct Arbre *droite;
}Arbre;

/*---------------Prototypes fonctions ---------------*/

ListeDouble * newliste();
void ajouterListe(ListeDouble *l, Arbre *arbre);
void afficherliste(ListeDouble* list);
Arbre * newArbre();
void arbreHuffman(ListeDouble *l);
Arbre *creationArbre(char occu, int count);
void afficheArbre(Arbre * arbre);



#endif
