#include "gmock/gmock.h"
#include "user.h"
#include "constants.h"


using namespace testing;
using namespace std;

class attendanceFixture : public Test {
public:
	soccerUser soccerUser;
	void CheckWeekDayPoint(std::string str, int expect) {
		int result = soccerUser.GetWeekdayPoint(str);
		EXPECT_EQ(result, expect);
	}

private:
	ifstream fin{ "attendance_weekday_500.txt" };

	void SetUp() override {
		for (int i = 0; i < MAX_INPUT; i++) {
			string name, weekday;
			fin >> name >> weekday;
			soccerUser.SetUserData(name, weekday);
		}
	}
	void TearDown() override {

	}
};

TEST_F(attendanceFixture, weekdayPoint) {
	CheckWeekDayPoint("monday",1);
	CheckWeekDayPoint("tuesday", 1);
	CheckWeekDayPoint("thursday", 1);
	CheckWeekDayPoint("friday", 1);
	CheckWeekDayPoint("saturday", 2);
	CheckWeekDayPoint("sunday", 2);
	CheckWeekDayPoint("wednesday", 3);
	CheckWeekDayPoint("abc", 0);
}

TEST_F(attendanceFixture, calculateScore) {
	soccerUser.SetSpecialPoint();
	soccerUser.SetUserGrade();
	soccerUser.PrintUserResult();
	soccerUser.PrintRemovedPlayer();
}