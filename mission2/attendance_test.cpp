#include "gmock/gmock.h"
#include "user.h"
#include "constants.h"


using namespace testing;
using namespace std;

class attendanceFixture : public Test {
public:
	soccerUser soccerUser;
	void LoadFileData() {
		for (int i = 0; i < MAX_INPUT; i++) {
			string name, weekday;
			fin >> name >> weekday;
			soccerUser.SetUserData(name, weekday);
		}
		soccerUser.SetSpecialPoint();
		soccerUser.SetUserGrade();
	}
	void LoadTestData() {
		for (int i = 0; i < TEST_NUM; i++) {
			soccerUser.SetUserData(name[i], weekday[i]);
		}
		soccerUser.SetSpecialPoint();
		soccerUser.SetUserGrade();
	}
	void CheckWeekDayPoint(std::string str, int expect) {
		int result = soccerUser.GetWeekdayPoint(str);
		EXPECT_EQ(result, expect);
	}

private:
	ifstream fin{ "attendance_weekday_500.txt" };
	static const int TEST_NUM = 5;
	const string name[TEST_NUM] = { "Andy", "Tony", "Clair", "Crystal", "Tony" };
	const string weekday[TEST_NUM] = { "monday", "tuesday", "wednesday", "saturday", "sunday" };
	void SetUp() override {

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

TEST_F(attendanceFixture, calculateFileDataScore) {
	LoadFileData();
	int result = soccerUser.PrintRemovedPlayer();
	EXPECT_EQ(result, 2);
}

TEST_F(attendanceFixture, calculateUserDataScore) {
	LoadTestData();
	int result = soccerUser.PrintRemovedPlayer();
	EXPECT_EQ(result, 1);
}

TEST_F(attendanceFixture, CheckUserPrintReuslt) {
	LoadTestData();
	soccerUser.PrintUserResult();
}

TEST_F(attendanceFixture, CheckUserCnt) {
	LoadTestData();
	EXPECT_EQ(soccerUser.GetUserCnt(), 4);
}

TEST_F(attendanceFixture, CheckUserGradeForFile) {
	LoadFileData();
	EXPECT_EQ(soccerUser.GetUserGrade("Daisy"), SILVER);
	EXPECT_EQ(soccerUser.GetUserGrade("Alice"), GOLD);
	EXPECT_EQ(soccerUser.GetUserGrade("Nina"), GOLD);
	EXPECT_EQ(soccerUser.GetUserGrade("Steve"), SILVER);
	EXPECT_EQ(soccerUser.GetUserGrade("Charlie"), GOLD);
}

TEST_F(attendanceFixture, CheckUserPointForFile) {
	LoadFileData();
	EXPECT_EQ(soccerUser.GetUserPoint("Daisy"), 45);
	EXPECT_EQ(soccerUser.GetUserPoint("Alice"), 61);
	EXPECT_EQ(soccerUser.GetUserPoint("Nina"), 79);
	EXPECT_EQ(soccerUser.GetUserPoint("Steve"), 38);
	EXPECT_EQ(soccerUser.GetUserPoint("Charlie"), 58);
}

TEST_F(attendanceFixture, CheckUserGradeForTest) {
	LoadTestData();
	EXPECT_EQ(soccerUser.GetUserGrade("Tony"), NORMAL);
	EXPECT_EQ(soccerUser.GetUserGrade("Clair"), NORMAL);
	EXPECT_EQ(soccerUser.GetUserGrade("Crystal"), NORMAL);
	EXPECT_EQ(soccerUser.GetUserGrade("Andy"), NORMAL);
	EXPECT_EQ(soccerUser.GetUserGrade("Charlie"), NORMAL);
}

TEST_F(attendanceFixture, CheckUserPointForTest) {
	LoadTestData();
	EXPECT_EQ(soccerUser.GetUserPoint("Tony"), 3);
	EXPECT_EQ(soccerUser.GetUserPoint("Clair"), 3);
	EXPECT_EQ(soccerUser.GetUserPoint("Crystal"), 2);
	EXPECT_EQ(soccerUser.GetUserPoint("Andy"), 1);
	EXPECT_EQ(soccerUser.GetUserPoint("Charlie"), 0);
}