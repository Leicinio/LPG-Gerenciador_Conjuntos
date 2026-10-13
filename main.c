#include <stdio.h>
#include <stdbool.h>

// Tamanho da Matriz
#define M 5
#define N 5

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

// 2. Inserir valores dentro de um indice da matriz escolhido pelo usuário
void inserir_valores(int contador, int matriz[M][N], int quantidade[M]){
    int indice = pedir_indice_valores(0, contador, "inserir valores");
    int valor;

    if(quantidade[indice] != N){
        for(int j = quantidade[indice]; j < M; j++){
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
            matriz[indice][j] = valor;
            quantidade[indice]++;
        }
    }else{
        printf("\n"VERMELHO "O Conjunto não suporta mais valores" RESET "\n");
    }
}

// 6. Mostrar o conjunto escolhido pelo usuário
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

// 7. Mostrar todos os conjuntos já criados
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

// 8. Busca um valor especifíco dentro de toda a matiz criada
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

int main(){
    // Menu
    int opcao; 
    bool erro = false;
    
    int MATRIZ[M][N] = {{0}};
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
