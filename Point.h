#pragma once
#include <iostream>
#include <cmath>

class Point
{

public:

	// Constructors
	Point(); // initialize values to 0
	Point(const int x, const int y);
	
	// important functions
	static double calcSlope(const Point& src, const Point& dst) ;
	double calcSlope(const Point& dst) const;
	Point abS();
	static Point direction(const Point& src, const Point& dst);

	// Operators
	Point operator+(const Point& other) const;
    Point operator/(const Point& other) const;
	Point& operator+=(const Point& other);
	Point operator-(const Point& other) const;
	Point& operator-=(const Point& other);
	bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

	// Getters
	int getX() const;
	int getY() const;

private:
	int _x;
	int _y;
};