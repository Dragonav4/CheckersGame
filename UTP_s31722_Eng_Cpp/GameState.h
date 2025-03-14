#include "Piece.h"
#include "vector"
#include "optional"
class GameState {
    const int rows = 8;
    const int columns = 8;
public:
    GameState();

    int checkState();

    bool isActivePlayerWhite() const;

    void resetGame();

    void insertPiece(int x, int y, bool isWhite, bool isQueen);

    Piece* findPiece(int x, int y);

    bool hasFigure(int x, int y);

    char getFigureColor(int x, int y);

    bool isQueen(int x, int y);

    bool mustAttack(int x, int y);

    bool isSelected(int x, int y);


     const int getRowsCount();

     const int getColumnsCount();

    Piece* selectPiece(Piece* piece);

    void handleClick(int x, int y);

    bool isValidMove(int newX, int newY);

    // for test purpose only
    void moveSelectedPiece(int x, int y);

    void resetBoard();

private:

    void changeActivePlayer();

    bool canMoveAsSimple(int newX, int newY);

    int getDeltaY();

    bool canBeatAsSimple(int newX, int newY);

    bool canBeatAsSimple(const Piece* piece, int newX, int newY);

    bool canMoveAsQueen(int newX, int newY);

    static int sign(int val);

    bool canMoveAsQueen(const Piece* piece, int newX, int newY);

    bool canBeatAsQueen(int newX, int newY);

    bool canBeatAsQueen(const Piece* piece, int newX, int newY);

    bool canAttack(const Piece* piece);

    std::vector<const Piece*> getAttackingPieces();

    static int ave(int val1, int val2);

    std::vector<const Piece*> getFiguresOnQueenPath(const Piece* piece, int newX, int newY);

    bool isValidQueenMove(const Piece* piece, int newX, int newY);

    void checkTurnContinuation();

    bool _isActivePlayerWhite = true;

    std::vector<Piece> pieces;

    std::vector<const Piece *> attackingPieces;

    Piece *SelectedPiece = nullptr;
};