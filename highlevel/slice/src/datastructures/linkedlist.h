#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdio.h>

struct linkedlistnode {
  struct linkedlistnode *next, *prev;
  void *payload;
};

typedef struct linkedlistnode linkedlistnode;

typedef struct {
  linkedlistnode *first, *last;
  int size;
} linkedlist;

linkedlist *linkedlist_make(void);
void linkedlist_insertfirst(linkedlist *ll, linkedlistnode *lln);
void linkedlist_remove(linkedlist *ll, linkedlistnode *lln);

linkedlistnode *linkedlist_makepaynode(void *payload);
void linkedlist_insertafter(linkedlist *ll,
			    linkedlistnode *lln,
			    linkedlistnode *pos
                            );

linkedlistnode *ll_insert(linkedlist *ll, void *payload);



#endif /* !LINKEDLIST_H_ */
