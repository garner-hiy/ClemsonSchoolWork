package cpsc2150.extendedConnects;

import cpsc2150.extendedConnectX.models.GameBoard;
import cpsc2150.extendedConnectX.models.GameBoardMem;
import cpsc2150.extendedConnectX.models.IGameBoard;
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
 */
public class GameScreen {

  public static void main(String[] args) {

    boolean playAgain = true;
    Scanner scnr = new Scanner(System.in);

    int maxNumberOfPlayers = 10,
        minNumberOfPlayers = 2, 
        maxNumberOfRowsColumns = 100,
        minNuamberOfRowsColumns = 3, 
        maxNumberOfWins = 25,
        minNumberOfWins = 3; 

    while (playAgain) {
      IGameBoard board;
      int numRows = 0;
      int numCols = 0;
      int numsToWin = 0;
      boolean GameOver = false;
      int ColChoice = 0;
      String playAgainChoice = " ";
      String gameVersion = " ";
      char playerToken = ' ';
      int numberPlayers = 0;
      List<Character> playCharacters = new ArrayList<Character>(); // List of Charactes playing.

      System.out.println("How many players?");

      numberPlayers = Integer.parseInt(scnr.nextLine());

      while (numberPlayers > maxNumberOfPlayers || numberPlayers < minNumberOfPlayers) {
        if (numberPlayers > maxNumberOfPlayers) {
          System.out.println("Must be 10 players or fewer");
        } else if (numberPlayers < minNumberOfPlayers) {
          System.out.println("Must be at least 2 players");
        }
        System.out.println("How many players?");

        numberPlayers = Integer.parseInt(scnr.nextLine());
      }

      String temp = " ";
      Character tempChar = ' ';
      for (int i = 0; i < numberPlayers; i++) { // For loop adds character tokens to list avoiding same characters
        System.out.println("Enter the character to represent player " + (i + 1));
        temp = scnr.nextLine();
        temp = temp.toUpperCase();
        tempChar = temp.charAt(0);

        while (playCharacters.contains(tempChar)) {
          System.out.println(tempChar + " is already taken as a player token!");
          System.out.println("Enter the character to represent player " + (i + 1));
          temp = scnr.nextLine();
          temp = temp.toUpperCase();
          tempChar = temp.charAt(0);
        }
        playCharacters.add(tempChar);
      }

      System.out.println("How many rows should be on the board?");

      numRows = Integer.parseInt(scnr.nextLine());
      while (numRows > maxNumberOfRowsColumns || numRows < minNuamberOfRowsColumns) {
        if (numRows > maxNumberOfRowsColumns) {
          System.out.println("Rows cannot be greater than 100");
        } else if (numRows < minNuamberOfRowsColumns) {
          System.out.println("Rows cannot be less than 3");
        }
        System.out.println("How many rows should be on the board?");

        numRows = Integer.parseInt(scnr.nextLine());
      }

      System.out.println("How many columns should be on the board?");

      numCols = Integer.parseInt(scnr.nextLine());
      while (numCols > maxNumberOfRowsColumns || numCols < minNuamberOfRowsColumns) {
        if (numCols > maxNumberOfRowsColumns) {
          System.out.println("Columns cannot be greater than 100");
        } else if (numCols < minNuamberOfRowsColumns) {
          System.out.println("Columns cannot be less than 3");
        }
        System.out.println("How many columns should be on the board?");

        numCols = Integer.parseInt(scnr.nextLine());
      }

      System.out.println("How many in a row to win?");
      numsToWin = Integer.parseInt(scnr.nextLine());

      while (numsToWin > maxNumberOfWins || numsToWin < minNumberOfWins || numsToWin > numCols || numsToWin > numRows) {
        if (numsToWin > maxNumberOfWins) {
          System.out.println("Number of tokens needed to win must minNumberOfPlayers be greater than 25");
        } else if (numsToWin < minNumberOfWins) {
          System.out.println("Number of tokens needed to win must minNumberOfPlayers be less than 3");
        } else if (numsToWin > numCols) {
          System.out.println("Number of tokens needed to win must minNumberOfPlayers be larger than number of columns");
        } else if (numsToWin > numRows) {
          System.out.println("Number of tokens needed to win must minNumberOfPlayers be larger than number of Rows");
        }
        System.out.println("How many in a row to win?");

        numsToWin = Integer.parseInt(scnr.nextLine());
      }
      System.out.println("Would you like a Fast Game (F/f) or a Memory Efficient Game (M/m)?");
      gameVersion = scnr.nextLine();

      while (!(gameVersion.equalsIgnoreCase("m") || gameVersion.equalsIgnoreCase("f"))) {
        System.out.println("Please enter F or M");
        System.out.println("Would you like a Fast Game (F/f) or a Memory Efficient Game (M/m)?");
        gameVersion = scnr.nextLine();
      }

      if (gameVersion.equalsIgnoreCase("f")) {
        board = new GameBoard(numRows, numCols, numsToWin);
      } else {
        board = new GameBoardMem(numRows, numCols, numsToWin);
      }

      int playerTurn = 0;
      System.out.println(board.toString());

      while (GameOver == false) {

        if (playerTurn == numberPlayers) {
          playerTurn = 0;
        }

        playerToken = playCharacters.get(playerTurn);

        System.out.println("Player " + playerToken + ", what column do you want to place your marker in?");
        ColChoice = Integer.parseInt(scnr.nextLine());
        while (ColChoice > board.getNumColumns() - 1 || ColChoice < 0 || board.checkIfFree(ColChoice) != true) {

          if (ColChoice > board.getNumColumns() - 1) {

            System.out.println("Column cannot be greater than " + (board.getNumColumns() - 1));
            System.out.println("Player " + playerToken + ", what column do you want to place your marker in?");
            ColChoice = scnr.nextInt();
          } else if (ColChoice < 0) {
            System.out.print("Column cannot be less than 0\n");
            System.out.println("Player " + playerToken + ", what column do you want to place your marker in?");
            ColChoice = Integer.parseInt(scnr.nextLine());

          } else {
            System.out.print("Column is full\n");
            System.out.println("Player " + playerToken + ", what column do you want to place your marker in?");
            ColChoice = Integer.parseInt(scnr.nextLine());
          }

        }

        board.dropToken(playerToken, ColChoice);
        System.out.println(board.toString());

        if (board.checkForWin(ColChoice)) {

          System.out.println("Player " + playerToken + " Won!");
          break;
        }

        if (board.checkTie()) {
          System.out.println("Game ended in Tie!");
          break;
        }
        playerTurn++;
      }

      System.out.println("Would you like to play again? Y/N");
      playAgainChoice = scnr.nextLine();
      while (!(playAgainChoice.equalsIgnoreCase("N") || playAgainChoice.equalsIgnoreCase("Y"))) {
        System.out.println("Would you like to play again? Y/N");
        playAgainChoice = scnr.nextLine();
      }

      if (playAgainChoice.equalsIgnoreCase("Y")) {
        continue;
      }

      if (playAgainChoice.equalsIgnoreCase("N")) {
        playAgain = false;
        break;
      }

    }

    scnr.close();
  }

}
