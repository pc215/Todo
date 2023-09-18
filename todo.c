#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

#include "todo.h"
  

static void prepend_string(char *prefix, char *original) {
  int prefix_len = strlen(prefix);
  int original_len = strlen(original);
  // Copy the original string (including the '\0') and offset it
  memcpy(original + prefix_len, original, original_len + 1);
  // Move the prefix string to the start
  memmove(original, prefix, prefix_len);
}

// Find the closest todo-list encompassing the pwd if any
// Returns the address if found else NULL
static void find_dir(char *dir, char *start_dir, char (*found_dir)[PATH_MAX]) {
  // Since each directory has a single parent, just search upwards till /
  // Search cwd, then prepend ..

  char target_path[PATH_MAX];
  // Get absolute path of start_dir
  realpath(start_dir, target_path);
  strcat(target_path, "/");
  strcat(target_path, dir);

  // Inductive step (if it exists)
  struct stat st;
  int result = stat(target_path, &st);
  if (result == 0 && S_ISDIR(st.st_mode)) {
    strcpy(*found_dir, target_path);
    // printf("Found: %s\n", *found_dir);
  } else {
    // Base case if directory does not exist
    char root_dir[PATH_MAX] = "//"; 
    if (strcmp(target_path, strcat(root_dir, dir)) != 0) {
      // Recursive condition
      char parent_prefix[] = "../";
      char cwd[PATH_MAX];
      strcpy(cwd, start_dir);
      prepend_string(parent_prefix, cwd);
      find_dir(dir, cwd, found_dir);
    }
  }
}

// Function to print the argp_state contents
// static void print_argp_state(const struct argp_state *state) {
//     printf("argc: %d\n", state->argc);
//     printf("argv:\n");
//     for (int i = 0; i < state->argc; i++) {
//         printf("  argv[%d]: \"%s\"\n", i, state->argv[i]);
//     }
//     printf("next: %d\n", state->next);
//     printf("input: %p\n", state->input);
//     printf("root_argp: %p\n", (void *)state->root_argp);
//     printf("name: \"%s\"\n", state->name);
// }

static error_t parse_opt_add (int key, char *arg, struct argp_state *state) {
  switch (key) {
    case 'i': printf ("Have reached i\n"); break;
    case 'u': printf ("Have reached u\n"); break;
  }
  return 0;
}

static error_t parse_opt_del (int key, char *arg, struct argp_state *state) {
  switch (key) {
    case 'r': printf ("Have reached r\n"); break;
    case 'c': printf ("Have reached c\n"); break;
  }
  return 0;
}


static error_t todo_init() {
  // pwd will be required so calculate each time any todo command is called.
  char cwd[PATH_MAX];
  if (getcwd(cwd, PATH_MAX) == NULL) {
    fprintf(stderr, "Can't get the current working directory!\n");
    return EXIT_FAILURE;
  }

  char todo_dir[] = ".todo";
  char tasks_dir[] = ".todo/tasks";
  char refs_dir[] = ".todo/refs";
  char head_file[] = ".todo/refs/HEAD";
  char todo_dir_above[PATH_MAX] = "";
  find_dir(todo_dir, ".", &todo_dir_above);
  if (strcmp(todo_dir_above, "") == 0) {
    printf("No .todo directory found\n");
  } else {
    printf(".todo directory found at %s\n", todo_dir_above);
  }

  // todo init
  if (mkdir(todo_dir, 0755) != 0) {
    fprintf(stderr, "%s already exists!\n", todo_dir);
    fprintf(stderr, "Please drop the current todo list to create a new one.\n");
    return EXIT_FAILURE;
  }

  if (mkdir(tasks_dir, 0755) != 0) {
    fprintf(stderr, "Could not create %s\n", tasks_dir);
    return EXIT_FAILURE;
  }

  if (mkdir(refs_dir, 0755) != 0) {
    fprintf(stderr, "Could not create %s!\n", refs_dir);
    return EXIT_FAILURE;
  }

  printf("Initialised empty Todo list in %s/%s\n", cwd, todo_dir);

  // When adding a task and there is no HEAD file
  // Creating an empty HEAD file
  FILE *fp_head = fopen(head_file, "w");
  if (fp_head == NULL) {
    fprintf(stderr, "Could not create %s file!\n", head_file);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  switch (key) {
    case ARGP_KEY_ARG: {
      // To stop parsing at the current argument
      int argc = state->argc;
      state->argc = 2;

      if (!strcmp(arg, INIT_COMMAND)) {
         return todo_init();
      } else if (!strcmp(arg, ADD_COMMAND)) {
        struct argp argp_add = {add_options, parse_opt_add};
        argp_parse(&argp_add, argc-1, state->argv+1, 0, 0, 0);
      } else if (!strcmp(arg, DEL_COMMAND)) {
        struct argp argp_del = {del_options, parse_opt_del};
        argp_parse(&argp_del, argc - 1, state->argv + 1, 0, 0, 0);
      } else if (!strcmp(arg, DROP_COMMAND)) {

      } else {
        fprintf(stderr, "Invalid Command!\n");
      }
      break;
    }
    case ARGP_ERR_UNKNOWN: {
      // TODO
      fprintf(stderr, "Invalid Command!\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int main( int argc, char **argv) {

  if (argc == 1) {
    // Print todo list
    printf("Print todo list!\n");
  } else {
    struct argp argp_opt = {NULL, parse_opt};
    argp_parse(&argp_opt, argc, argv, ARGP_IN_ORDER, NULL, NULL);
  }
	return EXIT_SUCCESS;
}
