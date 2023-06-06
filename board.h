#pragma once
#include"Sound.h"
#include "Piece.h"
#include "Point.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#define SIZE 8

class Piece;
class Point;

enum
{
	valid_move = 0,
	checked_rival,
	player_not_src,
	player_in_dst,
	will_check_player,
	invalid_index,
	invalid_movment,
	dst_is_src,
	checkmate
};


class board
{
public:
	bool* _en_passent = &_enPassent;


	board();
	~board();

	//geters
	std::string getLastMove() const;

	// checkers
	bool isInboard(const Point& point) const;
	bool playerInPos(const Point& src, const bool player) const; 
	bool isBlockedPath(const Point& src, const Point& dst) const;
	bool canReach(const Point& dst ,const bool player) const;
	bool checkIfMovesExist(const bool player);

	// board actions
	int canMovePiece(const Point & src, const Point & dst, const bool player, Piece * tempOut[2]);
	int subMovePiece(const Point& src, const Point& dst, const bool player) const;
	void movePiece(const Point& src, const Point& dst);

	// static functions
	static Point convertPositionType(const std::string& pos);
	static std::string convertPositionType(const Point& pos);

	//opeators
	Point find(const char target) const;
	Piece* operator[](const Point& index) const;
	Piece* operator[](const int index) const;
	std::string convertToString() const;

private:
	Piece* _board[SIZE][SIZE] = {nullptr};
	std::vector <std::string> _log;
	bool _enPassent;
};
