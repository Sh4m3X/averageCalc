#include <stdio.h>
#include <stdlib.h>
#include <list.h>



/*
 
  char buffer[100];
  FILE* file = fopen("./database.bin", "r+");
  fread(buffer, sizeof(char), 100, file);
  printf("%s\n", buffer);
  fwrite("abcde\0", 5*sizeof(char), 1, file);
  fclose(file);
  return 0;

*/

void read_elem_from_file(ELEM** head, FILE * file){
  USER buff;
  int counter = 0;
 
  while(fread(&buff, sizeof(USER), 1, file)==1){
    USER * new_user = calloc(1, sizeof(USER));
    if(new_user == NULL){
      printf("Error occurred: cannot instantiate new user\n");
      exit(1);
    }
    *new_user = buff;
    append_list(head, new_user);
    counter++;
  }
  if(counter == 0) printf("no user found in the database\n");
  else printf("%d user was found in database and loaded into memory\n", counter);
  return;
}

void read_file(ELEM**head){
  FILE* file = fopen("./database.bin", "r+");
  if (file == NULL){
    file = fopen("./database.bin", "w+");
    if(file==NULL){
      printf("Error occurred: cannot create a file\n");
      exit(1);
    }
    printf("Created a file called database.bin\neven if it is not a real database :)\n");
  }
  
  read_elem_from_file(head, file);

  fclose(file);
  return;
}





int main(){
  ELEM * head = NULL;
  read_file(&head);
  printf("file readed succesfully\n");

}



