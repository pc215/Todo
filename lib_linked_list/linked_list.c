#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

// Create a linked list
linked_list *create_linked_list( void ) {
	return calloc(sizeof(node *), 1);
}

// Returns true if the head is NULL
bool is_empty_list(linked_list *list) {
	return is_null_node(*list);
}

bool is_null_list(linked_list *list) {
  return list==NULL;
}

// Checks if the next node exists
bool has_next(node *current) {
	return !is_null_node(current) ? is_null_node(current->next) : false;
}

// Returns NULL if the current node is NULL 
node *get_next(node *current) {
	return !is_null_node(current) ? current->next : NULL;
}

// Set next node of a given node
bool set_next(node *current, node *next) {
	if (!is_null_node(current)) {
		current->next = next;
		return true;
	}
	return false;
}

// Find a certain node at a given position
node *find_node(linked_list *list, int position) {
	assert(!is_null_list(list) && !is_empty_list(list));
	node *current = *list;
	while ( (position--) && !is_null_node(current) ) {
		current = get_next(current);
	}
	// If NULL then gives an appropriate message
	return current;
}


// Remove a node at a given position
bool remove_node(linked_list *list, int position) {
	// The head
	
	assert(!is_null_list(list));
	node *current = *list;
	node *prev = NULL;
	// Search for the node
	
	while ( (position--) && !is_null_node(current) ) {
		prev = current;
		current = get_next(current);
	}

	// Either current is NULL or value is found
	if (is_null_node(current)) {
		return false;
	}

	// Remove the node
	if (is_null_node(prev)) {
		// remove head
		*list = get_next(current);

	} else if (!has_next(current)) {
		// remove tail
		set_next(prev, NULL);
	} else {
		// middle
		set_next(prev, get_next(current));
	}

	free_node(current);

	return true;
}

void insert_node(linked_list *list, node **task_node, comparator node_comparator) {
	assert(!is_null_list(list));
  assert(!is_null_node(*task_node));
	// The head
	node *current = *list;
	node *prev = NULL;
	// If equal, gets added before 
	while (current != NULL && node_comparator(*task_node, current) <= 0) {
		prev = current;
		current = get_next(current);
	}
	// current == NULL || node_comparator(task_node, current) < value
  // If node comes after with same priority, must be placed after

	if (current == NULL) {
		if (prev == NULL) {
			// Empty list
			*list = *task_node;
		} else {
			// Add to tail
			set_next(prev, *task_node); 
		}
	} else {
    if (prev == NULL) {
      // Add to head
      *list = *task_node;
      set_next(*task_node, current);
    } else {
      // Add to middle
      set_next(prev, *task_node);
      set_next(*task_node, current);
    } 
	}
}

// Free the memory allocated for the linked list
void free_linked_list(linked_list *list) {
  if (!is_null_list(list)) {
    if (!is_empty_list(list)) {
      node *current = *list;
      node *prev = NULL;
      while (!is_null_node(current)) {
        prev = current;
        current = get_next(current);
        free_node(prev);
      }
    }
    // Freeing list
    free(list);
  }
}


void print_linked_list(linked_list *list) {
	if (is_null_list(list)) {
		printf("Linked list does not exist!\n");
	} else {
		node *current = *list;
		while (!is_null_node(current)) {
      print_node(current);
			current = get_next(current);
		}
	}
}


// Linked lists
linked_list todo_list;
