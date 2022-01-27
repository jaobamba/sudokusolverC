#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int sudoku[9][9];

void printSudoku(int sudoku[9][9]){

	for(int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			printf("%d\t", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
	
int lemmeCheck(int x, int y, int num, int sudoku[9][9]){

    for(int i = 0; i < 9; i++){
		if(sudoku[x][i] == num){
			return 1;
		}
	}

    for(int i = 0; i < 9; i++){
		if(sudoku[i][y] == num){
			return 1;
		}
	}

	if(x < 3){
		x = 0;
	}
	else if(x < 6){
		x = 3;
	}
	else{
		x = 6;
	}

	if(y < 3){
		y = 0;
	}
	else if(y < 6){
		y = 3;
	}
	else{
		y = 6;
	}	

	for(int i = x; i < x+3; i++){
		for(int j = y; j < y+3; j++){
			if(sudoku[i][j] == num){
				return 1;
			}
		}
	}
	return 0;
}

int solve(int x, int y, int sudoku[9][9]){

	int num = 1;
	int tx = 0;
	int ty = 0;

	if(sudoku[x][y] != 0){

		if(x == 8 && y == 8){
			return 1;
		}

		if(x < 8){
			x++;
		}
		else{
			if(y < 8){
				x = 0;
				y++;
			}
		}

		if(solve(x,y,sudoku)){
			return 1;
		}
		else{
			return 0;
		}

	}

	if(sudoku[x][y] == 0){
		while(num < 10){
			if(!lemmeCheck(x, y, num, sudoku)){
				sudoku[x][y] = num;

				if(x == 8 && y == 8){
					return 1;
				}

				if(x < 8){
					tx = x + 1;
				}

				else{
					if(y < 8){
						tx = 0;
						ty = y + 1;
					}
				}

				if(solve(tx,ty,sudoku)){
					return 1;
				}
			}
			num++;
		}
		sudoku[x][y] = 0;
	}
	return 0;
}


int main(int argc, char* argv[argc+1]){

	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) return 0;

    clock_t time = clock();
	int sudoku[9][9];
	char buff[100][100];

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			fscanf(fp, "%c ", &buff[i][j]);
			if(!isdigit(buff[i][j])){
				sudoku[i][j] = 0;
			}
			else if(isdigit(buff[i][j])){
				sudoku[i][j] = atoi(&buff[i][j]);
			}
			//fscanf(fp, "%d ", &sudoku[i][j]);
		}
	}

	int x = 0;
	int y = 0;
	if(solve(x,y,sudoku)){
		printSudoku(sudoku);
	}

	time = clock() - time;
	double runtime = ((double)time)/CLOCKS_PER_SEC;
	printf("runtime: %f \n", runtime);
	return 0;
}
