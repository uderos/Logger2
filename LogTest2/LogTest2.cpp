// LogTest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "LoggerWriterStdio.h"


static void f_test01()
{
	udrlog::LoggerWriterStdio<char> lwc;
	udrlog::LoggerWriterStdio<wchar_t> lwwc;

	lwc.write(std::string("'char' message"));
	lwwc.write(std::wstring(L"'wchar' message"));
}



int main()
{
	f_test01();

    return 0;
}

