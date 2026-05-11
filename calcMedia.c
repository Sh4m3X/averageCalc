#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "utils.h"
#include "calculation.h"
#include "storage.h"


/*  OTHER USER INTERACTION FUNCTION  */
int ui_load(ELEM **phead){
  int c = load_database(phead); 
  if(c==1){
    printf("Error occurred while loading database\n");
    return 1;
  }else if(c==-1){
    printf("Unfortunately without that file i must interrupt the execution. bye bye\n");
    return 1;
  }
  return 0;
}

void ui_write_file(ELEM *head){
  int c = write_file(head);
  if(c==-1) printf("Impossible to write in the file.\n");
  else if(c == 0) printf("no user saved in the database\n");
  else printf("%d user saved in the database\n", c);
  return;
}

/* DATABASE ASK  */
int ask_user_to_create_database(){
  printf("Hi user this software need the creation of a file called \"database.bin\" to store information for further execution.\n"
    "If your are reading this could be for two reason, it's the first time you are executing the software, or the file created previously has not been found from the software.\n"
    "If it is the first case i want to know if you agree with the creation of the file.\nType (Y/N): ");
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

/*  FIRST OPTION  */

void print_user(USER * user, int c){
  printf("[ELEMENT %d]\n", c);
  printf("Name: %s\n", user->name);
  printf("Surname: %s\n", user->surname);
  printf("Votes-Credits: ");
  int i=0;
  while(i<user->num_votes && user->votes[i]!=0){
    printf("[%d, %d] ", user->votes[i], user->credits[i]);
    i++;
  }
  printf("Weighted average: %.2f\n", weighted_average(user->votes, user->credits, user->num_votes)); 
  printf("Arithmetic average: %.2f\n", arithmetic_average(user->votes, user->credits, user->num_votes)); 
  printf("Institute average: %.2f\n\n", institute_average(user->votes, user->credits, user->num_votes));
  printf("Note: if some value is 0 something has gone bad\n");
  return;
}



/*  SECOND OPTION (ADD A PERSON)  */
void ask_name(USER *new_user){
  int valid;
  do{
    printf("\n\nInsert the name (max 49 char): ");
    get_string(new_user->name, sizeof(new_user->name));

    valid = only_letters(new_user->name);
    if(!valid){
      printf("Only letters allowed.\n");
    }
  }while(!valid);
  return;
}

void read_user_data(USER *new_user){
  ask_name(new_user);



  
}


int handle_add_element(ELEM **phead){
  USER * new_user = calloc(1, sizeof(USER));
  if(new_user == NULL){
    return 1;
  }
  read_user_data(new_user);
  append_list(phead, new_user);
  return 0;
}



/* USER SWITCH BLOCK */
void user_interaction(ELEM**phead){
  printf("Hi dear user, this code is meant to store informations about your marks and the one of your friends," 
          "also it allows you to calculate of some specific means, or to do some hypotetical calculation.\n"
          "That said choose what you want to do:\n");
  while(true){
    printf("0 exit\n1 show database\n2 add a person\n3 remove a person\n4 update an entry\n5 calculation mode\nInsert the number: ");
    char c = (char)read_char();
    switch(c){
      case '0':
        printf("bye bye\n");
	      return;
      case '1':
        traverse_database(*phead);
        break;
      case '2':
        if(handle_add_element(phead)){
          printf("Something has gone wrong.\n"); 
        };    
        break;
      default:
        printf("Choice didn't recognized\n");    
    }
  }
}



/*  MAIN  */
int main(){
  ELEM * head = NULL;
  if(ui_load(&head)) exit(1);

  user_interaction(&head); 

  //implement write anddeallocate
  
  ui_write_file(head);

  deallocate(&head);
  return 0;
}

