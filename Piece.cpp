#include "Piece.h"

extern bool onOffSound;

Piece::Piece(char type, sounds deathSound) : _type(type), _moved(false), _death(deathSound)
{
}


Piece::~Piece()
{
    // play eaten piece sound
	playSound(_death);
}


char Piece::getType() const
{
	return this->_type;
}


bool Piece::getMoved() const
{
	return this->_moved;
}


void Piece::setMoved(bool r)
{
	_moved = r;
}


using namespace Pieces;

Pieces::Rook::Rook(bool player) : Piece((player ? 'r' : 'R'), meow)
{
}


Pieces::Rook::~Rook()
{
}


bool Pieces::Rook::isValidMove(const Point& src, const Point& dst, const board& board) const
{
	return  (!(src - dst).getX() || !(src - dst).getY()) && (!board.isBlockedPath(src, dst));
}


Pieces::Pawn::Pawn(bool player) : Piece((player ? 'p' : 'P'), hitCool)
{
}


Pieces::Pawn::~Pawn()
{
}


bool Pieces::Pawn::isValidMove(const Point& src, const Point& dst, const board& board) const
{
    // check for valid forward move
    if ((abs((dst - src).getY()) <= 1 + 1 * !_moved) && ((dst - src).getY() / (2 * (_type == 'p') - 1) > 0)) 
    {
        // check for blocking items in path
        if (abs((dst - src).getY() == 2 && nullptr != board[src + Point::direction(src, dst)])) { 
            return false;
        }
        // check if piece is eater
        else if ((dst - src).abS() == Point(1, 1)) {
            if (board.playerInPos(dst, _type == 'P')) {
                return true;
            }
            else {
                // check for enpassant move
                Point lastSrc = board::convertPositionType(board.getLastMove()); 
                Point lastDst = board::convertPositionType(std::string() + board.getLastMove()[2] + board.getLastMove()[3]);
                if ((abs((lastSrc - lastDst).getY()) == 2) && !(lastSrc - lastDst).getX() && (board[lastDst]->getType() == ((_type == 'p') ? 'P' : 'p'))) { *board._en_passent = true; return true; }
                else { return false; }
            }
        }

        // if piece has not been moved to the sides
        else {
            return (!(dst - src).getX()) && (board[dst] == nullptr); 
        }
    }
    return false;
}


Pieces::Queen::Queen(bool player) : Rook(player), Bishop(player), Piece((player ? 'q' : 'Q'), queenDeath)
{
}


Pieces::Queen::~Queen()
{
}


bool Pieces::Queen::isValidMove(const Point& src, const Point& dst, const board& board) const
{
	return Rook::isValidMove(src, dst, board) || Bishop::isValidMove(src, dst, board);
}


Pieces::Bishop::Bishop(bool player) : Piece(player ? 'b' : 'B')
{
}


Pieces::Bishop::~Bishop()
{
}


bool Pieces::Bishop::isValidMove(const Point& src, const Point& dst, const board& board) const
{
	return (abs(Point::calcSlope(src, dst)) == 1 && !board.isBlockedPath(src, dst));
}

Pieces::King::King(bool player) : Piece(player ? 'k' : 'K')
{
}


Pieces::King::~King()
{
}


bool Pieces::King::isValidMove(const Point& src, const Point& dst, const board& board) const
{
	return ((dst-src)==Point::direction(src,dst));
}


Pieces::Knight::Knight(bool player) : Piece((player) ? 'n' : 'N', knigtDeath)
{
}


Pieces::Knight::~Knight()
{
}


bool Pieces::Knight::isValidMove(const Point& src, const Point& dst, const board& board) const
{
	return (abs(Point::calcSlope(src,dst))==2 || abs(Point::calcSlope(src, dst)) == .5) && (abs((dst-src).getX())<=2&& abs((dst - src).getY()) <= 2);
}


