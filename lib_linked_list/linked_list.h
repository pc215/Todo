#include "node.h"

// Point to the head of the linked list
typedef node *linked_list;
typedef int (*comparator)(void *, void *);

extern linked_list *create_linked_list( void );
extern bool is_null_list(linked_list *list);
extern bool is_empty_list(linked_list *list);
extern node *find_node(linked_list *list, int position);
extern bool has_next(node *current);
extern node *get_next(node *current);
extern bool set_next(node *current, node *next);
extern bool remove_node(linked_list *list, int position);
extern void insert_node(linked_list *list, node **task_node, 
                                comparator node_comparator);
extern void free_linked_list(linked_list *list);
extern void print_linked_list(linked_list *list);

// Linked lists
extern linked_list todo_list;
