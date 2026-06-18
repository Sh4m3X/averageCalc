#ifndef STORAGE_H
#define STORAGE_H
#include "list.h"

int ask_user_to_create_database();
void print_user(USER * user, int c);
int ui_load(ELEM **phead);
void ui_write_file(ELEM *head);
void ask_num_elements_to_add(USER * pers, int *c, char *str);
void ask_num_elements_to_remove(USER * pers, int *c, char *str);
void ask_num_elements_to_edit(USER * person, int *c, char * str);
void ask_string(char *new_str, int size, char * str);
void read_user_data(USER **new_user);
int handle_add_element(ELEM **phead);
void handle_remove_element(ELEM**phead);
void ask_votes_add(USER * person);
void handle_remove(USER * pers, int * removed_votes, int * removed_credits, int size);
void handle_edit(USER * pers, int * edited_votes, int * edited_credits, int size);
void ask_votes_remove(USER * person);
void modify_options(USER *person);
void update_entry(ELEM *head);
void new_mean_estimator(USER * pers);
void calculation_options(ELEM * head);
void user_interaction(ELEM**phead);
int main();

#endif
