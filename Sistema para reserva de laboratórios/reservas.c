#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservas.h"
#include "laboratorios.h"
#include "utils.h"

// Funções principais da Reserva
void cadastrarReserva(VetReservasLab *reservas, VetLaboratorios *vetLab) {

    if (vetLab->qtd == 0) {
        printf("\nNão existem laboratórios cadastrados, cadastre um laboratório antes de criar uma reserva.\n");
        return;
    }

    if (reservas->qtd == reservas->cap) {
        if (!aumentarCapacidadeReservas(reservas)) {
            return;
        }
    }

    ReservaLab nova;

    nova.id = proximoIdReserva(reservas);

//  Pessoa que tá solicitando
    do {

        printf("\nNome ou matrícula do solicitante: ");

        lerTexto(nova.solicitante, sizeof(nova.solicitante) );

        if (strlen(nova.solicitante) == 0) {
            printf("Campo obrigatório.\n");
        }
    } while (strlen(nova.solicitante) == 0);

//  Informações do laboratório

    listarLaboratorios(vetLab);

    while (1) {
        printf("ID do laboratório: ");

        if (!lerInteiro(&nova.idLaboratorio)) {
            printf("ID inválido.\n");
            continue;
        }

        int indiceLab = encontrarID(nova.idLaboratorio, vetLab);

        if (indiceLab == -1) {
            printf("Laboratório não encontrado.\n");
            continue;
        }

        if (vetLab->itens[indiceLab].status == LAB_INDISPONIVEL) {
            printf("Esse laboratório esta indisponível.\n");
            continue;
        }

        break;
    }

//  Informações da data
    while (1) {
        printf("\nData da reserva\n");

        printf("Dia: ");

        if (!lerInteiro(&nova.data.dia)) {
            printf("Valor inválido.\n");
            continue;
        }

        printf("Mês: ");

        if (!lerInteiro(&nova.data.mes)) {
            printf("Valor inválido.\n");
            continue;
        }

        printf("Ano: ");

        if (!lerInteiro(&nova.data.ano)) {
            printf("Valor inválido.\n");
            continue;
        }

        if (dataValida(&nova.data))
            break;

        printf("Data inválida! Utilize uma data válida de 2026.\n");
    }

//  Informação de horários
    while (1) {
        printf("\nHorário inicial\n");

        printf("Hora: ");

        if (!lerInteiro(&nova.inicio.hora)) {
            printf("Hora inválida.\n");
            continue;
        }

        printf("Minuto: ");

        if (!lerInteiro(&nova.inicio.minuto)) {
            printf("Minuto inválido.\n");
            continue;
        }

        if (horarioInicioValido(&nova.inicio))
            break;

        printf("Horário inicial inválido.\n");
    }

    while (1) {

        printf("\nHorário final\n");

        printf("Hora: ");

        if (!lerInteiro(&nova.fim.hora)) {
            printf("Hora inválida.\n");
            continue;
        }

        printf("Minuto: ");

        if (!lerInteiro(&nova.fim.minuto)) {
            printf("Minuto inválido.\n");
            continue;
        }

        if (horarioFinalValido(&nova.fim, &nova.inicio)) {

            break;
        }

        printf("Horário final inválido.\n");
    }

//  Verifivar se está disponível
    if (!verificarDisponibilidade(reservas, nova.idLaboratorio, nova.data, nova.inicio, nova.fim, -1)) {

        printf("\nO laboratório já esta reservado nesse horário.\n");
        return;
    }

    reservas->itens[reservas->qtd] = nova;

    reservas->qtd++;

    salvarReservas(reservas);

    printf("\nReserva realizada com sucesso!\n");
}

void listarReservas(VetReservasLab *reservas, VetLaboratorios *laboratorios) {
    if (reservas->qtd == 0) {
        printf("\nNenhuma reserva cadastrada.\n");
        return;
    }

    printf("\n========== RESERVAS ==========\n");

    for (int i = 0; i < reservas->qtd; i++) {

        ReservaLab *r = &reservas->itens[i];

        int indiceLab = encontrarID(r->idLaboratorio, laboratorios);

        printf("\nID da reserva: %d\n", r->id);

        printf("Solicitante: %s\n", r->solicitante);

        printf("Laboratório: ");

        if (indiceLab != -1) {
            printf("%s\n", laboratorios->itens[indiceLab].nome);
        } else {
            printf("Laboratório não encontrado\n");
        }

        printf("Data: %02d/%02d/%04d\n", r->data.dia, r->data.mes, r->data.ano);

        printf("Horário: %02d:%02d - %02d:%02d\n", r->inicio.hora, r->inicio.minuto, r->fim.hora, r->fim.minuto);
    }
}

void atualizarReserva(VetReservasLab *reservas, VetLaboratorios *laboratorios) {
    if (reservas->qtd == 0) {
        printf("\nNenhuma reserva cadastrada.\n");
        return;
    }

    int id;

    printf("\nID da reserva: ");

    if (!lerInteiro(&id)) {
        printf("ID invalido.\n");
        return;
    }

    int indice = buscarReservaPorId(reservas, id);

    if (indice == -1) {
        printf("A reserva não foi encontrada.\n");
        return;
    }

    // Isso cria uma cópia pra evitar perder a original caso algo falhe.
    ReservaLab nova = reservas->itens[indice];

    do {
        printf("\nNovo solicitante: ");

        lerTexto(nova.solicitante, sizeof(nova.solicitante));

        if (strlen(nova.solicitante) == 0) {
            printf("Campo obrigatório.\n");
        }
    } while (strlen(nova.solicitante) == 0);

    while (1) {

        printf("Novo ID do laboratório: ");

        if (!lerInteiro(&nova.idLaboratorio)) {
            printf("ID inválido.\n");
            continue;
        }

        int indiceLab = encontrarID(nova.idLaboratorio, laboratorios);

        if (indiceLab == -1) {
            printf("Laboratório não encontrado.\n");
            continue;
        }

        if (laboratorios->itens[indiceLab].status == LAB_INDISPONIVEL) {
            printf("Laboratório indisponível.\n");
            continue;
        }

        break;
    }

    while (1) {

        printf("\nNova data\n");

        printf("Dia: ");

        if (!lerInteiro(&nova.data.dia))
            continue;

        printf("Mês: ");

        if (!lerInteiro(&nova.data.mes))
            continue;

        printf("Ano: ");

        if (!lerInteiro(&nova.data.ano))
            continue;

        if (dataValida(&nova.data))
            break;

        printf("Data inválida.\n");
    }

    while (1) {

        printf("\nNovo horário inicial\n");

        printf("Hora: ");

        if (!lerInteiro(&nova.inicio.hora))
            continue;

        printf("Minuto: ");

        if (!lerInteiro(&nova.inicio.minuto))
            continue;

        if (horarioInicioValido(&nova.inicio))
            break;

        printf("Horário inicial inválido.\n");
    }


    while (1) {

        printf("\nNovo horário de término\n");

        printf("Hora: ");

        if (!lerInteiro(&nova.fim.hora))
            continue;

        printf("Minuto: ");

        if (!lerInteiro(&nova.fim.minuto))
            continue;

        if (horarioFinalValido(&nova.fim, &nova.inicio)) {

            break;
        }

        printf("Horário de término inválido.\n");
    }

    if (!verificarDisponibilidade(reservas, nova.idLaboratorio, nova.data, nova.inicio, nova.fim, nova.id)) {
        printf("Conflito com outra reserva existente.\n");
        return;
    }

    reservas->itens[indice] = nova;

    salvarReservas(reservas);

    printf("Reserva atualizada com sucesso!\n");
}

void removerReserva(VetReservasLab *reservas) {
    if (reservas->qtd == 0) {
        printf("\nNenhuma reserva cadastrada.\n");
        return;
    }

    int id;

    printf("\nID da reserva: ");

    if (!lerInteiro(&id)) {
        printf("ID invalido.\n");
        return;
    }

    int indice = buscarReservaPorId(reservas, id);

    if (indice == -1) {
        printf("A reserva não foi encontrada.\n");
        return;
    }

    int confirmar;

    do {
        printf("Confirma a remoção da reserva %d? [1] Sim [0] Nao\n", id);
        printf("Opção: ");

        if (!lerInteiro(&confirmar)) {
            printf("Opção inválida.\n");
            continue;
        }

    } while (confirmar != 0 && confirmar != 1);

    if (confirmar == 0) {
        printf("Remoção cancelada.\n");
        return;
    }

//  Mover as reservas anteriores para ficar organizado
    for (int i = indice; i < reservas->qtd - 1; i++) {
        reservas->itens[i] = reservas->itens[i + 1];
    }

    reservas->qtd--;

    salvarReservas(reservas);

    printf("Reserva removida com sucesso!\n");
}

void relatorioPorData(VetReservasLab *reservas, VetLaboratorios *laboratorios) {
    Data data;

    int encontrou = 0;

    printf("\nDigite a data a ser pesquisada\n");

    printf("Dia: ");

    if (!lerInteiro(&data.dia))
        return;

    printf("Mês: ");

    if (!lerInteiro(&data.mes))
        return;

    printf("Ano: ");

    if (!lerInteiro(&data.ano))
        return;

    if (!dataValida(&data)) {
        printf("Data inválida!\n");
        return;
    }

    printf("\n====== RELATÓRIO DE %02d/%02d/%04d ======\n", data.dia, data.mes, data.ano);

    for (int i = 0; i < reservas->qtd; i++) {

        ReservaLab *r = &reservas->itens[i];

        if (r->data.dia == data.dia && r->data.mes == data.mes && r->data.ano == data.ano) {
            
            int indiceLab = encontrarID(r->idLaboratorio, laboratorios);

            encontrou = 1;

            printf("\nReserva: %d\n", r->id);

            printf("Solicitante: %s\n", r->solicitante);

            if (indiceLab != -1) {
                printf("Laboratório: %s\n", laboratorios->itens[indiceLab].nome);
            }

            printf("Horário: %02d:%02d - %02d:%02d\n", r->inicio.hora, r->inicio.minuto, r->fim.hora, r->fim.minuto);
        }
    }

    if (!encontrou) {

        printf("\nNenhuma reserva foi encontrada nessa data.\n");
    }
}

//  Funções auxiliares da Reserva

//  Funções referentes ao Horário / Data
int dataValida(Data *dt) {
    int dias;

    if (dt->ano != 2026)
        return 0;

    if (dt->mes < 1 || dt->mes > 12)
        return 0;

    if (dt->mes == 2) {
        dias = 28;
        
    } else if (dt->mes == 4 || dt->mes == 6 || dt->mes == 9 || dt->mes == 11) {
        dias = 30;

    } else {
        dias = 31;
    }

    if (dt->dia < 1 || dt->dia > dias)
        return 0;

    return 1;
}

int horarioInicioValido(Horario *hi) {

    if (hi->hora < 7 || hi->hora > 20)
        return 0;

    if (hi->minuto < 0 || hi->minuto > 59)
        return 0;

    return 1;
}

int horarioFinalValido(Horario *hf,Horario *hi) {

    if (hf->hora < 8 || hf->hora > 21)
        return 0;

    if (hf->minuto < 0 || hf->minuto > 59)
        return 0;

    // Converte os horários para minutos para ficar mais fácil de compará-los.
    int inicio = hi->hora * 60 + hi->minuto;

    int fim =hf->hora * 60 + hf->minuto;

    if (fim <= inicio)
        return 0;

    return 1;
}

int verificarDisponibilidade(VetReservasLab *reservas, int idLaboratorio, Data data, Horario inicio, Horario fim, int idReservaIgnorar) {

    int novoInicio = inicio.hora * 60 + inicio.minuto;

    int novoFim = fim.hora * 60 + fim.minuto;

    for (int i = 0; i < reservas->qtd; i++) {

        ReservaLab *r = &reservas->itens[i];

        // Ignora a reserva que está sendo atualizada.
        if (r->id == idReservaIgnorar)
            continue;


        if (r->idLaboratorio != idLaboratorio)
            continue;

        if (r->data.dia != data.dia || r->data.mes != data.mes || r->data.ano != data.ano)
            continue;

        int inicioExistente = r->inicio.hora * 60 + r->inicio.minuto;

        int fimExistente = r->fim.hora * 60 + r->fim.minuto;

        // Dá conflito se o horário coincidir.
        if (novoInicio < fimExistente && novoFim > inicioExistente) {

            return 0;
        }
    }


    return 1;
}

// Relação com alloc e memória

void inicializarReservas(VetReservasLab *vet) {
    vet->qtd = 0;
    vet->cap = 10;

    vet->itens =malloc(vet->cap * sizeof(ReservaLab));

    if (vet->itens == NULL) {
        printf("Erro ao tentar alocar memória para as reservas.\n");
        exit(1);
    }
}

int aumentarCapacidadeReservas(VetReservasLab *reservas) {

    int novaCapacidade = reservas->cap + 10;

// O ponteiro temporário (assim como no dos laboratórios) é pra evitar perder o endereço original caso o realloc dê erro.
    ReservaLab *temporario = realloc( reservas->itens, novaCapacidade * sizeof(ReservaLab));

    if (temporario == NULL) {
        printf("Erro ao tentar aumentar a memória das reservas.\n");
        return 0;
    }

    reservas->itens = temporario;

    reservas->cap = novaCapacidade;

    return 1;
}

void liberarReservas(VetReservasLab *vet) {

    free(vet->itens);

    vet->itens = NULL;

    vet->qtd = 0;

    vet->cap = 0;
}

// Relação com fopen
void carregarReservas(VetReservasLab *vet) {

    FILE *arquivo = fopen("reservas.txt", "r");

    if (arquivo == NULL)
        return;

    ReservaLab r;

    while (
        fscanf(arquivo, "%d|%63[^|]|%d|%d|%d|%d|%d|%d|%d|%d\n", &r.id, r.solicitante, &r.idLaboratorio, &r.data.dia, &r.data.mes, &r.data.ano,
            &r.inicio.hora, &r.inicio.minuto, &r.fim.hora, &r.fim.minuto) == 10) {

        if (vet->qtd == vet->cap) {
            if (!aumentarCapacidadeReservas(vet))
                break;
        }

        // Vê se os dados carregados são válidos
        if (r.id <= 0 || r.idLaboratorio <= 0 || !dataValida(&r.data) || !horarioInicioValido(&r.inicio) || !horarioFinalValido( &r.fim, &r.inicio)) {
            continue;
        }

        // Evita IDs duplicados.
        if (buscarReservaPorId(vet, r.id) != -1)
            continue;

        vet->itens[vet->qtd] = r;

        vet->qtd++;
    }


    fclose(arquivo);
}

void salvarReservas(VetReservasLab *vet) {
    FILE *arquivo =
        fopen("reservas.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao tenar abrir o arquivo\n");

        return;
    }

    for (int i = 0; i < vet->qtd; i++) {
        ReservaLab *r = &vet->itens[i];

        fprintf(arquivo, "%d|%s|%d|%d|%d|%d|%d|%d|%d|%d\n", r->id, r->solicitante, r->idLaboratorio, r->data.dia, r->data.mes, r->data.ano, 
        r->inicio.hora, r->inicio.minuto, r->fim.hora, r->fim.minuto);
    }

    fclose(arquivo);
}

// Relação com ID
int buscarReservaPorId(VetReservasLab *vet, int id) {

    for (int i = 0; i < vet->qtd; i++) {
        if (vet->itens[i].id == id)
            return i;
    }

    return -1;
}

int proximoIdReserva(VetReservasLab *vet) {

    int maior = 0;

    for (int i = 0; i < vet->qtd; i++) {

        if (vet->itens[i].id > maior)
            maior = vet->itens[i].id;
    }

    return maior + 1;
}

int quantidadeReservas(VetReservasLab *vet) {

    return vet->qtd;
}
