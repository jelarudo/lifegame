#include "Cell.h"

void Cell::step()
{
    State next = _state;
    if(isBirth() == true || isStay() == true)
    {
        next = Cell::Alive;
    }
    else if(isEmpty() == true || isFull() == true)
    {
        next = Cell::Death;
    }
    setState(next);
    _roundAliveCellCount = 0;
}

void Cell::sendNotify()
{
    _notifyInfo["cell"] = (void*)this;
    notify(_notifyInfo);
}

void Cell::setState(State state)
{
    _state = state;
}

void Cell::update(std::map<std::string,void*>& info)
{
    const Cell * cell = (const Cell*)(info["cell"]);
    if(cell->isAlive() == true)
    {
        _roundAliveCellCount++;
    }
}

bool Cell::isAlive() const
{
    return _state == Cell::Alive;
}

bool Cell::isBirth() const
{
    if(isAlive() == false && getAliveRoundCellCount() == 3)
    {
        return true;
    }
    return false;
}

bool Cell::isStay() const
{
    if(isAlive() == true && (getAliveRoundCellCount() == 2 || getAliveRoundCellCount() == 3))
    {
        return true;
    }
    return false;
}

bool Cell::isEmpty() const
{
    if(isAlive() == true && getAliveRoundCellCount() <= 1)
    {
        return true;
    }
    return false;
}

bool Cell::isFull() const
{
    if(isAlive() == true && getAliveRoundCellCount() >= 4)
    {
        return true;
    }
    return false;
}

int Cell::getAliveRoundCellCount() const
{
    return _roundAliveCellCount;
}
