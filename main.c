#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

// This is where you can implement your own tests for the hash table
// implementation.
int main(void)
{
  printf("starting allocate\n");

  hashtable *ht = NULL;
  int size = 10;
  int res = allocate(&ht, size);
  printf("allocate result: %d\n", res);

  int key = 0;
  int value = -1;

  res = put(ht, key, value);
  printf("put result: %d\n", res);

  int num_values = 1;

  valType *values = malloc(1 * sizeof(valType));
  int num_res = 0;
  int *num_results = &num_res;

  res = get(ht, key, values, num_values, num_results);
  printf("get result: %d, num_results %p %d\n", res, num_results, *num_results);

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
  (void)ht;
  return 0;
}
