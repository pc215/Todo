#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <openssl/sha.h>
#include "support.h"

void serialise_task_with_next(node *task_node, char *file_name) {
  FILE *fp = fopen(file_name, "w");
  if (fp == NULL) {
    fprintf(stderr, "%s file cannot be opened!", file_name);
    exit(EXIT_FAILURE);
  }
  memcpy(fp, task_node->importance, sizeof(int));
  memcpy(fp + sizeof(int), task_node->urgency, sizeof(int));
  // hash the next node before writing
  memcpy(fp + 2 * sizeof(int), task_node->next, sizeof(node *));
  memcpy(fp + 2 *sizeof(int) + sizeof(node *), task_node->task, 
         strlen(task_node->task));
  fclose(fp);
}

void deserialise_task(char *file_name, node *task_node) {
  // Gets everything except node (has a different function for it)
  memcpy(fp, task_node->importance, sizeof(int));
  memcpy(fp + sizeof(int), task_node->urgency, sizeof(int));
  // hash the next node before writing
  memcpy(fp + 2 * sizeof(int), task_node->next, sizeof(node *));
}

void deserialise_next(char *file_name, node *task_node) {

}
