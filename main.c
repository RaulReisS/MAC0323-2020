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

// define FWAIT 'w'
// define FCPU 'c'
// define FPRINT 'p'

#define PROB 0.06
#define UTMAX 10000
unsigned int id = 1;

// Essa função gera, com probabilidade PROB, um novo processo representado por
// um apontador para um Node (Link). Caso esse processo não seja gerado, o valor
// NULL é retornado. Utiliza a variável gobal id para criar identificadores para
// os processos
Link newProcess();


int main(int argc, char *argv[]) {
	unsigned int ut = 0; // Unidades de tempo executadas
	unsigned int utMax = UTMAX; // Unidade de tempo total da simulação
	unsigned int end = 0; // Quantos processos encerraram sua execução
	unsigned int endEspera = 0; // Soma do tempo na lista de espera dos processos encerrados
	unsigned int endCpu = 0; // Soma do tempo na cpu dos processo encerrados
	unsigned int endImpressora = 0; // Soma do tempo de espera na fila de impressao
	unsigned int endTotal = 0;
	double endRazao = 0.0; // Soma da razão entre o tempo de processamento e o tempo total
	bool completa = false; // Se a saída é completa
	Link impressoras[3]; // Impressoras: apontaram para o processo que estiver imprimindo
	Fila espera = criaFila(); // Fila de processos em espera
	Fila cpu = criaFila(); // Fila de processos na CPU
	Fila esperaImpressora = criaFila(); // Fila de processos em espera das impressoras

	srand(time(NULL));

	for (int i = 0; i < 3; i++)
		impressoras[i] = NULL;

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
			printf(" Tempo de processamento: %d\n", processo->timeNeed);
			printf(" Linhas para imprimir: %d\n\n", processo->linesNeed);
			enfila(espera, processo);
		}
		else
			printf("Nenhum processo novo gerado.\n\n");

		if(!cheia(cpu)) {
			enfila(cpu, desenfila(espera));
		}

		processo = clockCPU(cpu);

		if (processo != NULL) {
			if (temLinhas(processo) == false) {
				unsigned int tempoTotal = processo->timeWait + processo->timeCPU + processo->timePrinter;
				double razao = ((double) tempoTotal)/((double) processo->timeNeed);
				printf("Processo encerrado:\n");
				printf(" id: %d\n", processo->id);
				end += 1;
				printf(" Dados iniciais:\n");
				printf(" 	Tempo de processamento: %d\n", processo->timeNeed);
				printf(" 	Linhas para imprimir: %d\n", processo->linesNeed);
				printf(" Dados finais:\n");
				printf(" 	Tempo da fila de espera: %d\n", processo->timeWait);
				endEspera += processo->timeWait;
				printf(" 	Tempo da fila de cpu: %d\n", processo->timeCPU);
				endCpu += processo->timeCPU;
				printf(" 	Tempo da fila de impressão: %d\n", processo->timePrinter);
				endImpressora += processo->timePrinter;
				printf("	Tempo total de permanência no sistema: %d\n", tempoTotal);
				endTotal += tempoTotal;
				printf("	Razão entre o tempo de processamento e o tempo total : %.2f\n\n", razao);
				endRazao += razao;
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
				end += 1;
				printf(" Dados iniciais:\n");
				printf(" 	Tempo de processamento: %d\n", processo->timeNeed);
				printf(" 	Linhas para imprimir: %d\n", processo->linesNeed);
				printf(" Dados finais:\n");
				printf(" 	Tempo da fila de espera: %d\n", processo->timeWait);
				endEspera += processo->timeWait;
				printf(" 	Tempo da fila de cpu: %d\n", processo->timeCPU);
				endCpu += processo->timeCPU;
				printf(" 	Tempo da fila de impressão: %d\n", processo->timePrinter);
				endImpressora += processo->timePrinter;
				printf("	Tempo total de permanência no sistema: %d\n", tempoTotal);
				endTotal += tempoTotal;
				printf("	Razão entre o tempo de processamento e o tempo total : %.2f\n\n", razao);
				endRazao += razao;
				freeNode(processo);
				processo = NULL;
				impressoras[i] = NULL;
			}
		}

		if(completa) {
			printf("\nTamanho da fila de espera: %d. Estado da fila: \n", espera->size);
			printFila(espera);
			printf("\nTamanho da fila da cpu: %d. Estado da fila: \n", cpu->size);
			printFila(cpu);
			printf("\nTamanho da fila de impressão: %d. Estado da fila: \n", esperaImpressora->size);
			printFila(esperaImpressora);
			printf("\n");

		}
		timeAdd(espera, FWAIT);
		timeAdd(cpu, FCPU);
		timeAdd(esperaImpressora, FPRINT);
		ut++;
	}
	liberaFila(cpu);
	liberaFila(espera);
	liberaFila(esperaImpressora);

	printf("\nSIMULAÇÃO FINALIZADA: \n");
	printf("	Número total de processos executados: %d\n", end);
	printf("	Média do tempo gasto na fila de espera: %.2f\n", ((double) endEspera)/((double) end));
	printf("	Média do tempo gasto na fila de cpu: %.2f\n", ((double) endCpu)/((double) end));
	printf("	Média do tempo gasto na fila de impressão: %.2f\n", ((double) endImpressora)/((double) end));
	printf("	Média do tempo total de permanência no sistema: %.2f\n", ((double) endTotal)/((double) end));
	printf("    Média da razão entre o tempo de processamento e o tempo total: %.2f\n", endRazao/((double) end));

	return 0; 	
}

Link newProcess() {
	double p = ((double) rand())/((double)RAND_MAX);
	if (p <= PROB) {
		int cpuTime = (rand() % 61) + 1;
		int lines = rand() % 501;
		Link node = newNode(id++, cpuTime, lines, NULL, NULL);
		return node;
	}
	return NULL;
}