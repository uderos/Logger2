#pragma once

#include "logger_base.h"
#include "LoggerWriterStdio.h"

namespace udrlog
{

	using logger  = logger_base<char>;
	using wlogger = logger_base<wchar_t>;

} // namespace udrlog
