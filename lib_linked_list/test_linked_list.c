#include <stdio.h>

#include "linked_list.h"

int node_comparator(void *value_1, void *value_2) {
  node *node_1 = (node *)value_1;
  node *node_2 = (node *)value_2;
  if (node_1->importance == node_2->importance) {
    if (node_1->urgency == node_2->urgency) {
      return 0;
    } 
    // else 
    return node_1->urgency > node_2->urgency ? 1 : -1;
  }
  // else 
  return node_1->importance > node_2->importance ? 1 : -1;
}

int main(void) {
  linked_list *list = create_linked_list();
  char *t1 = "First";
  char *t2 = "Fourth";
  char *t3 = "Second";
  char *t4 = "Third";
  node *n1 = create_node(t1, 8, 9);
  node *n2 = create_node(t2, 7, 9);
  node *n3 = create_node(t3, 8, 6);
  node *n4 = create_node(t4, 8, 6);
  insert_node(list, &n1, &node_comparator);
  printf("After inserting t1: \n");
  print_linked_list(list);
  insert_node(list, &n2, &node_comparator);
  printf("After inserting t2: \n");
  print_linked_list(list);
  insert_node(list, &n3, &node_comparator);
  printf("After inserting t3: \n");
  print_linked_list(list);
  insert_node(list, &n4, &node_comparator);
  printf("After inserting t4: \n");
  print_linked_list(list);
    
  return 0;
}
