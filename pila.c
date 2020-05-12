#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define CAPACIDAD_INICIAL 10

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

enum operaciones {AUMENTAR, REDUCIR};

bool redimensionar_pila(pila_t *pila, enum operaciones operacion, size_t factor){

    size_t nueva_capacidad = (operacion ? (pila->capacidad / factor) : (pila->capacidad * factor));
    void** auxiliar = realloc(pila->datos, sizeof(void*) * nueva_capacidad);
    if(auxiliar == NULL ){
        return false;
    }
    pila->datos = auxiliar;
    pila->capacidad = nueva_capacidad;
    return true;
}

pila_t* pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));
    if( pila == NULL ){
        return NULL;
    }
    pila->datos = malloc(sizeof(void*) * CAPACIDAD_INICIAL);
    if(pila->datos == NULL){
        free(pila);
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = CAPACIDAD_INICIAL;
    return pila;
}

void pila_destruir(pila_t *pila){
    free( pila->datos );
    free( pila );
}

bool pila_esta_vacia(const pila_t *pila){
    return !pila->cantidad;
}

bool pila_apilar(pila_t *pila, void* valor){
    
    if( pila->capacidad <= pila->cantidad ){
        bool redimensiono = redimensionar_pila(pila, AUMENTAR, 2);
        if(!redimensiono){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad += 1;
    return true;
}

void* pila_ver_tope(const pila_t *pila){
    if( pila->cantidad == 0 ){
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){

    if(pila->cantidad == 0){
        return NULL;
    }
    void* dato = pila->datos[pila->cantidad - 1];
    pila->cantidad = pila->cantidad -1;
    if( (pila->cantidad <= (pila->capacidad) / 4) && ( pila->capacidad > CAPACIDAD_INICIAL ) ){
        redimensionar_pila(pila, REDUCIR, 2);
    }
    return dato;
}