#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

// Return true if node is NULL
bool is_null(node *task_node) { 
	return task_node == NULL;
}

// Return a pointer to a node created by the given arguments
node *create_node(char *task, int importance, int urgency) {
  node *task_node = malloc(sizeof(node));
  task_node->task = strdup(task);
  task_node->importance = importance;
  task_node->urgency = urgency;
  task_node->next = NULL;
  return task_node;
}

// Print node in a human-readable form
void print_node(node *task_node) {
  // Make a header row first
  printf("%s\n", task_node->task);
}

// Free the node's memory
void free_node(node *task_node) {
  free(task_node->task);
  free(task_node);
}
