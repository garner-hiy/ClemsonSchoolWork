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
 */

/**
 * IGameBoard is an interface that outlines methods essential for managing a game board, 
 * including retrieving board dimensions (getNumRows() and getNumColumns()) and determining the winning conditions (getNumToWin())
 * 
 * @Initialization ensures : A gameBoard is created with number of rows and columns. 
 * 
 * @Defines  Row: Z
 *          Column: Z
 *          numsToWin: Z
 * 
 * @Constraints:  3 <= Row <= 100
 *                3 <= Column <= 100
 *                3 <= numsToWin <= 25
 */


public interface IGameBoard {
    /**
     * This method will check if the column on the game board can
     * accept another token
     * 
     * @param c the value of the column
     * @pre c >= 0 AND c < Column
     * @post [check each top most row space in the column to see if there is an X or
     *       O, if a char is found return false.
     * @post if the space is empty return true to indicate that the column has a
     *       blank space]
     * @return true OR false
     */
    default public boolean checkIfFree(int c){
        return whatsAtPos(new BoardPosition(getNumRows() - 1, c)) == ' ';
    }


    /**
     * This method allows the user to place a token on the game board
     * the token will be placed at the lowest position possible in the column
     * 
     * @param p the value of the token
     * @param c the value representing the column
     * 
     * @pre c >= 0 AND c < Column AND checkIfFree(c) = true
     * @post self = #self AND c = [lowest available row to p]
     */
    public void dropToken(char p, int c);


    /**
     * 
     * This method will check to see if the last token placed in column c resulted in the player winning the game.
     * If so it will return true, otherwise false. Note: this is not checking the entire board for a win, it is just
     * checking if the last token placed results in a win. You may call other methods to complete this method.
     * 
     * @param c value of the column the token was placed in
     * 
     * @pre c >= 0 AND c < Column
     * @post self = #self AND (checkHorizWin() = true OR checkVertWin() = true)
     * 
     * @return true OR false
     */
    default public boolean checkForWin(int c){
        int i = 0;
        char lastToken = ' ';
        for (i = getNumRows() - 1; i >= 0; i--) {
            char compToken = whatsAtPos(new BoardPosition(i, c));
            if (compToken != ' ') {
                lastToken = compToken;
                break;
            }
        }
        BoardPosition lastpos = new BoardPosition(i, c);

        if (checkHorizWin(lastpos, lastToken))
            return true;
        if (checkDiagWin(lastpos, lastToken))
            return true;
        if (checkVertWin(lastpos, lastToken))
            return true;

        return false;
    }
        

    /**
     * This method will check to see if the game has resulted in a tie. A game is tied if there are no free board
     * positions remaining. You do not need to check for any potential wins because we can assume that the players
     * were checking for win conditions as they played the game. It will return true if the game is tied and false otherwise.
     * 
     * @pre board[][] = [all positions in the array are filled]
     * 
     * @post #self = self  
     * 
     * @return true OR false
     */

    default public boolean checkTie(){
        for (int i = 0; i < getNumColumns(); i++) {
            if (checkIfFree(i)) {
                return false;
            }
        }
        return true;
    }


    /**
     * This method checks to see if the last token placed (which was placed in position pos by
     * player p resulted in 5 in a row horizontally. Returns true if it does, otherwise false.
     * 
     * @param pos the value for the x and y coordinates of a position on the board
     * @param p   the char of the players last placed token
     * 
     * @pre pos = [valid position] AND p != ' '
     * 
     * @post self = #self 
     * 
     * @return true OR false
     */
    
    default public boolean checkHorizWin(BoardPosition pos, char p){
        int score = 1;

        for(int i = 1; i < getNumToWin(); i++){
            if(pos.getColumn() + i < getNumColumns() && whatsAtPos(new BoardPosition(pos.getRow(), pos.getColumn() + i)) == p){
                score++;
            } else{
                break;
            }
        }

        for(int i = 1; i < getNumToWin(); i++){
            if(pos.getColumn() - i >= 0 && whatsAtPos(new BoardPosition(pos.getRow(), pos.getColumn() -i)) == p){
                score++;
            } else{
                break;
            }
        }
        return score >= getNumToWin();
    }

    /**
     * This method checks to see if the last token placed (which was placed in position pos by
     * player p) resulted in 5 in a row vertically. Returns true if it does, otherwise false
     * 
     * @param pos the value for the x and y coordinates of a position on the board
     * @param p   the char of the players last placed token
     * 
     * @pre pos = [valid position] AND p != ' '
     * 
     * @post self = #self 
     * 
     * @return true OR false
     */
    default public boolean checkVertWin(BoardPosition pos, char p){
        int score = 1;

        for(int i = 1; i < getNumToWin(); i ++){
            if(pos.getRow() + i < getNumRows() && whatsAtPos(new BoardPosition(pos.getRow()+ i, pos.getColumn())) == p){
                score++;
            }
            else{
                break;
            }
        }
        for(int i = 1; i < getNumToWin(); i++){
            if(pos.getRow() - i >= 0 && whatsAtPos(new BoardPosition(pos.getRow() - i, pos.getColumn())) == p){
                score++;
            }
            else{
                break;
            }
        }
        return score >= getNumToWin();
    }

    /**
     * This method checks to see if the last token placed (which was placed in position pos by
     * player p) resulted in 5 in a row diagonally. 
     * Returns true if it does, otherwise false Note: there are two diagonals to check
     * 
     * @param pos the value for the x and y coordinates of a position on the board
     * @param p   the char of the players last placed token
     * 
     * @pre pos = [valid position] AND p != ' '
     * 
     * @post self = #self
     * 
     * @return true OR false
     */
    default public boolean checkDiagWin(BoardPosition pos, char p){
        int score = 0;
        int j = 0;
        j = pos.getRow();

        for (int i = pos.getColumn(); i < getNumColumns(); i++) {// Checks top right
            if (whatsAtPos(new BoardPosition(j, i)) != p) {
                break;
            }

            score++;
            j++;

            if (j > getNumRows() - 1) {
                break;
            }
        }

        j = pos.getRow();

        for (int i = pos.getColumn(); i >= 0; i--) {// Checks bottom left;
            if (whatsAtPos(new BoardPosition(j, i)) != p) {
                break;
            }

            score++;
            j--;

            if (j < 0) {
                break;
            }
        }

        if (score >= getNumToWin() + 1)
            return true;

        score = 0;
        j = pos.getRow();

        for (int i = pos.getColumn(); i >= 0; i--) {// Checks top right;
            if (whatsAtPos(new BoardPosition(j, i)) != p) {
                break;
            }

            score++;
            j++;

            if (j > getNumRows() - 1) {
                break;
            }
        }

        j = pos.getRow();

        for (int i = pos.getColumn(); i < getNumColumns(); i++) {// Checks bottom right;
            if (whatsAtPos(new BoardPosition(j, i)) != p) {
                break;
            }

            score++;
            j--;

            if (j < 0) {
                break;
            }
        }

        if (score >= getNumToWin() + 1)
            return true;

        return false;
    }


    /**
     * This method will take in a BoardPosition object and check to see if there is an
     * occupied spot there. It will return what is there or return a blank char if
     * nothing is found.
     *
     * @param pos the object that is passed into the method that will be checked by
     *            the function.
     * @pre none
     * 
     * @post self = #self
     * 
     * @return ' ' OR [a character]
     */
    public char whatsAtPos(BoardPosition pos);
    

    /**
     * This method will take in two paramaters, it will then check to see if there
     * is an occupied spot there. It will return true or false depending.
     *
     * @param pos    the object that is passed into the method that will be checked
     *               by the function.
     * @param player is the char that is checked against pos to determine if there
     *               is a marker present
     * 
     * @pre player = 'X' OR player = 'O'
     * 
     * @post player == pos OR player != pos AND self = #self
     * 
     * @return true OR false
     */
    default public boolean isPlayerAtPos(BoardPosition pos, char player){
        return whatsAtPos(pos) == player;
    }


    /**
     * This method will return a string that will show the positions in the form
     * of a string. "<row>,<column>"
     *
     * @pre None
     *
     * @post integers >> string AND self = #self
     * 
     * @return currentBoard
     */
    @Override
    public String toString();


    /**
     * Return Row
     * 
     * @pre none
     * 
     * @post self = #self
     * 
     * @return Row
     */
    public int getNumRows();


    /**
     * Return Column
     * 
     * @pre none
     * 
     * @post self = #self
     * 
     * @return Column
     */
    public int getNumColumns();


    /**
     * Returns the number of tokens needed to win
     * 
     * @pre none
     * 
     * @post self = #self
     * 
     * @return numsToWin
     */
    public int getNumToWin();
}
