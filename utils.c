#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

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
