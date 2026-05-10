#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int append_list(ELEM ** phead, USER * new_user){
  ELEM* new_elem = calloc(1, sizeof(ELEM));
  if (new_elem == NULL) {
    return 1;
  }

  new_elem->data = new_user;
  new_elem->next = NULL;
  if(*phead==NULL){
     *phead = new_elem;
  }else{
    ELEM* current = *phead;
    while(current->next != NULL){
      current = current->next;
    }
    current->next = new_elem;
  }
  return 0;
}

void traverse_database(ELEM * head){ 
  if(head==NULL){
    printf("No records in the database\n");
    return;
  }
  ELEM * current = head;
  int c = 0;
  USER * info;
  while(current!=NULL){
    info = current->data;
    c++;
    print_user(info, c);
    current = current->next;
  }
  return;
}

void deallocate(ELEM** phead){
  ELEM *current = *phead;
  ELEM *next;
  while(current!=NULL){
    next = current->next;
    
    free(current->data);
    free(current);
    
    current = next;
  }
  *phead = NULL;
  return;
}




