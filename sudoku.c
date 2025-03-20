#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "ansi_colors.h"

char tabuleiro[9][9];//tabuleiro que está acontecendo o jogo.
char espelho[9][9];//marcação de caracteres fixos
char solucao[9][9];

typedef unsigned char seletor;
seletor tela=0;
seletor op=0;//'opção' do menu
seletor dif=0;//dificuldade

int verificar_vitoria();
int verifica_geracao();
int gerar();
void gerar_tabuleiro();
void tela_menu();
void menu(char ch);
void tela_jogo(char jogo[9][9]);
void jogo_teclado(char ch);


int verificar_vitoria(){
    int quadrados[9][9];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {//Separa os quadrados para facilitar a correção
            quadrados[0][i*3+j]=tabuleiro[i][j];
            quadrados[1][i*3+j]=tabuleiro[i][j+3];
            quadrados[2][i*3+j]=tabuleiro[i][j+6];
            quadrados[3][i*3+j]=tabuleiro[i+3][j];
            quadrados[4][i*3+j]=tabuleiro[i+3][j+3];
            quadrados[5][i*3+j]=tabuleiro[i+3][j+6];
            quadrados[6][i*3+j]=tabuleiro[i+6][j];
            quadrados[7][i*3+j]=tabuleiro[i+6][j+3];
            quadrados[8][i*3+j]=tabuleiro[i+6][j+6];
        }
    }

    for (int i = 0; i < 9; i++)
    {   
        for (int j = 0; j < 9; j++)
        {
            if(tabuleiro[i][j]==' ') return 0;//vazio retorna
            for (int k = j+1; k < 9; k++)
            {
                if (quadrados[i][j]==quadrados[i][k])//verifica o quadrado
                {
                   return 0;
                }
                
                if (tabuleiro[i][j]==tabuleiro[i][k] || tabuleiro[j][i]==tabuleiro[k][i])//verifica horizontal e vertical
                    return 0;
            }
        }
    }
    


    return 1;
}

int verifica_geracao(){
    int quadrados[9][9];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            quadrados[0][i*3+j]=tabuleiro[i][j];
            quadrados[1][i*3+j]=tabuleiro[i][j+3];
            quadrados[2][i*3+j]=tabuleiro[i][j+6];
            quadrados[3][i*3+j]=tabuleiro[i+3][j];
            quadrados[4][i*3+j]=tabuleiro[i+3][j+3];
            quadrados[5][i*3+j]=tabuleiro[i+3][j+6];
            quadrados[6][i*3+j]=tabuleiro[i+6][j];
            quadrados[7][i*3+j]=tabuleiro[i+6][j+3];
            quadrados[8][i*3+j]=tabuleiro[i+6][j+6];
        }
    }
    for (int i = 0; i < 9; i++)
    {   
        for (int j = 0; j < 9; j++)
        {
            for (int k = j+1; k < 9; k++)
            {
                if (quadrados[i][j]==quadrados[i][k] && quadrados[i][j]!=' ')
                {
                   return 0;
                }
                
                if (tabuleiro[j][i]==tabuleiro[k][i] && tabuleiro[j][i]!=' ')
                    return 0;
                if (tabuleiro[i][j]==tabuleiro[i][k] && tabuleiro[i][j]!=' ')
                    return 0;
            }
        }
    }
    


    return 1;

}

// Função para embaralhar um array de números
void embaralhar(char *numeros, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int j = rand() % (i + 1);
        char temp = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = temp;
    }
}


int gerar(int linha, int coluna){


    if (linha==9) return verifica_geracao();

    int prox_coluna = (coluna + 1) % 9;
    int prox_linha = (prox_coluna == 0 ) ? linha + 1 : linha;
    
    char numeros[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    embaralhar(numeros, 9);
    for (int i = 0; i < 9; i++) {
        if (verifica_geracao()) {
            tabuleiro[linha][coluna] = numeros[i];
            if (gerar(prox_linha, prox_coluna)) {
                return 1;
            }
            tabuleiro[linha][coluna] = ' '; // Backtracking
        }
    }
    return 0;

}


void gerar_tabuleiro(){
    printf("\nLoading...");
    char padrao[9][9] = {//Padrao enquanto o gerador não está pronto
        {'4', ' ', ' ', '9', '3', '6', '1', ' ', ' '},
        {'3', '8', ' ', '5', '1', ' ', '4', '9', '6'},
        {' ', '6', '9', '8', '4', ' ', ' ', '5', '3'},
        {'8', ' ', '6', '4', '2', ' ', '3', '7', '1'},
        {'9', '3', '4', ' ', '7', '5', ' ', ' ', '2'},
        {' ', '1', '7', '3', '6', ' ', '5', '4', ' '},
        {'6', '2', ' ', '7', ' ', ' ', '9', ' ', '4'},
        {' ', '9', '1', ' ', '8', ' ', '2', '3', '7'},
        {'7', '4', '3', '2', ' ', ' ', '6', ' ', '5'}
    };
    memset(tabuleiro,' ',81);
    int retirados=0;
    switch (dif)
    {
        case 1:
        while (!gerar(0,0));
        retirados=((rand()%41)+5);
        break;
        case 2:
        while (!gerar(0,0));
        retirados=((rand()%16)+45);
        break;
        case 3:
        while (!gerar(0,0));
        retirados=((rand()%8)+60);
        break;
    default:
        for (int i = 0; i < 9; i++)
        {
           for (int j = 0; j < 9; j++)
           {
            tabuleiro[i][j]=padrao[i][j];
           }
           
        }
        break;
    }
    printf(TEXT_CLEAR);
    memcpy(solucao,tabuleiro,81);
    
    for (int i = 0; i < retirados; i++)
    {
        int x= (rand()%9);
        int y= (rand()%9);
        if(tabuleiro[y][x]==' '){
            i--;
        }
        else tabuleiro[y][x]=' ';
    }
    
    memcpy(espelho,tabuleiro,81);
}

//   ____        __     __       
//  / __/_ _____/ /__  / /____ __
// _\ \/ // / _  / _ \/  '_/ // /
///___/\_,_/\_,_/\___/_/\_\\_,_/
void tela_menu(){
    char vet[][10]={{"Padrao"},{"Facil"},{"Medio"},{"Dificil"}};
    printf(TEXT_REVERSE);
    printf("\n\t   ____        __     __       ");
    printf("\n\t  / __/_ _____/ /__  / /____ __");
    printf("\n\t _\\ \\/ // / _  / _ \\/  '_/ // /");
    printf("\n\t/___/\\_,_/\\_,_/\\___/_/\\_\\\\_,_/ ");
    printf(RESET);

    printf("\n\n");
    op == 0 ? printf(TEXT_REVERSE TEXT_BOLD) : 0;
    printf("\tJOGAR\n");
    printf(RESET);
    op == 1 ? printf(TEXT_REVERSE TEXT_BOLD) : 0;
    printf("\tDIFICULDADE:\n\t<-%s->\n",vet[dif]);
    printf(RESET);
}

void menu(char ch){
    static char special=0;
    if(ch == -32){
        special = 1;
        return;
    }
    if(special){
        special=0;
        switch (ch)
        {
        case 72://cima
            if (op>0)op--;
            break;
        case 80://baixo
            if (op<1)op++;
            break;
        case 75://esquerda
            if(op==1){
                if (dif==0)dif=3;
                else dif--;
            }
            break;
        case 77://direita
            if(op==1){
                if (dif==3)dif=0;
                else dif++;
            }
            break;
        }
        return;
    }
    if(ch==13){
        switch (op)
        {
        case 0:
            tela=1;
            gerar_tabuleiro();
            break;
        }

    }
}
/*
	┐ 191
    └ 192
    ┴ 193
    ┬ 194
    ├ 195
    ─ 196
    ┼ 197
    ┘ 217
    ┌ 218
    │ 179
    ┤ 180
*/
unsigned char x=0;
unsigned char y=0;
void tela_jogo(char jogo[9][9]){
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
    218,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,191);
    for (int i = 0; i < 9; i++)
    {
        printf("%c",179);
        for (int j = 0; j < 9; j++)
        {
            if(espelho[i][j]!=' ') printf(BG_BLUE);
            if(i==y && x==j) printf(TEXT_REVERSE TEXT_BOLD);
            printf(" %c ",jogo[i][j]);
            printf(RESET);
            printf("%c",179);
        }
        if(i!=8){
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
            195,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,180);
        }
    }
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
    192,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,217);

}

void jogo_teclado(char ch){
    static char special=0;
    if(ch == -32){
        special = 1;
        return;
    }
    if(special){
        special=0;
        switch (ch)
        {
        case 72://cima
            if (y>0)y--;
            break;
        case 80://baixo
            if (y<8)y++;
            break;
        case 75://esquerda
            if (x>0)x--;
            break;
        case 77://direita
            if (x<8)x++;
            break;
        }
        return;
    }
    /*O switch poderia ser substituido por um if
    e o código ficaria menor. Mas optei por deixar assim
    para deixar mais visual e fácil de adicionar mais opções de teclas no futuro!*/
    if(espelho[y][x]==' ')
    switch (ch)
    {
    case '1':
        tabuleiro[y][x]='1';
        break;
    case '2':
        tabuleiro[y][x]='2';
        break;
    case '3':
        tabuleiro[y][x]='3';
        break;
    case '4':
        tabuleiro[y][x]='4';
        break;
    case '5':
        tabuleiro[y][x]='5';
        break;
    case '6':
        tabuleiro[y][x]='6';
        break;
    case '7':
        tabuleiro[y][x]='7';
        break;
    case '8':
        tabuleiro[y][x]='8';
        break;
    case '9':
        tabuleiro[y][x]='9';
        break;
    case 8:
        tabuleiro[y][x]=' ';
        break;
    }
    switch (ch)
    {
    case 'q':
    case 'Q':
        tela=0;
        break;
    case 's':
    case 'S':
        tela_jogo(solucao);
        break;
    case 13:
        if(verificar_vitoria()){
            printf("\nGanhou!!\n");
            tela=0;
        }
        else{
            printf("\nIncorreto\n");
        }
        break;
    default:
        break;
    }
}

int main(){
    srand(time(NULL));
    char ch;
    tela_menu();
     while ((ch = _getch()) != 27){//ESC = 27
        printf(TEXT_CLEAR);
        //\x1B[2J limpa a tela
        //\x1B[H volta o cursor para o inicio

        switch (tela)//configura entrada do teclado
        {
        case 0:
            menu(ch);
            break;
        case 1:
            jogo_teclado(ch);
            break;
        }

        switch (tela)//seleciona a tela
        {
        case 0:
            tela_menu();
            break;
        case 1:
            tela_jogo(tabuleiro);
            break;
        }
     }
}
/*
-32
72 cima
-32
75 esquerda
-32
80 baixo
-32
77 direita
*/