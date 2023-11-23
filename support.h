#include "node.h"

extern void serialise_task_node(node *task_node, char *tasks_dir);
extern void print_task_node(char *hash, char *tasks_dir);
extern void deserialise_task_node(char *file_name, node *task_node);
extern void deserialise_next(char *file_name, node *task_node); 

// Path the .todo dir everywhere (malloc)
// Get the tasks dir by appending when needed

/* Takes the file path to the .todo directory and polls the HEAD file 
   If empty, then the linked list is empty */
extern bool is_empty(const char *todo_dir);

/* Returns the hash to the task with the given index, where 0 represents the 
   first task whose hash is stored in the HEAD file */
// Used when task is deleted or completed, fetch previous index and use that 
// for performing the steps required
extern const char *get_task_file(int index);

/* Get the path to the next task */
// Probably used as a helper function
// Make get_file_name function available in the API for use here
// and in other places
extern const char *get_next(const char *hash);

