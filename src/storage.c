#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "calcMedia.h"
#include "storage.h"

int database_path(char * db_path, size_t size){  
  ssize_t len = readlink("/proc/self/exe", db_path, size - 1);
  if(len <  0 || (size_t)len >= size - 1){
    return 0;
  }
  db_path[len] = '\0';

  char * last_slash = strrchr(db_path, '/');
  if (!last_slash){
    return 0;  
  }  
  
  *last_slash = '\0';

  if(strlen(db_path) + strlen(DATABASE_FILE) + 2 > size)
    return 0;
  strcat(db_path, "/");
  strcat(db_path, DATABASE_FILE);
  return 1;
}


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

FILE * create_file(char * db_path){
  FILE * file;
   
  file = fopen(db_path, "wb+");
  if(file==NULL){
    return NULL;   
  }
  printf("\nFile %s created successfully :)\n\n", db_path);
  return file;
}

int load_database(ELEM **phead){
  char db_buff[1024];
  if(!database_path(db_buff, sizeof(db_buff))){
    return 1;
  }

  FILE* file = fopen(db_buff, "rb+"); 
  if (file == NULL){
    if(ask_user_to_create_database()){
      file = create_file(db_buff);
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
  char db_buff[1024];
  if(!database_path(db_buff, sizeof(db_buff))){
    return -1;
  }

  FILE* file = fopen(db_buff, "wb");
  if(file == NULL){ 
    return -1;
  }

  int written = write_elem_on_file(head, file);

  fclose(file);

  return written;
}
