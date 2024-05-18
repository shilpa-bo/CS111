#include "hash-table-base.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include <pthread.h>
// static pthread_mutex_t hash_lock[HASH_TABLE_CAPACITY];


struct list_entry {
	const char *key;
	uint32_t value;
	SLIST_ENTRY(list_entry) pointers;
};

SLIST_HEAD(list_head, list_entry);

//struct of each entry, each entry has a list_head, and a hash lock
struct hash_table_entry {
	struct list_head list_head;
	pthread_mutex_t hash_lock;
};

//we have hash_table_capacity many of these entries 
struct hash_table_v2 {
	struct hash_table_entry entries[HASH_TABLE_CAPACITY];
};

//creating the hash tbale, we declare and initialize each entry with a block for the hash table 
struct hash_table_v2 *hash_table_v2_create()
{
	struct hash_table_v2 *hash_table = calloc(1, sizeof(struct hash_table_v2));
	assert(hash_table != NULL);

	for (size_t i = 0; i < HASH_TABLE_CAPACITY; ++i) { //we can create locks here 
		struct hash_table_entry *entry = &hash_table->entries[i];
		SLIST_INIT(&entry->list_head);
		//creating a mutex per hash table bucket
		if (pthread_mutex_init(&entry->hash_lock, NULL) != 0) {
			free(hash_table); //do i need to do this?
            perror("pthread_mutex_init");
            exit(EXIT_FAILURE);
        }
	}
	return hash_table;
}

static struct hash_table_entry *get_hash_table_entry(struct hash_table_v2 *hash_table,
                                                     const char *key)
{
	assert(key != NULL);
	uint32_t index = bernstein_hash(key) % HASH_TABLE_CAPACITY;
	struct hash_table_entry *entry = &hash_table->entries[index];
	return entry;
}

static struct list_entry *get_list_entry(struct hash_table_v2 *hash_table,
                                         const char *key,
                                         struct list_head *list_head)
{
	assert(key != NULL);

	struct list_entry *entry = NULL;
	
	SLIST_FOREACH(entry, list_head, pointers) {
	  if (strcmp(entry->key, key) == 0) {
	    return entry;
	  }
	}
	return NULL;
}

bool hash_table_v2_contains(struct hash_table_v2 *hash_table,
                            const char *key)
{
	struct hash_table_entry *hash_table_entry = get_hash_table_entry(hash_table, key);
	struct list_head *list_head = &hash_table_entry->list_head;
	struct list_entry *list_entry = get_list_entry(hash_table, key, list_head);
	return list_entry != NULL;
}

void hash_table_v2_add_entry(struct hash_table_v2 *hash_table,
                             const char *key,
                             uint32_t value)
{

//the goal is to lock each bucket so only one thread can access a specific bucket at a time
//race conditions occur when multiple threads are trying to access the SAME bucket at at time 
	struct hash_table_entry *hash_table_entry = get_hash_table_entry(hash_table, key);
	//lock here once you get the hash_table_entry?- each hash table entry has its own lock
	if (pthread_mutex_lock(&hash_table_entry->hash_lock)!=0){
		exit(EXIT_FAILURE);
	}
	struct list_head *list_head = &hash_table_entry->list_head;
	struct list_entry *list_entry = get_list_entry(hash_table, key, list_head);
	/* Update the value if it already exists */
	if (list_entry != NULL) {
		list_entry->value = value;
		return;
	}

	list_entry = calloc(1, sizeof(struct list_entry));
	list_entry->key = key;
	list_entry->value = value;
	SLIST_INSERT_HEAD(list_head, list_entry, pointers);
	if (pthread_mutex_unlock(&hash_table_entry->hash_lock)!=0){
		exit(EXIT_FAILURE);
	}
}

uint32_t hash_table_v2_get_value(struct hash_table_v2 *hash_table,
                                 const char *key)
{
	struct hash_table_entry *hash_table_entry = get_hash_table_entry(hash_table, key);
	struct list_head *list_head = &hash_table_entry->list_head;
	struct list_entry *list_entry = get_list_entry(hash_table, key, list_head);
	assert(list_entry != NULL);
	return list_entry->value;
}

void hash_table_v2_destroy(struct hash_table_v2 *hash_table)
{
	// if (pthread_mutex_destroy(&hash_lock)!=0){ //don't really get how to know which exit calls to use
	// 	exit(-1);
	// }
	for (size_t i = 0; i < HASH_TABLE_CAPACITY; ++i) {
		struct hash_table_entry *entry = &hash_table->entries[i];
		struct list_head *list_head = &entry->list_head;
		struct list_entry *list_entry = NULL;
		while (!SLIST_EMPTY(list_head)) {
			list_entry = SLIST_FIRST(list_head);
			SLIST_REMOVE_HEAD(list_head, pointers);
			free(list_entry);
		}
		if(pthread_mutex_destroy(&entry->hash_lock)!=0){
			perror("pthread_mutex_destroy");
			// exit(EXIT_FAILURE); //do we exit here or not??
		}

	}
	free(hash_table);
}
