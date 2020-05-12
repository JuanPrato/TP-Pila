#include "pila.h"
#include "testing.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


bool desapilar_pruebas(const size_t veces ,pila_t *pila){

    for(int i = 0; i < veces; i++){
        void* valor = pila_ver_tope(pila);

        void* valor_desapilado = pila_desapilar(pila);

        if(valor != valor_desapilado){
            return false;
        }
    }
    return true;
}
//Funcion que apilar un numero determinado de veces y se le puede pasar parametros 
// para que apile y desapile, apile o solamente desapile
bool apilar_pruebas(const size_t veces, pila_t *pila,const bool apilar,const bool desapilar){
    if(apilar){
        for(int i = 0; i < veces / 2; i++){
            int* valor = malloc(sizeof(int));
            if(!pila_apilar(pila, valor)){
                free(valor);
                return false;
            }
            void* tope = pila_ver_tope(pila);
            if(tope != valor){
                free(valor);
                return false;
            }
            char* valor2 = malloc(sizeof(char));
            if(!pila_apilar(pila, valor2)){
                free(valor2);
                return false;
            }
            tope = pila_ver_tope(pila);
            if(tope != valor2){
                free(valor2);
                return false;
            }
            free(valor);
            free(valor2);
        }
    }

    if(desapilar){
        return desapilar_pruebas(veces, pila);
    }
    return true;
}

bool iniciar_pila_prueba(){

    pila_t* pila = pila_crear();

    if(!pila){
        return false;
    }

    pila_destruir(pila);

    return true;
}

bool mantener_invariante_prueba(){

    bool retorno = true;

    pila_t* pila = pila_crear();

    if((!apilar_pruebas( 5, pila, true, true)) && retorno ){
        retorno = false;
    }
    if((!apilar_pruebas( 5, pila, true, false )) && retorno ){
        retorno = false;
    }
    pila_destruir(pila);

    return retorno;
}

bool prueba_volumen(){

    bool retorno = true;
    pila_t* pila = pila_crear();

    if((!apilar_pruebas( 100, pila, true, true )) && retorno ){
        retorno = false;
    }
    if((!apilar_pruebas( 1000, pila, true, true )) && retorno ){
        retorno = false;
    }
    if((!apilar_pruebas( 10000, pila, true, true )) && retorno){
        retorno = false;
    }

    pila_destruir(pila);

    return retorno;
}

bool apilar_null(){
    pila_t* pila = pila_crear();

    bool retorno = pila_apilar(pila,NULL);

    pila_destruir(pila);

    return retorno;
}

bool pruebas_pila_vacia(pila_t* pila){

    if(!pila){
        return false;
    }

    if(!pila_esta_vacia(pila) || pila_desapilar(pila) || pila_ver_tope(pila)){
        return false;
    }

    return true;
}

bool pruebas_pila_recien_creada(){
    bool retorno;
    pila_t* pila = pila_crear();

    retorno = pruebas_pila_vacia(pila);

    pila_destruir(pila);

    return retorno;
}

bool pruebas_pila_vaciada(){
    bool retorno;
    pila_t* pila = pila_crear();

    if(!apilar_pruebas(10, pila, true,true)){
        return false;
    }

    retorno = pruebas_pila_vacia(pila);

    pila_destruir(pila);

    return retorno;
}

bool prueba_guardado(){
    bool retorno = true;
    pila_t* pila = pila_crear();

    if(!pila){
        return false;
    }

    void** vectorDatos = malloc(sizeof(void*) * 10);

    if(!vectorDatos){
        pila_destruir(pila);
        return false;
    }

    for(int i = 0; i<10; i++){
        int* dato = malloc(sizeof(int));
        vectorDatos[i] = (void*)dato;
        pila_apilar(pila,dato);
    }

    for(int i = 9; i >= 0; i--){
        void* dato = pila_desapilar(pila);
        if( dato != vectorDatos[i]){
            retorno = false;
        }
    }

    for(int i = 0; i<10;i++){
        free(vectorDatos[i]);
    }

    free(vectorDatos);

    pila_destruir(pila);
    return retorno;
}

void pruebas_pila_alumno() {

    print_test("Incializar una pila vacia y se destruye", iniciar_pila_prueba());

    print_test("Al desapilar se mantiene la invariante", mantener_invariante_prueba());

    print_test("Prueba de volumen", prueba_volumen());

    print_test("Apilar NULL", apilar_null());

    print_test("Todo lo ingresado se guarda correctamete", prueba_guardado());

    //CONDICIONES DE BORDE
    print_test("condiciones borde: pila vacia", pruebas_pila_recien_creada());

    print_test("Condiciones de borde: pila vaciada", pruebas_pila_vaciada());
}