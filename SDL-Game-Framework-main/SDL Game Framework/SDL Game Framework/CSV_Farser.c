#include "stdafx.h"
#include "Framework/Csv.h"
#include "CSV_farser.h"
#include "Framework/Csv.h"
#include "Framework/Scene.h"
#include "Framework/Image.h"
#include "Framework/Audio.h"


/// <summary>
/// 
/// </summary>
/// <param name="a">���ϸ�</param>
/// <param name="b">X��</param>
/// <param name="c">Y��</param>
/// <returns></returns>
/// 
char* csvfile = "GGAM.CSV";

void* csv_t(char* fileName, int x, int y)
{
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, fileName);

	char* str = ParseToUnicode(csvFile.Items[x][y]);
	return str;
}

//char* csv_s(MainSceneData )