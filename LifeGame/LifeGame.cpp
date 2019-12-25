#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <stdlib.h>

#include "Cell.h"
#include "CellManager.h"

namespace Console {
    namespace Display
    {
        static void setPosition(int x, int y)
        {
            printf("\033[%d;%dH", y, x);
        }

        static void flush()
        {
            fflush(stdout);
        }

        static void clear()
        {
            printf("\033\[2J");
        }

        static void write(const char * outPutString)
        {
            printf("%s", outPutString);
        }

        static void writeLine(const char * outPutString)
        {
            write((std::string(outPutString) + "\n").c_str());
        }
    }
}
#if 0
class Cell
{
public:
    Cell(int x, int y, bool isDead);
    ~Cell();
    // 次の世代へ
    void Update();
    // 描画
    void Draw();
    // 死亡か生存か判定し、設定する
    void DeadOrAlive(int deadCellCount, int aliveCellCount);
    // 死亡しているかを所得
    bool GetIsDead();
    // 死亡していることを設定
    void SetIsDead(bool isDead);
    // 座標所得
    Vector2 GetPosition();
private:
    // 死亡しているか
    bool _IsDead;
    // 次の世代に死亡しているか
    bool _IsNextDead;
    // 座標
    Vector2 _Position;
};

Cell::Cell(int x, int y, bool isDead)
{
    _Position.x = x;
    _Position.y = y;
    _IsDead = isDead;
}

Cell::~Cell()
{
}

// 次の世代へ
void Cell::Update()
{
    SetIsDead(_IsNextDead);
}

// 描画
void Cell::Draw()
{
    if( _IsDead )
    {
        // 死亡
        Console::Display::write("×");
    }
    else
    {
        // 生存
        Console::Display::write("○");
    }
}

// 死亡か生存か判定し、設定する
void Cell::DeadOrAlive(int deadCellCount, int aliveCellCount)
{
    bool isDead = GetIsDead();
    // 誕生（死亡セルに隣接する生存セルが3つなら生存）
    if(_IsDead)
    {
        if(aliveCellCount == 3)
        {
            isDead = false;
        }
    }
    else if(!_IsDead)
    {
        // 生存（生存セルに隣接する生存セルが2つか3つなら生存）
        if(aliveCellCount == 2 || aliveCellCount == 3)
        {
            isDead = false;
        }
        // 過疎（生存セルに隣接する生存セルが1つ以下なら死亡）
        if(aliveCellCount <= 1)
        {
            isDead = true;
        }
        // 過密（生存セルに隣接する生存セル画4つ以上なら死亡）
        if(aliveCellCount >= 4)
        {
            isDead = true;
        }
    }
    _IsNextDead = isDead;
}

// 死亡しているかを所得
bool Cell::GetIsDead()
{
    return _IsDead;
}

// 生存か死亡かを設定
void Cell::SetIsDead(bool isDead)
{
    _IsDead = isDead;
}

Vector2 Cell::GetPosition()
{
    return _Position;
}

class Board
{
public:
    Board(int width, int height);
    ~Board();
    // セルが死亡しているかどうかを判定する
    void CellDeadOrAlive();
    // セルをランダムに死亡か生存を設定する
    void SetCellRandamIsAlive();
    // 描画
    void Draw();
private:
    // 座標から、隣接セルを返す
    void GetAroundCellBox(std::vector<Cell>* aroundcellBox, Vector2 cellPosition);
private:
    std::vector<Cell> _CellContainer;
    int _Width;
    int _Height;
};

Board::Board(int width, int height)
{
    for( int y = 0; y< height; ++y )
    {
        for( int x = 0; x < width; ++x )
        {
            _CellContainer.push_back( Cell(x, y, false) );
        }
    }
}

Board::~Board()
{
    _CellContainer.clear();
}

// セルが死亡しているかどうかを判定する
void Board::CellDeadOrAlive()
{
    std::vector<Cell>::iterator findIterator;
    for(findIterator = _CellContainer.begin(); findIterator != _CellContainer.end(); ++findIterator)
    {
        // 自分の座標を所得
        Vector2 myPosition = (*findIterator).GetPosition();
        // 周りのセルを所得
        std::vector<Cell> judgeBox;
        GetAroundCellBox(&judgeBox, myPosition);
        // 隣接している死亡セルと生存セルを数える
        int deadCellCount = 0;
        int aliveCellCount = 0;
        std::vector<Cell>::iterator getIterator;
        for(getIterator = judgeBox.begin(); getIterator != judgeBox.end(); ++getIterator)
        {
            if((*getIterator).GetIsDead())
            {
                ++deadCellCount;
            }
            else
            {
                ++aliveCellCount;
            }
        }
        // 生存か死亡か判定する
        (*findIterator).DeadOrAlive(deadCellCount,aliveCellCount);
    }
    // 判定を適応する
    for(findIterator = _CellContainer.begin(); findIterator != _CellContainer.end(); ++findIterator)
    {
        (*findIterator).Update();
    }
}

// セルをランダムに死亡か生存を設定する
void Board::SetCellRandamIsAlive()
{
    int maxCellCount = _CellContainer.size();
    std::vector<Cell>::iterator iterator;
    for(iterator = _CellContainer.begin(); iterator != _CellContainer.end(); ++iterator)
    {
        int random = rand() % 2;
        if(random == 0)
        {
            (*iterator).SetIsDead(true);
        }
        else
        {
            (*iterator).SetIsDead(false);
        }
    }
}

// 描画
void Board::Draw()
{
    std::vector<Cell>::iterator iterator;
    for(iterator = _CellContainer.begin(); iterator != _CellContainer.end(); ++iterator)
    {
        if((*iterator).GetPosition().x == 0)
        {
            Console::Display::writeLine("");
        }
        (*iterator).Draw();
    }
}

// 座標から、隣接セルを返す
void Board::GetAroundCellBox(std::vector<Cell>* aroundcellBox, Vector2 cellPosition)
{
    const static Vector2 aroundCellPositionBox[] =
    {
        Vector2(-1, -1), Vector2(0, -1), Vector2(1, -1),
        Vector2(-1,  0),                 Vector2(1,  0),
        Vector2(-1,  1), Vector2(0,  1), Vector2(1,  1),
    };
    std::vector<Cell>::iterator findIterator;
    for(findIterator = _CellContainer.begin(); findIterator != _CellContainer.end(); ++findIterator)
    {
        Vector2 thatPosition = (*findIterator).GetPosition();
        for(int i = 0; i < 8; ++i)
        {
            Vector2 judgePosition = cellPosition + aroundCellPositionBox[i];
            if(judgePosition == thatPosition)
            {
                aroundcellBox->push_back((*findIterator));
            }
        }
    }
}

class LifeGameApplication
{
public:
    LifeGameApplication();
    LifeGameApplication(Vector2 boardSize, int endturn = 10);
public:
    // ゲーム開始
    void run();
private:
    // 開始
    void Start();
    // 更新
    void Update();
    // 描画
    void Draw();
    // 終了
    void Finish();
    // ゲーム終了
    bool IsEnd();
private:
    Board _Board;
    int _EndTurn;
    int _TurnCount;
};

LifeGameApplication::LifeGameApplication():
    _Board(10,10),
    _EndTurn(10),
    _TurnCount(0)
{
}

LifeGameApplication::LifeGameApplication(Vector2 boardSize, int endturn):
    _Board(boardSize.x,boardSize.y),
    _EndTurn(endturn),
    _TurnCount(0)
{
}

// ゲーム開始
void LifeGameApplication::run()
{
    Start();
    while(!IsEnd())
    {
        Update();
        Draw();
    }
    Finish();
}

// 開始
void LifeGameApplication::Start()
{
    _Board.SetCellRandamIsAlive();
    Draw();
}

// 更新
void LifeGameApplication::Update()
{
    ++_TurnCount;
    _Board.CellDeadOrAlive();
}

// 描画
void LifeGameApplication::Draw()
{
    _Board.Draw();
    Console::Display::writeLine("");
    Console::Display::write(std::to_string(_TurnCount).c_str());
    Console::Display::writeLine("ターン目");
}

// 終了
void LifeGameApplication::Finish()
{

}

// ゲーム終了
bool LifeGameApplication::IsEnd()
{
    return _TurnCount >= _EndTurn;
}
#endif
int main()
{
    srand((unsigned int)time(NULL));

    //LifeGameApplication gameApplication = LifeGameApplication(Vector2(15,15), 20);
    //gameApplication.run();
    CellManager * cellManager = new CellManager();

    cellManager->createSimulateSize(50, 30);
    cellManager->setRandomAliveCells();
    for(;;){
        cellManager->update();
        cellManager->draw();
        //_sleep(200 * 1000);
    }
    return 0;
}
