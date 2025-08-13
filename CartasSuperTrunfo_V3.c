/*
    SUPER TRUNFO - PAÍSES (V3.0)
    ------------------------------------------------------------
    O objetivo desta versão é modernizar o código:
      - Armazenar as cartas em uma "struct" (tipo composto).
      - Calcular e guardar atributos derivados (PIB per capita,
        densidade e densidade invertida).
      - Menus com cores, UX melhor e validações.
      - Duelo com 4 rodadas (4 atributos distintos).
      - Pontuação por rodada e soma final dos 4 atributos usados.
      - Densidade: regra especial -> menor densidade vence,
        por isso usamos a "densidade invertida" nas comparações.

    O código é largamente comentado para fins didáticos.
*/

#include <stdio.h>     // printf, scanf
#include <stdlib.h>    // system, rand, srand
#include <string.h>    // strcpy, strcmp
#include <locale.h>    // setlocale
#include <time.h>      // time (semente do rand)
#ifdef _WIN32
  #include <windows.h> // Sleep(ms) no Windows
#else
  #include <unistd.h>  // usleep(ms*1000) no Linux/macOS
#endif

/* ============================================================
   PALETA DE CORES ANSI (strings com sequências de escape)
   ------------------------------------------------------------
   Usamos #define para facilitar. Ex.: printf(C_TIT "Olá" C_RESET);
   ============================================================ */
#define C_RESET   "\033[0m"
#define C_DIM     "\033[2m"
#define C_BOLD    "\033[1m"
#define C_TIT     "\033[1;38;5;39m"   // azul ciano vivo (títulos)
#define C_SUB     "\033[1;38;5;45m"   // roxo/azul (subtítulos)
#define C_OK      "\033[1;38;5;82m"   // verde
#define C_WARN    "\033[1;38;5;214m"  // laranja
#define C_ERR     "\033[1;38;5;196m"  // vermelho
#define C_MENU    "\033[38;5;81m"     // azul claro
#define C_GRAY    "\033[38;5;245m"    // cinza
#define C_BAR     "\033[38;5;219m"    // rosa (barrinhas de loading)

/* ============================================================
   TIPOS E ENUMERAÇÕES
   ============================================================ */

/* Representa uma carta de país com atributos "básicos" e os
   "derivados" que vamos calcular uma única vez. */
typedef struct {
    char  codigo[5];
    char  nome[50];
    unsigned long area;          // km²
    unsigned long populacao;     // habitantes
    double pib;                  // em dólares (valor total)
    unsigned long pontosTur;     // pontos turísticos

    // Atributos derivados
    double pibPerCapita;         // pib / populacao
    double densidade;            // populacao / area
    double densidadeInv;         // 1 / densidade  (para comparar "maior vence")
} Carta;

/* Enumerador de atributos possíveis (facilita menus e lógica) */
typedef enum {
    A_POPULACAO = 1,
    A_AREA      = 2,
    A_PIB       = 3,
    A_PONTOS    = 4,
    A_DENSIDADE = 5,   // regra especial: menor vence (usaremos densidadeInv)
    A_PIB_PC    = 6
} Atributo;

/* ============================================================
   FUNÇÕES AUXILIARES DE SISTEMA/UX
   ============================================================ */

/* limpa a tela de modo portável */
void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* pausa em milissegundos (2500 = 2.5s), portável */
void pausa_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 2000);
#endif
}

/* animação simples de "carregando..." com barra de progresso */
void loading(const char *msg, int duracao_ms) {
    int passos = 20;
    int passo_ms = duracao_ms / passos;
    printf("%s%s%s\n", C_BAR, msg, C_RESET);
    printf("%s[", C_BAR);
    for (int i = 0; i < passos; i++) {
        printf("#");
        fflush(stdout);
        pausa_ms(passo_ms);
    }
    printf("]%s\n", C_RESET);
}

/* retorna o nome "bonito" do atributo para exibição */
const char* nomeAtributo(Atributo a) {
    switch (a) {
        case A_POPULACAO: return "População";
        case A_AREA:      return "Área";
        case A_PIB:       return "PIB";
        case A_PONTOS:    return "Pontos Turísticos";
        case A_DENSIDADE: return "Densidade Demográfica (menor vence)";
        case A_PIB_PC:    return "PIB per capita";
        default:          return "Atributo Desconhecido";
    }
}

/* ============================================================
   CÁLCULO DE ATRIBUTOS DERIVADOS
   ------------------------------------------------------------
   Esta função recebe uma carta e calcula:
     - PIB per capita        (pib / populacao)
     - Densidade             (populacao / area)
     - Densidade invertida   (1 / densidade)
   ============================================================ */
void calcularAtributos(Carta *c) {
    if (!c) return;
    if (c->populacao == 0 || c->area == 0) {
        c->pibPerCapita = 0.0;
        c->densidade    = 0.0;
        c->densidadeInv = 0.0;
        return;
    }
    c->pibPerCapita = c->pib / (double)c->populacao;
    c->densidade    = (double)c->populacao / (double)c->area;
    c->densidadeInv = (c->densidade > 0.0) ? (1.0 / c->densidade) : 0.0;
}

/* ============================================================
   EXIBIÇÃO DE UMA CARTA
   ------------------------------------------------------------
   Imprime os dados de uma carta com um layout legível e colorido.
   ============================================================ */
void exibirCarta(const Carta *c, const char *titulo) {
    if (!c) return;
    printf(C_SUB "--------------------------------------------------\n" C_RESET);
    printf(C_TIT "%s\n" C_RESET, titulo);
    printf(C_SUB "--------------------------------------------------\n" C_RESET);
    printf(C_BOLD "Código: " C_RESET "%s\n", c->codigo);
    printf(C_BOLD "País:   " C_RESET "%s\n", c->nome);
    printf(C_BOLD "Área:   " C_RESET "%lu km²\n", c->area);
    printf(C_BOLD "Popul.: " C_RESET "%lu hab\n", c->populacao);
    printf(C_BOLD "PIB:    " C_RESET "US$ %.2f\n", c->pib);
    printf(C_BOLD "Turismo:" C_RESET " %lu pontos\n", c->pontosTur);
    printf(C_GRAY "----------------------------------------------\n" C_RESET);
    printf("PIB per capita:            US$ %.2f\n", c->pibPerCapita);
    printf("Densidade demográfica:     %.2f hab/km²\n", c->densidade);
    printf("Densidade (valor invert.): %.8f\n", c->densidadeInv);
    printf(C_SUB "--------------------------------------------------\n" C_RESET);
}

/* ============================================================
   VALOR NUMÉRICO DE UM ATRIBUTO
   ------------------------------------------------------------
   Para facilitar comparações e soma final, esta função devolve
   o "valor usado na disputa" para um atributo específico:
     - Densidade usa "densidadeInv" (maior = melhor).
     - Os demais usam o valor direto.
   ============================================================ */
double valorDoAtributoParaDisputa(const Carta *c, Atributo a) {
    switch (a) {
        case A_POPULACAO: return (double)c->populacao;
        case A_AREA:      return (double)c->area;
        case A_PIB:       return c->pib;
        case A_PONTOS:    return (double)c->pontosTur;
        case A_DENSIDADE: return c->densidadeInv;   // regra especial
        case A_PIB_PC:    return c->pibPerCapita;
        default:          return 0.0;
    }
}

/* ============================================================
   ENTRADA MANUAL DE UMA CARTA
   ------------------------------------------------------------
   Permite ao jogador preencher os campos de uma carta na hora.
   Ao final, os atributos derivados são calculados.
   ============================================================ */
void preencherCartaManual(Carta *c) {
    if (!c) return;

    printf(C_TIT "Cadastro manual da sua carta\n" C_RESET);
    printf("Código (ex: B01): ");
    scanf("%4s", c->codigo);

    printf("Nome do país: ");
    scanf("%49s", c->nome);

    printf("Área (km²): ");
    scanf("%lu", &c->area);

    printf("População: ");
    scanf("%lu", &c->populacao);

    printf("PIB (US$): ");
    scanf("%lf", &c->pib);

    printf("Número de pontos turísticos: ");
    scanf("%lu", &c->pontosTur);

    calcularAtributos(c);
}

/* ============================================================
   ESCOLHA DE UMA CARTA PRÉ-DEFINIDA
   ------------------------------------------------------------
   Lista as cartas disponíveis e permite escolher pelo código.
   Retorna 1 se achou, 0 se código inválido.
   ============================================================ */
int escolherCartaPredefinida(const Carta *todas, int n, const char *codigo, Carta *saida) {
    for (int i = 0; i < n; i++) {
        if (strcmp(todas[i].codigo, codigo) == 0) {
            if (saida) *saida = todas[i];
            return 1;
        }
    }
    return 0;
}

/* ============================================================
   MENU DE ATRIBUTOS DINÂMICO
   ------------------------------------------------------------
   Exibe somente os atributos ainda não escolhidos. Garante que
   o usuário não repete a opção. Retorna um valor do enum Atributo.
   ============================================================ */
Atributo escolherAtributo(int jaEscolhido[7], int rodada) {
    int opcao = 0;
    while (1) {
        printf(C_SUB "--------------------------------------------------\n" C_RESET);
        printf(C_TIT "Rodada %d  ?  escolha um atributo" C_RESET "\n", rodada);
        printf(C_SUB "--------------------------------------------------\n" C_RESET);

        if (!jaEscolhido[A_POPULACAO]) printf(C_MENU "1 - População" C_RESET "\n");
        if (!jaEscolhido[A_AREA])      printf(C_MENU "2 - Área" C_RESET "\n");
        if (!jaEscolhido[A_PIB])       printf(C_MENU "3 - PIB" C_RESET "\n");
        if (!jaEscolhido[A_PONTOS])    printf(C_MENU "4 - Pontos Turísticos" C_RESET "\n");
        if (!jaEscolhido[A_DENSIDADE]) printf(C_MENU "5 - Densidade Demográfica (menor vence)" C_RESET "\n");
        if (!jaEscolhido[A_PIB_PC])    printf(C_MENU "6 - PIB per capita" C_RESET "\n");

        printf(C_BOLD "Sua escolha: " C_RESET);
        if (scanf("%d", &opcao) != 1) {
            // leitura inválida
            while (getchar() != '\n'); // limpa buffer
            printf(C_ERR "Entrada inválida. Tente novamente.\n" C_RESET);
            continue;
        }
        if (opcao < 1 || opcao > 6) {
            printf(C_ERR "Opção fora do intervalo. Tente novamente.\n" C_RESET);
            continue;
        }
        if (jaEscolhido[opcao]) {
            printf(C_WARN "Você já escolheu esse atributo. Selecione outro.\n" C_RESET);
            continue;
        }
        jaEscolhido[opcao] = 1; // marca como escolhido
        return (Atributo)opcao;
    }
}

/* ============================================================
   COMPARA UMA ÚNICA RODADA
   ------------------------------------------------------------
   - Recebe o atributo da rodada e as duas cartas.
   - Calcula o valor usado na disputa (respeita regra da densidade).
   - Exibe resultado e retorna:
         1 se jogador venceu,
         2 se computador venceu,
         0 se empate.
   ============================================================ */
int compararRodada(const Carta *jog, const Carta *cpu, Atributo attr) {
    double vJog = valorDoAtributoParaDisputa(jog, attr);
    double vCpu = valorDoAtributoParaDisputa(cpu, attr);

    limparTela();
    loading("Carregando resultado da rodada...", 1000);

    printf(C_TIT "==> Atributo: %s\n" C_RESET, nomeAtributo(attr));
    printf(C_GRAY "--------------------------------------------------\n" C_RESET);

    // Mostra os valores "humanizados"
    switch (attr) {
        case A_POPULACAO:
            printf("%s: %lu hab\n", jog->nome, jog->populacao);
            printf("%s: %lu hab\n", cpu->nome, cpu->populacao);
            break;
        case A_AREA:
            printf("%s: %lu km²\n", jog->nome, jog->area);
            printf("%s: %lu km²\n", cpu->nome, cpu->area);
            break;
        case A_PIB:
            printf("%s: US$ %.2f\n", jog->nome, jog->pib);
            printf("%s: US$ %.2f\n", cpu->nome, cpu->pib);
            break;
        case A_PONTOS:
            printf("%s: %lu pontos turísticos\n", jog->nome, jog->pontosTur);
            printf("%s: %lu pontos turísticos\n", cpu->nome, cpu->pontosTur);
            break;
        case A_DENSIDADE:
            printf("%s: %.2f hab/km²  (menor é melhor)\n", jog->nome, jog->densidade);
            printf("%s: %.2f hab/km²  (menor é melhor)\n", cpu->nome, cpu->densidade);
            break;
        case A_PIB_PC:
            printf("%s: US$ %.2f por pessoa\n", jog->nome, jog->pibPerCapita);
            printf("%s: US$ %.2f por pessoa\n", cpu->nome, cpu->pibPerCapita);
            break;
        default: break;
    }

    printf(C_GRAY "--------------------------------------------------\n" C_RESET);

    if (vJog > vCpu) {
        printf(C_OK "Vitória de %s!\n" C_RESET, jog->nome);
        return 1;
    } else if (vCpu > vJog) {
        printf(C_ERR "Vitória de %s!\n" C_RESET, cpu->nome);
        return 2;
    } else {
        printf(C_WARN "Empate nesta rodada!\n" C_RESET);
        return 0;
    }
}

/* ============================================================
   MOSTRA AS REGRAS DO JOGO
   ============================================================ */
void mostrarRegras(void) {
    limparTela();
    printf(C_TIT "========== REGRAS DO JOGO ==========\n" C_RESET);
    printf(C_GRAY "Interface e funcionamento da V3\n" C_RESET);
    printf("1) Você pode jogar com uma carta pré-definida OU cadastrar uma carta manualmente.\n");
    printf("2) O computador joga com outra carta (pré-definida aleatória, diferente da sua).\n");
    printf("3) Você escolherá " C_BOLD "4 atributos distintos" C_RESET " para disputar 4 rodadas.\n");
    printf("4) Em cada rodada, quem tiver o maior valor do atributo vence.\n");
    printf("   " C_WARN "Exceção: Densidade Demográfica" C_RESET " ? vence quem tiver a menor densidade.\n");
    printf("   Para isso, o jogo usa a " C_BOLD "densidade invertida (1/densidade)" C_RESET " na comparação.\n");
    printf("5) A cada vitória de rodada: " C_BOLD "pontuacao1++ (jogador)" C_RESET " ou " C_BOLD "pontuacao2++ (computador)\n" C_RESET);
    printf("6) Ao final das 4 rodadas, também é feita a " C_BOLD "soma dos 4 atributos usados\n" C_RESET);
    printf("   (já considerando densidade invertida). Maior soma vence.\n");
    printf("7) Havendo empate na soma, será exibido " C_BOLD "\"Empate!\"" C_RESET ".\n");
    printf(C_TIT "====================================\n" C_RESET);
    printf(C_DIM "Pressione ENTER para voltar ao menu..." C_RESET);
    while (getchar() != '\n'); // consome resto
    getchar();                  // aguarda ENTER
}

/* ============================================================
   FUNÇÃO PRINCIPAL (main)
   ------------------------------------------------------------
   Controla o fluxo geral: menu inicial, seleção de carta,
   duelo em 4 rodadas e resultado final.
   ============================================================ */
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand((unsigned)time(NULL));

    /* ----------------------------------------------
       1) Banco de cartas pré-definidas
       ---------------------------------------------- */
    Carta banco[] = {
        {"B01","Brasil",         8514877, 212559000, 2554000000000.0, 47500},
        {"A02","Alemanha",        357022,  83000000, 3846000000000.0, 39500},
        {"R03","Rússia",        17098242, 144000000, 1576000000000.0, 25000},
        {"E04","Estados_Unidos", 9833517, 331000000,21430000000000.0, 79000},
        {"C05","China",          9596961,1400000000,14340000000000.0, 65000}
    };
    const int N = (int)(sizeof(banco)/sizeof(banco[0]));
    for (int i = 0; i < N; i++) calcularAtributos(&banco[i]);

    /* ----------------------------------------------
       2) Menu principal
       ---------------------------------------------- */
menu_principal:
    limparTela();
    printf(C_TIT "Super Trunfo" C_RESET " - " C_SUB "Países (V3.0)\n" C_RESET);
    printf(C_SUB "==================================================\n" C_RESET);
    printf(C_MENU "1 - Iniciar Jogo\n" C_RESET);
    printf(C_MENU "2 - Regras do jogo\n" C_RESET);
    printf(C_MENU "3 - Sair\n" C_RESET);
    printf(C_SUB "==================================================\n" C_RESET);
    printf(C_BOLD "Escolha: " C_RESET);

    int op = 0;
    if (scanf("%d", &op) != 1) {
        while (getchar() != '\n'); // limpa buffer
        printf(C_ERR "Entrada inválida.\n" C_RESET);
        pausa_ms(1200);
        goto menu_principal;
    }

    if (op == 3) {
        printf(C_OK "Obrigado por jogar!\n" C_RESET);
        return 0;
    }
    else if (op == 2) {
        while (getchar() != '\n'); // consome '\n' pendente
        mostrarRegras();
        goto menu_principal;
    }
    else if (op != 1) {
        printf(C_ERR "Opção inexistente.\n" C_RESET);
        pausa_ms(1200);
        goto menu_principal;
    }

    /* ----------------------------------------------
       3) Escolha/Criação da carta do jogador
       ---------------------------------------------- */
    limparTela();
    printf(C_TIT "Deseja jogar com uma carta pré-definida?\n" C_RESET);
    printf(C_MENU "1 - Sim  |  0 - Não (cadastrar manualmente)\n" C_RESET);
    printf(C_BOLD "Escolha: " C_RESET);

    int usarPre = 0;
    if (scanf("%d", &usarPre) != 1) {
        while (getchar() != '\n');
        printf(C_ERR "Entrada inválida.\n" C_RESET);
        pausa_ms(1200);
        goto menu_principal;
    }

    Carta jogador;
    if (usarPre) {
        limparTela();
        printf(C_TIT "Cartas disponíveis:\n" C_RESET);
        for (int i = 0; i < N; i++) {
            printf(C_MENU "%s" C_RESET " - %s\n", banco[i].codigo, banco[i].nome);
        }
        printf(C_BOLD "Digite o código da sua carta: " C_RESET);

        char cod[8];
        scanf("%7s", cod);

        if (!escolherCartaPredefinida(banco, N, cod, &jogador)) {
            printf(C_ERR "Código inválido.\n" C_RESET);
            pausa_ms(1200);
            goto menu_principal;
        }
    } else {
        while (getchar() != '\n'); // consome '\n'
        limparTela();
        preencherCartaManual(&jogador);
    }

    /* ----------------------------------------------
       4) Carta do computador (aleatória e diferente)
       ---------------------------------------------- */
    Carta cpu;
    if (usarPre) {
        // sorteia uma carta diferente da escolhida
        int idx;
        do {
            idx = rand() % N;
        } while (strcmp(banco[idx].codigo, jogador.codigo) == 0);
        cpu = banco[idx];
    } else {
        // se o jogador cadastrou manualmente, pegamos uma aleatória do banco
        cpu = banco[rand() % N];
    }

    /* ----------------------------------------------
       5) Tela de confirmação/cartas
       ---------------------------------------------- */
    limparTela();
    loading("Preparando cartas...", 800);
    exibirCarta(&jogador, "Sua Carta");
    exibirCarta(&cpu,     "Carta do Computador");

    printf(C_DIM "Pressione ENTER para continuar..." C_RESET);
    while (getchar() != '\n'); // limpa buffer
    getchar();

    /* ----------------------------------------------
       6) Escolha dinâmica de 4 atributos
       ---------------------------------------------- */
    int jaEscolhido[7] = {0}; // índices 1..6 usados
    Atributo escolhidos[4];
    for (int r = 0; r < 4; r++) {
        limparTela();
        escolhidos[r] = escolherAtributo(jaEscolhido, r+1);
    }

    /* ----------------------------------------------
       7) Duelo: 4 rodadas + placar
       ---------------------------------------------- */
    int pontuacao1 = 0; // jogador
    int pontuacao2 = 0; // computador

    for (int r = 0; r < 4; r++) {
        int res = compararRodada(&jogador, &cpu, escolhidos[r]);
        if (res == 1) pontuacao1++;
        else if (res == 2) pontuacao2++;

        printf(C_GRAY "--------------------------------------------------\n" C_RESET);
        printf("Placar parcial ? %s: %d  |  %s: %d\n",
               jogador.nome, pontuacao1, cpu.nome, pontuacao2);

        printf(C_DIM "Avançando para a próxima rodada..." C_RESET "\n");
        pausa_ms(2500); // 2.5s entre as rodadas
    }

    /* ----------------------------------------------
       8) Soma final dos 4 atributos escolhidos
          (densidade já usa o valor invertido)
       ---------------------------------------------- */
    double somaJog = 0.0, somaCpu = 0.0;
    for (int r = 0; r < 4; r++) {
        somaJog += valorDoAtributoParaDisputa(&jogador, escolhidos[r]);
        somaCpu += valorDoAtributoParaDisputa(&cpu,     escolhidos[r]);
    }

    limparTela();
    loading("Calculando resultado final...", 1200);

    printf(C_TIT "===== RESULTADO FINAL =====\n" C_RESET);
    printf("Atributos usados:\n");
    for (int r = 0; r < 4; r++) {
        printf("  - %s\n", nomeAtributo(escolhidos[r]));
    }
    printf(C_GRAY "--------------------------------------------------\n" C_RESET);
    printf(C_BOLD "%s" C_RESET " ? Pontos por rodada: %d | Soma dos atributos: %.4f\n",
           jogador.nome, pontuacao1, somaJog);
    printf(C_BOLD "%s" C_RESET " ? Pontos por rodada: %d | Soma dos atributos: %.4f\n",
           cpu.nome,     pontuacao2, somaCpu);
    printf(C_GRAY "--------------------------------------------------\n" C_RESET);

    if (somaJog > somaCpu) {
        printf(C_OK "Vitória do jogador (%s) pela soma dos atributos!\n" C_RESET, jogador.nome);
    } else if (somaCpu > somaJog) {
        printf(C_ERR "Vitória do computador (%s) pela soma dos atributos!\n" C_RESET, cpu.nome);
    } else {
        printf(C_WARN "Empate pela soma dos atributos!\n" C_RESET);
    }

    printf(C_SUB "==================================================\n" C_RESET);
    printf(C_MENU "1 - Jogar novamente\n" C_RESET);
    printf(C_MENU "2 - Voltar ao menu principal\n" C_RESET);
    printf(C_MENU "3 - Sair\n" C_RESET);
    printf(C_BOLD "Escolha: " C_RESET);

    int fim = 0;
    if (scanf("%d", &fim) != 1) fim = 3;
    if (fim == 1) goto menu_principal;     // recomeça tudo
    else if (fim == 2) goto menu_principal;
    else printf(C_OK "Até a próxima!\n" C_RESET);

    return 0;
}
