#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"

// void cadastrarReserva(Data *prt){
//     printf("Defina o dia, mês e ano para sua reserva.\n");
//     scanf("%d %d %d", &prt->dia, &prt->mes, &&prt->ano);
    
// }



int cadastrarLaboratorio(Laboratorio *lab, VetLaboratorios *vetLab) {
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


    // Leitura de informações
    printf("Insira o ID:\n");
    scanf("%d", &lab->id);

    printf("Insira o nome do lab:\n");
    scanf("%s", lab->nome);

    printf("Insira a capacidade:\n");
    scanf("%d", &lab->capacidade);

    printf("Insira uma descrição do lab:\n");
    scanf("%s", lab->equipamentos);

    do {
        printf("Insira a situação do lab: [1] Ativo / [0] Inativo\n");
        scanf("%d", (int *)&lab->status);
    } while (lab->status != LAB_ATIVO && lab->status != LAB_INDISPONIVEL);

    return 0;
}

void alocarMemoriaVetLaboratorios(VetLaboratorios *vetLab) {
    vetLab->itens = realloc(vetLab, (vetLab->cap + 5) * sizeof(Laboratorio));
    vetLab->cap += 5;
}

void retirarMemoriaVetLaboratorios(VetLaboratorios *vetLab) {
    vetLab->itens = realloc(vetLab, (vetLab->cap - 5 * sizeof(Laboratorio)));
    vetLab->cap -= 5;
}

void verificarMemoriaVetLaboratorios(VetLaboratorios *vetLab) {
    if (vetLab->cap - vetLab->qtd <= 1) { // pouca memória
        alocarMemoriaVetLaboratorios(vetLab);
    } else if (vetLab->cap - vetLab->qtd >= 10) { // muita memória
        retirarMemoriaVetLaboratorios(vetLab);
    }
}
