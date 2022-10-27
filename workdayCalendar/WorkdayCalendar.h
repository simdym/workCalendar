#pragma once
#include <chrono>
#include "DateTime.h"

using namespace std::chrono;

class WorkdayCalendar
{
	public:
		DateTime getEndDateTime(DateTime startDate, float fullDaysWorked);
		time_point<system_clock> toChrono(int y, int m, int d, int hh, int mm);
};
