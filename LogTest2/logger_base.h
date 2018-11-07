#pragma once

#include "LoggerWriter.h"

namespace udrlog
{

	template <typename CHAR_T>
	class logger_base
	{
	public:

		using char_t = CHAR_T;
		using writer_t = LoggerWriter<CHAR_T>;
		using writer_ptr_t = std::shared_ptr<writer_t>;
		using string_t = std::basic_string<CHAR_T>;
		using ostringstream_t = std::basic_ostringstream<CHAR_T>;

		logger_base();
		logger_base(const logger_base & rv) = delete;
		logger_base(logger_base && rv);
		virtual ~logger_base();

		template <typename VALUE_T>
		logger_base<CHAR_T> & operator<<(const VALUE_T & value);

		static writer_ptr_t set_writer(writer_ptr_t writer_ptr);
		static logger_base<CHAR_T> create_instance();


	private:

		static writer_ptr_t m_writer_ptr;
		static string_t m_separator;

		bool m_has_data;
		ostringstream_t m_ostream;

		string_t m_create_timestamp() const;
	};


template <typename CHAR_T>
logger_base<CHAR_T>::logger_base() : m_has_data(false)
{
}

template <typename CHAR_T>
logger_base<CHAR_T>::logger_base(logger_base<CHAR_T> && rv)
{
	m_has_data = rv.m_has_data;
	m_ostream = std::move(rv.m_ostream);

	rv.m_has_data = false;
}

template <typename CHAR_T>
logger_base<CHAR_T>::~logger_base()
{
	if (m_has_data && m_writer_ptr.get())
		m_writer_ptr->write(m_ostream.str());
}

template <typename CHAR_T>
typename logger_base<CHAR_T>::string_t
logger_base<CHAR_T>::m_create_timestamp() const
{
	using clock_t = std::chrono::system_clock;
	const auto now = clock_t::now();

	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm;
	localtime_s(&now_tm, &now_c);

	constexpr CHAR_T ZERO('0');
	ostringstream_t oss;
	oss << std::setfill(ZERO) << std::setw(4) << now_tm.tm_year + 1900
		<< std::setfill(ZERO) << std::setw(2) << now_tm.tm_mon + 1
		<< std::setfill(ZERO) << std::setw(2) << now_tm.tm_mday
		<< m_separator
		<< std::setfill(ZERO) << std::setw(2) << now_tm.tm_hour
		<< std::setfill(ZERO) << std::setw(2) << now_tm.tm_min
		<< std::setfill(ZERO) << std::setw(2) << now_tm.tm_sec;

	return oss.str();
}

template <typename CHAR_T>
typename logger_base<CHAR_T>::writer_ptr_t 
logger_base<CHAR_T>::set_writer(writer_ptr_t writer_ptr)
{
	typename logger_base<CHAR_T>::writer_ptr_t old_writer_ptr = m_writer_ptr;
	m_writer_ptr = writer_ptr;
	return old_writer_ptr;
}


template <typename CHAR_T>
template <typename VALUE_T>
logger_base<CHAR_T> & 
logger_base<CHAR_T>::operator<<(const VALUE_T & value)
{
	if (!m_has_data)
	{
		m_has_data = true;

		m_ostream	<< m_create_timestamp() << m_separator << value;
	}
	else
	{
		m_ostream << m_separator << value;
	}

	return (*this);
}

template <typename CHAR_T>
logger_base<CHAR_T> 
logger_base<CHAR_T>::create_instance()
{
//	return std::move(logger_base<CHAR_T>());
	return logger_base<CHAR_T>();
}


} // namespace udrlog
