#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

// This is where you can implement your own tests for the hash table
// implementation.
int main(void)
{
  node *head = NULL;
  node *second = NULL;
  node *third = NULL;

  head = (node *)malloc(sizeof(node));
  second = (node *)malloc(sizeof(node));
  third = (node *)malloc(sizeof(node));

  head->key = 1;
  head->val = 10;
  head->next = second;

  second->key = 2;
  second->val = 20;
  second->next = third;

  third->key = 3;
  third->val = 30;
  third->next = NULL;

  printf("Hi this is running third key %d val %d", head->next->next->key, head->next->next->val);

  hashtable *ht = NULL;
  int size = 10;
  allocate(&ht, size);

  int key = 0;
  int value = -1;

  put(ht, key, value);

  int num_values = 1;

  valType *values = malloc(1 * sizeof(valType));

  int *num_results = NULL;

  get(ht, key, values, num_values, num_results);
  if ((*num_results) > num_values)
  {
    values = realloc(values, (*num_results) * sizeof(valType));
    get(ht, 0, values, num_values, num_results);
  }

  for (int i = 0; i < (*num_results); i++)
  {
    printf("value of %d is %d \n", i, values[i]);
  }
  free(values);

  erase(ht, 0);

  deallocate(ht);
  return 0;
}
