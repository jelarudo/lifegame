#include <stdlib.h>

#include "CellManager.h"
#include "Cell.h"
#include "Console.h"

CellManager::CellManager()
{
}

void CellManager::createSimulateSize(int row, int col)
{
    for(int i = 0; i < col; ++i)
    {
        std::vector<Cell*> * rowCells = new std::vector<Cell*>();
        for(int j = 0; j < row; ++j)
        {
            rowCells->push_back(new Cell());
        }
        _cellMatrix.push_back(rowCells);
    }
    _simulate.x = row;
    _simulate.y = col;

    for(int i = 0; i < _cellMatrix.size(); ++i)
    {
        for(int j = 0; j < _cellMatrix[i]->size(); ++j)
        {
            std::vector<Vector2> indexVector;
            _getRoundCellIndex(indexVector, j, i);
            for(unsigned int k = 0; k < indexVector.size(); ++k)
            {
                _cellMatrix[i]->at(j)->addObserver(_getCell(indexVector[k].x, indexVector[k].y));
            }
        }
    }

}

void CellManager::setRandomAliveCells()
{
    for(int i = 0; i < _cellMatrix.size(); ++i)
    {
        for(int j = 0; j < _cellMatrix[i]->size(); ++j)
        {
            _cellMatrix[i]->at(j)->setState(rand()%2 == 0 ? Cell::Alive : Cell::Death);
        }
    }
}

bool CellManager::isAlive(int row, int col)
{
    return _getCell(row, col)->isAlive();
}

Cell* CellManager::_getCell(int row, int col)
{
    return _cellMatrix[col]->at(row);
}

void CellManager::_getRoundCellIndex(std::vector<Vector2> & out, int row, int col)
{
    out.clear();
    const static Vector2 roundIndexer[] =
    {
        Vector2(-1, -1), Vector2(0, -1), Vector2(1, -1),
        Vector2(-1,  0),                 Vector2(1,  0),
        Vector2(-1,  1), Vector2(0,  1), Vector2(1,  1),
    };

    for(int i = 0; i < 8; ++i)
    {
        Vector2 index;
        index.x = _calcCircleIndex(row + roundIndexer[i].x, 0, _simulate.x);
        index.x = _calcCircleIndex(row + roundIndexer[i].x, 0, _simulate.x);
        out.push_back(index);
    }
}

int CellManager::_calcCircleIndex(int target, int min, int max)
{
    if(target < min)
    {
        target = max - 1;
    }
    else if(target > max - 1)
    {
        target = min;
    }
    return target;
}
/*
int CellManager::getAliveCellCount(Vector2 * checkTargetIndex, int size)
{

}
*/
void CellManager::update()
{
    for(int i = 0; i < _cellMatrix.size(); ++i)
    {
        for(int j = 0; j < _cellMatrix[i]->size(); ++j)
        {
            _cellMatrix[i]->at(j)->sendNotify();
        }
    }

    for(int i = 0; i < _cellMatrix.size(); ++i)
    {
        for(int j = 0; j < _cellMatrix[i]->size(); ++j)
        {
            _cellMatrix[i]->at(j)->step();
        }
    }
}

void CellManager::draw()
{
    Console::Display::write("\033[2J");
    for(int i = 0; i < _cellMatrix.size(); ++i)
    {
        for(int j = 0; j < _cellMatrix[i]->size(); ++j)
        {
            Console::Display::setPosition(i, j);
            Console::Display::write(_cellMatrix[i]->at(j)->isAlive() == true ? "@" : " ");
        }
    }

    fflush(stdout);
}


