#include <stdio.h>
#include <stdlib.h>
#include <list.h>

float weighted_average(ELEM * current){
  int sum_votes = 0;
  int sum_credits = 0;
  USER * info = current->data;
  for(int i = 0; i<info.num_votes-1; i++){
    if(info->votes[i]>30){
      sum_votes += 30*info->credits[i];
      sum_credits += info->credits[i];
    }else{
      sum_votes += info->votes[i]*(info->credits[i]);
      sum_credits += info->credits[i];
    }
  }
  
  return sum_votes/sum_credits;
}

float arithmetic_average(ELEM * current){
  int sum_votes = 0;
  USER * info = current->data;
  for(int i = 0; i<info.num_votes-1; i++){
    if(info->votes[i]>30){
      sum_votes += 30;
    }else{
      sum_votes += info->votes[i];
    }
  }
  
  return sum_votes/info.num_votes;
}

float institute_average(ELEM * current){
  int sum_votes = 0;
  int sum_credits = 0;
  USER * info = current->data;
  for(int i = 0; i<info.num_votes-1; i++){
    sum_votes += info->votes[i]* (info->credits[i]);
    sum_credits += info->credits[i];
  }
  
  return sum_votes/sum_credits;
}

void print_database(ELEM * head){
  ELEM * current = head;
  if(head==NULL){
    printf("No records in the database\n");
    return;
  }
  int c = 0;
  USER * info = current->data;
  while(current!=NULL){
    c++;
    printf("[ELEMENT %d]\n", c);
    printf("Name: %s\n", info->name);
    printf("Surname: %s\n", info->surname);
    printf("Votes-Credits: ");
    int i=0;
    while(i<info.num_votes-1 && info->votes[i]!=0){
      printf("[%d, %d] ", info->votes[i], info->credits[i]);
    }
    printf("Weighted average: %.2f\n", weighted_average(current)); 
    printf("Arithmetic average: %.2f\n", arithmetic_average(current)); 
    printf("Institute average: %.2f\n\n", Institute_average(current));
    current = current->next;
    info = current->data;
  }
  return;
}




