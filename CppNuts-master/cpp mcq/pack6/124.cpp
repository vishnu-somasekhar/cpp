#include <iostream>
using namespace std;

int main()
{
    int x = 1 , y = 1;
    cout << ( ++x  || ++y ) << endl;   // outputs 1;
    cout << x << " " << y;             // x = 2 , y = 1;
    return 0;
}

// A. 1
//	  2 1
// B. Compile Time Error
// C. Run Time Error
// D. Garbage Value
// E. 2
//    2 1
// F. 1
//    2 2