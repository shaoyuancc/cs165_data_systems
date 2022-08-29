#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// Hash the key
int hash(hashtable *ht, keyType key)
{
    return key % ht->size;
}

node *create_node(keyType key, valType val)
{
    node *new_node;

    new_node = malloc(sizeof(node));

    if (!new_node)
    {
        return NULL;
    }

    new_node->key = key;
    new_node->val = val;

    new_node->next = NULL;

    return new_node;
}

// Initialize the components of a hashtable.
// The size parameter is the expected number of elements to be inserted.
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the parameter passed to the method is not null, if malloc fails, etc).
int allocate(hashtable **ht, int size)
{
    if (*ht || size < 1)
    {
        return -1;
    }

    *ht = (hashtable *)malloc(sizeof(hashtable));
    if (!*ht)
    {
        return -1;
    }

    (*ht)->array = malloc(sizeof(node *) * size);
    if (!(*ht)->array)
    {
        free(*ht);
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        (*ht)->array[i] = NULL;
    }

    (*ht)->size = size;

    return 0;
}

// This method inserts a key-value pair into the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if malloc is called and fails).
int put(hashtable *ht, keyType key, valType value)
{
    int slot = hash(ht, key);
    printf("slot %d\n", slot);
    node *new_node = create_node(key, value);
    if (!new_node)
    {
        return -1;
    }
    printf("New node key: %d val: %d\n", new_node->key, new_node->val);

    node *current_node = ht->array[slot];
    if (!current_node)
    {
        ht->array[slot] = new_node;
    }
    else
    {
        printf("current node key: %d, val: %d, next: %p", current_node->key, current_node->val, current_node->next);
        while (current_node->next != NULL)
        {
            printf("current_node->next != NULL, going to next one\n");
            current_node = current_node->next;
        };

        current_node->next = new_node;
    }
    return 0;
}

// This method retrieves entries with a matching key and stores the corresponding values in the
// values array. The size of the values array is given by the parameter
// num_values. If there are more matching entries than num_values, they are not
// stored in the values array to avoid a buffer overflow. The function returns
// the number of matching entries using the num_results pointer. If the value of num_results is greater than
// num_values, the caller can invoke this function again (with a larger buffer)
// to get values that it missed during the first call.
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int get(hashtable *ht, keyType key, valType *values, int num_values, int *num_results)
{
    if (!ht || !num_results || num_values < 0)
    {
        return -1;
    };

    int slot = hash(ht, key);
    printf("get slot %d\n", slot);
    *num_results = 0;
    node *current_node = ht->array[slot];
    while (current_node)
    {
        printf("num results: %d, current node key: %d, val: %d, next: %p\n", *num_results, current_node->key, current_node->val, current_node->next);

        if (current_node->key == key)
        {
            printf("current_node->key == key\n");
            *num_results += 1;
            if (num_values > *num_results)
            {
                continue;
            }
            values[*num_results - 1] = current_node->val;
        };
        current_node = current_node->next;
    }

    return 0;
}

// This method erases all key-value pairs with a given key from the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int erase(hashtable *ht, keyType key)
{
    int slot = hash(ht, key);
    node *last_node = ht->array[slot];
    node *current_node = ht->array[slot];

    while (current_node)
    {
        if (current_node->key == key)
        {
            if (current_node == ht->array[slot])
            {
                ht->array[slot] = current_node->next;
            }
            else
            {
                node *ptr_to_free = current_node;
                last_node->next = current_node->next;
                current_node = current_node->next;
                free(ptr_to_free);
            }
        }
        else
        {
            current_node = current_node->next;
        }
    }
    return 0;
}

// This method frees all memory occupied by the hash table.
// It returns an error code, 0 for success and -1 otherwise.
int deallocate(hashtable *ht)
{
    free(ht->array);
    free(ht);
    return 0;
}