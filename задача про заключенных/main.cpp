#include <QDebug>
#include <QCoreApplication>

//Класс лампочка
class Bulb
{
public:
    Bulb();
    void turnOn();
    void turnOff();
    bool OnOffBulb();
private:
    bool bulb;

};
//методы
Bulb::Bulb()
{
    bulb=false; // лампочка выключена
}
void Bulb::turnOn()
{
    bulb=true; // лампочка включена
}
void Bulb::turnOff()
{
    bulb=false; // лампочка выключена
}

bool Bulb::OnOffBulb() // лампочка включена или выключена
{
    return bulb;
}

//Класс стратегии
class IStrategy
{
public:
    virtual bool doBehavior (Bulb* light)=0;
};

class BehaviorRest: public IStrategy // класс заключенных, кроме счетчика
{
    bool doBehavior (Bulb* light)
    {
        if(light->OnOffBulb() == false && first == true)
        {
            light->turnOn();
            first = false;
        }
        return false;
    }

private:
    bool first = true;
};

class BehaviorCounter: public IStrategy // класс счетчика
{
    bool doBehavior (Bulb* light)
    {
        if(light->OnOffBulb() == true)
        {
            light->turnOff();
            count++;
            if(count == 3)
                return true;
            else
                return false;
        }
        else return false;
    }
private:
    int count=0;
};

//Класс заключенного
class Prisoner
{
public:
    Prisoner() {}
    virtual bool enterRoom(Bulb* light);
    void setStrategyInRoom (IStrategy* IS);

private:
    IStrategy* pStrategy;

};

bool Prisoner::enterRoom(Bulb* light)
{
    return pStrategy->doBehavior(light);
}
void Prisoner::setStrategyInRoom (IStrategy* IS)
{
    pStrategy = IS;
}


//Класс надзирателя
class Warden
{
public:
    Warden(){pBulb = new Bulb;}
    void Experiment ();
    void counter(); // выбирают счетчика

private:
    Bulb* pBulb;
    Prisoner massivPrisoner [4];
};
void Warden::Experiment()
{
     bool liberty = false;
     srand(time(0));
     while(liberty==false)
     {
         int start = 0;
         int end = 3;
         int i = rand() % (end - start + 1) + start;
         qDebug() << i;
         liberty = massivPrisoner[i].enterRoom(pBulb);
     }
     qDebug()<< "YOU WON";

}
void Warden::counter()
{
    massivPrisoner[0].setStrategyInRoom(new BehaviorRest);
    massivPrisoner[1].setStrategyInRoom(new BehaviorRest);
    massivPrisoner[2].setStrategyInRoom(new BehaviorRest);
    massivPrisoner[3].setStrategyInRoom(new BehaviorCounter);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Warden warden;
    warden.counter();
    warden.Experiment();

    return a.exec();
}
