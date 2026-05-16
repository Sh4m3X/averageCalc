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
  else if(c == 0) printf("No user saved in the database\n");
  else printf("%d user saved in the database\n", c);
  return;
}

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
  printf("\n");
  printf("Weighted average: %.2f\n", weighted_average(user->votes, user->credits, user->num_votes)); 
  printf("Arithmetic average: %.2f\n", arithmetic_average(user->votes, user->credits, user->num_votes)); 
  printf("Institute average: %.2f\n\n", institute_average(user->votes, user->credits, user->num_votes));
  printf("Note: if some value is 0 moybe something has gone bad\n");
  return;
}



/*  SECOND OPTION (ADD A PERSON)  */
void read_user_data(USER **pnew_user){
  printf("\nWhenever you can type \"c\" to interupt the data gathering\n");
 
  USER * new_user = *pnew_user;
  ask_string(new_user->name, MAX_STR_LEN, "name");
  if(empty_str(new_user->name)){
    deallocate_pers(pnew_user);
    return;
  }

  ask_string(new_user->surname, MAX_STR_LEN, "surname");
  if(empty_str(new_user->surname)){
    deallocate_pers(pnew_user);
    return;
  }

  ask_num_elements(&(new_user->num_votes), "votes");
  if(new_user->num_votes == -1){
    deallocate_pers(pnew_user);
    return;
  }
  if(new_user->num_votes == 0){
    return;
  }
  if(!ask_pair_values(new_user->num_votes, new_user->votes, new_user->credits, "votes", "credits")){
    deallocate_pers(pnew_user);
    return;
  }
  return;
}


int handle_add_element(ELEM **phead){
  USER * new_user = calloc(1, sizeof(USER));
  if(new_user == NULL){
    return 1;
  }
  read_user_data(&new_user);
  
  if(new_user!=NULL){
    append_list(phead, new_user);
  }
  return 0;
}

/*  THIRD OPTION (REMOVE A PERSON)  */
void handle_remove_element(ELEM**phead){
  int size = MAX_STR_LEN;
  char name[size];
  char surname[size];

  printf("\nTo remove a person follow the instruction\n");
  printf("Type c whenever you want to interrupt the action\n");
  ask_string(name, size, "name");
  if(empty_str(name)) return;
  ask_string(surname, size, "surname");
  if(empty_str(surname)) return;
  remove_person(phead, name, surname, size);
  return;
}
 

/* FOURTH OPTION (UPDATE AN ENTRY) */
void ask_votes(USER * person){
  int new_votes_num;
  ask_num_elements(&new_votes_num, "votes");
  if(new_votes_num == -1 || new_votes_num == 0){
    return;
  }
  if(person->num_votes + new_votes_num >= MAX_NUM_VOTES){
    printf("You exceeded the limit of votes %d\n", MAX_NUM_VOTES);
    return;
  }
  int new_votes[new_votes_num];
  int new_credits[new_votes_num];
  if(!ask_pair_values(new_votes_num, new_votes, new_credits, "votes", "credits")){
    return;
  }
  int i;
  for(i = 0; i<new_votes_num; i++){
    person->votes[person->num_votes+i] = new_votes[i];
    person->credits[person->num_votes+i] = new_credits[i];
  }
  person->num_votes = person->num_votes + new_votes_num;
  return;
}

void modify_options(USER *person){
  while(true){
    printf("\nWhat do you want to change about %s %s:\n", person->name, person->surname);
    printf("0 nothing more\n"
           "1 name\n"
           "2 surename\n"
           "3 add votes\n"
           "4 remove vote\n"
           "5 modify a vote\n"
           "Insert the number: ");
    char c = (char)read_char();
    switch(c){
      case '0':
        printf("\n");
        print_user(person, 1);            
	return;
      case '1':
        change_string(person->name, "name");
        break;
      case '2':
        change_string(person->surname, "surname");
        break;
      case '3':
        ask_votes(person);
        break;
      default:
        printf("\nChoice didn't recognized\n");    
    } 
  }
}

void update_entry(ELEM *head){
  if(head == NULL){
    printf("\nNo user to be modified\n");
    return;
  }
  int size = MAX_STR_LEN;
  char name[size];
  char surname[size];
  ELEM * person;
  printf("\nType c whenever you want to interrupt the action\n"); 
  printf("Choose the person to modify\n");
  ask_string(name, size, "name");
  if(empty_str(name)) return;
  ask_string(surname, size, "surname");
  if(empty_str(surname)) return;
  person = retrive(head, name, surname);
  if(person!=NULL){
    modify_options(person->data);
  }
  return;
}


/* USER SWITCH BLOCK */
void user_interaction(ELEM**phead){

  printf("Hi dear user, this code is meant to store informations about your marks and the one of your friends," 
          "also it allows you to calculate of some specific means, or to do some hypotetical calculation.\n"
          "That said choose what you want to do:\n");
  while(true){
    printf("0 exit\n"
           "1 show database\n"
           "2 add a person\n"
           "3 remove a person\n"
           "4 update an entry\n"
           "5 calculation mode\n"
           "Insert the number: ");
    char c = (char)read_char();
    switch(c){
      case '0':
        printf("\nbye bye\n");
	return;
      case '1':
        traverse_database(*phead);
        break;
      case '2':
        if(handle_add_element(phead)){
          printf("Something has gone wrong.\n"); 
        };    
        break;
      case '3':
        handle_remove_element(phead);
        break;
      case '4':
        update_entry(*phead);
        break;
      default:
        printf("\nChoice didn't recognized\n");    
    }
    printf("\n");
  }
}



/*  MAIN  */
int main(){
  ELEM * head = NULL;
  printf("[INITIALIZATION]\n"); 
  if(ui_load(&head)) exit(1);
  printf("[INITIALIZATION TERMINATED]\n\n");
  
  user_interaction(&head); 

  printf("\n[TERMINATION]\n"); 
  ui_write_file(head);
  deallocate_list(&head);
  printf("[TERMINATION TERMINATED]\n");
  return 0;
}

