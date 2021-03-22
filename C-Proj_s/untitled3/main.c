#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

struct rec *head = NULL;
struct rec {
    struct rec *next;
    int i;
};

int done = 0;
pthread_cond_t cond;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void add_to_list(struct rec **head_ptr, int i) {
    struct rec *node = malloc(sizeof(struct rec));
    node->i = i;
    pthread_mutex_lock(&mutex);
    node->next = *head_ptr;
    *head_ptr = node;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void print_list(struct rec *head) {
    while(head != NULL) {
        printf("%d\n", head->i);
        head = head->next;
    }
}

void *adders(void *v) {
    for (int i = 0; i < 100000; i++) {
        add_to_list(&head, i);
    }
}

void *totallers(void *v) {
    long long total = 0;
    pthread_mutex_lock(&mutex);
    while (!done || head != NULL) {
        if (head != NULL) {
            total += head->i;
            head = head->next;
        } else {
            pthread_cond_wait(&cond, &mutex);
        }
    }
    pthread_mutex_unlock(&mutex);
    printf("total is %lld\n", total);
}

int main() {
    pthread_cond_init(&cond, NULL);
    pthread_t a[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&a[i], NULL, adders, NULL);
    }

    pthread_t t[1];
    for (int i = 0; i < 1; i++) {
        pthread_create(&t[i], NULL, totallers, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(a[i], NULL);
    }

    pthread_mutex_lock(&mutex);
    done = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_join(t[0], NULL);
    return 0;
}
