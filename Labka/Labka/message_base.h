#ifndef _MESSAGE_BASE_
#define _MESSAGE_BASE_
#include "pch.h"

typedef unsigned int uint;
typedef const unsigned int cuint;

class message_base
{
private:
	class data_msg
	{
	private:
		class date_time
		{
		private:
			uint year, month, day, hours, minutes;

			static bool leap(cuint &year);
			static bool check_day(cuint &year, cuint &month, cuint &day);
			static bool check_date(cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes);
			bool check_date() const;

		public:

			date_time();
			date_time(cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes);

			void set_date(cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes);

			void rand_date();

			void date_bin_out(std::ostream& fout) const;
			void date_bin_in(std::istream& fin);

			bool operator==(const date_time &other_date) const;
			bool operator>(const date_time &other_date) const;
			bool operator<(const date_time &other_date) const;

			std::ostream& operator<<(std::ostream& out) const;
			std::istream& operator>>(std::istream& in);

			friend data_msg;
			friend message_base;
			friend void interactive();
			friend void demo();
			friend void benchmark_binary();
			friend void benchmark_text();
		};

		std::string message;
		date_time date;
		uint priority, type;
		double system_loading;

	public:

		data_msg();
		data_msg(const std::string &message);
		data_msg(const std::string &message, cuint &type, cuint &priority, const double &system_loading, cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes);

		void set_data_msg(const std::string &message, cuint &type, cuint &priority, const double &system_loading, cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes);

		void rand_msg();

		void bin_out_msg(std::ostream& fout) const;
		void bin_in_msg(std::istream& fin);

		std::ostream& operator<<(std::ostream& out) const;
		std::istream& operator>>(std::istream& in);
		
		friend message_base;
		friend void interactive();
		friend void demo();
		friend void benchmark_binary();
		friend void benchmark_text();
	};

	std::vector<data_msg> list;

public:

	message_base();

	void create_rand_list(cuint &n);
	void insert(const data_msg &new_message);
	void pop_back();
	void pop_for_message(const std::string &message);
	void modificate_message(const std::string &old_message, const std::string &new_message);
	
	void bin_out() const;
	void bin_in();
	void bin_out(std::fstream &fios) const;
	void bin_in(std::fstream &fios);

	message_base* search_for_time_interval
	(const data_msg::date_time &date1, const data_msg::date_time &date2) const;

	message_base* search_for_type_and_system_loading
	(cuint &type, const double &system_loading) const;

	message_base* search_for_fragment
	(const std::string &fragment) const;

	friend std::ostream& operator<<(std::ostream &out, const message_base &base);
	friend std::istream& operator>>(std::istream &fin, message_base &base);
	friend void interactive();
	friend void demo();
	friend void benchmark_binary();
	friend void benchmark_text();
};
#endif /* _MESSAGE_BASE_ */