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
    // vector<vector<int>> result = firstComeFirstServe(originalList);
    // vector<vector<int>> result = shortestJobFirst(originalList, false);
    //vector<vector<int>> result = shortestJobFirst(originalList, true);
    vector<vector<int>> result = roundRobin(originalList, 3);
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
    int pickList = 4;
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
    else if (pickList == 2)
    {
        // SJF non-preemptive
        // slide 27
        list.push_back(vector<int>{1, 0, 7});
        list.push_back(vector<int>{2, 2, 4});
        list.push_back(vector<int>{3, 4, 1});
        list.push_back(vector<int>{4, 5, 4});
    }
    else if (pickList == 3)
    {
        // SJF preemptive
        //  slide 33
        list.push_back(vector<int>{1, 2, 1});
        list.push_back(vector<int>{2, 1, 5});
        list.push_back(vector<int>{3, 4, 1});
        list.push_back(vector<int>{4, 0, 6});
        list.push_back(vector<int>{5, 2, 3});
    }
    else if (pickList == 4)
    {
        // RR
        //  slide 42
        // switched wait time to 4th element (for consistency)
        list.push_back(vector<int>{1, 0, 8});
        list.push_back(vector<int>{2, 5, 2});
        list.push_back(vector<int>{3, 1, 7});
        list.push_back(vector<int>{4, 6, 3});
        list.push_back(vector<int>{5, 8, 5});
    }
    return list;
}
//TODO: Test all if the first process arrives after 0 time eg 1,2... 