#include <stdbool.h>

#ifndef NODE_H
#define NODE_H

typedef struct node node;

struct node{
	int importance;
	int urgency;
	node *next;
	char *task;
};

extern bool is_null_node(node *task_node);
extern node *create_node(char *task, int importance, int urgency);
extern void print_node(node *task_node);
extern void free_node(node *task_node);

#endif /* NODE_H */
