// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma pack (1)
#include "targetver.h"
#include "stdlib.h"
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "conio.h"
#include "string.h"
#include "time.h"




// TODO: reference additional headers your program requires here
#include"caro_table.h"
#define W   119 
#define S 115  
#define A   97   
#define D   100 
#define ENTER 13
#define SPACE 32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define esc 27
#define f1 59
#define f2 60
#define f3 61
#define f4 62
#define f5 63

typedef struct CARO
{
	char type[3];
	int  sizegame;
	int  caro_matrix[1000];
};
typedef struct ROW
{
	int Background;
	int New_Game;
	int Help;
};
typedef struct CONDITION
{
	int Exist_Background;
	int Exist_New_Game;
	int Exist_Help;
	int Exist_Table;
	int End;
};


