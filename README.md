# Hangman Game

A classic Hangman game implemented in C++ with multiple difficulty levels, hints, and ASCII art animations.

## Features

- 🎮 **Three Difficulty Levels**: Easy, Medium, and Hard
- 💡 **Word Hints**: Helpful clues for each word
- 🎨 **ASCII Art Animation**: Visual hangman progression
- 🔤 **Input Validation**: Proper handling of user inputs
- 📊 **Game Statistics**: Track remaining attempts and guessed letters
- 🔄 **Play Again**: Option to restart with new words

## Difficulty Levels

| Level  | Word Length | Attempts | Description |
|--------|-------------|----------|-------------|
| Easy   | 4-5 letters | 8 attempts | Simple, common words |
| Medium | 6-7 letters | 6 attempts | Moderate difficulty |
| Hard   | 8+ letters  | 4 attempts | Challenging words |

## Word Categories

The game includes words from various categories:
- Animals (CAT, DOG, ELEPHANT, etc.)
- Nature (FISH, BIRD, JUNGLE, etc.)
- Technology (PYTHON, KEYBOARD, etc.)
- Space (ROCKET, ASTRONAUT, etc.)
- Everyday objects (BOOK, BUTTERFLY, etc.)

## Installation & Compilation

### Prerequisites
- C++ compiler (g++ recommended)
- Windows/Linux/macOS terminal

### Compilation Instructions

**Windows:**
```bash
g++ -o hangman hangman.cpp
hangman.exe
```

**Linux/macOS:**
```bash
g++ -o hangman hangman.cpp
./hangman
```

## How to Play

1. **Start the game**: Run the compiled executable
2. **Choose difficulty**: Select from Easy, Medium, or Hard
3. **Read the hint**: Use the clue to help guess the word
4. **Guess letters**: Enter one letter at a time
5. **Win condition**: Guess all letters before running out of attempts
6. **Lose condition**: Hangman drawing completes before word is guessed
7. **Play again**: Option to restart with a new word

## Game Rules

- Guess one letter at a time
- Letters can be uppercase or lowercase
- You cannot guess the same letter twice
- Correct guesses reveal the letter in the word
- Wrong guesses advance the hangman drawing
- Game ends when word is guessed or hangman is complete

## Controls

- **Letter input**: Type a single character and press Enter
- **Continue**: Press Enter after each guess to proceed
- **Play again**: Enter 'y' or 'n' when prompted

## Screenshots

### Game Start
```
Welcome to Hangman!

Select difficulty level:
1. Easy (4-5 letters, 8 attempts)
2. Medium (6-7 letters, 6 attempts)
3. Hard (8+ letters, 4 attempts)
Enter your choice (1-3):
```

### Gameplay Example
```
=== HANGMAN GAME ===
Difficulty: Medium
Attempts remaining: 4/6
Hint: A programming language

  +---+
  |   |
  O   |
 /|   |
      |
      |
=========

Word: P Y T H _ _

Guessed letters: P Y T H
```

### Win Screen
```
Congratulations! You won!
The word was: PYTHON

Do you want to play again? (y/n):
```

### Lose Screen
```
Game Over! You lost!
The word was: ELEPHANT

Do you want to play again? (y/n):
```

## File Structure

```
hangman/
├── hangman.cpp    # Main game source code
├── hangman.exe    # Compiled executable (Windows)
└── README.md      # This file
```

## Technical Details

- **Language**: C++
- **Standard**: C++11 or later
- **Dependencies**: Standard library only
- **Platform**: Cross-platform (Windows/Linux/macOS)

## Features Overview

### ASCII Art Animation
The game features 7 progressive hangman drawings:
1. Empty gallows
2. Head
3. Head + Body
4. Head + Body + One arm
5. Head + Body + Both arms
6. Head + Body + Arms + One leg
7. Complete hangman (game over)

### Word List
The game includes 10+ carefully selected words with appropriate hints and difficulty classifications.

### Error Handling
- Invalid menu choices
- Non-letter inputs
- Duplicate guesses
- Multi-character inputs

## Troubleshooting

### Common Issues

1. **"clear" command not found (Windows)**
   - Solution: Code uses `system("cls")` for Windows compatibility

2. **Weird characters displayed**
   - Solution: Emojis have been removed for better terminal compatibility

3. **Input buffer issues**
   - Solution: Proper input buffer management implemented

### Compilation Errors
- Ensure you have a C++ compiler installed
- Use C++11 or later standard: `g++ -std=c++11 -o hangman hangman.cpp`

## Contributing

Feel free to:
- Add more words to the word list
- Improve the ASCII art
- Add new features
- Report bugs or issues

## License

This project is open source and available under the MIT License.

## Enjoy Playing!

Test your vocabulary skills and see how many words you can guess correctly! The game is educational, fun, and perfect for all ages.

---
*Created with ❤️ using C++*
