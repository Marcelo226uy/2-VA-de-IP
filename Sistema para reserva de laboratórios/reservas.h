#ifndef RESERVAS_H
#define RESERVAS_H

#include "laboratorios.h"

// Structs
typedef struct {
    int dia, mes, ano; // DD/MM/AAAA
} Data;

typedef struct {
    int hora, minuto; //24h
} Horario;

typedef struct {
    int id;
    char solicitante[64]; // nome ou matrícula
    int idLaboratorio;
    Data data;
    Horario inicio; // início do uso
    Horario fim; // fim do uso
} ReservaLab;

typedef struct {
    ReservaLab *itens;
    int qtd, cap;
} VetReservasLab;

// Funções principais da Reserva
void cadastrarReserva(VetReservasLab *reservas, VetLaboratorios *vetLab);
void listarReservas(VetReservasLab *reservas, VetLaboratorios *laboratorios);
void atualizarReserva(VetReservasLab *reservas, VetLaboratorios *laboratorios);
void removerReserva(VetReservasLab *reservas);
void relatorioPorData(VetReservasLab *reservas, VetLaboratorios *laboratorios);

//  Funções auxiliares da Reserva
int dataValida(Data *dt);
int horarioInicioValido(Horario *hi);
int horarioFinalValido(Horario *hf, Horario *hi);
int verificarDisponibilidade(VetReservasLab *reservas, int idLaboratorio, Data data, Horario inicio, Horario fim, int idReservaIgnorar);
void inicializarReservas(VetReservasLab *vet);
int aumentarCapacidadeReservas(VetReservasLab *reservas);
void liberarReservas(VetReservasLab *vet);
void carregarReservas(VetReservasLab *vet);
void salvarReservas(VetReservasLab *vet);
int buscarReservaPorId(VetReservasLab *vet, int id);
int proximoIdReserva(VetReservasLab *vet);
int quantidadeReservas(VetReservasLab *vet);

#endif
