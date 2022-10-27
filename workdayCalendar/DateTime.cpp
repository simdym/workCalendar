#include "DateTime.h"

std::ostream& operator<<(std::ostream& stream, const DateTime& datetime) {
	stream << datetime.getYear() << ':' << datetime.getMonth() << ':' << datetime.getDay() << ':'
		<< datetime.getHour() << ':' << datetime.getMin() << ':' << datetime.getSec();
	return stream;
}

bool DateTime::operator < (const DateTime& other) const {
	if (year == other.getYear()) {
		if (month == other.getMonth()) {
			if (day == other.getDay()) {
				if (hour == other.getHour()) {
					if (min == other.getMin()) {
						return sec < other.getSec();
					}
					else {
						return min < other.getMin();
					}
				}
				else {
					return hour < other.getHour();
				}
			}
			else {
				return day < other.getDay();
			}
		}
		else {
			return month < other.getMonth();
		}
	}
	else {
		return year < other.getYear();
	}
}

bool DateTime::operator > (const DateTime& other) const {
	if (year == other.getYear()) {
		if (month == other.getMonth()) {
			if (day == other.getDay()) {
				if (hour == other.getHour()) {
					if (min == other.getMin()) {
						return sec > other.getSec();
					}
					else {
						return min > other.getMin();
					}
				}
				else {
					return hour > other.getHour();
				}
			}
			else {
				return day > other.getDay();
			}
		}
		else {
			return month > other.getMonth();
		}
	}
	else {
		return year > other.getYear();
	}
}

DateTime& DateTime::operator + (const Duration& other) const {
	DateTime sum = DateTime(0, 0, 0, 0, 0, 0);
	sum.addYears(other.year);
	sum.addMonths(other.month);
	sum.addDays(other.day);
	sum.addHours(other.hour);
	sum.addMinutes(other.min);
	sum.addSeconds(other.sec);

	return sum;
}

/*dateTime& dateTime::operator - (const duration& other) const {
	dateTime sum = dateTime(0, 0, 0, 0, 0, 0);
	sum.subtractYears(other.year);
	sum.subtractMonths(other.month);
	sum.subtractDays(other.day);
	sum.subtractHours(other.hour);
	sum.subtractMinutes(other.min);
	sum.subtractSeconds(other.sec);

	return sum;
}*/

void DateTime::addSeconds(int ss) {
	sec += ss - ((ss + sec) / 60) * 60;
	addMinutes((ss + sec) / 60);
}

void DateTime::addMinutes(int mm) {
	min += mm - ((mm + min) / 60) * 60;
	addHours((mm + min) / 60);
}

void DateTime::addHours(int hh) {
	hour += hh - ((hh + hour) / 24) * 24;
	addDays((hh + hour) / 24);
}

void DateTime::addDays(int d) {
	day += d;
	while (daysInMonth(month, year) < day) {
		day -= daysInMonth(month, year);
		addMonths(1);
	}
}

void DateTime::addMonths(int m) {
	month += m;
	while (12 < month) {
		addYears(1);
		month -= 12;
	}
}
void DateTime::addYears(int y) {
	year += y;
}

void DateTime::subtractSeconds(int ss) {
	sec -= ss;
	if (0 < (ss - sec)) {
		sec += ((-sec) / 60) * 60 + 60;
		subtractMinutes(((-sec) / 60) +1);
	}
}

void DateTime::subtractMinutes(int mm) {
	min -= mm;
	if (0 < (mm - min)) {
		min += ((-min) / 60) * 60 + 60;
		subtractHours(((-min) / 60) + 1);
	}
}

void DateTime::subtractHours(int hh) {
	hour -= hh;
	if (0 < (hh - hour)) {
		hour += ((-hour) / 24) * 24 + 24;
		subtractDays(((-hour) / 60) + 1);
	}
}

void DateTime::subtractDays(int d) {
	day -= d;
	while (day < 1) {
		subtractMonths(1);
		day += daysInMonth(month, year);
	}
}

void DateTime::subtractMonths(int m) {
	month -= m;
	if (0 < (m - month)) {
		 month += ((-month) / 12) * 12 + 12;
		 subtractYears(1);
	}
	if (day > daysInMonth(month, year)) {
		day = daysInMonth(month, year); //In case there are fewer days in the month than the date
	}
}

void DateTime::subtractYears(int y) {
	year -= y;
}

std::chrono::time_point<std::chrono::system_clock> DateTime::toChrono() const {
	std::tm tm_time = {
		/* .tm_sec  = */ sec,
		/* .tm_min  = */ min,
		/* .tm_hour = */ hour,
		/* .tm_mday = */ day,
		/* .tm_mon  = */ month - 1,
		/* .tm_year = */ year - 1900,
	};
	return std::chrono::system_clock::from_time_t(std::mktime(&tm_time));
}

int DateTime::daysSinceSunday() const {
	DateTime sundayDate = DateTime(2022, 10, 23, 12, 0, 0);
	int daysSinceDate = daysSince(sundayDate);
	if (daysSinceDate < 0) { return 7 - (daysSinceDate % 7); }
	else { return daysSinceDate % 7; }
}

bool isLeapYear(int year) {
	if ((year % 4 == 0 && year % 400 != 0) || year % 400 == 0) {
		return true;
	}
	else {
		return false;
	}
}

int daysInYear(int year) {
	return 365 + (int)isLeapYear(year);
}

int daysInMonth(int month, int year) {
	std::map<int, int> monthAndDay = {
		{1,31},
		{2,28},
		{3,31},
		{4,30},
		{5,31},
		{6,30},
		{7,31},
		{8,31},
		{9,30},
		{10,31},
		{11,30},
		{12,31}
	};
	if (month == 2) {
		return monthAndDay[month] + (int)isLeapYear(year);
	}
	else {
		return monthAndDay[month];
	}
}

int DateTime::daysSince(DateTime other) const {
	int daysSince = 0;
	if ((*this) > other) {
		while (year != other.getYear() || month != other.getMonth() || day != other.getDay()) {
			other.addDays(1);
			daysSince++;
		}
		return daysSince;
	}
	else {
		while (year != other.getYear() || month != other.getMonth() || day != other.getDay()) {
			other.subtractDays(1);
			daysSince++;
		}
		return daysSince;
	}
}

int DateTime::hoursSince(DateTime other) const {
	int hoursSince = 0;

	if ((*this) > other) {
		while (year != other.getYear() || month != other.getMonth()
			|| day != other.getDay() || hour != other.getHour()) {
			other.addHours(1);
			hoursSince++;
		}
		return hoursSince;
	}
	else {
		while (year != other.getYear() || month != other.getMonth() || day != other.getDay()) {
			other.subtractHours(1);
			hoursSince--;
		}
		return hoursSince;
	}
}

void DateTime::addWorkSeconds(int ss) {
	sec += ss - ((ss + sec) / 60) * 60;
	addWorkMinutes((ss + sec) / 60);
}

void DateTime::addWorkMinutes(int mm) {
	min += mm - ((mm + min) / 60) * 60;
	addWorkHours((mm + min) / 60);
}

void DateTime::addWorkHours(int hh) {
	if (hour < 8) { //Before worktime set to 8 o'clock before adding
		hour = 8;
		min = 0;
		sec = 0;
		addHours(hh % 8);
		addWorkDays(hh / 8);
	}
	else if (hour > 16) { //After worktime set to 8 o'clock the next day before adding
		hour = 8;
		min = 0;
		sec = 0;
		addWorkDays(1);

		addHours(hh % 8);
		addWorkDays(hh / 8);
	}
	else {
		if (16 < hour + (hh % 8)) {
			subtractHours((hh % 8) + 16);
		}
		else {
			subtractHours((hh % 8));
		}
	}
}

void DateTime::addWorkDays(int d) {
	int sinceSunday = daysSinceSunday();
	std::cout << sinceSunday << std::endl;
	if (sinceSunday == 6) { //Saturday
		sinceSunday = 1;
		addDays(2);
		hour = 8;
		min = 0;
		sec = 0;
	}
	else if (sinceSunday == 0) { //Sunday
		sinceSunday = 1;
		addDays(1);
		hour = 8;
		min = 0;
		sec = 0;
	}
	std::cout << "Test:: " << sinceSunday + (d % 5) << std::endl;
	if (sinceSunday + (d % 5) <= 5) {
		addDays(d % 5);
		std::cout << "Added days" << d % 5 << std::endl;
	}
	else {
		addDays(d % 5 + 2);
		std::cout << "Added days" << d % 5 + 2 << std::endl;
	}
	addDays(7 * (d / 5));
}

void DateTime::subtractWorkSeconds(int ss) {
	sec -= ss;
	if (0 < (ss - sec)) {
		sec += ((-sec) / 60) * 60 + 60;
		subtractMinutes(((-sec) / 60) + 1);
	}
}

void DateTime::subtractWorkMinutes(int mm) {
	min -= mm;
	if (0 < (mm - min)) {
		min += ((-min) / 60) * 60 + 60;
		subtractWorkHours(((-min) / 60) + 1);
	}
}


void DateTime::subtractWorkHours(int hh) {
	if (hour < 8) { //Before worktime set to 16 o'clock previous day subtracting adding
		subtractWorkDays(1);
		hour = 16;
		min = 0;
		sec = 0;

		subtractHours(hh % 8);
	}
	else if (hour > 16) { //After worktime set to 16 o'clock the next day before adding
		hour = 16;
		min = 0;
		sec = 0;

		subtractHours(hh % 8);
	}
	else { //In work hour
		if (hour - (hh % 8) < 8) {
			subtractHours((hh % 8) + 16);
		}
		else {
			std::cout << "Checkpoint 2\n";
			subtractHours((hh % 8));
		}
	}
	subtractWorkDays(hh / 8);
}

void DateTime::subtractWorkDays(int d) {
	int sinceSunday = daysSinceSunday();
	if (sinceSunday == 6) { //Saturday
		sinceSunday = 5;
		subtractDays(1);
		hour = 16;
		min = 0;
		sec = 0;
	}
	else if (sinceSunday == 0) { //Sunday
		sinceSunday = 5;
		subtractDays(2);
		hour = 16;
		min = 0;
		sec = 0;
	}
	else { //Weekday
		if (sinceSunday - (d % 5) == 0 || sinceSunday - (d % 5) == 6) {
			subtractDays(d % 5 + 2);
		}
		else {
			subtractDays(d % 5);
		}
	}
	subtractDays(7 * (d / 5));
}

int isHoliday(int day, int month, int year) { return true; }