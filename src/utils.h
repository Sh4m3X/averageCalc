#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>


int ask_yes_or_no();
int c_char(char *buff);
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
int get_num(int *c, char *str); 
void split_string(char * buff, int size, char *str1, char *str2);
int get_two_values(char *buff, int *val1, int *val2, char *name_val_1, char *name_val_2);
int ask_pair_values(int num_votes, int *votes, int *credits, char *name_val_1, char *name_val_2);
int is_right_person(USER *data, char *name, char *surname); 
void change_string(char *str, char *request);
void clear_array(int * arr, int size);
int get_index_of_pair(int *arr1, int *arr2, int v, int c);
void remove_elem_from_array(int * arr, int i);
void remove_pair(int *arr1, int *arr2, int *to_remove1, int *to_remove_2, int size);
int edit_elem_pair(int *arr1, int *arr2, int i);
void edit_pair(int *arr1, int *arr2, int *to_edit_1, int *to_edit_2, int size);
void concat_array(int * arr1, int elems1, int *arr2, int elems2, int maxElems);



#endif
