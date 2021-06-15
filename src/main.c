/* System Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/* Project Includes */
#include "trie.h"

/* Defines */
#define NUM_FILES 10
#define FILE_NAME_MAX_SIZE 15

/* Global variables */
struct trie_node* trie_root;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* Function defintions */
void *process_file(void *file_name)
{
    char filename[FILE_NAME_MAX_SIZE];
    strcpy(filename, (char *)file_name);
    free(file_name); // Free pointer passed into function as it is not needed anymore
    printf("Reading file: %s\n", filename);

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not read file: %s\n", filename);
        return NULL;
    }

    int c;
    char buf[MAX_WORD_LENGTH + 1] = {'\0'};
    for (int j = 0; (c = getc(fp)) != EOF && j < MAX_WORD_LENGTH; j++)
    {
        if (c == '\n')
        {
            pthread_mutex_lock(&lock);
            trie_add_word(trie_root, buf);
            pthread_mutex_unlock(&lock);
            j = -1;
            for (int k = 0; buf[k]; k++) buf[k] = '\0';
            continue;
        }

        buf[j] = (char)c;
    }

    fclose(fp);
}

int main(void)
{
    trie_root = trie_create();
    pthread_t threads[NUM_FILES];

    // Cycle through each data file
    for (int i = 0; i < NUM_FILES; i++)
    {
        char *filename = malloc(sizeof(char) * FILE_NAME_MAX_SIZE);
        sprintf(filename, "data_%d.txt", i);
        pthread_create(&threads[i], NULL, process_file, (void *)filename);
    }

    for (int i = 0; i < NUM_FILES; i++)
    {
        pthread_join(threads[i], NULL);
    }

    char buf[MAX_WORD_LENGTH + 1] = {'\0'};
    putchar('\n');
    trie_print(trie_root, buf);

    trie_delete(trie_root);
    printf("Done.\n");


    return 0;
}
