#pragma pack (1)
#include "stdafx.h"
#include "caro_table.h"

//2 Players
//Support function for playing 2 players
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int Change_x(int x)
{
	if (x == 2)
	{
		return 0;
	}
	return Change_x(x - 4) + 1;
}
int Change_y(int y)
{
	if (y == 1)
	{
		return 0;
	}
	return Change_y(y - 2) + 1;
}
void Creat_New_Table(int n)
{
	SetColor(3);
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (i == 0 && j == 0)
			{
				printf("%c", 218);
			}
			if (i == n && j == 0)
			{
				printf("%c", 192);
			}
			if (i > 0 && i < n &&j == 0)
			{
				printf("%c", 195);
			}
			if (i == 0 && j > 0 && j < n)
			{
				printf("%c", 194);
			}
			if (i == n && j > 0 && j <n)
			{
				printf("%c", 193);
			}
			if (i > 0 && i <n && j>0 && j < n)
			{
				printf("%c", 197);
			}
			if (i == 0 && j == n)
			{
				printf("%c\n", 191);
			}

			if (i == n && j == n)
			{
				printf("%c\n", 217);
			}
			if (i > 0 && i < n&&j == n)
			{
				printf("%c\n", 180);
			}
			if (j < n)
			{
				for (int k = 0; k < 3; k++)
				{
					printf("%c", 196);
				}
			}
		}
		if (i < n)
		{
			for (int j = 0; j <= n; j++)
			{
				if (j == n)
				{
					printf("%c\n", 179);
				}
				else
				{
					printf("%c   ", 179);
				}
			}
		}
	}
}
void Creat_Background_Function(char background[][100], ROW &row, CONDITION &condition)
{
	row.Background = 1;
	for (int i = 0; i < 6; i++)
	{
		if (i == row.Background)
		{
			SetColor(112);
			printf("%s\n", background[i]);
			SetColor(7);
		}
		else
		{
			printf("%s\n", background[i]);
		}
	}

	gotoxy(0, 7);
	printf("Fast shortcut\n");
	printf("F1: Help\n");
	printf("F2: New Game with setting regime\n");
	printf("F3: Save Playing Game\n");
	printf("F4: Load Played Game\n");
	printf("F5: About Game Information\n");
	condition.Exist_Background = 0;
	condition.Exist_Table = 0;
}
void Creat_Help_Function(char Help[][1000], ROW &row, CONDITION &condition)
{
	row.Help = 7;
	row.New_Game = -1;
	for (int i = 0; i < 8; i++)
	{
		if (i == row.Help)
		{
			SetColor(112);
			printf("%s\n", Help[i]);
			SetColor(7);
		}
		else
		{
			printf("%s\n", Help[i]);
		}
	}
	condition.Exist_Background = 1;
}
void Creat_Used_Table_Function(int a[100][100], int n, int &player, ROW &row, CONDITION &condition)
{

	if (row.New_Game == 0)
	{
		SetColor(7);
		condition.Exist_Help = 1;
		playgame_NPC(a, n, 0, row , condition);
	}
	if (row.New_Game == 1) 
	{
		SetColor(7);
		condition.Exist_Help = 1;
		playgame(a, n, player, row, condition);
	}
}
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
bool Check_Row(int a[100][100], int n, int i)
{
	int fail_condition = 0;
	for (int j = 0; j < n; j++)
	{
		int temp = 0;
		int temp_1 = 0;
		int temp_2 = 0;
		if (a[i][j] != 0)
		{
			for (int k = j + 1; k <= j + 4; k++)
			{
				if (a[i][j] == a[i][k])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (a[i][j] != a[i][j - 1] && a[i][j] != a[i][j + 5])
				{
					if (j - 1 >= 0)
					{
						if (a[i][j - 1] != 0)
						{
							temp_1 = 1;
						}
					}
					if (j + 5 < n)
					{
						if (a[i][j + 5] != 0)
						{
							temp_2 = 1;
						}
					}

					if (temp_1 != temp_2 || (temp_1 == temp_2 && temp_1 == 0))
					{
						return true;
					}
				}
			}
		}
		fail_condition++;
	}
	if (fail_condition == n)
	{
		return false;
	}
}
bool Check_Column(int a[100][100], int n, int j)
{
	int fail_condition = 0;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		int temp_1 = 0;
		int temp_2 = 0;
		if (a[i][j] != 0)
		{
			for (int k = i + 1; k <= i + 4; k++)
			{
				if (a[i][j] == a[k][j])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (a[i][j] != a[i - 1][j] && a[i][j] != a[i + 5][j])
				{
					if (i - 1 >= 0)
					{
						if (a[i - 1][j] != 0)
						{
							temp_1 = 1;
						}
					}
					if (i + 5 < n)
					{
						if (a[i + 5][j] != 0)
						{
							temp_2 = 1;
						}
					}

					if (temp_1 != temp_2 || (temp_1 == temp_2 && temp_1 == 0))
					{
						return true;
					}
				}
			}
		}
		fail_condition++;
	}
	if (fail_condition == n)
	{
		return false;
	}
}
bool Check_Diagonal_1_Up(int a[100][100], int n, int i)
{
	int fail_condition = 0;
	int position = i;
	for (int j = 0; j <= position, i >= 0; j++, i--)
	{
		int temp = 0;
		int temp_1 = 0;
		int temp_2 = 0;
		if (a[i][j] != 0)
		{
			for (int k = i - 1, l = j + 1; k >= i - 4, l <= j + 4; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (a[i][j] != a[i + 1][j - 1] && a[i][j] != a[i - 5][j + 5])
				{
					if (i + 1 < n && j - 1 >= 0)
					{
						if (a[i + 1][j - 1] != 0)
						{
							temp_1 = 1;
						}
					}
					if (i - 5 >= 0 && j + 5 < n)
					{
						if (a[i - 5][j + 5] != 0)
						{
							temp_2 = 1;
						}
					}

					if (temp_1 != temp_2 || (temp_1 == temp_2 && temp_1 == 0))
					{
						return true;
					}
				}
			}
		}
		fail_condition++;
	}
	if (fail_condition == position + 1)
	{
		return false;
	}
}
bool Check_Diagonal_1_Down(int a[100][100], int n, int j)
{
	int fail_condition = 0;
	int position = j;
	for (int i = n - 1; i >= position, j <= n - 1; i--, j++)
	{
		int temp = 0;
		int temp_1 = 0;
		int temp_2 = 0;
		if (a[i][j] != 0)
		{
			for (int k = i - 1, l = j + 1; k >= i - 4, l <= j + 4; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (a[i][j] != a[i + 1][j - 1] && a[i][j] != a[i - 5][j + 5])
				{
					if (i + 1 < n && j - 1 >= 0)
					{
						if (a[i + 1][j - 1] != 0)
						{
							temp_1 = 1;
						}
					}
					if (i - 5 >= 0 && j + 5 < n)
					{
						if (a[i - 5][j + 5] != 0)
						{
							temp_2 = 1;
						}
					}

					if (temp_1 != temp_2 || (temp_1 == temp_2 && temp_1 == 0))
					{
						return true;
					}
				}
			}
		}
		fail_condition++;
	}
	if (fail_condition == j - position)
	{
		return false;
	}
}
bool Check_Diagonal_2_Up(int a[100][100], int n, int j)
{
	int fail_condition = 0;
	int position = j;
	for (int i = 0; i <= n - position - 1, j <= n - 1; j++, i++)
	{
		int temp = 0;
		int temp_1 = 0;
		int temp_2 = 0;
		if (a[i][j] != 0)
		{
			for (int k = i + 1, l = j + 1; k <= i + 4, l <= j + 4; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (a[i][j] != a[i - 1][j - 1] && a[i][j] != a[i + 5][j + 5])
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						if (a[i - 1][j - 1] != 0)
						{
							temp_1 = 1;
						}
					}
					if (i + 5 < n && j + 5 < n)
					{
						if (a[i + 5][j + 5] != 0)
						{
							temp_2 = 1;
						}
					}

					if (temp_1 != temp_2 || (temp_1 == temp_2 && temp_1 == 0))
					{
						return true;
					}
				}
			}
		}
		fail_condition++;
	}
	if (fail_condition == n - position)
	{
		return false;
	}
}
bool Check_Diagonal_2_Down(int a[100][100], int n, int i)
{
	int fail_condition = 0;
	int position = i;
	for (int j = 0; j <= n - position - 1, i <= n - 1; j++, i++)
	{
		int temp = 0;
		int temp_1 = 0;
		int temp_2 = 0;
		if (a[i][j] != 0)
		{
			for (int k = i + 1, l = j + 1; k <= i + 4, l <= j + 4; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (a[i][j] != a[i - 1][j - 1] && a[i][j] != a[i + 5][j + 5])
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						if (a[i - 1][j - 1] != 0)
						{
							temp_1 = 1;
						}
					}
					if (i + 5 < n && j + 5 < n)
					{
						if (a[i + 5][j + 5] != 0)
						{
							temp_2 = 1;
						}
					}

					if (temp_1 != temp_2 || (temp_1 == temp_2 && temp_1 == 0))
					{
						return true;
					}
				}
			}
		}
		fail_condition++;
	}
	if (fail_condition == n - position)
	{
		return false;
	}
}
bool Check_Win(int a[100][100], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (Check_Row(a, n, i) == true)
		{
			return true;
		}
	}


	for (int j = 0; j < n; j++)
	{
		if (Check_Column(a, n, j) == true)
		{
			return true;
		}
	}


	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up(a, n, i) == true)
		{
			return true;
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down(a, n, j) == true)
		{
			return true;
		}
	}


	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up(a, n, j) == true)
		{
			return true;
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down(a, n, i) == true)
		{
			return true;
		}
	}


	return false;
}
//Main Function for playing with 2 players
void playgame(int Check_Table[100][100] ,int n,int &player, ROW &row, CONDITION &condition)
{
	char background[][100] = { "CARO GAME","New game","Help","Load Game","About","Exit" };
	char Help[][1000] = { "For 1 player:","X - NPC","O - player - use arrow key to move up, down, right, left - use enter key to tick 'O'","For 2 players:","X - player 1 - use arrow key to move up, down, right, left - use enter key to tick 'X'","O - player 2 - use W, S, D, A key to move up, down, right, left - use enter key to tick 'O'","First player have to tick at the center table","_Back" };
	system("cls");
	if (condition.Exist_Help == 0)
	{
		Creat_New_Table(n);
	}
	else
	{
		SetColor(7);
		Creat_New_Table(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Check_Table[i][j] == 1)
				{
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
					SetColor(12);
					printf("X");
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				}
				if (Check_Table[i][j] == 2)
				{
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
					SetColor(10);
					printf("O");
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				}
			}
		}
		if (condition.End == 1)
		{
			gotoxy(0, 2 * n + 2);
			SetColor(7);
			printf("Chuc mung nguoi choi 1 da chien thang\n");
			return;
		}
		if (condition.End == 2)
		{
			gotoxy(0, 2 * n + 2);
			SetColor(7);
			printf("Chuc mung nguoi choi 2 da chien thang\n");
			return;
		}
		if (condition.End == 3)
		{
			gotoxy(0, 2 * n + 2);
			SetColor(7);
			printf("2 nguoi choi hoa nhau\n");
			return;
		}
	}
	condition.End = 0;
    condition.Exist_Background = 0;
	int x, y;


	if (n % 2 == 0)
	{
		x = 2 * n - 2;
		y = n - 1;

	}
	if (n % 2 != 0)
	{
		x = 2 * n;
		y = n;
	}
	gotoxy(x, y);


	
	if (condition.Exist_Help == 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Check_Table[i][j] = 0;
			}
		}
		if (player == 1)
		{
			SetColor(12);
			printf("X");
			Check_Table[Change_y(y)][Change_x(x)] = 1;
			x = x + 4;
			gotoxy(x, y);
			player = 2;
		}
		else
		{
			SetColor(10);
			printf("O");
			Check_Table[Change_y(y)][Change_x(x)] = 2;
			x = x + 4;
			gotoxy(x, y);
			player = 1;
		}
	}
	do
	{
		char key = _getch();
		if (key == -32 || key == 0)
		{
			key = _getch();
		}
		switch (key)
		{
		case SPACE:
		{
			if (Check_Table[Change_y(y)][Change_x(x)] == 0 && player == 2)
			{
				SetColor(10);
				printf("O");
				Check_Table[Change_y(y)][Change_x(x)] = 2;
				player = 1;


				if (Check_Win(Check_Table, n) == true)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					printf("Chuc mung nguoi choi 2 da chien thang\n");
					condition.End = 2;
					return;
				}
				int empty = 0;
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (Check_Table[i][j] == 0)
						{
							empty++;
						}
					}
				}
				if (empty == 0)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					printf("2 nguoi choi hoa nhau");
					condition.End = 3;
					return;
				}
				gotoxy(x, y);
			}
			break;
		}
		case ENTER:
		{
			if (Check_Table[Change_y(y)][Change_x(x)] == 0 && player == 1)
			{
				SetColor(12);
				printf("X");
				Check_Table[Change_y(y)][Change_x(x)] = 1;
				player = 2;


				if (Check_Win(Check_Table, n) == true)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					printf("Chuc mung nguoi choi 1 da chien thang\n");
					condition.End = 1;
					return;
				}
				int empty = 0;
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (Check_Table[i][j] == 0)
						{
							empty++;
						}
					}
				}
				if (empty == 0)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					printf("2 nguoi choi hoa nhau");
					condition.End = 3;
					return;
				}
				gotoxy(x, y);
			}
			break;
		}
		case UP:
		{
			if (player == 1)
			{
				if (y > 1)
				{
					y = y - 2;
					gotoxy(x, y);
				}

			}
			break;

		}
		case DOWN:
		{
			if (player == 1)
			{
				if (y < 2 * n - 1)
				{
					y = y + 2;
					gotoxy(x, y);
				}

			}
			break;
		}
		case LEFT:
		{
			if (player == 1)
			{
				if (x > 2)
				{
					x = x - 4;
					gotoxy(x, y);
				}

			}
			break;
		}
		case RIGHT:
		{
			if (player == 1)
			{
				if (x < 4 * n - 2)
				{
					x = x + 4;
					gotoxy(x, y);
				}
			}
			break;
		}
		case A:
		{
			if (player == 2)
			{
				if (x > 2)
				{
					x = x - 4;
					gotoxy(x, y);
				}
			}
			break;
		}
		case D:
		{
			if (player == 2)
			{
				if (x < 4 * n - 2)
				{
					x = x + 4;
					gotoxy(x, y);
				}
			}
			break;
		}
		case W:
		{
			if (player == 2)
			{
				if (y > 1)
				{
					y = y - 2;
					gotoxy(x, y);
				}
			}
			break;
		}
		case S:
		{
			if (player == 2)
			{
				if (y < 2 * n - 1)
				{
					y = y + 2;
					gotoxy(x, y);
				}
			}
			break;
		}
		case esc:
		{
			system("cls");
			SetColor(7);
			Creat_Background_Function(background, row, condition);
			return;
		}
		case f1:
		{
			system("cls");
			SetColor(7);
			row.New_Game = -1;
			condition.Exist_Table = 1;
			condition.Exist_Help = 0;
			Creat_Help_Function(Help, row, condition);
			return;
		}
		case f2:
		{
			int decision;
			gotoxy(0, 2 * n + 3);
			SetColor(7);
			printf("Ban co muon luu lai game\n");
			do
			{
				printf("Neu muon luu game bam 1 nguoc lai bam 0: ");
				scanf("%d", &decision);
			} while (decision < 0 && decision > 1);
			if (decision == 1)
			{
				SaveGame(n, Check_Table);
			}
			system("cls");
			condition.Exist_Help = 0;
			do
			{
				printf("Nhap 1 neu player 1 muon danh truoc nhap 2 neu player 2 muon danh truoc:");
				scanf_s("%d", &player);
			} while (player < 1 || player > 2);
			f2_Node(Check_Table, n, x, y);
			if (player == 1)
			{
				SetColor(12);
				printf("X");
				Check_Table[Change_y(y)][Change_x(x)] = 1;
				x = x + 4;
				gotoxy(x, y);
				player = 2;
			}
			else
			{
				SetColor(10);
				printf("O");
				Check_Table[Change_y(y)][Change_x(x)] = 2;
				x = x + 4;
				gotoxy(x, y);
				player = 1;
			}
			break;
		}
		case f3:
		{
			SaveGame(n, Check_Table);
			gotoxy(0, 2 * n + 2);
			SetColor(7);
			printf("Game da duoc luu lai\n");
			break;
		}
		case f4:
		{
			condition.Exist_Help = 1;
			system("cls");
			SetColor(7);
			printf("Hay chon file game can choi cua ban trong danh sach sau:\n");
			ShowFileName();
			char* ChosenFile = new char[17];
			printf("Nhap ten file can mo: ");
			_flushall();
			InputString(ChosenFile);
			condition.Exist_Help = 1;
			LoadGame(ChosenFile, Check_Table, player);
			break;
		}
		case f5:
		{
			system("cls");
			SetColor(7);
			printf("- Game Genter: Logic Game\n");
			printf("- Devoloper: Tran Pham khanh Son\n");
			printf("+ University of Science\n");
			printf("+ Speciality: Information Technology\n");
			printf("+ 17CTT6 - 1712733\n");
			printf("- Devoloper: Nguyen Hoang Son\n");
			printf("+ University of Science\n");
			printf("+ Speciality: Information Technology\n");
			printf("+ 17CTT6 - 1712729\n\n");			
			printf("-----------press esc to bac-----------");
			break;
		}
		default:
			break;
		}
	} while (1);
}





//Player vs NPC
//Support function for playing player vs NPC
int Change_from_j_to_x(int j)
{
	if (j == 0)
	{
		return 2;
	}
	return Change_from_j_to_x(j - 1) + 4;
}
int Change_from_i_to_y(int i)
{
	if (i == 0)
	{
		return 1;
	}
	return Change_from_i_to_y(i - 1) + 2;
}
//function for checking the win PLAYER (in NPC vs PLAYER)
//For Row
bool Check_Row_2_steps(int a[100][100], int n, int i)
{
	for (int j = 0; j < n; j++)
	{
		int temp = 0;
		if (a[i][j] == 2)
		{
			for (int k = j + 1; k <= j + 4; k++)
			{
				if (a[i][j] == a[i][k])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (j - 1 >= 0 && j + 5 < n)
				{
					if (a[i][j - 1] == 0 && a[i][j + 5] == 0)
					{
						return true;
					}
				}

			}
		}
	}
	return false;
}
//For Column
bool Check_Column_2_steps(int a[100][100], int n, int j)
{
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		if (a[i][j] != 0)
		{
			for (int k = i + 1; k <= i + 4; k++)
			{
				if (a[i][j] == a[k][j])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (i - 1 >= 0 && i + 5 < n)
				{
					if (a[i - 1][j] == 0 && a[i + 5][j] == 0)
					{
						return true;
					}
				}

			}
		}
	}
	return false;
}
//For Diagonal 1
bool Check_Diagonal_1_Up_2_steps(int a[100][100], int n, int i)
{
	int position = i;
	for (int j = 0; j <= position, i >= 0; j++, i--)
	{
		int temp = 0;
		if (a[i][j] != 0)
		{
			for (int k = i - 1, l = j + 1; k >= i - 4, l <= j + 4; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (i + 1 < n && j - 1 >= 0 && i - 5 >= 0 && j + 5 < n)
				{
					if (a[i + 1][j - 1] == 0 && a[i - 5][j + 5] == 0)
					{
						return true;
					}
				}

			}
		}

	}

	return false;
}
bool Check_Diagonal_1_Down_2_steps(int a[100][100], int n, int j)
{
	int position = j;
	for (int i = n - 1; i >= position, j <= n - 1; i--, j++)
	{
		int temp = 0;
		if (a[i][j] != 0)
		{
			for (int k = i - 1, l = j + 1; k >= i - 4, l <= j + 4; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (i + 1 < n && j - 1 >= 0 && i - 5 >= 0 && j + 5 < n)
				{
					if (a[i + 1][j - 1] == 0 && a[i - 5][j + 5] == 0)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
//For Diagonal 2
bool Check_Diagonal_2_Up_2_steps(int a[100][100], int n, int j)
{
	int position = j;
	for (int i = 0; i <= n - position - 1, j <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] != 0)
		{
			for (int k = i + 1, l = j + 1; k <= i + 4, l <= j + 4; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (i - 1 >= 0 && j - 1 >= 0 && i + 5 < n && j + 5 < n)
				{

					if (a[i - 1][j - 1] == 0 && a[i + 5][j + 5] == 0)
					{
						return true;
					}

				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_2_Down_2_steps(int a[100][100], int n, int i)
{
	int position = i;
	for (int j = 0; j <= n - position - 1, i <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] != 0)
		{
			for (int k = i + 1, l = j + 1; k <= i + 4, l <= j + 4; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 4)
			{
				if (a[i][j] != a[i - 1][j - 1] && a[i][j] != a[i + 5][j + 5])
				{
					if (i - 1 >= 0 && j - 1 >= 0 && i + 5 < n && j + 5 < n)
					{

						if (a[i - 1][j - 1] == 0 && a[i + 5][j + 5] == 0)
						{
							return true;
						}

					}
				}
			}
		}
	}
	return false;
}
//Check Win
bool Check_Win_2_steps(int a[100][100], int n)
{
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_2_steps(a, n, i) == true)
		{
			return true;
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_2_steps(a, n, j) == true)
		{
			return true;
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_2_steps(a, n, i) == true)
		{
			return true;
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_2_steps(a, n, j) == true)
		{
			return true;
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_2_steps(a, n, j) == true)
		{
			return true;
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_2_steps(a, n, i) == true)
		{
			return true;
		}
	}


	return false;
}


//function for checking 4 steps of NPC (in NPC vs PLAYER)
//For Row
bool Check_Row_Main_NPC_2_steps(int a[100][100], int n, int i, int & CASE)
{
	CASE = 0;
	for (int j = 0; j < n; j++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = j + 1; k <= j + 3; k++)
			{
				if (a[i][j] == a[i][k])
				{
					temp++;
				}
			}
			if (temp == 3)
			{
				if (j - 2 >= 0 && j + 5 < n)
				{
					if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (j - 2 >= 0)
				{
					if (a[i][j - 1] == 0 && a[i][j - 2] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (j + 5 < n)
				{
					if (a[i][j + 4] == 0 && a[i][j + 5] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
//For Column
bool Check_Column_Main_NPC_2_steps(int a[100][100], int n, int j, int & CASE)
{
	CASE = 0;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1; k <= i + 3; k++)
			{
				if (a[i][j] == a[k][j])
				{
					temp++;
				}
			}
			if (temp == 3)
			{
				if (i - 2 >= 0 && i + 5 < n)
				{
					if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (i - 2 >= 0)
				{
					if (a[i - 1][j] == 0 && a[i - 2][j] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i + 5 < n)
				{
					if (a[i + 4][j] == 0 && a[i + 5][j] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}

	}
	return false;
}
//For Diagonal 1
bool Check_Diagonal_1_Up_Main_NPC_2_steps(int a[100][100], int n, int i, int & CASE)
{
	CASE = 0;
	int position = i;
	for (int j = 0; j <= position, i >= 0; j++, i--)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i - 1, l = j + 1; k >= i - 3, l <= j + 3; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 3)
			{
				if (i + 2 < n && j - 2 >= 0 && i - 5 >= 0 && j + 5 < n)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0)
					{

						CASE = 1;
						return true;
					}
				}
				if (i + 2 < n && j - 2 >= 0)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i - 5 >= 0 && j + 5 < n)
				{
					if (a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0)
					{

						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_1_Down_Main_NPC_2_steps(int a[100][100], int n, int j, int & CASE)
{
	CASE = 0;
	int position = j;
	for (int i = n - 1; i >= position, j <= n - 1; i--, j++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i - 1, l = j + 1; k >= i - 3, l <= j + 3; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 3)
			{
				if (i + 2 < n && j - 2 >= 0 && i - 5 >= 0 && j + 5 < n)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0)
					{

						CASE = 1;
						return true;
					}
				}
				if (i + 2 < n && j - 2 >= 0)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i - 5 >= 0 && j + 5 < n)
				{
					if (a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0)
					{

						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
//For Diagonal 2
bool Check_Diagonal_2_Up_Main_NPC_2_steps(int a[100][100], int n, int j, int & CASE)
{
	CASE = 0;
	int position = j;
	for (int i = 0; i <= n - position - 1, j <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1, l = j + 1; k <= i + 3, l <= j + 3; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 3)
			{
				if (i - 2 >= 0 && j - 2 >= 0 && i + 5 < n && j + 5 < n)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (i - 2 >= 0 && j - 2 >= 0)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i + 5 < n && j + 5 < n)
				{
					if (a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_2_Down_Main_NPC_2_steps(int a[100][100], int n, int i, int &CASE)
{
	CASE = 0;
	int position = i;
	for (int j = 0; j <= n - position - 1, i <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1, l = j + 1; k <= i + 3, l <= j + 3; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 3)
			{
				if (i - 2 >= 0 && j - 2 >= 0 && i + 5 < n && j + 5 < n)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (i - 2 >= 0 && j - 2 >= 0)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i + 5 < n && j + 5 < n)
				{
					if (a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
//Check Win
bool Check_Win_Main_NPC_2_steps(int a[100][100], int n, int &CASE)
{
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_Main_NPC_2_steps(a, n, i, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_Main_NPC_2_steps(a, n, j, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_Main_NPC_2_steps(a, n, i, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_Main_NPC_2_steps(a, n, j, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_Main_NPC_2_steps(a, n, j, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_Main_NPC_2_steps(a, n, i, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_Main_NPC_2_steps(a, n, i, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_Main_NPC_2_steps(a, n, j, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_Main_NPC_2_steps(a, n, i, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_Main_NPC_2_steps(a, n, j, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_Main_NPC_2_steps(a, n, j, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_Main_NPC_2_steps(a, n, i, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	return false;
}

//function for checking 3 steps of NPC (in NPC vs PLAYER)
//For Row
bool Check_Row_Main_NPC_3_steps(int a[100][100], int n, int i, int & CASE)
{
	CASE = 0;
	for (int j = 0; j < n; j++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = j + 1; k <= j + 2; k++)
			{
				if (a[i][j] == a[i][k])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (j - 3 >= 0 && j + 5 < n)
				{
					if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (j - 3 >= 0)
				{
					if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (j + 5 < n)
				{
					if (a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
//For Column
bool Check_Column_Main_NPC_3_steps(int a[100][100], int n, int j, int & CASE)
{
	CASE = 0;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1; k <= i + 2; k++)
			{
				if (a[i][j] == a[k][j])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (i - 3 >= 0 && i + 5 < n)
				{
					if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (i - 3 >= 0)
				{
					if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i + 5 < n)
				{
					if (a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}

	}
	return false;
}
//For Diagonal 1
bool Check_Diagonal_1_Up_Main_NPC_3_steps(int a[100][100], int n, int i, int & CASE)
{
	CASE = 0;
	int position = i;
	for (int j = 0; j <= position, i >= 0; j++, i--)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i - 1, l = j + 1; k >= i - 2, l <= j + 2; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (i + 3 < n && j - 3 >= 0 && i - 5 >= 0 && j + 5 < n)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0 && a[i - 3][j + 3] == 0)
					{

						CASE = 1;
						return true;
					}
				}
				if (i + 3 < n && j - 3 >= 0)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i - 5 >= 0 && j + 5 < n)
				{
					if (a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0 && a[i - 3][j + 3] == 0)
					{

						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_1_Down_Main_NPC_3_steps(int a[100][100], int n, int j, int & CASE)
{
	CASE = 0;
	int position = j;
	for (int i = n - 1; i >= position, j <= n - 1; i--, j++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i - 1, l = j + 1; k >= i - 2, l <= j + 2; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (i + 3 < n && j - 3 >= 0 && i - 5 >= 0 && j + 5 < n)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0 && a[i - 3][j + 3] == 0)
					{

						CASE = 1;
						return true;
					}
				}
				if (i + 3 < n && j - 3 >= 0)
				{
					if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i - 5 >= 0 && j + 5 < n)
				{
					if (a[i - 5][j + 5] == 0 && a[i - 4][j + 4] == 0 && a[i - 3][j + 3] == 0)
					{

						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
//For Diagonal 2
bool Check_Diagonal_2_Up_Main_NPC_3_steps(int a[100][100], int n, int j, int & CASE)
{
	CASE = 0;
	int position = j;
	for (int i = 0; i <= n - position - 1, j <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1, l = j + 1; k <= i + 2, l <= j + 2; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (i - 3 >= 0 && j - 3 >= 0 && i + 5 < n &&j + 5 < n)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (i - 3 >= 0 && j - 3 >= 0)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i + 5 < n && j + 5 < n)
				{
					if (a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_2_Down_Main_NPC_3_steps(int a[100][100], int n, int i, int &CASE)
{
	CASE = 0;
	int position = i;
	for (int j = 0; j <= n - position - 1, i <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1, l = j + 1; k <= i + 2, l <= j + 2; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (i - 3 >= 0 && j - 3 >= 0 && i + 5 < n &&j + 5 < n)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 1;
						return true;
					}
				}
				if (i - 3 >= 0 && j - 3 >= 0)
				{
					if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0)
					{
						CASE = 2;
						return true;
					}
				}
				if (i + 5 < n && j + 5 < n)
				{
					if (a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
					{
						CASE = 3;
						return true;
					}
				}
			}
		}
	}
	return false;
}
//Check Win
bool Check_Win_Main_NPC_3_steps(int a[100][100], int n, int &CASE)
{
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_Main_NPC_3_steps(a, n, i, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_Main_NPC_3_steps(a, n, j, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_Main_NPC_3_steps(a, n, i, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_Main_NPC_3_steps(a, n, j, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_Main_NPC_3_steps(a, n, j, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_Main_NPC_3_steps(a, n, i, CASE) == true)
		{
			if (CASE == 1)
			{
				return true;
			}
		}
	}
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_Main_NPC_3_steps(a, n, i, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_Main_NPC_3_steps(a, n, j, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_Main_NPC_3_steps(a, n, i, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_Main_NPC_3_steps(a, n, j, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_Main_NPC_3_steps(a, n, j, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_Main_NPC_3_steps(a, n, i, CASE) == true)
		{
			if (CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	return false;
}

//function for checking NPC with 2 steps more (in NPC vs PLAYER)
//For Row
bool Check_Row_NPC_2_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	for (int j = 0; j < n; j++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = j + 1; k <= j + 2; k++)
			{
				if (a[i][j] == a[i][k])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (a[i][j - 1] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				//2 points
				if (a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
			}

		}
	}
	return false;
}
//For Column
bool Check_Column_NPC_2_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1; k <= i + 2; k++)
			{
				if (a[i][j] == a[k][j])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (a[i - 1][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 1;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 2;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i + 3][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 3;
					return true;
				}
				//2 points
				if (a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 4;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 5;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i + 3][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 6;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 7;
					return true;
				}
			}
		}
	}
	return false;
}
//For Diagonal 1
bool Check_Diagonal_1_Up_NPC_2_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = i;
	for (int j = 0; j <= position, i >= 0; j++, i--)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i - 1, l = j + 1; k >= i - 2, l <= j + 2; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (a[i + 1][j - 1] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				//2 points
				if (a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_1_Down_NPC_2_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = j;
	for (int i = n - 1; i >= position, j <= n - 1; i--, j++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i - 1, l = j + 1; k >= i - 2, l <= j + 2; k--, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (a[i + 1][j - 1] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				//2 points
				if (a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
			}
		}
	}
	return false;
}
//For Diagonal 2
bool Check_Diagonal_2_Up_NPC_2_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = j;
	for (int i = 0; i <= n - position - 1, j <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1, l = j + 1; k <= i + 2, l <= j + 2; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (a[i - 1][j - 1] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				//2 points
				if (a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_2_Down_NPC_2_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = i;
	for (int j = 0; j <= n - position - 1, i <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			for (int k = i + 1, l = j + 1; k <= i + 2, l <= j + 2; k++, l++)
			{
				if (a[i][j] == a[k][l])
				{
					temp++;
				}
			}
			if (temp == 2)
			{
				if (a[i - 1][j - 1] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				//2 points
				if (a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
			}
		}
	}
	return false;
}
//Check Win
bool Check_Win_NPC_2_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_NPC_2_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_NPC_2_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_NPC_2_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_NPC_2_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_NPC_2_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_NPC_2_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3)
			{
				return true;
			}
		}
	}
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_NPC_2_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 4 || CASE == 5 || CASE == 6 || CASE == 7)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_NPC_2_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 4 || CASE == 5 || CASE == 6 || CASE == 7)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_NPC_2_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 4 || CASE == 5 || CASE == 6 || CASE == 7)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_NPC_2_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 4 || CASE == 5 || CASE == 6 || CASE == 7)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_NPC_2_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 4 || CASE == 5 || CASE == 6 || CASE == 7)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_NPC_2_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 4 || CASE == 5 || CASE == 6 || CASE == 7)
			{
				return true;
			}
		}
	}
	//Else
	return false;
}

//function for checking NPC with 3 steps more (in NPC vs PLAYER)
//For Row
bool Check_Row_NPC_3_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	for (int j = 0; j < n; j++)
	{
		if (a[i][j] == 1)
		{
			if (a[i][j] == a[i][j + 1])
			{
				if (a[i][j - 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j - 4] == 0 && a[i][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				//2 points
				if (a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 8;
					return true;
				}
				if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j - 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i;
					l_position = j + 1;
					CASE = 9;
					return true;
				}
			}

		}
	}
	return false;
}
//For Column
bool Check_Column_NPC_3_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	for (int i = 0; i < n; i++)
	{
		if (a[i][j] == 1)
		{
			if (a[i][j] == a[i + 1][j])
			{
				if (a[i - 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 1;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 2;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 3;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0 && a[i + 2][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 4;
					return true;
				}
				//2 points
				if (a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 5;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 6;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 7;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i + 2][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 8;
					return true;
				}
				if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j;
					CASE = 9;
					return true;
				}
			}

		}
	}
	return false;
}
//For Diagonal 1
bool Check_Diagonal_1_Up_NPC_3_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = i;
	for (int j = 0; j <= position, i >= 0; j++, i--)
	{
		if (a[i][j] == 1)
		{
			if (a[i][j] == a[i - 1][j + 1])
			{
				if (a[i + 1][j - 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i - 2][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				//2 points
				if (a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 2][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 8;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 9;
					return true;
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_1_Down_NPC_3_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = j;
	for (int i = n - 1; i >= position, j <= n - 1; i--, j++)
	{
		if (a[i][j] == 1)
		{
			if (a[i][j] == a[i - 1][j + 1])
			{
				if (a[i + 1][j - 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i - 2][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				//2 points
				if (a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 2][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 8;
					return true;
				}
				if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i - 1;
					l_position = j + 1;
					CASE = 9;
					return true;
				}
			}
		}
	}
	return false;
}
//For Diagonal 2
bool Check_Diagonal_2_Up_NPC_3_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = j;
	for (int i = 0; i <= n - position - 1, j <= n - 1; j++, i++)
	{
		if (a[i][j] == 1)
		{
			if (a[i][j] == a[i + 1][j + 1])
			{
				if (a[i - 1][j - 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 4][j - 4] == 0 && a[i + 2][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				//2 points
				if (a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
				if (a[i + 2][j + 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 8;
					return true;
				}
				if (a[i - 4][j - 4] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 9;
					return true;
				}
			}
		}
	}
	return false;
}
bool Check_Diagonal_2_Down_NPC_3_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = i;
	for (int j = 0; j <= n - position - 1, i <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			if (a[i][j] == a[i + 1][j + 1])
			{
				if (a[i - 1][j - 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 1;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 2;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 3;
					return true;
				}
				if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 4][j - 4] == 0 && a[i + 2][j + 2] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 4;
					return true;
				}
				//2 points
				if (a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 5;
					return true;
				}
				if (a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 6;
					return true;
				}
				if (a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 7;
					return true;
				}
				if (a[i + 2][j + 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 8;
					return true;
				}
				if (a[i - 4][j - 4] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
				{
					i_position = i;
					j_position = j;
					k_position = i + 1;
					l_position = j + 1;
					CASE = 9;
					return true;
				}
			}
		}
	}
	return false;
}
//Check Win
bool Check_Win_NPC_3_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_NPC_3_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_NPC_3_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_NPC_3_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_NPC_3_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_NPC_3_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_NPC_3_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4)
			{
				return true;
			}
		}
	}
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_NPC_3_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 5 || CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_NPC_3_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 5 || CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_NPC_3_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 5 || CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_NPC_3_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 5 || CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_NPC_3_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 5 || CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_NPC_3_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 5 || CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9)
			{
				return true;
			}
		}
	}

	//Else
	return false;
}

//function for checking NPC with 4 steps more (in NPC vs PLAYER)
//For Row
bool Check_Row_NPC_4_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	for (int j = 0; j < n; j++)
	{
		if (a[i][j] == 1)
		{
			if (a[i][j - 1] == 0 && a[i][j + 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 1;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j + 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 2;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j + 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 3;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j - 4] == 0 && a[i][j + 1] == 0 && a[i][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 4;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j - 4] == 0 && a[i][j - 5] == 0 && a[i][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 5;
				return true;
			}
			//2 points
			if (a[i][j + 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 6;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j + 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 7;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j + 1] == 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 8;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j + 1] == 0 && a[i][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 9;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j - 4] == 0 && a[i][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 10;
				return true;
			}
			if (a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j - 4] == 0 && a[i][j - 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i;
				l_position = j + 1;
				CASE = 11;
				return true;
			}
		}

	}
	return false;
}
//For Column
bool Check_Column_NPC_4_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	for (int i = 0; i < n; i++)
	{
		if (a[i][j] == 1)
		{
			if (a[i - 1][j] == 0 && a[i + 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 1;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i + 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 2;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i + 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 3;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0 && a[i + 1][j] == 0 && a[i + 2][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 4;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0 && a[i - 5][j] == 0 && a[i + 1][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 5;
				return true;
			}
			//2 points
			if (a[i + 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0 && a[i + 5][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 6;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i + 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0 && a[i + 4][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 7;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i + 1][j] == 0 && a[i + 2][j] == 0 && a[i + 3][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 8;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i + 1][j] == 0 && a[i + 2][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 9;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0 && a[i + 1][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 10;
				return true;
			}
			if (a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0 && a[i - 5][j] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j;
				CASE = 11;
				return true;
			}
		}

	}
	return false;
}
//For Diagonal 1
bool Check_Diagonal_1_Up_NPC_4_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = i;
	for (int j = 0; j <= position, i >= 0; j++, i--)
	{
		if (a[i][j] == 1)
		{
			if (a[i + 1][j - 1] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 1;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 2;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 3;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 4;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i + 5][j - 5] == 0 && a[i - 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 5;
				return true;
			}
			//2 points
			if (a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 6;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 7;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 8;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 9;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i - 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 10;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i + 5][j - 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 11;
				return true;
			}
		}
	}
	return false;
}
bool Check_Diagonal_1_Down_NPC_4_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = j;
	for (int i = n - 1; i >= position, j <= n - 1; i--, j++)
	{
		if (a[i][j] == 1)
		{
			if (a[i + 1][j - 1] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 1;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 2;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 3;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 4;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i + 5][j - 5] == 0 && a[i - 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 5;
				return true;
			}
			//2 points
			if (a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0 && a[i - 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 6;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0 && a[i - 4][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 7;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0 && a[i - 3][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 8;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i - 1][j + 1] == 0 && a[i - 2][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 9;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i - 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 10;
				return true;
			}
			if (a[i + 1][j - 1] == 0 && a[i + 2][j - 2] == 0 && a[i + 3][j - 3] == 0 && a[i + 4][j - 4] == 0 && a[i + 5][j - 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i - 1;
				l_position = j + 1;
				CASE = 11;
				return true;
			}
		}
	}
	return false;
}
//For Diagonal 2
bool Check_Diagonal_2_Up_NPC_4_steps(int a[100][100], int n, int j, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = j;
	for (int i = 0; i <= n - position - 1, j <= n - 1; j++, i++)
	{
		if (a[i][j] == 1)
		{
			if (a[i - 1][j - 1] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 1;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 2;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 3;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 4][j - 4] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 4;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 4][j - 4] == 0 && a[i - 5][j - 5] == 0 && a[i + 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 5;
				return true;
			}
			//2 points
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 6;
				return true;
			}
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 7;
				return true;
			}
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 8;
				return true;
			}
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 9;
				return true;
			}
			if (a[i - 4][j - 4] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0 && a[i + 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 10;
				return true;
			}
			if (a[i - 5][j - 5] == 0 && a[i - 4][j - 4] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 11;
				return true;
			}
		}
	}
	return false;
}
bool Check_Diagonal_2_Down_NPC_4_steps(int a[100][100], int n, int i, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	CASE = 0;
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	int position = i;
	for (int j = 0; j <= n - position - 1, i <= n - 1; j++, i++)
	{
		int temp = 0;
		if (a[i][j] == 1)
		{
			if (a[i - 1][j - 1] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 1;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 2;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 3;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 4][j - 4] == 0 && a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 4;
				return true;
			}
			if (a[i - 1][j - 1] == 0 && a[i - 2][j - 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 4][j - 4] == 0 && a[i - 5][j - 5] == 0 && a[i + 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 5;
				return true;
			}
			//2 points
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i + 5][j + 5] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 6;
				return true;
			}
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i + 4][j + 4] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 7;
				return true;
			}
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i + 3][j + 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 8;
				return true;
			}
			if (a[i + 1][j + 1] == 0 && a[i + 2][j + 2] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 9;
				return true;
			}
			if (a[i - 4][j - 4] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0 && a[i + 1][j + 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 10;
				return true;
			}
			if (a[i - 5][j - 5] == 0 && a[i - 4][j - 4] == 0 && a[i - 3][j - 3] == 0 && a[i - 2][j - 2] == 0 && a[i - 1][j - 1] == 0)
			{
				i_position = i;
				j_position = j;
				k_position = i + 1;
				l_position = j + 1;
				CASE = 11;
				return true;
			}
		}
	}
	return false;
}
//Check Win
bool Check_Win_NPC_4_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position, int &k_position, int &l_position)
{
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_NPC_4_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4 || CASE == 5)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_NPC_4_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4 || CASE == 5)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_NPC_4_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4 || CASE == 5)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_NPC_4_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4 || CASE == 5)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_NPC_4_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4 || CASE == 5)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_NPC_4_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 1 || CASE == 2 || CASE == 3 || CASE == 4 || CASE == 5)
			{
				return true;
			}
		}
	}
	//For Row
	for (int i = 0; i < n; i++)
	{
		if (Check_Row_NPC_4_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9 || CASE == 10 || CASE == 11)
			{
				return true;
			}
		}
	}

	//For Column
	for (int j = 0; j < n; j++)
	{
		if (Check_Column_NPC_4_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9 || CASE == 10 || CASE == 11)
			{
				return true;
			}
		}
	}

	//For Diagonal 1
	for (int i = 0; i < n; i++)
	{
		if (Check_Diagonal_1_Up_NPC_4_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9 || CASE == 10 || CASE == 11)
			{
				return true;
			}
		}
	}
	for (int j = 1; j < n; j++)
	{
		if (Check_Diagonal_1_Down_NPC_4_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9 || CASE == 10 || CASE == 11)
			{
				return true;
			}
		}
	}

	//For Diagonal 2
	for (int j = 0; j < n; j++)
	{
		if (Check_Diagonal_2_Up_NPC_4_steps(a, n, j, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9 || CASE == 10 || CASE == 11)
			{
				return true;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (Check_Diagonal_2_Down_NPC_4_steps(a, n, i, CASE, i_position, j_position, k_position, l_position) == true)
		{
			if (CASE == 6 || CASE == 7 || CASE == 8 || CASE == 9 || CASE == 10 || CASE == 11)
			{
				return true;
			}
		}
	}

	//Else
	return false;
}

//Center Function
bool Check_Win_NPC_1_step(int a[100][100], int n, int &i_position, int &j_position)
{
	i_position = -1;
	j_position = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 1;
				if (Check_Win(a, n) == true)
				{
					i_position = i;
					j_position = j;
					a[i][j] = 0;
					return true;
				}
				else
				{
					a[i][j] = 0;
				}
			}
		}
	}
	return false;
}
bool Check_Win_Player_1_step(int a[100][100], int n, int &i_position, int &j_position)
{
	i_position = -1;
	j_position = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 2;
				if (Check_Win(a, n) == true)
				{
					i_position = i;
					j_position = j;
					a[i][j] = 0;
					return true;
				}
				else
				{
					a[i][j] = 0;
				}
			}
		}
	}
	return false;
}
bool Check_Win_Player_2_steps(int a[100][100], int n, int &i_position, int &j_position, int &k_position, int &l_position)
{
	i_position = -1;
	j_position = -1;
	k_position = -1;
	l_position = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 2;
				for (int k = 0; k < n; k++)
				{
					for (int l = 0; l < n; l++)
					{
						if (a[k][l] == 0)
						{
							a[k][l] = 2;
							if (Check_Win_2_steps(a, n) == true)
							{
								i_position = i;
								j_position = j;
								k_position = k;
								l_position = l;
								a[i][j] = 0;
								a[k][l] = 0;
								return true;
							}
							else
							{
								a[k][l] = 0;
							}
						}
					}
				}
				a[i][j] = 0;
			}
		}
	}
	return false;
}
bool Check_NPC_4_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position)
{
	i_position = -1;
	j_position = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 1;
				if (Check_Win_Main_NPC_2_steps(a, n, CASE) == true)
				{
					i_position = i;
					j_position = j;
					a[i][j] = 0;
					return true;
				}
				else
				{
					a[i][j] = 0;
				}
			}
		}
	}
	return false;
}
bool Check_NPC_3_steps(int a[100][100], int n, int &CASE, int &i_position, int &j_position)
{
	i_position = -1;
	j_position = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 1;
				if (Check_Win_Main_NPC_3_steps(a, n, CASE) == true)
				{
					i_position = i;
					j_position = j;
					a[i][j] = 0;
					return true;
				}
				else
				{
					a[i][j] = 0;
				}
			}
		}
	}
	return false;
}

//Main Function for playing with player vs NPC
void NPC_turn(int a[100][100], int n)
{
	int i_position, j_position;
	//Attack turn (Checking NPC win)
	if (Check_Win_NPC_1_step(a, n, i_position, j_position) == true)
	{
		gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
		printf("X");
		a[i_position][j_position] = 1;
		gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
	}
	//Defense turn (Checking Player win) 
	else
	{
		if (Check_Win_Player_1_step(a, n, i_position, j_position) == true)
		{
			gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
			printf("X");
			a[i_position][j_position] = 1;
			gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
		}
		else
		{
			int k_position, l_position;
			int delta_1;
			int delta_2;
			int CASE;
			//Main Attack turn 
			if (Check_NPC_4_steps(a, n, CASE, i_position, j_position) == true)
			{
				if (CASE == 1)
				{
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					printf("X");
					a[i_position][j_position] = 1;
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					return;
				}
			}
			//Defense turn
			if (Check_Win_Player_2_steps(a, n, i_position, j_position, k_position, l_position) == true)
			{
				gotoxy(Change_from_j_to_x(l_position), Change_from_i_to_y(k_position));
				printf("X");
				a[k_position][l_position] = 1;
				gotoxy(Change_from_j_to_x(l_position), Change_from_i_to_y(k_position));
				return;
			}
			//Main Attack turn 
			if (Check_NPC_4_steps(a, n, CASE, i_position, j_position) == true)
			{
				if (CASE == 2)
				{
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					printf("X");
					a[i_position][j_position] = 1;
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					return;
				}
				if (CASE == 3)
				{
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					printf("X");
					a[i_position][j_position] = 1;
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					return;
				}
			}
			//Support Attack turn
			if (Check_Win_NPC_2_steps(a, n, CASE, i_position, j_position, k_position, l_position) == true)
			{
				delta_1 = k_position - i_position;
				delta_2 = l_position - j_position;
				if (CASE == 1)
				{
					i_position = i_position + delta_1 + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 2)
				{
					i_position = i_position + delta_1 + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 3)
				{

					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 4)
				{
					i_position = i_position + delta_1 + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 5)
				{
					i_position = i_position + delta_1 + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 6)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 7)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
			}
			//
			if (Check_NPC_3_steps(a, n, CASE, i_position, j_position) == true)
			{
				if (CASE == 1)
				{
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					printf("X");
					a[i_position][j_position] = 1;
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					return;
				}
			}
			//
			if (Check_Win_NPC_3_steps(a, n, CASE, i_position, j_position, k_position, l_position) == true)
			{
				delta_1 = k_position - i_position;
				delta_2 = l_position - j_position;
				if (CASE == 1)
				{
					i_position = i_position + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 2)
				{
					i_position = i_position + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 3)
				{
					i_position = i_position + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 4)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
			}
			//
			if (Check_NPC_3_steps(a, n, CASE, i_position, j_position) == true)
			{
				if (CASE == 2)
				{
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					printf("X");
					a[i_position][j_position] = 1;
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					return;
				}
				if (CASE == 3)
				{
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					printf("X");
					a[i_position][j_position] = 1;
					gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
					return;
				}
			}
			//
			if (Check_Win_NPC_3_steps(a, n, CASE, i_position, j_position, k_position, l_position) == true)
			{
				delta_1 = k_position - i_position;
				delta_2 = l_position - j_position;
				if (CASE == 5)
				{
					i_position = i_position + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 6)
				{
					i_position = i_position + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 7)
				{
					i_position = i_position + delta_1 + delta_1;
					j_position = j_position + delta_2 + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 8)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 9)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
			}
			if (Check_Win_NPC_4_steps(a, n, CASE, i_position, j_position, k_position, l_position) == true)
			{
				delta_1 = k_position - i_position;
				delta_2 = l_position - j_position;
				if (CASE == 1)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 2)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 3)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 4)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 5)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 6)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 7)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 8)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 9)
				{
					i_position = i_position + delta_1;
					j_position = j_position + delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 10)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
				if (CASE == 11)
				{
					i_position = i_position - delta_1;
					j_position = j_position - delta_2;
					if (i_position >= 0 && i_position < n && j_position >= 0 && j_position < n)
					{
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						printf("X");
						a[i_position][j_position] = 1;
						gotoxy(Change_from_j_to_x(j_position), Change_from_i_to_y(i_position));
						return;
					}
				}
			}
			//Random turn (Checking empty box)
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (a[i][j] == 0)
					{
						gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
						printf("X");
						a[i][j] = 1;
						gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
						return;
					}
				}
			}
		}
	}
}
void playgame_NPC(int Check_Table[100][100], int n, int player_first_turn, ROW &row, CONDITION &condition)
{
	char background[][100] = { " CARO GAME","_New game","_Help","_Load Game","_About","_Exit" };
	char Help[][1000] = { "For 1 player:","X - NPC","O - player - use arrow key to move up, down, right, left - use enter key to tick 'O'","For 2 players:","X - player 1 - use arrow key to move up, down, right, left - use enter key to tick 'X'","O - player 2 - use W, S, D, A key to move up, down, right, left - use enter key to tick 'O'","_Back" };
	system("cls");

	if (condition.Exist_Help == 0)
	{
		Creat_New_Table(n);
	}
	else
	{
		SetColor(7);
		Creat_New_Table(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Check_Table[i][j] == 1)
				{
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
					SetColor(12);
					printf("X");
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				}
				if (Check_Table[i][j] == 2)
				{
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
					SetColor(10);
					printf("O");
					gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				}
			}
		}
		if (condition.End == 1)
		{
			gotoxy(0, 2 * n + 2);
			SetColor(7);
			printf("Chuc mung ban da chien thang\n");
			return;
		}
		if (condition.End == 2)
		{
			gotoxy(0, 2 * n + 2);
			SetColor(7);
			printf("Ban thua cuoc\n");
			return;
		}
		if (condition.End == 3)
		{
			gotoxy(0, 2 * n + 2);
			SetColor(7);
			printf("2 nguoi choi hoa nhau\n");
			return;
		}
	}
	condition.Exist_Background = 0;
	int x, y;

	if (n % 2 == 0)
	{
		x = 2 * n - 2;
		y = n - 1;

	}
	if (n % 2 != 0)
	{
		x = 2 * n;
		y = n;
	}
    gotoxy(x, y);

	condition.End = 0;
	
	if (condition.Exist_Help == 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Check_Table[i][j] = 0;
			}
		}
		if (player_first_turn == 0)
		{
			SetColor(12);
			printf("X");
			Check_Table[Change_y(y)][Change_x(x)] = 1;
			x = x + 4;
			gotoxy(x, y);
		}
		else
		{
			SetColor(10);
			printf("O");
			Check_Table[Change_y(y)][Change_x(x)] = 2;
			x = x + 4;
			gotoxy(x, y);
			SetColor(12);
			printf("X");
			Check_Table[Change_y(y)][Change_x(x)] = 1;
			x = x + 4;
			gotoxy(x, y);
		}
	}
	do
	{
		char key = _getch();
		if (key == -32 || key == 0)
		{
			key = _getch();
		}
		switch (key)
		{
		case ENTER:
		{
			if (Check_Table[Change_y(y)][Change_x(x)] == 0)
			{
				SetColor(10);
				printf("O");
				Check_Table[Change_y(y)][Change_x(x)] = 2;


				if (Check_Win(Check_Table, n) == true)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					printf("Chuc mung ban da chien thang\n");
					condition.End = 2;
					return;
				}
				int empty = 0;
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (Check_Table[i][j] == 0)
						{
							empty++;
						}
					}
				}
				if (empty == 0)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					printf("2 nguoi choi hoa nhau\n");
					condition.End = 3;
					return;
				}
				SetColor(12);
				NPC_turn(Check_Table, n);
				if (Check_Win(Check_Table, n) == true)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					printf("Ban thua cuoc\n");
					condition.End = 1;
					return ;
				}
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (Check_Table[i][j] == 0)
						{
							empty++;
						}
					}
				}
				if (empty == 0)
				{
					gotoxy(0, 2 * n + 2);
					SetColor(7);
					condition.End = 3;
					printf(" 2 nguoi choi hoa nhau\n");
					return;
				}
				gotoxy(x, y);
			}
			break;
		}
		case UP:
		{
			if (y > 1)
			{
				y = y - 2;
				gotoxy(x, y);
			}
			break;
		}
		case DOWN:
		{

			if (y < 2 * n - 1)
			{
				y = y + 2;
				gotoxy(x, y);
			}


			break;
		}
		case LEFT:
		{
			if (x > 2)
			{
				x = x - 4;
				gotoxy(x, y);
			}

			break;
		}
		case RIGHT:
		{
			if (x < 4 * n - 2)
			{
				x = x + 4;
				gotoxy(x, y);
			}
			break;
		}
		case esc:
		{
			system("cls");
			SetColor(7);
			Creat_Background_Function(background, row, condition);
			
			return;
		}
		case f1:
		{
			system("cls");
			SetColor(7);
			row.New_Game = -1;
			condition.Exist_Table = 1;
			condition.Exist_Help = 0;
			Creat_Help_Function(Help, row, condition);
			return;
		}
		case f2:
		{
			int decision;
			SetColor(7);
			gotoxy(0, 2 * n + 3);
			printf("Ban co muon luu lai game\n");
			do
			{
				printf("Neu muon luu game bam 1 nguoc lai bam 0: ");
				scanf("%d", &decision);
			} while (decision < 0 && decision > 1);
			if (decision == 1)
			{
				SaveGame(n, Check_Table);
			}
			system("cls");
			do
			{
				printf("Nhap 1 neu muon danh truoc nhap 0 neu muon danh sau:");
				scanf_s("%d", &player_first_turn);
			} while (player_first_turn > 1 || player_first_turn < 0);
			f2_Node(Check_Table, n, x, y);
			if (player_first_turn == 0)
			{
				SetColor(12);
				printf("X");
				Check_Table[Change_y(y)][Change_x(x)] = 1;
				x = x + 4;
				gotoxy(x, y);
			}
			else
			{
				SetColor(10);
				printf("O");
				Check_Table[Change_y(y)][Change_x(x)] = 2;
				x = x + 4;
				gotoxy(x, y);
				SetColor(12);
				printf("X");
				Check_Table[Change_y(y)][Change_x(x)] = 1;
				x = x + 4;
				gotoxy(x, y);
			}
			break;
		}
		case f3:
		{
			SaveGame(n, Check_Table);
			gotoxy(0, 2 * n + 3);
			SetColor(7);
			printf("Game da duoc luu lai\n");
			break;
		}
		case f4:
		{
			system("cls");
			SetColor(7);
			printf("Hay chon file game can choi cua ban trong danh sach sau:\n");
			ShowFileName();
			char* ChosenFile = new char[17];
			printf("Nhap ten file can mo: ");
			_flushall();
			InputString(ChosenFile);
			condition.Exist_Help = 1; int temp;
			LoadGame(ChosenFile, Check_Table, temp);
			break;
		}
		case f5:
		{
			system("cls");
			SetColor(7);
			printf("- Game Genter: Logic Game\n");
			printf("- Devoloper: Tran Pham khanh Son\n");
			printf("+ University of Science\n");
			printf("+ Speciality: Information Technology\n");
			printf("+ 17CTT6 - 1712733\n");
			printf("- Devoloper: Nguyen Hoang Son\n");
			printf("+ University of Science\n");
			printf("+ Speciality: Information Technology\n");
			printf("+ 17CTT6 - 1712729\n\n");
			printf("-----------press esc to bac-----------");
			break;
		}
		default:
			break;
		}
	} while (1);
}

//Function Node
//Support Function
char* Get_Time(char* result)
{
	time_t     now;
	struct tm  ts;
	time(&now);
	ts = *localtime(&now);
	char hour[3];
	char min[3];
	char day[3];
	char month[3];
	char year[5];
	sprintf(min, "%d", ts.tm_min);
	sprintf(hour, "%d", ts.tm_hour);
	sprintf(day, "%d", ts.tm_mday);
	sprintf(month, "%d", ts.tm_mon + 1);
	sprintf(year, "%d", ts.tm_year + 1900);
	strcpy(result, hour);
	sprintf(result, "%s%c", result, '_');
	strcat(result, min);
	sprintf(result, "%s%c", result, '_');
	strcat(result, day);
	sprintf(result, "%s%c", result, '_');
	strcat(result, month);
	sprintf(result, "%s%c", result, '_');
	strcat(result, year);
	return result;
}
void ShowFileName()
{
	FILE *p = fopen("Saved_Game.txt", "r");
	if (p == NULL)
	{
		printf("Khong mo duoc file vui long kiem tra lai\n");
		return;
	}
	const size_t line_size = 300;
	char* line = new char[line_size];
	while (fgets(line, line_size, p) != NULL)
	{
		printf(line);
	}
	free(line);
}
void InputString(char str[])
{
	int i;
	do
	{
		for (i = 0; 1; i++)
		{
			str[i] = getchar();
			if (str[i] == '\n')
			{
				str[i] = '\0';
				break;
			}
		}
	} while (strlen(str) == 0);
}
//Main Function
void SaveGame(int n, int check[100][100])
{
	char* time = new char[17];
	time = Get_Time(time);
	char Sig[4] = ".CR";
	char *name = new char[strlen(time) + strlen(Sig)];
	strcpy(name, time);
	strcat(name, Sig);
	FILE *f = fopen("Saved_Game.txt", "a");
	fputs(name, f);
	fprintf(f, "\n");
	FILE *p = fopen(name, "wb");
	CARO SavedGame;
	char Signature[] = "CR";
	fwrite(Signature, sizeof(Signature), 1, p);
	fwrite(&n, sizeof(n), 1, p);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fwrite(&check[i][j], sizeof(int), 1, p);
		}
	}
	fclose(f);
	fclose(p);
}
void LoadGame(char * FileName, int  Check_Table[100][100],int &player)
{
	CARO SavedGame;
	FILE *p = fopen(FileName, "rb");
	fread(&SavedGame, sizeof(CARO), 1, p);
	if ((SavedGame.type[0] != 'C') && (SavedGame.type[1] != 'R'))
	{
		SetColor(7);
		printf("File da doc khong phai la file game caro vui long kiem tra lai!");
		return;
	}
	system("cls");
	Creat_New_Table(SavedGame.sizegame);
	int k = 0;
	int temp_1 = 0;
	int temp_2 = 0;
	for (int i = 0; i < SavedGame.sizegame; i++)
	{
		for (int j = 0; j < SavedGame.sizegame; j++, k++)
		{
			Check_Table[i][j] = SavedGame.caro_matrix[k];
		}
	}
	for (int i = 0; i < SavedGame.sizegame; i++)
	{
		for (int j = 0; j < SavedGame.sizegame; j++)
		{
			if ((Check_Table[i][j]) == 1)
			{
				SetColor(12);
				gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				printf("X");
				gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				temp_1++;
			}
			if ((Check_Table[i][j]) == 2)
			{
				SetColor(10);
				gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				printf("O");
				gotoxy(Change_from_j_to_x(j), Change_from_i_to_y(i));
				temp_2++;
			}
		}
	}
	if (temp_1 > temp_2)
	{
		player = 2;
	}
	if(temp_1 < temp_2)
	{
		player = 1;
	}
}
void f2_Node(int Check_Table[][100], int n,int &x,int &y)
{
	system("cls");
	Creat_New_Table(n);

	if (n % 2 == 0)
	{
		x = 2 * n - 2;
		y = n - 1;

	}
	if (n % 2 != 0)
	{
		x = 2 * n;
		y = n;
	}
	gotoxy(x, y);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Check_Table[i][j] = 0;
		}
	}
}
