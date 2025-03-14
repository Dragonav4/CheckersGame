#include "Board_GameStateJNI.h"
#include "GameState.h"

#include <jni.h>

GameState gameState;


JNIEXPORT jboolean JNICALL Java_Board_GameStateJNI_isActivePlayerWhite(JNIEnv *, jobject) {
    return gameState.isActivePlayerWhite();
}


JNIEXPORT void JNICALL Java_Board_GameStateJNI_handleClick(JNIEnv *, jobject, jint x, jint y) {
    gameState.handleClick(x, y);
}

JNIEXPORT void JNICALL Java_Board_GameStateJNI_resetBoard(JNIEnv *, jobject) {
    gameState.resetBoard();
}

JNIEXPORT void JNICALL Java_Board_GameStateJNI_insertPiece(JNIEnv *, jobject, jint x, jint y, jboolean isWhite, jboolean isQueen) {
    gameState.insertPiece(x, y, isWhite, isQueen);
}

JNIEXPORT jint JNICALL Java_Board_GameStateJNI_checkState(JNIEnv *, jobject) {
    return gameState.checkState();
}

JNIEXPORT void JNICALL Java_Board_GameStateJNI_resetGame(JNIEnv *, jobject) {
    gameState.resetGame();
}

JNIEXPORT jboolean JNICALL Java_Board_GameStateJNI_hasFigure(JNIEnv *, jobject, jint x, jint y) {
    return gameState.hasFigure(x, y);
}

JNIEXPORT jchar JNICALL Java_Board_GameStateJNI_getFigureColor(JNIEnv *, jobject, jint x, jint y) {
    return gameState.getFigureColor(x, y);
}

JNIEXPORT jboolean JNICALL Java_Board_GameStateJNI_isQueen(JNIEnv *, jobject, jint x, jint y) {
    return gameState.isQueen(x, y);
}

JNIEXPORT jboolean JNICALL Java_Board_GameStateJNI_mustAttack(JNIEnv *, jobject, jint x, jint y) {
    return gameState.mustAttack(x, y);
}

JNIEXPORT jboolean JNICALL Java_Board_GameStateJNI_isSelected(JNIEnv *, jobject, jint x, jint y) {
    return gameState.isSelected(x, y);
}

JNIEXPORT jint JNICALL Java_Board_GameStateJNI_getRowsCount(JNIEnv *, jobject) {
    return gameState.getRowsCount();
}

JNIEXPORT jint JNICALL Java_Board_GameStateJNI_getColumnsCount(JNIEnv *, jobject) {
    return gameState.getColumnsCount();
}

JNIEXPORT jboolean JNICALL Java_Board_GameStateJNI_isValidMove(JNIEnv *, jobject, jint newX, jint newY) {
    return gameState.isValidMove(newX, newY);
}