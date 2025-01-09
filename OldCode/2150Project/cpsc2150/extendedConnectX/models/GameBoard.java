package cpsc2150.extendedConnectX.models;

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
 * @invariant [The game board should have dimensions consistent with the specified row and column values.]
 * 
 * @Corresponds Row = #Row
 *              Column = #Column
 *              numsToWin = #numsToWin
 * 
 */
public class GameBoard extends AbsGameBoard {
    private char[][] board;
    private int Row = 0;
    private int Column = 0;
    private int numsToWin = 0;

    /**
     * This constructor will represent the game board itself.
     * The game board is represented as a 2 d array of characters
     * where each spot on the board can be represented as
     * an x y coordinate.
     * 
     * @pre none
     * @post board[][] = [created and ready to accept characters]
     * @return [A gameboard that is aRow x aColumn in size all spaces empty on the board]
     */
    public GameBoard(int aRow, int aColumn, int aNumsToWin) {

        Row = aRow;
        Column = aColumn;
        numsToWin = aNumsToWin;

        this.board = new char[Row][Column];
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Column; j++) {
                board[i][j] = ' ';
            }
        }
    }

    public boolean checkIfFree(int c) {
        // returns true if the column can accept another token; false otherwise.
        return board[Row - 1][c] == ' ';
    }

    public void dropToken(char p, int c) {
        // places the character p in column c. The token will be placed in the lowest
        // available row in column c.
        if (checkIfFree(c)) {
            for (int row = 0; row < board.length; row++) {
                // Check if the current row in column c is free (empty)
                if (board[row][c] == ' ') {
                    // Place the token 'p' in the empty cell
                    board[row][c] = p;
                    // Exit the loop since the token has been placed
                    break;
                }
            }
        }
    }
    public char whatsAtPos(BoardPosition pos) {

        return board[pos.getRow()][pos.getColumn()];
    }

    public boolean isPlayerAtPos(BoardPosition pos, char player) {

        return (player == board[pos.getRow()][pos.getColumn()]);
    }

    public int getNumRows() {
        return Row;
    }

    public int getNumColumns() {
        return Column;
    }

    public int getNumToWin() {

        return numsToWin;
    }

}