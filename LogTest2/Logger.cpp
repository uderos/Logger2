#include "stdafx.h"

#include "Logger.h"


namespace udrlog
{
	std::shared_ptr<logger::writer_t>  logger::m_writer_ptr;
	std::shared_ptr<wlogger::writer_t> wlogger::m_writer_ptr;

	logger::string_t  logger::m_separator("|");
	wlogger::string_t wlogger::m_separator(L"#");

} // namespace udrlog
