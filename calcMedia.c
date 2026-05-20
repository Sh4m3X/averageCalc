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
  return ask_yes_or_no();
}

void ask_num_elements_to_add(USER * pers, int *c, char *str){
  char buff[128];
  do{ 
    printf("Insert the number of %s you want to insert (max %d): ", str, MAX_NUM_VOTES-pers->num_votes);
  }while(!get_num(c, str));
}

void ask_num_elements_to_remove(USER * pers, int *c, char *str){
  char buff[128];
  do{ 
    printf("Insert the number of %s you want to remove (max %d): ", str, pers->num_votes);
  }while(!get_num(c, str));
}

void ask_num_elements_to_edit(USER * person, int *c, char * str){
  char buff[128];
  do{ 
    printf("Insert the number of %s you want to edit (max %d): ", str, person->num_votes);
  }while(!get_num(c, str));
}

void ask_num_hp_elements(USER *person, int * c, char * str){
  char buff[128];
  do{ 
    printf("Insert the number of hypotetical %s (max %d): ", str, MAX_NUM_VOTES-person->num_votes);
  }while(!get_num(c, str));
}
 


/*  FIRST OPTION  */
void print_user(USER * user, int c){
  printf("[ELEMENT %d]\n", c);
  printf("Name: %s\n", user->name);
  printf("Surname: %s\n", user->surname);
  printf("Number of votes: %d\n", user->num_votes);
  printf("Votes-Credits: ");
  int i=0;
  while(i<user->num_votes && user->votes[i]!=0){
    printf("[%d, %d] ", user->votes[i], user->credits[i]);
    i++;
  }
  printf("\n");
  printf("Weighted average: %.2f\n", weighted_average(user->votes, user->credits, user->num_votes)); 
  printf("Arithmetic average: %.2f\n", arithmetic_average(user->votes, user->credits, user->num_votes)); 
  printf("Institute average: %.2f\n", institute_average(user->votes, user->credits, user->num_votes));
  printf("Average for final vote: %.2f\n\n", final_vote_average(institute_average(user->votes, user->credits, user->num_votes)));
 
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

  ask_num_elements_to_add(*pnew_user, &(new_user->num_votes), "votes");
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
void ask_votes_add(USER * person){
  int new_votes_num;
  ask_num_elements_to_add(person, &new_votes_num, "votes");
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


void handle_remove(USER * pers, int * removed_votes, int * removed_credits, int size){
  if(size >= pers->num_votes){
    printf("You asked to remove %d votes but there are only %d\n", 
           size, pers->num_votes);
    printf("Do you want to remove all the votes (Y/N): ");
    if(ask_yes_or_no()){
      clear_array(pers->votes, MAX_NUM_VOTES);
      clear_array(pers->credits, MAX_NUM_VOTES);
      pers->num_votes = 0;
    }
    return;
  }
  remove_pair(pers->votes, pers->credits, removed_votes, removed_credits, size);
}

void ask_votes_remove(USER * person){
  int remove_votes_num;
  int removed_votes[remove_votes_num];
  int removed_credits[remove_votes_num];
 
  ask_num_elements_to_remove(person, &remove_votes_num, "votes");
  if(remove_votes_num == -1 || remove_votes_num == 0){
    return;
  }
  if(person->num_votes > remove_votes_num){
    if(!ask_pair_values(remove_votes_num, removed_votes, removed_credits, "votes", "credits")){
      return;
    }
  }
  handle_remove(person, removed_votes, removed_credits, remove_votes_num);
}

void handle_edit(USER * pers, int * edited_votes, int * edited_credits, int size){
  if(size > pers->num_votes){
    printf("You asked to edit %d votes but there are only %d\n", 
           size, pers->num_votes);
    printf("Please try again\n");
    return;
  }
  edit_pair(pers->votes, pers->credits, edited_votes, edited_credits, size);
}

void ask_votes_to_edit(USER * person){
  int edit_votes_num;
  int edited_votes[edit_votes_num];
  int edited_credits[edit_votes_num];
  ask_num_elements_to_edit(person, &edit_votes_num, "votes");
  if(edit_votes_num == -1 || edit_votes_num == 0){
    return;
  }

  if(person->num_votes >edit_votes_num){
    if(!ask_pair_values(edit_votes_num, edited_votes, edited_credits, "votes", "credits")){
      return;
    }
  }
  handle_edit(person, edited_votes, edited_credits, edit_votes_num);
}

void modify_options(USER *person){
  USER copy = *person;
  USER * pcopy = &copy;
  while(true){
    printf("\nWhat do you want to change about %s %s:\n", person->name, person->surname);
    printf("0 nothig more\n"
           "1 name\n"
           "2 surename\n"
           "3 add votes\n"
           "4 remove votes\n"
           "5 modify a vote\n"
           "6 show changes\n"
           "Insert the number: ");
    char c = (char)read_char();
    printf("\n");
    switch(c){
      case '0':
        printf("Do you want to save changes (Y/N): ");
        if(ask_yes_or_no()){
          *person = copy; 
          printf("\nChanges applied\n\n");
        }else{
          printf("\nChanges discarded\n\n");
        }
        print_user(person, 1);  
        printf("Note: if some value is 0 maybe something has gone bad\n");  
	return;
      case '1':
        change_string(pcopy->name, "name");
        break;
      case '2':
        change_string(pcopy->surname, "surname");
        break;
      case '3':
        ask_votes_add(pcopy);
        break;
      case '4':
        ask_votes_remove(pcopy);
        break;
      case '5':
        ask_votes_to_edit(pcopy);
        break;
      case '6':
        printf("\n");
        printf("Old_version:\n ");
        print_user(person, 0);  
        printf("New_version:\n ");
        print_user(pcopy, 0);  
        printf("Note: if some value is 0 maybe something has gone bad\n");  	
        break;
      default:
        printf("Choice didn't recognized\n");    
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


/* CALCULATION MODE */
void new_mean_estimator(USER * pers){
  int hp_votes_num;
  int hp_votes[MAX_NUM_VOTES];
  clear_array(hp_votes, MAX_NUM_VOTES);
  int hp_credits[MAX_NUM_VOTES];
  clear_array(hp_credits, MAX_NUM_VOTES);
  ask_num_hp_elements(pers, &hp_votes_num, "votes");
  if(hp_votes_num == -1 || hp_votes_num == 0){
    return;
  }

  if(MAX_NUM_VOTES < pers->num_votes + hp_votes_num){
    printf("You exceeded the limit of votes %d\n", MAX_NUM_VOTES);
    return; 
  }
  if(!ask_pair_values(hp_votes_num, hp_votes, hp_credits, "votes", "credits")){
    return;
  }
  concat_array(hp_votes, hp_votes_num, pers->votes, pers->num_votes, MAX_NUM_VOTES);
  concat_array(hp_credits, hp_votes_num, pers->credits, pers->num_votes, MAX_NUM_VOTES);

  hp_votes_num = hp_votes_num + pers->num_votes;
 
  printf("\nHypotetical set of votes:\n");
  int i = 0;
  while(i<hp_votes_num && hp_votes[i]!=0){
    printf("[%d, %d] ", hp_votes[i], hp_credits[i]);
    i++;
  }
  printf("\n");
  printf("\nNew mean estimated for %s %s:\n", pers->name, pers->surname);

  printf("Weighted average: %.2f\n", weighted_average(hp_votes, hp_credits, hp_votes_num)); 
  printf("Arithmetic average: %.2f\n", arithmetic_average(hp_votes, hp_credits, hp_votes_num)); 
  printf("Institute average: %.2f\n", institute_average(hp_votes, hp_credits, hp_votes_num));
  printf("Average for final vote: %.2f\n\n", final_vote_average(institute_average(hp_votes, hp_credits, hp_votes_num)));
 
  return;
}

void calculation_options(USER * pers){
  printf("\nWelcome to calculation mode.\n");
  while(true){
    printf("Choose what to do:\n"
           "0 exit\n"
           "1 estimate new mean\n");
    char c = (char)read_char();
    printf("\n");
    switch(c){
      case '0':
        printf("Exiting from calculation mode\n");
	return;
      case '1':
        new_mean_estimator(pers);
        break;
      default:
        printf("Choice didn't recognized\n");
    }
  }
}

void calculation_mode(ELEM * head){
  if(head == NULL){
    printf("\nNo user, add someone in the database then try calculation mode\n");
    return;
  }
  int size = MAX_STR_LEN;
  char name[size];
  char surname[size];
  ELEM * person;
  printf("\nType c whenever you want to interrupt the action\n"); 
  printf("Choose the person and enter in calculation mode\n");
  ask_string(name, size, "name");
  if(empty_str(name)) return;
  ask_string(surname, size, "surname");
  if(empty_str(surname)) return;
  person = retrive(head, name, surname);
  if(person!=NULL){
    calculation_options(person->data);
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
        printf("Note: if some value is 0 maybe something has gone bad\n");
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
      case '5':
        calculation_mode(*phead);
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

