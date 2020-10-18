/*    
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO-PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Raul dos Reis Soares
  NUSP: 8535596

  main.c

  Exemplo de uso para saída simples:
  	./EP1 10000

  Exemplos de uso para sáida completa:
  	./EP1 10000 c
  	./EP1 10000 C
  	./EP1 10000 completa
  	./EP1 10000 Cmpt
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "node.h"
#include "filaCPU.h"
#include "filaEspera.h"

// define FWAIT 'w'
// define FCPU 'c'
// define FPRINT 'p'

#define PROB 0.05 // Probabilidade de gerar novo processo
#define UTMAX 10000 // Tempo de simulação padrão
unsigned int id = 1;

// Essa função gera, com probabilidade PROB, um novo processo representado por
// um apontador para um Node (Link). Caso esse processo não seja gerado, o valor
// NULL é retornado. Utiliza a variável gobal id para criar identificadores para
// os processos. Cada processo recebe uma prioridade entre 0 e 9, sendo a última
// maior. As prioridades são escolhidas com distribuição uniforme.
Link newProcess();


int main(int argc, char *argv[]) {
	unsigned int ut = 0; // Unidades de tempo executadas
	unsigned int utMax = UTMAX; // Unidade de tempo total da simulação
	unsigned int end, endP[10]; // Quantos processos encerraram sua execução e separados por prioridade
	unsigned int endEspera, endEsperaP[10]; // Soma do tempo na lista de espera dos processos concluídos e separados por prioridade
	unsigned int endCpu = 0; // Soma do tempo na cpu dos processo encerrados
	unsigned int endImpressora = 0; // Soma do tempo de espera na fila de impressao
	unsigned int endTotal, endTotalP[10]; // Soma do tempo total do processo no sistema e separados por prioridade
	unsigned int gerados = 0; // Número toal de processos gerados
	unsigned int tamEsp, tamCpu, tamImp; // Tamanho das filas ao final da simulação
	unsigned int *contP = NULL; // Número de processos na fila de espera separados por prioridade
	unsigned int invalidos[2] = {0, 0}; // Processos que foram excluídos na contagem por entrarem no sistema quando ut < 100
	double endRazao = 0.0; // Soma da razão entre o tempo de processamento e o tempo total
	bool completa = false; // Se a saída é completa
	Link impressoras[3]; // Impressoras: apontaram para o processo que estiver imprimindo
	FilaEspera espera = criaFilaEspera(); // Fila de processos em espera
	Fila cpu = criaFila(); // Fila de processos na CPU
	Fila esperaImpressora = criaFila(); // Fila de processos em espera das impressoras

	srand(time(NULL));

	for (unsigned int i = 0; i < 3; i++)
		impressoras[i] = NULL;
	for (unsigned int i = 0; i < 10; i++) {
		endP[i] = 0;
		endTotalP[i] = 0;
		endEsperaP[i] = 0;
	}

	if (argc >= 2)
		utMax = atoi(argv[1]);
	if (argc >= 3 && (argv[2][0] == 'C' || argv[2][0] == 'c'))
		completa = true;

	while (ut < utMax) {
		printf("------------------------");
		printf(" UT = %d\n\n", ut);
		Link processo = newProcess();

		// Imprime o processo que foi gerado
		if (processo != NULL) {
			printf("Novo processo:\n");
			printf(" id: %d\n", processo->id);
			printf(" Prioridade: %d\n", processo->priori);
			printf(" Tempo de processamento: %d\n", processo->timeNeed);
			printf(" Linhas para imprimir: %d\n\n", processo->linesNeed);
			if (ut < 100) {
				processo->valid = false;
				invalidos[0] += 1;
			}
			else
				gerados++;
			enfilaEspera(espera, processo);
		}
		else
			printf("Nenhum processo novo gerado.\n\n");

		if(!cheia(cpu)) {
			enfila(cpu, desenfilaEspera(espera));
		}

		processo = clockCPU(cpu);

		if (processo != NULL) {
			if (temLinhas(processo) == false) {
				unsigned int tempoTotal = processo->timeWait + processo->timeCPU + processo->timePrinter;
				double razao = ((double) tempoTotal)/((double) processo->timeNeed);
				printf("Processo encerrado:\n");
				printf(" id: %d\n", processo->id);
				printf(" Dados iniciais:\n");
				printf("	Prioridade: %d\n", processo->priori);
				printf(" 	Tempo de processamento: %d\n", processo->timeNeed);
				printf(" 	Linhas para imprimir: %d\n", processo->linesNeed);
				printf(" Dados finais:\n");
				printf(" 	Tempo da fila de espera: %d\n", processo->timeWait);
				printf(" 	Tempo da fila de cpu: %d\n", processo->timeCPU);
				printf(" 	Tempo da fila de impressão: %d\n", processo->timePrinter);
				printf("	Tempo total de permanência no sistema: %d\n", tempoTotal);
				printf("	Razão entre o tempo de processamento e o tempo total : %.2f\n\n", razao);
				if (processo->valid == false) {
					invalidos[1] += 1;
				}
				else {
					endP[processo->priori] += 1;
					endEsperaP[processo->priori] += processo->timeWait;
					endCpu += processo->timeCPU;
					endImpressora += processo->timePrinter;
					endTotalP[processo->priori] += tempoTotal;
					endRazao += razao;
				}
				freeNode(processo);
				processo = NULL;
			}
			else
				enfila(esperaImpressora, processo);
		}

		for (int i = 0; i < 3; i++)
			if (impressoras[i] == NULL)
				impressoras[i] = desenfila(esperaImpressora);

		for (int i = 0; i < 3; i++) {
			processo = imprimeLinhas(impressoras[i]);
			if (processo != NULL) {
				unsigned int tempoTotal = processo->timeWait + processo->timeCPU + processo->timePrinter + (processo->linesNeed/10) + 1;
				double razao = ((double) processo->timeNeed)/((double) tempoTotal);
				printf("Processo encerrado:\n");
				printf(" id: %d\n", processo->id);
				printf(" Dados iniciais:\n");
				printf("	Prioridade: %d\n", processo->priori);
				printf(" 	Tempo de processamento: %d\n", processo->timeNeed);
				printf(" 	Linhas para imprimir: %d\n", processo->linesNeed);
				printf(" Dados finais:\n");
				printf(" 	Tempo da fila de espera: %d\n", processo->timeWait);
				printf(" 	Tempo da fila de cpu: %d\n", processo->timeCPU);
				printf(" 	Tempo da fila de impressão: %d\n", processo->timePrinter);
				printf("	Tempo total de permanência no sistema: %d\n", tempoTotal);
				printf("	Razão entre o tempo de processamento e o tempo total : %.2f\n\n", razao);
				if (processo->valid == false) {
					invalidos[1] += 1;
				}
				else {
					endP[processo->priori] += 1;
					endEsperaP[processo->priori] += processo->timeWait;
					endCpu += processo->timeCPU;
					endImpressora += processo->timePrinter;
					endTotalP[processo->priori] += tempoTotal;
					endRazao += razao;
				}
				freeNode(processo);
				processo = NULL;
				impressoras[i] = NULL;
			}
		}

		if(completa) {
			printf("\nTamanho da fila de espera: %d. Estado da fila: \n", espera->size);
			printFilaEspera(espera);
			printf("\nTamanho da fila da cpu: %d. Estado da fila: \n", cpu->size);
			printFila(cpu);
			printf("\nTamanho da fila de impressão: %d. Estado da fila: \n", esperaImpressora->size);
			printFila(esperaImpressora);
			printf("\n");

		}
		timeAddEspera(espera);
		timeAdd(cpu, FCPU);
		timeAdd(esperaImpressora, FPRINT);
		ut++;
	}
	tamEsp = tamEspera(espera);
	tamCpu = tam(cpu);
	tamImp = tam(esperaImpressora);
	contP = contagemEspera(espera);
	liberaFila(cpu);
	liberaFilaEspera(espera);
	liberaFila(esperaImpressora);

	for (int i = end = endTotal = endEspera = 0; i < 10; i++) {
		end += endP[i];
		endTotal += endTotalP[i];
		endEspera += endEsperaP[i];
	}

	printf("\nSIMULAÇÃO FINALIZADA: \n");
	printf("	Número total de processos gerados: %d\n", gerados+invalidos[0]);
	printf("	Número total de processos concluídos: %d\n", end+invalidos[1]);
	printf("	Número de processos na fila de espera ao final da simulação: %d\n", tamEsp);
	printf("	Número de processos na fila da cpu ao final da simulação: %d\n", tamCpu);
	printf("	Número de processos na fila de impressão ao final da simulação: %d\n", tamImp);
	printf("	Média do tempo gasto na fila de espera: %.2f\n", ((double) endEspera)/((double) end));
	printf("	Média do tempo gasto na fila de cpu: %.2f\n", ((double) endCpu)/((double) end));
	printf("	Média do tempo gasto na fila de impressão: %.2f\n", ((double) endImpressora)/((double) end));
	printf("	Média do tempo total de permanência no sistema: %.2f\n", ((double) endTotal)/((double) end));
	printf("    Média da razão entre o tempo de processamento e o tempo total: %.2f\n", endRazao/((double) end));
	printf("\nDADOS POR PRIORIDADE: \n");
	for (unsigned int i = 0; i < 10; i++) {
		if (endP[i] == 0)
			continue;
		printf("Prioridade %d:\n", i);
		printf("	Média do tempo total de permanência no sistema: %.2f\n", ((double) endTotalP[i])/((double) endP[i]));
		printf("	Média do tempo total de permanência na fila de espera: %.2f\n", ((double) endEsperaP[i])/((double) endP[i]));
		printf("	Número de processos na fila de espera ao final da simulação: %d\n", contP[i]);
	}

	free(contP);
	return 0; 	
}

Link newProcess() {
	double p = ((double) rand())/((double)RAND_MAX);
	if (p <= PROB) {
		int cpuTime = (rand() % 61) + 1;
		int lines = rand() % 501;
		unsigned int priori = (unsigned int) (rand() % 10);

		Link node = newNode(id++, priori, cpuTime, lines, NULL, NULL);
		node->valid = true;
		return node;
	}
	return NULL;
}