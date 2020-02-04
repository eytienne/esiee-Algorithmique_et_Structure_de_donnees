#include "note.h"
#include "simpleLinkedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	SimpleLinkedList *notes = newSimpleLinkedList();

	ajouterNoteListe(&notes, 1, 13);
	assert(notes->value->n.idEleve == 1);
	assert(notes->value->n.valeurNote == 13);

	ajouterNoteListe(&notes, 2, 20);
	assert(notes->value->n.idEleve == 2);
	assert(notes->value->n.valeurNote == 20);

	afficheNoteId(notes, 1);

	return 0;
}
