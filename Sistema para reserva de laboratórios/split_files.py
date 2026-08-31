import os

with open('Funcoes.c', 'r') as f:
    lines_c = f.readlines()

utils_c = ['#include <stdio.h>\n', '#include <string.h>\n', '#include "utils.h"\n\n'] + lines_c[8:29]
labs_c = ['#include <stdio.h>\n', '#include <stdlib.h>\n', '#include <string.h>\n', '#include "laboratorios.h"\n', '#include "utils.h"\n\n'] + lines_c[29:498] + lines_c[1152:1157]
res_c = ['#include <stdio.h>\n', '#include <stdlib.h>\n', '#include <string.h>\n', '#include "reservas.h"\n', '#include "laboratorios.h"\n', '#include "utils.h"\n\n'] + lines_c[498:1151] + lines_c[1157:]

with open('utils.c', 'w') as f:
    f.writelines(utils_c)

with open('laboratorios.c', 'w') as f:
    f.writelines(labs_c)

with open('reservas.c', 'w') as f:
    f.writelines(res_c)

utils_h = """#ifndef UTILS_H
#define UTILS_H

// Função para validar entradas int
int lerInteiro(int *valor);

// Função para ler texto
void lerTexto(char *texto, int tamanho);

#endif
"""

labs_h = """#ifndef LABORATORIOS_H
#define LABORATORIOS_H

// Structs
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
    Laboratorio *itens;
    int qtd, cap;
} VetLaboratorios;

// Funções principais dos laboratórios
int cadastrarLaboratorio(VetLaboratorios *vetLab);
void listarLaboratorios(VetLaboratorios *vetLab);
void atualizarLaboratorio(VetLaboratorios *vetLab);
void removerLaboratorio(VetLaboratorios *vetLab);

// Funções auxiliares dos laboratórios
void inicializarLaboratorios(VetLaboratorios *vet);
int aumentarCapacidadeLaboratorios(VetLaboratorios *vet);
void liberarLaboratorios(VetLaboratorios *vet);
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

// Funções para mostrar quantas reservas e Laboratórios têm
int quantidadeLaboratorios(VetLaboratorios *vet);

#endif
"""

res_h = """#ifndef RESERVAS_H
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
"""

with open('utils.h', 'w') as f:
    f.write(utils_h)

with open('laboratorios.h', 'w') as f:
    f.write(labs_h)

with open('reservas.h', 'w') as f:
    f.write(res_h)

