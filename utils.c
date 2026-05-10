#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int read_char(){
  int c = getchar();
  int discard;
  
  while ((discard = getchar()) != '\n' && discard != EOF);
  return c;
}






