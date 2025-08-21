#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum {
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
};

const int GOLD = 1;
const int SILVER = 2;
const int NORMAL = 0;
const int SPECIAL_DAY_POINT = 10;
const int SPECIAL_DAY_TH = 10;
const int GOLD_SCORE_TH = 50;
const int SILVER_SCORE_TH = 30;

static const int MAX_USER = 100;
static const int MAX_WEEKDAY = 7;
static const int MAX_INPUT = 500;