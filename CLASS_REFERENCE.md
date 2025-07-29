# 🐍 Snake Class Reference

## Table of Contents
1. [Class Overview](#class-overview)
2. [Class Architecture](#class-architecture)
3. [Member Variables](#member-variables)
4. [Constructor Details](#constructor-details)
5. [Method Reference](#method-reference)
6. [Game State Management](#game-state-management)
7. [Internal Algorithms](#internal-algorithms)
8. [Memory Management](#memory-management)

---

## Class Overview

The `snake` class is the core component of the Snake Game, implementing a complete game engine within a single class. It follows object-oriented principles and encapsulates all game logic, state management, and rendering operations.

### Class Signature
```cpp
class snake {
private:
    // Private member variables and internal state
public:
    // Public interface for game interaction
};
```

### Design Pattern
- **Encapsulation**: All game state is contained within the class
- **Single Responsibility**: The class handles all snake game operations
- **State Machine**: Manages game states (playing, game over)

---

## Class Architecture

### Class Diagram
```
┌─────────────────────────────────────┐
│             snake class             │
├─────────────────────────────────────┤
│ Private Members:                    │
│ - vector<pair<int,int>> body        │
│ - pair<int,int> food1               │
│ - int specialFoodX, specialFoodY    │
│ - int poisonFoodX, poisonFoodY      │
│ - int barrierX, barrierY            │
│ - int specialFoodCounter            │
│ - bool gameover                     │
├─────────────────────────────────────┤
│ Public Members:                     │
│ + int score                         │
│ + char direction                    │
├─────────────────────────────────────┤
│ Public Methods:                     │
│ + snake()                          │
│ + void generateRandom(int&, int&)   │
│ + void draw()                       │
│ + void input()                      │
│ + void logic()                      │
│ + bool isgameover() const           │
└─────────────────────────────────────┘
```

---

## Member Variables

### Private Members

#### `vector<pair<int, int>> body`
- **Type**: `std::vector<std::pair<int, int>>`
- **Purpose**: Stores all segments of the snake's body
- **Structure**: Each pair represents (x, y) coordinates
- **Index 0**: Snake head position
- **Index 1+**: Body segments in order from neck to tail
- **Growth**: New segments added at head, tail removed when not eating

**Example Structure:**
```cpp
// Snake with 4 segments
body[0] = {10, 5};  // Head
body[1] = {9, 5};   // Neck
body[2] = {8, 5};   // Body
body[3] = {7, 5};   // Tail
```

#### `pair<int, int> food1`
- **Type**: `std::pair<int, int>`
- **Purpose**: Position of regular food item
- **Representation**: (x, y) coordinates on game board
- **Regeneration**: New position generated when consumed
- **Rendering**: Displayed as `@` character

#### `int specialFoodX, specialFoodY`
- **Type**: `int` (separate variables)
- **Purpose**: Position of special bonus food
- **Special Values**: `-1` indicates no special food present
- **Trigger**: Appears after consuming 5 regular foods
- **Rendering**: Displayed as `$` character
- **Points**: Awards +3 points when consumed

#### `int poisonFoodX, poisonFoodY`
- **Type**: `int` (separate variables)
- **Purpose**: Position of poisonous food
- **Behavior**: Randomly regenerates position when consumed
- **Rendering**: Displayed as `X` character
- **Points**: Deducts 5 points (minimum score 0)

#### `int barrierX, barrierY`
- **Type**: `int` (separate variables)
- **Purpose**: Position of static obstacle
- **Behavior**: Remains in same position throughout game
- **Collision**: Causes immediate game over
- **Rendering**: Displayed as `#` character

#### `int specialFoodCounter`
- **Type**: `int`
- **Purpose**: Tracks regular foods consumed toward special food
- **Range**: 0-4 (resets to 0 when special food spawns)
- **Increment**: +1 for each regular food consumed
- **Reset**: Set to 0 when special food appears

#### `bool gameover`
- **Type**: `bool`
- **Purpose**: Game state flag
- **Initial Value**: `false`
- **Set to `true`**: When collision occurs or user exits
- **Access**: Read-only through `isgameover()` method

### Public Members

#### `int score`
- **Type**: `int`
- **Initial Value**: `0`
- **Modification**: Updated automatically by game logic
- **Increment**: +1 for regular food, +3 for special food
- **Decrement**: -5 for poison food (minimum 0)
- **Access**: Direct read access for external display

#### `char direction`
- **Type**: `char`
- **Purpose**: Current movement direction
- **Values**: `'N'` (none), `'U'` (up), `'D'` (down), `'L'` (left), `'R'` (right)
- **Initial**: `'N'` (no movement until first input)
- **Constraints**: Cannot reverse to opposite direction

---

## Constructor Details

### `snake()` Constructor
```cpp
snake() : direction('N'), gameover(false)
```

#### Initialization List
- `direction('N')`: Sets initial direction to "no movement"
- `gameover(false)`: Sets initial game state to active

#### Constructor Body Operations
1. **Snake Body Initialization**:
   ```cpp
   body.push_back({ width / 2, height / 2 });      // Head at center
   body.push_back({ width / 2 - 1, height / 2 });  // First segment left of head
   body.push_back({ width / 2 - 2, height / 2 });  // Second segment further left
   ```

2. **Random Element Placement**:
   ```cpp
   generateRandom(food1.first, food1.second);     // Place regular food
   generateRandom(poisonFoodX, poisonFoodY);      // Place poison food
   generateRandom(barrierX, barrierY);            // Place barrier
   ```

#### Initial State
- Snake: 3 segments horizontally aligned at board center
- Score: 0
- Special food: Not present (coordinates -1, -1)
- Counter: 0 foods consumed toward special food

---

## Method Reference

### `void generateRandom(int &posX, int &posY)`

#### Algorithm
```cpp
void generateRandom(int &posX, int &posY) {
    posX = rand() % (width-2) + 1;   // Range: 1 to width-2
    posY = rand() % (height-2) + 1;  // Range: 1 to height-2
}
```

#### Boundary Logic
- **Excludes**: Border positions (0 and max-1)
- **Ensures**: Generated positions are within playable area
- **Avoids**: Wall collision for placed elements

#### Usage Patterns
- Food placement after consumption
- Initial element positioning
- Poison food regeneration

### `void draw()`

#### Rendering Algorithm
1. **Console Management**:
   ```cpp
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   COORD cursorPos = {0, 0};
   SetConsoleCursorPosition(hConsole, cursorPos);
   ```

2. **Board Iteration**:
   ```cpp
   for (int i = 0; i < height; i++) {
       for (int j = 0; j < width; j++) {
           // Determine what to render at position (j, i)
       }
   }
   ```

3. **Priority Rendering Order**:
   1. Walls and barriers (`#`)
   2. Snake head (`O`)
   3. Regular food (`@`)
   4. Special food (`$`)
   5. Poison food (`X`)
   6. Snake body (`o`)
   7. Empty space (` `)

#### Performance Characteristics
- **Time Complexity**: O(width × height + snake_length)
- **Console Calls**: One per character + cursor positioning
- **Frame Rate**: Called once per game loop iteration

### `void input()`

#### Input Handling Logic
```cpp
if (_kbhit()) {  // Check if key is pressed
    switch (_getch()) {  // Get the pressed key
        // Process movement keys with direction constraints
    }
}
```

#### Direction Constraints Implementation
```cpp
case 'a':
    if (direction != 'R') direction = 'L';  // Prevent Left←→Right reversal
    break;
case 'w':
    if (direction != 'D') direction = 'U';  // Prevent Up←→Down reversal
    break;
// Similar constraints for other directions
```

#### Supported Input Types
- **Character Keys**: `w`, `a`, `s`, `d` (case-sensitive)
- **Arrow Keys**: Virtual key codes 72, 75, 77, 80
- **Exit Key**: `x` (immediate game over)
- **Non-blocking**: Uses `_kbhit()` to avoid waiting for input

### `void logic()`

#### Movement Calculation
```cpp
pair<int, int> newhead = body[0];  // Copy current head position

switch (direction) {
    case 'L': newhead.first--;  break;   // Move left
    case 'R': newhead.first++;  break;   // Move right
    case 'U': newhead.second--; break;   // Move up
    case 'D': newhead.second++; break;   // Move down
}
```

#### Collision Detection Sequence
1. **Wall Collision**:
   ```cpp
   if (newhead.first == 0 || newhead.first == width - 1 || 
       newhead.second == 0 || newhead.second == height - 1) {
       gameover = true;
       return;
   }
   ```

2. **Barrier Collision**:
   ```cpp
   if (newhead.first == barrierX && newhead.second == barrierY) {
       gameover = true;
       return;
   }
   ```

3. **Self Collision**:
   ```cpp
   for (int i = 1; i < body.size(); i++) {
       if (newhead.first == body[i].first && newhead.second == body[i].second) {
           gameover = true;
           return;
       }
   }
   ```

#### Food Consumption Logic
1. **Regular Food** (`@`):
   ```cpp
   if (newhead.first == food1.first && newhead.second == food1.second) {
       body.insert(body.begin(), newhead);  // Grow snake
       score++;                             // Increase score
       specialFoodCounter++;               // Count toward special food
       generateRandom(food1.first, food1.second);  // New food position
       
       if (specialFoodCounter >= 5) {      // Trigger special food
           generateRandom(specialFoodX, specialFoodY);
           specialFoodCounter = 0;
       }
   }
   ```

2. **Special Food** (`$`):
   ```cpp
   else if (newhead.first == specialFoodX && newhead.second == specialFoodY) {
       score += 3;                         // Bonus points
       specialFoodX = specialFoodY = -1;   // Remove special food
   }
   ```

3. **Poison Food** (`X`):
   ```cpp
   else if (newhead.first == poisonFoodX && newhead.second == poisonFoodY) {
       score = max(0, score - 5);          // Decrease score (minimum 0)
       generateRandom(poisonFoodX, poisonFoodY);  // Regenerate position
   }
   ```

#### Movement Without Food
```cpp
else {
    body.insert(body.begin(), newhead);  // Add new head
    body.pop_back();                     // Remove tail (no growth)
}
```

### `bool isgameover() const`

#### Simple State Query
```cpp
bool isgameover() const {
    return gameover;
}
```

- **Const Method**: Guarantees no state modification
- **Direct Return**: Returns private `gameover` member
- **Usage**: Loop condition and external state checking

---

## Game State Management

### State Transitions
```
[Initial] → [Playing] → [Game Over]
    ↑           ↓
    └──── [Reset] ←───┘
```

### State Variables
- **Playing State**: `gameover == false`, `direction != 'N'`
- **Initial State**: `gameover == false`, `direction == 'N'`
- **Game Over State**: `gameover == true`

### State Triggers
- **Start Playing**: First directional input
- **Game Over**: Collision detection or 'x' key press
- **Reset**: Create new snake instance

---

## Internal Algorithms

### Snake Growth Algorithm
1. **Normal Movement**: Add head, remove tail (constant length)
2. **Food Consumption**: Add head, keep tail (length increases by 1)
3. **Body Management**: Vector operations maintain segment order

### Food Spawn Algorithm
1. **Generate Random Position**: Within game boundaries
2. **No Collision Check**: May spawn on snake body (design choice)
3. **Immediate Availability**: Can be consumed on same frame

### Special Food Timing
- **Counter-Based**: After exactly 5 regular foods
- **Single Instance**: Only one special food at a time
- **Persistent**: Remains until consumed (doesn't regenerate)

---

## Memory Management

### Dynamic Memory Usage
- **Snake Body**: Grows with `std::vector` (automatic memory management)
- **Maximum Size**: Theoretical maximum = (width-2) × (height-2) segments
- **Typical Size**: 3-50 segments in normal gameplay

### Memory Efficiency
- **Coordinate Storage**: 2 integers per segment (8 bytes on 32-bit, 16 bytes on 64-bit)
- **Vector Overhead**: Capacity may exceed size for growth efficiency
- **Stack Allocation**: All other variables use stack memory

### Performance Implications
- **Vector Reallocations**: May occur during rapid growth
- **Search Operations**: Linear search for self-collision (O(n))
- **Memory Fragmentation**: Minimal due to simple data types

---

*Technical Reference for Snake Game Implementation*
*Version: 1.0*