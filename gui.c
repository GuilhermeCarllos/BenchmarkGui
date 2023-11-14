#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarNovosNumeros(int total) {
    FILE *arquivoNovo = fopen("novos_numeros.txt", "w");
    if (arquivoNovo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < total; i++) {
        int novoNum = rand() % 1000; // Gerando números aleatórios até 999
        fprintf(arquivoNovo, "%d ", novoNum);
    }

    fclose(arquivoNovo);
}

int buscaSequencial(int num, int total) {
    FILE *arquivoSeq = fopen("novos_numeros.txt", "r");
    if (arquivoSeq == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    int elementoSeq;
    while (fscanf(arquivoSeq, "%d", &elementoSeq) != EOF) {
        if (elementoSeq == num) {
            fclose(arquivoSeq);
            return 1; // Elemento encontrado
        }
    }

    fclose(arquivoSeq);
    return 0; // Elemento não encontrado
}

int buscaSentinela(int num, int total) {
    FILE *arquivoSent = fopen("novos_numeros.txt", "r");
    if (arquivoSent == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    int ult, elementoSent;
    fscanf(arquivoSent, "%d", &ult);

    while (ult != num) {
        if (fscanf(arquivoSent, "%d", &elementoSent) == EOF)
            break;
        if (elementoSent == num) {
            fclose(arquivoSent);
            return 1; // Elemento encontrado
        }
    }

    fclose(arquivoSent);
    return 0; // Elemento não encontrado
}

int buscaBinaria(int num, int total) {
    FILE *arquivoBin = fopen("novos_numeros.txt", "r");
    if (arquivoBin == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    int inicio = 0, fim = total - 1, meio, elementoBin;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(arquivoBin, meio * sizeof(int), SEEK_SET);
        fscanf(arquivoBin, "%d", &elementoBin);

        if (elementoBin == num) {
            fclose(arquivoBin);
            return 1; // Elemento encontrado
        } else if (elementoBin < num) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    fclose(arquivoBin);
    return 0; // Elemento não encontrado
}

void bubbleSort(int array[], int tamanho) {
    clock_t inicioBubble = clock();

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int tempBubble = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tempBubble;
            }
        }
    }

    clock_t fimBubble = clock();
    double tempoBubble = (double)(fimBubble - inicioBubble) / CLOCKS_PER_SEC;
    printf("Tempo Bubble Sort: %.6f segundos\n", tempoBubble);
}

void quickSort(int array[], int start, int end) {
    if (start < end) {
        int pivot = array[end];
        int i = start - 1;

        for (int j = start; j < end; j++) {
            if (array[j] < pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }

        int temp = array[i + 1];
        array[i + 1] = array[end];
        array[end] = temp;

        int pivot_pos = i + 1;

        quickSort(array, start, pivot_pos - 1);
        quickSort(array, pivot_pos + 1, end);
    }
}

void showArray(int array[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int totalNum;
    printf("Quantidade de números a gerar: ");
    scanf("%d", &totalNum);

    gerarNovosNumeros(totalNum);

    int escolha;
    printf("Escolha a operação:\n");
    printf("1. Operações de busca de elemento\n");
    printf("2. Operações de classificação de elementos\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            printf("Insira o número para buscar: ");
            int numBusca;
            scanf("%d", &numBusca);

            if (buscaSequencial(numBusca, totalNum)) {
                printf("Número encontrado usando busca sequencial.\n");
            } else {
                printf("Número não encontrado usando busca sequencial.\n");
            }

            if (buscaSentinela(numBusca, totalNum)) {
                printf("Número encontrado usando busca sentinela.\n");
            } else {
                printf("Número não encontrado usando busca sentinela.\n");
            }

            if (buscaBinaria(numBusca, totalNum)) {
                printf("Número encontrado usando busca binária.\n");
            } else {
                printf("Número não encontrado usando busca binária.\n");
            }
            break;

        case 2:
            FILE *arquivo = fopen("novos_numeros.txt", "r");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.");
                exit(1);
            }

            int *numeros = malloc(totalNum * sizeof(int));
            if (numeros == NULL) {
                printf("Erro de alocação de memória.");
                exit(1);
            }

            for (int i = 0; i < totalNum; i++) {
                fscanf(arquivo, "%d", &numeros[i]);
            }
            fclose(arquivo);

            bubbleSort(numeros, totalNum);

            printf("Array ordenado pelo Bubble Sort: ");
            showArray(numeros, totalNum);

            clock_t inicioQuick = clock();
            quickSort(numeros, 0, totalNum - 1);
            clock_t fimQuick = clock();
            double tempoQuick = (double)(fimQuick - inicioQuick) / CLOCKS_PER_SEC;
            printf("Tempo Quick Sort: %.6f segundos\n", tempoQuick);

            printf("Array ordenado pelo Quick Sort: ");
            showArray(numeros, totalNum);

            free(numeros);
            break;

        default:
            printf("Opção inválida.\n");
            break;
    }

    return 0;
}
