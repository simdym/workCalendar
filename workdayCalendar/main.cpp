#include <iostream>

#include "DateTime.h"
#include "WorkdayCalendar.h"


int main() {
	WorkdayCalendar wc = WorkdayCalendar();
	DateTime date1 = DateTime(2022, 10, 29, 8, 0, 0);
	
	DateTime date2 = wc.getEndDateTime(date1, 4.5);
	std::cout << date2;

	int p;
	std::cin >> p;

	return 0;
}