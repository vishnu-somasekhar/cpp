#include <bits/stdc++.h>

using namespace std;

#define COUNT 26

string isValid(string s) {

  int arr[COUNT] = {0};

    for(size_t i = 0; i < s.length(); i++)
        arr[s[i] - 'a']++;

    int i = 0, freq1 = 0, count_freq1 = 0, freq2 = 0, count_freq2 = 0;

    for(i = 0; i < COUNT; i++)
    {
        if(arr[i] != 0){
            if(freq1 == 0)
            {
                freq1 = arr[i];
                count_freq1 = 1;
                 cout<<arr[i]<<count_freq1;
            }
            else if(freq2 == 0)
            {
                if(arr[i] == freq1)
                {    
                    count_freq1++;
                }
                else
                {
                    freq2 = arr[i];
                    count_freq2++;
                }
                cout<<arr[i]<<count_freq2;
            }
            else
            {
                cout<<arr[i];
                return string("NO");
            }
            
        }

        if(count_freq1 > 1 && count_freq2 > 1)
            return string("NO");
    }

    return string("YES");

    
}
int main()
{

    string s("abcdefghhgfedecba");

    cout<<isValid(s);


    return 0;
}
