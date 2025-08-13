#include <stdio.h>
#include <locale.h>
#include <stdlib.h>   // para system()
#include <unistd.h>   // para sleep()

// Desafio Super Trunfo - Países

int main() {

    // Configuração de localidade para aceitar caracteres especiais - foi mudado o enconding para Western (ISO-8859-1) para funcionar corretamente
    setlocale(LC_ALL, "Portuguese");

    //Variáveis para armazenar os dados das cartas
    unsigned int opcao, opcao2, opcao3;
    unsigned int populacao, populacao2, numero_de_pontos_turisticos, numero_de_pontos_turisticos2, pontuacao = 0, pontuacao2 = 0;
    char capital[50], capital2[50], pais[50], pais2[50], codigo_carta[10], codigo_carta2[10];
    float area, area2, densidade1, densidade2, densidade_invertida1, densidade_invertida2, pibpercapita1, pibpercapita2;
    double pib, pib2;
    double super_poder, super_poder2;

    // menu inicial
    printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
    printf("\n\033[1;34m------------------------\033[0m\n");
    printf("para começar selecione uma opção");
    printf("\n\033[1;34m------------------------\033[0m\n");
    printf("1 - Iniciar Jogo\n");
    printf("2 - Regras do jogo\n");
    printf("3 - Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Iniciando jogo...\n");
            // Espera 3 segundos
            sleep(3);
            // Limpa o terminal (Windows ou Linux/macOS)
            #ifdef _WIN32
                system("cls");

            #else
                system("clear");

            #endif

                // * Solicitar os dados da primeira carta
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
            printf("Carregando menu de ação...\n");

            // Espera 3 segundos
            sleep(3);

            // Limpa o terminal (Windows ou Linux/macOS)
            #ifdef _WIN32
                system("cls");

            #else
                system("clear");

            #endif

            printf("\033[0;36m===================================\033[0m\n");
            printf("\033[0;36m           Menu de Ações           \033[0m\n");
            printf("\033[0;36m===================================\033[0m\n");
            printf("\033[1;34m1 - Verificar cartas cadastradas\033[0m\n");
            printf("\033[1;34m2 - Comparar atributos\033[0m\n");
            printf("\033[1;34m3 - reiniciar programa\033[0m\n");
            printf("\033[0;36m===================================\033[0m\n");
            printf("\033[1;33mEscolha uma opção: \033[0m");
            scanf("%d", &opcao2);
            printf("\n");
            switch (opcao2) {

                case 1:
                printf("\033[0;36m===================================\033[0m\n");
                // * Exibir os dados da carta nº1 cadastrada
                printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
                printf("Código da carta: %s\n", codigo_carta);
                printf("País: %s\n", pais);
                printf("Capital: %s\n", capital);
                printf("População: %u\n", populacao);
                printf("Área: %.2f km²\n", area);
                printf("PIB: %.2lf trilhões de dólares\n", pib);
                printf("Número de pontos turísticos: %u\n", numero_de_pontos_turisticos);
                densidade1 = populacao / area;
                printf("Densidade populacional: %.2f habitantes/km²\n", densidade1);
                densidade_invertida1 = 1 / densidade1;
                printf("Densidade populacional invertida: %f habitantes/km²\n", densidade_invertida1);
                pibpercapita1 = pib / populacao;
                printf("PIB per capita: %.2lf dólares\n", pibpercapita1); 

                // * Exibir os dados da segunda carta cadastrada
                printf("\n\033[1;34mSuper Trunfo\033[0m - \033[1;33mPaíses\033[0m\n");
                printf("Código da carta: %s\n", codigo_carta2);
                printf("País: %s\n", pais2);
                printf("Capital: %s\n", capital2);
                printf("População: %u\n", populacao2);
                printf("Área: %.2f km²\n", area2);
                printf("PIB: %.2f trilhões de dólares\n", pib2);
                printf("Número de pontos turísticos: %u\n", numero_de_pontos_turisticos2);
                densidade2 = populacao2 / area2;
                printf("Densidade populacional: %.2f habitantes/km²\n", densidade2);
                densidade_invertida2 = 1 / densidade2;
                printf("Densidade populacional invertida: %f habitantes/km²\n", densidade_invertida2);
                pibpercapita2 = pib2 / populacao2;
                printf("PIB per capita: %.2lf dólares\n" , pibpercapita2);
                printf("\033[0;36m===================================\033[0m\n");
                break;

                case 2:
                printf("\033[0;36m===================================\033[0m\n");
                printf("\033[1;34mComparação de atributos\033[0m\n");
                printf("\033[0;36m===================================\033[0m\n");
                printf("\033[1;34m1 - Comparar população\033[0m\n");
                printf("\033[1;34m2 - Comparar área\033[0m\n");
                printf("\033[1;34m3 - Comparar PIB\033[0m\n");
                printf("\033[1;34m4 - Comparar número de pontos turísticos\033[0m\n");
                printf("\033[1;34m5 - Comparar densidade populacional\033[0m\n");
                printf("\033[1;34m6 - Comparar PIB per capita\033[0m\n");
                printf("\033[0;36m===================================\033[0m\n");
                printf("\n");
                printf("\033[1;34mEscolha uma opção:\033[0m\n");
                scanf("%d", &opcao3);
                printf("\n");
                switch (opcao3) {

                    case 1:
                    printf("\033[0;36m===================================\033[0m\n");
                    printf("%s vs %s\n", pais, pais2);
                    printf("População\n");
                    printf("%s tem uma população de %u habitantes\n", pais, populacao);
                    printf("%s tem uma população de %u habitantes\n", pais2, populacao);
                    printf("\033[0;36m===================================\033[0m\n");
                    if (populacao > populacao2) {
                        printf("%s venceu com uma população maior de %u habitantes\n", pais, populacao - populacao2);
                        } else if (populacao < populacao2) {
                            printf("%s venceu com uma população maior de %u habitantes\n", pais2, populacao2 - populacao);
                            } else {
                                printf("EMPATE!!!, Ambos os países têm a mesma população\n");
                                }
                    break;
                    case 2:
                    printf("\033[0;36m===================================\033[0m\n");
                    printf("%s vs %s\n", pais, pais2);
                    printf("Área\n");
                    printf("%s tem uma área de %.2f km²\n", pais, area);
                    printf("%s tem uma área de %.2f km²\n", pais2, area2);
                    printf("\033[0;36m===================================\033[0m\n");
                    if (area > area2) {
                        printf("%s venceu com uma área maior de %.2f km²\n", pais, area - area2);
                        } else if (area < area2) {
                            printf("%s venceu com uma área maior de %.2f km²\n", pais, area2 - area);
                            } else {
                                printf("EMPATE!!!, Ambos os países têm a mesma área\n");
                                }
                    break;
                    case 3:
                    printf("\033[0;36m===================================\033[0m\n");
                    printf("%s vs %s\n", pais, pais2);
                    printf("PIB\n");
                    printf("%s tem um PIB de U$ %.2f de doláres\n", pais, pib);
                    printf("%s tem um PIB de U$ %.2f de doláres\n", pais2, pib2);
                    printf("\033[0;36m===================================\033[0m\n");
                    if (pib > pib2) {
                        printf("%s venceu com um PIB maior de U$ %.2f de doláres\n");
                        } else if (pib < pib2) {
                            printf("%s venceu com um PIB maior de U$ %.2f de doláres\n");
                            } else {
                                printf("EMPATE!!!, Ambos os países têm o mesmo PIB\n");
                                }
                    break;
                    case 4:
                    printf("\033[0;36m===================================\033[0m\n");
                    printf("%s vs %s\n", pais, pais2);
                    printf("Pontos Turísticos\n");
                    printf("%s tem %u pontos turísticos\n", pais, numero_de_pontos_turisticos);
                    printf("%s tem %u pontos turísticos\n", pais2, numero_de_pontos_turisticos2);
                    printf("\033[0;36m===================================\033[0m\n");
                    if (numero_de_pontos_turisticos > numero_de_pontos_turisticos2) {
                        printf("%s venceu com %u pontos turísticos\n", pais, numero_de_pontos_turisticos - numero_de_pontos_turisticos2);
                        } else if (numero_de_pontos_turisticos < numero_de_pontos_turisticos2) {
                            printf("%s venceu com %u pontos turísticos\n", pais2, numero_de_pontos_turisticos2 - numero_de_pontos_turisticos);
                            } else {
                                printf("EMPATE!!!, Ambos os países têm o mesmo número de pontos turísticos");
                                }
                            
                    break;
                    case 5: 
                    printf("\033[0;36m===================================\033[0m\n");
                    printf("%s vs %s\n", pais, pais2);
                    printf("Densidade Populacional\n");
                    densidade1 = (populacao / area);
                    printf("%s tem uma densidade populacional de %.2f habitantes/km²\n", pais, densidade1);
                    densidade2 = (populacao2 / area2);
                    printf("%s tem uma densidade populacional de %.2f habitantes/km²\n", pais2, densidade2);
                    printf("\033[0;36m===================================\033[0m\n");
                    densidade_invertida1 = 1 / densidade1;
                    densidade_invertida2 = 1 / densidade2;
                    if (densidade_invertida1 > densidade_invertida2) {
                        printf("%s venceu com uma densidade populacional nenor de %.2f habitantes por km²\n", pais, densidade1 / densidade2);
                        } else if (densidade_invertida1 < densidade_invertida2) {
                            printf("%s venceu com uma densidade populacional menor de %.2f habitantes por km²\n", pais2, densidade2 / densidade1);
                            } else {
                                printf("EMPATE!!!, Ambos os países têm a mesma densidade populacional");
                                }
                    
                    break;
                    case 6:
                    printf("\033[0;36m===================================\033[0m\n");
                    printf("%s vs %s\n", pais, pais2);
                    printf("PIB per capita\n");
                    pibpercapita1 = (pib / populacao);
                    printf("%s tem um PIB per capita de U$ %.2f de doláres\n", pais, pibpercapita1);
                    pibpercapita2 = (pib2 / populacao2);
                    printf("%s tem um PIB per capita de U$ %.2f de doláres\n", pais2, pibpercapita2);
                    printf("\033[0;36m===================================\033[0m\n");
                    if (pibpercapita1 > pibpercapita2) {
                        printf("%s venceu com um PIB per capita maior de U$ %.2f de doláres\n", pais, pibpercapita1 - pibpercapita2);
                        } else if (pibpercapita1 < pibpercapita2) {
                            printf("%s venceu com um PIB per capita maior de U$ %.2f de doláres\n", pais2, pibpercapita2 - pibpercapita1);
                            } else {
                                printf("EMPATE!!!, Ambos os países têm o mesmo PIB per capita\n");
                                }
                    break;
                    default:
                    printf("\033[0;36m===================================\033[0m\n");
                    printf("opção inválida!\n");
                    printf("\033[0;36m===================================\033[0m\n");

                }
                break;
                case 3:
                printf("\033[0;36m===================================\033[0m\n");
                printf("Reiniciando o programa!\n");
                printf("\033[0;36m===================================\033[0m\n");

                system("pause");
                system("cls");
                main();

                break;
                default:
                printf("\033[0;36m===================================\033[0m\n");
                printf("opção inválida!\n");
                printf("\033[0;36m===================================\033[0m\n");
            }
    break;
    case 2:
    printf("\033[0;36m===================================\033[0m\n");
    printf("\033[1;34m========== REGRAS DO JOGO =========\033[0m\n");
    printf("\033[0;36m===================================\033[0m\n");
    printf("\n");
    printf("1. O jogador cadastra duas com a informação dos países escolhidos.\n");
    printf("2. O jogador que tiver o maior valor na característica escolhida vence.\n");
    printf("3. O jogador pode escolher entre 6 opções de caracteristicas.\n");
    printf("4. A caracteristica de densidade, é calculada invertidamente ganhando quem tiver a menor\n");
    printf("\n");
    printf("\033[0;36m===================================\033[0m\n");
    system("pause");
    system("cls");
    main();

    break;
    case 3:
    printf("\033[0;36m===================================\033[0m\n");
    printf("Obrigado por jogar!\n");
    printf("\033[0;36m===================================\033[0m\n");
    system("pause");
    break;

    }
    return 0;
}