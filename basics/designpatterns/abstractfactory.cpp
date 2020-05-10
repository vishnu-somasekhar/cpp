#include <iostream>

using namespace std;

class Button
{
    public:
    virtual void paint() = 0;
};

class WinButton : public Button
{
    public:
    void paint() { cout<< "Windows Button\n"; }
};

class MacButton : public Button{
    public:
    void paint() { cout<< "Mac Button \n"; }
};

class ScrollBar
{
    public:
    virtual void paint() = 0;
};

class WinScrollBar : public ScrollBar{
    public:
    void paint() { cout<< "Windows ScrollBar\n"; }
};

class MacScrollBar : public ScrollBar{
    public:
    void paint() { cout<< "Mac ScrollBar\n"; }
};

class GuiFactory {
    public:

    virtual Button* CreateButton() = 0;
    virtual ScrollBar* CreateScrollbar() = 0;
};

class WinFactory : public GuiFactory{
    public:
    Button* CreateButton() { return new WinButton;  }

    ScrollBar* CreateScrollbar() { return new WinScrollBar; }
};

class MacFactory : public GuiFactory{
    public:
    Button* CreateButton() { return new MacButton;  }

    ScrollBar* CreateScrollbar() { return new MacScrollBar; }
};


int main()
{
    GuiFactory* guiFactory;
    Button* button;
    ScrollBar* scrollbar;

    guiFactory = new MacFactory;
    button = guiFactory->CreateButton();
    button->paint();
    scrollbar = guiFactory->CreateScrollbar();
    scrollbar->paint();

    guiFactory = new WinFactory;
    button = guiFactory->CreateButton();
    button->paint();
    scrollbar = guiFactory->CreateScrollbar();
    scrollbar->paint();

    return 0;
}