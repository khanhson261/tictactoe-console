#include "stdafx.h"
//2 Players
//Support function for playing 2 players
void gotoxy(int x, int y);
int Change_x(int x);
int Change_y(int y);
void Creat_New_Table(int n);
void Creat_Background_Function(char background[][100], struct ROW &row, struct CONDITION &condition);
void Creat_Help_Function(char Help[][1000], struct ROW &row, struct CONDITION &condition);
void Creat_Used_Table_Function(int a[100][100], int n, int &player, struct ROW &row, struct CONDITION &condition);
void SetColor(int color);
bool Check_Row(int a[100][100], int n, int i);
bool Check_Column(int a[100][100], int n, int j);
bool Check_Diagonal_1_Up(int a[100][100], int n, int i);
bool Check_Diagonal_1_Down(int a[100][100], int n, int j);
bool Check_Diagonal_2_Up(int a[100][100], int n, int j);
bool Check_Diagonal_2_Down(int a[100][100], int n, int i);
bool Check_Win(int a[100][100], int n);
//Main Function for playing with 2 players
void playgame(int Check_Table[100][100], int n,int &player, struct ROW &row, struct CONDITION &condition);





//Player vs NPC
//Support function for playing player vs NPC
int Change_from_j_to_x(int j);
int Change_from_i_to_y(int i);
//function for checking the win PLAYER (in NPC vs PLAYER)
//For Row
bool Check_Row_2_steps(int a[100][100], int n, int i);
//For Column
bool Check_Column_2_steps(int a[100][100], int n, int j);
//For Diagonal 1
bool Check_Diagonal_1_Up_2_steps(int a[100][100], int n, int i);
bool Check_Diagonal_1_Down_2_steps(int a[100][100], int n, int j);
//For Diagonal 2
bool Check_Diagonal_2_Up_2_steps(int a[100][100], int n, int j);
bool Check_Diagonal_2_Down_2_steps(int a[100][100], int n, int i);
//Check Win
bool Check_Win_2_steps(int a[100][100], int n);

//function for checking 4 steps of NPC (in NPC vs PLAYER)
//For Row
bool Check_Row_Main_NPC_2_steps(int a[100][100], int n, int i, int & CASE);
//For Column
bool Check_Column_Main_NPC_2_steps(int a[100][100], int n, int j, int & CASE);
//For Diagonal 1
bool Check_Diagonal_1_Up_Main_NPC_2_steps(int a[100][100], int n, int i, int & CASE);
bool Check_Diagonal_1_Down_Main_NPC_2_steps(int a[100][100], int n, int j, int & CASE);
//For Diagonal 2
bool Check_Diagonal_2_Up_Main_NPC_2_steps(int a[100][100], int n, int j, int & CASE);
bool Check_Diagonal_2_Down_Main_NPC_2_steps(int a[100][100], int n, int i, int &CASE);
//Check Win
bool Check_Win_Main_NPC_2_steps(int a[100][100], int n, int &CASE);

//function for checking 3 steps of NPC (in NPC vs PLAYER)
//For Row
bool Check_Row_Main_NPC_3_steps(int a[100][100], int n, int i, int & CASE);
//For Column
bool Check_Column_Main_NPC_3_steps(int a[100][100], int n, int j, int & CASE);
//For Diagonal 1
bool Check_Diagonal_1_Up_Main_NPC_3_steps(int a[100][100], int n, int i, int & CASE);
bool Check_Diagonal_1_Down_Main_NPC_3_steps(int a[100][100], int n, int j, int & CASE);
//For Diagonal 2
bool Check_Diagonal_2_Up_Main_NPC_3_steps(int a[100][100], int n, int j, int & CASE);
bool Check_Diagonal_2_Down_Main_NPC_3_steps(int a[100][100], int n, int i, int &CASE);
//Check Win
bool Check_Win_Main_NPC_3_steps(int a[100][100], int n, int &CASE);

//function for checking NPC with 2 steps more (in NPC vs PLAYER)
//For Row
bool Check_Row_NPC_2_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Column
bool Check_Column_NPC_2_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Diagonal 1
bool Check_Diagonal_1_Up_NPC_2_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
bool Check_Diagonal_1_Down_NPC_2_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Diagonal 2
bool Check_Diagonal_2_Up_NPC_2_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
bool Check_Diagonal_2_Down_NPC_2_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
	//Check Win
bool Check_Win_NPC_2_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);

//function for checking NPC with 3 steps more (in NPC vs PLAYER)
//For Row
bool Check_Row_NPC_3_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Column
bool Check_Column_NPC_3_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Diagonal 1
bool Check_Diagonal_1_Up_NPC_3_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
bool Check_Diagonal_1_Down_NPC_3_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Diagonal 2
bool Check_Diagonal_2_Up_NPC_3_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
bool Check_Diagonal_2_Down_NPC_3_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//Check Win
bool Check_Win_NPC_3_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);

//function for checking NPC with 4 steps more (in NPC vs PLAYER)
//For Row
bool Check_Row_NPC_4_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Column
bool Check_Column_NPC_4_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Diagonal 1
bool Check_Diagonal_1_Up_NPC_4_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
bool Check_Diagonal_1_Down_NPC_4_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//For Diagonal 2
bool Check_Diagonal_2_Up_NPC_4_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
bool Check_Diagonal_2_Down_NPC_4_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);
//Check Win
bool Check_Win_NPC_4_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position);

//Center Function
bool Check_Win_NPC_1_step(int a[100][100], int n, int &i_position, int &j_position);
bool Check_Win_Player_1_step(int a[100][100], int n, int &i_position, int &j_position);
bool Check_Win_Player_2_steps(int a[100][100], int n, int &i_position, int &j_position, int &k_position, int &l_position);
bool Check_NPC_4_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position);
bool Check_NPC_3_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position);

//Main Function for playing with player vs NPC
void NPC_turn(int a[100][100], int n);
void playgame_NPC(int Check_Table[100][100], int n, int player_first_turn, struct ROW &row, struct CONDITION &condition);

//Function Node
//Support Function
char* Get_Time(char* result);
void ShowFileName();
void InputString(char str[]);
//Main Function
void SaveGame(int n, int check[100][100]);
void LoadGame(char * FileName, int  Check_Table[100][100],int &player);
void f2_Node(int Check_Table[][100], int n,int &x,int &y);