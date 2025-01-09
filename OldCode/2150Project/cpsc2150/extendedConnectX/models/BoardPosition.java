package cpsc2150.extendedConnectX.models;

/**
 * GROUP MEMBER NAMES AND GITHUB USERNAMES SHOULD GO HERE
 * Jared Alvarado (Alvara8)
 * AJ Garner (AJ-USA)
 * Jakob Padar (Jpadar)
 */
/**
 * This class will be used to keep track of an individual cell for a board. 
 * BoardPosition will have variables to
 * represent the Row position and the Column position.
 *
 * @authors AJ Garner, Jared Alvarado, Jakob Padar
 * @version 4.0
 *
 * @invariant Row >= 0 AND Column >= 0
 */

public class BoardPosition
{
    private int Row;
    private int Column;

    /**
    * This is a constructor for the class BoardPosition. which will take in an 
    * int for the Row position and an int
    * for the Column position. After the constructor has been called, there 
    * will be no other way to change any
    * fields through any seter methods.
    *
    * @param aRow the value for the position of the player on the rows
    * @param aColumn the value for the poition of the player on the columns
    *
    * @pre aRow >= 0 AND aColumn >= 0
    *
    * @post Row = aRow AND Column = aColumn
    */
    public BoardPosition(int aRow, int aColumn){
        Row = aRow;
        Column = aColumn;
        //parameterized constructor for BoardPosition
    }


    /**
    * This method will return the amount for Row position.
    *
    * @pre None
    *
    * @post Row = #Row AND self = #self
    *
    * @return Row
    */
    public int getRow(){
        //returns the row
        return Row;
    }


    /**
    * This method will return the amount for Column position.
    *
    * @pre  None
    *
    * @post Column = #Column AND self = #self
    *
    * @return Column
    */
    public int getColumn(){
        //returns the column
        return Column;
    }


    /**
    * This method will return true or false if two BoardPositions are equal.
    * They should have the same row and column.
    *
    * @param obj the object containing the values for Row and Column
    *
    * @pre None
    *
    * @post obj = #obj OR obj != #obj
    *
    * @return true OR false
    */
    @Override
    public boolean equals(Object obj){
        if (this == obj){
            return true; 
        }
        //type cast simple obj to board pos to compare
        BoardPosition pos2 = (BoardPosition) obj;
        return this.Row == pos2.Row && this.Column == pos2.Column;
    }


    /**
    * This method will return a string that will show the positions in the form
    * of a string. "<row>,<column>"
    *
    * @pre None
    *
    * @post integers >> string AND self = #self
    *
    * @return positions
    */
    @Override
    public String toString(){
        String positions = Row + "," + Column;

        return positions;
    }
}