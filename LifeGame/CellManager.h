#pragma once

#include <stdio.h>
#include <vector>

#include "Vector2.h"

class Cell;

class CellManager
{
public:
    CellManager();

private:
    Vector2 _simulate;
    std::vector<std::vector<Cell*> * > _cellMatrix;

public:
    void createSimulateSize(int row, int col);

    void setRandomAliveCells();

public:
    bool isAlive(int row, int col);

private:
    Cell* _getCell(int row, int col);
    void _getRoundCellIndex(std::vector<Vector2> & out, int row, int col);
    int _calcCircleIndex(int target, int min, int max);
    int getAliveCellCount(Vector2 * checkTargetIndex, int size);
public:
    void update();
    void draw();
};

