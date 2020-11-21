#include "FileSockTrans.h"
#include <cassert>
#include <stdlib.h>
int File_Name_To_MEG_SF(MEG_SF& msg, WCHAR* FileName)
{
	int FileNameLength = lstrlenW(FileName)+1;

	msg.FileStaticLen = Offsetof(MEG_SF, FileName);
	msg.LENGTH=FileNameLength*sizeof(WCHAR);//LEG==40
	auto temp = (WCHAR*)malloc(msg.LENGTH);
	memcpy(temp, FileName, msg.LENGTH);
	msg.FileName = temp;
	msg.LENGTH += msg.FileStaticLen;
	return msg.LENGTH;
}

char* MEG_SF2FlatMem(MEG_SF &msg)
{
	int temp = (int)msg.LENGTH;
	char* ret = (char*)malloc(temp);
	memcpy(ret, &msg, msg.FileStaticLen);
	int size = (msg.LENGTH - msg.FileStaticLen);
	memcpy(ret + msg.FileStaticLen, msg.FileName,size);
	return ret;
}

MEG_SF* FlatMem2Meg_SF(char* msg)
{ 
	MEG_SF* ret = (MEG_SF*)malloc(sizeof(MEG_SF)) ;
	memcpy(ret, msg, Offsetof(MEG_SF, FileName));
	if (ret->type != SendFile)
		exit(1);
	WCHAR* fileName = (WCHAR*)malloc(ret->LENGTH-ret->FileStaticLen);
	ret->FileName = fileName;
	int a = (int)(ret->LENGTH - ret->FileStaticLen);
	char* sourse = msg + ret->FileStaticLen;
	memcpy(fileName,sourse ,a );
	return ret;

}

bool test_MEG_SF_Flat_mem(MEG_SF msg)
{
	wchar_t man;
	WCHAR Name[] = L"helloworld,from Ò¦í²ê¿";
	File_Name_To_MEG_SF(msg, (WCHAR*)Name);
	auto chr = MEG_SF2FlatMem(msg);
	MEG_SF* ans = FlatMem2Meg_SF(chr);
	if (ans->type == SendFile && ans->LENGTH == msg.LENGTH && ans->FileStaticLen == msg.FileStaticLen)
	{
		printf("%ls", ans->FileName);
		return true;
	}

}