//Issue during interview: Using 'temp.size() == numbers.size()' instead of 'numbers.empty()' after using 'numbers.erase()'
//Space: O(n!), however O(n) space is possible if we only want to print the results instead of keeping a permutation set.
//Time: O(n!)

#include <iostream>
#include <vector>
using namespace std;

void permute(vector<int> numbers, vector<vector<int>> &perm_set, vector<int> temp)
{
    if (numbers.empty())
    {
        //Alternatively, we can use cout if we only want to print each permutation for O(n) space instead of keeping a permutation set.
        perm_set.push_back(temp);
    }
    else
    {
        for (int i = 0; i < numbers.size(); i++)
        {
            int tmp = numbers[i];
            temp.push_back(numbers[i]);
            numbers.erase(numbers.begin() + i);

            permute(numbers, perm_set, temp);

            numbers.insert(numbers.begin() + i, tmp);
            temp.pop_back();
        }
    }
}

int main()
{
    vector<int> numbers = {1, 2, 3, 4};
    vector<vector<int>> perm_set;

    permute(numbers, perm_set, vector<int>());

    for (int i = 0; i < perm_set.size(); i++)
    {
        for (int j = 0; j < perm_set[i].size(); j++)
            cout << perm_set[i][j] << " ";
        cout << endl;
    }

    return 0;
}