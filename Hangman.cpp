#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <random>
#include <ctime>
#include <limits>

using namespace std;

// Word structure containing the word and its hint
struct WordWithHint {
    string word;
    string hint;
    string difficulty;
};

class HangmanGame {
private:
    vector<WordWithHint> words;
    string secretWord;
    string hint;
    string difficulty;
    string guessedWord;
    string guessedLetters;
    int maxAttempts;
    int remainingAttempts;
    bool gameWon;
    
    // Hangman animation frames
    vector<string> hangmanFrames = {
        // Frame 0: Empty gallows
        "  +---+\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // Frame 1: Head
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // Frame 2: Head and body
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // Frame 3: Head, body, and one arm
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|   |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // Frame 4: Head, body, and both arms
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // Frame 5: Head, body, arms, and one leg
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " /    |\n"
        "      |\n"
        "=========",
        
        // Frame 6: Complete hangman (game over)
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " / \\  |\n"
        "      |\n"
        "========="
    };

    void initializeWords() {
        // Easy words (4-5 letters)
        words.push_back({"CAT", "A common pet animal", "Easy"});
        words.push_back({"DOG", "Man's best friend", "Easy"});
        words.push_back({"FISH", "Lives in water", "Easy"});
        words.push_back({"BIRD", "Flies in the sky", "Easy"});
        words.push_back({"BOOK", "You read it", "Easy"});
        
        // Medium words (6-7 letters)
        words.push_back({"PYTHON", "A programming language", "Medium"});
        words.push_back({"JUNGLE", "Dense tropical forest", "Medium"});
        words.push_back({"ROCKET", "Flies to space", "Medium"});
        words.push_back({"GARDEN", "Where plants grow", "Medium"});
        
        // Hard words (8+ letters)
        words.push_back({"ELEPHANT", "Large mammal with a trunk", "Hard"});
        words.push_back({"ASTRONAUT", "Person who travels to space", "Hard"});
        words.push_back({"BUTTERFLY", "Insect with colorful wings", "Hard"});
        words.push_back({"KEYBOARD", "Computer input device", "Hard"});
    }

    void selectDifficulty() {
        cout << "\nSelect difficulty level:\n";
        cout << "1. Easy (4-5 letters, 8 attempts)\n";
        cout << "2. Medium (6-7 letters, 6 attempts)\n";
        cout << "3. Hard (8+ letters, 4 attempts)\n";
        cout << "Enter your choice (1-3): ";
        
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid input! Please enter 1, 2, or 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch(choice) {
            case 1:
                difficulty = "Easy";
                maxAttempts = 8;
                break;
            case 2:
                difficulty = "Medium";
                maxAttempts = 6;
                break;
            case 3:
                difficulty = "Hard";
                maxAttempts = 4;
                break;
        }
    }

    void selectRandomWord() {
        vector<WordWithHint> filteredWords;
        
        // Filter words by selected difficulty
        for(const auto& word : words) {
            if(word.difficulty == difficulty) {
                filteredWords.push_back(word);
            }
        }
        
        if(filteredWords.empty()) {
            // Fallback to any word if no words match the difficulty
            filteredWords = words;
        }
        
        // Random selection
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, filteredWords.size() - 1);
        
        WordWithHint selected = filteredWords[dis(gen)];
        secretWord = selected.word;
        hint = selected.hint;
        
        // Initialize guessed word with underscores
        guessedWord = string(secretWord.length(), '_');
    }

    void clearScreen() {
        system("cls"); // Windows command to clear screen
    }

    void displayGame() {
        clearScreen();
        cout << "=== HANGMAN GAME ===\n";
        cout << "Difficulty: " << difficulty << "\n";
        cout << "Attempts remaining: " << remainingAttempts << "/" << maxAttempts << "\n";
        cout << "Hint: " << hint << "\n\n";
        
        // Display hangman animation
        int frameIndex = maxAttempts - remainingAttempts;
        if(frameIndex >= hangmanFrames.size()) {
            frameIndex = hangmanFrames.size() - 1;
        }
        cout << hangmanFrames[frameIndex] << "\n\n";
        
        // Display guessed word
        cout << "Word: ";
        for(char c : guessedWord) {
            cout << c << " ";
        }
        cout << "\n\n";
        
        // Display guessed letters
        if(!guessedLetters.empty()) {
            cout << "Guessed letters: " << guessedLetters << "\n";
        }
    }

    char getValidGuess() {
        char guess;
        while(true) {
            cout << "Enter your guess (a single letter): ";
            string input;
            cin >> input;
            
            if(input.length() != 1) {
                cout << "Please enter exactly one letter!\n";
                continue;
            }
            
            guess = toupper(input[0]);
            
            if(!isalpha(guess)) {
                cout << "Please enter a valid letter!\n";
                continue;
            }
            
            if(guessedLetters.find(guess) != string::npos) {
                cout << "You already guessed that letter!\n";
                continue;
            }
            
            break;
        }
        return guess;
    }

    void processGuess(char guess) {
        guessedLetters += guess;
        guessedLetters += " ";
        
        bool correctGuess = false;
        for(int i = 0; i < secretWord.length(); i++) {
            if(secretWord[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }
        
        if(!correctGuess) {
            remainingAttempts--;
            cout << "Wrong guess! '" << guess << "' is not in the word.\n";
        } else {
            cout << "Good guess! '" << guess << "' is in the word.\n";
        }
        
        // Check if game is won
        if(guessedWord == secretWord) {
            gameWon = true;
        }
    }

    void waitForEnter() {
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

public:
    HangmanGame() {
        initializeWords();
    }

    void playGame() {
        cout << "Welcome to Hangman!\n";
        
        while(true) {
            selectDifficulty();
            selectRandomWord();
            remainingAttempts = maxAttempts;
            guessedLetters = "";
            gameWon = false;
            
            while(remainingAttempts > 0 && !gameWon) {
                displayGame();
                char guess = getValidGuess();
                processGuess(guess);
                
                if (!gameWon && remainingAttempts > 0) {
                    waitForEnter();
                }
            }
            
            displayGame();
            
            if(gameWon) {
                cout << "\n Congratulations! You won! \n";
                cout << "The word was: " << secretWord << "\n";
            } else {
                cout << "\n Game Over! You lost! \n";
                cout << "The word was: " << secretWord << "\n";
            }
            
            // Ask if player wants to play again
            cout << "\nDo you want to play again? (y/n): ";
            char playAgain;
            cin >> playAgain;
            
            if(tolower(playAgain) != 'y') {
                break;
            }
            
            // Clear the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cout << "Thanks for playing Hangman!\n";
    }
};

int main() {
    HangmanGame game;
    game.playGame();
    return 0;
}