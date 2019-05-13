TIC TAC TOE!
Por Gabriel Alexandre Müller

Jogo onde há um tabuleiro 3x3, no qual o objetivo é preencher três células (uma "trinca") com o
mesmo caracter ('X' ou 'O').

Regras:

	Há duas opções de jogo apresentadas incialmente, jogar com outro jogador (1) ou contra o computador (2).
	Ao escolher a opção 2, tem-se a possibilidade de escolher dois míveis de dificuldade (fácil e difícil). 

    1- O primeiro jogador será representado pelo caracter 'X'. 
	2- O jogo irá terminar apenas quando haver um vencedor ou quando o jogo empatar ("dar velha").

	COMANDOS:
	 Para a entrada de uma jogada deve-se digitar o valor para a linha e em seguida um valor para a coluna.
	 Não serão aceitos valores menores que 1 e/ou maiores que 3.
	 Exemplo de entrada:
	 Jogador 1:	1 1
	 Jogador 2:	2 3

	 Saída:
	
	 x _ _
	 _ _ _
     _ _ _

	 x _ _
	 _ _ o
	 _ _ _

	CHAMADA EM TEMPO DE EXECUÇÃO:
	
	Para realizar a chamada do tipo de jogo em tempo de execução deve-se enviar as ordens de jogo
	em sequência de necessidade através da compilação via terminal.
	
	Exemplo de chamada:

	1- make ARGS = "2 1" run
	2- make ARGS = "1" run

	Exemplo 1 fará com que o programa esteja no modo (2)Humano vs Computador na dificuldade (1)fácil.
	Exemplo 2 fará a chamada para o modo (1)Humano vs Humano.


http://ubuntued.info/como-instalar-o-latex-no-ubuntu

