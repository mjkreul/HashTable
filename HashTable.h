#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#define INIT_CAP 16
#define FNV_OFFSET_BASIS 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * Entries in the Hash table.  Each one contains a key and a value associated with it.  These are stored in a Table
 * struct.
 */
typedef struct entry_t{
	/**
	 *
	 */
	char * key;
	/**
	 *
	 */
	void * item;
}entries;


/**
 * Table
 */
typedef struct Table_t {
	/**
	 *
	 */
	entries * items;
	/**
	 *
	 */
	 uint32_t maxCap;
	/**
	 *
	 */
	uint32_t currLen;
}Table;

/**
 *
 */
typedef struct TableIter_t{
	/**
	 *
	 */
	char * key;
	/**
	 *
	 */
	void * item;
	/**
	 *
	 */
	Table * table;
	/**
	 *
	 */
	uint32_t index;
}TableIter;

/**
 *
 * @return
 */
Table * createTable();

/**
 *
 */
void freeTable(Table *);

/**
 *
 * @return
 */
void * getItem(Table *, const char *);

/**
 *
 * @return
 */
const char * setItem(Table *, const char *, void * );



/**
 *
 */
static uint64_t hashKey(const char *);

/**
 *
 */
static const char * setEntryTable(entries * , uint32_t , const char* , void* , uint32_t * );

/**
 *
 * @return
 */
static int expandTab(Table* );

/**
 *
 * @return
 */
static int tableLength(Table* );

/**
 *
 * @return
 */
TableIter tableIterator(Table * );

static int tableNextEntry(TableIter *);


#endif //HASHTABLE_HASHTABLE_H
