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
        printf(VERDE "Conjunto criado! Agora existem %d conjunto(s)." RESET "\n", *contador);
    }else{
        printf(VERMELHO "Limite de %d conjuntos atingido." RESET "\n", M);
    }
}

// 2.
void inserir_valores(int contador, int matriz[M][N], int conjunto){
    if(conjunto >= contador){
        printf(VERMELHO "ERRO: Conjunto nao existente!\n" RESET);
        return;
    }

    int i = 0;
    while(true){
        
        if(i >= N) break;
        if(matriz[conjunto][i] == 0){
            //Eh possivel adicionar um numero
            int entrada;
            scanf("%d", &entrada);
            if(entrada == 0) break;

            matriz[conjunto][i] = entrada;
        }
        i++;
    }
}

// 6.
void mostrar_conjunto(int contador, int MATRIZ[M][N]){

}

int main(){
    int opcao; 
    bool erro = false;
    
    int MATRIZ[M][N] = {{0}};
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
                    int conjunto;
                    printf("Digite o indice do conjunto voce deseja inserir: ");
                    scanf("%d", &conjunto);
                    inserir_valores(contador, MATRIZ, conjunto);
                }
                pausar();
                break;
            case 6:
                if(existe_conjunto(contador)){
                    mostrar_conjunto(contador, MATRIZ);
                }
                pausar();
                break;
            case 10:
                return 0;
            default:
                erro = true;
                break;
        }

    }while(true);

    return 0;
}
