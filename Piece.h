#pragma once
#include "board.h"
#include "Point.h"

class board;

class Piece
{
public:
	// initializers
	Piece(char type, sounds deathSound = hit);
	virtual ~Piece();

	//getters
	char getType() const;
	bool getMoved() const;
	void setMoved(bool r);

	// actions
	virtual bool isValidMove(const Point& src, const Point& dst, const board& board) const { return false; };

protected:
	char _type;
	bool _moved;
	sounds _death;
};

namespace Pieces
{

	class Rook : virtual public Piece
	{
	public:
		Rook(bool player);
		~Rook() override;
		bool isValidMove(const Point& src,const Point& dst, const board& board) const override;
	};

	class Pawn :
		virtual public Piece
	{
	public:
		Pawn(bool player);
		~Pawn() override;

		bool isValidMove(const Point& src, const Point& dst, const board& board) const override;
	};
	
	class Knight :
		virtual public Piece
	{
	public:
		Knight(bool player);
		~Knight() override;

		bool isValidMove(const Point& src, const Point& dst, const board& board) const override;
	};

	class King :
		virtual public Piece
	{
	public:
		King(bool player);
		~King() override;

		bool isValidMove(const Point& src, const Point& dst, const board& board) const override;
	};

	class Bishop :
		virtual public Piece
	{
	public:
		Bishop(bool player);
		~Bishop() override;

		bool isValidMove(const Point& src, const Point& dst, const board& board) const override;
	};

	class Queen :
		virtual public Rook, virtual public Bishop
	{
	public:
		Queen(bool player);
		~Queen() override;

		bool isValidMove(const Point& src, const Point& dst, const board& board) const override;
	};
}


