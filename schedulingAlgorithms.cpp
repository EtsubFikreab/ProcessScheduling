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
    // sort process by shortest burst time
    return v1[2] < v2[2];
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
    sort(processes.begin(), processes.end(), sortByArrivalTime);

    // processStack[Process[ProcessNumber, RemainingBurstTime, ResponseTime]]
    list<vector<int>> processStack;
    vector<int> currentProcess;

    int completionTime = 0;
    int turnAroundTime, waitingTime, responseTime;
    int clock = 0, visited = 0;

    if (preemptive)
    {
        result = processes;
        processStack.push_front(processes[0]);
        visited = 1;
        while (!processStack.empty() || visited < processes.size())
        {
            // check if processes arrived
            cout<<"h";
            for (int i = visited; i < processes.size() && processes[i][1] <= clock; i++)
            {
                processStack.push_back(processes[i]);
                visited++;
            }
            if (processStack.empty()){
                clock++;
                continue;
            }
            processStack.sort(sortByRemainingTime);
            // cout<<"Process: "<<currentProcess[0]<<endl;
            currentProcess = processStack.front();

            // completion time= if burst ==0
            // response time = if burst initial == burst remaining
            // tat and wt if complete

            // responseTime = previousCompletionTime - arrivalTimeOfCurrentProcess
            responseTime = clock - currentProcess[1]; // clock - arrivalTime
            // completionTime = previousCompletionTime + burstTime
            completionTime = clock + currentProcess[2];
            // turnAroundTime = CompletionTime - arrivalTime
            turnAroundTime = completionTime - currentProcess[1];
            // waitingTime = turnAroundTime - burstTime
            waitingTime = turnAroundTime - currentProcess[2];

            currentProcess.push_back(waitingTime);
            currentProcess.push_back(completionTime);
            currentProcess.push_back(turnAroundTime);
            currentProcess.push_back(responseTime);

            clock += currentProcess[2];
            processStack.pop_front();
            result.push_back(currentProcess);
            // cout <<"Clock: "<< clock << endl;
        }
    }
    else
    {
        processStack.push_front(processes[0]);
        visited = 1;
        while (!processStack.empty() || visited < processes.size())
        {
            // check whether processes have arrived during execution of previous process
            for (int i = visited; i < processes.size() && processes[i][1] <= clock; i++)
            {
                processStack.push_back(processes[i]);
                visited++;
            }
            processStack.sort(sortByRemainingTime);
            if (processStack.empty()){
                clock++;
                continue;
            }
            currentProcess = processStack.front();
            // responseTime = previousCompletionTime - arrivalTimeOfCurrentProcess
            responseTime = clock - currentProcess[1]; // clock - arrivalTime
            // completionTime = previousCompletionTime + burstTime
            completionTime = clock + currentProcess[2];
            // turnAroundTime = CompletionTime - arrivalTime
            turnAroundTime = completionTime - currentProcess[1];
            // waitingTime = turnAroundTime - burstTime
            waitingTime = turnAroundTime - currentProcess[2];
            
            currentProcess.push_back(waitingTime);
            currentProcess.push_back(completionTime);
            currentProcess.push_back(turnAroundTime);
            currentProcess.push_back(responseTime);

            clock += currentProcess[2];
            processStack.pop_front();
            result.push_back(currentProcess);
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
