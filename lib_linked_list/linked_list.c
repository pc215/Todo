#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

#define HEAD_POSITON 0

/* Create a linked list */
linked_list create_linked_list(void) {
	return calloc(1, sizeof(node *));
}

/* Returns true if the list has been created */
static bool 
list_exists(linked_list list) {
	return list != NULL;
}

/* Returns true if the head is NULL */
static bool 
is_empty_list(linked_list list) {
  assert(list_exists(list));
  return is_null_node(*list);
}

/* Returns the next node in the linked list */
static node *
get_next(node *cur) {
  /* Returns NULL if the current node is NULL */ 
	return !is_null_node(cur) ? cur->next : NULL;
}

/* Set next node of a given node */
static bool 
set_next(node *cur, node *next) {
  if (is_null_node(cur)) {
    return false;
  }

  cur->next = next;
  return true;
}

/* Returns a certain node at a given position */
node *
get_node(linked_list list, int pos) {
	assert(list_exists(list) && !is_empty_list(list));

	node *cur = *list;
	while ((pos--) && !is_null_node(cur)) {
		cur= get_next(cur);
	}

	return cur;
}


/* Remove a node at a given position */
bool 
remove_node(linked_list list, int pos) {
	assert(list_exists(list));
  if (pos < HEAD_POSITON) {
    return false;
  }

 	/* The head */
  if (pos == HEAD_POSITON) {
    node *cur = *list;
    *list = get_next(cur);
    free_node(cur);
    return true;
  }

  /* The previous node must exist unless position is out of bounds */
  node *prev = get_node(list, pos - 1);
  node *cur  = get_next(prev);

  if (!is_null_node(cur)) {
    set_next(prev, get_next(cur));
    free_node(cur);
    return true;
  }

  return false;
}

bool 
insert_node(linked_list list, node *task_node, comparator node_compare) {
	assert(list_exists(list));
  /* NULL must be the maximum element */
  assert(node_compare(task_node, NULL) > 0);

  /* Invalid input but don't exit program */
  if (task_node == NULL) {
    return false;
  }

  /* Set the head node */
  if (is_empty_list(list)) {
    *list = task_node;
    return true;
  }

	node *prev = NULL;
  node *cur  = *list;
	/* If equal, gets added after */ 
	while (node_compare(task_node, cur) <= 0) {
    /* Comparator must define comparison with NULL as well */
    prev = cur;
		cur = get_next(cur);
	}

  /* Previous can only be NULL when task_node is added to the head 
   * This is due to the fact that NULL is the minimum element and 
   * therefore when cur == NULL, the loop will break */
  if (prev == NULL) {
    set_next(task_node, *list);
    *list = task_node;
    return true;
  }

  set_next(task_node, get_next(prev));
  set_next(prev, task_node);
  return true;
}

/* Free the memory allocated for the linked list */
void 
free_linked_list(linked_list list) {
  assert(list_exists(list));

  node *cur = *list;
  node *prev = NULL;
  while (!is_null_node(cur)) {
    prev = cur;
    cur = get_next(cur);
    free_node(prev);
  }

  free(list);
}

/* Print the contents of the linked list */
void 
print_linked_list(linked_list list) {
  assert(list_exists(list));

  node *cur = *list;
  while (!is_null_node(cur)) {
    print_node(cur);
    cur = get_next(cur);
  }
}
