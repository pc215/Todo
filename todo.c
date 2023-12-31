#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
  

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

int main( int argc, char **argv) {

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
