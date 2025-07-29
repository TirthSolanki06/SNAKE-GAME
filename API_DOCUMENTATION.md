# 🐍 Snake Game - API Documentation

## Table of Contents
1. [Overview](#overview)
2. [Snake Class API](#snake-class-api)
3. [Utility Functions](#utility-functions)
4. [Constants and Global Variables](#constants-and-global-variables)
5. [Usage Examples](#usage-examples)
6. [Integration Guide](#integration-guide)

---

## Overview

This document provides comprehensive documentation for all public APIs, functions, and components in the Snake Game C++ project. The main game logic is encapsulated in the `snake` class, with additional utility functions for console management.

### Key Components
- **Snake Class**: Core game logic and state management
- **Utility Functions**: Console cursor management
- **Main Function**: Game loop and initialization

---

## Snake Class API

The `snake` class is the core component that handles all game mechanics, rendering, input processing, and game state management.

### Class Declaration
```cpp
class snake {
private:
    vector<pair<int, int>> body;
    pair<int, int> food1;
    int specialFoodX, specialFoodY;
    int poisonFoodX, poisonFoodY;
    int barrierX, barrierY;
    int specialFoodCounter;
    bool gameover;

public:
    int score;
    char direction;
    // Public methods...
};
```

### Public Properties

#### `int score`
- **Type**: `int`
- **Description**: Current game score
- **Initial Value**: `0`
- **Modification**: Automatically updated when food is consumed
- **Usage**: Read-only access to current score for display purposes

#### `char direction`
- **Type**: `char`
- **Description**: Current movement direction of the snake
- **Possible Values**: 
  - `'N'` - No movement (initial state)
  - `'U'` - Up
  - `'D'` - Down
  - `'L'` - Left
  - `'R'` - Right
- **Usage**: Can be read to determine current snake direction

### Public Methods

#### `snake()` - Constructor
```cpp
snake() : direction('N'), gameover(false)
```
- **Description**: Initializes a new snake game instance
- **Parameters**: None
- **Returns**: New snake object
- **Side Effects**: 
  - Creates initial snake body (3 segments)
  - Places initial food, poison food, and barrier randomly
  - Sets initial direction to 'N' (no movement)
  - Sets gameover to false

**Example Usage:**
```cpp
snake game;  // Creates new game instance
```

#### `void generateRandom(int &posX, int &posY)`
```cpp
void generateRandom(int &posX, int &posY)
```
- **Description**: Generates random coordinates within the game board boundaries
- **Parameters**: 
  - `posX` (int&): Reference to X coordinate variable
  - `posY` (int&): Reference to Y coordinate variable
- **Returns**: `void`
- **Side Effects**: Modifies the passed reference variables with random coordinates
- **Coordinate Range**: 
  - X: 1 to (width-2)
  - Y: 1 to (height-2)

**Example Usage:**
```cpp
int x, y;
game.generateRandom(x, y);
cout << "Random position: (" << x << ", " << y << ")" << endl;
```

#### `void draw()`
```cpp
void draw()
```
- **Description**: Renders the entire game board to console
- **Parameters**: None
- **Returns**: `void`
- **Side Effects**: 
  - Clears console and redraws game state
  - Displays snake, food items, barriers, and score
  - Updates cursor position

**Rendering Legend:**
- `#` - Walls and barriers
- `O` - Snake head
- `o` - Snake body segments
- `@` - Regular food
- `$` - Special food (bonus points)
- `X` - Poisonous food
- ` ` - Empty space

**Example Usage:**
```cpp
game.draw();  // Renders current game state
```

#### `void input()`
```cpp
void input()
```
- **Description**: Processes keyboard input for snake movement
- **Parameters**: None
- **Returns**: `void`
- **Side Effects**: Updates snake direction based on key press
- **Supported Keys**:
  - `'w'` or Arrow Up (72): Move up
  - `'s'` or Arrow Down (80): Move down
  - `'a'` or Arrow Left (75): Move left
  - `'d'` or Arrow Right (77): Move right
  - `'x'`: Exit game

**Direction Constraints:**
- Cannot move in opposite direction (prevents immediate collision)
- Up ↔ Down reversal blocked
- Left ↔ Right reversal blocked

**Example Usage:**
```cpp
game.input();  // Process any pending keyboard input
```

#### `void logic()`
```cpp
void logic()
```
- **Description**: Core game logic processing for each frame
- **Parameters**: None
- **Returns**: `void`
- **Side Effects**: 
  - Moves snake in current direction
  - Checks for collisions
  - Handles food consumption
  - Updates game state

**Logic Flow:**
1. Calculate new head position based on direction
2. Check wall and barrier collisions
3. Check self-collision
4. Process food consumption (regular, special, poison)
5. Update snake body

**Collision Detection:**
- **Wall Collision**: Boundaries (0, width-1, 0, height-1)
- **Barrier Collision**: Static obstacle position
- **Self Collision**: Snake head touching body segments

**Food Mechanics:**
- **Regular Food (`@`)**: +1 point, grows snake, triggers special food after 5 consumed
- **Special Food (`$`)**: +3 points, appears after every 5 regular foods
- **Poison Food (`X`)**: -5 points (minimum 0), regenerates position

**Example Usage:**
```cpp
game.logic();  // Process one game frame
```

#### `bool isgameover() const`
```cpp
bool isgameover() const
```
- **Description**: Checks if the game has ended
- **Parameters**: None
- **Returns**: `bool` - true if game is over, false otherwise
- **Const Method**: Does not modify object state

**Game Over Conditions:**
- Snake hits wall boundary
- Snake hits barrier
- Snake collides with itself
- Player presses 'x' key

**Example Usage:**
```cpp
if (game.isgameover()) {
    cout << "Game Over! Final Score: " << game.score << endl;
}
```

---

## Utility Functions

### `void HideCursor()`
```cpp
void HideCursor()
```
- **Description**: Hides the console cursor for better visual experience
- **Parameters**: None
- **Returns**: `void`
- **Platform**: Windows-specific (uses Windows API)
- **Side Effects**: Makes console cursor invisible

**Example Usage:**
```cpp
HideCursor();  // Hide cursor before game loop
```

### `int main()`
```cpp
int main()
```
- **Description**: Main program entry point and game loop
- **Parameters**: None (standard main signature)
- **Returns**: `int` - Exit code (0 for success)
- **Side Effects**: 
  - Initializes random seed
  - Runs complete game session
  - Displays final score

**Game Loop Structure:**
1. Initialize random number generator
2. Create snake game instance
3. Loop while game is not over:
   - Draw current state
   - Process input
   - Update game logic
   - Sleep for 30ms (frame rate control)
   - Hide cursor
4. Display final score

**Example Usage:**
```cpp
// Called automatically when program starts
// Returns 0 on successful completion
```

---

## Constants and Global Variables

### `const int height = 20`
- **Description**: Game board height in characters
- **Type**: `const int`
- **Value**: `20`
- **Usage**: Defines vertical boundary for game area

### `const int width = 80`
- **Description**: Game board width in characters  
- **Type**: `const int`
- **Value**: `80`
- **Usage**: Defines horizontal boundary for game area

---

## Usage Examples

### Basic Game Setup
```cpp
#include "snake.cpp"  // Include the snake game code

int main() {
    // Initialize random seed
    srand(time(0));
    
    // Create game instance
    snake myGame;
    
    // Hide cursor for better display
    HideCursor();
    
    // Basic game loop
    while (!myGame.isgameover()) {
        myGame.draw();   // Render game
        myGame.input();  // Get user input
        myGame.logic();  // Update game state
        Sleep(30);       // Control frame rate
    }
    
    // Show final score
    cout << "Final Score: " << myGame.score << endl;
    return 0;
}
```

### Custom Game Loop with Score Tracking
```cpp
snake game;
int highScore = 0;

while (!game.isgameover()) {
    game.draw();
    game.input();
    game.logic();
    
    // Track high score
    if (game.score > highScore) {
        highScore = game.score;
        cout << "New High Score: " << highScore << endl;
    }
    
    Sleep(30);
}
```

### Position Generation Example
```cpp
snake game;
int foodX, foodY;

// Generate random food position
game.generateRandom(foodX, foodY);
cout << "Food spawned at: (" << foodX << ", " << foodY << ")" << endl;

// Generate multiple random positions
for (int i = 0; i < 5; i++) {
    int x, y;
    game.generateRandom(x, y);
    cout << "Position " << i+1 << ": (" << x << ", " << y << ")" << endl;
}
```

### Direction Monitoring
```cpp
snake game;
char lastDirection = 'N';

while (!game.isgameover()) {
    game.input();
    
    // Check if direction changed
    if (game.direction != lastDirection) {
        cout << "Direction changed from " << lastDirection 
             << " to " << game.direction << endl;
        lastDirection = game.direction;
    }
    
    game.logic();
    game.draw();
    Sleep(30);
}
```

---

## Integration Guide

### Including in Your Project
1. **Copy Files**: Copy `snake.cpp` to your project directory
2. **Include Headers**: Ensure all required headers are available:
   ```cpp
   #include <bits/stdc++.h>
   #include <conio.h>
   #include <cstdlib>
   #include <ctime>
   #include <windows.h>
   ```

### Platform Requirements
- **Windows**: Uses `conio.h` and `windows.h` for input and console management
- **Compiler**: C++ compiler with C++11 support (for vector and pair)
- **Console**: Windows console application

### Compilation
```bash
g++ snake.cpp -o snake.exe
```

### Extending the Game
To extend functionality, you can:

1. **Inherit from snake class**:
```cpp
class ExtendedSnake : public snake {
public:
    void addPowerUp() {
        // Custom power-up logic
    }
};
```

2. **Wrap in game manager**:
```cpp
class GameManager {
private:
    snake game;
    int level;
    
public:
    void startNewGame() {
        game = snake();
        level = 1;
    }
    
    void runGameLoop() {
        while (!game.isgameover()) {
            game.draw();
            game.input();
            game.logic();
            Sleep(max(10, 50 - level * 5)); // Increase speed by level
        }
    }
};
```

### Error Handling
The current implementation handles:
- **Boundary Collisions**: Automatic game over
- **Self Collisions**: Automatic game over  
- **Invalid Moves**: Direction constraints prevent immediate reversal

For additional error handling, consider wrapping calls in try-catch blocks and validating inputs before processing.

---

## Performance Considerations

- **Frame Rate**: Current implementation uses 30ms delay (≈33 FPS)
- **Memory Usage**: Snake body grows dynamically with score
- **Console Operations**: Drawing entire board each frame may be inefficient for larger boards

### Optimization Tips
1. **Differential Rendering**: Only update changed screen areas
2. **Input Buffering**: Handle multiple rapid key presses
3. **Memory Management**: Consider maximum snake length limits
4. **Cross-Platform**: Replace Windows-specific code for broader compatibility

---

*Generated by API Documentation Generator*
*Last Updated: 2024*