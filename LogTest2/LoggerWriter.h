#pragma once

namespace udrlog
{
	template <typename CHAR_T>
	class LoggerWriter
	{
	public:

		using string_t = std::basic_string<CHAR_T>;

		LoggerWriter() = default;
		LoggerWriter(const LoggerWriter & rv) = delete;
		LoggerWriter(LoggerWriter && rv) = default;

		virtual ~LoggerWriter() = default;

		virtual void write(const string_t & msg) = 0;
	};

} // namespace

