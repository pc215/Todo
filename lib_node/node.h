#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct node node;

struct node{
	int imp;
	int urg;
	node *next;
	char *task;
};

extern node *create_node(int imp, int urg, char *task);
extern bool is_null_node(node *task_node);
extern void print_node(node *task_node);
extern void free_node(node *task_node);

#endif /* NODE_H */
