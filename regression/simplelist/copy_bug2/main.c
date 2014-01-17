#include "../heap_builtins.h"

/* copy */

/* expect bottom */

struct list {
  struct list* value;
  struct list* next;
};

typedef struct list* list_t;

void main() {
  list_t x, y;
  list_t tmpx, tmpy, cell;
  list_t res, err;
 
  __CPROVER_assume(res!=err);

  if (x == NULL) {
    y = NULL;
    return;
  }

  y = (list_t)malloc(sizeof(struct list));
  if(y == NULL) res=err;
  y->next = NULL;
  if(x == NULL) res=err;
  y->value = x->value;
  if(x == NULL) res=err;
  tmpx = x->next;
  tmpy = y;

  while(tmpx != NULL) {
    cell = (list_t)malloc(sizeof(struct list));
    if(cell == NULL) res=err;
    if(tmpx == NULL) res=err;
    cell->value = tmpx->value;
    if(tmpy == NULL) res=err;
    tmpy->next = cell;
    cell->next = NULL; // BUG: line added
    tmpy = cell->next; //->next added (found with 2 unwindings)
    if(tmpx == NULL) res=err;
    tmpx = tmpx->next; 
  }

  if(tmpy == NULL) res=err;
  tmpy->next = NULL;

  assert(res!=err);
  assert(__CPROVER_HEAP_path(y, NULL, "next"));
}



