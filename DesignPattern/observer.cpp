#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Observer;
class Car {

    private:

        int m_position;
        vector<Observer*> m_observer;

        void Update();
    public:

        Car(): m_position(0) {}

        int getPositoin() { return m_position; }

        void SetPosition(int pos) { 
            m_position = pos;
            Update();
        }

        void Attach(Observer* obs)
        {
            if(obs != nullptr)
                m_observer.push_back(obs);
        }

        void Detach(Observer* obs)
        {
            if(obs != nullptr)
                m_observer.erase(remove(m_observer.begin(), m_observer.end(), obs), m_observer.end());
        }

};



class Observer {
    private:
        Car* m_car;

    public:
        Observer(Car* car): m_car(car) {
            m_car->Attach(this);
        }

        virtual void notify() = 0;

    protected:
        Car* GetCar() { return m_car; }
};

void Car::Update()
{
    for (Observer* obs : m_observer)
    {
        if(obs != nullptr)
            obs->notify();
    }
}

class LeftObs : public Observer
{
    public:
        LeftObs(Car* car):Observer(car) {}

        void notify()
        {
            if(GetCar()->getPositoin() == -1)
                cout<< "Left side \n";
        }
};

class RightObs : public Observer
{
    public:
        RightObs(Car* car):Observer(car) {}

        void notify()
        {
            if(GetCar()->getPositoin() == 1)
                cout<< "Right side \n";
        }
};

class CenterObs : public Observer
{
    public:
        CenterObs(Car* car):Observer(car) {}

        void notify()
        {
            if(GetCar()->getPositoin() == 0)
                cout<< "Center side \n";
        }
};

int main()
{
    Car* car = new Car();
    LeftObs* LObs = new LeftObs(car);
    RightObs* RObs = new RightObs(car);
    CenterObs* CObs = new CenterObs(car);
    char keyPress;
    bool bBreak = false;
    while(!bBreak)
    {
        cin>>keyPress;

        cout<<keyPress<< " ";
        
        switch(keyPress)
        {
            case 108:
            {
                car->SetPosition(-1);
            }
            break;
            case 99:
            {
                car->SetPosition(0);
            }
            break;
            case 114:
            {
                car->SetPosition(1);
            }
            break;
            case 98:
            {
                bBreak = true;
            }
            break;
            default:
            {
                cout<<"Wrong input!" << endl;
            }
            break;

        }
    }

    delete car;
    delete LObs;
    delete RObs;
    delete CObs;

    return 0;
}