#include <stdio.h>
#include <locale.h>
#include <stdlib.h>   // para system()
#include <unistd.h>   // para sleep()

// Desafio Super Trunfo - Países

int main() {
    //Variáveis para armazenar os dados das cartas
    unsigned int populacao, populacao2, numero_de_pontos_turisticos, numero_de_pontos_turisticos2, pontuacao=0, pontuacao2=0;
    char capital[50], capital2[50], pais[50], pais2[50], codigo_carta[10], codigo_carta2[10];
    float area, area2, densidade1, densidade2, densidade_invertida1, densidade_invertida2;
    double pib, pib2;
    double super_poder, super_poder2;
    
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
                scanf("%u", &populacao);
                
                printf("Digite a área do país (em km²):");
                scanf("%f", &area);
                
                printf("Digite o PIB do país (em dólares): ");
                scanf("%lf", &pib);
                
                printf("Digite o número de pontos turísticos: ");
                scanf("%u", &numero_de_pontos_turisticos);
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
                scanf("%u", &populacao2);
                
                printf("Digite a área do país (em km²): ");
                scanf("%f", &area2);
                
                printf("Digite o PIB do país (em dólares): ");
                scanf("%lf", &pib2);
                
                printf("Digite o número de pontos turísticos: ");
                scanf("%u", &numero_de_pontos_turisticos2);
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

        // * Exibir os dados da carta nº1 cadastrada
        printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
        printf("Código da carta: %s\n", codigo_carta);
        printf("País: %s\n", pais);
        printf("Capital: %s\n", capital);
        printf("População: %u\n", populacao);
        printf("Área: %.2f km²\n", area);
        printf("PIB: %.2lf trilhões de dólares\n", pib);
        printf("Número de pontos turísticos: %u\n", numero_de_pontos_turisticos);
        // ! Cálculos adicionais e exibição de resultados
        densidade1 = (float)populacao / area;
        printf("Densidade populacional: %.2f habitantes/km²\n", densidade1);
        printf("Densidade populacional invertida: %f habitantes/km²\n", densidade_invertida1 = 1 / densidade1);
        printf("PIB per capita: %.2lf dólares\n", pib / populacao); 

        // * Exibir os dados da segunda carta cadastrada
        printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
        printf("Código da carta: %s\n", codigo_carta2);
        printf("País: %s\n", pais2);
        printf("Capital: %s\n", capital2);
        printf("População: %u\n", populacao2);
        printf("Área: %.2f km²\n", area2);
        printf("PIB: %.2f trilhões de dólares\n", pib2);
        printf("Número de pontos turísticos: %u\n", numero_de_pontos_turisticos2);
        // ! Cálculos adicionais e exibição de resultados
        densidade2 = (float)populacao2 / area2;
        printf("Densidade populacional: %.2f habitantes/km²\n", densidade2);
        printf("Densidade populacional invertida: %f habitantes/km²\n", densidade_invertida2 = 1 / densidade2);
        printf("PIB per capita: %.2lf dólares\n" , pib2 / populacao2);

        printf("\n\033[1;32mAgora vamos ao Duelo\033[0m\n");

        printf("\n\033[1;33m*** REGRAS ***\033[0m\n");
        printf("1. Cada jogador cadastra uma carta uma carta com a informação do país escolhido.\n");
        printf("2. O jogador que tiver o maior valor na característica da vez vence a rodada.\n");
        printf("3. O jogo continua até que todas as rodadas sejam jogadas.\n");
        printf("4. O jogador com mais rodadas vencidas no final do jogo é o vencedor.\n");

        // * Implementar o duelo entre as cartas
        // Exemplo de duelo baseado na população
        printf("\n\033[1;34mDuelo - População\033[0m\n");
        if (populacao > populacao2) {
            pontuacao++; // incremento de pontuação
            printf("A carta do país %s vence com uma população de %u habitantes!\n", codigo_carta, populacao);
        } else if (populacao < populacao2) {
            pontuacao2++;
            printf("A carta do país %s vence com uma população de %u habitantes!\n", codigo_carta2, populacao2);
        } else {
            printf("Empate! Ambos as cartas têm a mesma população de %u habitantes.\n", populacao);
        }
        
        // Exemplo de duelo baseado na área
        printf("\n\033[1;34mDuelo - Área\033[0m\n");
        if (area > area2) {
            pontuacao++;
            printf("A carta do país %s vence com uma área de %.2f km²!\n", codigo_carta, area);
        } else if (area < area2) {
            pontuacao2++;
            printf("A carta do país %s vence com uma área de %.2f km²!\n", codigo_carta2, area2);
        }
        else {
            printf("Empate! Ambas as cartas têm a mesma área de %.2f km².\n", area);
        }

        // Exemplo de duelo baseado no PIB
        printf("\n\033[1;34mDuelo - PIB\033[0m\n");
        if (pib > pib2) {
            pontuacao++;
            printf("A carta do país %s vence com um PIB de %.2lf trilhões de dólares!\n", codigo_carta, pib);
        } else if (pib < pib2) {
            pontuacao2++;
            printf("A carta do país %s vence com um PIB de %.2lf trilhões de dólares!\n", codigo_carta2, pib2);
        }
        else {
            printf("Empate! Ambas as cartas têm o mesmo PIB de %.2lf trilhões de dólares.\n", pib);
        }

        // Exemplo de duelo baseado no número de pontos turísticos
        printf("\n\033[1;34mDuelo - Número de Pontos Turísticos\033[0m\n");
        if (numero_de_pontos_turisticos > numero_de_pontos_turisticos2) {
            pontuacao++;
            printf("A carta do país %s vence com %u pontos turísticos!\n", codigo_carta, numero_de_pontos_turisticos);
        } else if (numero_de_pontos_turisticos < numero_de_pontos_turisticos2) {
            pontuacao2++;
            printf("A carta do país %s vence com %u pontos turísticos!\n", codigo_carta2, numero_de_pontos_turisticos2);
        }
        else {
            printf("Empate! Ambas as cartas têm o mesmo número de pontos turísticos: %u.\n", numero_de_pontos_turisticos);
        }

        // Exemplo de duelo baseado na densidade populacional
        printf("\n\033[1;34mDuelo - Densidade Populacional\033[0m\n");
        if (densidade_invertida1 > densidade_invertida2) {
            pontuacao++;
            printf("A carta do país %s vence com uma densidade populacional menor de %.2f habitantes/km²!\n", codigo_carta, densidade_invertida1 = 1 / densidade1);
        }
        else if (densidade_invertida1 < densidade_invertida2) {
            pontuacao2++;
            printf("A carta do país %s vence com uma densidade populacional menor de %.2f habitantes/km²!\n", codigo_carta2, densidade_invertida2 = 1 / densidade2);
        }
        else {
            printf("Empate! Ambas as cartas têm a mesma densidade populacional de %.2f habitantes/km².\n", densidade_invertida1 = 1 / densidade1);
        }

        // Exemplo de duelo baseado no PIB per capita
        float pib_per_capita1 = pib / populacao;
        float pib_per_capita2 = pib2 / populacao2;

        printf("\n\033[1;34mDuelo - PIB per Capita\033[0m\n");
        if (pib_per_capita1 > pib_per_capita2) {
            pontuacao++;
            printf("A carta do país %s vence com um PIB per capita maior de %.2f dólares!\n", codigo_carta, pib_per_capita1);
        } 
        else if (pib_per_capita1 < pib_per_capita2) {
            pontuacao2++;
            printf("A carta do país %s vence com um PIB per capita maior de %.2f dólares!\n", codigo_carta2, pib_per_capita2);
        }
        else {
            printf("Empate! Ambas as cartas têm o mesmo PIB per capita de %.2f dólares.\n", pib_per_capita1);
        }

        // Exemplo de duelo baseado no Super Poder (todos valores somados)
        super_poder = populacao + area + pib + numero_de_pontos_turisticos + densidade1 + pib_per_capita1;
        super_poder2 = populacao2 + area2 + pib2 + numero_de_pontos_turisticos2 + densidade2 + pib_per_capita2;
        printf("\n\033[1;34mDuelo -\033[0m \033[31mSuper Poder\033[0m\n");
        if (super_poder > super_poder2) {
            pontuacao++;
            printf("A carta do país %s vence com um Super Poder de %.2lf!\n", codigo_carta, super_poder);
        }
        else if (super_poder < super_poder2) {
            pontuacao2++;
            printf("A carta do país %s vence com um Super Poder de %.2lf!\n", codigo_carta2, super_poder2);
        }
        else {
            printf("Empate! Ambas as cartas têm o mesmo Super Poder de %.2lf.\n", super_poder);
        }

        printf("\n\033[1;32mE o vencedor é......\033[0m\n");
        // Espera 2 segundos
            sleep(5);

        // Exibir o resultado final do duelo
        printf("\n\033[1;33m*** RESULTADO FINAL DO DUELO ***\033[0m\n");
        printf("Pontuação da carta %s: %u\n", codigo_carta, pontuacao);
        printf("Pontuação da carta %s: %d\n", codigo_carta2, pontuacao2);
        if (pontuacao > pontuacao2) {
            printf("\033[1;32mA carta %s é a grande vencedora do duelo!\033[0m\n", codigo_carta);
        }
        else if (pontuacao < pontuacao2) {
            printf("\033[1;32mA carta %s é a grande vencedora do duelo!\033[0m\n", codigo_carta2);
        }
        else {}       

    // Finalizar o programa
    return 0;
}