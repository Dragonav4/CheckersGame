package JUnit5_Tests;
import Board.GameStateJNI;
import org.junit.Test;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

public class JUnitTests {
    private GameStateJNI gameState;

    @BeforeEach
    public void setUp() {
        gameState = new GameStateJNI();
        gameState.resetGame();
    }

    @Test
    public void TestBoardSize() {
        assertEquals(8, gameState.getRowsCount(), "Board should have 8 rows.");
        assertEquals(8, gameState.getColumnsCount(), "Board should have 8 columns.");
    }

    @Test
    public void InitialFigurePlacementTest() {
        for (int row = 0; row < gameState.getRowsCount(); row++) {
            for (int col = 0; col < gameState.getColumnsCount(); col++) {
                var factFigure = gameState.getFigureColor(col, row);
                var expectedFigure = '-';
                if (row<3 && (row+col)%2 == 1) {
                    expectedFigure = 'b';
                }
                if (row>=5 && (row+col)%2 == 1) {
                    expectedFigure = 'w';
                }
                assertEquals(factFigure, expectedFigure, "Expected: "+expectedFigure+", received: " + factFigure + " on position "+col+","+row);
            }
        }
    }

    @Test
    public void pieceSelectionTest() {
        gameState.handleClick(2, 5);
        assertTrue(gameState.isSelected(2, 5), "Piece at (2, 5) should be selected.");
    }

        @Test
    public void pieceSelectionAndMoveTest() {
        pieceSelectionTest();
        //Assume that 3,4 is a valid move
        gameState.handleClick(3,4); //Move selectedPiece to 3,4
        assertFalse(gameState.hasFigure(2,5), "The piece should be at the new position (2, 5).");
        assertTrue(gameState.hasFigure(3,4), "The piece should be at the new position (3, 4).");
    }

    @Test
    public void unableToSelectBlackFigureOnWhiteTurnTest() {
        gameState.handleClick(2,2);
        assertFalse(gameState.isSelected(2,2),"White piece shouldn't be selectable when it's black's turn.");
    }

    @Test
    public void captureMoveTest() {
        gameState.handleClick(2,5); //-> select white piece on 2:5
        gameState.handleClick(3,4); // -> move it to 3:4 and change active player

        // Move black piece into capturing position
        gameState.handleClick(5, 2); // select black piece on 5:2
        gameState.handleClick(4, 3); // move it to 4:3

        // White player performs capture
        gameState.handleClick(3, 4);  // -> Select white piece
        gameState.handleClick(5, 2);  // -> Capture black piece at (5, 2)

        assertFalse(gameState.hasFigure(4, 3), "Captured black piece should be removed from (4, 3).");
        assertEquals('w', gameState.getFigureColor(5, 2), "White piece should be at (5,2) after capturing.");

    }
    @Test
    public void StalemateSituationTest() {
        assertEquals(0, gameState.checkState(), "The game should be a stalemate if no moves are possible.");
    }


    @Test
    public void promotionToQueenTest() {
        gameState.resetBoard();
        gameState.insertPiece(2,1,true,false);
        gameState.handleClick(2,1);
        gameState.handleClick(1,0);
        assertEquals(true, gameState.isQueen(1,0), "The piece should be a Queen");
    }

    @Test
    public void testQueenWCanCaptureOpponentPieceOverDistance() {
        gameState.resetBoard();
        gameState.insertPiece(3,4,true,true);
        gameState.insertPiece(5,2,false,false);
        gameState.handleClick(6,1);
//        assertEquals(2, gameState.checkState(), "The white should won");
        assertTrue(gameState.hasFigure(5,2), "On the position (5,2) should not be piece, cause of capture");
    }




}
