#include "node.h"

extern void serialise_task_node(node *task_node, char *tasks_dir);
extern const int get_imp(FILE *fp);
extern const int get_urg(FILE *fp);
extern void get_hash(FILE *fp, char *hash);
extern void get_task(FILE *fp, char *task);

// I shouldn't have to deal with any file stuff
// I should only deal with task_nodes
// Instead of passing todo_dir, pass the head node in the HEAD file
// Serialise and deserialise internally but always return a task_node

// Path the .todo dir everywhere (malloc)
// Get the tasks dir by appending when needed

// Use of hash shouldn't be exposed with the API

// EXPOSED TO API
/* Takes the file path to the .todo directory and polls the HEAD file 
   If empty, then the linked list is empty */
extern bool is_empty(const char *todo_dir);

// EXPOSED TO API
/* Returns the file name for the given index, where 0 represents the 
   first task whose hash is stored in the HEAD file */
// Used when task is deleted or completed, fetch previous index and use that 
// for performing the steps required
extern const char *get_task_file(int index, const char *todo_dir);

// NEED NOT BE EXPOSED TO API - Just HELPER - Remove from .h later 
/* Get the path to the next task */
// Return NULL if there isn't a next file
extern const char *get_next_file(const char *task_file, const char *todo_dir);

// Making Implementation of insert_task generic so that can work on other nodes */
extern const char *insert_node(void *task_node);






