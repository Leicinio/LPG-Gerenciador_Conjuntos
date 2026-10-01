#include <stdio.h>
#include <stdbool.h>

#define M 5
#define N 5

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pausar(){
    printf("\n\033[1;37mPressione Enter para continuar...\033[0m");
    limpar_buffer();
}

int main(){
    int MATRIZ[M][N] = {{0}};

    int opcao;
    int contador = 0;
    
    do{
        printf("\033[H\033[2J"); // Limpar o terminal

        printf("╔══════════════════════════════════════════════════╗\n");
        printf("║              GERENCIADOR DE CONJUNTOS            ║\n");
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
        printf("Digite uma das opções: ");

        if(scanf("%d", &opcao) != 1){
            opcao = -1;
        }
        limpar_buffer();

        switch(opcao){
            case 1:
                if(contador < M){
                    contador++;
                    printf("\n\033[32mO conjunto foi espandido(%d) \033[0m\n", contador);
                }else{
                    printf("\n \033[32m Limite máximo para o conjunto atingindo! \033[0m\n");
                }
                pausar();
                break;
            case 10:
                return 0;
            default:
                printf("\n\033[31mOps! Houve um erro de digitação, tente novamente ;)\033[0m\n");
                pausar();
                break;
        }

    }while(true);

    return 0;
}