#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>

// Structs
typedef struct {
int dia, mes, ano; // DD/MM/AAAA
} Data;

typedef struct {
int hora, minuto; //24h
} Horario;

typedef enum {
LAB_ATIVO = 1,
LAB_INDISPONIVEL = 0 // manutenção, bloqueio, etc.
} StatusLab;

typedef struct {
int id;
char nome[64];
int capacidade;
char equipamentos[256]; // texto livre (ex.: "PCs, GPU, Projetor")
StatusLab status;
} Laboratorio;

typedef struct {
int id;
char solicitante[64]; // nome ou matrícula
int idLaboratorio;
Data data;
Horario inicio; // início do uso
Horario fim; // fim do uso
} ReservaLab;

// Coleções dinâmicas
typedef struct {
Laboratorio *itens;
int qtd, cap;
} VetLaboratorios;

typedef struct {
ReservaLab *itens;
int qtd, cap;
} VetReservasLab;

// Funções gerais

// Função para validar entradas int
int lerInteiro(int *valor);

// Função para ler texto
void lerTexto(char *texto, int tamanho);

// Funções principais dos laboratórios
int cadastrarLaboratorio(VetLaboratorios *vetLab);

void listarLaboratorios(VetLaboratorios *vetLab);

void atualizarLaboratorio(VetLaboratorios *vetLab);

void removerLaboratorio(VetLaboratorios *vetLab);

// Funções auxiliares dos laboratórios

// Relação com alloc e memória
void inicializarLaboratorios(VetLaboratorios *vet);

int aumentarCapacidadeLaboratorios(VetLaboratorios *vet);

void liberarLaboratorios(VetLaboratorios *vet);

// Relação com ID
int encontrarID(int id, VetLaboratorios *vetLab);

int escolherLaboratorio(VetLaboratorios *vetLab);

// Funções para a lista
void exibirCabecalhoTabela(void);

void exibirLaboratorioLinha(Laboratorio lab);

void exibirRodapeTabela(void);

const char *obterStatusTexto(StatusLab status);

// Relação com fopen
void carregarLaboratorios(VetLaboratorios *vet);

void salvarLaboratorios(VetLaboratorios *vet);


// Funções principais da Reserva
void cadastrarReserva(VetReservasLab *reservas, VetLaboratorios *vetLab);

void listarReservas(VetReservasLab *reservas, VetLaboratorios *laboratorios);

void atualizarReserva(VetReservasLab *reservas, VetLaboratorios *laboratorios);

void removerReserva(VetReservasLab *reservas);

void relatorioPorData(VetReservasLab *reservas, VetLaboratorios *laboratorios);

//  Funções auxiliares da Reserva

//  Funções referentes ao Horário / Data
int dataValida(Data *dt);

int horarioInicioValido(Horario *hi);

int horarioFinalValido(Horario *hf, Horario *hi);

int verificarDisponibilidade(VetReservasLab *reservas, int idLaboratorio, Data data, Horario inicio, Horario fim, int idReservaIgnorar);

// Relação com alloc e memória
void inicializarReservas(VetReservasLab *vet);

int aumentarCapacidadeReservas(VetReservasLab *reservas);

void liberarReservas(VetReservasLab *vet);

// Relação com fopen
void carregarReservas(VetReservasLab *vet);

void salvarReservas(VetReservasLab *vet);

// Relação com ID
int buscarReservaPorId(VetReservasLab *vet, int id);

int proximoIdReserva(VetReservasLab *vet);


// Funções para mostrar quantas reservas e Laboratórios têm
int quantidadeLaboratorios(VetLaboratorios *vet);

int quantidadeReservas(VetReservasLab *vet);

#endif