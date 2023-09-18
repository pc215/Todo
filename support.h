#include "node.h"

extern void serialise_task_node(node *task_node, char *file_name);
extern void deserialise_task_node(char *file_name, node *task_node);
extern void deserialise_next(char *file_name, node *task_node); 
