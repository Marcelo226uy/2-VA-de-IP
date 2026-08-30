#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"


void menuLaboratorios(VetLaboratorios *laboratorios) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("       GERENCIAR LABORATORIOS       \n");
        printf("====================================\n");
        printf("1 - Inserir laboratorio\n");
        printf("2 - Listar laboratorios\n");
        printf("3 - Atualizar laboratorio\n");
        printf("4 - Remover laboratorio\n");
        printf("0 - Voltar\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
//              inserirLaboratorio(laboratorios);
                break;

            case 2:
            //listarLaboratorios(laboratorios);
                break;

            case 3:
           //     atualizarLaboratorio(laboratorios);
                break;

            case 4:
           //     removerLaboratorio(laboratorios);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}


void menuReservas(VetReservasLab *reservas,
                  VetLaboratorios *laboratorios) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("          GERENCIAR RESERVAS        \n");
        printf("====================================\n");
        printf("1 - Inserir reserva\n");
        printf("2 - Listar reservas\n");
        printf("3 - Atualizar reserva\n");
        printf("4 - Remover reserva\n");
        printf("5 - Relatorio por data\n");
        printf("0 - Voltar\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarReserva(reservas, laboratorios);
                break;

            case 2:
                listarReservas(reservas, laboratorios);
                break;

            case 3:
                atualizarReserva(reservas, laboratorios);
                break;

            case 4:
                removerReserva(reservas);
                break;

            case 5:
                relatorioPorData(reservas, laboratorios);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}


int main() {
    VetLaboratorios laboratorios;
    VetReservasLab reservas;
    int opcao;

//    inicializarLaboratorios(&laboratorios);
    inicializarReservas(&reservas);

//    carregarLaboratorios(&laboratorios);
    carregarReservas(&reservas);

    do {
        printf("\n============================================\n");
        printf("      SISTEMA DE RESERVA DE LABORATORIOS    \n");
        printf("============================================\n");

        printf("Laboratorios cadastrados: %d\n", laboratorios.qtd);
        printf("Reservas cadastradas: %d\n", reservas.qtd);

        printf("\n");
        printf("1 - Gerenciar laboratorios\n");
        printf("2 - Gerenciar reservas\n");
        printf("3 - Listar laboratorios\n");
        printf("4 - Listar reservas\n");
        printf("5 - Relatorio por data\n");
        printf("0 - Sair\n");

        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuLaboratorios(&laboratorios);
                break;

            case 2:
                menuReservas(&reservas, &laboratorios);
                break;

            case 3:
                listarLaboratorios(&laboratorios);
                break;

            case 4:
                listarReservas(&reservas, &laboratorios);
                break;

            case 5:
                relatorioPorData(&reservas, &laboratorios);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

//    liberarLaboratorios(&laboratorios);
    liberarReservas(&reservas);

    return 0;
}