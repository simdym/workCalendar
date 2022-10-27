#pragma once

#include <iostream>
#include <map>
#include <chrono>
#include "duration.h"


class DateTime {
	int year; //since year 0
	int month; //1 indexed
	int day, hour, min, sec;
	public:
		DateTime(int y, int m, int d, int hh, int mm, int ss) :
			year(y), month(m), day(d), hour(hh), min(mm), sec(ss) {}
		DateTime& operator + (const Duration& other) const;
		Duration& operator -  (const DateTime& other) const;
		bool operator < (const DateTime& other) const;
		bool operator > (const DateTime& other) const;
		int getYear() const { return year; }
		int getMonth() const { return month; }
		int getDay() const { return day; }
		int getHour() const { return hour; }
		int getMin() const { return min; }
		int getSec() const { return sec; }
		void addSeconds(int ss);
		void addMinutes(int mm);
		void addHours(int hh);
		void addDays(int d);
		void addMonths(int m);
		void addYears(int y);
		void subtractSeconds(int ss);
		void subtractMinutes(int mm);
		void subtractHours(int hh);
		void subtractDays(int d);
		void subtractMonths(int m);
		void subtractYears(int y);
		std::chrono::time_point<std::chrono::system_clock> toChrono() const;
		int daysSince(DateTime other) const;
		int hoursSince(DateTime other) const;
		int daysSinceSunday() const;
		void addWorkSeconds(int ss);
		void addWorkMinutes(int mm);
		void addWorkHours(int hh);
		void addWorkDays(int d);
		void subtractWorkSeconds(int ss);
		void subtractWorkMinutes(int mm);
		void subtractWorkHours(int hh);
		void subtractWorkDays(int d);
};

std::ostream& operator<<(std::ostream& stream, const DateTime& datetime);

bool isLeapYear(int year);
int daysInYear(int year);
int daysInMonth(int month, int year);
int isHoliday(int day, int month, int year); //TODO: Implement function
