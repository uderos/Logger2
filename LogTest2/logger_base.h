#pragma once

namespace udrlog
{

	template <typename CHAR_T, typename WRITER_T>
	class logger_base
	{
	public:

		using char_t = CHAR_T;
		using writer_t = WRITER_T;
		using string_t = std::basic_string<CHAR_T>;

		logger_base();
		logger_base(const logger_base & rv) = delete;
		// TODO logger_base(logger_base && rv);
		virtual ~logger_base();

		template <typename VALUE_T>
		logger_base<CHAR_T, WRITER_T> &
		operator<<(const VALUE_T & value);


	private:

		static WRITER_T m_writer;
		static string_t m_separator;

		bool m_has_data;
		std::basic_ostringstream<CHAR_T> m_ostream;

		string_t m_create_timestamp() const;
	};


template <typename CHAR_T, typename WRITER_T>
logger_base<CHAR_T, WRITER_T>::logger_base() : m_has_data(false)
{
}

template <typename CHAR_T, typename WRITER_T>
logger_base<CHAR_T, WRITER_T>::~logger_base()
{
	if (m_ostream)
		m_writer.write(m_ostream.str());
}

template <typename CHAR_T, typename WRITER_T>
typename logger_base<CHAR_T, WRITER_T>::string_t
logger_base<CHAR_T, WRITER_T>::m_create_timestamp() const
{
	using clock_t = std::chrono::system_clock;

	const auto ts = clock_t::now();
	const auto ts_c = clock_t::to_time_t(ts);
	
	typename logger_base<CHAR_T, WRITER_T>::string_t ts_str;
	ts_str = std::put_time(&ts_c, "%F %T");

	return ts_str;
}

template <typename CHAR_T, typename WRITER_T>
template <typename VALUE_T>
logger_base<CHAR_T, WRITER_T> & 
logger_base<CHAR_T, WRITER_T>::operator<<(const VALUE_T & value)
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
}


} // namespace udrlog
