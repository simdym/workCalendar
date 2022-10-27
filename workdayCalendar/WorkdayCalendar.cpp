#include "WorkdayCalendar.h"

using namespace std::chrono;

DateTime WorkdayCalendar::getEndDateTime(DateTime startDate, float fullDaysWorked)
{	
	int workingDays = (int)fullDaysWorked;
	int workingHours = (int)(8 * (fullDaysWorked - (int)fullDaysWorked));
	int workingMin = (int)(60 * (fullDaysWorked * 8 - (int)(fullDaysWorked * 8)));
	int workingSec = (int)(60 * (fullDaysWorked * 8 * 60 - (int)(fullDaysWorked * 8 * 60)));

	startDate.addWorkDays(workingDays);
	startDate.addWorkHours(workingHours);
	startDate.addWorkMinutes(workingMin);
	startDate.addWorkSeconds(workingSec);

	return startDate;
}

time_point<system_clock> WorkdayCalendar::toChrono(int y, int m, int d, int hh, int mm)
{
	std::tm tm_time = {
		/* .tm_sec  = */ 0,
		/* .tm_min  = */ mm,
		/* .tm_hour = */ hh,
		/* .tm_mday = */ d,
		/* .tm_mon  = */ m - 1,
		/* .tm_year = */ y - 1900,
	};
	return system_clock::from_time_t(std::mktime(&tm_time));
}