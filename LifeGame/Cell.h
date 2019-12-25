#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <list>
#include <map>

class IObserver
{
public:
    virtual void update(std::map<std::string, void*>& info) = 0;
};

class Subject
{
public:
    Subject(){}
    virtual ~Subject(){}
protected:
    std::list<IObserver*> _observerList;

public:
    virtual void addObserver(IObserver* observer)
    {
        _observerList.push_back(observer);
    }

    virtual void remoteObserver(IObserver* observer)
    {
        for(std::list<IObserver*>::iterator i = _observerList.begin(); i != _observerList.end(); i++)
        {
            if((*i) == observer)
            {
                _observerList.erase(i);
            }
        }
    }

public:
    virtual void notify(std::map<std::string, void*> info)
    {
        for(std::list<IObserver*>::iterator i = _observerList.begin(); i != _observerList.end(); i++)
        {
            (*i)->update(info);
        }
    }
};

class Cell : public Subject, public IObserver
{
public:
    enum State
    {
        None = -1,
        Death = 0,
        Alive = 1,
    };
public:
    Cell()
    {
    }
public:
    void step();
    void sendNotify();
public:
    void setState(State state);
    virtual void update(std::map<std::string,void*>& info);
private:
    int getAliveRoundCellCount() const;
private:
    State _state;
    int _roundAliveCellCount;

    std::map<std::string, void*> _notifyInfo;

public:
    bool isAlive() const;
    bool isBirth() const;
    bool isStay() const;
    bool isEmpty() const;
    bool isFull() const;

};
