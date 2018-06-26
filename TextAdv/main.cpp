#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "PrintLib.h"
#include "CSVLib.h"

using namespace std;

void Save(int select)
{
	FILE* fp = fopen("save.dat", "w+b");
	if (NULL != fp)
	{
		if (1 == fwrite(&select, sizeof(int), 1, fp))
		{
			printf("Save Success %d\n", select);
		}
		else
		{
			printf("Save Failed\n");
		}

		fclose(fp);
	}
	else
	{
		printf("File Open Error\n");
	}
}

int Load()
{
	FILE* fp = fopen("save.dat", "rb");
	if (NULL != fp)
	{
		int loadSelect = 0;
		if (1 == fread(&loadSelect, sizeof(int), 1, fp))
		{
			printf("Load Success %d\n", loadSelect);
		}
		else
		{
			printf("Load Failed\n");
		}
		fclose(fp);
		return loadSelect;
	}
	else
	{
		printf("File Open Error\n");
	}
	return 0;
}

int main(void)
{
	struct sParagraphList paragraphList;
	ParsingCSV("story.csv", &paragraphList);

	int select = 0;

	printf("Load Game? Y or N\n");
	char ch = _getche();
	if ('y' == ch || 'Y' == ch)
	{
		select = Load();
	}	

	while(true)
	{
		int nextSelect = 0;

		if(select < paragraphList.count)
		{
			printf("\n");
			nextSelect = PrintParagraph(&paragraphList.list[select]);
		}
		else
		{
			break;
		}

		if (nextSelect < 0)
		{
			break;
		}			
		else
		{
			select = nextSelect;
		}			
	}

	Save(select);

	for (int i = 0; i < paragraphList.count; i++)
	{
		paragraphList.list[i].current = paragraphList.list[i].start;
		while (NULL != paragraphList.list[i].current)
		{
			sString* nextString = paragraphList.list[i].current->next;
			free(paragraphList.list[i].current);
			paragraphList.list[i].current = nextString;
		}
	}
	free(paragraphList.list);
		
	return 0;
}
