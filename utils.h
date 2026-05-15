#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

void flush_stdin();
int read_char();
int only_letters(char *str);
int only_digits(char *str);
void get_string(char *str, size_t size);
void ask_num_in_range(int c, int range);
int empty_str(char *str);
void ask_string(char * new_str, int size, char * str);
int num_of_digits(int num);
int str_convertable_to_int(char *buff, int *pvotes);
int convert_to_int(int *c, char *num, int min, int max);
void ask_num_elements(int *c, char *str); 
void split_string(char * buff, int size, char *str1, char *str2);
int ger_two_values(char *buff, int *val1, int *val2, char *name_val_1, char *name_val_2);
void ask_pair_values(USER *new_user, char *name_val_1, char *name_val_2); 
int is_right_person(USER *data, char *name, char *surname); 

#endif
