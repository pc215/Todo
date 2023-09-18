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

struct argp_option add_options[] = {
  {"importance", 'i', "INT", OPTION_ARG_OPTIONAL, 
   "Importance level (between 0 and 9, both inclusive)", OPT_ADD},
  {"urgency", 'u', "INT", OPTION_ARG_OPTIONAL,
   "Urgency level (between 0 and 9, both inclusive)", OPT_ADD},
  {0}
};  

// Need a separate flag to ensure mutual exclusivity
struct argp_option del_options[] = {
  {"remove", 'r', "INT", OPTION_ARG_OPTIONAL, 
   "Removes a task from the todo-list (top by default)", OPT_DEL},
  {"complete", 'c', "INT", OPTION_ARG_OPTIONAL, 
   "Completes a task from the todo-list (top by default)", OPT_DEL},
  {0}
};

