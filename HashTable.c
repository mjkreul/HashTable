#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 *
 * @return
 */
Table * createTable(){
	//INIT the table and make sure it initialized correctly
	Table * table = (Table*) malloc(sizeof(Table ));
	if(table == NULL)return NULL;
	
	//Set initial values for everything
	table->currLen = 0;
	table->maxCap = INIT_CAP;
	
	//Initialize the items array to 16 and if it doesn't work, free everything
	table->items = calloc(table->maxCap, sizeof(entries));
	if(table->items == NULL){
//		free(table->items);
		free(table);
		return NULL;
	}
	//return the table
	return table;
}

/**
 *
 */
void freeTable(Table * t){
	for(int i = 0; i < t->maxCap; i++){
		if(t->items[i].key != NULL){
			free(t->items[i].key);
		}
	}
	
	free(t->items);
	free(t);
}

/**
 *
 * @return
 */
void * getItem(Table * t , const char * k){
	
	uint64_t hash = hashKey(k);
	int index = (int) (hash & (uint64_t)(t->maxCap - 1));
	while(t->items[index].key != NULL){
		if(strcmp(t->items[index].key, k) == 0){
			return t->items[index].item;
		}
		index++;
		if(index >= t->maxCap){
			index = 0;
		}
	}
	return NULL;
}

/**
 *
 * @return
 */
const char * setItem(Table * t, const char * k, void * v){
	assert(v != NULL);
	
	if(v == NULL){
		return v;
	}
	
	if(t->currLen >= (t->maxCap/2)){
		if(!expandTab(t)) return NULL;
	}
	
	
	return setEntryTable(t->items, t->maxCap, k, v, &t->currLen);
}

/**
 *
 * @return
 */
TableIter * tableIterator(Table * t){
	return NULL;
}

/**
 * Uses the FNV-1 Algorithm.
 * @return
 */
static uint64_t hashKey(const char * k){
	//Set the hash
	uint64_t hash = FNV_OFFSET_BASIS;
	//For every char in the key
	for(int i = 0; i < strlen(k); i++){
		char charCode = k[i];
		//Multiply by the prime which will cause some wrapping
		hash*=FNV_PRIME;
		//XOR the bits of the char and the new hash
		hash = (hash ^ (uint64_t)(unsigned char)charCode);
	}
	return hash;
}


static const char * setEntryTable(entries * e, uint32_t m, const char* k, void* v, uint32_t * l){
	uint64_t hash = hashKey(k);
	uint32_t index = (uint32_t)(hash & (uint64_t) m);
	
	
	
	return NULL;
}

int expandTab(Table *t) {
	
	return 0;
}
