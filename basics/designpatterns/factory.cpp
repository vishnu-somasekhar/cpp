#include <iostream>

using namespace std;

class Button{
    public:
    virtual void print() = 0;
};

class WinButton : public Button{
    public:
    void print() { cout<< "Windows button\n"; }
};

class MacButton : public Button{
    public:
    void print() { cout<< "Mac button\n"; }
};

class GuiFactory{
    public:
    virtual Button* createButton(int iType){
        switch(iType){
            case 1:
            return (new WinButton);

            case 2:
            return (new MacButton);
        }
        return nullptr;
    }
};

int main()
{
    Button* btn;
    GuiFactory* fac = new GuiFactory;
    
    btn = fac->createButton(1);
    btn->print();

    btn = fac->createButton(2);
    btn->print();

    return 0;
}