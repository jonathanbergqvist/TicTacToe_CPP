#include <iostream>
#include <string>
#include <limits>

class Game {
    
public:
    Game() {
        // Initialize the game.
        initializeNewGame();
        // Play the game.
        playGame();
    }


private:
    const static int gameBoardSize = 3;
    char gameBoard[gameBoardSize][gameBoardSize];
    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer;
    int roundNumber;

    // Make the game board be set with chars of integer 1 - 9. Set round number to 0.
    void initializeNewGame() {
        int counter = 1;
        for (int i = 0; i < gameBoardSize; i++) {
            for (int j = 0; j < gameBoardSize; j++) {
                gameBoard[i][j] = static_cast<char>(counter + '0'); // Print the correct ASCII char.
                counter++;
            }
        }

        roundNumber = 0;
    }

    // Print the game board.
    void printBoard() {
        const std::string line = "+---+---+---+";

        for (int i = 0; i < gameBoardSize; i++) {
            std::cout << line << std::endl;
            for (int j = 0; j < gameBoardSize; j++) {
                char coor = gameBoard[i][j];
                std::cout << "| " << coor << " ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << line << std::endl;

    }

    // Play the game with the current game board.
    void playGame() {
        std::cout << "Let's start playing Tic Tac Toe!" << std::endl;
        bool winnerFound = false;
        
        // Play the actual game, checking for valid inputs and winner status.
        while (!winnerFound) {

            // Increase round number by 1 and select current player.
            roundNumber++;
            currentPlayer = playerX;
            if (roundNumber % 2 == 0) {
                currentPlayer = playerO;
            }

            // Print the game board for the player to select from.
            printBoard();

            // Get the input from the player and make sure it's valid regarding game rules and syntax.
            std::cout << "Round " << roundNumber << ". Player " << currentPlayer << ". Select integer between 1 - 9" << std::endl;
            getValidPlayerInput();

            // Check if the game has a winner when a winner is possible.
            if (roundNumber > 4) {
                winnerFound = checkIfWinner(currentPlayer);
            
                // A winner was found. Print the board. GZ to the winner.
                if (winnerFound) {
                    printBoard();
                    winnerFound = true;
                }
                // The game ends in a tie. New game?
                if (roundNumber == 9 && !winnerFound) {
                    std::cout << "The game ends in a tie!" << std::endl;
                    printBoard();
                    winnerFound = true;
                }
            }
            
        }

    }

    void getValidPlayerInput() {
        char playerChoice;
        bool validPlayerChoice = false;

        // Get a valid input
        while (!validPlayerChoice) {
            // Get the input as an integer
            playerChoice = getPlayerInput(playerChoice);
            validPlayerChoice = getValidInputValue(playerChoice);
        }
        

    }

    // Get the input as an integer.
    int getPlayerInput(char playerChoice) {
        std::cin >> playerChoice;

        // Make sure that the input char is an integer char.
        while(std::cin.fail() || !std::isdigit(playerChoice)) {
            std::cin.clear(); // Clear possible errors.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line, i.e. other chars than the first one.
            std::cout << "Input was not an integer. Select integer between 1 - 9." << std::endl;
            std::cin >> playerChoice;
        }
        // Clear cin to not allow other chars after initial char to affect game board.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line, i.e. other chars than the first one.
        return playerChoice;
    }

    // Validate that the integer char is a valid value.
    bool getValidInputValue(char playerChoiceChar) {
        // Get the integer from the char.
        int playerChoice = playerChoiceChar - '0';

        // Check if the integer is a number on the game board.
        if (playerChoice < 1 || playerChoice > 9) {
            std::cout << "The integer input was not within the allowed range, please select again." << std::endl;
            return false;

        // Check if the first slot chosen was in the middle slot of the board.
        } else if (playerChoice == 5 && roundNumber == 1) {
            std::cout << "The first choice can't be in the middle, please select another number between 1 - 9." << std::endl;
            return false;
        } else {
            // Check if the player mark is on a non-taken slot.
            for (int i = 0; i < gameBoardSize; i++) {
                for (int j = 0; j < gameBoardSize; j++) {
                    if (gameBoard[i][j] == playerChoiceChar) {
                        gameBoard[i][j] = currentPlayer;
                        std::cout << "Player selected slot " << playerChoiceChar << std::endl;
                        return true;
                    }
                }
            }
            std::cout << "Slot already taken, please select again." << std::endl;
            return false;
        }
    }

    // Check if there is a winner of the current game.
    bool checkIfWinner(char player) {
        for (int i = 0; i < gameBoardSize; i++) {
            // Check rows
            if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] == player) {
                std::cout << "Player " << player << " wins by row! GZ!" << std::endl;
                return true;
            }
            // Check columns
            if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[0][i] == player) {
                std::cout << "Player " << player << " wins by column! GZ!" << std::endl;
                return true;
            }
        }

        // Check diagonals
        if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2] && gameBoard[0][0] == player) {
            std::cout << "Player " << player << " wins by diagonal! GZ!" << std::endl;
            return true;
        }
        if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[0][2] == player) {
            std::cout << "Player " << player << " wins by diagonal! GZ!" << std::endl;
            return true;
        }

        // No winner
        return false;
    }


    
};