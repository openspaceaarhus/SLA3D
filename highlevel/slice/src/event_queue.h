#ifndef EVENT_QUEUE_H_
#define EVENT_QUEUE_H_
#include "structs.h"

/* Stores a iterator in cur and uses TreeSuccessor to iterate through the tree
 with peek and pop
*/

/* Queue functions */
int Q_Compare(const void* a, const void* b); 
void Q_DestroyKey (void* a);
void Q_DestroyInfo(void* a);
void Q_PrintKey(const void* a);
void Q_PrintInfo(void* a);


event_queue *make_event_queue();

void ev_start_iterator(event_queue *eq);

/* What is the next point? */
ev_point *ev_peek(event_queue *);
/* next */
void ev_pop(event_queue *);

void ev_insert(event_queue *Q, ev_point *e);

#endif /* !EVENT_QUEUE_H_ */
