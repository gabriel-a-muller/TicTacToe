#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//struct que armazena a posicao da jogada (x,y),
//a pontuacao da posicao da arvore e sua profundidade.
struct dados {
	int x;
	int y;
	int score;
	int profundidade;
};


//classe Node generica.
//metodos e atributos para a representacao de um node de uma arvore.
//armazena um dado do tipo T1 e um vector de nodes (filhos).
template <typename T1>
class Node{
		std::vector < Node<T1> > filhos;
		T1 dado;
	public:
		Node(){}
		Node(int x, int y,int profundidade=0,int score=70){
			dado.x = x;
			dado.y = y;
			dado.profundidade = profundidade;
			dado.score = score;		
		}

		Node(const Node& n){
			dado.x=n.dado.x; 
			dado.y=n.dado.y;
			dado.score=n.dado.score;
			dado.profundidade=n.dado.profundidade;
			filhos=n.filhos;
		}

		Node(T1 dado){this->dado=dado;}
		Node<T1>& criaFilho(T1 dado){filhos.emplace_back(dado);return filhos.back();}
		void criaFilho(){filhos.emplace_back();}
		T1& getDado(){return dado;}
		Node<T1>& avancaFilho(int num){return filhos[num];}
		int qtdFilhos(){return filhos.size();}

		void imprime(){
			cout << "X: " << getDado().x << endl;
			cout << "Y: " << getDado().y << endl;
			cout << "Score: " << getDado().score << endl;
			cout << "Profundidade: " << getDado().profundidade << endl;
		}

		void imprimeNo(){
			for(int i=0;i<qtdFilhos();i++){
				filhos[i].imprime();
			}
		}
				
};

//classe para arvore generica.
//armazena um dado do tipo Node como raiz da arvore.
template <typename T>
class Tree{
private:
	Node<T> raiz;
public:
	Tree(Node<T> r){raiz=r;}
	Node<T>& getRaiz(){return raiz;}
};

#endif
