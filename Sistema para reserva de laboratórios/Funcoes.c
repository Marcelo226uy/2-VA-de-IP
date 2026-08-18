#include <stdio.h>
#include "codigoBase.h"
#include "Funcoes.h"

int cadastrarLaboratorio(void) {
    // ESTRUTURA DE LABORATORIO
    // typedef struct {
    //     int id; 
    //     char nome[64];
    //     int capacidade;
    //     char equipamentos[256]; // texto informativo
    //     StatusLab status;
    // } Laboratorio;


    // ESTRUTURA DE STATUSLAB
    // typedef enum {
    //     LAB_ATIVO = 1,
    //     LAB_INDISPONIVEL = 0 // manutenção, bloqueio, etc.
    // } StatusLab;

    Laboratorio lab;

    printf("Insira o ID:\n");
    scanf("%d", &lab.id);

    printf("Insira o nome do lab:\n");
    scanf("%s", &lab.nome);

    printf("Insira a capacidade:\n");
    scanf("%d", &lab.capacidade);

    printf("Insira uma descrição do lab:\n");
    scanf("%s", &lab.equipamentos);

    do {
        printf("Insira a situação do lab: [1] Ativo / [0] Inativo\n");
        scanf("%d", (int *)&lab.status);
    } while (lab.status != LAB_ATIVO && lab.status != LAB_INDISPONIVEL);

    return 0;
}
