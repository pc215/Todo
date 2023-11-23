#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include "support.h"

#define ASCII_HASH_SIZE (2 * SHA256_DIGEST_LENGTH)
#define LENGTH_OF_DIR_NAME (2)
/* Number of paramaters for the comparator (imp and urg here) */
#define NUM_OF_PARAMS (2)
#define MAX_TASK_SIZE (512)

/* Sets hash_str to the ascii representation of the hash 
 * calculated from the task_node. 
 * Considers importance, urgency and pointer to the next node. 
 * A null next node is handled by hashing 0x0 */
static void 
get_node_hash(const node *task_node, char *hash_str) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  if (task_node) {
    /* Hash value of importance, urgency and pointer to next node */
    int size = 2 * sizeof(int) + sizeof(node *);
    SHA256_Update(&sha256, task_node, size);
  } else {
    /* Termination of the linked list */
    SHA256_Update(&sha256, task_node, 0);
  } 

  SHA256_Final(hash, &sha256);

  /* Convert to ASCII readable form */
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(hash_str + (2 * i), "%02x", hash[i]);
  }
}

/* Gets the name of the directory based on the first two 
 * characters of the hash */
static void 
get_dir_name(const char *hash, const char *tasks_dir, char *file) {
  strcpy(file, tasks_dir);
  strncat(file, hash, LENGTH_OF_DIR_NAME * sizeof(char));
}

/* Gets the name of file for the task based on the hash of 
 * its task node.
 * First 2 characters of the hash make the name of the directory 
 * and the remaining constitute the file name */
static void 
get_file_name(const char *hash, const char *tasks_dir, char *file) {
  get_dir_name(hash, tasks_dir, file);
  strcat(file, "/");
  strncat(file, LENGTH_OF_DIR_NAME + hash, 
          (ASCII_HASH_SIZE - LENGTH_OF_DIR_NAME) * sizeof(char));
}

/* Writes important information from the task node to the 
 * file representing it in the tasks directory.
 * The urgency and importance are written directly, followed 
 * by the hashed form of the next node. 
 * Lastly, the task is written in ASCII */
static bool 
write_node_to_file(const char *file, node *task_node) {
  FILE *fp = fopen(file, "w");
  if (fp == NULL) {
    fprintf(stderr, "Could not create %s file!\n", file);
    return false;
  }

  fprintf(fp, "%d", task_node->importance);
  fprintf(fp, "%d", task_node->urgency);

  /* Hashing the pointer to the next node */
  char hash_next[ASCII_HASH_SIZE];
  get_node_hash(task_node->next, hash_next);

  fprintf(fp, "%s", hash_next);
  fprintf(fp, "%s", task_node->task);
  fclose(fp);
  return true;
}

/* The task node is hashed and its contents are represented 
 * appropriately in a file in the tasks directory */
void serialise_task_node(node *task_node, char *tasks_dir) {
  /* Hash the task_node */
  char hash_curr[ASCII_HASH_SIZE];
  get_node_hash(task_node, hash_curr);

  /* Get the name of the directory */
  const int dir_name_len = LENGTH_OF_DIR_NAME + strlen(tasks_dir);
  char dir[dir_name_len];
  get_dir_name(hash_curr, tasks_dir, dir);

  /* Create the directory */
  mkdir(dir, 0755);

  /* Get the name of the file */ 
  char file[ASCII_HASH_SIZE + dir_name_len];
  get_file_name(hash_curr, tasks_dir, file);

  /* Can also store the size of the text in the file */
  if (!write_node_to_file(file, task_node)) {
    // Force exit for now, think of more elegant approach later
    exit(-1);
  }

  print_task_node(hash_curr, tasks_dir);
}

/* Returns the urgency, read from the file */
static const int 
get_imp(FILE *fp) {
  fseek(fp, 0, SEEK_SET);
  return fgetc(fp) - '0';
}

/* Returns the importance, read from the file */
static const int 
get_urg(FILE *fp) {
  fseek(fp, sizeof(char), SEEK_SET);
  return fgetc(fp) - '0';
}

/* The string passed in should have at least enough space to accommodate
 * an ASCII hash string */
static void
get_hash(FILE *fp, char *hash) {
  fseek(fp, NUM_OF_PARAMS * sizeof(char), SEEK_SET);
  fgets(hash, ASCII_HASH_SIZE + 1, fp);
}

/* The string passed in should have at least enough space to accommodate
 * an MAX_TASK_SIZE task string */
static void
get_task(FILE *fp, char *task) {
  fseek(fp, NUM_OF_PARAMS * sizeof(char) + ASCII_HASH_SIZE, SEEK_SET);
  fgets(task, MAX_TASK_SIZE, fp);
}

/* Retrieve the task from the file stored in the tasks directory 
 * for a certain task node */
void print_task_node(char *hash, char *tasks_dir) {
  char hash_null[ASCII_HASH_SIZE];
  get_node_hash(NULL, hash_null);
  if (strcmp(hash, hash_null) == 0) {
    printf("Terminated!\n");
    return;
  }

  const int dir_name_len = LENGTH_OF_DIR_NAME + strlen(tasks_dir);
  char file[ASCII_HASH_SIZE + dir_name_len];
  get_file_name(hash, tasks_dir, file);

  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    fprintf(stderr, "Could not open %s file!\n", file);
    return;
  }

  char hash_next[ASCII_HASH_SIZE + 1];
  get_hash(fp, hash_next);
  printf("Next hash:%s\n", hash_next);

  printf("Imp:%d\n", get_imp(fp));

  printf("Urg:%d\n", get_urg(fp));

  char task[MAX_TASK_SIZE];
  get_task(fp, task);
  printf("Task:%s\n", task);

  print_task_node(hash_next, tasks_dir);
}

// void deserialise_task(char *file_name, node *task_node) {
//   // Gets everything except node (has a different function for it)
//   memcpy(fp, task_node->importance, sizeof(int));
//   memcpy(fp + sizeof(int), task_node->urgency, sizeof(int));
//   // hash the next node before writing
//   memcpy(fp + 2 * sizeof(int), task_node->next, sizeof(node *));
// }
//
// void deserialise_next(char *file_name, node *task_node) {
//
// }
