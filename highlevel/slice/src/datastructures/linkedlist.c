#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "misc.h"
#include "linkedlist.h"

linkedlist *linkedlist_make(void) {
  linkedlist *ll;
  ll = (linkedlist*) SafeMalloc(sizeof(linkedlist));
  ll->first = ll->last = NULL;
  return ll;
}

linkedlistnode *linkedlist_makepaynode(void *payload) {
  linkedlistnode *lln;
  lln = (linkedlistnode*) SafeMalloc(sizeof(linkedlistnode));
  lln->next = lln->prev = NULL;
  lln->payload = payload;
  return lln;
}


void linkedlist_insertfirst(linkedlist *ll,
			    linkedlistnode *lln) {
  lln->next = lln->prev = NULL;
  if (ll->first == NULL) {
    ll->first = ll->last = lln;
    return;
  }
  lln->next = ll->first;
  ll->first->prev = lln;
  ll->first = lln;
}

void linkedlist_insertafter(linkedlist *ll,
			    linkedlistnode *lln,
			    linkedlistnode *pos) {
  lln->next = lln->prev = NULL;
  lln->next = pos->next;
  lln->prev = pos;
  pos->next = lln;
  if (pos == ll->last) {
    ll->last = lln;
  }
}

void linkedlist_remove(linkedlist *ll, linkedlistnode *lln) {
  if (lln->prev != NULL) {
    lln->prev->next = lln->next;
  }
  if (lln->next != NULL) {
    lln->next->prev = lln->prev;
  }
  if (ll->first == lln) {
    ll->first = lln->next;
  }
  if (ll->last == lln) {
    ll->last = lln->prev;
  }
}

linkedlistnode *ll_insert(linkedlist *ll, void *payload) {
  linkedlistnode *lln;
  lln = linkedlist_makepaynode(payload);
  linkedlist_insertfirst(ll, lln);
  return lln;
}
