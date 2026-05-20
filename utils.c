#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "list.h"

int c_char(char *buff){
  return buff[0] == 'c' && buff[1] == '\0';
}

void flush_stdin(){
  int discard;
  while ((discard = getchar()) != '\n' && discard != EOF);
  return;
}

int read_char(){
  int c = getchar();
  flush_stdin();
  return c;
}

int ask_yes_or_no(){
  while(true){
    char c = (char)read_char();
    if(c=='Y'){
      return 1;
    }else if(c=='N'){
      return 0;
    }
    printf("\nYou should be precise (Y/N): ");
  }
}

int only_letters(char *str){
  for(int i = 0; str[i]!='\0'; i++){
    if(!isalpha((unsigned char)str[i])) return 0;
  }
  return 1;
}

void get_string(char *str, size_t size){
  if(fgets(str, size, stdin)!=NULL){
    char *newline = strchr(str, '\n');
    if(newline != NULL){
       *newline = '\0';
    }else{
      flush_stdin();
    }
  }
  return;
}

int empty_str(char *str){
  return str[0] == '\n' || str[0] == '\0';
}

void ask_string(char * new_str, int size, char * str){
  int valid;
  char buff[size];
  do{
    valid = 1;
    printf("Insert the %s (max %d char): ", str, size);
    get_string(buff, size);
    
    if(!only_letters(buff)){
      printf("Only letters allowed.\n");
      valid = 0;
    }else if(empty_str(buff)){
      printf("The string can't be empty\n");
      valid = 0;
    }
  }while(!valid);
  if(!c_char(buff)){
    int i = 0;
    for(i = 0; buff[i]!='\0'; i++){
      new_str[i] = buff[i];
    }
    new_str[i] = '\0';
  }else{
    new_str[0] = '\0';
  }
  return;
}

int only_digits(char *str){
  for(int i = 0; str[i]!='\0'; i++){
    if( str[i] < 48 || str[1]>57) return 0;
  }
  return 1;
 
}

int str_convertable_to_int(char *buff, long *pvotes){
  long votes;
  char *endptr;
  errno = 0;
  
  votes = strtol(buff, &endptr, 10);
  if(endptr == buff){
    printf("Must contain only numbers!\n");
    return 0;
  }

  if(*endptr != '\0'){
    printf("Invalid characters detected!\n");
    return 0;
  }

  if(errno == ERANGE){
    printf("Number is too large!\n");
    return 0;
  }

  *pvotes = (int)votes;
  return 1;
}

int convert_to_int(int *c, char *num, int min, int max){  
  long number = 0;

  if(empty_str(num)){
    printf("Must insert a number\n");
    return 0;
  }
   
  if(c_char(num)){
    *c = -1;
    return 1;
  }
  
 
  if(!str_convertable_to_int(num, &number)){
    return 0;
  }

  if(number < min || number > max){
    printf("Must be %d <= x <= %d!\n", min, max);
    return 0;
  }

  *c = (int)number;
  return 1;
}

int get_num(int *c, char *str){
  char buff[128];
  get_string(buff, sizeof(buff));
  return convert_to_int(c, buff, MIN_NUM_VOTES, MAX_NUM_VOTES);
}

void split_string(char * buff, int size, char* str1, char* str2){
  int i = 0;
  int j = 0;
  while(i<size && buff[i]!='-' && buff[i]!='\0'){
    str1[i] = buff[i];
    i++;
  }
  if(buff[i] == '-'){
    str1[i] = '\0';
    i++;
  }

  while(i<size && buff[i]!='\0'){
    str2[j] = buff[i];
    i++;
    j++;
  } 
  str2[j] = '\0';
}


int get_two_values(char *buff, int *val1, int *val2, char* name_val_1, char* name_val_2){
  char str1[128];
  char str2[128];
  split_string(buff, sizeof(buff), str1, str2);
  if(!convert_to_int(val1, str1, MIN_VALUE_VOTE, MAX_VALUE_VOTE) 
     || !convert_to_int(val2, str2, MIN_CREDIT_VAL, MAX_CREDIT_VAL)){
    printf("FORMAT MUST BE: %s-%s\nRANGE %s MUST BE: from %d to %d\n", 
            name_val_1, name_val_2, name_val_1, MIN_VALUE_VOTE, MAX_VALUE_VOTE);
    printf("FORMAT MUST BE: %s-%s\nRANGE %s MUST BE: from %d to %d\n", 
            name_val_1, name_val_2, name_val_2, MIN_CREDIT_VAL, MAX_CREDIT_VAL);
 
    return 0;
  }
  return 1;
}


int ask_pair_values(int num_votes, int *votes, int *credits, char *name_val_1, char *name_val_2){
  char buff[128];
  int vote;
  int credit;
  printf("Insert %d pair of %s-%s one at the time (range of votes: %d to %d):\n", 
          num_votes, name_val_1, name_val_2, MIN_VALUE_VOTE, MAX_VALUE_VOTE);
  for(int i = 0; i<num_votes; i++){
    do{
      printf("%d) ", i+1);
      get_string(buff, sizeof(buff));
    }while(!c_char(buff) && !get_two_values(buff, &vote, &credit, name_val_1, name_val_2));
    if(!c_char(buff)){
      votes[i] = vote;
      credits[i] = credit;
    }else{
      return 0;
    }
  }
  return 1;
}

int is_right_person(USER *data, char *name, char *surname){
  return (strcmp(data->name, name)==0 && strcmp(data->surname, surname)==0);
}

void change_string(char *str, char *request){
  int size = MAX_STR_LEN;
  char name[size];
  ask_string(name, size, request);
  if(empty_str(name)) return;
  else{
    int i;
    for(i = 0; name[i]!='\0'; i++){
      str[i] = name[i];
    }      
    for(; str[i]!='\0'; i++){
      str[i] = '\0';
    }      
  } 
  return;
      
}

void clear_array(int * arr, int size){
  for(int i=0; i<size; i++){
     arr[i] = 0;
  }
  return;
}

int get_index_of_pair(int *arr1, int *arr2, int v, int c){
  int i;
  for(i = 0; i<MAX_NUM_VOTES; i++){
    if(arr1[i] == v && arr2[i] == c){
      return i;
    }
  }
  return -1;
}

void remove_elem_from_array(int * arr, int i){
  int j = i;
  while(j<MAX_NUM_VOTES-1){
    arr[j] = arr[j+1];
    j++;
  }
  return;
}


void remove_pair(int *arr1, int *arr2, int *to_remove_1, int *to_remove_2, int size){
  int j;
  int i;
  for(j = 0; j<size; j++){
    i = get_index_of_pair(arr1, arr2, to_remove_1[j], to_remove_2[j]);   
    if(i!=-1){
      remove_elem_from_array(arr1, i);
      remove_elem_from_array(arr2, i);
    }else{
      printf("Pair %d-%d not found\n", to_remove_1[j], to_remove_2[j]);
    }
  } 
}

int edit_elem_pair(int *arr1, int *arr2, int i){
  char buff[128];
  int new_vote;
  int new_credit;
  do{
    get_string(buff, sizeof(buff));
  }while(!c_char(buff) && !get_two_values(buff, &new_vote, &new_credit, "vote", "credit"));
  if(!c_char(buff)){ 
    arr1[i] = new_vote;
    arr2[i] = new_credit;
    return 1;
  }
  return 0;
}

void edit_pair(int *arr1, int *arr2, int *to_edit_1, int *to_edit_2, int size){  
  int j;
  int i;
  for(j = 0; j<size; j++){
    i = get_index_of_pair(arr1, arr2, to_edit_1[j], to_edit_2[j]);   
    if(i!=-1){
      printf("Edit the pair %d-%d: ", to_edit_1[j], to_edit_2[j]);
      edit_elem_pair(arr1, arr2, i);
    }else{
      printf("Pair %d-%d not found\n", to_edit_1[j], to_edit_2[j]);
    }
  } 

}

void concat_array(int * arr1, int elems1, int *arr2, int elems2, int maxElems){
  int i = 0;
  while( i<elems2 ){
    arr1[i+elems1] = arr2[i];
    i++;
  }
  return;
}

