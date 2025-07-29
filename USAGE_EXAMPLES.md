# 🐍 Snake Game - Usage Examples & Integration Guide

## Table of Contents
1. [Basic Usage Examples](#basic-usage-examples)
2. [Advanced Integration Patterns](#advanced-integration-patterns)
3. [Game Customization Examples](#game-customization-examples)
4. [Error Handling & Debugging](#error-handling--debugging)
5. [Performance Optimization](#performance-optimization)
6. [Cross-Platform Adaptations](#cross-platform-adaptations)
7. [Testing Examples](#testing-examples)

---

## Basic Usage Examples

### Simple Game Launch
```cpp
#include <bits/stdc++.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

// Include the snake game implementation
#include "snake.cpp"

int main() {
    // Initialize random seed for consistent gameplay
    srand(time(0));
    
    // Create game instance
    snake game;
    
    // Hide cursor for cleaner display
    HideCursor();
    
    // Basic game loop
    while (!game.isgameover()) {
        game.draw();    // Render current state
        game.input();   // Process user input
        game.logic();   // Update game logic
        Sleep(30);      // 30ms delay for ~33 FPS
    }
    
    // Display final score
    cout << "\nGame Over! Final Score: " << game.score << endl;
    system("pause");  // Wait for user input before closing
    
    return 0;
}
```

### Basic Score Tracking
```cpp
int main() {
    srand(time(0));
    snake game;
    HideCursor();
    
    int lastScore = 0;
    
    while (!game.isgameover()) {
        game.draw();
        game.input();
        game.logic();
        
        // Detect score changes
        if (game.score != lastScore) {
            cout << "\nScore increased from " << lastScore 
                 << " to " << game.score << endl;
            lastScore = game.score;
        }
        
        Sleep(30);
    }
    
    cout << "Final Score: " << game.score << endl;
    return 0;
}
```

### Direction Monitoring
```cpp
int main() {
    srand(time(0));
    snake game;
    HideCursor();
    
    char previousDirection = 'N';
    
    while (!game.isgameover()) {
        game.input();
        
        // Log direction changes
        if (game.direction != previousDirection) {
            cout << "Direction changed: " << previousDirection 
                 << " -> " << game.direction << endl;
            previousDirection = game.direction;
        }
        
        game.logic();
        game.draw();
        Sleep(30);
    }
    
    return 0;
}
```

---

## Advanced Integration Patterns

### Game Session Manager
```cpp
class GameSession {
private:
    snake* currentGame;
    int sessionCount;
    int totalScore;
    int highScore;
    vector<int> gameScores;

public:
    GameSession() : currentGame(nullptr), sessionCount(0), 
                   totalScore(0), highScore(0) {}
    
    ~GameSession() {
        if (currentGame) delete currentGame;
    }
    
    void startNewGame() {
        if (currentGame) {
            // Save previous game score
            gameScores.push_back(currentGame->score);
            totalScore += currentGame->score;
            if (currentGame->score > highScore) {
                highScore = currentGame->score;
            }
            delete currentGame;
        }
        
        currentGame = new snake();
        sessionCount++;
        HideCursor();
        
        cout << "Starting Game #" << sessionCount << endl;
        cout << "High Score: " << highScore << endl;
        Sleep(2000);  // Show info for 2 seconds
    }
    
    void playGame() {
        if (!currentGame) {
            startNewGame();
        }
        
        while (!currentGame->isgameover()) {
            currentGame->draw();
            currentGame->input();
            currentGame->logic();
            Sleep(30);
        }
        
        cout << "\nGame Over! Score: " << currentGame->score << endl;
        
        if (currentGame->score > highScore) {
            cout << "NEW HIGH SCORE!" << endl;
        }
    }
    
    void showStatistics() {
        cout << "\n=== Session Statistics ===" << endl;
        cout << "Games Played: " << sessionCount << endl;
        cout << "High Score: " << highScore << endl;
        cout << "Total Score: " << totalScore << endl;
        
        if (sessionCount > 0) {
            cout << "Average Score: " << (totalScore / sessionCount) << endl;
        }
        
        cout << "Score History: ";
        for (int score : gameScores) {
            cout << score << " ";
        }
        cout << endl;
    }
    
    bool askPlayAgain() {
        cout << "Play again? (y/n): ";
        char choice;
        cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }
};

// Usage
int main() {
    srand(time(0));
    GameSession session;
    
    do {
        session.startNewGame();
        session.playGame();
    } while (session.askPlayAgain());
    
    session.showStatistics();
    return 0;
}
```

### Difficulty Manager
```cpp
class DifficultyManager {
public:
    enum Level { EASY, MEDIUM, HARD, EXPERT };
    
private:
    Level currentLevel;
    
public:
    DifficultyManager() : currentLevel(EASY) {}
    
    void setLevel(Level level) { currentLevel = level; }
    
    int getSpeed() const {
        switch (currentLevel) {
            case EASY:   return 100;  // 100ms delay
            case MEDIUM: return 70;   // 70ms delay
            case HARD:   return 40;   // 40ms delay
            case EXPERT: return 20;   // 20ms delay
            default:     return 50;
        }
    }
    
    string getLevelName() const {
        switch (currentLevel) {
            case EASY:   return "Easy";
            case MEDIUM: return "Medium";
            case HARD:   return "Hard";
            case EXPERT: return "Expert";
            default:     return "Unknown";
        }
    }
    
    void displayMenu() {
        cout << "Select Difficulty:" << endl;
        cout << "1. Easy (Slow)" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cout << "4. Expert (Fast)" << endl;
        cout << "Choice: ";
    }
    
    void selectFromInput() {
        displayMenu();
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: setLevel(EASY); break;
            case 2: setLevel(MEDIUM); break;
            case 3: setLevel(HARD); break;
            case 4: setLevel(EXPERT); break;
            default: setLevel(EASY); break;
        }
        
        cout << "Difficulty set to: " << getLevelName() << endl;
    }
};

// Usage with difficulty
int main() {
    srand(time(0));
    
    DifficultyManager difficulty;
    difficulty.selectFromInput();
    
    snake game;
    HideCursor();
    
    cout << "Playing on " << difficulty.getLevelName() << " difficulty" << endl;
    Sleep(2000);
    
    while (!game.isgameover()) {
        game.draw();
        game.input();
        game.logic();
        Sleep(difficulty.getSpeed());  // Use difficulty-based speed
    }
    
    cout << "Final Score: " << game.score << endl;
    return 0;
}
```

### Game State Logger
```cpp
class GameLogger {
private:
    ofstream logFile;
    time_t startTime;
    
public:
    GameLogger(const string& filename) {
        logFile.open(filename, ios::app);
        time(&startTime);
        
        logFile << "\n=== Game Session Started ===" << endl;
        logFile << "Time: " << ctime(&startTime);
    }
    
    ~GameLogger() {
        time_t endTime;
        time(&endTime);
        
        logFile << "Session Duration: " 
                << difftime(endTime, startTime) << " seconds" << endl;
        logFile << "=== Session Ended ===" << endl;
        logFile.close();
    }
    
    void logScore(int score) {
        logFile << "Score: " << score << endl;
    }
    
    void logDirection(char direction) {
        logFile << "Direction changed to: " << direction << endl;
    }
    
    void logEvent(const string& event) {
        time_t now;
        time(&now);
        
        logFile << "[" << ctime(&now) << "] " << event << endl;
    }
};

// Usage with logging
int main() {
    srand(time(0));
    
    GameLogger logger("snake_game.log");
    snake game;
    HideCursor();
    
    char lastDirection = 'N';
    int lastScore = 0;
    
    logger.logEvent("Game started");
    
    while (!game.isgameover()) {
        game.draw();
        game.input();
        
        // Log direction changes
        if (game.direction != lastDirection) {
            logger.logDirection(game.direction);
            lastDirection = game.direction;
        }
        
        game.logic();
        
        // Log score changes
        if (game.score != lastScore) {
            logger.logScore(game.score);
            lastScore = game.score;
        }
        
        Sleep(30);
    }
    
    logger.logEvent("Game ended with score: " + to_string(game.score));
    cout << "Game logged to file!" << endl;
    
    return 0;
}
```

---

## Game Customization Examples

### Custom Snake Class Extension
```cpp
class ExtendedSnake : public snake {
private:
    int powerUpX, powerUpY;
    bool powerUpActive;
    int powerUpTimer;
    bool speedBoost;
    
public:
    ExtendedSnake() : snake(), powerUpActive(false), 
                     powerUpTimer(0), speedBoost(false) {
        generatePowerUp();
    }
    
    void generatePowerUp() {
        generateRandom(powerUpX, powerUpY);
        powerUpActive = true;
    }
    
    // Override draw to include power-ups
    void draw() {
        // Call parent draw method
        snake::draw();
        
        // Add power-up to display (would need to modify original draw)
        if (powerUpActive) {
            cout << "Power-up available at (" << powerUpX 
                 << ", " << powerUpY << ")" << endl;
        }
        
        if (speedBoost) {
            cout << "SPEED BOOST ACTIVE! (" << powerUpTimer << ")" << endl;
        }
    }
    
    // Override logic to handle power-ups
    void logic() {
        // Call parent logic
        snake::logic();
        
        // Handle power-up timer
        if (speedBoost && powerUpTimer > 0) {
            powerUpTimer--;
            if (powerUpTimer <= 0) {
                speedBoost = false;
                cout << "Speed boost ended!" << endl;
            }
        }
        
        // Check power-up collision (simplified - would need access to head position)
        // This is a conceptual example since we can't access private members
    }
    
    void activateSpeedBoost() {
        speedBoost = true;
        powerUpTimer = 100;  // 100 frames of speed boost
        powerUpActive = false;
    }
    
    bool hasSpeedBoost() const { return speedBoost; }
};

// Usage
int main() {
    srand(time(0));
    ExtendedSnake game;
    HideCursor();
    
    while (!game.isgameover()) {
        game.draw();
        game.input();
        game.logic();
        
        // Faster speed when power-up is active
        int delay = game.hasSpeedBoost() ? 15 : 30;
        Sleep(delay);
    }
    
    return 0;
}
```

### Multi-Player Score Tracking
```cpp
struct Player {
    string name;
    int bestScore;
    int gamesPlayed;
    vector<int> recentScores;
    
    Player(const string& n) : name(n), bestScore(0), gamesPlayed(0) {}
    
    void addScore(int score) {
        recentScores.push_back(score);
        if (recentScores.size() > 5) {
            recentScores.erase(recentScores.begin());
        }
        
        if (score > bestScore) {
            bestScore = score;
        }
        gamesPlayed++;
    }
    
    double getAverageScore() const {
        if (recentScores.empty()) return 0.0;
        
        int total = 0;
        for (int score : recentScores) {
            total += score;
        }
        return static_cast<double>(total) / recentScores.size();
    }
};

class MultiPlayerManager {
private:
    vector<Player> players;
    int currentPlayerIndex;
    
public:
    MultiPlayerManager() : currentPlayerIndex(0) {}
    
    void addPlayer(const string& name) {
        players.emplace_back(name);
    }
    
    Player& getCurrentPlayer() {
        return players[currentPlayerIndex];
    }
    
    void nextPlayer() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
    
    void displayLeaderboard() {
        cout << "\n=== LEADERBOARD ===" << endl;
        
        // Sort players by best score
        vector<Player> sortedPlayers = players;
        sort(sortedPlayers.begin(), sortedPlayers.end(),
             [](const Player& a, const Player& b) {
                 return a.bestScore > b.bestScore;
             });
        
        for (size_t i = 0; i < sortedPlayers.size(); i++) {
            const Player& player = sortedPlayers[i];
            cout << (i + 1) << ". " << player.name 
                 << " - Best: " << player.bestScore
                 << " - Avg: " << fixed << setprecision(1) 
                 << player.getAverageScore()
                 << " - Games: " << player.gamesPlayed << endl;
        }
    }
    
    void playRound() {
        for (size_t i = 0; i < players.size(); i++) {
            Player& player = getCurrentPlayer();
            
            cout << "\n" << player.name << "'s turn!" << endl;
            cout << "Best score: " << player.bestScore << endl;
            system("pause");
            
            // Play game
            snake game;
            HideCursor();
            
            while (!game.isgameover()) {
                game.draw();
                game.input();
                game.logic();
                Sleep(30);
            }
            
            cout << player.name << " scored: " << game.score << endl;
            player.addScore(game.score);
            
            nextPlayer();
            system("pause");
        }
        
        displayLeaderboard();
    }
};

// Usage
int main() {
    srand(time(0));
    
    MultiPlayerManager manager;
    
    // Add players
    int numPlayers;
    cout << "Number of players: ";
    cin >> numPlayers;
    
    for (int i = 0; i < numPlayers; i++) {
        string name;
        cout << "Player " << (i + 1) << " name: ";
        cin >> name;
        manager.addPlayer(name);
    }
    
    // Play multiple rounds
    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        manager.playRound();
        
        cout << "Play another round? (y/n): ";
        cin >> playAgain;
    }
    
    return 0;
}
```

---

## Error Handling & Debugging

### Safe Game Wrapper
```cpp
class SafeSnakeGame {
private:
    snake* game;
    bool isValid;
    string lastError;
    
public:
    SafeSnakeGame() : game(nullptr), isValid(false) {
        try {
            game = new snake();
            isValid = true;
        } catch (const exception& e) {
            lastError = e.what();
            game = nullptr;
        }
    }
    
    ~SafeSnakeGame() {
        if (game) {
            delete game;
        }
    }
    
    bool isGameValid() const { return isValid && game != nullptr; }
    
    string getLastError() const { return lastError; }
    
    bool runGame() {
        if (!isGameValid()) {
            cout << "Game initialization failed: " << lastError << endl;
            return false;
        }
        
        try {
            HideCursor();
            
            while (!game->isgameover()) {
                game->draw();
                game->input();
                game->logic();
                Sleep(30);
            }
            
            cout << "Final Score: " << game->score << endl;
            return true;
            
        } catch (const exception& e) {
            cout << "Game error: " << e.what() << endl;
            return false;
        }
    }
    
    int getScore() const {
        return isGameValid() ? game->score : -1;
    }
};

// Usage with error handling
int main() {
    srand(time(0));
    
    SafeSnakeGame safeGame;
    
    if (safeGame.runGame()) {
        cout << "Game completed successfully!" << endl;
    } else {
        cout << "Game failed to run properly." << endl;
    }
    
    return 0;
}
```

### Debug Information Display
```cpp
class DebugSnake : public snake {
private:
    bool debugMode;
    
public:
    DebugSnake() : snake(), debugMode(false) {}
    
    void toggleDebug() { debugMode = !debugMode; }
    
    void draw() {
        // Call parent draw
        snake::draw();
        
        if (debugMode) {
            cout << "\n=== DEBUG INFO ===" << endl;
            cout << "Direction: " << direction << endl;
            cout << "Score: " << score << endl;
            // Note: Private members would need accessor methods
            cout << "Game Over: " << (isgameover() ? "Yes" : "No") << endl;
            cout << "=================" << endl;
        }
    }
    
    // Additional debug methods would require access to private members
    // or additional accessor methods in the base class
};

// Debug usage
int main() {
    srand(time(0));
    DebugSnake game;
    HideCursor();
    
    cout << "Press 'F1' for debug mode (not implemented in this example)" << endl;
    
    while (!game.isgameover()) {
        game.draw();
        game.input();
        game.logic();
        Sleep(30);
    }
    
    return 0;
}
```

---

## Performance Optimization

### Frame Rate Controller
```cpp
class FrameRateController {
private:
    chrono::high_resolution_clock::time_point lastFrame;
    int targetFPS;
    int actualFPS;
    int frameCount;
    chrono::high_resolution_clock::time_point fpsCounterStart;
    
public:
    FrameRateController(int fps = 30) : targetFPS(fps), actualFPS(0), frameCount(0) {
        lastFrame = chrono::high_resolution_clock::now();
        fpsCounterStart = lastFrame;
    }
    
    void waitForNextFrame() {
        auto now = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastFrame);
        
        int targetDelay = 1000 / targetFPS;
        
        if (elapsed.count() < targetDelay) {
            Sleep(targetDelay - elapsed.count());
        }
        
        lastFrame = chrono::high_resolution_clock::now();
        
        // Update FPS counter
        frameCount++;
        auto fpsElapsed = chrono::duration_cast<chrono::seconds>(lastFrame - fpsCounterStart);
        
        if (fpsElapsed.count() >= 1) {
            actualFPS = frameCount;
            frameCount = 0;
            fpsCounterStart = lastFrame;
        }
    }
    
    int getActualFPS() const { return actualFPS; }
    void setTargetFPS(int fps) { targetFPS = fps; }
};

// Usage with frame rate control
int main() {
    srand(time(0));
    
    snake game;
    FrameRateController frameController(30);  // 30 FPS
    HideCursor();
    
    while (!game.isgameover()) {
        game.draw();
        game.input();
        game.logic();
        
        frameController.waitForNextFrame();
        
        // Display FPS (optional)
        if (frameController.getActualFPS() > 0) {
            cout << "FPS: " << frameController.getActualFPS() << endl;
        }
    }
    
    return 0;
}
```

### Memory Usage Monitor
```cpp
class MemoryMonitor {
private:
    size_t initialMemory;
    
public:
    MemoryMonitor() {
        initialMemory = getCurrentMemoryUsage();
    }
    
    size_t getCurrentMemoryUsage() {
        // Simplified memory monitoring (platform-specific implementation needed)
        return 0;  // Placeholder
    }
    
    void reportMemoryUsage() {
        size_t current = getCurrentMemoryUsage();
        cout << "Memory usage: " << (current - initialMemory) 
             << " bytes from start" << endl;
    }
};
```

---

## Cross-Platform Adaptations

### Platform-Agnostic Input Handler
```cpp
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    
    bool kbhit() { return _kbhit(); }
    int getch() { return _getch(); }
    void sleepMs(int ms) { Sleep(ms); }
    
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    
    bool kbhit() {
        int ch = getchar();
        if (ch != EOF) {
            ungetc(ch, stdin);
            return true;
        }
        return false;
    }
    
    int getch() { return getchar(); }
    void sleepMs(int ms) { usleep(ms * 1000); }
#endif

// Cross-platform snake implementation would require modifications
// to the original snake class to use these functions
```

---

## Testing Examples

### Unit Test Framework
```cpp
class SnakeTestSuite {
private:
    int testsRun;
    int testsPassed;
    
public:
    SnakeTestSuite() : testsRun(0), testsPassed(0) {}
    
    void assert(bool condition, const string& testName) {
        testsRun++;
        if (condition) {
            testsPassed++;
            cout << "[PASS] " << testName << endl;
        } else {
            cout << "[FAIL] " << testName << endl;
        }
    }
    
    void runAllTests() {
        testInitialization();
        testScoring();
        testMovement();
        testCollision();
        
        cout << "\nTest Results: " << testsPassed << "/" << testsRun 
             << " tests passed" << endl;
    }
    
private:
    void testInitialization() {
        snake game;
        assert(game.score == 0, "Initial score is zero");
        assert(game.direction == 'N', "Initial direction is N");
        assert(!game.isgameover(), "Game not over initially");
    }
    
    void testScoring() {
        snake game;
        int initialScore = game.score;
        // Would need public methods to simulate food consumption
        // This is conceptual since we can't access private methods
        assert(game.score >= initialScore, "Score doesn't decrease unexpectedly");
    }
    
    void testMovement() {
        snake game;
        game.direction = 'U';
        assert(game.direction == 'U', "Direction setter works");
    }
    
    void testCollision() {
        snake game;
        // Would need way to set game state for testing
        // This would require additional testing methods in the snake class
    }
};

// Run tests
int main() {
    SnakeTestSuite tests;
    tests.runAllTests();
    return 0;
}
```

---

## Complete Integration Example

### Full-Featured Game Application
```cpp
class SnakeGameApplication {
private:
    GameSession session;
    DifficultyManager difficulty;
    GameLogger* logger;
    FrameRateController frameController;
    
public:
    SnakeGameApplication() : frameController(30) {
        logger = new GameLogger("snake_game.log");
    }
    
    ~SnakeGameApplication() {
        delete logger;
    }
    
    void run() {
        showWelcome();
        difficulty.selectFromInput();
        
        do {
            playGameSession();
        } while (session.askPlayAgain());
        
        session.showStatistics();
        showGoodbye();
    }
    
private:
    void showWelcome() {
        cout << "================================" << endl;
        cout << "    🐍 ADVANCED SNAKE GAME 🐍   " << endl;
        cout << "================================" << endl;
        cout << "Features: Multiple difficulty levels," << endl;
        cout << "          Session tracking," << endl;
        cout << "          Automatic logging" << endl;
        cout << "================================" << endl;
    }
    
    void playGameSession() {
        session.startNewGame();
        logger->logEvent("New game started");
        
        snake game;
        HideCursor();
        
        frameController.setTargetFPS(30 + (difficulty.getSpeed() / 10));
        
        while (!game.isgameover()) {
            game.draw();
            game.input();
            game.logic();
            
            frameController.waitForNextFrame();
        }
        
        logger->logEvent("Game ended with score: " + to_string(game.score));
    }
    
    void showGoodbye() {
        cout << "\nThanks for playing!" << endl;
        cout << "Check snake_game.log for detailed game history." << endl;
    }
};

// Main application entry point
int main() {
    srand(time(0));
    
    try {
        SnakeGameApplication app;
        app.run();
    } catch (const exception& e) {
        cout << "Application error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```

---

*Comprehensive Usage Examples for Snake Game*
*Covers basic usage through advanced integration patterns*