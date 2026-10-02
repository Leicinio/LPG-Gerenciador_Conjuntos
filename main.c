#include <stdio.h>
#include <stdbool.h>

// Tamanho da Matriz
#define M 5
#define N 5

// Cores para os textos
#define VERMELHO "\033[31m"
#define AMARELO  "\033[33m"
#define VERDE    "\033[32m"
#define AZUL     "\033[34m"
#define BRANCO   "\033[37m"
#define NEGRITO  "\033[1;37m"
#define RESET    "\033[0m"

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pausar(){
    printf("\n" NEGRITO "Pressione Enter para continuar..." RESET);
    limpar_buffer();
}

/*
    Fiz essa função para impedir, o usúario chamar uma função, sem ter criado
    um conjunto, o que acha?
*/
int existe_conjunto(int contador){
    if(contador == 0){
        printf(VERMELHO "\nVocê precisa criar um novo conjunto!" RESET "\n");
        return false;
    }

    return true;
}

// 1.
void criar_conjunto(int *contador){
    if(*contador < M){
        (*contador)++;
        printf("\n" VERDE "Conjunto criado! Agora existem %d conjunto(s)." RESET "\n", *contador);
    }else{
        printf("\n" VERMELHO "Limite de %d conjuntos atingido." RESET "\n", M);
    }
}

// 2.
void inserir_valores(int contador, int matriz[][N], int quantidade[]){
    int indice = 0;
    int valor;
    do{
        printf("Em qual conjunto deseja inserir valores(0 - %d)", contador - 1);
        if(scanf("%d", &indice) != 1){
            indice = -1;
        }
        limpar_buffer();
        if(indice < 0 || indice >= contador){
            printf(VERMELHO "Índice inválido!" RESET "\n");
        }
    }while(indice < 0 || indice >= contador);

    for(int j = quantidade[indice]; j < N; j++){
        printf("Digite um valor (0 para parar): ");
        scanf("%d", &valor);

        if(valor == 0){
            break;
        }
        matriz[indice][j] = valor;
        quantidade[indice]++;
    }
}

// 6.
void mostrar_conjunto(int contador, int MATRIZ[M][N]){
    int indice = 0;
    
    do{
        printf("Qual o conjunto deseja ver os valores(0 - %d)", contador - 1);
        if(scanf("%d", &indice) != 1){
            indice = -1;
        }
        limpar_buffer();
        if(indice < 0 || indice >= contador){
            printf(VERMELHO "Índice inválido!" RESET "\n");
        }
    }while(indice < 0 || indice >= contador);

    printf(" Conjunto %d: {", indice);
    for(int j = 0; j < quantidade[indice]; j++){
        if(j > 0){
            printf(", ");
        }
        printf("%d", matriz[indice][j]);
    }
    printf("}\n");
}

int main(){
    int opcao; 
    bool erro = false;
    
    int MATRIZ[M][N] = {{0}};
    int quantidade[N] = {0};
    int contador = 0;
    
    do{
        printf("\033[H\033[2J"); // Limpar o terminal

        printf("╔══════════════════════════════════════════════════╗\n");
        printf("║" NEGRITO "              GERENCIADOR DE CONJUNTOS            ║" RESET "\n");
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
            printf(VERMELHO "Ops! Essa opção não está no menu, tente novamente." RESET "\n");
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
            case 10:
                printf("\n" NEGRITO "Obrigado por usar o sistema! Volte sempre." RESET "\n");
                return 0;
            default:
                erro = true;
                break;
        }

    }while(true);

    return 0;
}
