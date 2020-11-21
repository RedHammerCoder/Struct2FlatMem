#pragma once
#include <windows.h>
#include <string>
#include <memory>
#include <stdlib.h>

using namespace std;


#define Offsetof(TYPE, MEMBER) ((int)(&((TYPE *)0)->MEMBER))

#pragma pack(4)
enum  MsgType:DWORD
{
	SendFile=0,//C 2 S and S 2 C  have file
	RequestFileList,//C 2 S FileList
	SendFileNameList,//S 2 C charlist
	Error_Name_Repeat,//client send file and name repeat 
	Error_No_Such_File//Client request a file and no such file in server
	

	
};

struct MEG_SF
{
	MsgType type = SendFile;
	INT32 LENGTH;
	INT32 FileStaticLen;
	WCHAR* FileName;

};
int File_Name_To_MEG_SF(MEG_SF& msg, WCHAR* FileName);
char* MEG_SF2FlatMem(MEG_SF&);
MEG_SF* FlatMem2Meg_SF(char* meg);
bool test_MEG_SF_Flat_mem(MEG_SF msg);


struct ReqFileList
{
	MsgType type = RequestFileList;
};
struct SendFileName
{
	MsgType type = SendFileNameList;
		
};
struct Back_Name_repeat
{
	MsgType type = Error_Name_Repeat;
};
struct Back_N0_Such_File
{
	MsgType type = Error_No_Such_File;
};