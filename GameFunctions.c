#include "SudokoProject.h"

//input: sudoko board, possibilites digits array, x and y.
//this function filled all the cells that have just 1 posiible digit, put in x and y the cell with the minimum possibilities, and check if there is duplications.
int OneStage(short board[][9], Array ***possibilities, int *x, int *y)
{
	BOOL check = TRUE; //to know if there is any cell with just 1 possible digit.
	RESULT res = FINISH_SUCCESS; //for the result.
	int min; //for the minimum size. 
	int i, j; //for index.
	while (check == TRUE && res != FINISH_FAILURE) //while there is any cell with just 1 possible digit, and thereisnt duplications.
	{
		check = FALSE; //put false in check.
		min = ROWSIZE; //start with the max size that possible
		res = FINISH_SUCCESS; //put FINISH_SUCCESS in res.
		for (i = 0; i < COLUMNSIZE; i++) //for all the cells.
		{
			for (j = 0; j < ROWSIZE; j++)
			{
				if (board[i][j] == -1) //if the cell is empty.
				{
					if (possibilities[i][j]->size > 1 && min > possibilities[i][j]->size) //if the size of possible digits of this cell is bigger than 1 and smaller from min.
					{
						res = NOT_FINISH; //update res to NOT_FINISH.
						min = possibilities[i][j]->size; //update min.
						*(x) = i; //update x.
						*(y) = j; //update y.
					}
					else if (possibilities[i][j]->size == 1) //else, if the possible digits size is 1.
					{
						check = TRUE; //put TRUE in check.
						board[i][j] = possibilities[i][j]->arr[0]; //update the board with the digit.
						free(possibilities[i][j]->arr); //free this possible digits arr of this cell.
						free(possibilities[i][j]); //free this possible digits of this cell.
						possibilities[i][j] = NULL; //put NULL in this possible digits of this cell.
						UpatePossibleDigitsInRowColumnSquare(board, possibilities, i, j); //update the row, column and square of this cell.
					}
					else if (possibilities[i][j]->size == 0) //if this is empty cell with no possible digits, there is duplication.
					{
						res = FINISH_FAILURE; //put FINISH_FAILURE in res.
						return res;
					}
				}
			}
		}
	}
	return res;
}

//input: pointers of tow ints.
//this program swap between the arguments value.
void swap(short* i, short* j)
{
	int temp;
	temp = *(i);
	*(i) = *(j);
	*(j) = temp;
}

//input: cell, a number.
//return: True if the number exist in the possible digits array of cell, FALSE otherwise.  
BOOL CheckIfExistInArray(Array* cell, int num)
{
	BOOL res = FALSE;
	int i;
	for (i = 0; i < cell->size; i++)
	{
		if (cell->arr[i] == num)
			res = TRUE;
	}
	return res;
}

//input: possibilities array, x and y.
//output: the possible digits of the cell (x,y).
void PrintPossibleDigitsArray(Array ***possibilities, int x, int y)
{
	int i; //for index.
	int size; //for the size of the array.
	if (possibilities[x][y] != NULL) //if this cell is empty.
	{
		size = possibilities[x][y]->size; //insert his size to size.
		for (i = 0; i < size; i++) //print all the values in his array.
		{
			printf("%d. %d\n", i + 1, possibilities[x][y]->arr[i]);
		}
	}
	else //else print error.
		printf("This is not empty cell!");
}

//input: range.
//return: lottery number between 1 to range.
unsigned int RandNumber(unsigned int range)
{
	int res;
	res = 1 + rand() % range;
	return res;
}

//this function get player name from user.
char* getPlayerName()
{
	char* name; //for the name.
	char ch; //for any char.
	int len = 0; //for the length of the name.
	name = (char*)malloc(PLAYER_NAME*sizeof(char)); //allocate name.
	CheckStringAllocation(name); //check allocation.
	ch = getchar(); //get char from user.
	while (ch != '\n' && len < PLAYER_NAME) //while ch isn't '\n' and len is smaller than PLAYER_NAME.
	{
		name[len] = ch; //add ch to his place.
		len++; //add 1 to len.
		ch = getchar(); //get another char form user.
	}
	name[len] = '\0'; //insert '\0' in the end.
	len++; //add 1 to len.
	name = realloc(name, len*sizeof(char)); //realloc name to his actual size.
	CheckStringAllocation(name); //check allocation.
	return name;
}

//this function create new player.
Player* CreateNewPlayer()
{
	Player* res; //the new player.
	res = (Player*)malloc(sizeof(Player)); //allocate the new player.
	CheckPlayerAllocation(res); //check allocation.
	res->name = getPlayerName(); //get the player name.
	MakeEmptyBoard(res->board); //make empty the player board.
	res->PossibleDigits = makeRandomBoard(res->board); //make random board for this player and get the possible digits array of this board.
	return res; //return the player.
}

//input: pointers of: players list, Array of pointers of players list node. and the size of the Array.
//this function copy all the pointers of the nodes in the list to Array.
void CopyPLAYERSListNODEpointersFromListToArray(PLAYERSList* lst, PLAYERSListNode** Arr, int size)
{
	PLAYERSListNode* curr;
	int i = 0;
	curr = lst->head;
	while (curr != NULL && size > i)
	{
		Arr[i] = curr;
		i++;
		curr = curr->next;
	}
}

//input: pointer of player.
//this function return the filled cells number of the player's board.
int getFilledCellsNumOfPlayer(PLAYERSListNode* Player)
{
	int i, j; //for index.
	int res = 0; //for result.
	for (i = 0; i < COLUMNSIZE; i++) //for all the cells in the board.
	{
		for (j = 0; j < ROWSIZE; j++)
		{
			if (Player->player->board[i][j] != -1) //if the cell isn't empty.
				res++; //add 1 to res.
		}
	}
	return res;
}

//input: pointer of Array of pointers of players node, and his size.
//this function create and return Array of all the filled cells number of all the nodes in this Array.
int* CreateFilledCellsNumOfPlayerArray(PLAYERSListNode** Arr, int size)
{
	int* res; //for the result.
	int i; //for index.
	if (size == 0) //if the array is empty return NULL.
		return NULL;
	else
	{
		res = (int*)malloc(size * sizeof (int)); //allocate res.
		if (res == NULL) //check allocation.
		{
			printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
			exit(1);
		}
		for (i = 0; i < size; i++) //for all the pointers of players in this array.
		{
			res[i] = getFilledCellsNumOfPlayer(Arr[i]); //get their filled cells number.
		}
	}
	return res;
}

//input: array of pointers, first index, last index.
//this function split the array to smallest groups of pointers, sort each group and between them.
void mergesort(PLAYERSListNode** pointers, int first, int last)
{
	if (first < last) //if there is more than 1 pointer in the array.
	{
		int middle = (first + last) / 2; //the middle of the array.
		mergesort(pointers, first, middle); //call the function again with first halve of the array.
		mergesort(pointers, middle + 1, last); //call the function again with second havle of the array.
		merge(pointers, first, last, middle); //merge.
	}
}

//input: array of pointers of playerslistnode, the first index, the last index, the middle index.
// this function split arr to tow, and sort them by the number of filled cells or (if they have the same number of filled cells) by thier names.
void merge(PLAYERSListNode** pointers, int first, int last, int middle)
{
	PLAYERSListNode** firsthalve; //for first havle.
	PLAYERSListNode** secondhalve; //for second halve.
	int *firstFilledCellsNum, *secondFilledCellsNum; //in these arrayes will be the number of filled cells of any pointer in the halves.
	int num1; //the size of first havle array.
	int num2; // the size of second halve array.
	int i, j, k; //for index.

	//split pointers to tow arrays.
	num1 = (middle - first) + 1; //the size of the first havle is middle - first + 1.
	num2 = last - middle; //the size of the second halve is last - middle.
	firsthalve = (PLAYERSListNode**)malloc(num1 * sizeof(PLAYERSListNode*)); //allocation first havle.
	CheckActiveArrAllocation(firsthalve); //check allocation.
	secondhalve = (PLAYERSListNode**)malloc(num2 * sizeof (PLAYERSListNode*)); // allocation second havle.
	CheckActiveArrAllocation(secondhalve); //check allocation.
	for (i = 0; i < num1; i++) //copy pointers from pointers to first halve.
		firsthalve[i] = pointers[i + first];
	for (j = 0; j < num2; j++) //copy pointers from pointers to second halve.
		secondhalve[j] = pointers[j + middle + 1];

	//get number of filled cells of any pointer in any halve
	firstFilledCellsNum = CreateFilledCellsNumOfPlayerArray(firsthalve, num1);
	secondFilledCellsNum = CreateFilledCellsNumOfPlayerArray(secondhalve, num2);

	//sort firsthavle and secondhalve to pointers.
	i = 0; //index of first havle.
	j = 0; //index of second halve.
	k = first; //index of pointers.
	while (i < num1 && j < num2) //while there is pointers in the tow arrays.
	{
		if (firstFilledCellsNum[i] > secondFilledCellsNum[j]) //if the number of filled cells of the pointer in first halve is bigger.
		{
			pointers[k] = firsthalve[i]; //insert it to pointers.
			i++; //add 1 to firsthalve index.
		}
		else if (secondFilledCellsNum[j] > firstFilledCellsNum[i]) //if the number of filled cells of the pointer in second halve is bigger.
		{
			pointers[k] = secondhalve[j]; //insert secondhalve pointer value to pointers.
			j++; //add 1 to secondhalve index.
		}
		else if (strcmp(firsthalve[i]->player->name, secondhalve[j]->player->name) > 0) //if they have the same number of filled cells, sort by the name.
		{
			pointers[k] = firsthalve[i]; //insert it to pointers.
			i++; //add 1 to firsthalve index.
		}
		else
		{
			pointers[k] = secondhalve[j]; //insert secondhalve pointer value to pointers.
			j++; //add 1 to secondhalve index.
		}
		k++; // add 1 to pointers index.
	}
	while (i < num1) //if there is still pointers in firsthalve, insert them to pointers.
	{
		pointers[k] = firsthalve[i];
		i++;
		k++;
	}
	while (j < num2) //if there is still pointers in secondhalve, insert them to pointers.
	{
		pointers[k] = secondhalve[j];
		j++;
		k++;
	}

	//free allocations.
	free(firstFilledCellsNum);
	free(secondFilledCellsNum);
	free(firsthalve);
	free(secondhalve);
}

//input: x (double).
//return: log Base2 of x.
double CalculateLogBase2(double x)
{
	double res;
	res = log(x) / log(LOG_BASE); //log base 2 of x = (log base e of x) / (log base e of 2).
	return res;
}

//input: Active_Arr, pointer of x (the number of the players).
//this function expand Active_Arr and update x to the new size of Active_Arr.
PLAYERSListNode** ExpandActive_Arr(PLAYERSListNode** Active_Arr, int* x)
{
	int i; //for index.
	int n; //for the new size of Active_Arr.
	double logBase2; //for the log Base 2 calculation.
	logBase2 = (CalculateLogBase2((double)(*(x)+1))); //calculate log base 2 of x+1.
	n = (int)logBase2; //n is the integer value of logBase2.
	if (logBase2 > n) //if logBase2 is bigger than n, add 1 to n. (we are looking for the top value of logBase2).
		n++;
	n = (int)(pow(2.0, (double)n) - 1); //calculate the new size of Active_Arr (2^(logBase2(x+1) - 1 ).
	Active_Arr = (PLAYERSListNode**)realloc(Active_Arr, n * sizeof (PLAYERSListNode*)); //realloc Active_Arr to his new Size.
	CheckActiveArrAllocation(Active_Arr); //check allocation.
	for (i = *(x); i < n; i++) //put NULL in all the new cells in the array. 
	{
		Active_Arr[i] = NULL;
	}
	*(x) = n;
	return Active_Arr;
}

//input: Pointers of: Tree, ActiveList, WinnersList.
//this function call to RoundHelper with the root of the Tree.
void Round(Tree* tr, PLAYERSList *ActiveList, PLAYERSList *WinnersList)
{
	RoundHelper(tr->root, ActiveList, WinnersList);
}

//input: Pointers of: TreeNode, ActiveList, WinnersList.
//this function run on the Tree InOrder, and execute OneStage for each player.
void RoundHelper(TreeNode* root, PLAYERSList *ActiveList, PLAYERSList *WinnersList)
{
	int x, y; //for coordinate.
	RESULT res; //for result from OneStage.
	if (root == NULL) //if the tree is emtpy return.
		return;
	else
	{
		RoundHelper(root->left, ActiveList, WinnersList); //go to the left side of the tree.
		if (root->data != NULL)
		{
			res = OneStage(root->data->player->board, root->data->player->PossibleDigits, &x, &y); //execute OneStage for this player.
			if (res == FINISH_FAILURE) //if the result is FINISH_FAILURE, remove player from active list, and from the active tree.
			{
				printf("%s Lost the Game!\nBye Bye!\n", root->data->player->name);
				deleteNodeFromPLAYERSList(ActiveList, root->data);
				root->data = NULL;
			}
			else if (res == FINISH_SUCCESS) //if res is FINISH_SUCCESS, insert player to winner list, remove him from active list and tree active.
			{
				printf("Congratulations!\n%s Succeed to fill the board!\n", root->data->player->name);
				insertPlayerToEndPLAYERSList(WinnersList, root->data->player);
				deleteNodeFromPLAYERSListWithoutfreePlayer(ActiveList, root->data); //delete the player from ActiveList but don't free Player.
				root->data = NULL;
			}
			else if (res == NOT_FINISH) //if res is NOT_FINISH, allow player to fill 1 cell (with the minimum possible digits (coordinate from one stage)).
			{
				printf("%s Board: \n", root->data->player->name);
				sudokoPrintBoard(root->data->player->board);
				PlayerFillBoard(root->data, x, y);
			}
		}
		RoundHelper(root->right, ActiveList, WinnersList); //go to the right side of the tree.
	}
}

//input: pointer of PlayerListNode, coordinate (x and y).
//this function shows to user all his possible digits for this coordinate, get the digit that the user chose, filling his board, and update possible digits.
void PlayerFillBoard(PLAYERSListNode* Player, int x, int y)
{
	int getNum; //input by user.
	printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);
	PrintPossibleDigitsArray(Player->player->PossibleDigits, x, y); //print possible digits of the cell with the minimum possible digits.
	scanf("%d", &getNum); //insert the chose getNum.
	Player->player->board[x][y] = getNum; //update the sudoko board.
	printf("Updating cell %d with value %d\n\n", (x*ROWSIZE + y), getNum); //print message that the suduko board updated.
	UpatePossibleDigitsInRowColumnSquare(Player->player->board, Player->player->PossibleDigits, x, y); //update the possible digits of row, column and square of this cell.
}

//this function check allocation of short.
void CheckShortAllocation(short* arr)
{
	if (arr == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}

//this function check allocation of ARRAY.
void CheckArrayAllocation(Array* arr)
{
	if (arr == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}

//this function check allocation of PLAYERSListNode array.
void CheckActiveArrAllocation(PLAYERSListNode** arr)
{
	if (arr == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}

//this functuin check allocation of strings.
void CheckStringAllocation(char* str)
{
	if (str == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}

//this function check allocation of Player.
void CheckPlayerAllocation(Player* pl)
{
	if (pl == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}

//input: PossibeDigits array.
//this function free possible digits array.
void FreePD(Array*** PD)
{
	int i, j; //for indexes.
	for (i = 0; i < ROWSIZE; i++) //for all the rows.
	{
		for (j = 0; j < COLUMNSIZE; j++) //for all the columns.
		{
			free(PD[i][j]); //free his cell possible digits.
		}
		free(PD[i]); //print this row possible digits.
	}
	free(PD); //free possible digits.
}