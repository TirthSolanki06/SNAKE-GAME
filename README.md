
# 🐍 Snake Game in C++

A simple **Snake Game** built using C++ with additional features like special food, poisonous food, and barriers.

## 🎮 Features
- **Classic Snake Movement**: Move the snake using the **W, A, S, D** keys.
- **Food Mechanics**:  
  - **Regular Food (@)**: Increases the snake's length and score by **+1**.  
  - **Special Food ($)**: Appears after eating 5 regular food items and grants **+3** bonus points.  
  - **Poisonous Food (X)**: Reduces score by **-5** points.  
- **Barrier Mechanics**: A randomly placed **barrier (#)** that the snake must avoid.  
- **Game Over Conditions**:  
  - Hitting the **walls**  
  - Hitting the **barrier**  
  - Colliding with **itself**  

## 🛠️ Installation & Usage

### 1️⃣ Clone the Repository
```sh
git clone https://github.com/TirthSolanki06/SNAKE-GAME
cd snake-game-cpp
```

### 2️⃣ Compile & Run
Compile the program using a C++ compiler (`g++` recommended):
```sh
g++ snake.cpp -o snake.exe
```
Run the executable:
```sh
./snake.exe
```

## 🕹️ Controls
| Key  | Action          |
|------|----------------|
| `W`  | Move Up        |
| `A`  | Move Left      |
| `S`  | Move Down      |
| `D`  | Move Right     |

## 🏗️ Code Structure
### 1️⃣ **Class `snake`**
Handles all game mechanics.

- **`draw()`**: Renders the game grid, snake, food, and score.  
- **`input()`**: Captures keyboard input using `_kbhit()` and `_getch()`.  
- **`logic()`**: Updates the game state:  
  - Moves the snake  
  - Checks for **collisions** (walls, itself, barrier)  
  - Manages **food consumption** and score updates  

### 2️⃣ **Main Function**
- Initializes the game.
- Runs the **game loop**:
  1. **Draws the screen**  
  2. **Processes input**  
  3. **Updates the game logic**  
- Ends when the game is over.

## 📝 Future Improvements
- Add **more obstacles**.  
- Implement **different difficulty levels**.  
- Enhance **graphics using a GUI library**.  

## 🔗 License
This project is **open-source** under the **MIT License**
