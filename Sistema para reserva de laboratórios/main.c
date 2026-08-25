#include <stdio.h>
#include "Funcoes.h"

int main(void){

    // ESTRUTURA DE VETLABORATORIOS
    // typedef struct {
    //     Laboratorio *itens;
    //     int qtd, cap;
    // } VetLaboratorios;

    int 
    cadastrarLaboratorio();

    VetReservasLab reservas;

    inicializarReservas(&reservas);

    cadastrarReserva(&reservas);

    free(reservas.itens);


    return 0;
}
