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

public abstract class AbsGameBoard implements IGameBoard {

    /**
     * This Method will print the game board to the termail, so as to give a display
     * for the users to see what actions occur.
     *
     *
     * @pre The Board must be initialized with valid rows and columns
     * 
     * @post self = #self AND [Returns a string representation of the game board]
     * 
     * @return ' ' OR [A string representation of the current state of the game board]
     */
    @Override
    public String toString() {

        String currentBoard = "|";

        for (int i = 0; i < getNumColumns(); i++) {
            if (i <= 9) {
                currentBoard += " " + i;
            } else {
                currentBoard += i;
            }
            currentBoard += "|";
        }

        currentBoard += "\n";
        for (int i = getNumRows() - 1; i >= 0; i--) {

            for (int j = 0; j < getNumColumns(); j++) {

                BoardPosition temp = new BoardPosition(i, j);

                currentBoard += "|" + whatsAtPos(temp) + " ";

                if (j == getNumColumns() - 1) {
                    currentBoard += "|\n";
                }

            }
        }

        return currentBoard;
    }

}
