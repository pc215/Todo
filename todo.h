#include <argp.h>
#include <stdbool.h>
/* Specification:
 * ADD: Add a new task (with importance and urgency values)
 * DELETE: Remove and unwanted task
 * COMPLETE: Complete a task and add to another list (then delete it)
 * COMPLETE_TOP_TASK: A special command using the COMPLETE function
 * CHANGE URGENCY: Change urgency of the task and re-order
 * CHANGE IMPORTANCE: Change importance of the task and re-order
 */

// To make it future-proof adding the list as an argument

/**
 * Add a new task to the todo list
 * @param list - The todo list
 * @param task - The task to be added
 * @param importance - The importance of the task (from 0-9)
 * @param urgency - The urgency of the task (from 0-9)
 */

#define INIT_COMMAND "init"
#define DROP_COMMAND "drop"
#define ADD_COMMAND "add"
#define DEL_COMMAND "del"
#define OPT_ADD 1
#define OPT_DEL 2

const char *argp_program_verison = "Todo 0.05";
const char *argp_program_bug_address = "chouksepranav@gmail.com";

struct add_arguments {
  int importance;
  int urgency;
};

struct del_arguments {
  bool remove;
  bool complete;
};


