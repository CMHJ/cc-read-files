#pragma once

#ifndef __TRIE_H__
#define __TRIE_H__

#define NUM_CHARS 26
#define MAX_WORD_LENGTH 30

#include <stdint.h>

struct trie_node
{
    struct trie_node *branches[NUM_CHARS];
    uint64_t count;
};

struct trie_node * trie_create();
void trie_add_word(struct trie_node*, const char *);
void trie_delete_word(struct trie_node*, const char *);
void trie_print(struct trie_node *, char *);
void trie_delete(struct trie_node *);

#endif /* __TRIE_H__ */