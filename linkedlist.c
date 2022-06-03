/** 
	Linked list implementation. 
*/
#include "linkedlist.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void print(struct linkedlist_t *l){
	if(l == NULL){
		printf(" ");
		return;
	}
	printf("data_sz %d\n", l->data_sz);
	printf("length %d\n", l->length);
	printf("max_length %d\n", l->max_length);
	//printf("alo\n");
	struct linkedlist_node_t* head = l->first;
	while(head != NULL){
		printf("%d ", *(int*)head->data);
		head = head->next;
	}

}

struct linkedlist_node_t *linkedlist_insert_node(struct linkedlist_node_t *l, void *e, unsigned int datasize){
	struct linkedlist_node_t *aux=(struct linkedlist_node_t *) malloc(sizeof(struct linkedlist_node_t));
	aux->next = l;
	aux->data = (void*)malloc(sizeof(e)*datasize);
	aux->data = e;
	return aux;
}

/**
 * @brief Create a new linked list.
 * 
 * @param sz Size of the data.
 * @return Pointer to the list descriptor.
 */
 
struct linkedlist_t *linkedlist_create(unsigned int sz, unsigned int max_length){
	struct linkedlist_t *descriptor = (struct linkedlist_t *) malloc(sizeof(struct linkedlist_t));
	descriptor->first = NULL;
	descriptor->last = NULL;
	descriptor->length = 0;
	descriptor->data_sz = sz;
	descriptor->max_length = max_length;
	return descriptor;
}


/**
 * @brief Insert new element to the end of the list.
 * 
 * @param l Pointer to the list.
 * @param e Element to be inserted (copied) in the list.
 *
 * 
 */
void linkedlist_insert_tail(struct linkedlist_t *l, void *e){
	if(l == NULL)
		return;
	
	l->last->next = linkedlist_insert_node(l->last->next, e, l->data_sz); // é inserido um elemento no final da lista
	l->last = l->last->next; // faz o ponteiro last apontar para o novo elemento inserido
	l->length++;
}

/**
 * @brief Insert new element to the head of the list.
 * 
 * @param l Pointer to the list descriptor.
 * @param e Element to be inserted (copied) in the list.
 *
 * 
 */
void linkedlist_insert_head(struct linkedlist_t *l, void *e){
	if (l==NULL) return;
	l->first = linkedlist_insert_node(l->first, e, l->data_sz);
	if (l->first != NULL) l->length++;
	if(l->length == 1) l->last = l->first; // se o tamanho da lista for 1 entao a cabeça e a cauda apontam para o mesmo endereço
}

// como estou usando a função somente nesse arquivo, não preciso declarar seu cabeçalho no .h
struct linkedlist_node_t * node_anterior_last(struct linkedlist_node_t *l, struct linkedlist_node_t *last){
	// percorre até o penúltimo elemento
	while(l->next != last)
		l = l->next;
	return l; // retorna o penúltimo elemento
}

/**
 * @brief Remove element from the end of the list.
 * 
 * @param l Pointer to the list descriptor.
 * @param e Pointer to the memory do receive the element in data. 
 *
 */
void linkedlist_remove_tail(struct linkedlist_t *l, void *e){
	if(l == NULL || l->first == NULL)
		return;
	struct linkedlist_node_t* tail = l->last;
	struct linkedlist_node_t* anterior = node_anterior_last(l->first, l->last); // penultimo elemento da lista
	l->last = anterior; // como vou remover o último elemento, o penúltimo se torna o último elemento
	anterior->next = tail->next; // como agr ele é o último, ele precisa apontar onde o último apontava, nesse caso vai ser sempre NULL
	e = &(tail->data); // guardo o dado que o último elemento estava armazenando
	l->length--; // diminui o tamanho da lista
	free(tail); // libera a memória onde o último nó estava armazenado
}

/**
 * @brief Remove element from the head of the list.
 * 
 * @param l Pointer to the list descriptor.
 * @param e Pointer to the memory do receive the element in data. 
 *
 */
void linkedlist_remove_head(struct linkedlist_t *l, void *e){
	if(l == NULL || l->first == NULL)
		return;

	struct linkedlist_node_t* head = l->first; // variável temporária para guardar a referência da cabeça
	l->first = l->first->next; // a nova cabeça agora é o próximo nó da cabeça atual
	e = &(l->first->data); // guardo o dado que o último elemento estava armazenando
	l->length--; // diminui o tamnanho da lista
	free(head); // libera a memória onde a cabeça estava armazenado
}

/**
 * @brief Return the list length. 
 * 
 * @param l Pointer to the list descriptor.
 *
 * @return Number of elements in the list.
 */
int linkedlist_size(struct linkedlist_t *l){
	return l->length;
}


/**
 * @brief Remove all elements of the list and free it.
 * 			Make sure no threads are using the list.  
 * 
 * @param l Pointer to the list.
 */
void linkedlist_destroy(struct linkedlist_t **l){
	// laço para percorrer todos os elementos da lista
	for(int i = 0; i< (*l)->length;i++){
		struct linkedlist_node_t* temp = (*l)->first; // guarda o nó que vai ser liberado a memória alocada
		(*l)->first = (*l)->first->next; // vai para o próximo que será liberado
		free(temp); // libera o nó que foi armazenado em temp
	}
	free(*l); // libera a memória alocada para o descriptor
	*l = NULL; // descriptor aponta para NULL
}




///
///
///
///



pthread_mutex_t m1,m2,m3;

	int idade;
void * th1(){
	int cont=0;

	while(1 && cont<2){
		pthread_mutex_lock(&m1);
		printf("digite sua idade:\n");
		scanf("%d", &idade);
		if(idade<18){
			printf("voce ainda eh um jovem seboso\n");
			fflush(stdout);
			sleep(1);
			pthread_mutex_unlock(&m2);
		}else{
			printf("voce nao eh mais seboso\n");
			
		}
		
		
		cont++;
	}
}

void * th2(){
	int cont=0;
	while(1 && a<(18-idade)){
		pthread_mutex_lock(&m2);
		printf("Mais um ano se passa\n");
		fflush(stdout);
		sleep(2);
		idade++;		
		
		pthread_mutex_unlock(&m1);
		
		cont++;
	}
}


int threadTest(){

	pthread_t thread1, thread2, thread3;
	pthread_mutex_init(&m1,NULL);
	pthread_mutex_init(&m2,NULL);
	//pthread_mutex_init(&m3,NULL);
	
	pthread_mutex_lock(&m2);
	//pthread_mutex_lock(&m3);
	

		
		if(pthread_create(&thread1, NULL, th1, NULL)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
		}

		if(pthread_create(&thread2, NULL, th2, NULL)) {
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}

		

		if(pthread_join(thread1, NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 1;
		}	
}


int main(){

	printf("Digite o primeiro valor a: ");
	int a;
	scanf("%d", &a);
	printf("\nDigite o segundo valor b: ");
	int b;
	scanf("%d", &b);
	printf("\nDigite o terceiro valor c: ");
	int c;
	scanf("%d", &c);
	printf("\nDigite o quarto valor d: ");
	int d;
	scanf("%d", &d);

	struct linkedlist_t *descriptor = NULL;
	


	descriptor = linkedlist_create(3, 4);
	//linkedlist_insert_head(descriptor, threadTest());
				
	//switch case 
	//opcao1:1 thread conta ate o valor a, depois ate o valor b, ate o valor c, ate o valor d; outra thread calcula a multiplicacao dos valores entre si
	//opcao2:1 thread conta ate o valor a, depois ate o valor b, ate o valor c, ate o valor d; outra thread calcula a multiplicacao dos valores entre si
	
	
	int q;
	do {
        printf("\n\nOpcoes: \n1 -> para inserir novo produto;\nL -> para listar os produtos; \nS -> para sair \n:");
        
        
        scanf("%d", &q);     /* Le a opcao do usuario */
        switch(q) {
            case 1: linkedlist_insert_head(descriptor, threadTest(&a); break;
            case 2: linkedlist_insert_head(descriptor, &b);; break;
            case 3: linkedlist_insert_head(descriptor, &c);; break;
            case 4: linkedlist_insert_head(descriptor, &d);; break;                        
            case 's': case 'S': break;
            default: printf("\n\n Opcao nao valida");
        }
        fflush(stdin);    /* Limpa o buffer de entrada */
    	} while ((q != 's') && (q != 'S') );
	//linkedlist_insert_tail(descriptor, &a);
	//linkedlist_insert_tail(descriptor, &b);
	//linkedlist_insert_tail(descriptor, &c);
	//linkedlist_insert_tail(descriptor, &d);
	//linkedlist_insert_head(descriptor,SemapthThread());
	
	int value=0;

	print(descriptor);
	linkedlist_remove_tail(descriptor, &value); //descriptor, &valor
	linkedlist_destroy(&descriptor);
	print(descriptor);
	free(descriptor);
	
	//return 0;
	//printf("bananinha4");
	//threadTest();
	
}
