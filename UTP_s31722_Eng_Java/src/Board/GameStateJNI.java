package Board;

import java.io.File;

public class GameStateJNI implements IGameState {
    static {
        System.load(new File("libs/libs31722_Checkers_Engine_lib.dylib").getAbsolutePath());

        //System.load("/Users/dragonav/Desktop/Study/UTP/UTP_s31722_Eng_Project1/UTP_s31722_Eng_Cpp/cmake-build-debug/libs31722_Checkers_Engine_lib.dylib");
    }

    public native boolean isActivePlayerWhite();
    public native int checkState();

    public native void resetGame();
    public native void resetBoard();

    public native void insertPiece(int x, int y, boolean isWhite, boolean isQueen);
    public native void handleClick(int x, int y);
    public native boolean hasFigure(int x, int y);
    public native char getFigureColor(int x, int y);
    public native boolean isQueen(int x, int y);
    public native boolean mustAttack(int x, int y);
    public native boolean isSelected(int x, int y);
    public native boolean isValidMove(int x, int y);
    public native int getRowsCount();
    public native int getColumnsCount();
}
