#include "time_util.h"

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

/*
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
*/