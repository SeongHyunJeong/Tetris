#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib> // rand
#include <ctime> // time
#include <algorithm> // copy

using namespace std;

#define TABLEX 15
#define TABLEY 38

#define LEFT 75 // ←
#define RIGHT 77  // →
#define UP 72 // ↑
#define DOWN 80 // ↓
#define SPACE 32 // space

//콘솔 커서 위치 이동
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CursorView(char show) {
    CONSOLE_CURSOR_INFO ConsoleCursor;

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

const int block1[4][4][4] = { //막대모양
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {2, 2, 2, 2},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {2, 2, 2, 2},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
    }
};

const int block2[4][4][4] = { //네모 모양
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0},
    }
};

const int block3[4][4][4] = { //계단 모양
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {2, 2, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 2, 0},
        {0, 0, 2, 0},
    },
  {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {2, 2, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 2, 0},
        {0, 0, 2, 0},
    }
};


const int block4[4][4][4] = { //T자 모양
    {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {2, 2, 2, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 2, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {2, 2, 2, 0},
        {0, 2, 0, 0},
    }
};

const int block5[4][4][4] = { //ㄴ자 모양
    {
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 2, 0},
        {2, 2, 2, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 2, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 2},
        {0, 2, 0, 0},
        {0, 0, 0, 0},
    }
};

class Block {
protected:
    int blockShape[4][4][4];
    int x;
    int y;
    int rotation;

public:
    int getShape(int rotation, int x, int y) {
        return blockShape[rotation][x][y];
    }
    int getY() {
        return y;
    }
    int getX() {
        return x;
    }
    int getRotation() {
        return rotation;
    }
    void up() {
        y--;
    }
    void down() { // 블럭 한 칸 아래 이동
        y++;
    }
    void left() { // 블럭 한 칸 왼쪽 이동
        x--;
    }
    void right() { // 블럭 한 칸 오른쪽 이동
        x++;
    }
    void rotate() {
        rotation = (rotation + 1) % 4;
    }
    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->y = y;
    }
    void setRotationCount(int r) {
        this->rotation = r;
    }
    void setShape(int r, int y, int x, int value) {
        this->blockShape[r][y][x] = value;
    }
};

class backup {
public:
    /*블럭 백업*/
    static void updateBlock(Block* source, Block& backupBlock) {
        backupBlock.setX(source->getX()); // 블럭의 x좌표 백업
        backupBlock.setY(source->getY()); // 블럭의 y좌표 백업
        backupBlock.setRotationCount(source->getRotation()); // 블럭의 회전 상태 변수 백업
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    backupBlock.setShape(i, j, k, source->getShape(i, j, k)); // 블럭의 모양 백업
                }
            }
        }
    }
    /*table 백업*/
    static void updateTable(vector<vector<int> >& source, vector<vector<int> >& backupTable) {
        backupTable.resize(source.size(), vector<int>(source.size())); // 기존 table의 크기만큼 2차원 벡터 크기 할당
        copy(source.begin(), source.end(), backupTable.begin()); // 기존 table vector을 backupTable vector에 백업
    }
};

class Block1 : public Block {
public:
    Block1() {
        x = TABLEX / 2 - 2;
        y = 1;
        rotation = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    blockShape[i][j][k] = block1[i][j][k]; // 블럭 객체 정보 저장
                }
            }
        }
    }
};

class Block2 : public Block {
public:
    Block2() {
        x = TABLEX / 2 - 2;
        y = 1;
        rotation = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    blockShape[i][j][k] = block2[i][j][k]; // 블럭 객체 정보 저장
                }
            }
        }
    }
};
class Block3 : public Block {
public:
    Block3() {
        x = TABLEX / 2 - 2;
        y = 1;
        rotation = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    blockShape[i][j][k] = block3[i][j][k]; // 블럭 객체 정보 저장
                }
            }
        }
    }
};

class Block4 : public Block {
public:
    Block4() {
        x = TABLEX / 2 - 2;
        y = 1;
        rotation = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    blockShape[i][j][k] = block4[i][j][k]; // 블럭 객체 정보 저장
                }
            }
        }
    }
};
class Block5 : public Block {
public:
    Block5() {
        x = TABLEX / 2 - 2;
        y = 1;
        rotation = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    blockShape[i][j][k] = block5[i][j][k]; // 블럭 객체 정보 저장
                }
            }
        }
    }
};

void titleScene() {
    cout << "\n\n\n\n";
    cout << "\t\t"; cout << "@@@@@@@@@@@@  @@@@@@@@@   @@@@@@@@@@@  @@@@@@@@   @   @@@@@@@@@@@\n";
    cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
    cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
    cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @     @    @   @@@@@@@@@@@\n";
    cout << "\t\t"; cout << "      @       @                @       @ @ @      @             @\n";
    cout << "\t\t"; cout << "      @       @                @       @     @    @             @\n";
    cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @      @   @   @@@@@@@@@@@\n\n\n\n\n";
    cout << "\t\t"; cout << "                게임을 시작하려면 아무키나 누르세요.\n\n\n\n\n\n\n";
    getchar();
    system("cls");
}

class GameTable {
private:
    int x;
    int y;
    Block* blockObject;
    vector<vector<int>> table;
public:
    GameTable(int x, int y) {
        this->x = x;
        this->y = y;
        blockObject = nullptr;
        for (int i = 0; i < y; i++) {
            vector<int> temp;
            for (int j = 0; j < x; j++) {
                temp.push_back(0);
            }
            table.push_back(temp);
        }

        for (int i = 0; i < x; i++) {
            table[0][i] = 1;
            table[y - 1][i] = 4;
        }
        for (int i = 1; i < y-1; i++) {
            table[i][0] = 1;
            table[i][x-1] = 1;
        }
    }

    void DrawTable() {
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (table[i][j] == 1 || table[i][j] == 4)
                    cout << "□";
                else if (table[i][j] == 2 || table[i][j] == 3)
                    cout << "■";
                else
                    cout << "  ";
            }
            cout << "\n";
        }
    }

    void CreateBlock() {
        srand((unsigned int)time(NULL));
        int randBlock = rand() % 5 + 1; // 1 ~ 5 블럭
        if (randBlock == 1) blockObject = new Block1();
        else if (randBlock == 2) blockObject = new Block2();
        else if (randBlock == 3) blockObject = new Block3();
        else if (randBlock == 4) blockObject = new Block4();
        else if (randBlock == 5) blockObject = new Block5();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range 방지

                table[Y][X] = blockObject->getShape(blockObject->getRotation(), i, j);
                //블럭 객체를 테이블에 업데이트
            }
        }
    }

    void controlBlock(int key) {
        /*백업*/
        Block backupBlock; // 백업용 Block 객체
        vector<vector<int> > backupTable; // 백업용 table vector
        backup::updateBlock(blockObject, backupBlock); // block 백업
        backup::updateTable(table, backupTable); // table 백업
        //기존 블럭 삭제
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range 방지

                if (table[Y][X] == 2) table[Y][X] = 0;
            }
        }



        if (key == LEFT) blockObject->left();
        if (key == RIGHT) blockObject->right();
        if (key == UP) blockObject->rotate();
        if (key == DOWN) blockObject->down();
       
        //블럭 재생성
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range 방지

                int moveBlock = blockObject->getShape(blockObject->getRotation(), i, j);
                if (moveBlock != 2) continue;
                if(table[Y][X] == 0) { // 빈공간이면 (갱신)
                    table[Y][X] = moveBlock; // 블럭을 이동시킴
                }
                else if (table[Y][X] == 1) { // 블럭이 양 옆 벽면에 닿으면 (취소)
                    copy(backupTable.begin(), backupTable.end(), table.begin()); // table 백업
                    blockObject->setX(backupBlock.getX()); // 블럭 x 좌표 백업
                    blockObject->setY(backupBlock.getY()); // 블럭 y 좌표 백업
                    return; // 함수 종료
                }
                else if (table[Y][X] == 4 || table[Y][X] == 3) { //만약에 맨 밑바닥에 접촉했으면
                    copy(backupTable.begin(), backupTable.end(), table.begin()); // table 백업
                    blockObject->setX(backupBlock.getX()); // 블럭 x 좌표 백업
                    blockObject->setY(backupBlock.getY()); // 블럭 y 좌표 백업
                    if (key == DOWN) { // 만약 아랫 방향일 경우에
                        BuildBlock(); // 블럭을 쌓고
                        CreateBlock(); // 새로운 블럭을 만듬
                    }
                    return; // 함수 종료
                }
            }
        }
    }
    void BuildBlock() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range 방지

                int blockValue = blockObject->getShape(blockObject->getRotation(), i, j); //블럭 배열 값 얻기
                if (blockValue != 2) continue; // 블럭이 아니면 무시 (블럭은 2로 이루어져있음)
                table[Y][X] = 3;
            }
        }
    }

    void DeleteLinear() {
        for (int Y = 1; Y < TABLEY - 1; Y++) {
            bool isLinear = true;
            for (int X = 1; X < TABLEX - 1; X++) {
                if (table[Y][X] != 3) isLinear = false;
            }
            if (isLinear) {
                for (int i = Y; i > 1; i--) {
                    for (int j = 1; j < TABLEX - 1; j++) {
                        table[i][j] = table[i - 1][j];
                    }
                }
            }
        }
    }

    

};

int main() {
    CursorView(false); // 콘솔 화면 커서 제거 
    system("mode con cols=100 lines=40 | title 테트리스 게임"); // 콘솔창 크기 및 제목 설정
    titleScene();
    GameTable* gameTable;
    gameTable = new GameTable(TABLEX, TABLEY);
    gameTable->CreateBlock();
    gameTable->DrawTable();

    while (true) { // 방향키 입력 이벤트
        int nSelect;
        int timer = 0;
        clock_t start, end;
        start = clock();
        float time;
        while (true) { // 방향키 입력 이벤트
            int nSelect;
            end = clock();
            time = ((float)(end - start) / CLOCKS_PER_SEC);
            if (time >= 1) { // 약 1초가 지나면
                gameTable->controlBlock(DOWN); //블럭을 한 칸 떨어뜨림
                start = clock(); // 시간을 다시 잰다
            }
            if (_kbhit()) {
                nSelect = _getch();
                if (nSelect == 224) {
                    nSelect = _getch();
                    switch (nSelect) {
                    case LEFT: // 화살표 왼쪽 눌렀을 떄
                        gameTable->controlBlock(LEFT); // 블럭을 한 칸 왼쪽으로 이동
                        break;
                    case RIGHT: // 화살표 오른쪽 눌렀을 때
                        gameTable->controlBlock(RIGHT); // 블럭을 한 칸 오른쪽으로 이동
                        break;
                    case UP:
                        gameTable->controlBlock(UP);
                        break;
                    case DOWN:
                        gameTable->controlBlock(DOWN);
                        break;
                    default:
                        break;
                    }
                }

            }
            gotoxy(0, 0); //system("cls") 안쓰고 (0, 0)으로 커서 이동 후
            gameTable->DrawTable();
            gameTable->DeleteLinear();
        }

    }
}