#ifndef STORAGE_H
#define STORAGE_H

#include "list.h"

int read_elem_from_file(ELEM **phead, void * file);
void * create_file();
int load_database(ELEM **phead);
int write_elem_on_file(ELEM *head, void * file);
int write_file(ELEM *head);

#endif

#define DATABASE_FILE "database.bin"


