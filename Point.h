#pragma once
#include <string>

using namespace std;

struct Point {
	Point(int x=1, int y=1): i(y-1), j(x-1){}
	string ToString();

	int i;
	int j;
};