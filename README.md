# 🐍 Snake Game in C++  

## 👥 Team: Code Mavericks  

### 🔹 Team Members:  
1. **Tirth Solanki**  
2. **Darpan Sherathiya**  
3. **Deep Shobhashana**  
4. **Shaurya Pratap Singh Shekhawat**  

---

## 🎮 1. Overview  
This project is a **console-based Snake Game** written in C++. The objective is to control a snake to eat food while avoiding walls, barriers, and its own body. Special elements such as bonus and poisonous food enhance gameplay.  

---

## 🚀 2. Features  
✅ **Classic Snake Gameplay** – Eat food (`@`) to grow and increase the score.  
⭐ **Special Food (`$`)** – Grants bonus points after eating 5 normal foods.  
☠️ **Poisonous Food (`X`)** – Reduces the score.  
🚧 **Barriers (`#`)** – Obstacles that cause **Game Over** upon collision.  
🎮 **Real-time User Input** – Control the snake using `WASD` keys.  
💀 **Game Over Conditions**:  
   - Hitting a **wall** (`#`) (boundary).  
   - Colliding with a **barrier** (`#`).  
   - Biting its **own body**.  

---

## 📜 3. Game Rules  
- The snake moves continuously in the last set direction.  
- The goal is to eat **food (`@`)** to grow and increase the score.  
- After every **5 foods**, a **special food (`$`)** appears, granting **+3 points**.  
- **Poisonous food (`X`)** randomly appears and decreases the score by **5 points**.  
- The game ends when the snake collides with a wall, a barrier, or itself.  

---

## 🎮 4. Controls  

| Key  | Action  |  
|------|--------|  
| `W`  | Move Up |  
| `S`  | Move Down |  
| `A`  | Move Left |  
| `D`  | Move Right |  

---

## 🛠️ 5. Code Structure  

### 🐍 5.1 Class `snake`  
The game follows an **object-oriented approach** with the `snake` class handling:  
- **Snake movement**  
- **Food and obstacle generation**  
- **Collision detection**  
- **Score calculation**  

### 🔍 5.2 Important Functions  

| Function | Purpose |  
|----------|---------|  
| `draw()` | Renders the game board, snake, food, and obstacles. |  
| `input()` | Captures user keypresses for movement. |  
| `logic()` | Updates snake position, checks collisions, and manages food consumption. |  
| `generateRandom()` | Randomly places food and barriers on the board. |  
| `isgameover()` | Checks if the game has ended. |  

### 🔄 5.3 Game Loop  
The game runs in a **while loop**:  
1. **Draw the board (`draw()`)**  
2. **Read user input (`input()`)**  
3. **Update game logic (`logic()`)**  
4. **Repeat until `gameover` is true**  

---

## 🖥️ 6. Compilation & Execution  

### 📌 6.1 Requirements  
- **C++ Compiler** (`g++` for Windows/Linux/macOS)  
- **Windows** (`conio.h` for `_kbhit()` and `_getch()`)  
- **Linux/macOS** (`termios.h` for user input handling)  

### ⚡ 6.2 Steps to Compile and Run  
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

## 🔮 7. Future Enhancements  
✨ **Multiplayer Mode** – Two snakes on the same board.  
🚀 **Levels & Difficulty Settings** – Speed increases over time.  
⏸️ **Pause/Resume Functionality**.  
⚡ **Power-ups & New Obstacles**.  

---

### 🏆 Developed by **Team Code Mavericks**  
