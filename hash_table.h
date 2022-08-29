#ifndef CS165_HASH_TABLE // This is a header guard. It prevents the header from being included more than once.
#define CS165_HASH_TABLE

#define num_slots // number of slots

typedef int keyType;
typedef int valType;

typedef struct node
{
    keyType key;
    valType val;
    struct node *next;
} node;

typedef struct hashtable
{
    // define the components of the hash table here (e.g. the array, bookkeeping for number of elements, etc)
    node **array;
    int num_pairs;
    int size;
} hashtable;

int allocate(hashtable **ht, int size);
int put(hashtable *ht, keyType key, valType value);
int get(hashtable *ht, keyType key, valType *values, int num_values, int *num_results);
int erase(hashtable *ht, keyType key);
int deallocate(hashtable *ht);

#endif
