#include <stdio.h>

#include "node.h"

int main(void) {
  char *task = "Complete todo-list program";
  int urgency = 9;
  int importance = 8;
  node *task_1 = create_node(task, importance, urgency);
  node *task_2 = NULL;
  printf("Task1 is null: %d\n", is_null(task_1));
  printf("Task2 is null: %d\n", is_null(task_2));
  print_node(task_1);
  free_node(task_1);
  return 0;
}
