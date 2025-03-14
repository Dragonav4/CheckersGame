#include "Piece.h"


//We got 2 constructors to simplify the code. The first one creats simply(with minimal info)
// object(for example for placing started figures on the board) and after creating the first
// the second will automaticcaly get info from the first and thanks to that we will escape from
//duplication of code
Piece::Piece(int xPosition, int yPosition, bool isWhite) : Piece(xPosition, yPosition, isWhite, false) {
}

Piece::Piece(int xPosition, int yPosition, bool isWhite, bool isQueen)
        : xPosition(xPosition), yPosition(yPosition), isWhite(isWhite), isQueen(isQueen), isActive(true)  {
}


//We overload "==" operator for ex to compare some objects between
// themselves just to simplify code and not compare every time each attribute of the objects between themself
//and if we compare 2 vectors we can use find insted of find_if with lamda expression thats also simplify code which also need write all
//attributes
bool Piece::operator==(const Piece& other) const {
    return xPosition == other.xPosition &&
           yPosition == other.yPosition &&
           isWhite == other.isWhite &&
           isQueen == other.isQueen &&
           isActive == other.isActive;
}

void Piece::setNewPosition(int newX, int newY, int rowsCount){
    xPosition = newX;
    yPosition = newY;
    if (yPosition == (isWhite ? 0 : rowsCount - 1)) {
        isQueen = true;
    }
}

void Piece::setInactive() {
    isActive = false;
}
