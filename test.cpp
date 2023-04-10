#include "schedulingAlgorithms.cpp"
using namespace std;
vector<vector<int>> testListGenerator();
void test();
void display(vector<vector<int>>);

//-----------------------------------
void test()
{
    vector<vector<int>> originalList = testListGenerator();

    // test fcfs
    //vector<vector<int>> result = firstComeFirstServe(originalList);
    vector<vector<int>> result = shortestJobFirst(originalList, false);
    display(result);
}
//-----------------------------------

void display(vector<vector<int>> list)
{
    cout << "Process\tArrival Time\tBurst Time\n";
    for (auto row : list)
    {
        for (auto column : row)
            cout << column << "\t";
        cout << endl;
    }
}
vector<vector<int>> testListGenerator()
{
    int pickList = 2;
    // change pickList to test different lists
    vector<vector<int>> list;
    if (pickList == 1)
    {
        // Chapter 3, slide 15
        // for testing first come first serve (FCFS)
        list.push_back(vector<int>{1, 0, 24});
        list.push_back(vector<int>{2, 5, 3});
        list.push_back(vector<int>{3, 10, 3});
        // list.push_back(vector<int>{4, 5, 4});
    }
    else if (pickList = 2)
    {
        // SJF
        // slide 27
        list.push_back(vector<int>{1, 0, 7});
        list.push_back(vector<int>{2, 2, 4});
        list.push_back(vector<int>{3, 4, 1});
        list.push_back(vector<int>{4, 5, 4});
    }
    return list;
}