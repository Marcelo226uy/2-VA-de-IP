#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"

int main(void){
    Laboratorio *lab = malloc(5 * sizeof(Laboratorio));

    // ESTRUTURA DE VETLABORATORIOS
    // typedef struct {
    //     Laboratorio *itens;
    //     int qtd, cap; -> capacidade de 5 em 5 itens
    // } VetLaboratorios;
    VetLaboratorios vetLab;

    vetLab.itens = lab;
    vetLab.qtd = 0;
    vetLab.cap = 5;

    cadastrarLaboratorio(lab, &vetLab);
    cadastrarLaboratorio(lab, &vetLab);
    cadastrarLaboratorio(lab, &vetLab);

    listarLaboratorios(&vetLab);

    removerLaboratorio(&vetLab);

    listarLaboratorios(&vetLab);

    // VetReservasLab reservas;

    // inicializarReservas(&reservas);

    // cadastrarReserva(&reservas);

    // free(reservas.itens);


    return 0;
}
