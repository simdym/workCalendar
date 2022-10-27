#pragma once

struct Duration {
	int year, month, day, hour, min, sec;
	public:
		Duration(int y, int m, int d, int hh, int mm, int ss) :
			year(y), month(m), day(d), hour(hh), min(mm), sec(ss) {}
};