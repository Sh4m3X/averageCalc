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

//READING FROM FILE

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
    char c;
    printf("Hi user this software need the creation of a file called \"database.bin\" to store information for further execution.\n If your are reading this could be for two reason, it's the first time you are executing the software, or the file created previously has not been find from the software.\n If it is the first case i want to know if you agree with the creation of the file.\n Type (Y/N): ")
    c = getchar();
    getchar();
    while(true){
      if(c=="Y"){
        file = fopen("./database.bin", "w+");
        if(file==NULL){
          printf("Error occurred: cannot create a database file\n");
          exit(1);
        }
        printf("Created a file called database.bin\neven if it is not a real database :)\n");
        return;
      }else if(c=="N"){
        printf("Unfortunately without that file i must interrupt the execution. bye bye\n");
        exit(1);
      }
      print("\nYou should be precise (Y/N): ");
    }
  }
  
  read_elem_from_file(head, file);

  fclose(file);
  printf("file readed succesfully\n"); 
  return;
}

//USER INTERACTION
void user_interaction(ELEM**head){
  int choice = -1;
  while(choice!=0){
    printf("Hi dear user this software is meant to use a file as a database, you can manage it with the following options. The idea is that for each person you can store the information about the their exams votes, then you can ask for the calculation of some specific means, or to do some hypotetical calculation.\n I'm building this beacuse i think often how some marks can influece my mean, and every time i has to do such huge calculation that is just boring.\nThat said choose what you want to do:\n"
    printf("0 exit\n
	    1 show database\n
	    2 add a person\n
	    3 remove a person\n
	    4 update an entry\n
	    5 calculation mode\n
	    Insert the number: ");
    scanf("%d", &choice);
    switch(choice){
      case 1:
        printf("bye bye\n");
	return;
      default:
        print("Choice didn't recognized\n");    
    }

  }
}


int main(){
  ELEM * head = NULL;
  read_file(&head);
  user_interaction(&head); 

}



