#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"

void menuLaboratorios(VetLaboratorios *laboratorios) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("       GERENCIAR OS LABORATÓRIOS       \n");
        printf("====================================\n");
        printf("1 - Cadastrar laboratório\n");
        printf("2 - Listar laboratórios\n");
        printf("3 - Atualizar laboratório\n");
        printf("4 - Remover laboratório\n");
        printf("0 - Voltar\n");
        printf("Opção: ");

        if (!lerInteiro(&opcao)) {
            printf("Opção inválida. Digite um número.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarLaboratorio(laboratorios);
                break;

            case 2:
                listarLaboratorios(laboratorios);
                break;

            case 3:
                atualizarLaboratorio(laboratorios);
                break;

            case 4:
                removerLaboratorio(laboratorios);
                break;

            case 0:
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
}

void menuReservas(VetReservasLab *reservas, VetLaboratorios *laboratorios) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("        GERENCIAR AS RESERVAS        \n");
        printf("====================================\n");
        printf("1 - Cadastrar reserva\n");
        printf("2 - Listar reservas\n");
        printf("3 - Atualizar reserva\n");
        printf("4 - Remover reserva\n");
        printf("5 - Relatório por data\n");
        printf("0 - Voltar\n");
        printf("Opção: ");

        if (!lerInteiro(&opcao)) {
            printf("Opção inválida. Digite um número.\n");
            continue;
        }

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
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
}

int main(void) {
    VetLaboratorios laboratorios;
    VetReservasLab reservas;
    int opcao;

//  Inicializa os vetores
    inicializarLaboratorios(&laboratorios);
    inicializarReservas(&reservas);

//  Carrega reservas e laboratórios já existentes
    carregarLaboratorios(&laboratorios);
    carregarReservas(&reservas);

    do {
        printf("\n============================================\n");
        printf("      SISTEMA DE RESERVA DE LABORATÓRIOS    \n");
        printf("============================================\n");

        printf("Laboratórios cadastrados: %d\n", quantidadeLaboratorios(&laboratorios));

        printf("Reservas cadastradas: %d\n", quantidadeReservas(&reservas));

        printf("\n1 - Gerenciar laboratórios\n");
        printf("2 - Gerenciar reservas\n");
        printf("3 - Listar laboratórios\n");
        printf("4 - Listar reservas\n");
        printf("5 - Relatório por data\n");
        printf("0 - Sair\n");
        printf("Opção: ");

        if (!lerInteiro(&opcao)) {
            printf("\nOpção inválida! Digite um número.\n");
            continue;
        }

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
                printf("\nSistema Desligado");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

//  Salva os dados antes de encerrar.
    salvarLaboratorios(&laboratorios);
    salvarReservas(&reservas);

//  Libera a memória não utilizada
    liberarLaboratorios(&laboratorios);
    liberarReservas(&reservas);

    return 0;
}