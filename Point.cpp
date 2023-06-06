#include "Point.h"

Point::Point() : _x(0), _y(0) {}

Point::Point(const int x, const int y) : _x(x), _y(y) {}

Point Point::direction(const Point& src, const Point& dst){
	return (dst - src).abS() / (dst - src);
}

Point Point::operator/(const Point& other) const{
	int x, y;
	if (_x == other.getX() && !_x) { x = 0; }
	else { x = _x / other.getX(); }
	if ((_y == other.getY()) && !_y) { y = 0; }
	else { y = _y / other.getY(); }
	return Point(x, y);
}

double Point::calcSlope(const Point& src, const Point& dst)
{
	if (dst.getX() - src.getX() != 0) { return (dst.getY() - src.getY()) / (double)(dst.getX() - src.getX()); }
	else if (dst.getY() - src.getY() > 0) { return INT_MAX; }
	return INT_MIN;
}

double Point::calcSlope(const Point& dst) const
{
	return calcSlope(*this, dst);
}

Point Point::operator+(const Point& other) const
{
	// return point of sum of two points
	return Point(this->_x + other.getX(), this->_y + other.getY());
}

Point& Point::operator+=(const Point& other)
{
	// add points together
	_x += other.getX(); _y += other.getY();
	return *this;
}

Point Point::operator-(const Point& other) const
{
	return Point(this->_x - other.getX(), this->_y - other.getY());
}

Point& Point::operator-=(const Point& other)
{
	_x -= other.getX(); _y -= other.getY(); //sub
	return *this;
}

bool Point::operator==(const Point& other) const
{
	return (_x == other.getX()) && (_y == other.getY());
}

bool Point::operator!=(const Point& other) const
{
	return (_x != other.getX()) || (_y != other.getY());
}

int Point::getX() const
{
	return this->_x;
}

int Point::getY() const
{
	return this->_y;
}

Point Point::abS() { return Point(abs(_x), abs(_y)); }
