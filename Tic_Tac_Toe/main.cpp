#include "Jogo.h"

int main (int argc, char** argv){
	Jogo velha;
	int d;
	if(argc == 1) velha.jogoMenu();
	else if(argc == 2){
		d = atoi(argv[1]);
		if(d==1) velha.jogoHumano();
		else if(d==2) velha.jogoComputador();
	}
	else if(argc == 3){
		d = atoi(argv[1]);
		if(d==2){
			d = atoi(argv[2]);
			if(d==1) velha.jogoFacil();
			else if(d==2) velha.jogoDificil(); 
		}
	}
	return 0;
}
