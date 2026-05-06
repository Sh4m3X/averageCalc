#include <list.h>
#include <stdlib.h>

void append_list(ELEM ** phead, USER * new_user){
  ELEM* new_elem = calloc(1, sizeof(ELEM));
  if (new_elem == NULL) {
    printf("Error occurred: impossible to instantiate memory\n");
    exit(1);
  }

  new_elem->data = new_user;
  new_elem->next = NULL;
  if(*phead==NULL){
     *phead = new_elem;
     return;
  }
  ELEM* current = *phead;
  while(current->next != NULL){
    current = current->next;
  }
  current->next = new_elem;
  return;
}






