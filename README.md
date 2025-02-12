# Snake Game in C++
1.Created By: Code Mavericks Team ,
     Team Members : 1.Tirth Solanki ,
		    2.Darpan Sherathiya ,
		    3.Deep Shobhashana , 
                    4.Shaurya Singh Shekhawat

## 2. Brief Overview
This project is a **console-based Snake Game** written in C++. The game involves controlling a snake to eat food while avoiding walls, barriers, and its own body. Additional elements like special food and poisonous food enhance gameplay. The game ends when the snake collides with a wall, a barrier, or itself.

### Features:
- **Classic Snake Gameplay**: Eat food to grow the snake and increase the score.
- **Special Food (`$`)**: Grants bonus points after eating 5 normal foods.
- **Poisonous Food (`X`)**: Reduces the score.
- **Barrier (`#`)**: Acts as an obstacle, causing **Game Over** upon collision.
- **Real-time User Input**: Control the snake using `WASD` keys.
- **Game Over Condition**: Collision with a wall, the barrier, or itself ends the game.

---
   2.Created By: Code Mavericks
     Team Members : 1.Tirth Solanki
		    2.Darpan Sherathiya
		    3.Deep Shobhashana
        4.Shaurya Singh Shekhawat			
## 3. Detailed Explanation

### 2.1 Game Rules
- The snake moves continuously in the last set direction.
- The goal is to eat **food (`@`)** to grow the snake and increase the score.
- After every **5 foods**, a **special food (`$`)** appears, giving **+3 points**.
- **Poisonous food (`X`)** randomly appears and decreases the score by **5 points**.
- The snake **dies** if it hits:
  - A **wall (`#`)** (boundary).
  - The **barrier (`#`)** (randomly placed obstacle).
  - Its **own body**.

### 3.2 Game Controls
| Key  | Action  |
|------|--------|
| `W`  | Move Up |
| `S`  | Move Down |
| `A`  | Move Left |
| `D`  | Move Right |

---

## 4. Code Explanation

### 3.1 Class `snake`
The game is structured using an **object-oriented approach** with the `snake` class, which manages:
- **Snake movement**
- **Food and obstacle generation**
- **Collision detection**
- **Score calculation**

### 4.2 Important Functions
| Function | Purpose |
|----------|---------|
| `draw()` | Renders the game board, snake, food, and obstacles. |
| `input()` | Captures user keypresses for movement. |
| `logic()` | Updates snake position, checks collisions, and manages food consumption. |
| `generateRandom()` | Randomly places food and barriers on the board. |
| `isgameover()` | Checks if the game has ended. |

### 4.3 Game Loop
The game runs in a **while loop**:
1. **Draw the board (`draw()`)**
2. **Read user input (`input()`)**
3. **Update game logic (`logic()`)**
4. **Repeat until `gameover` is true**

---

## 5. Compilation & Execution

### 4.1 Requirements
- **C++ Compiler** (`g++` for Windows/Linux/macOS)
- **Windows** (`conio.h` for `_kbhit()` and `_getch()`)
- **For Linux/macOS**, use `termios` to replace `conio.h`

### 5.2 Steps to Compile and Run
1. **Open terminal/command prompt**.
2. **Navigate to the source file location**.
3. **Compile the program**:
   ```sh
   g++ snake.cpp -o snake.exe
   ```
4. **Run the game**:
   ```sh
   ./snake.exe
   ```

---

## 6. Future Enhancements
- **Multiplayer Mode** (Two snakes on the same board).
- **Levels & Difficulty Settings** (Speed increases over time).
- **Pause/Resume Functionality**.
- **Power-ups & New Obstacles**.


