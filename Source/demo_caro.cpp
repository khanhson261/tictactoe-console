// demo_caro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "caro_table.h"


int main()
{
	char background[][100] = {" CARO GAME","_New game","_Help","_Load Game","_About","_Exit"};
	char NewGame[][15] = { "_For 1 player","_For 2 players","_Back" };
	char Help[][1000] = { "For 1 player:","X - NPC","O - player - use arrow key to move up, down, right, left - use enter key to tick 'O'","For 2 players:","X - player 1 - use arrow key to move up, down, right, left - use enter key to tick 'X'","O - player 2 - use W, S, D, A key to move up, down, right, left - use enter key to tick 'O'","First player have to tick at the center table","_Back" };

	ROW row;
	row.Background = 1;
	int Check_Table[100][100];
	int player, player_first_turn;

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
	CONDITION condition;

	condition.Exist_Background = 0;
	condition.Exist_Help = 0;
	condition.Exist_Table = 0;

	int New_Game_regime = -1;
	int n = 15;
 	do
	{
		char key = _getch();
		if (key == -32 || key == 0)
		{
			key = _getch();
		}
		switch (key)
		{
		case UP:
		{
			if (row.Background >= 2 && condition.Exist_Background == 0 && condition.Exist_Table == 0)
			{
				gotoxy(0, row.Background);
				printf("%s\n", background[row.Background]);
				row.Background--;
				gotoxy(0, row.Background);
				SetColor(112);
				printf("%s\n", background[row.Background]);
				SetColor(7);
				gotoxy(0, row.Background);
			}
			if (row.New_Game >= 1 && condition.Exist_Background > 0 && condition.Exist_Table == 0)
			{
				gotoxy(0, row.New_Game);
				printf("%s\n", NewGame[row.New_Game]);
				row.New_Game--;
				gotoxy(0, row.New_Game);
				SetColor(112);
				printf("%s\n", NewGame[row.New_Game]);
				SetColor(7);
				gotoxy(0, row.New_Game);
			}
			break;
		}
		case DOWN:
		{
			if (row.Background > 0 && row.Background < 5 && condition.Exist_Background == 0 && condition.Exist_Table == 0)
			{
				gotoxy(0, row.Background);
				printf("%s\n", background[row.Background]);
				row.Background++;
				gotoxy(0, row.Background);
				SetColor(112);
				printf("%s\n", background[row.Background]);
				SetColor(7);
				gotoxy(0, row.Background);
			}
			if (row.New_Game >= 0 && row.New_Game <= 1 && condition.Exist_Background > 0 && condition.Exist_Table == 0)
			{
				gotoxy(0, row.New_Game);
				printf("%s\n", NewGame[row.New_Game]);
				row.New_Game++;
				gotoxy(0, row.New_Game);
				SetColor(112);
				printf("%s\n", NewGame[row.New_Game]);
				SetColor(7);
				gotoxy(0, row.New_Game);
			}
			break;
		}
		case ENTER:
		{
			//Background
			if (row.Background == 1 && condition.Exist_Background == 0 && condition.Exist_Table == 0)
			{
				system("cls");
				row.New_Game = 0;
				for (int i = 0; i < 3; i++)
				{
					if (i == row.New_Game)
					{
						SetColor(112);
						printf("%s\n", NewGame[i]);
						SetColor(7);
					}
					else
					{
						printf("%s\n", NewGame[i]);
					}
				}
				condition.Exist_Background = 1;

				break;
			}

			//New game
			if (row.New_Game == 0 && condition.Exist_Background > 0 && condition.Exist_Table == 0)
			{
				condition.Exist_Table++;
				New_Game_regime = 0;
				system("cls");
				do
				{
					printf("Nhap 1 neu muon danh truoc nhap 0 neu muon danh sau:");
					scanf_s("%d", &player_first_turn);
				} while (player_first_turn > 1 || player_first_turn < 0);
				system("cls");
				condition.Exist_Help = 0;
				playgame_NPC(Check_Table, n, player_first_turn, row, condition);
				break;
			}
			if (row.New_Game == 1 && condition.Exist_Background > 0 && condition.Exist_Table == 0)
			{
				condition.Exist_Table++;
				New_Game_regime = 1;
				system("cls");

				do
				{
					printf("Nhap 1 neu player 1 muon danh truoc nhap 2 neu player 2 muon danh truoc:");
					scanf_s("%d", &player);
				} while (player < 1 || player > 2);
				system("cls");
				condition.Exist_Help = 0;
				playgame(Check_Table, n, player, row, condition);
				break;
			}
			if (row.New_Game == 2 && condition.Exist_Background > 0 && condition.Exist_Table == 0)
			{
				system("cls");
				Creat_Background_Function(background, row, condition);

				break;
			}
			//Background
			if (row.Background == 2 && condition.Exist_Background == 0 && condition.Exist_Table == 0)
			{
				system("cls");
				Creat_Help_Function(Help, row, condition);
				break;
			}
			if (row.Help == 7 && condition.Exist_Background > 0)
			{
				if (condition.Exist_Table == 0)
				{
					system("cls");
					row.New_Game = 0;
					Creat_Background_Function(background, row, condition);
				}
				if (condition.Exist_Table > 0)
				{
					row.New_Game = -1;
					system("cls");
					if (New_Game_regime == 0)
					{
						row.New_Game = 0;
						Creat_Used_Table_Function(Check_Table, n, player, row, condition);
					}
					if (New_Game_regime == 1)
					{
						row.New_Game = 1;
						Creat_Used_Table_Function(Check_Table, n, player, row, condition);
					}
				}
				break;
			}


			if (row.Background == 3 && condition.Exist_Background == 0 && condition.Exist_Table == 0)
			{
				system("cls");
				printf("Chuc nang nay dang bi bug tam thoi chua tim ra cach sua vui long tao game moi roi bam F4 load game\n");
				printf("Press Esc to back");
				condition.Exist_Help = 1;
				/*ShowFileName();
				char* ChosenFile = new char[17];
				printf("Nhap ten file can mo: ");
				_flushall();
				InputString(ChosenFile);
				condition.Exist_Help = 1;
				LoadGame(ChosenFile, Check_Table, player);
				playgame(Check_Table, n, player, row, condition);*/
			}

			if (row.Background == 4 && condition.Exist_Background == 0 && condition.Exist_Table == 0)
			{
				system("cls");
				printf("- Game Genter: Logic Game\n");
				printf("- Devoloper: Tran Pham khanh Son\n");
				printf("+ University of Science\n");
				printf("+ Speciality: Information Technology\n");
				printf("+ 17CTT6 - 1712733\n");
				printf("- Devoloper: Nguyen Hoang Son\n");
				printf("+ University of Science\n");
				printf("+ Speciality: Information Technology\n");
				printf("+ 17CTT6 - 1712729\n");
				printf("\n   press esc to back");
			}

			if (row.Background == 5 && condition.Exist_Background == 0 && condition.Exist_Table == 0)
			{
				system("cls");
				return 0;
			}
			break;
		}
		case esc:
		{
			system("cls");
			SetColor(7);
			condition.Exist_Table = 0;
			Creat_Background_Function(background, row, condition);
			break;
		}
		case f1:
		{
			system("cls");
			SetColor(7);
			Creat_Help_Function(Help, row, condition);
			break;
		}
		case f2:
		{
			int decision;
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
			if (row.New_Game == 0)
			{
				do
				{
					printf("Nhap 1 neu muon danh truoc nhap 0 neu muon danh sau:");
					scanf_s("%d", &player_first_turn);
				} while (player_first_turn > 1 || player_first_turn < 0);
				system("cls");
				playgame_NPC(Check_Table, n, player_first_turn, row, condition);
			}
			if (row.New_Game == 1)
			{
				do
				{
					printf("Nhap 1 neu player 1 muon danh truoc nhap 2 neu player 2 muon danh truoc:");
					scanf_s("%d", &player);
				} while (player < 1 || player > 2);
				system("cls");
				playgame(Check_Table, n, player, row, condition);

			}
			break;
		}
		case f4:
		{
			system("cls");
			printf("Chuc nang nay dang bi bug tam thoi chua tim ra cach sua vui long tao game moi roi bam F4 load game\n");
			printf("Press Esc to back");
			break;
		}
		case f5:
		{
			system("cls");
			printf("- Game Genter: Logic Game\n");
			printf("- Devoloper: Tran Pham khanh Son\n");
			printf("+ University of Science\n");
			printf("+ Speciality: Information Technology\n");
			printf("+ 17CTT6 - 1712733\n");
			printf("-----------press esc to bac-----------");
			break;
		}
		default:
			break;
		}

	} while (1);
    return 0;
}

