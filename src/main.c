#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

#define NUM_FILES 3

int main(void)
{
    FILE *fp;
    char buf[MAX_WORD_LENGTH + 1] = {'\0'};
    struct trie_node* trie_root = trie_create();

    // Cycle through each data file
    for (int i = 0; i < NUM_FILES; i++)
    {
        char filename[11];
        sprintf(filename, "data_%d.txt", i);
        printf("Reading file: %s\n", filename);

        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            printf("Could not read file: %s\n", filename);
            return 1;
        }

        int c;
        for (int j = 0;(c = getc(fp)) != EOF && j < MAX_WORD_LENGTH; j++)
        {
            if (c == '\n')
            {
                trie_add_word(trie_root, buf);
                j = -1;
                memset(buf, 0, sizeof(buf));
                continue;
            }

            buf[j] = (char)c;
        }
    }

    memset(buf, 0, sizeof(buf));
    putchar('\n');
    trie_print(trie_root, buf);

    trie_delete(trie_root);
    free(fp);

    return 0;
}
