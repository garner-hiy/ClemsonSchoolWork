#/**
# * GROUP MEMBER NAMES AND GITHUB USERNAMES SHOULD GO HERE
# * Jared Alvarado (Alvara8)
# * AJ Garner (AJ-USA)
# * Jakob Padar (Jpadar)
# */
#/**
# *
# * 
# * @authors AJ Garner, Jared Alvarado, Jakob Padar
# * @version 4.0
# *
# */

default: cpsc2150/extendedConnects/GameScreen.java cpsc2150/extendedConnectX/models/GameBoard.java cpsc2150/extendedConnectX/models/GameBoard.java cpsc2150/extendedConnectX/models/BoardPosition.java cpsc2150/extendedConnectX/models/AbsGameBoard.java cpsc2150/extendedConnectX/models/GameBoardMem.java
	javac cpsc2150/extendedConnects/GameScreen.java cpsc2150/extendedConnectX/models/IGameBoard.java cpsc2150/extendedConnectX/models/GameBoard.java cpsc2150/extendedConnectX/models/BoardPosition.java cpsc2150/extendedConnectX/models/AbsGameBoard.java cpsc2150/extendedConnectX/models/GameBoardMem.java

run: cpsc2150/extendedConnects/GameScreen.class
	java cpsc2150.extendedConnects.GameScreen

test: cpsc2150/extendedConnectX/tests/TestGameBoard.java cpsc2150/extendedConnectX/tests/TestGameBoardMem.java
		javac -cp .:lib/junit-4.13.2.jar:lib/hamcrest-core-1.3.jar cpsc2150/extendedConnectX/tests/TestGameBoard.java cpsc2150/extendedConnectX/tests/TestGameBoardMem.java

testGB: 
	java -cp .:lib/junit-4.13.2.jar:lib/hamcrest-core-1.3.jar org.junit.runner.JUnitCore cpsc2150.extendedConnectX.tests.TestGameBoard 

testGBmem: 
	java -cp .:lib/junit-4.13.2.jar:lib/hamcrest-core-1.3.jar org.junit.runner.JUnitCore cpsc2150.extendedConnectX.tests.TestGameBoardMem


clean:
	rm -f cpsc2150/extendedConnects/GameScreen.class cpsc2150/extendedConnectX/tests/TestGameBoardMem.class cpsc2150/extendedConnectX/tests/TestGameBoard.class  cpsc2150/extendedConnectX/models/*.class 





