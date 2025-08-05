#include <stdio.h>
#include <locale.h>
#include <stdlib.h>   // para system()
#include <unistd.h>   // para sleep()

// Desafio Super Trunfo - Pa�ses
// Tema 1 - Cadastro das Cartas
// Este c�digo inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os coment�rios para implementar cada parte do desafio.
//Teste larissa

int main() {
    //Vari�veis para armazenar os dados das cartas
    int populacao, populacao2, numero_de_pontos_turisticos, numero_de_pontos_turisticos2;
    char capital[50], capital2[50], pais[50], pais2[50], codigo_carta[10], codigo_carta2[10];
    float area, area2;
    float pib, pib2;
    
        // Configura��o de localidade para aceitar caracteres especiais - foi mudado o enconding para Western (ISO-8859-1) para funcionar corretamente
        setlocale(LC_ALL, "Portuguese");

                // * Solicitar os dados da primeira carta
                printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPa�ses\033[0m\n");

                printf("\033[0;36mVamos cadastrar a carta n�mero 1 dos Pa�ses\033[0m\n");
                printf("Digite o nome do pa�s: ");
                scanf("%s", pais);
                
                printf("Digite o codigo da carta: ");
                scanf("%s", codigo_carta);
                
                printf("Digite o nome da capital: ");
                scanf("%s", capital);
                
                printf("Digite a popula��o do pa�s: ");
                scanf("%d", &populacao);
                
                printf("Digite a �rea do pa�s (em km�:");
                scanf("%f", &area);
                
                printf("Digite o PIB do pa�s (em d�lares): ");
                scanf("%f", &pib);
                
                printf("Digite o n�mero de pontos tur�sticos: ");
                scanf("%d", &numero_de_pontos_turisticos);
                printf("\n\033[1;32mObrigado por cadastrar a carta!\033[0m\n");
                
                printf("\033[0;36mCarta cadastrada com sucesso!\033[0m\n");
                
                // * Cadastro da segunda carta
                printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPa�ses\033[0m\n");
                
                printf("\033[0;36mVamos cadastrar a carta n�mero 2 dos Pa�ses\033[0m\n");
                printf("Digite o nome do pa�s: ");
                scanf("%s", pais2);
                
                printf("Digite o codigo da carta: ");
                scanf("%s", codigo_carta2);
                
                printf("Digite o nome da capital: ");
                scanf("%s", capital2);
                
                printf("Digite a popula��o do pa�s: ");
                scanf("%d", &populacao2);
                
                printf("Digite a �rea do pa�s (em km�): ");
                scanf("%f", &area2);
                
                printf("Digite o PIB do pa�s (em d�lares): ");
                scanf("%f", &pib2);
                
                printf("Digite o n�mero de pontos tur�sticos: ");
                scanf("%d", &numero_de_pontos_turisticos2);
                printf("\n\033[1;32mObrigado por cadastrar a carta!\033[0m\n");
                
                printf("\033[0;36mCarta cadastrada com sucesso!\033[0m\n");

            // Mostra mensagem de carregamento
            printf("Carregando informa��es...\n");

            // Espera 2 segundos
            sleep(2);

            // Limpa o terminal (Windows ou Linux/macOS)
            #ifdef _WIN32
                system("cls");

            #else
                system("clear");

            #endif

        // Exibir os dados da carta n�1 cadastrada
        printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPa�ses\033[0m\n");
        printf("C�digo da carta: %s\n", codigo_carta);
        printf("Pa�s: %s\n", pais);
        printf("Capital: %s\n", capital);
        printf("Popula��o: %d\n", populacao);
        printf("�rea: %.2f km�\n", area);
        printf("PIB: %.2f trilh�es de d�lares\n", pib);
        printf("N�mero de pontos tur�sticos: %d\n", numero_de_pontos_turisticos);
        // ! C�lculos adicionais e exibi��o de resultados
        printf("Densidade populacional: %.2f habitantes/km�\n", (float)populacao / area);
        printf("PIB per capita: %.2f d�lares\n", pib / populacao); 

        // Exibir os dados da segunda carta cadastrada
        printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPa�ses\033[0m\n");
        printf("C�digo da carta: %s\n", codigo_carta2);
        printf("Pa�s: %s\n", pais2);
        printf("Capital: %s\n", capital2);
        printf("Popula��o: %d\n", populacao2);
        printf("�rea: %.2f km�\n", area2);
        printf("PIB: %.2f trilh�es de d�lares\n", pib2);
        printf("N�mero de pontos tur�sticos: %d\n", numero_de_pontos_turisticos2);
        // ! C�lculos adicionais e exibi��o de resultados
        printf("Densidade populacional: %.2f habitantes/km�\n", (float)populacao2 / area2);
        printf("PIB per capita: %.2f d�lares\n" , pib2 / populacao2);

    // Finalizar o programa
    return 0;
}
