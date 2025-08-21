#pragma once

#include "constants.h"
#include <string>
#include <map>

class soccerUser {
public:
	void SetUserData(std::string name, std::string weekday);
	void SetSpecialDayCnt(std::string& weekday, int curUser);
	void SetSpecialPoint();
	int GetWeekdayPoint(std::string& weekday);
	void SetUserGrade();
	void PrintUserResult();
	int PrintRemovedPlayer();
	int GetUserCnt();
	int GetUserGrade(std::string name);
	int GetUserPoint(std::string name);

private:
	std::map<std::string, int> user;
	int userCnt = 0;
	int userWeekdayCnt[MAX_USER][MAX_WEEKDAY];
	int userPoint[MAX_USER];
	int userGrade[MAX_USER];
	std::string names[MAX_USER];
	int wedCnt[MAX_USER];
	int weekenCnt[MAX_USER];

	int GetWeekdayIdx(std::string& weekday)
	{
		if (weekday == "monday") return MON;
		if (weekday == "tuesday") return TUE;
		if (weekday == "wednesday") return WED;
		if (weekday == "thursday") return THU;
		if (weekday == "friday") return FRI;
		if (weekday == "saturday") return SAT;
		if (weekday == "sunday") return SUN;
		return 0;
	}
};