#include "FileSockTrans.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <wchar.h>
#include <cassert>
using namespace std;




int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	INT32 a = 99;
	MEG_SF sfx;
	WCHAR Name[] = L"helloworld,from Ò¦í²ê¿";
		cout << lstrlenW(Name);
	assert( test_MEG_SF_Flat_mem(sfx));


	return 0;
}