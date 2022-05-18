#include "stdafx.h"
#include "Framework/Csv.h"
#include "CSV_farser.h"
#include "Framework/Csv.h"

/// <summary>
/// 
/// </summary>
/// <param name="a">파일명</param>
/// <param name="b">X값</param>
/// <param name="c">Y값</param>
/// <returns></returns>
/// 
char* csvfile = "qqqq.CSV";

void* csv_t(char* fileName, int x, int y)
{
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, fileName);

	char* str = ParseToUnicode(csvFile.Items[x][y]);
	return str;
}
