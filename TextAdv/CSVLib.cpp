#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PrintLib.h"
#include "CSVLib.h"

int CalcParagraphCount(FILE* fp)
{
	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);

	int prevParagraphIndex = -1;
	int count = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		char* token = strtok(record, ",");	// 문단 번호
		int paragraphIndex = atoi(token);

		if (paragraphIndex != prevParagraphIndex)
		{
			prevParagraphIndex = paragraphIndex;
			count++;
		}
	}

	// 다시 처음부터 시작하기 위한 초기화
	fseek(fp, 0, SEEK_SET);

	return count;
}

void ParsingCSV(const char* fileName, sParagraphList* paragraphList)
{
	FILE* fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("\nError : File Not Open!");
		return;
	}

	paragraphList->count = CalcParagraphCount(fp);
	paragraphList->list = (sParagraph*)malloc((paragraphList->count) * sizeof(sParagraph));

	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);

	int prevParagraphIndex = -1;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;
		
		char* token = strtok(record, ",");	// 문단 번호
		int paragraphIndex = atoi(token);

		token = strtok(NULL, ",");	// 타입
		eStringType type = (eStringType)atoi(token);
		
		token = strtok(NULL, ",");	// 대사
		char* text = token;

		token = strtok(NULL, ",");	// Y 선택지
		int selectY = atoi(token);

		token = strtok(NULL, ",");	// N 선택지
		int selectN = atoi(token);

		if (paragraphIndex != prevParagraphIndex)
		{
			prevParagraphIndex = paragraphIndex;

			paragraphList->list[prevParagraphIndex].current = NULL;
		}

		sString* newString = (sString*)malloc(sizeof(sString));
		InitString(newString, text, type, selectY, selectN);
		AddStringToParagraph(&paragraphList->list[paragraphIndex], newString);
	}

	fclose(fp);
}