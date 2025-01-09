package cpsc2150.extendedConnectX.tests;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

import cpsc2150.extendedConnectX.models.BoardPosition;
import cpsc2150.extendedConnectX.models.GameBoardMem;

/**
 * GROUP MEMBER NAMES AND GITHUB USERNAMES SHOULD GO HERE
 * Jared Alvarado (Alvara8)
 * AJ Garner (AJ-USA)
 * Jakob Padar (Jpadar)
 */
/**
 *
 * 
 * @authors AJ Garner, Jared Alvarado, Jakob Padar
 * @version 4.0
 *
 */

public class TestGameBoardMem {

    private GameBoardMem GameBoardMemFactory(int row, int col, int wins) {
        return new GameBoardMem(row, col, wins);
    }

    private String arrayToString(char[][] board) {
        int row = board.length;
        int col = board[0].length;
        String currentBoard = "|";
        for (int i = 0; i < col; i++) {
            if (i <= 9) {
                currentBoard += " " + i;
            } else {
                currentBoard += i;
            }
            currentBoard += "|";
        }
        currentBoard += "\n";
        for (int i = row - 1; i >= 0; i--) {
            for (int j = 0; j < col; j++) {
                currentBoard += "|" + board[i][j] + " ";

                if (j == col - 1) {
                    currentBoard += "|\n";
                }
            }
        }
        return currentBoard;
    }

    @Test(timeout = 200) // Creates an empty board of Max size values.
    public void Constructor_test_1() {
        int Row = 100;
        int Column = 100;
        int numsToWin = 25;
        char board[][] = new char[Row][Column];
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Column; j++) {
                board[i][j] = ' ';
            }
        }
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        assertEquals(temp.toString(), arrayToString(board));
    }

    @Test(timeout = 200) // test constructing a board with the same value for Row, Col, and numsToWin
    public void Constructor_test_equalRowColandNumsToWin() {
        int Row = 8;
        int Column = 8;
        int numsToWin = 8;
        char board[][] = new char[Row][Column];
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Column; j++) {
                board[i][j] = ' ';
            }
        }

        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        assertEquals(temp.toString(), arrayToString(board));
    }

    @Test(timeout = 200) // test constructing a board with the double digit values for Row, Col, and
                         // numsToWin
    public void Constructor_test_doubleDigetSize() {
        int Row = 40;
        int Column = 32;
        int numsToWin = 20;
        char board[][] = new char[Row][Column];
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Column; j++) {
                board[i][j] = ' ';
            }
        }
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);

        assertEquals(temp.toString(), arrayToString(board));
    }

    @Test(timeout = 200) // Drops a token in Column 0 and test if whatsAtPos returns the proper token
                         // from that position.
    public void whatsAtPos_Corner_test_1() {
        int Row = 5;
        int Column = 5;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('X', 0);
        assertEquals('X', temp.whatsAtPos(new BoardPosition(0, 0)));
    }

    @Test(timeout = 200) // Test if top right corner position on board is in range of method
    public void whatsAtPos_2_top_right_corner_Pos() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        temp.dropToken('X', 3);
        assertEquals('X', temp.whatsAtPos(new BoardPosition(3, 3)));
    }

    @Test(timeout = 200) // Test if top right corner position on board is in range of method
    public void whatsAtPos_3_top_left_corner_Pos_biggerSize() {
        int Row = 10;
        int Column = 10;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('X', 0);
        assertEquals('X', temp.whatsAtPos(new BoardPosition(9, 0)));
    }

    @Test(timeout = 200) // Test if top right corner position on board is in range of method
    public void whatsAtPos_4_routine_mutipleCalls() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        temp.dropToken('X', 3);
        assertEquals('O', temp.whatsAtPos(new BoardPosition(2, 3)));
        assertEquals('X', temp.whatsAtPos(new BoardPosition(3, 3)));
    }

    @Test(timeout = 200) // Test if bottom left position is in range of method
    public void whatsAtPos_5_bottomLeft_pos() {
        int Row = 6;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        assertEquals('O', temp.whatsAtPos(new BoardPosition(0, 0)));
    }

    @Test(timeout = 200) // Fills a 3x3 board with Tokens and calls checkTie, should returned true.
    public void checkTie_test_1() {
        int Row = 3;
        int Column = 3;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp.dropToken('X', i);
            }
        }
        assertTrue(temp.checkTie());
    }

    @Test(timeout = 200) // Fills a 4x4 board with Tokens and calls checkTie, should returned true.
    public void checkTie_test_2() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp.dropToken('X', i);
            }
        }
        assertTrue(temp.checkTie());
    }

    @Test(timeout = 200) // Fills a 20x20 board with Tokens and calls checkTie, should returned true.
    public void checkTie_test_3() {
        int Row = 20;
        int Column = 20;
        int numsToWin = 20;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                temp.dropToken('X', i);
            }
        }
        assertTrue(temp.checkTie());

    }

    @Test(timeout = 20000) // Fills a 100x100 board with Tokens and calls checkTie, should returned true.
                           // This is the edge test case
    public void checkTie_test_4() {
        int Row = 100;
        int Column = 100;
        int numsToWin = 25;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                temp.dropToken('X', i);
            }
        }
        assertTrue(temp.checkTie());

    }

    @Test(timeout = 200) // Drops a token in Column 1 and test if token is is the position it was dropped
                         // in, should return true.
    public void isPlayerAtPos_test_1() {

        int Row = 6;
        int Column = 6;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 1);
        assertTrue(temp.isPlayerAtPos(new BoardPosition(0, 1), 'O'));
    }

    @Test(timeout = 200) // Drops a token in Column 20 and test if token is is the position it was
                         // dropped
                         // in, should return true.
    public void isPlayerAtPos_test_2_boundary_max() {

        int Row = 20;
        int Column = 20;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 20);
        assertTrue(temp.isPlayerAtPos(new BoardPosition(0, 20), 'O'));
    }

    @Test(timeout = 200) // Drops a 3 tokens in Column 2 and test if token is is the position it was
                         // dropped
                         // in, should return true. (middle of the board)
    public void isPlayerAtPos_test_3_in_middle_of_board() {

        int Row = 5;
        int Column = 5;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 2);
        temp.dropToken('O', 2);
        temp.dropToken('O', 2);
        assertTrue(temp.isPlayerAtPos(new BoardPosition(2, 2), 'O'));
    }

    @Test(timeout = 200) // Drops a 4 tokens in Column 3 and test if token is is the position it was
                         // dropped
                         // in and filled all so that the top right corner of the board has a token,check
                         // corner case and should return true. (middle of the board)
    public void isPlayerAtPos_test_4_topRightofBoard() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        assertTrue(temp.isPlayerAtPos(new BoardPosition(3, 3), 'O'));
    }

    @Test(timeout = 200) // Drops a 4 tokens in Column 3 and test if token is is the position it was
                         // dropped
                         // in and filled all so that the top right corner of the board has a token,check
                         // corner case and should return true. (middle of the board)
    public void isPlayerAtPos_test_5_differentCharAtSamePos() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 2);
        temp.dropToken('X', 2);
        assertTrue(!(temp.isPlayerAtPos(new BoardPosition(3, 3), 'O')));
    }

    // Drops three similar tokens on top of each other with a win condition of
    // three. CheckVertWin is then called from last position, should return true.
    @Test(timeout = 200)
    public void checkVertWin_test_1() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        int lastRowPos = 2;
        int lastColPos = 0;
        assertTrue(temp.checkVertWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Drops 10 similar tokens on top of each other with a win condition of 10.
    // CheckVertWin is then called from bottom position, should return true.
    @Test(timeout = 200)
    public void checkVertWin_test_2() {
        int Row = 9;
        int Column = 9;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 5; i++) {
            temp.dropToken('O', 5);
        }
        int lastRowPos = 0;
        int lastColPos = 5;
        assertTrue(temp.checkVertWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    @Test(timeout = 200)//Same as first test, but added a different token first
    public void checkVertWin_test_3() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('X', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        int lastRowPos = 2;
        int lastColPos = 0;
        assertTrue(temp.checkVertWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    @Test(timeout = 200)//putting them into different columns
    public void checkVertWin_test_4() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('X', 1);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        int lastRowPos = 2;
        int lastColPos = 0;
        assertTrue(temp.checkVertWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Drops three similar tokens next to each other with a win condition of three.
    // checkHorizWin is then called from last position, should return true.
    @Test(timeout = 200)
    public void checkHorizWin_test_1() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 1);
        temp.dropToken('O', 2);
        int lastRowPos = 0;
        int lastColPos = 2;
        assertTrue(temp.checkHorizWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Drops 5 similar tokens next to each other with a win condition of 5.
    // checkHorizWin is then called from first position, should return true.
    @Test(timeout = 200)
    public void checkHorizWin_test_2() {
        int Row = 9;
        int Column = 9;
        int numsToWin = 5;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 6; i++) {
            temp.dropToken('O', i);
        }
        int lastRowPos = 0;
        int lastColPos = 0;
        assertTrue(temp.checkHorizWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Drops 5 similar tokens next to each other with a win condition of 5.
    // checkHorizWin is then called from middle position, should return true.
    @Test(timeout = 200)
    public void checkHorizWin_test_3() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 5;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 5; i++) {
            temp.dropToken('O', i);
        }
        int lastRowPos = 0;
        int lastColPos = 2;
        assertTrue(temp.checkHorizWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Drops 7 similar tokens next to each other with a win condition of 4, 3
    // tokens are placed on left side, 3 are placed on right.
    // last token is placed in the middle to join both sides which results in 7
    // tokens in a row.
    // checkHorizWin is then called from middle position, should return true.
    @Test(timeout = 200)
    public void checkHorizWin_test_4() {
        int Row = 9;
        int Column = 9;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        for (int i = 0; i < 3; i++) {
            temp.dropToken('O', i);
        }

        for (int i = 4; i < 7; i++) {
            temp.dropToken('O', i);
        }

        temp.dropToken('O', 3);
        int lastRowPos = 0;
        int lastColPos = 3;
        assertTrue(temp.checkHorizWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Forms a diag line of three tokens, checkDiagWin is then called from last
    // position, should return true.
    @Test(timeout = 200)
    public void checkDiagWin_test_1() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 1);
        temp.dropToken('O', 1);
        temp.dropToken('O', 2);
        temp.dropToken('O', 2);
        temp.dropToken('O', 2);
        int lastRowPos = 2;
        int lastColPos = 2;
        assertTrue(temp.checkDiagWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Forms a diag line of 3 tokens, checkDiagWin is then called from first
    // position, should return true.
    @Test(timeout = 200)
    public void checkDiagWin_test_2() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 1);
        temp.dropToken('O', 1);
        temp.dropToken('O', 2);
        temp.dropToken('O', 2);
        temp.dropToken('O', 2);
        int lastRowPos = 0;
        int lastColPos = 0;
        assertTrue(temp.checkDiagWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Forms a diag line of 5 tokens, 2 tokens are placed on left, 2 on right, one
    // is then placed in the middle to join them to make 5 in a row.
    // position, should return true.
    @Test(timeout = 200)
    public void checkDiagWin_test_3() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 1);
        temp.dropToken('O', 1);
        for (int i = 0; i < 4; i++)
            temp.dropToken('O', 3);
        for (int i = 0; i < 5; i++)
            temp.dropToken('O', 4);
        for (int i = 0; i < 4; i++)
            temp.dropToken('O', 2);
        int lastRowPos = 1;
        int lastColPos = 2;
        assertTrue(temp.checkDiagWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Forms a diag line of three tokens, checkDiagWin is then called from last
    // position, should return true.
    @Test(timeout = 200)
    public void checkDiagWin_test_4() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 1);
        temp.dropToken('O', 1);
        temp.dropToken('O', 2);
        int lastRowPos = 2;
        int lastColPos = 0;
        assertTrue(temp.checkDiagWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Forms a diag line of three tokens, checkDiagWin is then called from bottom
    // position, should return true.
    @Test(timeout = 200)
    public void checkDiagWin_test_5() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 0);
        temp.dropToken('O', 1);
        temp.dropToken('O', 1);
        temp.dropToken('O', 2);
        int lastRowPos = 0;
        int lastColPos = 2;
        assertTrue(temp.checkDiagWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // Forms a diag line of 5 tokens, 2 tokens are placed on left, 2 on right, one
    // is then placed in the middle to join them to make 5 in a row.
    // position, should return true.
    @Test(timeout = 200)
    public void checkDiagWin_test_6() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 4);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        for (int i = 0; i < 4; i++)
            temp.dropToken('O', 1);
        for (int i = 0; i < 5; i++)
            temp.dropToken('O', 0);
        for (int i = 0; i < 3; i++)
            temp.dropToken('O', 2);
        int lastRowPos = 1;
        int lastColPos = 2;
        assertTrue(temp.checkDiagWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }
    // Forms four crossing diag lines, three tokens are then dropped in the middle to join all four lines.
    // This allows them to meet the win condition and true should be returned. 
    @Test(timeout = 200)
    public void checkDiagWin_test_7() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        temp.dropToken('O', 3);
        for (int i = 0; i < 4; i++)
            temp.dropToken('O', 1);
        for (int i = 0; i < 5; i++)
            temp.dropToken('O', 0);
        for (int i = 0; i < 5; i++)
            temp.dropToken('O', 5);
        for (int i = 0; i < 4; i++)
            temp.dropToken('O', 4);
        for (int i = 0; i < 3; i++)
            temp.dropToken('O', 2);
        int lastRowPos = 1;
        int lastColPos = 2;
        assertTrue(temp.checkDiagWin(new BoardPosition(lastRowPos, lastColPos), 'O'));
    }

    // 5 tokens are dropped in aRow with a height of 6, checkIfFree is then called
    // in same row, should return true.
    @Test(timeout = 200)
    public void checkIfFree_test_1() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 3;

        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 3;
        for (int i = 0; i < 5; i++) {
            temp.dropToken('O', pos);
        }
        assertTrue(temp.checkIfFree(pos));
    }

    // 6 tokens are dropped in aRow with a height of 6, checkIfFree is then called
    // in same row, should return False;.
    @Test(timeout = 200)
    public void checkIfFree_test_2() {
        int Row = 6;
        int Column = 6;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 3;
        for (int i = 0; i < 6; i++) {
            temp.dropToken('O', pos);
        }
        assertTrue(!(temp.checkIfFree(pos)));
    }

    // 15 tokens are dropped in aRow with a height of 20, checkIfFree is then called
    // should return true as the column is free
    @Test(timeout = 200)
    public void checkIfFree_test_with_doubleDigit_sizedBoard() {
        int Row = 20;
        int Column = 20;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 3;
        for (int i = 0; i < 15; i++) {
            temp.dropToken('O', pos);
        }
        assertTrue((temp.checkIfFree(pos)));
    }

    // Drops 3 tokens in Row 3, whatsAtPos is then called to check last position to
    // ensure token was placed in correct spot. Should return true.
    @Test(timeout = 200)
    public void dropToken_test_1() {

        int Row = 6;
        int Column = 6;
        int numsToWin = 3;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 3;
        for (int i = 0; i < 6; i++) {
            temp.dropToken('O', pos);
        }
        int lastRowPos = 3;
        int lastColPos = 3;
        assertEquals('O', temp.whatsAtPos(new BoardPosition(lastRowPos, lastColPos)));
    }

    // Drops 4 tokens in col 1, whatsAtPos is then called to check last position to
    // ensure token was placed in correct spot. Should return true.
    @Test(timeout = 200)
    public void dropToken_test_first_col_boundary_2() {

        int Row = 4;
        int Column = 4;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 0;
        for (int i = 0; i < 5; i++) {
            temp.dropToken('O', pos);
        }
        int lastRowPos = 3;
        int lastColPos = 0;
        assertEquals('O', temp.whatsAtPos(new BoardPosition(lastRowPos, lastColPos)));
    }

    // testing to see if the whole collumed holds the value of the tokens dropped
    // drop 4 tokens in col 1 each pos in col 1 should return assert equal
    @Test(timeout = 200)
    public void dropToken_test_whole_col_filled_3() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 1;
        for (int i = 0; i < 4; i++) {
            temp.dropToken('O', pos);
            int lastColPos = 1;
            assertEquals('O', temp.whatsAtPos(new BoardPosition(i, lastColPos)));
        }
    }

    // testing to see if drop token works for a larger sized board
    // drop 20 tokens in col 10 each pos in col 10 should return assert equal
    @Test(timeout = 200)
    public void dropToken_for_double_digit_sizedBoard_4() {
        int Row = 20;
        int Column = 20;
        int numsToWin = 5;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 10;
        for (int i = 0; i < 20; i++) {
            temp.dropToken('O', pos);
            int lastColPos = 10;
            assertEquals('O', temp.whatsAtPos(new BoardPosition(i, lastColPos)));
        }
    }

    // testing to see if col can take different characters
    // drop 4 different char tokens in a colum and return true when comparing each
    // position's token to the expected
    @Test(timeout = 200)
    public void dropToken_test_different_chars_5() {
        int Row = 4;
        int Column = 4;
        int numsToWin = 4;
        GameBoardMem temp = GameBoardMemFactory(Row, Column, numsToWin);
        int pos = 1;
        temp.dropToken('O', pos);
        temp.dropToken('X', pos);
        temp.dropToken('@', pos);
        temp.dropToken('+', pos);
        assertEquals('O', temp.whatsAtPos(new BoardPosition(0, pos)));
        assertEquals('X', temp.whatsAtPos(new BoardPosition(1, pos)));
        assertEquals('@', temp.whatsAtPos(new BoardPosition(2, pos)));
        assertEquals('+', temp.whatsAtPos(new BoardPosition(3, pos)));
    }
}
