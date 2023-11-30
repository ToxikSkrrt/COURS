#include "distributeur.h"
#include <stdlib.h>
#include <pthread.h>

struct distributeur
{
    pthread_mutex_t mutex;
    int indice;
};

distributeur_t distributeur_new()
{
    distributeur_t d = calloc(1, sizeof(struct distributeur));
    pthread_mutex_init(&d->mutex, NULL);

    return d;
}

int distributeur_suivant(distributeur_t d)
{
    int ret;

    pthread_mutex_lock(&d->mutex);

    ret = d->indice++;

    pthread_mutex_unlock(&d->mutex);

    return ret;
}

int distributeur_valeur(distributeur_t d)
{
    return d->indice;
}

void raz(distributeur_t d)
{
    d->indice = 0;
}