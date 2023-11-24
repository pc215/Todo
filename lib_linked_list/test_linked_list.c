#include <stdio.h>

#include "linked_list.h"

int node_comparator(node *node_1, node *node_2) {
  if (node_1 == NULL) {
    return -1;
  }

  if (node_2 == NULL) {
    return 1;
  }

  if (node_1->imp == node_2->imp) {
    if (node_1->urg == node_2->urg) {
      return 0;
    } 
    return node_1->urg > node_2->urg ? 1 : -1;
  }
  return node_1->imp > node_2->imp ? 1 : -1;
}

int main(void) {
  linked_list list = create_linked_list();
  char *t1 = "First";
  char *t2 = "Fourth";
  char *t3 = "Second";
  char *t4 = "Third";
  node *n1 = create_node(8, 9, t1);
  node *n2 = create_node(7, 9, t2);
  node *n3 = create_node(8, 6, t3);
  node *n4 = create_node(8, 6, t4);

  insert_node(list, n1, &node_comparator);
  printf("After inserting t1: \n");
  print_linked_list(list);
  insert_node(list, n2, &node_comparator);
  printf("After inserting t2: \n");
  print_linked_list(list);
  insert_node(list, n3, &node_comparator);
  printf("After inserting t3: \n");
  print_linked_list(list);
  remove_node(list, 2);
  insert_node(list, n4, &node_comparator);
  printf("After inserting t4 and deleting t3: \n");
  print_linked_list(list);
  free_linked_list(list);
  return 0;
}
