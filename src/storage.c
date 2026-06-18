#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "calcMedia.h"
#include "storage.h"

int read_elem_from_file(ELEM** phead, void * file){
  USER buff;
  int counter = 0;
 
  while(fread(&buff, sizeof(USER), 1, file)==1){
    USER * new_user = calloc(1, sizeof(USER));
    if(new_user == NULL){
      return 1;
    }
    *new_user = buff;
    if(append_list(phead, new_user)) return 1;
    counter++;
  }
  if(counter == 0) printf("No user found in the database\n");
  else printf("%d users were found in database and loaded into memory\n", counter);
  return 0;
}

FILE * create_file(){
  FILE * file;
   
  file = fopen(DATABASE_FILE, "wb+");
  if(file==NULL){
    return NULL;   
  }
  printf("\nFile %s created successfully :)\n\n", DATABASE_FILE);
  return file;
}

int load_database(ELEM **phead){
  FILE* file = fopen(DATABASE_FILE, "rb+"); 
  if (file == NULL){
    if(ask_user_to_create_database()){
      file = create_file();
      if(file == NULL) return 1;
    }else{
      return -1;
    }
    return 0;
  }
  
  if(read_elem_from_file(phead, file)){
    fclose(file);
    return 1;
  }

  fclose(file);
  return 0;
}

int write_elem_on_file(ELEM *head, void * file){
  int c = 0;
  ELEM * current = head;
  while(current!=NULL){
    fwrite(current->data, sizeof(USER), 1, file);
    current = current->next;
    c++;
  }
  return c;
}

int write_file(ELEM *head){
  FILE* file = fopen(DATABASE_FILE, "wb");
  if(file == NULL){ 
    return -1;
  }

  int written = write_elem_on_file(head, file);

  fclose(file);

  return written;
}
