#pragma once

#define interface struct

interface grade {
	virtual int getGrade() = 0;
};

class gradeFactory {
public:
	grade* getGradeInstance(int score);
};

class gold : public grade {
public:
	int getGrade() override;
};

class silver : public grade {
public:
	int getGrade() override;
};

class normal : public grade {
public:
	int getGrade() override;
};