#include "Piece.h"
#include "vector"
#include "GameState.h"

using namespace std;

GameState::GameState() {

    //todo
    for(auto row=0; row<rows; row++) {
        if (row == rows/2 || row == rows/2-1) //skipping 2 middle lines
            continue;
        for(auto column=0; column<columns; column++) {
            if ((row + column) % 2 != 0) { // only odd
                pieces.emplace_back(column, row, row>rows/2); //row>rows/2 return bool
            }
        }
    }
    attackingPieces = getAttackingPieces();
}



bool GameState::isActivePlayerWhite() const {
    return _isActivePlayerWhite;
}

Piece *GameState::findPiece(int x, int y) {
    //auto&p --> avoid duplication and work with original(if we will make auto p
    // and change smth we'll change not original obj
    for (auto &p: pieces) {
        if (p.xPosition == x && p.yPosition == y && p.isActive) {
            return &p;
        }
    }
    return nullptr;
}

bool GameState::hasFigure(int x, int y) {
    return findPiece(x, y) != nullptr;

}

char GameState::getFigureColor(int x, int y) {
    auto figure = findPiece(x, y);
    if (figure == nullptr)
        return '-';
    return figure->isWhite ? 'w' : 'b';
}

bool GameState::isQueen(int x, int y) {
    Piece *figure = findPiece(x, y);
    return figure != nullptr && figure->isQueen;
}

//graphic podsvetka
bool GameState::mustAttack(int x, int y) {
    for (auto p: attackingPieces) {
        if (p->xPosition == x && p->yPosition == y)
            return true;
    }
    return false;
}

bool GameState::isSelected(int x, int y) {
    return SelectedPiece != nullptr &&
           SelectedPiece->xPosition == x &&
           SelectedPiece->yPosition == y;
}

const int GameState::getRowsCount() {
    return rows;
}

const int GameState::getColumnsCount() {
    return columns;
}

Piece *GameState::selectPiece(Piece *piece) { // Piece *piece указатель на фигуру otherwise -> nullptr
    if (piece != nullptr &&
        ((attackingPieces.empty() && piece->isWhite == _isActivePlayerWhite) ||
         (std::find(attackingPieces.begin(), attackingPieces.end(), piece) != attackingPieces.end()))) {
        SelectedPiece = piece;
    }
    return SelectedPiece;
}


void GameState::handleClick(int x, int y) {
    auto foundPiece = findPiece(x, y);
    if (foundPiece != nullptr) {
        selectPiece(foundPiece != SelectedPiece ? foundPiece : nullptr); //if choosed -> remove selection other give selection
    } else {
        if (SelectedPiece != nullptr && isValidMove(x, y)) {
            moveSelectedPiece(x, y);
        }
    }
}

void GameState::resetGame() {
    pieces.clear();
    _isActivePlayerWhite = true;
    SelectedPiece = nullptr;
    attackingPieces.clear();

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i + j) % 2 != 0) {
                pieces.emplace_back(i, j, false, false);

            }
        }
    }
    for (int i = 0; i < columns; i++) {
        for (int j = rows - 3; j < rows; j++) {
            if ((i + j) % 2 != 0) {
                pieces.emplace_back(i, j, true, false);
            }
        }
    }
    attackingPieces = getAttackingPieces();
}


void GameState::resetBoard() {
    pieces.clear();
    _isActivePlayerWhite = true;
    SelectedPiece = nullptr;
    attackingPieces.clear();
}

void GameState::insertPiece(int x, int y, bool isWhite, bool isQueen) {
    Piece *existingPiece = findPiece(x, y);
    if (existingPiece != nullptr) {
        existingPiece->isActive = false;
    }
    pieces.emplace_back(x, y, isWhite, isQueen);
    attackingPieces = getAttackingPieces(); // to be actual at the momement of the game
}

int GameState::ave(int val1, int val2) {
    return (val1 + val2) / 2;
}

void GameState::changeActivePlayer() {
    _isActivePlayerWhite = !_isActivePlayerWhite;
    SelectedPiece = nullptr;
    attackingPieces = getAttackingPieces();

    // if there are > than one figure the player can choose which figure he wanna
    if (attackingPieces.size() == 1) {
        SelectedPiece = (Piece *) attackingPieces[0];
    }
}

bool GameState::canMoveAsSimple(int newX, int newY) {
    return abs(SelectedPiece->xPosition - newX) == 1 &&
           SelectedPiece->yPosition - newY == getDeltaY() &&
           findPiece(newX, newY) == nullptr;
}

int GameState::getDeltaY() {
    return SelectedPiece->isWhite ? 1 : -1;
    //if 1 going to down
    //if -1 going to up
}

bool GameState::canBeatAsSimple(int newX, int newY) {
    return canBeatAsSimple(SelectedPiece, newX, newY);
}

bool GameState::canBeatAsSimple(const Piece *piece, int newX, int newY) {
    if (newX >= 0 && newX < columns &&
        newY >= 0 && newY < rows && // checks if it on the board
        abs(piece->xPosition - newX) == 2 && //checks if checker move in 2 cell(to beat someone need 2 cells)
        abs(piece->yPosition - newY) == 2) {
        auto figureToBeat = findPiece(ave(piece->xPosition, newX), ave(piece->yPosition, newY));
        auto figureOnNewPlace = findPiece(newX, newY);
        return figureOnNewPlace == nullptr &&
               figureToBeat != nullptr &&
               figureToBeat->isWhite != piece->isWhite;
    }
    return false;
}

bool GameState::canMoveAsQueen(int newX, int newY) {
    return canMoveAsQueen(SelectedPiece, newX, newY);
}

int GameState::sign(int val) {
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

vector<const Piece*> GameState::getFiguresOnQueenPath(const Piece* piece, int newX, int newY){
    vector<const Piece*> result; //all figures on the Queens path
    int dx = sign(newX - piece->xPosition); // dx — по оси X: +1 right or -1 left,
    int dy = sign(newY - piece->yPosition); // dy — по оси Y: +1 (down) или -1 (up).
    int x = piece->xPosition + dx, y = piece->yPosition + dy; // checks the first cell на пути к конечной
    while (x != newX && y != newY) {
        auto figure = findPiece(x, y);
        if (figure != nullptr) {
            result.push_back(figure);
        }
        x += dx;
        y += dy;
    }
    return result;
}

bool GameState::canMoveAsQueen(const Piece* piece, int newX, int newY) {
    //if is a Queen
    //if is free place
    // if there are coordinates on a board
    if (!piece->isQueen
        || findPiece(newX, newY) != nullptr
        || newX < 0
        || newX >= columns
        || newY < 0
        || newY >= rows
        || abs(piece->xPosition - newX) != abs(piece->yPosition - newY)) {
        return false;
    }
    auto figuresOnPath = getFiguresOnQueenPath(piece, newX, newY);
    return figuresOnPath.empty();
}

bool GameState::canBeatAsQueen(int newX, int newY) { //this method usefully: we do not need to transfer SelectedPiece
    // and if we need in the future change method
    // we can change in one place external method to simplify code maintenance
    return canBeatAsQueen(SelectedPiece, newX, newY);
}

bool GameState::canBeatAsQueen(const Piece *piece, int newX, int newY) {
    if (!piece->isQueen ||
        abs(piece->xPosition - newX) != abs(piece->yPosition - newY)
        || findPiece(newX, newY) != nullptr) { // if a queen and move like queen
        return false;
    }
    auto figuresOnPath = getFiguresOnQueenPath(piece, newX, newY);
    return figuresOnPath.size() == 1 &&
           figuresOnPath[0]->isWhite != piece->isWhite;
}

int GameState::checkState() {
    bool blackCanMove = false;
    bool whiteCanMove = false;

    for (const auto &piece: pieces) {
        if (!piece.isActive) continue;
        if (piece.isWhite) {
            whiteCanMove = true;
        } else {
            blackCanMove = true;
        }
    }
    return blackCanMove && !whiteCanMove ? 1 : whiteCanMove && !blackCanMove ? 2 : 0;
    // 1 -> black won
    // 2 -> white won
}


bool GameState::isValidMove(int newX, int newY) {
    return SelectedPiece != nullptr &&
           (canMoveAsSimple(newX, newY) ||
            canBeatAsSimple(newX, newY) ||
            canMoveAsQueen(newX, newY) ||
            canBeatAsQueen(newX, newY));
}

//generalized method which checks can attak or not
bool GameState::canAttack(const Piece *piece) {
    if (piece->isQueen) {
        for (int x = 0; x < columns; x++)
            for (int y = 0; y < rows; y++)
                if (x != piece->xPosition && y != piece->yPosition && canBeatAsQueen(piece, x, y))
                    return true;
        return false;
    } else {
        return canBeatAsSimple(piece, piece->xPosition + 2, piece->yPosition + 2) ||
               canBeatAsSimple(piece, piece->xPosition + 2, piece->yPosition - 2) ||
               canBeatAsSimple(piece, piece->xPosition - 2, piece->yPosition + 2) ||
               canBeatAsSimple(piece, piece->xPosition - 2, piece->yPosition - 2);
    }
}

vector<const Piece *> GameState::getAttackingPieces() {
    //this method allow us to check all checkers which can attack
    std::vector<const Piece *> result; //const to defend from editing the obj
    for (const auto &p: pieces) {
        if (p.isActive && p.isWhite == _isActivePlayerWhite && canAttack(&p)) {
            result.push_back(&p);
        }
    }
    return result;
}

void GameState::checkTurnContinuation() {
    auto newAttackingPieces = getAttackingPieces();
    if (find(newAttackingPieces.begin(), newAttackingPieces.end(), SelectedPiece) != //return an itterator of SelectedPiece in a vector
        newAttackingPieces.end()) { //if not found return itterrator == newAttackingPieces.end();
        attackingPieces = {SelectedPiece}; // TODO what does that mean {}. это значит что вектор состоит из однго поинтера на attacking pieces, где фигурные скоки это констурктор
    } else {
        changeActivePlayer();
    }
}


void GameState::moveSelectedPiece(int x, int y) {
    if (SelectedPiece->isQueen && canBeatAsQueen(SelectedPiece, x, y)) {
        auto figureToRemove = getFiguresOnQueenPath(SelectedPiece, x, y);
        ((Piece*)(figureToRemove[0]))->setInactive(); // remove figure on path
        SelectedPiece->setNewPosition(x, y, rows);
        checkTurnContinuation();
    } else if (canBeatAsSimple(SelectedPiece, x, y)) {
        auto figureToBeat = findPiece(ave(SelectedPiece->xPosition, x), ave(SelectedPiece->yPosition, y));
        figureToBeat->setInactive();
        SelectedPiece->setNewPosition(x, y, rows);
        auto newAttackingPieces = getAttackingPieces();
        checkTurnContinuation();
    } else if (canMoveAsSimple(x, y) || canMoveAsQueen(x, y)) {
        SelectedPiece->setNewPosition(x, y, rows);
        changeActivePlayer();
    }
}