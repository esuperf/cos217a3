#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"

struct Node {
   char *key;
   void *value;
   struct Node *next;
};

struct SymTable {
   struct Node *first;
};

static size_t SymTable_hash(const char *pcKey, size_t uBucketCount)
{
   const size_t HASH_MULTIPLIER = 65599;
   size_t u;
   size_t uHash = 0;

   assert(pcKey != NULL);

   for (u = 0; pcKey[u] != '\0'; u++)
      uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];

   return uHash % uBucketCount;
}
