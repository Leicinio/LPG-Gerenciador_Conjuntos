#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Tamanho da Matriz
#define M 8 // Conjuntos 
#define N 10 // Elementos
#define P 2 

// Redefinir todas as formatações de texto
#define RESET    "\033[0m"

// Cores Padrão
#define VERMELHO "\033[91m"
#define VERDE    "\033[92m"
#define AMARELO  "\033[93m"
#define AZUL     "\033[94m"
#define MAGENTA  "\033[95m"
#define CIANO    "\033[96m"
#define BRANCO   "\033[97m"

// Cores em Negrito
#define NEGRITO_VERMELHO "\033[1;91m"
#define NEGRITO_VERDE    "\033[1;92m"
#define NEGRITO_AMARELO  "\033[1;93m"
#define NEGRITO_AZUL     "\033[1;94m"
#define NEGRITO_MAGENTA  "\033[1;95m"
#define NEGRITO_CIANO    "\033[1;96m"
#define NEGRITO_BRANCO   "\033[1;97m"

// Cores de Fundo
#define FUNDO_VERMELHO "\033[7;91m"
#define FUNDO_VERDE    "\033[7;92m"
#define FUNDO_AMARELO  "\033[7;93m"
#define FUNDO_AZUL     "\033[7;94m"
#define FUNDO_MAGENTA  "\033[7;95m"
#define FUNDO_CIANO    "\033[7;96m"
#define FUNDO_BRANCO   "\033[7;97m"

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

// 2-6-8
int pedir_indice_valores(int chave, int contador, char *acao){
    if(chave == 0){
        int indice = -1;
        do{
            printf("\nEm qual conjunto deseja %s(0 - %d): ", acao, contador - 1);
            if(scanf("%d", &indice) != 1){
                indice = -1;
            }
            limpar_buffer();
            if(indice < 0 || indice >= contador){
                printf(VERMELHO "Índice inválido!" RESET "\n");
            }

        }while(indice < 0 || indice >= contador);

        return indice;
    }else{
        int valor = 0;
        int leu_corretamente = 0;
        do{
            printf("\nQual valor deseja buscar dentro dos conjuntos: ", acao);
            leu_corretamente = scanf("%d", &valor);
            limpar_buffer();
            if (leu_corretamente != 1) {
                printf(VERMELHO "Valor inválido! Digite um número." RESET "\n");
            }
        }while(leu_corretamente != 1);
        
        return valor;
    }
}

//Pode ser utilizado no item 8 no futuro.
//Retorna -1 se não existe no conjunto, retorna o índice se existe no conjunto.
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
    int indice = pedir_indice_valores(0, contador, "inserir valores");
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
                printf("\n"VERMELHO "Esse valor já existe nesse conjunto" RESET "\n");
                j--;
                continue;
            }

            matriz[indice][j] = valor;
            quantidade[indice]++;
        }
    }else{
        printf("\n"VERMELHO "O Conjunto não suporta mais valores" RESET "\n");
    }
}

// 3. Remover um conjunto
void remover_conjunto(int *contador, int matriz[M][N], int quantidade[M]){
    int indice = pedir_indice_valores(0, *contador, "remover");
    int conjunto_maximo = *contador - 1;

    for(int i = indice; i < conjunto_maximo; i++){ 
        for(int j = 0; j < N; j++){
            matriz[i][j] = matriz[i+1][j];
        }
        quantidade[i] = quantidade[i+1];
    }


    for(int i = 0; i < N; i++){
        matriz[conjunto_maximo][i] = 0;
    }
    quantidade[conjunto_maximo] = 0;
    (*contador)--;

    printf("\n" AMARELO "Conjunto removido! Os conjuntos com indíces maiores foram movidos. Agora existem %d conjunto(s)." RESET "\n", *contador);
}

// 4. União de Conjuntos
void uniao_conjuntos(int *contador, int matriz[M][N], int quantidade[M]){
    if(*contador < 1){
        printf("\n" VERMELHO "Você precisa de no mínimo 1 conjunto criado.\n");
        return;
    }
    if(*contador >= M){
        printf("\n" VERMELHO "O limite de conjuntos já foi atingido.\n");
        return;
    }

    int indice = pedir_indice_valores(0, *contador, "unir primeiro");
    int indice2 = pedir_indice_valores(0, *contador, "unir segundo");

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
    printf("\n" VERDE "O conjunto união foi criado no índice %d.\n", (*contador - 1));


}


// 5. Interseção de conjuntos
void intersecao_conjuntos(int *contador, int matriz[M][N], int quantidade[M]){
    if(*contador < 1){
        printf("\n" VERMELHO "Você precisa de no mínimo 1 conjunto criado.\n");
        return;
    }
    if(*contador >= M){
        printf("\n" VERMELHO "O limite de conjuntos já foi atingido.\n");
        return;
    }

    int indice = pedir_indice_valores(0, *contador, "unir primeiro");
    int indice2 = pedir_indice_valores(0, *contador, "unir segundo");

    int k = 0;

    for(int i = 0; i < N; i++){
        int valor1 = matriz[indice][i];
        if(valor1 == 0 && k >= N){
            break;
        }

        for(int j = 0; j < N; j++){
            int valor2 = matriz[indice2][j];
            if(valor2 == 0){
                break;
            }

            if(valor1 == valor2){
                matriz[*contador][k] = valor1;
                quantidade[*contador]++;
                k++;
            }
        }
    }

    (*contador)++;
    printf("\n" VERDE "O conjunto interseção foi criado no índice %d.\n", (*contador - 1));
}

// 6. Mostrar um conjunto 
void mostrar_conjunto(int contador, int matriz[M][N], int quantidade[M]){
    int indice = pedir_indice_valores(0, contador, "mostrar");

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

// 8. Busca um valor especifíco
void buscar_valores(int contador, int matriz[M][N], int quantidade[M]){
    int valor = pedir_indice_valores(1, contador,"");
    int referencia = 0;
    for(int indice = 0; indice < contador; indice++){
        bool encontrado = false;
        for(int j = 0; j < quantidade[indice]; j++){
            if(valor == matriz[indice][j]){
                encontrado = true;
                referencia++;
                break;
            }
        }

        if(encontrado){
            printf("\nConjunto %d\n", indice);
        }
    }
    if(referencia == 0){
        printf("\n" VERMELHO "Desculpa, não existe nenhum conjunto com esse valor\n");
    }
}

// 9. Calcula media e o desvio
void media_desvio(int contador, int matriz[M][N], int quantidade[M], int med_dev[P][N]){
    int indice = pedir_indice_valores(0, contador, "ver a media e o desvio padrao");
    if(quantidade[indice] >= 2){
        float soma = 0.0;
        float media = 0.0;
        float desvio_padrao = 0.0;
    
        for(int j = 0; j < quantidade[indice]; j++){
            soma += matriz[indice][j];
        }
        media = soma/quantidade[indice];
    
        printf("\nMedia = %.2f", media);
    
        for(int j = 0; j < quantidade[indice]; j++){
            desvio_padrao += pow(matriz[indice][j] - media, 2);
        }
    
        desvio_padrao = sqrt(desvio_padrao/(quantidade[indice] - 1));
    
        printf("\nDesvio padrão: %.2f\n", desvio_padrao);
    
        med_dev[0][indice] = media;
        med_dev[1][indice] = desvio_padrao;
    
    }else{
        printf(AMARELO "\nDesculpa, mas o conjunto escolhido precisa de 2 ou mais elementos" RESET);
    }
}

int main(){

    //Compatibilidade dos caracteres especiais
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    // Menu
    int opcao; 
    bool erro = false;
    
    int MATRIZ[M][N] = {{0}};
    int med_dev[P][N] = {0};
    int quantidade[M] = {0};
    int contador = 0;
    
    do{
        printf("\033[H\033[2J"); // Limpar o terminal

        printf("\n\n");
        printf("╔══════════════════════════════════════════════════╗\n");
        printf("║" NEGRITO_BRANCO "              GERENCIADOR DE CONJUNTOS            ║" RESET "\n");
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
            printf("\n"VERMELHO "Ops! Essa opção não está no menu, tente novamente." RESET "\n");
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
                    remover_conjunto(&contador, MATRIZ, quantidade);
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

    return 0;
}
