#include <stdio.h>

#include "node.h"

int main(void) {
  char *task = "Complete todo-list program";
  int urg = 9;
  int imp = 8;
  node *task_1 = create_node(imp, urg, task);
  node *task_2 = NULL;
  printf("Task1 is null: %d\n", is_null_node(task_1));
  printf("Task2 is null: %d\n", is_null_node(task_2));
  print_node(task_1);
  free_node(task_1);
  return 0;
}
