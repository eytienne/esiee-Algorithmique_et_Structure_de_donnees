#include "note.h"
#include "simpleLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void ajouterNoteListe(SimpleLinkedList **notes, long idEleve, float note) {
	Element e;
	e.n.idEleve = idEleve;
	e.n.valeurNote = note;
	ajouterAListe(notes, &e);
}

void afficheNoteId(const SimpleLinkedList *notes, long idEleve) {
	while (notes != NULL && notes->value != NULL) {
		if (notes->value->n.idEleve == idEleve) {
			printf("Note eleve n° %ld : %f\n", idEleve,
				   notes->value->n.valeurNote);
		}
		notes = notes->next;
	}
}