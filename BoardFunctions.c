#include "SudokoProject.h"

//input: sudoko board.
//This funcion make and return an Array of all the possible digits of each square.
Array ***PossibleDigits(short sudokuBoard[][9])
{
	int i, j; //for index.
	Array *** PD; //the array.
	PD = CreatePD(sudokuBoard); //create the PossibleDigits array.
	for (i = 0; i < COLUMNSIZE; i++) //for all the squares.
	{
		for (j = 0; j < ROWSIZE; j++)
		{
			if (sudokuBoard[i][j] == -1) //if the square doesnt filled yet.
			{
				UpdatePossibleDigitsOfCell(PD[i][j], i, j, sudokuBoard); //update possible digits of this square.
			}
		}
	}
	return PD;
}

//This function Create Possible Digits array.
Array *** CreatePD(short sudokuBoard[][9])
{
	Array *** PD; //the Possible Digits array.
	int i, j; //for index.
	PD = (Array***)malloc(COLUMNSIZE * sizeof (Array **)); //allocate PD.
	if (PD == NULL) //check allocation.
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
	for (i = 0; i < COLUMNSIZE; i++) //allocate each line in PD.
	{
		PD[i] = (Array**)malloc(ROWSIZE * sizeof(Array*));
		if (PD[i] == NULL) //check allocation.
		{
			printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
			exit(1);
		}

		for (j = 0; j < ROWSIZE; j++) //allocate each cell in PD.
		{
			if (sudokuBoard[i][j] == -1) //if this is empty square allocate it.
			{
				PD[i][j] = (Array*)malloc(sizeof(Array));
				if (PD[i][j] == NULL) //check allocation.
				{
					printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
					exit(1);
				}
			}
			else //if this is not empty square put NULL.
			{
				PD[i][j] = NULL;
			}
		}
	}
	return PD;
}
//input: number of row, number of column, array of ints, and sudoko board.
//This function mark the numbers that in the square of the point.
void EXIST_IN_SQUARE(int x, int y, int* ExistDigits, short board[][9])
{
	int i, j; //for index.
	for (i = x - (x % SQUARSIZE); i < x - (x % SQUARSIZE) + SQUARSIZE; i++) //for all the rows of the square.
	{
		for (j = y - (y % SQUARSIZE); j < y - (y % SQUARSIZE) + SQUARSIZE; j++)// for all the columns in the sqaure.
		{
			if ((board[i][j] - 1) != -1 && ExistDigits[board[i][j] - 1] == 0) //if theres is any number, and it didnt marked yet, mark it.
				ExistDigits[board[i][j] - 1]++;
		}
	}
}
//input: number of row, array of ints, and sudoko board.
//This function mark the digits that in the row of the cell.
void EXIST_IN_ROW(int x, int* ExistDigits, short board[][9])
{
	int i; //for index;
	for (i = 0; i < ROWSIZE; i++) //for all the numbers in the row.
	{
		if (board[x][i] != -1 && ExistDigits[board[x][i] - 1] == 0)//if theres is any number, and it didnt marked yet, mark it.
			ExistDigits[board[x][i] - 1]++;
	}
}

//input: number of column, array of ints, and sudoko board.
//This function mark the digits that in the column of the cell.
void EXIST_IN_COLUMN(int y, int* ExistDigits, short board[][9])
{
	int i; //for index
	for (i = 0; i < COLUMNSIZE; i++) //for all the numbers in  the column. 
	{
		if (board[i][y] != -1 && ExistDigits[board[i][y] - 1] == 0) //if there is any number, and it didnt marked yet, mark it.
			ExistDigits[board[i][y] - 1]++;
	}
}

//input: Array of ints and his size.
//this function zero the array.
void ZERO_ARRAY(int* Arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		Arr[i] = 0;
}

//input: Array of ints and his size.
//this function return the number of the digits that didnt marked in the array.
unsigned short COUNT_POSSIBLE_DIGITS(int* Arr, int size)
{
	unsigned short count = 0; //for count.
	int i; //for index.
	for (i = 0; i < size; i++)
	{
		if (Arr[i] != 1) //if this number didnt marked count it.
			count++;
	}
	return count;
}

//input: cell, his row, his column, sudoko board.
//this function update in cell array all his possible digits and update cell array size.
void UpdatePossibleDigitsOfCell(Array* cell, int row, int column, short sudokuBoard[][9])
{
	int i; //for index.
	int IndOfArr; //for index.
	int ExistDigits[COLUMNSIZE]; //for mark the digits that exist.
	ZERO_ARRAY(ExistDigits, COLUMNSIZE); //zero the exist digits array.
	EXIST_IN_SQUARE(row, column, ExistDigits, sudokuBoard); //mark all the digits in the sqaure.
	EXIST_IN_ROW(row, ExistDigits, sudokuBoard); //mark all the digits in the row.
	EXIST_IN_COLUMN(column, ExistDigits, sudokuBoard); //mark all the digits in the column.
	cell->size = COUNT_POSSIBLE_DIGITS(ExistDigits, COLUMNSIZE); //insert to cell size the number of the digits that doesnt marked. 
	cell->arr = (short*)malloc(cell->size * sizeof (short)); //create cell possible digits array.
	CheckShortAllocation(cell->arr); //check allocation.
	IndOfArr = 0; //zero the index of the array.
	for (i = 0; i < ROWSIZE; i++) //for all the digits.
	{
		if (ExistDigits[i] != 1) //if the digit doesnt exist.
		{
			cell->arr[IndOfArr] = i + 1; //insert it to square arr.
			IndOfArr++; //add 1 to the index.
		}
	}
}

//input: board, possible digits array, row, column.
//this function update the possible digits of all the row,column and square of the cell (x,y).
void UpatePossibleDigitsInRowColumnSquare(short board[][9], Array*** PD, int x, int y)
{
	UpatePossibleDigitsInRow(board, PD, x, y); //update the row.
	UpatePossibleDigitsInColumn(board, PD, x, y); //update the column.
	UpatePossibleDigitsInSquare(board, PD, x, y); //update the square.
}

//input: board, possible digits array, row, column.
//this function update the possible digits of all the row of the cell (x,y).
void UpatePossibleDigitsInRow(short board[][9], Array*** PD, int x, int y)
{
	int i, j; //for index.
	BOOL checkifexist; //to know if the digit that enterd is exist in possible digits array of the cell.
	for (i = 0; i < ROWSIZE; i++) //for all the squares in the line.
	{
		if (board[x][i] == -1) //if the cell is empty.
		{
			checkifexist = CheckIfExistInArray(PD[x][i], board[x][y]); //check if the digit exist.
			if (checkifexist == TRUE) //if yes
			{
				PD[x][i]->size--; //minus 1 from size.
				for (j = 0; j < PD[x][i]->size; j++) //put the digit in the end of the array.
				{
					if (PD[x][i]->arr[j] == board[x][y])
						swap(&PD[x][i]->arr[j], &PD[x][i]->arr[j + 1]);
				}
				PD[x][i]->arr = realloc((short*)PD[x][i]->arr, PD[x][i]->size * sizeof(short)); //realloc the array to his new size.
				if (PD[x][i]->size > 0) //if the size isn't 0 check allocation.
				{
					CheckShortAllocation(PD[x][i]->arr); //check allocation.
				}
			}
		}
	}
}

//input: board, possible digits array, row, column.
//this function update the possible digits of all the column of the cell (x,y).
void UpatePossibleDigitsInColumn(short board[][9], Array*** PD, int x, int y)
{
	int i, j; //for index.
	BOOL checkifexist; //to know if the digit that enterd is exist in possible digits array of the cell.
	for (i = 0; i < COLUMNSIZE; i++) //for all the cells in the column.
	{
		if (board[i][y] == -1) //if the cell is empty.
		{
			checkifexist = CheckIfExistInArray(PD[i][y], board[x][y]); //check if the digit exist.
			if (checkifexist == TRUE) //if yes
			{
				PD[i][y]->size--; //minus 1 from size.
				for (j = 0; j < PD[i][y]->size; j++) //put the digit in the end of the array.
				{
					if (PD[i][y]->arr[j] == board[x][y])
						swap(&PD[i][y]->arr[j], &PD[i][y]->arr[j + 1]);
				}
				PD[i][y]->arr = realloc((short*)PD[i][y]->arr, PD[i][y]->size * sizeof(short)); //realloc the array to his new size.
				if (PD[i][y]->size > 0) //if the size isn't 0 check allocation.
				{
					CheckShortAllocation(PD[i][y]->arr);
				}
			}
		}
	}
}

//input: board, possible digits array, row, column.
//this function update the possible digits of all the cells in the sqaure of the cell (x,y).
void UpatePossibleDigitsInSquare(short board[][9], Array*** PD, int x, int y)
{
	int i, j, k; //for index
	BOOL checkifexist; //to know if the digit that enterd exist in possible digits array of the cell.
	for (i = x - (x % SQUARSIZE); i < x - (x % SQUARSIZE) + SQUARSIZE; i++) //for all the rows of the square.
	{
		for (j = y - (y % SQUARSIZE); j < y - (y % SQUARSIZE) + SQUARSIZE; j++)// for all the columns of the sqaure.
		{
			if (board[i][j] == -1) //if the cell is empty.
			{
				checkifexist = CheckIfExistInArray(PD[i][j], board[x][y]); //check if the digit exist.
				if (checkifexist == TRUE) //if yes
				{
					PD[i][j]->size--; //minus 1 from square size.
					for (k = 0; k < PD[i][j]->size; k++) //put the digit in the end of the array.
					{
						if (PD[i][j]->arr[k] == board[x][y])
							swap(&PD[i][j]->arr[k], &PD[i][j]->arr[k + 1]);
					}
					PD[i][j]->arr = realloc((short*)PD[i][j]->arr, PD[i][j]->size * sizeof(short)); //realloc the array to his new size.
					if (PD[i][j]->size > 0)//if the size isn't 0 check allcoation
					{
						CheckShortAllocation(PD[i][j]->arr);
					}
				}
			}
		}
	}
}

//input: board.
//this function make this board empty (filling all his cells with -1).
void MakeEmptyBoard(short board[][COLUMNSIZE])
{
	int i, j;
	for (i = 0; i < COLUMNSIZE; i++)
	{
		for (j = 0; j < ROWSIZE; j++)
			board[i][j] = -1;
	}
}

//input: empty sudoko board.
//this function get empty sudoko board and make him random.
//return: the possible digits array of this board.
Array *** makeRandomBoard(short board[][9])
{
	PCList PCList; //Possible Cells List.
	PCListNODE* curr;
	Array*** possible_solutions; //for possibble digits.
	possible_solutions = PossibleDigits(board); //get possibble digits of board.
	makeEmptyPCList(&PCList); //make the list empty.
	BuildNewPCList(&PCList); //build the possible digits list.
	int i; // for index.
	int N; //for the number of the cells that start with value.
	int K; //for the number of the cell that will be delete.
	int M; //for lottery the index of the possible digits array.
	N = RandNumber(20); //lottery number between 1-20.
	for (i = 0; i < N; i++) //do it N times.
	{
		K = RandNumber(PCList.size); //lottery the number of the cell that will be filled.
		curr = getPCListNode(&PCList, K - 1); //get this cell. (K-1 because the numbers of the cells is between 0 to 80-i).
		M = RandNumber(possible_solutions[curr->place.R][curr->place.C]->size) - 1; // lottery the place of the possible digit of the cell.
		board[curr->place.R][curr->place.C] = possible_solutions[curr->place.R][curr->place.C]->arr[M]; //fill the cell with the possible digit.
		UpatePossibleDigitsInRowColumnSquare(board, possible_solutions, curr->place.R, curr->place.C);//update possible digits of the row, column and square of this cell.
		deleteNodeFromPCList(&PCList, curr); //delete this cell from PCList.
	}
	freePCList(&PCList); //free the pc list.
	return possible_solutions;
}

//input: open file, sudoku board.
//this function print this sudoku board into this file.
void sudokoPrintBoardToFile(FILE* fp, short sudokuBoard[][9])
{
	int i, j; //for index.
	fprintf(fp, "\n\n%3c", DIVIDE); //down tow lines and print divide of the numbers of the columns.
	for (i = 0; i < ROWSIZE; i++) //print all the columns numbers.
	{
		fprintf(fp, "%2d", i); //print the number of the column.
		if (i%SQUARSIZE == 2 && i != COLUMNSIZE - 1) //add DIVIDE between each 3 columns numbers.
			fprintf(fp, "%c", DIVIDE);
	}
	fprintf(fp, "\n"); //end line.
	fprintf(fp, "%s\n", DIVIDING_LINE); //print dividing line.
	for (i = 0; i < 9; i++) //for all the rows
	{
		fprintf(fp, "%2d%c", i, DIVIDE); //print number of row.
		for (j = 0; j < 9; j++) //print all the numbers in this row.
		{
			if (sudokuBoard[i][j] != -1) //if the cell isnt empty, print his value.
				fprintf(fp, "%2d", sudokuBoard[i][j]);
			else //else print empty cell.
				fprintf(fp, "%s", EMPTYCELL);
			if (j%SQUARSIZE == 2 && j != COLUMNSIZE - 1) //if its the end of the square, and this not the last sqaure.
				fprintf(fp, "%c", DIVIDE); //print DIVIDE
		}
		fprintf(fp, "\n"); //end line.
		if (i%SQUARSIZE == 2 && i != COLUMNSIZE - 1) //if its the end of the square, and this not the last sqaure.
			fprintf(fp, "%s\n", DIVIDING_LINE); //print DIVIDING_LINE.
	}
	fprintf(fp, "%s\n\n\n", DIVIDING_LINE); //print DIVIDING_LINE in the end of the board.
}

//input: sudoku board.
//output: this function print suduko board.
void sudokoPrintBoard(short sudokuBoard[][9])
{
	int i, j; //for index.
	printf("\n\n%3c", DIVIDE); //down tow lines and print divide of the numbers of the columns.
	for (i = 0; i < ROWSIZE; i++) //print all the columns numbers.
	{
		printf("%2d", i); //print the number of the column.
		if (i%SQUARSIZE == 2 && i != COLUMNSIZE - 1) //add DIVIDE between each 3 columns numbers.
			printf("%c", DIVIDE);
	}
	printf("\n"); //end line.
	printf("%s\n", DIVIDING_LINE); //print dividing line.
	for (i = 0; i < 9; i++) //for all the rows
	{
		printf("%2d%c", i, DIVIDE); //print number of row.
		for (j = 0; j < 9; j++) //print all the numbers in this row.
		{
			if (sudokuBoard[i][j] != -1) //if the cell isnt empty, print his value.
				printf("%2d", sudokuBoard[i][j]);
			else //else print empty cell.
				printf("%s", EMPTYCELL);
			if (j%SQUARSIZE == 2 && j != COLUMNSIZE - 1) //if its the end of the square, and this not the last sqaure.
				printf("%c", DIVIDE); //print DIVIDE
		}
		printf("\n"); //end line.
		if (i%SQUARSIZE == 2 && i != COLUMNSIZE - 1) //if its the end of the square, and this not the last sqaure.
			printf("%s\n", DIVIDING_LINE); //print DIVIDING_LINE.
	}
	printf("%s\n\n\n", DIVIDING_LINE); //print DIVIDING_LINE in the end of the board.
}