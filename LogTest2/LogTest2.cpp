// LogTest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Logger.h"
#include "LoggerWriterStdio.h"


static void f_test01()
{
	std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;
	udrlog::LoggerWriterStdio<char> lwc;
	udrlog::LoggerWriterStdio<wchar_t> lwwc;

	lwc.write(std::string("'char' message"));
	lwwc.write(std::wstring(L"'wchar' message"));
}

static void f_test02()
{
	std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

	udrlog::logger::set_writer(std::make_shared<udrlog::LoggerWriterStdio<char>>());

	udrlog::logger l;

	const int a = 1;
	const int b = 2;
	const double c = 0.1 * (a + b);

	l << "a=" << a;
	l << " b=" << b << " c=" << c;
}


int main()
{
	f_test01();
	f_test02();

    return 0;
}

