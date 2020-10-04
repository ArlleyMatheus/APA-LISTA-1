#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
Para o problema do quadrado m�gico h� diversas implementa��es diferentes, at� implementa��es com algoritmos gen�ticos,
mas para esse trabalho, foi escolhido um metodo mais direto e simples. Para isso tem que levar em considera��o que existem
3 tipos diferentes de quadrados m�gicos e para cada um, existe uma forma diferente de solucionar:
1 -> Quadrado m�gico Impar, em que o valor de n � impar, chamado de 'Odd Even' (3,5,7,9,...)
2 -> Quadrados que s�o divisiveis perfeitamente por 4, em que valor de n pode ser encontrado atrav�s da formula n = (m*4), 
	 chamados de 'Doubly Even' (4,8,12,16,...)
3 -> Quadrado que s�o divisiveis por 2, s�o aqueles que n�o entram na caso acima, mas ainda s�o pares e o valor de n � encontrado 
	 atrav�s da formula n = 2(2*m+1), s�o chamados de 'Singly even' (6,10,14,18,...)
*/

void printSquare(int n, int square[][n]){
	//Fun��o usada para imprimir os quadrados m�gicos
	int i, j;
	printf("Solucao para n = %d e soma magica = %d\n", n, (n*(n*n+1)/2));
	for(i = 0; i < n; i++){
		printf("| ");
		for(j = 0; j < n; j++){
			printf("%3d |", square[i][j]);
		}
		printf("\n");
	}
}

void oddSolution(int n,int square[][n]){
	/*
	Quando se n � impar, se come�a na linha do meio e na ultima coluna
	(existem implementa��es diferentes, mas sempre se come�a pelo cantos da coluna ou linha do meio)
	Tem que se levar em considera��o 3 condi��es
	1 -> A pr�xima posi��o � encontrada decrementando a linha(i) em 1 (i--) e incrementando coluna(j) em 1 (j++)
		,se o valor de i passar a ser negativo, ele recebe n-1 e se a coluna tiver valor igual a n recebe 0.
	2 -> Se a posi��o em quest�o ja tiver um valor, ent�o j = j - 2 e i = i + 1
	3 -> Se a linha(i) tiver valor -1 e a coluna(j) tiver valor n, ent�o as novos valores passar a ser i = 0 , j = n-2
	*/
	int i, j;
	
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			square[i][j] = 0;
		}
	}
	
	i = n/2; //setando os valores que ser�o 
	j = n-1; //pontos de inicio do algoritmo
	int num = 1;
	
	while(num <= n*n) {
        //Controla a terceira condi��o
		if (i == -1 && j == n){
            j = n-2;
            i = 0;
        }
        else {
            //Controle da primeira condi��o para caso o j tenha valor menor que 0
            //isto �, caso saia do quadrado pela parte de cima
            if (i < 0) i = n-1;
                
            //Controle da primeira condi��o para caso o j tenha valor igual a n
            //isto �, caso saia do quadrado pela lateral
            if (j == n) j = 0;
        }
        //Controla a segunda condi��o para caso a posi��o verificada j� tenha um valor
        if (square[i][j] != 0) {
            j = j-2;
            i++;
        }
        else{
			square[i][j] = num; //coloca o valor naquela posi��o
			num++;
        	//Controle da primeira condi��o em que decrementa i e incrementa j
			i--; 
			j++;
		}
    }
}

void doublyEvenSolution(int n){
	
	int square[n][n], i, j; 
	int count = 1;
	//Primeiro passo � preencher o quadrado normalmente com valor de 1 a N
    for ( i = 0; i < n; i++){
    	for ( j = 0; j < n; j++) {
    		square[i][j] = count;
			count++; 
		}
			
	}
   
    // O proximo passo � alterar as posi��es de valores dentro da quadrado
    // por posi��es especificas dentro da matriz seguindo a seguinte regra:  
    // (n*n+1)-square[i][j] 
    
    // Se come�a pelo topo esquerda do quadrado  
    // A regi�o que ter� seus valores trocados � um quadrado menor com o tamanho (n/4)�
    // dentro do quadrado maior e ter� seus valores trocados com os valores que est�o
    // no quadrado de tamanho (n/4)� do canto inferior direito, de forma espelhada e invertida
    for ( i = 0; i < n/4; i++) 
        for ( j = 0; j < n/4; j++) 
            square[i][j] = (n*n + 1) - square[i][j]; 
     
    // Agora se troca os valores do topo direito do quadrado seguindo a mesma ideia
    // do passo anterior, uma regi�o quadrada (n/4)� tem seus valores substituidos
    // por um quadrado (n/4)� que se encontra no canto inferior direito, de forma espelhada e invertida
    for ( i = 0; i < n/4; i++) 
        for ( j = 3 * (n/4); j < n; j++) 
            square[i][j] = (n*n + 1) - square[i][j]; 
      
    // Agora se faz o mesmo processo em rela��o ao canto inferior esquerdo, seguindo a mesma
	// ideia dos dois primeiros passos, o que muda � que o vai se basear nos antigos valores
	// do canto superior direito de forma espelhada e invertida
    for ( i = 3 * n/4; i < n; i++) 
        for ( j = 0; j < n/4; j++) 
            square[i][j] = (n*n+1) - square[i][j]; 
     
    // Agora se faz o mesmo processo em rela��o ao canto inferior direito, seguindo a mesma
	// ideia dos dois primeiros passos, o que muda � que o vai se basear nos antigos valores
	// do canto superior esquerdo de forma espelhada e invertida
    for ( i = 3 * n/4; i < n; i++) 
        for ( j = 3 * n/4; j < n; j++) 
            square[i][j] = (n*n + 1) - square[i][j]; 
    
    // Agora se altera o centro do quadrado magico, inverteando os valores internos de forma espelhada
    // e invertida, o quadrado interno que ser� alterado tem tamanho (n/2)�
    for ( i = n/4; i < 3 * n/4; i++) 
        for ( j = n/4; j < 3 * n/4; j++) 
            square[i][j] = (n*n + 1) - square[i][j]; 
            
    printSquare(n, square);
}

void singlyEvenSolution(int n) {
	// | 1Q | 2Q |
	// | 3Q | 4Q |
	// Exemplo dos quadrantes dentro do quadrado magico
	//Esse quadrado tem uma caracteristicas interessante, pelo n ser um par e n�o divisivel por 4,
	//a metade de N vai sempre ser um valor impar e usaremos isso para resolver o quadrado m�gico.
	//O quadrado de tamanho N ter� dentro dele 4 quadrados de tamanho n/2, como eles s�o impares, se utiliza
	//o oddSolution para preencher esses quadrados impares.
	//Ap�s isso cada quadrante do quadrado maior ter� 4 sub quadrados preenchidos de 1 at� n/2, para criar 
	//o quadrado m�gico � necessario somar um valor em cada numero de cada quadrante, mas esse valor varia por quadrante, por conta do fator de multiplica��o
	//No primeiro quadrante(topo esquerda) � somado ((n/2)^2 * fator), sendo fator = 0, 
	//no o segundo quadrante(topo direito) � somado ((n/2)^2 * fator), sendo fator = 2,
	//no terceiro quadrante(base esquerda) � somado ((n/2)^2 * fator), sendo fator = 3,
	//e no ultimo quadrante (base direita) � somado ((n/2)^2 * fator), sendo fator = 1,
    
    int halfN = (n/2);
    //Inv�s de gerar os valores dentro do quadrado maior, fazemos isso em uma matriz a parte e utilizamos ela para as opera��es que ser�o feitas.
	int subSquare[halfN][halfN]; 
		 
	oddSolution(halfN, subSquare);
	
    int subSquaresFactors[] = {0, 2, 3, 1}; //Ser� utilizado para determinar o valor que ser� somado ao numero dentro de cada quadrante
    
    int square[n][n];

 	int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int factor;
            
            if((i < halfN) && (j < halfN)) { //quadrante topo esquerda
            	factor = 0;
			}
            else if((i < halfN) && (j >= halfN)){ // quadrante topo direita
            	factor = 2;
			} 
            else if((i >= halfN) && (j < halfN)){ //quadrante base esquerda
            	factor = 3;
			}
            else{// quadrante base direita
            	factor = 1;
			}  
            
            square[i][j] = subSquare[i % halfN][j % halfN]; // adicionando o valor do quadrado menor no quadrado maior
            square[i][j] += halfN * halfN * factor; //soma o valor extra a posi��o de determinado quadrante
        }
    }
 
 	//Ainda � necessario mais um passo para se chegar ao quadrado m�gico que consiste em
 	//pegar n�meros de posi��es especificas e trocar com  numeros de outras posi��es
 	//As trocas ir�o acontecer no quadrante da esquerda( 1 e 3) e as (m - 1) colunas dos quadrantes da direita(2 e 4) [O m vem da formula n = 2(2*m-1)]
 	//Nos da esquerda, os numeros a esquerda da coluna que divide o quadrante ao meio v�o trocar de lugar com o vizinho na vertical.
 	//Os numeros que est�o no quadrante 1 v�o para o 3 e vice versa, unica excess�o � na linha que se encontra no meio do quadrante,
 	//Na linha do meio se pula uma casa, isto �, se pega os numeros da posi��o 1 ate o numero do centro do quadrante.
 	//E para saber se teremos que alterar os quadrantes 2 e 4, � so usar a formula m-1 e o resultado � a quantidade de colunas que devem ser trocadas
 	// entre os quadrantes 2 e 4.
 	//Exemplo: no caso de n = 6, aplicamos em 6 = 2(2*m-1), temos m = 1, logo 1-1 � 0, logo n�o se mexe em nenhuma coluna, ja caso n = 10, 
	//teremos m = 2, 2-1 = 1, ent�o teriamos que mexer na ultima coluna dos quadrantes 2 e 4 e inverter eles.
	//Ao fim desse processo, temos um quadrado magico
    int nColsLeft = halfN / 2;
    int nColsRight = nColsLeft - 1;
 
    for (i = 0; i < halfN; i++){
    	for (j = 0; j < n; j++) {
            if (j < nColsLeft || j >= n - nColsRight || (j == nColsLeft && i == nColsLeft)) {

                if (j == 0 && i == nColsLeft)
                    continue;
 
                int tmp = square[i][j];
                square[i][j] = square[i + halfN][j];
                square[i + halfN][j] = tmp;
        	}
    	}	
	}
	printSquare(n, square);
}


int main(){
	int n, max;
	
	printf("N minimo eh sempre 3\nInsira o valor maximo de n:");
	scanf("%d", &max);
	
	n = 3;
	while(n <= max){
		int square[n][n];
		if((n%2) == 1){
			oddSolution(n, square);
			printSquare(n, square); //caso de impar
		}else if(n%4 == 0){
			doublyEvenSolution(n); //caso de divisiveis por 4
		} else if(((n%4)-2) == 0){
			singlyEvenSolution(n); // caso dos divisiveis por 2, mas n�o por 4
		}
		n++;	
	};

	return 0;
}
