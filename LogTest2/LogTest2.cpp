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

	l << "a" << a;
	l << "b" << b << "c" << c;
}

static void f_test03()
{
	std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

	udrlog::logger::set_writer(std::make_shared<udrlog::LoggerWriterStdio<char>>());

	udrlog::logger l1;

	const int a = 1;
	const int b = 2;
	const double c = 0.1 * (a + b);

	l1 << "a" << a;
	l1 << "b" << b << "c" << c;

	udrlog::logger l2(std::move(l1));
	l2 << "L2";
}

static void f_test04()
{
	std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

	udrlog::logger::set_writer(std::make_shared<udrlog::LoggerWriterStdio<udrlog::logger::char_t>>());
	udrlog::wlogger::set_writer(std::make_shared<udrlog::LoggerWriterStdio<udrlog::wlogger::char_t>>());

	udrlog::logger::create_instance() << "Hello" << 1 << 2;

	UDR_LOG << "Hello" << 3.3 << 4.4;

	int x = 0;
	UDR_WLOG << L"HELLO" << (&x) << 9.9;
}

int main()
{
	f_test01();
	f_test02();
	f_test03();
	f_test04();

    return 0;
}

