#ifndef LIST_H
#define LIST_H

typedef struct Persona{
  char name[50];
  char surname[50];
  float mean;
  float cfu_mean;
  float institute_mean;
  float mean_final;
} USER;


typedef struct Elem {
  USER * data;
  struct Elem * next;
} ELEM;

void append_list(ELEM ** head, USER * new_user);



#endif
