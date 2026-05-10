#ifndef LIST_H
#define LIST_H

typedef struct Persona{
  char name[50];
  char surname[50];
  int votes[20];
  int credits[20];
  int num_votes;
} USER;

typedef struct Elem {
  USER * data;
  struct Elem * next;
} ELEM;

int append_list(ELEM ** phead, USER * new_user);
void traverse_database(ELEM * head);
void deallocate(ELEM** phead);




#endif
