#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"

struct Binding {
   char *key;
   void *value;
   struct Binding *next;
};

struct Bucket {
   struct Binding *bucket;
}

struct SymTable {
   struct Binding **first;
   size_t bucketCount;
};

size_t auBucketCounts[] = {509, 1021}

static const size_t numBucketCounts = sizeof(auBucketCounts)/
   sizeof(auBucketCounts[0]);

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

SymTable_T SymTable_new(void) {
   SymTable_T new = (SymTable_T) malloc(sizeof(struct SymTable));
   if (new == NULL){
      return NULL;
   }
   int i = 0;
   new->first = calloc(auBucketCounts[i], sizeof(struct Binding*));
   if (new->first == NULL){
      free(new);
      return NULL;
   }
   return new;
}

void SymTable_free(SymTable_T oSymTable){
   struct Binding *clear = oSymTable->first;
   while (clear != NULL){
      struct Binding *next = clear->next;
      free(clear->key);
      free(clear);
      clear = next;
   }
   free(oSymTable);
}

size_t SymTable_getLength(SymTable_T oSymTable){
   size_t count = 0;
   struct Binding *temp = oSymTable->first;
   while (temp != NULL){
      count++;
      temp = temp->next;
   }
   return count;
}

int SymTable_put(SymTable_T oSymTable,
                 const char *pcKey, const void *pvValue){
   struct Node *current;
   struct Node *p;

   assert (oSymTable != NULL && pcKey != NULL);
   
   for(current = oSymTable->first; current != NULL;
       current = current->next){
      if (strcmp(current->key, pcKey) == 0){
         return 0;
      }
   }
   
   p = malloc(sizeof(struct Node));
   if (p == NULL){
      return 0;
   }
   
   p->key = malloc(strlen(pcKey) + 1);
   if (p->key == NULL){
      free(p);
      return 0;
   }

   strcpy(p->key, pcKey);
   p->value = (void*) pvValue;
   p->next = oSymTable->first;
   oSymTable->first = p;

   return 1;
}

void *SymTable_replace(SymTable_T oSymTable,
                       const char *pcKey, const void *pvValue){
   struct Node *p;
   void *temp;
   assert(oSymTable != NULL && pcKey != NULL);
   int i = 0;
   
   size_t target = SymTable_hash(pcKey, auBucketCounts[i];
   for(p = oSymTable->first; p!= NULL; p = p->next){
      if(strcmp(p->key, pcKey) == 0){
         temp = p->value;
         p->value = (void*) pvValue;
         return temp;
      }
   }
   return NULL;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
   struct Node *p;
   assert(oSymTable != NULL && pcKey != NULL);
   
   for(p = oSymTable->first; p!= NULL; p = p->next){
      if(strcmp(p->key, pcKey) == 0){
         return 1;
      }
   }
   return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
   struct Node *p;
   assert(oSymTable != NULL && pcKey != NULL);
   
   for(p = oSymTable->first; p!= NULL; p = p->next){
      if(strcmp(p->key, pcKey) == 0){
         return p->value;
      }
   }
   return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey){
   struct Node *p;
   struct Node *prev = NULL;
   void *store;
   assert(oSymTable != NULL && pcKey != NULL);
   
   for (p = oSymTable->first; p != NULL; prev = p, p = p->next){
      if (strcmp(p->key, pcKey) == 0){
         store = p->value;

         if (prev == NULL){
            oSymTable->first = p->next;
         }
         else {
            prev->next = p->next;
         }
         
         free(p->key);
         free(p);
         return store;
      }
   }
   return NULL;
}

void SymTable_map(SymTable_T oSymTable, void(*pfApply)
                  (const char *pcKey, void *pvValue, void *pvExtra),
                  const void *pvExtra){
   struct Node *p;
   assert(oSymTable != NULL && pfApply != NULL);
   /*if (oSymTable == NULL || pfApply == NULL){
     return NULL}*/

   for (p = oSymTable->first; p != NULL; p = p->next){
      if (p->next != NULL){
         (*pfApply)(p->key, p->value, (void*)pvExtra);
      }
   }
}
