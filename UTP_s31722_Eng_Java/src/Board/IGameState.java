package Board;

public interface IGameState {

    boolean isActivePlayerWhite();

    int checkState();
    void resetBoard();

    void insertPiece(int x, int y, boolean isWhite, boolean isQueen);

    void resetGame();
    void handleClick(int x, int y);

    boolean hasFigure(int x, int y);

    char getFigureColor(int x, int y);

    boolean isQueen(int x, int y);

    boolean mustAttack(int x, int y);

    boolean isSelected(int x, int y);

    boolean isValidMove(int x, int y);

    int getRowsCount();

    int getColumnsCount();
}
