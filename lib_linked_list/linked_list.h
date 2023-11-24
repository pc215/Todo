#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

/* Points to the head of the linked list */
typedef node **linked_list;
typedef int (*comparator)(node *, node *);

extern linked_list create_linked_list(void);
extern node *get_node(linked_list list, int pos);
extern bool remove_node(linked_list list, int pos);
extern bool insert_node(linked_list list, node *task_node, 
                        comparator node_compare);
extern void free_linked_list(linked_list list);
extern void print_linked_list(linked_list list);

#endif /* LINKED_LIST_H */
