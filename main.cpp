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

#define LEFT 75 // ��
#define RIGHT 77  // ��
#define UP 72 // ��
#define DOWN 80 // ��
#define SPACE 32 // space

//�ܼ� Ŀ�� ��ġ �̵�
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

const int block1[4][4][4] = { //������
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

const int block2[4][4][4] = { //�׸� ���
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

const int block3[4][4][4] = { //��� ���
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


const int block4[4][4][4] = { //T�� ���
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

const int block5[4][4][4] = { //���� ���
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
    void down() { // �� �� ĭ �Ʒ� �̵�
        y++;
    }
    void left() { // �� �� ĭ ���� �̵�
        x--;
    }
    void right() { // �� �� ĭ ������ �̵�
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
    /*�� ���*/
    static void updateBlock(Block* source, Block& backupBlock) {
        backupBlock.setX(source->getX()); // ���� x��ǥ ���
        backupBlock.setY(source->getY()); // ���� y��ǥ ���
        backupBlock.setRotationCount(source->getRotation()); // ���� ȸ�� ���� ���� ���
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    backupBlock.setShape(i, j, k, source->getShape(i, j, k)); // ���� ��� ���
                }
            }
        }
    }
    /*table ���*/
    static void updateTable(vector<vector<int> >& source, vector<vector<int> >& backupTable) {
        backupTable.resize(source.size(), vector<int>(source.size())); // ���� table�� ũ�⸸ŭ 2���� ���� ũ�� �Ҵ�
        copy(source.begin(), source.end(), backupTable.begin()); // ���� table vector�� backupTable vector�� ���
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
                    blockShape[i][j][k] = block1[i][j][k]; // �� ��ü ���� ����
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
                    blockShape[i][j][k] = block2[i][j][k]; // �� ��ü ���� ����
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
                    blockShape[i][j][k] = block3[i][j][k]; // �� ��ü ���� ����
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
                    blockShape[i][j][k] = block4[i][j][k]; // �� ��ü ���� ����
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
                    blockShape[i][j][k] = block5[i][j][k]; // �� ��ü ���� ����
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
    cout << "\t\t"; cout << "                ������ �����Ϸ��� �ƹ�Ű�� ��������.\n\n\n\n\n\n\n";
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
                    cout << "��";
                else if (table[i][j] == 2 || table[i][j] == 3)
                    cout << "��";
                else
                    cout << "  ";
            }
            cout << "\n";
        }
    }

    void CreateBlock() {
        srand((unsigned int)time(NULL));
        int randBlock = rand() % 5 + 1; // 1 ~ 5 ��
        if (randBlock == 1) blockObject = new Block1();
        else if (randBlock == 2) blockObject = new Block2();
        else if (randBlock == 3) blockObject = new Block3();
        else if (randBlock == 4) blockObject = new Block4();
        else if (randBlock == 5) blockObject = new Block5();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range ����

                table[Y][X] = blockObject->getShape(blockObject->getRotation(), i, j);
                //�� ��ü�� ���̺� ������Ʈ
            }
        }
    }

    void controlBlock(int key) {
        /*���*/
        Block backupBlock; // ����� Block ��ü
        vector<vector<int> > backupTable; // ����� table vector
        backup::updateBlock(blockObject, backupBlock); // block ���
        backup::updateTable(table, backupTable); // table ���
        //���� �� ����
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range ����

                if (table[Y][X] == 2) table[Y][X] = 0;
            }
        }



        if (key == LEFT) blockObject->left();
        if (key == RIGHT) blockObject->right();
        if (key == UP) blockObject->rotate();
        if (key == DOWN) blockObject->down();
       
        //�� �����
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range ����

                int moveBlock = blockObject->getShape(blockObject->getRotation(), i, j);
                if (moveBlock != 2) continue;
                if(table[Y][X] == 0) { // ������̸� (����)
                    table[Y][X] = moveBlock; // ���� �̵���Ŵ
                }
                else if (table[Y][X] == 1) { // ���� �� �� ���鿡 ������ (���)
                    copy(backupTable.begin(), backupTable.end(), table.begin()); // table ���
                    blockObject->setX(backupBlock.getX()); // �� x ��ǥ ���
                    blockObject->setY(backupBlock.getY()); // �� y ��ǥ ���
                    return; // �Լ� ����
                }
                else if (table[Y][X] == 4 || table[Y][X] == 3) { //���࿡ �� �عٴڿ� ����������
                    copy(backupTable.begin(), backupTable.end(), table.begin()); // table ���
                    blockObject->setX(backupBlock.getX()); // �� x ��ǥ ���
                    blockObject->setY(backupBlock.getY()); // �� y ��ǥ ���
                    if (key == DOWN) { // ���� �Ʒ� ������ ��쿡
                        BuildBlock(); // ���� �װ�
                        CreateBlock(); // ���ο� ���� ����
                    }
                    return; // �Լ� ����
                }
            }
        }
    }
    void BuildBlock() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();

                if (Y < 0 || X < 0 || Y >= TABLEY || X >= TABLEX) continue; // array out of range ����

                int blockValue = blockObject->getShape(blockObject->getRotation(), i, j); //�� �迭 �� ���
                if (blockValue != 2) continue; // ���� �ƴϸ� ���� (���� 2�� �̷��������)
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
    CursorView(false); // �ܼ� ȭ�� Ŀ�� ���� 
    system("mode con cols=100 lines=40 | title ��Ʈ���� ����"); // �ܼ�â ũ�� �� ���� ����
    titleScene();
    GameTable* gameTable;
    gameTable = new GameTable(TABLEX, TABLEY);
    gameTable->CreateBlock();
    gameTable->DrawTable();

    while (true) { // ����Ű �Է� �̺�Ʈ
        int nSelect;
        int timer = 0;
        clock_t start, end;
        start = clock();
        float time;
        while (true) { // ����Ű �Է� �̺�Ʈ
            int nSelect;
            end = clock();
            time = ((float)(end - start) / CLOCKS_PER_SEC);
            if (time >= 1) { // �� 1�ʰ� ������
                gameTable->controlBlock(DOWN); //���� �� ĭ ����߸�
                start = clock(); // �ð��� �ٽ� ���
            }
            if (_kbhit()) {
                nSelect = _getch();
                if (nSelect == 224) {
                    nSelect = _getch();
                    switch (nSelect) {
                    case LEFT: // ȭ��ǥ ���� ������ ��
                        gameTable->controlBlock(LEFT); // ���� �� ĭ �������� �̵�
                        break;
                    case RIGHT: // ȭ��ǥ ������ ������ ��
                        gameTable->controlBlock(RIGHT); // ���� �� ĭ ���������� �̵�
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
            gotoxy(0, 0); //system("cls") �Ⱦ��� (0, 0)���� Ŀ�� �̵� ��
            gameTable->DrawTable();
            gameTable->DeleteLinear();
        }

    }
}