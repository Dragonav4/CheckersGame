#ifndef PIECE_H
#define PIECE_H

class Piece {
public:
    int xPosition, yPosition;
    bool isWhite;
    bool isQueen;
    bool isActive;
    Piece(int xPosition, int yPosition, bool isWhite, bool isQueen);
    Piece(int xPosition, int yPosition, bool isWhite);

    void setNewPosition(int newX, int newY, int rowsCount);
    void setInactive();
    bool operator == (const Piece& other) const;
};

#endif // PIECE_H
