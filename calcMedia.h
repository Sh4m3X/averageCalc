#ifndef STORAGE_H
#define STORAGE_H
#include "list.h"



int ask_user_to_create_database();
void print_user(USER * user, int c);
int ui_load(ELEM **phead);
void ui_write_file(ELEM *head);
void ask_string(char *new_str, int size, char * str);
void read_user_data(USER **new_user);
int handle_add_element(ELEM **phead);
void handle_remove_element(ELEM**phead);
void ask_votes(USER * person);
void modify_options(USER *person);
void update_entry(ELEM *head);
void user_interaction(ELEM**phead);
int main();

#endif
