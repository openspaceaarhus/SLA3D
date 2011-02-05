#include "event_queue.h"
#include "structs.h"
#include "datastructures/red_black_tree.h"


#include <math.h>
#include <assert.h>


/* Queue functions */
int Q_Compare(const void* a, const void* b) {
  ev_point *e1, *e2;
  e1 = ((ev_point*) a);
  e2 = ((ev_point*) b);

  /* no EPISILON as we only need to be sure that we insert the same face, before we remove it */  
  if (e1->height < e2->height)
    return -1;

  if (e1->height == e2->height) {
    if (e1->type == EV_START)
      return -1;
    return 0;
  }
  return 1;
  
}
void Q_DestroyKey (void* a) {
  free( (ev_point*) a)  ;
}
void Q_DestroyInfo(void* a) {
  ;
}
void Q_PrintKey(const void* a) {
  ;
}
void Q_PrintInfo(void* a) {
  ;
}




event_queue *make_event_queue() {
  event_queue *eq;
  eq = (event_queue*) SafeMalloc(sizeof(event_queue));
  eq->Q = RBTreeCreate(Q_Compare, Q_DestroyKey, Q_DestroyInfo, Q_PrintKey, Q_PrintInfo);
  eq->cur = NULL;
  return eq;
}

/* What is the next point ? */
ev_point *ev_peek(event_queue *eq) {
  return (ev_point*)eq->cur->key;

}
/* pop / deleteMin */
void ev_pop(event_queue *eq) {
  eq->cur = TreeSuccessor(eq->Q, eq->cur);
/*   assert(eq->cur == eq->Q->nil && ev_peek(eq) == NULL); */
}

void ev_insert(event_queue *eq, ev_point *e) {
  RBTreeInsert(eq->Q, e, NULL);
}


/* Should initialize cur to the start value */
void ev_start_iterator(event_queue *eq) {
  eq->cur = RBFindMin(eq->Q);
}

