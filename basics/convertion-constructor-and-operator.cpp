//g++  5.4.0

#include <iostream>
#include <string>

using namespace std;

class Int
{
    int i;
    
    public:
    
    Int(int x = 0): i(x){
    std::cout<<"convertion constructor" << endl;
    }
    
    operator string ()
    {
        std::cout<< "convertion operator"<<endl;
        return to_string(i);
    }
    
    int get()
    {
        return i;
    }
};

int main()
{
    Int i(3);
    std::cout<< "i = " << i.get() <<endl;
    string str1 = i;
    std::cout<< "str1 = " << str1 <<endl;
    i = 20;
    std::cout<< "i = " << i.get() <<endl;
    string str2 = static_cast<string>(i);
    std::cout<< "str2 = " << str2 <<endl;
    i = static_cast<Int>(30);
    std::cout<< "i = " << i.get() <<endl;
    
    return 0;
}