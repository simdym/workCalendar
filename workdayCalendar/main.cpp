#include <iostream>

#include "DateTime.h"
#include "WorkdayCalendar.h"


int main() {
	WorkdayCalendar wc = WorkdayCalendar();


	DateTime date1 = DateTime(2022, 10, 29, 15, 23, 34);
	DateTime date2 = DateTime(2022, 2, 28, 15, 23, 34);

	//wc.getEndDateTime(date1, (float)5.32);
	std::cout << "Start" << std::endl;
	std::cout << date1 << std::endl;
	date1.subtractWorkHours(8);
	std::cout << date1 << std::endl;
	date1.subtractWorkDays(5);
	std::cout << date1 << std::endl;
	//date1.subtractWorkHours(465);
	//std::cout << date1 << std::endl;


	std::cout << "Date before" << std::endl;
	std::cout << date1.daysSince(date2) << std::endl;

	std::cout << "Days since sunday" << std::endl;
	std::cout << date2.daysSinceSunday() << std::endl;

	int p = 3;
	std::cin >> p;

	return 0;
}