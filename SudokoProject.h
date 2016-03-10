#ifndef __SUDOKOPROJECT_H
#define __SUDOKOPROJECT_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//consts:
#define ROWSIZE 9
#define COLUMNSIZE 9
#define SQUARSIZE 3
#define DIVIDE '|'
#define DIVIDING_LINE "-----------------------"
#define EMPTYCELL "  "
#define PLAYER_NAME 100
#define LOTTERY_RANGE 20
#define LOG_BASE 2.0
#define WINNER_LIST_FILE_NAME "winners.txt"


//structs:
typedef struct _Array
{
	short *arr;
	unsigned short size;
} Array;

typedef struct cellplace
{
	unsigned int R;
	unsigned int C;
} CellPlace;

typedef struct possible_cells_list_node
{
	CellPlace place;
	struct possible_cells_list_node* next;
	struct possible_cells_list_node* prev;
} PCListNODE;

typedef struct possible_cells_list
{
	PCListNODE* head;
	PCListNODE* tail;
	int size;
} PCList;

typedef struct player
{
	char* name;
	short board[COLUMNSIZE][ROWSIZE];
	Array*** PossibleDigits;
} Player;

typedef struct players_list_node
{
	Player* player;
	struct players_list_node* next;
	struct players_list_node* prev;
} PLAYERSListNode;

typedef struct players_list
{
	PLAYERSListNode* head;
	PLAYERSListNode* tail;
} PLAYERSList;

typedef struct treeNode{
	PLAYERSListNode* data;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

typedef struct tree{
	TreeNode *root;
}Tree;

typedef int RESULT;
#define NOT_FINISH 0
#define FINISH_SUCCESS  1
#define FINISH_FAILURE -1

typedef int RESULTFILL;
#define FAILD -1
#define FILLED  1

typedef int BOOL;
#define FALSE 0
#define TRUE  1

//functions:
Array *** PossibleDigits(short sudokuBoard[][9]);
Array *** CreatePD(short sudokuBoard[][9]);
void EXIST_IN_SQUARE(int x, int y, int* ExistDigits, short board[][9]);
void EXIST_IN_ROW(int x, int* ExistDigits, short board[][9]);
void EXIST_IN_COLUMN(int y, int* ExistDigits, short board[][9]);
void ZERO_ARRAY(int* Arr, int size);
unsigned short COUNT_POSSIBLE_DIGITS(int* Arr, int size);
void sudokoPrintBoard(short sudokuBoard[][9]);
int OneStage(short board[][9], Array ***possibilities, int *x, int *y);
void UpdatePossibleDigitsOfCell(Array* square, int row, int column, short sudokuBoard[][9]);
void swap(short* i, short* j);
void UpatePossibleDigitsInRowColumnSquare(short board[][9], Array*** PD, int x, int y);
void UpatePossibleDigitsInRow(short board[][9], Array*** PD, int x, int y);
void UpatePossibleDigitsInColumn(short board[][9], Array*** PD, int x, int y);
void UpatePossibleDigitsInSquare(short board[][9], Array*** PD, int x, int y);
BOOL CheckIfExistInArray(Array* arr, int num);
void PrintPossibleDigitsArray(Array ***possibilities, int x, int y);
void MakeEmptyBoard(short board[][COLUMNSIZE]);
unsigned int RandNumber(unsigned int range);
void makeEmptyPLAYERSList(PLAYERSList* lst);
BOOL isEmptyPLAYERSList(PLAYERSList* lst);
PLAYERSListNode* createNewPLAYERSListNode(Player* player, PLAYERSListNode* next, PLAYERSListNode* prev);
void insertPlayerToEndPLAYERSList(PLAYERSList* lst, Player* player);
void insertNodeToEndPLAYERSList(PLAYERSList* lst, PLAYERSListNode* Tail);
Player* CreateNewPlayer();
void deleteNodeFromPLAYERSList(PLAYERSList* lst, PLAYERSListNode* node);
void deleteNodeFromPLAYERSListWithoutfreePlayer(PLAYERSList* lst, PLAYERSListNode* node);
void PrintPLAYERSList(PLAYERSList* lst);
void freePLAYERSListNode(PLAYERSListNode* node);
void freePLAYERSList(PLAYERSList* lst);
char* getPlayerName();
BOOL isEmptyPCList(PCList* lst);
void makeEmptyPCList(PCList* lst);
PCListNODE* CreateNewPCListNODE(CellPlace cp, PCListNODE* next, PCListNODE* prev);
void insertCPtoEndOfPCList(PCList* lst, CellPlace cp);
void insertNodeToEndPCList(PCList* lst, PCListNODE* newTail);
PCListNODE* getPCListNode(PCList* lst, int place);
void deleteNodeFromPCList(PCList* lst, PCListNODE* node);
void freePCList(PCList* lst);
void BuildNewPCList(PCList* lst);
Array *** makeRandomBoard(short board[][9]);
void CopyPLAYERSListNODEpointersFromListToArray(PLAYERSList* lst, PLAYERSListNode** Arr, int size);
int getFilledCellsNumOfPlayer(PLAYERSListNode* Player);
int* CreateFilledCellsNumOfPlayerArray(PLAYERSListNode** Arr, int size);
void mergesort(PLAYERSListNode** pointers, int first, int last);
void merge(PLAYERSListNode** pointers, int first, int last, int middle);
double CalculateLogBase2(double x);
PLAYERSListNode** ExpandActive_Arr(PLAYERSListNode** Active_Arr, int* x);
TreeNode* CreateNewTreeNode(PLAYERSListNode* data, TreeNode* left, TreeNode* right);
void CheckTreeNodeAllocation(TreeNode* node);
Tree BuildTreeFromArray(PLAYERSListNode** arr, int size);
TreeNode* BuildTreeFromArrayHelper(PLAYERSListNode** arr, int first, int last);
void freeTree(Tree tr);
void freeTreeHelper(TreeNode * root);
void Round(Tree* tr, PLAYERSList *ActiveList, PLAYERSList *WinnersList);
void RoundHelper(TreeNode* root, PLAYERSList *ActiveList, PLAYERSList *WinnersList);
void PlayerFillBoard(PLAYERSListNode* Player, int x, int y);
void CheckPlayerListAllocation(PLAYERSList* lst);
void CheckPlayerListNodeAllocation(PLAYERSListNode* node);
void CheckArrayAllocation(Array* arr);
void CheckShortAllocation(short* arr);
void CheckActiveArrAllocation(PLAYERSListNode** arr);
void CheckStringAllocation(char* str);
void CheckPCListNodeAllocation(PCListNODE* node);
void CheckPlayerAllocation(Player* pl);
void PrintPLAYERSListToFile(PLAYERSList* lst);
void sudokoPrintBoardToFile(FILE* fp, short sudokuBoard[][9]);
void FreePD(Array*** PD);

#endif