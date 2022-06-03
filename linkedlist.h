#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/* pointer to the next list node */
struct linkedlist_node_t {
    struct linkedlist_node_t *next;
    void* data;             
};

/* Linked list descriptor (there is only one by list)*/
struct linkedlist_t{
	struct linkedlist_node_t *first; /* Pointer to the first node. */
	struct linkedlist_node_t *last; /* Pointer to the last node. */
	unsigned int length; /* Number of nodes in the list */
	unsigned int data_sz; /* Data size to be allocated in each node */
	unsigned int max_length;
	/* Place your sincronization primitives here */
};


/* Implement each one of this funcionalities */
struct linkedlist_t* linkedlist_create(unsigned int sz, unsigned int max_lengh);
void linkedlist_insert_tail(struct linkedlist_t *l, void *e);
void linkedlist_insert_head(struct linkedlist_t *l, void *e);
void linkedlist_remove_tail(struct linkedlist_t *l, void *e);
void linkedlist_remove_head(struct linkedlist_t *l, void *e);
int linkedlist_size(struct linkedlist_t *l);
void linkedlist_destroy(struct linkedlist_t **l);
struct linkedlist_node_t *linkedlist_insert_node(struct linkedlist_node_t *l, void *e, unsigned int datasize);
void print(struct linkedlist_t *l);
