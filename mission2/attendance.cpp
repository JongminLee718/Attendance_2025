#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "gmock/gmock.h"
#include "constants.h"
#include "user.h"

using namespace std;

#if defined(_DEBUG)
int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
void GetInputData(soccerUser* soccerUser);
void CalculateUserScore(soccerUser* soccerUser);

int main() {
	soccerUser soccerUser;
	GetInputData(&soccerUser);
	CalculateUserScore(&soccerUser);
}

void GetInputData(soccerUser* soccerUser) {
	ifstream fin{ "attendance_weekday_500.txt" };
	for (int i = 0; i < MAX_INPUT; i++) {
		string name, weekday;
		fin >> name >> weekday;
		soccerUser->SetUserData(name, weekday);
	}
}

void CalculateUserScore(soccerUser* soccerUser) {
	soccerUser->SetSpecialPoint();
	soccerUser->SetUserGrade();
	soccerUser->PrintUserResult();
	soccerUser->PrintRemovedPlayer();
}
#endif




