/*
    SUPER TRUNFO - PA�SES (V3.0)
    ------------------------------------------------------------
    O objetivo desta vers�o � modernizar o c�digo:
      - Armazenar as cartas em uma "struct" (tipo composto).
      - Calcular e guardar atributos derivados (PIB per capita,
        densidade e densidade invertida).
      - Menus com cores, UX melhor e valida��es.
      - Duelo com 4 rodadas (4 atributos distintos).
      - Pontua��o por rodada e soma final dos 4 atributos usados.
      - Densidade: regra especial -> menor densidade vence,
        por isso usamos a "densidade invertida" nas compara��es.

    O c�digo � largamente comentado para fins did�ticos.
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
   PALETA DE CORES ANSI (strings com sequ�ncias de escape)
   ------------------------------------------------------------
   Usamos #define para facilitar. Ex.: printf(C_TIT "Ol�" C_RESET);
   ============================================================ */
#define C_RESET   "\033[0m"
#define C_DIM     "\033[2m"
#define C_BOLD    "\033[1m"
#define C_TIT     "\033[1;38;5;39m"   // azul ciano vivo (t�tulos)
#define C_SUB     "\033[1;38;5;45m"   // roxo/azul (subt�tulos)
#define C_OK      "\033[1;38;5;82m"   // verde
#define C_WARN    "\033[1;38;5;214m"  // laranja
#define C_ERR     "\033[1;38;5;196m"  // vermelho
#define C_MENU    "\033[38;5;81m"     // azul claro
#define C_GRAY    "\033[38;5;245m"    // cinza
#define C_BAR     "\033[38;5;219m"    // rosa (barrinhas de loading)

/* ============================================================
   TIPOS E ENUMERA��ES
   ============================================================ */

/* Representa uma carta de pa�s com atributos "b�sicos" e os
   "derivados" que vamos calcular uma �nica vez. */
typedef struct {
    char  codigo[5];
    char  nome[50];
    unsigned long area;          // km�
    unsigned long populacao;     // habitantes
    double pib;                  // em d�lares (valor total)
    unsigned long pontosTur;     // pontos tur�sticos

    // Atributos derivados
    double pibPerCapita;         // pib / populacao
    double densidade;            // populacao / area
    double densidadeInv;         // 1 / densidade  (para comparar "maior vence")
} Carta;

/* Enumerador de atributos poss�veis (facilita menus e l�gica) */
typedef enum {
    A_POPULACAO = 1,
    A_AREA      = 2,
    A_PIB       = 3,
    A_PONTOS    = 4,
    A_DENSIDADE = 5,   // regra especial: menor vence (usaremos densidadeInv)
    A_PIB_PC    = 6
} Atributo;

/* ============================================================
   FUN��ES AUXILIARES DE SISTEMA/UX
   ============================================================ */

/* limpa a tela de modo port�vel */
void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* pausa em milissegundos (2500 = 2.5s), port�vel */
void pausa_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 2000);
#endif
}

/* anima��o simples de "carregando..." com barra de progresso */
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

/* retorna o nome "bonito" do atributo para exibi��o */
const char* nomeAtributo(Atributo a) {
    switch (a) {
        case A_POPULACAO: return "Popula��o";
        case A_AREA:      return "�rea";
        case A_PIB:       return "PIB";
        case A_PONTOS:    return "Pontos Tur�sticos";
        case A_DENSIDADE: return "Densidade Demogr�fica (menor vence)";
        case A_PIB_PC:    return "PIB per capita";
        default:          return "Atributo Desconhecido";
    }
}

/* ============================================================
   C�LCULO DE ATRIBUTOS DERIVADOS
   ------------------------------------------------------------
   Esta fun��o recebe uma carta e calcula:
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
   EXIBI��O DE UMA CARTA
   ------------------------------------------------------------
   Imprime os dados de uma carta com um layout leg�vel e colorido.
   ============================================================ */
void exibirCarta(const Carta *c, const char *titulo) {
    if (!c) return;
    printf(C_SUB "--------------------------------------------------\n" C_RESET);
    printf(C_TIT "%s\n" C_RESET, titulo);
    printf(C_SUB "--------------------------------------------------\n" C_RESET);
    printf(C_BOLD "C�digo: " C_RESET "%s\n", c->codigo);
    printf(C_BOLD "Pa�s:   " C_RESET "%s\n", c->nome);
    printf(C_BOLD "�rea:   " C_RESET "%lu km�\n", c->area);
    printf(C_BOLD "Popul.: " C_RESET "%lu hab\n", c->populacao);
    printf(C_BOLD "PIB:    " C_RESET "US$ %.2f\n", c->pib);
    printf(C_BOLD "Turismo:" C_RESET " %lu pontos\n", c->pontosTur);
    printf(C_GRAY "----------------------------------------------\n" C_RESET);
    printf("PIB per capita:            US$ %.2f\n", c->pibPerCapita);
    printf("Densidade demogr�fica:     %.2f hab/km�\n", c->densidade);
    printf("Densidade (valor invert.): %.8f\n", c->densidadeInv);
    printf(C_SUB "--------------------------------------------------\n" C_RESET);
}

/* ============================================================
   VALOR NUM�RICO DE UM ATRIBUTO
   ------------------------------------------------------------
   Para facilitar compara��es e soma final, esta fun��o devolve
   o "valor usado na disputa" para um atributo espec�fico:
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
   Ao final, os atributos derivados s�o calculados.
   ============================================================ */
void preencherCartaManual(Carta *c) {
    if (!c) return;

    printf(C_TIT "Cadastro manual da sua carta\n" C_RESET);
    printf("C�digo (ex: B01): ");
    scanf("%4s", c->codigo);

    printf("Nome do pa�s: ");
    scanf("%49s", c->nome);

    printf("�rea (km�): ");
    scanf("%lu", &c->area);

    printf("Popula��o: ");
    scanf("%lu", &c->populacao);

    printf("PIB (US$): ");
    scanf("%lf", &c->pib);

    printf("N�mero de pontos tur�sticos: ");
    scanf("%lu", &c->pontosTur);

    calcularAtributos(c);
}

/* ============================================================
   ESCOLHA DE UMA CARTA PR�-DEFINIDA
   ------------------------------------------------------------
   Lista as cartas dispon�veis e permite escolher pelo c�digo.
   Retorna 1 se achou, 0 se c�digo inv�lido.
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
   MENU DE ATRIBUTOS DIN�MICO
   ------------------------------------------------------------
   Exibe somente os atributos ainda n�o escolhidos. Garante que
   o usu�rio n�o repete a op��o. Retorna um valor do enum Atributo.
   ============================================================ */
Atributo escolherAtributo(int jaEscolhido[7], int rodada) {
    int opcao = 0;
    while (1) {
        printf(C_SUB "--------------------------------------------------\n" C_RESET);
        printf(C_TIT "Rodada %d  ?  escolha um atributo" C_RESET "\n", rodada);
        printf(C_SUB "--------------------------------------------------\n" C_RESET);

        if (!jaEscolhido[A_POPULACAO]) printf(C_MENU "1 - Popula��o" C_RESET "\n");
        if (!jaEscolhido[A_AREA])      printf(C_MENU "2 - �rea" C_RESET "\n");
        if (!jaEscolhido[A_PIB])       printf(C_MENU "3 - PIB" C_RESET "\n");
        if (!jaEscolhido[A_PONTOS])    printf(C_MENU "4 - Pontos Tur�sticos" C_RESET "\n");
        if (!jaEscolhido[A_DENSIDADE]) printf(C_MENU "5 - Densidade Demogr�fica (menor vence)" C_RESET "\n");
        if (!jaEscolhido[A_PIB_PC])    printf(C_MENU "6 - PIB per capita" C_RESET "\n");

        printf(C_BOLD "Sua escolha: " C_RESET);
        if (scanf("%d", &opcao) != 1) {
            // leitura inv�lida
            while (getchar() != '\n'); // limpa buffer
            printf(C_ERR "Entrada inv�lida. Tente novamente.\n" C_RESET);
            continue;
        }
        if (opcao < 1 || opcao > 6) {
            printf(C_ERR "Op��o fora do intervalo. Tente novamente.\n" C_RESET);
            continue;
        }
        if (jaEscolhido[opcao]) {
            printf(C_WARN "Voc� j� escolheu esse atributo. Selecione outro.\n" C_RESET);
            continue;
        }
        jaEscolhido[opcao] = 1; // marca como escolhido
        return (Atributo)opcao;
    }
}

/* ============================================================
   COMPARA UMA �NICA RODADA
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
            printf("%s: %lu km�\n", jog->nome, jog->area);
            printf("%s: %lu km�\n", cpu->nome, cpu->area);
            break;
        case A_PIB:
            printf("%s: US$ %.2f\n", jog->nome, jog->pib);
            printf("%s: US$ %.2f\n", cpu->nome, cpu->pib);
            break;
        case A_PONTOS:
            printf("%s: %lu pontos tur�sticos\n", jog->nome, jog->pontosTur);
            printf("%s: %lu pontos tur�sticos\n", cpu->nome, cpu->pontosTur);
            break;
        case A_DENSIDADE:
            printf("%s: %.2f hab/km�  (menor � melhor)\n", jog->nome, jog->densidade);
            printf("%s: %.2f hab/km�  (menor � melhor)\n", cpu->nome, cpu->densidade);
            break;
        case A_PIB_PC:
            printf("%s: US$ %.2f por pessoa\n", jog->nome, jog->pibPerCapita);
            printf("%s: US$ %.2f por pessoa\n", cpu->nome, cpu->pibPerCapita);
            break;
        default: break;
    }

    printf(C_GRAY "--------------------------------------------------\n" C_RESET);

    if (vJog > vCpu) {
        printf(C_OK "Vit�ria de %s!\n" C_RESET, jog->nome);
        return 1;
    } else if (vCpu > vJog) {
        printf(C_ERR "Vit�ria de %s!\n" C_RESET, cpu->nome);
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
    printf("1) Voc� pode jogar com uma carta pr�-definida OU cadastrar uma carta manualmente.\n");
    printf("2) O computador joga com outra carta (pr�-definida aleat�ria, diferente da sua).\n");
    printf("3) Voc� escolher� " C_BOLD "4 atributos distintos" C_RESET " para disputar 4 rodadas.\n");
    printf("4) Em cada rodada, quem tiver o maior valor do atributo vence.\n");
    printf("   " C_WARN "Exce��o: Densidade Demogr�fica" C_RESET " ? vence quem tiver a menor densidade.\n");
    printf("   Para isso, o jogo usa a " C_BOLD "densidade invertida (1/densidade)" C_RESET " na compara��o.\n");
    printf("5) A cada vit�ria de rodada: " C_BOLD "pontuacao1++ (jogador)" C_RESET " ou " C_BOLD "pontuacao2++ (computador)\n" C_RESET);
    printf("6) Ao final das 4 rodadas, tamb�m � feita a " C_BOLD "soma dos 4 atributos usados\n" C_RESET);
    printf("   (j� considerando densidade invertida). Maior soma vence.\n");
    printf("7) Havendo empate na soma, ser� exibido " C_BOLD "\"Empate!\"" C_RESET ".\n");
    printf(C_TIT "====================================\n" C_RESET);
    printf(C_DIM "Pressione ENTER para voltar ao menu..." C_RESET);
    while (getchar() != '\n'); // consome resto
    getchar();                  // aguarda ENTER
}

/* ============================================================
   FUN��O PRINCIPAL (main)
   ------------------------------------------------------------
   Controla o fluxo geral: menu inicial, sele��o de carta,
   duelo em 4 rodadas e resultado final.
   ============================================================ */
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand((unsigned)time(NULL));

    /* ----------------------------------------------
       1) Banco de cartas pr�-definidas
       ---------------------------------------------- */
    Carta banco[] = {
        {"B01","Brasil",         8514877, 212559000, 2554000000000.0, 47500},
        {"A02","Alemanha",        357022,  83000000, 3846000000000.0, 39500},
        {"R03","R�ssia",        17098242, 144000000, 1576000000000.0, 25000},
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
    printf(C_TIT "Super Trunfo" C_RESET " - " C_SUB "Pa�ses (V3.0)\n" C_RESET);
    printf(C_SUB "==================================================\n" C_RESET);
    printf(C_MENU "1 - Iniciar Jogo\n" C_RESET);
    printf(C_MENU "2 - Regras do jogo\n" C_RESET);
    printf(C_MENU "3 - Sair\n" C_RESET);
    printf(C_SUB "==================================================\n" C_RESET);
    printf(C_BOLD "Escolha: " C_RESET);

    int op = 0;
    if (scanf("%d", &op) != 1) {
        while (getchar() != '\n'); // limpa buffer
        printf(C_ERR "Entrada inv�lida.\n" C_RESET);
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
        printf(C_ERR "Op��o inexistente.\n" C_RESET);
        pausa_ms(1200);
        goto menu_principal;
    }

    /* ----------------------------------------------
       3) Escolha/Cria��o da carta do jogador
       ---------------------------------------------- */
    limparTela();
    printf(C_TIT "Deseja jogar com uma carta pr�-definida?\n" C_RESET);
    printf(C_MENU "1 - Sim  |  0 - N�o (cadastrar manualmente)\n" C_RESET);
    printf(C_BOLD "Escolha: " C_RESET);

    int usarPre = 0;
    if (scanf("%d", &usarPre) != 1) {
        while (getchar() != '\n');
        printf(C_ERR "Entrada inv�lida.\n" C_RESET);
        pausa_ms(1200);
        goto menu_principal;
    }

    Carta jogador;
    if (usarPre) {
        limparTela();
        printf(C_TIT "Cartas dispon�veis:\n" C_RESET);
        for (int i = 0; i < N; i++) {
            printf(C_MENU "%s" C_RESET " - %s\n", banco[i].codigo, banco[i].nome);
        }
        printf(C_BOLD "Digite o c�digo da sua carta: " C_RESET);

        char cod[8];
        scanf("%7s", cod);

        if (!escolherCartaPredefinida(banco, N, cod, &jogador)) {
            printf(C_ERR "C�digo inv�lido.\n" C_RESET);
            pausa_ms(1200);
            goto menu_principal;
        }
    } else {
        while (getchar() != '\n'); // consome '\n'
        limparTela();
        preencherCartaManual(&jogador);
    }

    /* ----------------------------------------------
       4) Carta do computador (aleat�ria e diferente)
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
        // se o jogador cadastrou manualmente, pegamos uma aleat�ria do banco
        cpu = banco[rand() % N];
    }

    /* ----------------------------------------------
       5) Tela de confirma��o/cartas
       ---------------------------------------------- */
    limparTela();
    loading("Preparando cartas...", 800);
    exibirCarta(&jogador, "Sua Carta");
    exibirCarta(&cpu,     "Carta do Computador");

    printf(C_DIM "Pressione ENTER para continuar..." C_RESET);
    while (getchar() != '\n'); // limpa buffer
    getchar();

    /* ----------------------------------------------
       6) Escolha din�mica de 4 atributos
       ---------------------------------------------- */
    int jaEscolhido[7] = {0}; // �ndices 1..6 usados
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

        printf(C_DIM "Avan�ando para a pr�xima rodada..." C_RESET "\n");
        pausa_ms(2500); // 2.5s entre as rodadas
    }

    /* ----------------------------------------------
       8) Soma final dos 4 atributos escolhidos
          (densidade j� usa o valor invertido)
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
        printf(C_OK "Vit�ria do jogador (%s) pela soma dos atributos!\n" C_RESET, jogador.nome);
    } else if (somaCpu > somaJog) {
        printf(C_ERR "Vit�ria do computador (%s) pela soma dos atributos!\n" C_RESET, cpu.nome);
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
    if (fim == 1) goto menu_principal;     // recome�a tudo
    else if (fim == 2) goto menu_principal;
    else printf(C_OK "At� a pr�xima!\n" C_RESET);

    return 0;
}
