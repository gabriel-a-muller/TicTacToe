#ifndef VELHA_H
#define VELHA_H
#include "Tabuleiro.h"
#include "Computer.h"
using namespace std;


//template para impressao de quem esta jogando
template <typename T>
//classe responsavel pelas principais operacoes do jogo.
class Velha{
private:
	Tabuleiro t;
	char letra_atual;
	string estado;
	T formata;
	void setEstado();
	void mudaLetra();
public:
	string imprimeJogador();
	Velha(const Velha &c);
	
	Velha(){
		letra_atual='x';
		estado="Jogando";
	}

	void changeJogador();
	char getLetra(){return letra_atual;}
	string getEstado(){return estado;}
	void setJogada(int l,int c);
	void imprimeJogo();	
	Tabuleiro getTab(){return t;}
};

//atualiza o estado atual de jogo.
template <typename T> void Velha<T>::setEstado(){
	int est=t.verificaVencedor();
	if(est==10){estado="Jogador X venceu!";}
	else if(est==-10){estado="Jogador O venceu!";}
	else if(t.getJogadas()==9){estado="Empate!";}
	return;
}
//retorna o jogador atual
template <typename T> string Velha<T>::imprimeJogador(){
	return formata.getJogador()+": ";
}
//muda a letra de jogada atual
template <typename T> void Velha<T>::mudaLetra(){
	if(letra_atual=='x') letra_atual='o';
	else letra_atual='x';
	return;
}

//construtor de cópia
template <typename T> Velha<T>::Velha(const Velha &c){
	t=c.t;
	letra_atual=c.letra_atual;
	estado=c.estado;
}
//muda para o próximo jogador
template <typename T> void Velha<T>::changeJogador(){
	formata.mudaJogador();
}
//seta a jogada na posição enviada como parâmetro;
//caso a posição seja inválida, haverá tratamento de exceção
template <typename T> void Velha<T>::setJogada(int l,int c){     				
	if(t.getJogadas()==9){return;}	
	l--;
	c--;
	//if(l!=0 || l!=1 || l!=2 || c!=0 || c!=1 || c!=2) throw(InvalidException("Posição inválida!"));
	if(l<0 || l>2 || c<0 || c>2) throw(InvalidException("Posição inválida!"));
	if(t.celulaVazia(l,c)!=true) throw(InvalidException("Posição Ocupada!"));
	t.setLetra(l,c,letra_atual);	
	mudaLetra();
	changeJogador();
	t.incrementaJogada();
	imprimeJogo();
	setEstado();
	return;
}	
//imprime o tabuleiro do jogo
template <typename T> void Velha<T>::imprimeJogo(){
	t.imprimeTabuleiro();
	return;
}	
#endif
