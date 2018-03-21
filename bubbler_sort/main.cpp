#include <iostream>
#include <vector>

using namespace std;

void swap(int &lrs, int &rhs)
{
    int sum = lrs + rhs;
    lrs = sum - lrs;
    rhs = sum - rhs;
}

void bubbler(vector<int> &input)
{
    int size = input.size();
    for (int i=0; i<size; i++)
    {
        bool isSwap = false;
        for (int j=0; j<size-1-i; j++)
        {
            if (input[j] > input[j+1])
            {
                swap(input[j], input[j+1]);
                isSwap = true;
            }
        }
        if (!isSwap) break;
    }
}

int main(int argc, char **argv)
{
    vector<int> a = {12,31,51,526,1,6,1,231,31,5,1,65,151,94,2,13,21,56,16,16,1};
    bubbler(a);
    for (auto i:a)
        cout << i << " ";
    return 0;
}
