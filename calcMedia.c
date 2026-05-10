#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "utils.h"


/*  OTHER USER INTERACTION FUNCTION  */
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
  print("Note: if some value i 0 something has gone bad\n");
  return;
}

void ui_load(ELEM **phead){
  int c = load_database(phead); 
  if(c==1){
    printf("Error occurred while loading database\n");
    return 1;
  }else if(c==-1){
    printf("Unfortunately without that file i must interrupt the execution. bye bye\n");
    return 0;
  }
  return;
}

void ui_write_file(ELEM *head){
  int c = write_file(head);
  if(c==-1) printf("Impossible to write in the file.\n");
  else if(c == 0) printf("no user saved in the database\n");
  else printf("%d user saved in the database\n", c);
  return;
}



//USER INTERACTION
void user_interaction(ELEM**head){
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
        traverse_database(*head);
        break;
      default:
        printf("Choice didn't recognized\n");    
    }
  }
}


int main(){
  ELEM * head = NULL;
  ui_load(&head);

  user_interaction(&head); 

  //implement write anddeallocate
  
  ui_write_file(head);

  deallocate(&head);
  return 0;
}



