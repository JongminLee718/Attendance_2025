#include <iostream>
#include "user.h"
#include "grade.h"

using namespace std;

void soccerUser::SetUserData(std::string name, std::string weekday) {
	if (user.count(name) == 0) {
		user.insert({ name, ++userCnt });
		names[userCnt] = name;
	}
	SetSpecialDayCnt(weekday, user[name]);
	userWeekdayCnt[user[name]][GetWeekdayIdx(weekday)] += 1;
	userPoint[user[name]] += GetWeekdayPoint(weekday);
}

int soccerUser::GetWeekdayPoint(std::string& weekday)
{
	if (weekday == "monday" || weekday == "tuesday" || weekday == "thursday" || weekday == "friday") return 1;
	if (weekday == "saturday" || weekday == "sunday") return 2;
	if (weekday == "wednesday") return 3;
	return 0;
}

void soccerUser::SetSpecialPoint()
{
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		if (userWeekdayCnt[userIdx][WED] >= SPECIAL_DAY_TH) userPoint[userIdx] += SPECIAL_DAY_POINT;
		if (userWeekdayCnt[userIdx][SAT] + userWeekdayCnt[userIdx][SUN] >= SPECIAL_DAY_TH) userPoint[userIdx] += SPECIAL_DAY_POINT;
	}
}

void soccerUser::SetSpecialDayCnt(std::string& weekday, int curUser)
{
	if (weekday == "wednesday") wedCnt[curUser] += 1;
	if (weekday == "saturday" || weekday == "sunday") weekenCnt[curUser] += 1;
}

void soccerUser::SetUserGrade()
{
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		gradeFactory gradeFactory;
		grade* grade = gradeFactory.getGradeInstance(userPoint[userIdx]);
		userGrade[userIdx] = grade->getGrade();
	}
}

void soccerUser::PrintUserResult()
{
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		cout << "NAME : " << names[userIdx] << ", ";
		cout << "POINT : " << userPoint[userIdx] << ", ";
		cout << "GRADE : ";

		if (userGrade[userIdx] == GOLD) cout << "GOLD" << "\n";
		else if (userGrade[userIdx] == SILVER) cout << "SILVER" << "\n";
		else cout << "NORMAL" << "\n";
	}
}

void soccerUser::PrintRemovedPlayer()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		if (userGrade[userIdx] == NORMAL && wedCnt[userIdx] == 0 && weekenCnt[userIdx] == 0) {
			std::cout << names[userIdx] << "\n";
		}
	}
}