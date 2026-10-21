#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Tamanho da Matriz
#define M 8  // Conjuntos 
#define N 10 // Elementos por conjunto
#define P 2  // Linhas para média (0) e desvio padrão (1)

// Redefinir todas as formatações de texto
#define RESET    "\033[0m"

// Cores Padrão
#define VERMELHO "\033[91m"
#define VERDE    "\033[92m"
#define AMARELO  "\033[93m"
#define AZUL     "\033[94m"

// Cores em Negrito
#define NEGRITO_BRANCO   "\033[1;97m"

// ---------- Utilitários ----------

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pausar(){
    printf("\n" NEGRITO_BRANCO "Pressione Enter para continuar..." RESET);
    limpar_buffer();
}

int existe_conjunto(int contador){
    if(contador == 0){
        printf(VERMELHO "\nVocê precisa criar um novo conjunto!" RESET "\n");
        return false;
    }
    return true;
}

int pedir_indice(int contador, char *acao){
    int indice = -1;
    do{
        printf("\nQual conjunto deseja %s (0 - %d): ", acao, contador - 1);
        if(scanf("%d", &indice) != 1){
            indice = -1;
        }
        limpar_buffer();
        if(indice < 0 || indice >= contador){
            printf(VERMELHO "Índice inválido!" RESET "\n");
        }
    }while(indice < 0 || indice >= contador);

    return indice;
}

int pedir_valores(int contador){
    int valor = 0;
    int leu_corretamente = 0;
    do{
        printf("\nQual valor deseja buscar dentro dos conjuntos: ");
        leu_corretamente = scanf("%d", &valor);
        limpar_buffer();
        if (leu_corretamente != 1) {
            printf(VERMELHO "Valor inválido! Digite um número." RESET "\n");
        }
    }while(leu_corretamente != 1);
        
    return valor;
}

// Retorna -1 se não existe no conjunto, retorna o índice se existe no conjunto.
int existe_valor(int conjunto[], int valor){
    int indice = -1;
    for(int i = 0; i < N; i++){
        if(conjunto[i] == valor){
            indice = i;
            break;
        }
    }
    return indice;
}

int pode_unir(int conj1[N], int conj2[N], int somaQtd){
    for(int i = 0; i < N; i++){
        if(conj1[i] == 0){
            break;
        }
        for(int j = 0; j < N; j++){
            if(conj2[j] == 0){
                break;
            }
            if(conj2[j] == conj1[i]){
                somaQtd--;
            }
        }
    }
    if(somaQtd <= N){
        return 1;
    }else{
        return 0;
    }
}

// ---------- Opções do menu ----------

// 1. Cria um novo conjunto para ser usado dentro da matriz
void criar_conjunto(int *contador){
    if(*contador < M){
        (*contador)++;
        printf("\n" VERDE "Conjunto criado! Agora existem %d conjunto(s)." RESET "\n", *contador);
    }else{
        printf("\n" VERMELHO "Limite de %d conjuntos atingido." RESET "\n", M);
    }
}

// 2. Inserir valores 
void inserir_valores(int contador, int matriz[M][N], int quantidade[M]){
    int indice = pedir_indice(contador, "inserir valores");
    int valor;

    if(quantidade[indice] != N){
        for(int j = quantidade[indice]; j < N; j++){
            printf("Digite um valor (0 para parar): ");
            if(scanf("%d", &valor) != 1){
                limpar_buffer();
                printf(VERMELHO "Digite apenas números!" RESET "\n");
                j--;
                continue;
            }

            if(valor == 0){
                break;
            }

            if(existe_valor(matriz[indice], valor) != -1){
                printf("\n" VERMELHO "Esse valor já existe nesse conjunto" RESET "\n");
                j--;
                continue;
            }

            matriz[indice][j] = valor;
            quantidade[indice]++;
        }
    }else{
        printf("\n" VERMELHO "O Conjunto não suporta mais valores" RESET "\n");
    }
}

// 3. Remover um conjunto (Atualizado para mover também a matriz med_dev)
void remover_conjunto(int *contador, int matriz[M][N], int quantidade[M], float med_dev[P][M]){
    int indice = pedir_indice(*contador, "remover");
    int conjunto_maximo = *contador - 1;

    for(int i = indice; i < conjunto_maximo; i++){ 
        for(int j = 0; j < N; j++){
            matriz[i][j] = matriz[i+1][j];
        }
        quantidade[i] = quantidade[i+1];
        med_dev[0][i] = med_dev[0][i+1];
        med_dev[1][i] = med_dev[1][i+1];
    }

    for(int i = 0; i < N; i++){
        matriz[conjunto_maximo][i] = 0;
    }
    quantidade[conjunto_maximo] = 0;
    med_dev[0][conjunto_maximo] = 0.0f;
    med_dev[1][conjunto_maximo] = 0.0f;
    (*contador)--;

    printf("\n" AMARELO "Conjunto removido! Os conjuntos com índices maiores foram movidos. Agora existem %d conjunto(s)." RESET "\n", *contador);
}

// 4. União de Conjuntos
void uniao_conjuntos(int *contador, int matriz[M][N], int quantidade[M]){
    if(*contador >= M){
        printf("\n" VERMELHO "O limite de conjuntos já foi atingido." RESET "\n");
        return;
    }

    int indice = pedir_indice(*contador, "unir (1)");
    int indice2 = pedir_indice(*contador, "unir (2)");

    int somaQtd = quantidade[indice] + quantidade[indice2];
    if(pode_unir(matriz[indice], matriz[indice2], somaQtd) == 0){
        printf("\n" VERMELHO "A união ultrapassa os limites do conjunto. Nenhum conjunto foi criado." RESET "\n");
        return;
    }

    quantidade[*contador] = 0;

    int i = 0;
    for(int j = 0; j < N; j++){
        int valor = matriz[indice][j];

        if(i >= N || valor == 0){
            break;
        }

        matriz[*contador][i] = valor;
        quantidade[*contador]++;
        i++;
    }
    
    for(int j = 0; j < N; j++){
        int valor = matriz[indice2][j];

        if(i >= N || valor == 0){
            break;
        }
        
        int repetido = -1;
        for(int k = 0; k < N; k++){
            if(matriz[indice][k] == 0){
                break;
            }

            if(matriz[indice][k] == valor){
                repetido = 1;
                break;
            }
        }

        if(repetido == 1){
            continue;
        }

        matriz[*contador][i] = valor;
        quantidade[*contador]++;
        i++;
    }

    (*contador)++;
    printf("\n" VERDE "O conjunto união foi criado no índice %d. " RESET "\n", (*contador - 1));
}

// 5. Interseção de conjuntos
void intersecao_conjuntos(int *contador, int matriz[M][N], int quantidade[M]){
    if(*contador >= M){
        printf("\n" VERMELHO "O limite de conjuntos já foi atingido. " RESET "\n");
        return;
    }

    int indice = pedir_indice(*contador, "fazer a interseção (1)");
    int indice2 = pedir_indice(*contador, "fazer a interseção (2)");

    
    quantidade[*contador] = 0;
    int k = 0;

    for(int i = 0; i < N; i++){
        int valor1 = matriz[indice][i];
        
        if(valor1 == 0){
            break;
        }

        for(int j = 0; j < N; j++){
            int valor2 = matriz[indice2][j];
            if(valor2 == 0){
                break;
            }

            if(valor1 == valor2){
                if(k < N){
                    matriz[*contador][k] = valor1;
                    quantidade[*contador]++;
                    k++;
                }
            }
        }
    }

    (*contador)++;
    printf("\n" VERDE "O conjunto interseção foi criado no índice %d." RESET "\n", (*contador - 1));
}

// 6. Mostrar um conjunto 
void mostrar_conjunto(int contador, int matriz[M][N], int quantidade[M]){
    int indice = pedir_indice(contador, "mostrar");

    printf("\nConjunto %d: {", indice);
    for(int j = 0; j < quantidade[indice]; j++){
        if(j > 0){
            printf(", ");
        }
        printf("%d", matriz[indice][j]);
    }
    printf("}\n");
}

// 7. Mostrar todos os conjuntos
void mostrar_todos_conjuntos(int contador, int matriz[M][N], int quantidade[M]){
    for(int indice = 0; indice < contador; indice++){
        printf("\nConjunto %d: {", indice);
        for(int j = 0; j < quantidade[indice]; j++){
            if(j > 0){
                printf(", ");
            }
            printf("%d", matriz[indice][j]);
        }
        printf("}\n");
    }
}

// 8. Busca um valor específico
void buscar_valores(int contador, int matriz[M][N], int quantidade[M]){
    int valor = pedir_valores(contador);
    int referencia = 0;
    for(int i = 0; i < contador; i++){
        if(existe_valor(matriz[i], valor) != -1){
            printf("Conjunto %d\n", i);
            referencia++;
        }
    }

    if(referencia == 0){
        printf("\n" VERMELHO "Desculpa, não existe nenhum conjunto com esse valor" RESET "\n");
    }
}

// 9. Calcula média e o desvio padrão
void media_desvio(int contador, int matriz[M][N], int quantidade[M], float med_dev[P][M]){
    int indice = pedir_indice(contador, "ver a media e o desvio padrao");
    if(quantidade[indice] >= 2){
        float soma = 0.0;
        float media = 0.0;
        float desvio_padrao = 0.0;
    
        for(int j = 0; j < quantidade[indice]; j++){
            soma += matriz[indice][j];
        }
        media = soma / quantidade[indice];
    
        printf("\nMédia = %.2f", media);
    
        for(int j = 0; j < quantidade[indice]; j++){
            desvio_padrao += pow(matriz[indice][j] - media, 2);
        }
    
        desvio_padrao = sqrt(desvio_padrao / (quantidade[indice] - 1));
    
        printf("\nDesvio padrão: %.2f\n", desvio_padrao);
    
        med_dev[0][indice] = media;
        med_dev[1][indice] = desvio_padrao;
    
    }else{
        printf(AMARELO "\nDesculpa, mas o conjunto escolhido precisa de 2 ou mais elementos\n" RESET);
    }
}

int main(){
    // Compatibilidade dos caracteres especiais
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    int opcao; 
    bool erro = false;
    
    int MATRIZ[M][N] = {{0}};
    float med_dev[P][M] = {{0.0f}};
    int quantidade[M] = {0};
    int contador = 0;
    
    do{
        printf("\033[H\033[2J"); // Limpar o terminal

        printf("\n\n");
        printf("╔══════════════════════════════════════════════════╗\n");
        printf("║" NEGRITO_BRANCO "             GERENCIADOR DE CONJUNTOS             ║" RESET "\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  1. Criar um novo conjunto vazio                 ║\n");
        printf("║  2. Inserir dados em um conjunto                 ║\n");
        printf("║  3. Remover um conjunto                          ║\n");
        printf("║  4. Fazer a união entre dois conjuntos           ║\n");
        printf("║  5. Fazer a intersecção entre dois conjuntos     ║\n");
        printf("║  6. Mostrar um conjunto                          ║\n");
        printf("║  7. Mostrar todos os conjuntos                   ║\n");
        printf("║  8. Buscar por um valor                          ║\n");
        printf("║  9. Calcular a média e o desvio padrão           ║\n");
        printf("║ 10. Sair do programa                             ║\n");
        printf("╚══════════════════════════════════════════════════╝\n");
        
        if(erro){
            printf("\n" VERMELHO "Ops! Essa opção não está no menu, tente novamente." RESET "\n");
            erro = false;
        }

        printf("\n" AZUL "Escolha a sua opção: " RESET);

        if(scanf("%d", &opcao) != 1){
            opcao = -1;
        }
        limpar_buffer();

        switch(opcao){
            case 1:
                criar_conjunto(&contador);
                pausar();
                break;
            case 2:
                if(existe_conjunto(contador)){
                    inserir_valores(contador, MATRIZ, quantidade);
                }
                pausar();
                break;
            case 3:
                if(existe_conjunto(contador)){
                    remover_conjunto(&contador, MATRIZ, quantidade, med_dev);
                }
                pausar();
                break;
            case 4:
                if(existe_conjunto(contador)){
                    uniao_conjuntos(&contador, MATRIZ, quantidade);
                }
                pausar();
                break;
            case 5:
                if(existe_conjunto(contador)){
                    intersecao_conjuntos(&contador, MATRIZ, quantidade);
                }
                pausar();
                break;
            case 6:
                if(existe_conjunto(contador)){
                    mostrar_conjunto(contador, MATRIZ, quantidade);
                }
                pausar();
                break;
            case 7:
                if(existe_conjunto(contador)){
                    mostrar_todos_conjuntos(contador, MATRIZ, quantidade);
                }
                pausar();
                break;
            case 8:
                if (existe_conjunto(contador)) {
                    buscar_valores(contador, MATRIZ, quantidade);
                }
                pausar();
                break;
            case 9:
                if(existe_conjunto(contador)){
                    media_desvio(contador, MATRIZ, quantidade, med_dev);
                }
                pausar();
                break;
            case 10:
                printf("\n" NEGRITO_BRANCO "Obrigado por usar o sistema! Volte sempre." RESET "\n");
                return 0;
            default:
                erro = true;
                break;
        }

    }while(true);
}
