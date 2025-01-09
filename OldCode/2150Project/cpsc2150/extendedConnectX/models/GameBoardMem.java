package cpsc2150.extendedConnectX.models;

import java.util.*;

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
 * @invariant gameBoardMap.size() <= Row * Column
 *            gameBoardMap contains valid mappings of characters to associated BoardPositions
 * 
 * @Corresponds Row = #Row
 *              Column = #Column
 *              numsToWin = #numsToWin
 */
public class GameBoardMem extends AbsGameBoard {

    // this is the variable used for the map that stores the character that goes
    // with the list of board positions
    private Map<Character, List<BoardPosition>> gameBoardMap;
    private int Row = 0;
    private int Column = 0;
    private int numsToWin = 0;

    public GameBoardMem(int Row, int Column, int numsToWin) {
        this.Row = Row;
        this.Column = Column;
        this.numsToWin = numsToWin;
        gameBoardMap = new HashMap<>();// this generates the new hashmap needed

    }

    public boolean checkIfFree(int c) {
        // returns true if the column can accept another token; false otherwise.
        BoardPosition tempPos = new BoardPosition(Row - 1, c);
        List<BoardPosition> temp = new ArrayList<BoardPosition>(); // List of Charactes playing.
          
        Object[] keys= gameBoardMap.keySet().toArray();

        for (int i = 0; i < keys.length; i++) {

            temp = gameBoardMap.get(keys[i]);

            if (temp != null) {
                for (int j = 0; j < temp.size(); j++) {

                    if ((tempPos.getRow() == temp.get(j).getRow())
                            && (tempPos.getColumn() == temp.get(j).getColumn())) {
                        return false;
                    }

                }
            }
        }

        return true;// All spaces in the column are filled, so it cannot accept another token
    }

    public void dropToken(char playerToken, int pos) {

        if (checkIfFree(pos)) {
            for (int i = 0; i < getNumRows(); i++) {
                BoardPosition temp = new BoardPosition(i, pos);
                if (whatsAtPos(temp) == ' ') {
                    if (!gameBoardMap.containsKey(playerToken)) {
                        List<BoardPosition> positions = new ArrayList<>();
                        positions.add(temp);
                        gameBoardMap.put(playerToken, positions);
                    } else {
                        gameBoardMap.get(playerToken).add(temp);
                    }
                    break;
                }
            }
        }
    }
    
    public char whatsAtPos(BoardPosition pos) {

       Object[] keys= gameBoardMap.keySet().toArray();

       List<BoardPosition> temp = new ArrayList<BoardPosition>(0); // List of Charactes playing.

        for (int i = 0; i < keys.length; i++) {

           temp = gameBoardMap.get(keys[i]);

            if (temp != null) {
                for (int j = 0; j < temp.size(); j++) {

                    if ((pos.getRow() == temp.get(j).getRow()) && (pos.getColumn() == temp.get(j).getColumn())) {
                        return (char) keys[i];
                    }

                }
            }

        }

        return ' ';// All spaces in the column are filled, so it cannot accept another token

    }

    @Override
    public boolean isPlayerAtPos(BoardPosition pos, char player) {
    char temp = whatsAtPos(pos);

     if(temp==player){
        return true;
     }
     return false;
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
