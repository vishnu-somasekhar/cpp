#include <iostream>
#include <vector>
using namespace std;


void InsertionSort(vector<int> &aItemList)
{
    int iKey = 1;

    for(int iPos = iKey; iPos < aItemList.size(); iPos++)
    {
        while(iPos > 0 && aItemList[iPos] < aItemList[iPos - 1])
        {
            
            int iTmp            = aItemList[iPos];
            aItemList[iPos]     = aItemList[iPos - 1];
            aItemList[iPos - 1] = iTmp;
            iPos--;
        }
    }
    
}


int main()
{
    vector<int> aItems = {4, 12, 43, 12, 5, 1, 2, 122, 115};

    InsertionSort(aItems);

    for(int x : aItems)
        cout<< x << " ";
    return 0;
}