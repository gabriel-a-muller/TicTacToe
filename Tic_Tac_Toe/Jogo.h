#include "Velha.h"

//Classe responsavel pelo manuseio dos comandos e chamadas das operacoes de jogo.
class Jogo{
private:
	
public:
	void jogoHumano(); 
	void jogoComputador(); 
	void jogoDificil();
	void jogoFacil();
	Jogo(){}
	void jogoMenu();
};

//Metodo que opera as chamadas para o modo jogador x jogador.
void Jogo::jogoHumano(){
	Velha<Human> jogo;
	int l,c;
	cout << "Início" << endl;
	//o jogo só para ao dar empate ou encontrar algum vencedor.
	while(jogo.getEstado()=="Jogando"){
	try{
		cin.clear();
		cout << jogo.imprimeJogador();
		cin >> l;
		cin >> c;
		jogo.setJogada(l,c);
	}
	//catch, caso ocorra alguma inserção inválida das posições
	catch(InvalidException &e){
		jogo.imprimeJogo();
		cout << e.consulta_erro() << endl << endl;
	}
	}
	cout << jogo.getEstado() << endl << endl;
	return;
}

//Metodo que faz a decisao da dificuldade do modo jogador x computador.
void Jogo::jogoComputador(){
	int d;
	while(1){
	try{
		cout << "1-Fácil" << endl << "2-Difícil" << endl;
		cin >> d;
		if(d==2) jogoDificil();
		else if(d==1) jogoFacil();
		else throw(InvalidException("Comando inexistente!"));
		break;
	}
	catch(InvalidException &e){cout << e.consulta_erro() << endl << endl;}	
	}
	return;
}

//Metodo responsavel pela dificuldade "dificil" no modo jogador x computador.
void Jogo::jogoDificil(){
	cout << endl;
	Velha<Computer> jogo;
	int l,c,k=0;
	cin.clear();
	cin.ignore();
	cout << jogo.imprimeJogador();
	cin >> l;
	cin >> c;
	if(l < 1 || l > 3 || c<1 || c>3){
		jogoDificil();
		return;
	}
	jogo.setJogada(l,c);
	Tabuleiro t(jogo.getTab());
	Computer player(t);
	Node<dados> aux(l-1,c-1);
	Tree<dados> a(aux);
	player.preencheArvore(a);
	Node<dados>& n = a.getRaiz();
	
	
	while(jogo.getEstado()=="Jogando"){
	try{
		if(k==1){
		cin.clear();
		cin.ignore();
		cout << jogo.imprimeJogador();
		cin >> l;
		cin >> c;
		jogo.setJogada(l,c);
		n = player.avancaNode(l-1,c-1);
		}
			
		//Se o jogo empatar, sai do laço while
		if(jogo.getTab().jogadasRestantes()==false){
			break;
		}
		//Atualiza o tabuleiro para o computador
		Tabuleiro t(jogo.getTab());
		player.setTabuleiro(t);
		player.setMatriz();
		
		//Jogada do computador
		cout << jogo.imprimeJogador();
		player.encontreJogada(n);
		cout << player.getRow()+1 << " " << player.getCol()+1 << endl;
		jogo.setJogada(player.getRow()+1,player.getCol()+1);
		k=1;
		n = player.getNode();
	}
	catch(InvalidException &e){
		jogo.imprimeJogo();
		cout << e.consulta_erro() << endl << endl;
	}
	}
	cout << jogo.getEstado() << endl << endl;
	return;
}

//Metodo responsavel pela dificuldade "facil" no modo jogador x computador
void Jogo::jogoFacil(){
	Velha<Computer> jogo;
	int l,c;
	Tabuleiro t(jogo.getTab());
	Computer player(t);

	while(jogo.getEstado()=="Jogando"){
	try{
		cin.clear();
		//cin.ignore();
		cout << jogo.imprimeJogador();
		cin >> l;
		cin >> c;
		jogo.setJogada(l,c);
		//Se o jogo empatar, sai do laço while
		if(jogo.getTab().jogadasRestantes()==false)	break;
		else if(jogo.getTab().verificaVencedor()!=0) break;
		//atualizando tabuleiro para o computador
		Tabuleiro t(jogo.getTab());
		Computer player(t);
		//Jogada do computador
		cout << jogo.imprimeJogador();
		player.findEasyMove();				
		cout << player.getRow()+1 << " " << player.getCol()+1 << endl;
		jogo.setJogada(player.getRow()+1,player.getCol()+1);

	}
	catch(InvalidException &e){
		jogo.imprimeJogo();
		cout << e.consulta_erro() << endl << endl;
	}
	}
	cout << jogo.getEstado() << endl << endl;
	return;	
}

//Menu do jogo. Neste metodo eh apresentado as opcoes de jogo existentes
//e chamadas dos metodos pedidos pelo usuario.
void Jogo::jogoMenu(){
	cout << "TIC TAC TOE!" << endl << endl;
	//laco de continuacao do jogo.
	while(1){
	try{	
		cout << "Opções de jogo: " << endl << "1- Contra outro jogador" << endl << "2- Contra o computador" << endl;
		cout << "0- Sair do jogo" << endl;
		int d;
		cin >> d;
		cout << endl;
		if(d==1) jogoHumano();
		else if(d==2) jogoComputador();
		else if(d==0) return;
		else throw(InvalidException("Comando inexistente!"));
	}
	catch(InvalidException &e){cout << e.consulta_erro() << endl << endl;}
	}
}	
