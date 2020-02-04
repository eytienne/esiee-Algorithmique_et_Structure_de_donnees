
#ifndef NOTE_H
#define NOTE_H

typedef struct SimpleLinkedList SimpleLinkedList;
typedef struct Note {
	long idEleve;
	float valeurNote;
} Note;

struct Element {
	Note n;
};

void ajouterNoteListe(SimpleLinkedList **notes, long idEleve, float note);

void afficheNoteId(const SimpleLinkedList *notes, long idEleve);

#endif