# ðŸ Snake Game in C++  

## ðŸ‘¥ Team: Code Mavericks  

### ðŸ”¹ Team Members:  
1. **Tirth Solanki**  
2. **Darpan Sherathiya**  
3. **Deep Shobhashana**  
4. **Shaurya Pratap Singh Shekhawat**  

---

## ðŸŽ® 1. Overview  
This project is a **console-based Snake Game** written in C++. The objective is to control a snake to eat food while avoiding walls, barriers, and its own body. Special elements such as bonus and poisonous food enhance gameplay.  

---

## ðŸš€ 2. Features  
âœ… **Classic Snake Gameplay** â€“ Eat food (`@`) to grow and increase the score.  
â­ **Special Food (`$`)** â€“ Grants bonus points after eating 5 normal foods.  
â˜ ï¸ **Poisonous Food (`X`)** â€“ Reduces the score.  
ðŸš§ **Barriers (`#`)** â€“ Obstacles that cause **Game Over** upon collision.  
ðŸŽ® **Real-time User Input** â€“ Control the snake using `WASD` keys.  
ðŸ’€ **Game Over Conditions**:  
   - Hitting a **wall** (`#`) (boundary).  
   - Colliding with a **barrier** (`#`).  
   - Biting its **own body**.  

---

## ðŸ“œ 3. Game Rules  
- The snake moves continuously in the last set direction.  
- The goal is to eat **food (`@`)** to grow and increase the score.  
- After every **5 foods**, a **special food (`$`)** appears, granting **+3 points**.  
- **Poisonous food (`X`)** randomly appears and decreases the score by **5 points**.  
- The game ends when the snake collides with a wall, a barrier, or itself.  

---

## ðŸŽ® 4. Controls  

| Key  | Action  |  
|------|--------|  
| `W`  | Move Up |  
| `S`  | Move Down |  
| `A`  | Move Left |  
| `D`  | Move Right |  

---

## ðŸ› ï¸ 5. Code Structure  

### ðŸ 5.1 Class `snake`  
The game follows an **object-oriented approach** with the `snake` class handling:  
- **Snake movement**  
- **Food and obstacle generation**  
- **Collision detection**  
- **Score calculation**  

### ðŸ” 5.2 Important Functions  

| Function | Purpose |  
|----------|---------|  
| `draw()` | Renders the game board, snake, food, and obstacles. |  
| `input()` | Captures user keypresses for movement. |  
| `logic()` | Updates snake position, checks collisions, and manages food consumption. |  
| `generateRandom()` | Randomly places food and barriers on the board. |  
| `isgameover()` | Checks if the game has ended. |  

### ðŸ”„ 5.3 Game Loop  
The game runs in a **while loop**:  
1. **Draw the board (`draw()`)**  
2. **Read user input (`input()`)**  
3. **Update game logic (`logic()`)**  
4. **Repeat until `gameover` is true**  

---

## ðŸ–¥ï¸ 6. Compilation & Execution  

### ðŸ“Œ 6.1 Requirements  
- **C++ Compiler** (`g++` for Windows/Linux/macOS)  
- **Windows** (`conio.h` for `_kbhit()` and `_getch()`)  
- **Linux/macOS** (`termios.h` for user input handling)  

### âš¡ 6.2 Steps to Compile and Run  
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

## ðŸ”® 7. Future Enhancements  
âœ¨ **Multiplayer Mode** â€“ Two snakes on the same board.  
ðŸš€ **Levels & Difficulty Settings** â€“ Speed increases over time.  
â¸ï¸ **Pause/Resume Functionality**.  
âš¡ **Power-ups & New Obstacles**.  

---

### ðŸ† Developed by **Team Code Mavericks**  
