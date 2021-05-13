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
	uint32_t index = (uint32_t)(hash & (uint64_t) (m - 1));

	while(e[index].key != NULL){
	    if(strcmp(k, e[index].key) == 0){
	        e[index].item = v;
	        return e[index].key;
	    }

	    index++;
	    if(index >= m){
	        index = 0;
	    }
	}

	if(l != NULL){
	    k = strdup(k);
	    if(k == NULL){
	        return NULL;
	    }
        (*l)++;
	}

	e[index].key = (char*) k;
	e[index].item = v;
	return k;
}

/**
 *
 * @param t
 * @return
 */
int expandTab(Table *t) {
    //TODO: maybe change this to actual boolean values
	uint32_t newMaxCap = t->maxCap * 2;

	if(newMaxCap < t->maxCap){
	    return 0;
	}
    entries * newEntries = calloc(newMaxCap, sizeof(entries));

	if(newEntries == NULL){
	    return 0;
	}

    for (int i = 0; i < t->maxCap; i++) {
        entries entryCopy = t->items[i];
        if(entryCopy.key != NULL){
            setEntryTable(newEntries, newMaxCap, entryCopy.key, entryCopy.item, NULL);
        }
    }
    free(t->items);
    t->items = newEntries;
    t->maxCap = newMaxCap;
	return 1;
}

/**
 *
 * @return
 */
static int tableLength(Table* t){
    return t->currLen;
}

/**
 *
 * @return
 */
TableIter tableIterator(Table * t){
    TableIter toRet;
    toRet.table = t;
    toRet.index = 0;
    return toRet;
}

/**
 *
 * @return
 */
static int tableNextEntry(TableIter * ti){
    Table * t = ti->table;
    while (ti->index < t->currLen){
        uint32_t i = ti->index;
        ti->index++;
        if (t->items[i].key != NULL){
            entries entry = t->items[i];
            ti->key = entry.key;
            ti->item = entry.item;
            return 1;
        }
    }
    return 0;
}
