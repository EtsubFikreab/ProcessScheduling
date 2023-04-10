#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
bool sortByArrivalTime(const vector<int> &v1, const vector<int> &v2)
{
    return v1[1] < v2[1];
}
bool sortByProcessNumber(const vector<int> &v1, const vector<int> &v2)
{
    return v1[0] < v2[0];
}
bool sortByRemainingTime(const vector<int> &v1, const vector<int> &v2)
{
    // used on SJF algorithm
    return v1[1] < v2[1];
}
// processes[process[0:ProcessNumber, 1:ArrivalTime, 2:BurstTime, 3:WaitTime, 4:CompletionTime, 5:TurnAroundTime, 6:ResponseTime]]

///////////////////////////////////////////////////////////////////////////////////////////////////
// for testing
void display2dVector(vector<vector<int>> list)
{
    cout << "Process\tArrival Time\tBurst Time\n";
    for (auto row : list)
    {
        for (auto column : row)
            cout << column << "\t";
        cout << endl;
    }
}
void displayVector(vector<int> list)
{
    cout << "\nVector\n";
    for (auto a : list)
    {
        cout << a << " ";
    }
    cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int>> firstComeFirstServe(vector<vector<int>> processes)
{
    vector<vector<int>> result;
    result = processes;

    // Complexity O(nLogn)
    // main bottleneck is sorting the array, but its necessary
    sort(result.begin(), result.end(), sortByArrivalTime);
    int completionTime = 0;
    int turnAroundTime, waitingTime, responseTime;
    for (int i = 0; i < processes.size(); i++)
    {
        // responseTime = previousCompletionTime - arrivalTimeOfCurrentProcess
        responseTime = completionTime - result[i][1];
        // completionTime = previousCompletionTime + burstTime
        completionTime += result[i][2];
        // turnAroundTime = CompletionTime - arrivalTime
        turnAroundTime = completionTime - result[i][1];
        // waitingTime = turnAroundTime - burstTime
        waitingTime = turnAroundTime - result[i][2];

        result[i].push_back(waitingTime);
        result[i].push_back(completionTime);
        result[i].push_back(turnAroundTime);
        result[i].push_back(responseTime);
    }
    sort(result.begin(), result.end(), sortByProcessNumber);

    return result;
}

vector<vector<int>> shortestJobFirst(vector<vector<int>> processes, bool preemptive)
{
    vector<vector<int>> result;
    result = processes;
    sort(result.begin(), result.end(), sortByArrivalTime);
    int completionTime = 0;
    int turnAroundTime, waitingTime, responseTime;
    int clock = 0, visited = 0;
    if (preemptive)
    {
    }
    else
    {
        list<vector<int>> remainingProcess;
        // remainingProcess[Process[ProcessNumber, RemainingBurstTime, ResponseTime]], acts like a stack
        remainingProcess.push_front(vector<int>{result[0][0], result[0][2]});
        visited = 1;
        vector<int> currentProcess;
        while (!remainingProcess.empty() || visited < result.size())
        {
            cout<<"start\n";
            // check processes with similar arrival time
            for (int i = visited; i < result.size() && result[i][1] < clock; i++)
            {
                remainingProcess.push_back(vector<int>{result[i][0], result[i][2]});
                visited++;
                cout<<i<<" ";
            }
            if (!remainingProcess.empty())
                currentProcess = remainingProcess.front();
            // if this is the first time the process runs
            // if (currentProcess.size() < 3)
            //     responseTime = clock - processes[currentProcess[0] - 1][1]; // clock - arrivalTime
            remainingProcess.pop_front();
            if (remainingProcess.empty())

            cout << visited<<" "<<result.size() << endl;
            // displayVector(currentProcess);
        }
    }
    sort(result.begin(), result.end(), sortByProcessNumber);

    return result;
}
vector<vector<int>> priorityScheduling(vector<vector<int>> processes, bool preemptive)
{
    vector<vector<int>> result;
    if (preemptive)
    {
    }
    else
    {
    }
    return result;
}
vector<vector<int>> roundRobin(vector<vector<int>> processes)
{
    vector<vector<int>> result;

    return result;
}
