#pragma once

#include <wchar.h>

#define MAXIMUM_ROW 200

typedef struct CsvItem
{
	byte* RawData;
} CsvItem;

typedef struct CsvFile
{
	int32		ColumnCount;
	int32		RowCount;
	CsvItem*	Items[MAXIMUM_ROW];
} CsvFile;

typedef enum mainGame
{
	SCENE_NUMBER,
	STORY,
	CHOICE1,
	CHOICE1_MOVE,
	CHOICE1_SOUND,
	CHOICE2,
	CHOICE2_MOVE,
	CHOICE2_SOUND,
	CHOICE3,
	CHOICE3_MOVE,
	CHOICE3_SOUND,
	SOUND,
	IMAGE
}MAINGAME;



/// <summary>
/// CSV ������ �м��� CsvFile ��ü�� �����.
/// </summary>
/// <param name="csvFile">CsvFile ��ü</param>
/// <param name="filename">���� �̸�</param> 
void		CreateCsvFile(CsvFile* csvFile, const char* filename);

/// <summary>
/// CSV ��ü�� �ڿ��� �ݳ��Ѵ�.
/// </summary>
/// <param name="csvFile">CsvFile ��ü</param>
void		FreeCsvFile(CsvFile* csvFile);

/// <summary>
/// ���ڵ带 ������ �����´�.
/// </summary>
/// <param name="item">���ڵ�</param>
/// <returns></returns>
int32		ParseToInt(const CsvItem item);

/// <summary>
/// ���ڵ带 ���ڿ��� �����´�.
/// </summary>
/// <param name="item">���ڵ�</param>
/// <returns></returns>
char*		ParseToAscii(const CsvItem item);

/// <summary>
/// ���ڵ带 �����ڵ� ���ڿ��� �����´�.
/// </summary>
/// <param name="item">���ڵ�</param>
/// <returns></returns>
wchar_t*	ParseToUnicode(const CsvItem item);

void csv_Init(void);

wchar_t* StringLine(wchar_t* string, wchar_t* stringl);