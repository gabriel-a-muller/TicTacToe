#ifndef TABULEIRO_H
#define TABULEIRO_H
#include <iostream>
#include <string>
using namespace std;


//classe para tratamento de excecao
class InvalidException {
private:
	string erro;
public:
	InvalidException(string errotxt = ""){erro=errotxt;}
	string consulta_erro()const{return erro;}
};

//classe responsavel por armazenar o numero de jogadas
//e os dados do tabuleiro.
class Tabuleiro{
private:
	int jogadas;
	char matriz[3][3];
public:
	//construtor padrão
	Tabuleiro(){
		jogadas=0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)
				matriz[i][j]='_';
		}
	}
	//Construtor de cópia
	Tabuleiro(const Tabuleiro &t){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)
				matriz[i][j]=t.matriz[i][j];
		}
		jogadas=t.jogadas;
	}
	int getJogadas(){return jogadas;}
	void incrementaJogada(){jogadas++;}
	int verificaVencedor();
	void setLetra(int l,int c,char letra){matriz[l][c]=letra;}
	void imprimeTabuleiro();
	bool jogadasRestantes();
	char getMatriz(int l,int c);
	bool celulaVazia(int l,int c);
};

//Função que verifica na matriz do tabuleiro se há vencedores ou não
//retorna 10 caso X seja vencedor, -10 para vencedor O e retorna 0 para
//os demais resultados.
int Tabuleiro::verificaVencedor(){
	for(int i=0;i<3;i++){
		if(matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2]){
			if(matriz[i][0]=='x'){return 10;}
			else if(matriz[i][0]=='o'){return -10;}
		}
	}for(int j=0;j<3;j++){
		if(matriz[0][j] == matriz[1][j] && matriz[1][j] == matriz[2][j]){
			if(matriz[0][j]=='x'){return 10;}
			else if(matriz[0][j]=='o'){return -10;}
		}
	}if(matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2]){
		if(matriz[1][1]=='x'){return 10;}
		else if(matriz[1][1]=='o'){return -10;}
	}
	else if(matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0]){
		if(matriz[1][1]=='x'){return 10;}
		else if(matriz[1][1]=='o'){return -10;}
	}

	return 0;
}

//imprime o tabuleiro
void Tabuleiro::imprimeTabuleiro(){
		for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;	
	return;
}
//verifica se há jogadas restantes.
//retorna true caso haja jogadas restantes
//e false caso contrário;
bool Tabuleiro::jogadasRestantes(){
	if(jogadas==9){return false;}
	return true;
}
//retorna um valor da matriz
char Tabuleiro::getMatriz(int l,int c){
	return matriz[l][c];
}
//verifica se a célula na posição enviada como parâmetro
//é vazia. Retorna true caso verdadeiro, false caso contrário.
bool Tabuleiro::celulaVazia(int l,int c){
	if(matriz[l][c]=='_')
		return true;
	return false;
}
#endif
