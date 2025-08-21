#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

enum {
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
};

map<string, int> user;
int userCnt = 0;
static const int MAX_USER = 100;
static const int MAX_WEEKDAY = 7;
static const int MAX_INPUT = 500;

//dat[사용자ID][요일]
int userWeekdayCnt[MAX_USER][MAX_WEEKDAY];
int points[MAX_USER];
int grade[MAX_USER];
string names[MAX_USER];

int wedCnt[MAX_USER];
int weekenCnt[MAX_USER];

const int GOLD = 1;
const int SILVER = 2;
const int NORMAL = 0;
const int SPECIAL_DAY_POINT = 10;
const int SPECIAL_DAY_TH = 10;
const int GOLD_SCORE_TH = 50;
const int SILVER_SCORE_TH = 30;

int GetWeekdayIdx(std::string& weekday);
int GetWeekdayPoint(std::string& weekday);
void SetSpecialDayCnt(std::string& weekday, int curUser);
void PrintRemovedPlayer();
void PrintUserResult();
void SetUserGrade();
void SetSpecialPoint();
void GetInputData();
void CalculateUserScore();
void SetUserData(string name, string weekday);

int main() {
	GetInputData();
	CalculateUserScore();
}

void GetInputData() {
	ifstream fin{ "attendance_weekday_500.txt" };
	for (int i = 0; i < MAX_INPUT; i++) {
		string name, weekday;
		fin >> name >> weekday;
		SetUserData(name, weekday);
	}
}

void CalculateUserScore() {
	SetSpecialPoint();
	SetUserGrade();
	PrintUserResult();
	PrintRemovedPlayer();
}

void SetUserData(string name, string weekday) {
	if (user.count(name) == 0) {
		user.insert({ name, ++userCnt });
		names[userCnt] = name;
	}

	SetSpecialDayCnt(weekday, user[name]);
	userWeekdayCnt[user[name]][GetWeekdayIdx(weekday)] += 1;
	points[user[name]] += GetWeekdayPoint(weekday);
}

int GetWeekdayIdx(std::string& weekday)
{
	if (weekday == "monday") return MON;
	if (weekday == "tuesday") return TUE;
	if (weekday == "wednesday") return WED;
	if (weekday == "thursday") return THU;
	if (weekday == "friday") return FRI;
	if (weekday == "saturday") return SAT;
	if (weekday == "sunday") return SUN;
}

void SetSpecialDayCnt(std::string& weekday, int curUser)
{
	if (weekday == "wednesday") wedCnt[curUser] += 1;
	if (weekday == "saturday" || weekday == "sunday") weekenCnt[curUser] += 1;
}

int GetWeekdayPoint(std::string& weekday)
{
	if (weekday == "monday" || weekday == "tuesday" || weekday == "thursday" || weekday == "friday") return 1;
	if (weekday == "saturday" || weekday == "sunday") return 2;
	if (weekday == "wednesday") return 3;
}

void SetSpecialPoint()
{
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		if (userWeekdayCnt[userIdx][WED] >= SPECIAL_DAY_TH) points[userIdx] += SPECIAL_DAY_POINT;
		if (userWeekdayCnt[userIdx][SAT] + userWeekdayCnt[userIdx][SUN] >= SPECIAL_DAY_TH) points[userIdx] += SPECIAL_DAY_POINT;
	}
}

void SetUserGrade()
{
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		if (points[userIdx] >= GOLD_SCORE_TH) grade[userIdx] = GOLD;
		else if (points[userIdx] >= SILVER_SCORE_TH) grade[userIdx] = SILVER;
		else grade[userIdx] = NORMAL;
	}
}

void PrintUserResult()
{
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		cout << "NAME : " << names[userIdx] << ", ";
		cout << "POINT : " << points[userIdx] << ", ";
		cout << "GRADE : ";

		if (grade[userIdx] == GOLD) cout << "GOLD" << "\n";
		else if (grade[userIdx] == SILVER) cout << "SILVER" << "\n";
		else cout << "NORMAL" << "\n";
	}
}

void PrintRemovedPlayer()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int userIdx = 1; userIdx <= userCnt; userIdx++) {
		if (grade[userIdx] == NORMAL && wedCnt[userIdx] == 0 && weekenCnt[userIdx] == 0) {
			std::cout << names[userIdx] << "\n";
		}
	}
}