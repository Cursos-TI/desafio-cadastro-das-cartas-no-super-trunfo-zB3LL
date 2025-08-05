#include <stdio.h>
#include <locale.h>
#include <stdlib.h>   // para system()
#include <unistd.h>   // para sleep()

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.
//Teste larissa

int main() {
    //Variáveis para armazenar os dados das cartas
    int populacao, populacao2, numero_de_pontos_turisticos, numero_de_pontos_turisticos2;
    char capital[50], capital2[50], pais[50], pais2[50], codigo_carta[10], codigo_carta2[10];
    float area, area2;
    float pib, pib2;
    
        // Configuração de localidade para aceitar caracteres especiais - foi mudado o enconding para Western (ISO-8859-1) para funcionar corretamente
        setlocale(LC_ALL, "Portuguese");

                // * Solicitar os dados da primeira carta
                printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");

                printf("\033[0;36mVamos cadastrar a carta número 1 dos Países\033[0m\n");
                printf("Digite o nome do país: ");
                scanf("%s", pais);
                
                printf("Digite o codigo da carta: ");
                scanf("%s", codigo_carta);
                
                printf("Digite o nome da capital: ");
                scanf("%s", capital);
                
                printf("Digite a população do país: ");
                scanf("%d", &populacao);
                
                printf("Digite a área do país (em km²:");
                scanf("%f", &area);
                
                printf("Digite o PIB do país (em dólares): ");
                scanf("%f", &pib);
                
                printf("Digite o número de pontos turísticos: ");
                scanf("%d", &numero_de_pontos_turisticos);
                printf("\n\033[1;32mObrigado por cadastrar a carta!\033[0m\n");
                
                printf("\033[0;36mCarta cadastrada com sucesso!\033[0m\n");
                
                // * Cadastro da segunda carta
                printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
                
                printf("\033[0;36mVamos cadastrar a carta número 2 dos Países\033[0m\n");
                printf("Digite o nome do país: ");
                scanf("%s", pais2);
                
                printf("Digite o codigo da carta: ");
                scanf("%s", codigo_carta2);
                
                printf("Digite o nome da capital: ");
                scanf("%s", capital2);
                
                printf("Digite a população do país: ");
                scanf("%d", &populacao2);
                
                printf("Digite a área do país (em km²): ");
                scanf("%f", &area2);
                
                printf("Digite o PIB do país (em dólares): ");
                scanf("%f", &pib2);
                
                printf("Digite o número de pontos turísticos: ");
                scanf("%d", &numero_de_pontos_turisticos2);
                printf("\n\033[1;32mObrigado por cadastrar a carta!\033[0m\n");
                
                printf("\033[0;36mCarta cadastrada com sucesso!\033[0m\n");

            // Mostra mensagem de carregamento
            printf("Carregando informações...\n");

            // Espera 2 segundos
            sleep(2);

            // Limpa o terminal (Windows ou Linux/macOS)
            #ifdef _WIN32
                system("cls");

            #else
                system("clear");

            #endif

        // Exibir os dados da carta nº1 cadastrada
        printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
        printf("Código da carta: %s\n", codigo_carta);
        printf("País: %s\n", pais);
        printf("Capital: %s\n", capital);
        printf("População: %d\n", populacao);
        printf("Área: %.2f km²\n", area);
        printf("PIB: %.2f trilhões de dólares\n", pib);
        printf("Número de pontos turísticos: %d\n", numero_de_pontos_turisticos);
        // ! Cálculos adicionais e exibição de resultados
        printf("Densidade populacional: %.2f habitantes/km²\n", (float)populacao / area);
        printf("PIB per capita: %.2f dólares\n", pib / populacao); 

        // Exibir os dados da segunda carta cadastrada
        printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
        printf("Código da carta: %s\n", codigo_carta2);
        printf("País: %s\n", pais2);
        printf("Capital: %s\n", capital2);
        printf("População: %d\n", populacao2);
        printf("Área: %.2f km²\n", area2);
        printf("PIB: %.2f trilhões de dólares\n", pib2);
        printf("Número de pontos turísticos: %d\n", numero_de_pontos_turisticos2);
        // ! Cálculos adicionais e exibição de resultados
        printf("Densidade populacional: %.2f habitantes/km²\n", (float)populacao2 / area2);
        printf("PIB per capita: %.2f dólares\n" , pib2 / populacao2);

    // Finalizar o programa
    return 0;
}
