/*******************************************************************************
 *  Objectif : Tester la pile d'entiers
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../lib/pile.h"

int main()
{
    Pile pile;

    /* Initialiser la pile */
    initialiser(&pile);
    assert(est_vide(pile));

    /* Empiler un premier �l�ment */
    empiler(&pile, 'A');
    assert(! est_vide(pile));
    assert(sommet(pile) == 'A');

    /* Empiler un deuxi�me �l�ment */
    empiler(&pile, 'B');
    assert(! est_vide(pile));
    assert(sommet(pile) == 'B');

    /* Empiler un troisi�me �l�ment */
    empiler(&pile, 'C');
    assert(! est_vide(pile));
    assert(sommet(pile) == 'C');

    /* D�piler tous les �l�ments */
    depiler(&pile);
    assert(! est_vide(pile));
    assert(sommet(pile) == 'B');
    depiler(&pile);
    assert(! est_vide(pile));
    assert(sommet(pile) == 'A');
    depiler(&pile);
    assert(est_vide(pile));

    return EXIT_SUCCESS;
}

