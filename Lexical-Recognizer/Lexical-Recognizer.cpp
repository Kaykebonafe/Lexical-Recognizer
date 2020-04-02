// Lexical-Recognizer.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

//Definindo o tamanho máximo do vetor 
#define TAM 500

using namespace std;

//Agrupamento dos protótipos das funções-estado
void e0();
void e1();
void e2();
void e3();
void e4();
void e5();
void e6();

//Agrupamento dos protótipos das funções sigma
void sigma1();
void sigma2();
void sigma3();
void sigma4();
void sigma5();
void sigma6();
void sigma7();
void sigma8();
void sigma9();
void sigma10();

//Variáveis relacionadas ao transdutor
string frase = "";
string tempC = "";
int tempN = 0;
string tempS = "";
char tabPalavrasReservadas[9][6] = { "IF", "THEN", "ELSE", "GOTO", "LET", "END", "PRINT", "READ", "OF" };
string tabela[TAM];
int tamTabela = 0;

//Variáveis de checagem
string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
string numeros = "0123456789";
string sinais = "();:><=,+-*/{}[].?!@#$¨¬&*_§ªº''#";

//Indice do caracter numa frase
int p = 0;

//Flag e auxiliar
bool aux = true;
string strAux = "";

//Função auxiliar para imprimir a tabela
void imprimeTabela() {
    for (int i = 0; i < tamTabela; i++) {
        cout << i << " ... " << tabela[i] << endl;

    }

}

void imprimeTabelaReservadas() {
    for (int i = 0; i < sizeof(tabPalavrasReservadas) / sizeof(tabPalavrasReservadas[0]); i++) {
        cout << i << " ... " << tabPalavrasReservadas[i] << endl;

    }

}

//Função que checa se o caracter é uma letra, um número, 
//um espaço ou o fim da frase
void checaCaracter() {
    for (int i = 0; i < alfabeto.length(); i++) {
        if (frase[p] == alfabeto[i]) {
            aux = true;
            strAux = "letra";

        }

    }

    for (int i = 0; i < numeros.length(); i++) {
        if (frase[p] == numeros[i]) {
            aux = true;
            strAux = "numero";

        }

    }

    for (int i = 0; i < sinais.length(); i++) {
        if (frase[p] == sinais[i]) {
            aux = true;
            strAux = "sinal";

        }

    }

    if (frase[p] == ' ') {
        strAux = "espaco";
        aux = false;

    }

    else if (frase[p] == 0) {
        strAux = "fim";
        aux = false;

    }

    else if (frase[p] == '%') {
        strAux = "comentario";
        aux = false;

    }
    return;

}

//Função que representa o estado 0
void e0() {
    checaCaracter();
    tempS = "";
    tempN = 0;
    tempC = "";
    if (strAux == "espaco") {
        p++;
        e0();

    }

    else if (strAux == "fim") {
        cout << endl;
        imprimeTabela();
        cout << endl;
        imprimeTabelaReservadas();
        cout << endl;

    }

    else if (strAux == "letra") {
        sigma1();
        p++;
        e1();

    }

    else if (strAux == "numero") {
        sigma4();
        p++;
        e2();

    }

    else if (frase[p] == sinais[3]) {
        p++;
        e3();

    }

    else if (strAux == "comentario") {
        p++;
        e6();

    }

    else {
        sigma9();
        p++;
        e5();

    }

}

//Função que representa o estado 1
void e1() {
    checaCaracter();
    if (strAux == "letra") {
        sigma2();
        p++;
        e1();

    }

    else if (strAux == "numero") {
        sigma2();
        p++;
        e1();

    }
    else {
        sigma3();
        e0();

    }

}

//Função que representa o estado 2
void e2() {
    checaCaracter();
    if (strAux == "numero") {
        sigma5();
        p++;
        e2();

    }
    else {
        sigma6();
        e0();

    }
}

//Função que representa o estado 3
void e3() {
    checaCaracter();
    if (frase[p] == sinais[6]) {
        p++;
        e4();

    }

    else {
        sigma7();
        e0();

    }

}

//Função que representa o estado 4
void e4() {
    sigma8();
    e0();

}

//Função que representa o estado 5
void e5() {
    sigma10();
    e0();

}

//Função que representa o estado 6
void e6() {
    while (frase[p] != 0) {
        p++;

    }
    e0();

}

//Função sigma 1
void sigma1() {
    tempS = frase[p];

}

//Função sigma 2
void sigma2() {
    tempS += frase[p];

}

//Função sigma 3
void sigma3() {   
    bool check = false;
    for (int i = 0; i < sizeof(tabPalavrasReservadas) / sizeof(tabPalavrasReservadas[0]); i++) {
        if (tempS == tabPalavrasReservadas[i]) {
            check = true;
            cout << "P(" << i << ")";

        }

    }
    
    if (!check) {
        if (tamTabela > 0) {
            bool existe = false;
            int i = 0;
            for (i = 0; i < tamTabela; i++) {
                if (tempS == tabela[i]) {
                    existe = true;
                    break;

                }

            }

            if (existe)
                cout << "V(" << i << ")";

            else {
                tabela[tamTabela] = tempS;
                cout << "V(" << tamTabela << ")";
                tamTabela++;

            }

        }
        else {
            tabela[tamTabela] = tempS;
            cout << "V(" << tamTabela << ")";
            tamTabela++;

        }
    
    }

}

//Função sigma 4
void sigma4() {
    tempN = (frase[p] - '0');

}

//Função sigma 5
void sigma5() {
    tempN = (frase[p] - '0') + (tempN * 10);

}

//Função sigma 6
void sigma6() {
    cout << "N(" << tempN << ")";

}

//Função sigma 7
void sigma7() {
    cout << " : ";

}

//Função sigma 8
void sigma8() {
    cout << " := ";

}

//Função sigma 9
void sigma9() {
    tempC = frase[p];

}

//Função sigma 10
void sigma10() {
    cout << tempC;

}

int main() {
    cout << "Digite a sentença: " << endl;
    getline(cin, frase);
    cout << endl;
    e0();
    cin.get();

    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
