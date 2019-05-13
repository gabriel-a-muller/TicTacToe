#ifndef COMPUTER_H
#define COMPUTER_H
#include "Tree.h"
using namespace std;


//classe para quando houver dois jogadores humanos.
//armazena uma string contendo o jogador atual.
class Human{
private:
	string jogador;
public:
	Human(string name="Jogador 1"):jogador{name}{}
	string getJogador(){return jogador;} 
	string mudaJogador(){
		if(jogador=="Jogador 1"){jogador="Jogador 2";}
		else{jogador="Jogador 1";}
		return jogador;	
	}
};

//classe responsavel pelo comportamento e decisao do computador.
//utilizada tambehm para printar em tela quando o usuario
//esta jogando contra o computador (template)
class Computer{
private:
	int row, col;
	Tabuleiro t;
	char tabuleiro[3][3];
	string jogador;
	Node<dados> current_node;


public:
	char const player = 'o', opponent = 'x';
	//construtores para recebimento do "nome" do jogador e tabuelrio, respectivamente.
	Computer(string name="Jogador 1"):jogador{name}{}
	Computer(Tabuleiro t); 	

	//metodo para a atualizacao do Tabuleiro t.
	void setTabuleiro(Tabuleiro t){this->t=t;}

	//metodos set e get para o jogador atual.
	string mudaJogador();	
	string getJogador(){return jogador;}
	
	//Metodos responsaveis pelas operacoes que envolvem operacoes para
	//a matriz da classe.
	bool isMovesLeft(char tabuleiro[3][3]);
	int verifica(char b[3][3]);
	int getRow(){return row;}
	int getCol(){return col;}
	void setMatriz(){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				tabuleiro[i][j] = t.getMatriz(i,j);
			}
		}
	}

	//Metodo responsavel por operar a dificuldade "facil" do modo jogador x computador.
	void findEasyMove();

	//Metodos utilizados para a criacao e operacao da arvore de decisao na aplicacao
	//da dificuldade "dificil".
	int preencheArvoreAux(char tabuleiro[3][3], Node<dados>& node, int profundidade, bool ehMax);
	void preencheArvore(Tree<dados> &tree);
	void imprime(Node<dados> n){n.imprime();}
	void encontreJogada(Node<dados>& n);
	Node<dados>& getNode(){return current_node;}
	Node<dados>& avancaNode(int x, int y);
	
};
 

Computer::Computer(Tabuleiro t){
	this->t = t;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			tabuleiro[i][j]=t.getMatriz(i,j);
		}
	}
}	

string Computer::mudaJogador(){
	if(jogador=="Jogador 1"){jogador="Computador";}
	else{jogador="Jogador 1";}
	return jogador;	
}

// Essa funcao retorna se ainda ha jogadas restantes
// no tabuleiro. Retorna falso caso nao haja jogadas
//e true caso contrario.
bool Computer::isMovesLeft(char tabuleiro[3][3]){
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (tabuleiro[i][j]=='_')
                return true;
    return false;
}
 
// Funcao que verifica se ha algum vencedor
// Ou se o jogo continuara em funcionamento.
// Retorna -10 caso X venca, 10 para O vencedor
// e 0 em demais casos.
int Computer::verifica(char b[3][3]){
    // Checando as linhas da matriz
    for (int row = 0; row<3; row++){
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player)
                return +10;
            else if (b[row][0]==opponent)
                return -10;
        }
    }
 
    // Checando colunas da matriz
    for (int col = 0; col<3; col++){
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==player)
                return +10;
 
            else if (b[0][col]==opponent)
                return -10;
        }
    }
 
    // Checando diagonais
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]){
        if (b[0][0]==player)
            return +10;
        else if (b[0][0]==opponent)
            return -10;
    }
 
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]){
        if (b[0][2]==player)
            return +10;
        else if (b[0][2]==opponent)
		    return -10;
    }
 
    // Se nao ha ganhador, retorna 0
    return 0;
}
 	
//Retorna uma jogada aleatoria do computador para
//os atributos "row" e "col".
void Computer::findEasyMove(){
	srand(time(NULL));
	row=rand()%3+1;
	col=rand()%3+1;
	while(t.celulaVazia(row-1,col-1)==false){
		row=rand()%3+1;
		col=rand()%3+1;
	}
	row--;
	col--;
	return;
}

//Metodo para preenchimento da arvore por recursao.
//Recebe a matriz do tabuleiro, uma referencia de dado do tipo Node<dados>, profundidade e  e se o jogador atual eh
//maximizador ou minimizador.
//Armazena os dados dentro dos nodes (posicoes, profundidade e pontuacao).
//Retorna pontuacao do node atual.
int Computer::preencheArvoreAux(char tabuleiro[3][3], Node<dados>& node, int profundidade, bool ehMax){	
	int score  = verifica(tabuleiro);
	char teste = (ehMax) ? player:opponent;
	node.getDado().score = (ehMax) ? -1000:1000; 
    // Se o maximizador ou minimizador ganhar o jogo, retorna seu score
    if (score == 10 || score == -10){
		node.getDado().score = score;
		return score;
    }
	// Se nao houver mais movimentos e vencedores, eh um empate
    if (isMovesLeft(tabuleiro)==false){
		node.getDado().score = 0;
		return score;
    }
	for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            // Cheque se ela esta vazia
            if (tabuleiro[i][j]=='_'){

                // Faca a jogada
                tabuleiro[i][j] = teste;
				Node<dados>& referencia = node.criaFilho(dados{i,j,0,profundidade});
				if(ehMax) node.getDado().score = max( node.getDado().score,preencheArvoreAux(tabuleiro, 
																							referencia, profundidade+1, !ehMax) );
				else node.getDado().score = min( node.getDado().score,preencheArvoreAux(tabuleiro, referencia,
																								 profundidade+1, !ehMax) );
				// Desfaca a jogada
                tabuleiro[i][j] = '_';
            }
        }
    }
    return node.getDado().score;	
}

//Recebe uma referencia de arvore do tipo Tree<dados> como parametro
//Chama a funcao preencheArvoreAux recursiva para preencher
//a arvore recebida com os dados de decisao.
void Computer::preencheArvore(Tree<dados> &tree){
	preencheArvoreAux(tabuleiro,tree.getRaiz(),1,true);		
}

//Metodo responsavel por setar os atributos, "row" e "col", com dados
//da melhor jogada possivel para o computador percorrendo a arvore
//de decisao existente, passada atraves do parametro que eh uma referencia
//para um node do tipo Node<dados>.
void Computer::encontreJogada(Node<dados>& node){
	int bestVal = -1000;
	row = -1;
	col = -1;
	for (int i = 0; i<node.qtdFilhos(); i++){
		Node<dados> n = node.avancaFilho(i);
		int X = n.getDado().x;
		int Y = n.getDado().y;
		if (tabuleiro[X][Y]=='_'){ 
	
				tabuleiro[X][Y] = player;
				int moveVal = n.getDado().score;

			tabuleiro[X][Y] = '_';
			if (moveVal > bestVal){
                row = X;
                col = Y;
				current_node = n; 
                bestVal = moveVal;
            }
		}
	}
}

//Metodo que procura nos filhos do atributo "current_node" um node com
//a posicao recebida como parametro.
//Retorna a referencia do node encontrado.
//Caso nao encontre o node havera tratamento da excessao.
Node<dados>& Computer::avancaNode(int x, int y){
	for(int i=0;i<current_node.qtdFilhos();i++){
		Node<dados>& n = current_node.avancaFilho(i);
		
		if(n.getDado().x==x && n.getDado().y==y)
			return n;
	}
	throw(InvalidException("Node nao encontrado"));
}
	
#endif
