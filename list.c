#include "list.h"
#include "utils.h"
#include "calcMedia.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
  printf("\n");
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

void remove_person(ELEM**phead, char *name, char *surname, int size){
  ELEM * head = *phead;
  if(head == NULL){
    printf("Database empty\n");
    return;
  }
  
  if(is_right_person(head->data, name, surname)){    
    *phead = (*phead)->next;
    free(head->data);
    free(head);
    printf("%s %s removed from database\n");
  }else{
    ELEM * current = head;
    while(current->next!=NULL && !is_right_person(current->next->data, name, surname)){
      current = current->next;
    }
    if(current->next!=NULL){
      ELEM * support = current->next;
      current->next = support->next;
      free(support->data);
      free(support);
      printf("%s %s removed from database\n");
    }else{
      printf("Person not found in the database\n");
    }
  }
  return;
}

void deallocate_pers(USER **new_user){  
  free(*new_user);
  *new_user = NULL;
  return;
}



void deallocate_list(ELEM** phead){
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

ELEM * retrive(ELEM *head, char *name, char *surname){
  ELEM * preturn = NULL;
  ELEM * current = head;
  if(head == NULL){
    printf("Database empty\n");
  }else{
    if(is_right_person(head->data, name, surname)){    
      preturn = head; 
    }else{
      while(current!=NULL && !is_right_person(current->data, name, surname)){
        current = current->next;
      }
      if(current!=NULL){
        preturn = current;
      }else{
        printf("Person not found in the database\n");
      }
    }
  }
  return preturn;
}





