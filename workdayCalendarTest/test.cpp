#include "pch.h"
#include <iostream>

#include "workdayCalendar.h"
#include "Duration.h"
#include "DateTime.h"

TEST(leapYearTest, yearDivisbleBy4) {
	EXPECT_EQ(isLeapYear(2020), true);
	EXPECT_TRUE(true);
};

TEST(leapYearTest, yearDivisbleBy100) {
	EXPECT_EQ(isLeapYear(2100), false);
	EXPECT_TRUE(true);
};

TEST(leapYearTest, yearDivisbleBy400) {
	EXPECT_EQ(isLeapYear(2100), true);
	EXPECT_TRUE(true);
};

TEST(leapYearTest, notLeapYear) {
	EXPECT_EQ(isLeapYear(2001), false);
	EXPECT_TRUE(true);
};

TEST(daysInYears, leapYear) {
	EXPECT_EQ(daysInYear(2021), 365);
	EXPECT_TRUE(true);
}

TEST(daysInYears, notLeapYear) {
	EXPECT_EQ(daysInYear(2020), 366);
	EXPECT_TRUE(true);
}

TEST(daysInMonths, randomMonthLeapYear) {
	EXPECT_EQ(daysInMonth(5, 2020), 31);
	EXPECT_TRUE(true);
}

int main(int argc, char* argv[]) {

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}