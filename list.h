#ifndef LIST_H
#define LIST_H

typedef struct Persona{
  char name[50];
  char surname[50];
  int N;
  int D;
} USER;


typedef struct Elem {
  USER * data;
  struct Elem * next;
} ELEM;

void append_list(ELEM ** head, USER * new_user);



#endif
