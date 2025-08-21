#include "constants.h"
#include "grade.h"

grade* gradeFactory::getGradeInstance(int point) {
	if (point >= GOLD_SCORE_TH) return new gold();
	else if (point >= SILVER_SCORE_TH) return new silver();
	else return new normal();
}

int gold::getGrade() {
	return GOLD;
}

int silver::getGrade() {
	return SILVER;
}

int normal::getGrade() {
	return NORMAL;
}