#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

struct trie_node * trie_create()
{
    struct trie_node *t = (struct trie_node *)malloc(sizeof(struct trie_node));
    for (int i = 0; i < NUM_CHARS; i++){ t->branches[i] = NULL; }
    t->count = 0;

    if (t == NULL)
    {
        fprintf(stderr, "Error: could not malloc memory for trie.\n");
        return NULL;
    }

    return t;
}

void trie_add_word(struct trie_node *root, const char *word)
{
    /* If at the end of a word increment count */
    if (strlen(word) == 0)
    {
        root->count++;
        return;
    }

    /* If no node for current letter */
    uint8_t idx = (uint8_t)(word[0] - 'a');
    if (root->branches[idx] == NULL)
    {
        struct trie_node *t = (struct trie_node *)malloc(sizeof(struct trie_node));
        for (int i = 0; i < NUM_CHARS; i++){ t->branches[i] = NULL; }
        t->count = 0;
        root->branches[idx] = t;
    }

    /* Add word */
    trie_add_word(root->branches[idx], &word[1]);
}

void trie_delete_word(struct trie_node*, const char *);

void trie_print(struct trie_node *root, char *buf)
{
    /* If at the end of a word, print before continuing */
    if (root->count)
    {
        printf("%s: %ld\n", buf, root->count);
    }

    /* For all letters in the current node */
    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (root->branches[i] == NULL)
            continue;

        /* Append letter to buffer and go to next node*/
        char c = 'a' + (char)i;
        int len = strlen(buf);

        if (len >= NUM_CHARS)
        {
            fprintf(stderr, "Error: Reached max word length\n");
            return;
        }

        buf[len] = c;
        trie_print(root->branches[i], buf);

        // memset(&buf[len], 0, sizeof(buf) - len);
        buf[len] = '\0';
    }
}

void trie_delete(struct trie_node *root)
{
    /* Delete all branch */
    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (root->branches[i] != NULL)
        {
            trie_delete(root->branches[i]);
        }
    }

    /* Delete node itself */
    free(root);
}
