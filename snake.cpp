#include <bits/stdc++.h>
#include <conio.h> 
#include <cstdlib> 
#include <ctime> 
#include <windows.h>     
using namespace std;

const int height = 20;
const int width = 80;
//declaring and intializing all variables
class snake {
private:
    vector<pair<int, int>> body;
    pair<int, int> food1;
    int specialFoodX = -1, specialFoodY = -1;
    int poisonFoodX = -1, poisonFoodY = -1;   
    int barrierX, barrierY;
    int specialFoodCounter = 0;

      bool gameover;


public:
    int score=0;
    char direction;
    void generateRandom(int &posX, int &posY) {
    posX = rand() % (width-2)+1;
    posY = rand() % (height-2)+1;
    }
    snake() : direction('N'), gameover(false) {
        body.push_back({ width / 2, height / 2 });
        body.push_back({ width / 2 - 1, height / 2 });
        body.push_back({ width / 2 - 2, height / 2 });

        generateRandom(food1.first, food1.second);
        generateRandom(poisonFoodX, poisonFoodY);
        generateRandom(barrierX, barrierY);
    }

//printing the board
    void draw() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorPos = {0, 0}; 
        SetConsoleCursorPosition(hConsole, cursorPos);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    cout << "#"; // Boundary
                }
                else if (i == body[0].second && j == body[0].first) {
                    cout << "O"; // Snake Head
                }
                else if (i == food1.second && j == food1.first) {
                    cout << "@";
                    

                }
                else if(i==specialFoodY && j==specialFoodX){
                    cout << "$"; // Special Food
                    
                    

                }
                else if(i==poisonFoodY && j==poisonFoodX){
                    cout << "X"; // Poisonous Food
                    
                }
                else if(i==barrierY && j==barrierX){
                    cout << "#"; // Barrier

                }
                
                else {
                    bool isbodypart = false;
                    for (int k = 1; k < body.size(); k++) {
                        if (body[k].first == j && body[k].second == i) {
                            cout << "o"; // Snake Body
                            isbodypart = true;
                            break;
                        }
                    }
                    if (!isbodypart) {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }

        cout << "\nScore: " << score << endl;
    }
//checking the input
    void input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                if (direction != 'R') direction = 'L';
                break;
            case 'w':
                if (direction != 'D') direction = 'U';
                break;
            case 's':
                if (direction != 'U') direction = 'D';
                break;
            case 'd':
                if (direction != 'L') direction = 'R';
                break;
            case 'x':
                gameover = true;
                break;
            case 75: 
                if (direction != 'R') direction = 'L'; 
                break; 
            case 77: 
                if (direction != 'L') direction = 'R'; 
                break; 
            case 72:
                if (direction != 'D') direction = 'U'; 
                break; 
            case 80: 
                if (direction != 'U') direction = 'D'; 
                break;
            
            }
        }
    }
//logic for eating food and collision
    void logic() {
        if(direction=='N'){
            return;
        }
        pair<int, int> newhead = body[0];

        switch (direction) {
        case 'L':
            newhead.first--;
            break;
        case 'R':
            newhead.first++;
            break;
        case 'U':
            newhead.second--; 
            break;
        case 'D':
            newhead.second++; 
            break;
        }
        

        // Checking the collision with walls
        if (newhead.first == 0 || newhead.first == width - 1 || newhead.second == 0 || newhead.second == height-1||(newhead.first == barrierX && newhead.second == barrierY)) {
            gameover = true;
            return;
        }

        // Checking the collision with itself
        for (int i = 1; i < body.size(); i++) {
            if (newhead.first == body[i].first && newhead.second == body[i].second) {
                gameover = true;
                return;
            }
        }
        
        // Checking if any food is eaten
        if (newhead.first == food1.first && newhead.second == food1.second) {
            body.insert(body.begin(), newhead);
            
            score++;
            
            specialFoodCounter++;
            generateRandom(food1.first,food1.second);
            if(specialFoodCounter>=5){
                generateRandom(specialFoodX, specialFoodY);
                specialFoodCounter=0;
            }
            
            }
        else if(newhead.first == specialFoodX && newhead.second == specialFoodY){
            score += 3;
            specialFoodX=specialFoodY=-1;
            
        }  
        else if (newhead.first == poisonFoodX && newhead.second == poisonFoodY){
            score -=5;
            score=max(0,score-5);
            generateRandom(poisonFoodX,poisonFoodY);
            
        }
        else {
            body.insert(body.begin(), newhead);
            body.pop_back();
        }
    }

    bool isgameover() const {
        return gameover;
    }


};

void HideCursor()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(console, &cursorInfo);
}

int main() {
    srand(time(0)); 
    snake game;
    
    while (!game.isgameover()) {
        game.draw();
        game.input();
        game.logic();
        Sleep(30);
        HideCursor();
    

}

    cout << "Game Over And Final Score: " << game.score << endl;
    return 0;
}
