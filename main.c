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

int criar_conjunto(int contador){
    if(contador < M){
        printf("\n\033[32 OI");
        return contador++;
    }else{

    }
}

void inserir_valores(int contador, int matriz[M][N], int conjunto){
    if(conjunto >= contador){
        printf("ERRO: Conjunto nao existente!");
        return;
    }

    int i = 0;
    while(true){
        
        if(i >= N) break;
        if(matriz[conjunto][i] != 0){
            //Eh possivel adicionar um numero
            int entrada;
            scanf("%d", &entrada);
            if(entrada == 0) break;

            matriz[conjunto][i] = entrada;
        }
        i++;
    }
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
                criar_conjunto(contador);
                printf("\n\033[32m %d\033[0m", contador);
                pausar();
                break;
            case 2:
                int conjunto;
                printf("Digite o indice do conjunto voce deseja inserir: ");
                scanf("%d", &conjunto);
                inserir_valores(contador, MATRIZ, conjunto);
                break;
            case 10:
                return 0;
            default:
                printf("\nOps! Digite novamente");
                pausar();
                break;
        }

    }while(true);

    return 0;
}