#include <iostream>
#include <vector>
#include <random>

using namespace std;

bool isSorted(vector<int> &input)
{
    if (input.size() < 2)
        return true;
    for (size_t i=1; i<input.size(); i++) {
        if (input[i] < input[i-1])
            return false;
    }
    return true;
}

void qSort(vector<int> &input)
{
    if (input.size() < 2)
        return;
    for (size_t i=1; i<input.size(); i++) {
        if (input[i] < input[i-1]) {
            int insertIdx = i - 1;
            int insertVal = input[i];
            while (insertIdx > -1 && insertVal < input[insertIdx]) {
                input[insertIdx + 1] = input[insertIdx];
                insertIdx--;
            }
            input[insertIdx+1] = insertVal;
        }
    }
}

int main(int argc, char *argv[])
{
    vector<int> t1;
    vector<int> t2(10, 0);
    vector<int> t3(10, 20);
    vector<int> t4;
    for (int i=0; i<100; i++)
        t4.push_back(rand());
    qSort(t1);
    qSort(t2);
    qSort(t3);
    qSort(t4);
    if (isSorted(t1) && isSorted(t2) && isSorted(t3) && isSorted(t4))
        cout << "tests successed" <<endl;
    else
        cout << "tests failed" << endl;
    return 0;
}
