/*symtable.h; defines all of the functions for the symtable*/

#ifndef SYMTABLE
#define SYMTABLE
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct SymTable *SymTable_T;

/*input is void, returns a new SymTable object that contains no 
  bindings, or NULL if insufficient memory is available */
SymTable_T SymTable_new(void);

/*input is a SymTable; frees the memory taken up by that SymTable and
   returns nothing*/
void SymTable_free(SymTable_T oSymTable);

/*input is a SymTable; returns a size_t that corresponds with the
   number of findings in the table*/
size_t SymTable_getLength(SymTable_T oSymTable);

/*input is a Symtable; returns 1 if a new binding is added, or a 0 if
  a new binding is not added*/
int SymTable_put(SymTable_T oSymTable,
   const char *pcKey, const void *pvValue);

/*inputs are a Symtable, a key*/
void *SymTable_replace(SymTable_T oSymTable,
                       const char *pcKey, const void *pvValue);

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

void SymTable_map(SymTable_T oSymTable,
                  void (*pfApply)(const char *pcKey, void *pvValue,
                                  void *pvExtra), const void *pvExtra);
#endif
