#include <iostream>
#include <vector>


using namespace std;

void merge(vector<int> aItemList, int iLeft, int iMiddle, int iRight)
{

}

void mergesort(vector<int> &aItemList, int iLeft, int iRight)
{
    if(iLeft < iRight)
    {
        int iMiddle = iLeft + (iRight - iLeft)/2;

        mergesort(aItemList, iLeft, iMiddle);
        mergesort(aItemList, iMiddle + 1, iRight);

        merge(aItemList, iLeft, iMiddle, iRight);
    }
}

int main()
{
    return 0;
}