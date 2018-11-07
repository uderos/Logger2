#pragma once

#include "logger_base.h"
#include "LoggerWriterStdio.h"

namespace udrlog
{

	using logger_stdout = logger_base<char, LoggerWriterStdio<char>>;
	using wlogger_stdout = logger_base<wchar_t, LoggerWriterStdio<wchar_t>>;

} // namespace udrlog
