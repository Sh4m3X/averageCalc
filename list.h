#ifndef LIST_H
#define LIST_H

typedef struct Persona{
  char name[50];
  char surname[50];
  int votes[50];
  int credits[50];
  int num_votes;
} USER;

typedef struct Elem {
  USER * data;
  struct Elem * next;
} ELEM;

int append_list(ELEM ** phead, USER * new_user);
void traverse_database(ELEM * head);
void remove_person(ELEM **phead, char *name, char *surname, int size);
void deallocate_list(ELEM** phead);
void deallocate_pers(USER **new_user);
ELEM * retrive(ELEM *head, char *name, char *surname);

#endif

#define MAX_STR_LEN 50
#define MIN_NUM_VOTES 0
#define MAX_NUM_VOTES 50
#define MIN_VALUE_VOTE 16
#define MAX_VALUE_VOTE 31
#define MIN_CREDIT_VAL 0
#define MAX_CREDIT_VAL 21

