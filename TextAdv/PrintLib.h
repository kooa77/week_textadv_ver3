#pragma once

enum eStringType
{
	TEXT,
	BRANCH,
	QUIT,
};

struct sString
{
	eStringType type;
	char text[256];

	int selectY;
	int selectN;

	sString* prev;
	sString* next;
};

struct sParagraph
{
	sString* start;
	sString* current;
};

struct sParagraphList
{
	struct sParagraph* list;
	int count;
};

void InitString(sString* string, char* text, eStringType type);
void InitString(sString* string, char* text, eStringType type, int selectY, int selectN);
void AddStringToParagraph(sParagraph* paragraph, sString* string);
void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph);

int PrintParagraph(sParagraph* paragraph);

void PrintText(const char* text);
