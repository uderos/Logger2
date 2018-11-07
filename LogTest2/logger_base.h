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

		logger_base();
		logger_base(const logger_base & rv) = delete;
		// TODO logger_base(logger_base && rv);
		virtual ~logger_base();

		template <typename VALUE_T>
		logger_base<CHAR_T> & operator<<(const VALUE_T & value);

		static writer_ptr_t set_writer(writer_ptr_t writer_ptr);


	private:

		static writer_ptr_t m_writer_ptr;
		static string_t m_separator;

		bool m_has_data;
		std::basic_ostringstream<CHAR_T> m_ostream;

		string_t m_create_timestamp() const;
	};


template <typename CHAR_T>
logger_base<CHAR_T>::logger_base() : m_has_data(false)
{
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

	const auto ts = clock_t::now();

	return typename logger_base<CHAR_T>::string_t(); // UBEDEBUG - TODO
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


} // namespace udrlog
