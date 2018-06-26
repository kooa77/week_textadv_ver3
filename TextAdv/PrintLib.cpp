#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "PrintLib.h"


void InitString(sString* string, char* text, eStringType type)
{
	strcpy(string->text, text);
	string->type = type;
}

void InitString(sString* string, char* text, eStringType type, int selectY, int selectN)
{
	InitString(string, text, type);
	string->selectY = selectY;
	string->selectN = selectN;
}

void AddStringToParagraph(sParagraph* paragraph, sString* string)
{
	if (NULL == paragraph->current)
	{
		// 첫번 째 노드이면 시작 노드 부터 시작
		paragraph->current = string;
		string->prev = NULL;
		string->next = NULL;

		paragraph->start = string;
	}
	else
	{
		paragraph->current->next = string;
		string->prev = paragraph->current;
		string->next = NULL;
		paragraph->current = string;
	}
}

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph)
{
	paragraphList->list[paragraphList->count] = *paragraph;
	paragraphList->count++;
}

int PrintParagraph(sParagraph* paragraph)
{
	paragraph->current = paragraph->start;
	while(NULL != paragraph->current)
	{
		switch (paragraph->current->type)
		{
		case eStringType::TEXT:
			PrintText(paragraph->current->text);
			break;
		case eStringType::BRANCH:	// 분기를 처리 해야 할 타입
			PrintText(paragraph->current->text);

			while (true)
			{
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return paragraph->current->selectY;
				}
				else if ('n' == ch || 'N' == ch)
				{
					return paragraph->current->selectN;
				}
				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;
				}
			}
			break;

		case eStringType::QUIT:
			PrintText(paragraph->current->text);
			return -1;
		}

		paragraph->current = paragraph->current->next;
	}

	return 0;
}

void PrintText(const char* text)
{
	printf(text);
	printf("\n");
}
