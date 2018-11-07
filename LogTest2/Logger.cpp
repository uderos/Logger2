#include "stdafx.h"

#include "Logger.h"


namespace udrlog
{
	logger_stdout::writer_t logger_stdout::m_writer;
	logger_stdout::string_t logger_stdout::m_separator("|");

	wlogger_stdout::writer_t wlogger_stdout::m_writer;
	wlogger_stdout::string_t wlogger_stdout::m_separator(L"#");

} // namespace udrlog
