#pragma once
#include "LoggerWriter.h"

namespace udrlog
{
	template <typename CHAR_T>
	class LoggerWriterStdio : public LoggerWriter<CHAR_T>
	{
	public:
		using string_t = std::basic_string<CHAR_T>;

		LoggerWriterStdio() = default;
		LoggerWriterStdio(LoggerWriterStdio && rv) = default;
		virtual ~LoggerWriterStdio() = default;

		virtual void write(const string_t & msg);
	};


	namespace internal
	{
		template <typename CHAR_T> struct cout_trait;

		template <> struct cout_trait<char>
		{
			using type = decltype(std::cout);
			static constexpr type & cout() { return std::cout; };
			static constexpr type & cerr() { return std::cerr; };
			static constexpr type & clog() { return std::clog; };
		};

		template <> struct cout_trait<wchar_t>
		{
			using type = decltype(std::wcout);
			static constexpr type & cout() { return std::wcout; };
			static constexpr type & cerr() { return std::wcerr; };
			static constexpr type & clog() { return std::wclog; };
		};
	}; // namespace internal
		
	template <typename CHAR_T>
	void LoggerWriterStdio<CHAR_T>::write(
		const typename LoggerWriterStdio<CHAR_T>::string_t & msg)
	{
		auto & outstream(internal::cout_trait<CHAR_T>::cout());
		outstream << msg << std::endl;
	}

} // namespace udrlog

