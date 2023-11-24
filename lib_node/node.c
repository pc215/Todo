#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"


/* Return a pointer to a node created by the given arguments */
node *
create_node(int imp, int urg, char *task) {
  node *task_node = calloc(1, sizeof(node));
  task_node->task = strdup(task);
  task_node->imp = imp;
  task_node->urg = urg;
  task_node->next = NULL;
  return task_node;
}

/* Query whether node is defined or not */
bool
is_null_node(node *task_node) { 
	return task_node == NULL;
}

/* Free the memory allocated for the node and the task */
void
free_node(node *task_node) {
  free(task_node->task);
  free(task_node);
}

/* Print node in a human-readable form for debugging */
void
print_node(node *task_node) {
  printf("Importance: %d\n", task_node->imp);
  printf("Urgency: %d\n", task_node->urg);
  printf("Task: %s\n", task_node->task);
}


