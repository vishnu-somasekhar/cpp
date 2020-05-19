#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'dynamicArray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
 */

vector<int> dynamicArray(int n, vector<vector<int>> queries) {
    vector<int> result;
    int lastAns = 0;
    int pos = 0;
    vector<int> seq[n];
    for(auto x : queries)
    {
        cout<<x[0]<<"->"<<x[1]<<"->"<<x[2];
        pos = (x[1] ^ lastAns)  n;
        if(x[0] == 1)
        {
            seq[pos].push_back(x[2]); 
        }
        else if(x[0] == 2)
        {
            int index = x[2] % static_cast<int>(seq[pos].size());
            lastAns = seq[pos][index];
            result.push_back(lastAns);
        }
    }

    return result;
}

int main()
{
    ifstream file("input10.txt");

    
    if(file.is_open())
    {
        cout<<"test";
        string first_multiple_input_temp;
        getline(file, first_multiple_input_temp);
        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int q = stoi(first_multiple_input[1]);

        vector<vector<int>> queries(q);

        for (int i = 0; i < q; i++) {
            queries[i].resize(3);

            string queries_row_temp_temp;
            getline(file, queries_row_temp_temp);

            vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

            for (int j = 0; j < 3; j++) {
                int queries_row_item = stoi(queries_row_temp[j]);

                queries[i][j] = queries_row_item;
            }
        }

        vector<int> result = dynamicArray(n, queries);

        for (int i = 0; i < result.size(); i++) {
            std::cout << result[i];

            if (i != result.size() - 1) {
                std::cout << "\n";
            }
        }

        file.close();
    }
    
    

    

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
