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
    return v1[3] < v2[3];
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

    // processStack[Process[0: ProcessNumber, 1: ArrivalTime, 2: OriginalBurstTime, 3: RemainingBurstTime, 4: ResponseTime]](the last 2 elements are only for preemptive)
    list<vector<int>> processStack;

    vector<int> currentProcess;
    vector<int> previousProcess;
    vector<int> tempProcess;

    int completionTime = 0;
    int turnAroundTime, waitingTime, responseTime;
    int clock = 0, visited = 0;

    processStack.push_front(processes[0]);
    clock = processes[0][1];
    visited = 1;
    if (preemptive)
    {
        (processStack.front()).push_back(processStack.front()[2]);
        while (!processStack.empty() || visited < processes.size())
        {
            // check if processes arrived
            for (int i = visited; i < processes.size() && processes[i][1] <= clock; i++)
            {
                currentProcess = processes[i];
                currentProcess.push_back(currentProcess[2]);
                //  duplicate burst time, so it can be used to calculate remaining burst time
                processStack.push_back(currentProcess);
                visited++;
            }
            if (processStack.empty())
            {
                clock++;
                continue;
            }
            processStack.sort(sortByRemainingTime);
            currentProcess = processStack.front();

            // check whether a process with a higher processNumber had already started executing
            if (!previousProcess.empty() && previousProcess[3] == currentProcess[3] && previousProcess[0] != currentProcess[0])
            {
                while (previousProcess[0] != processStack.front()[0])
                {
                    tempProcess = processStack.front();
                    processStack.pop_front();
                    processStack.push_back(tempProcess);
                }
                currentProcess = processStack.front();
            }

            // completion time= if burst ==0
            // response time = if burst initial == burst remaining
            // tat and wt if complete
            if (currentProcess.size() < 5)
            {
                // set third variable as the response time
                // responseTime = clock - arrivalTimeOfCurrentProcess
                currentProcess.push_back(clock - currentProcess[1]);
            }
            if (currentProcess[3] == 0) // if remaining-burst-time == 0
            {
                // process has completed

                responseTime = currentProcess[4];
                // completionTime = previousCompletionTime + burstTime
                completionTime = clock;
                // turnAroundTime = CompletionTime - arrivalTime
                turnAroundTime = completionTime - currentProcess[1];
                // waitingTime = turnAroundTime - burstTime
                waitingTime = turnAroundTime - currentProcess[2];

                currentProcess[3] = waitingTime;
                currentProcess[4] = completionTime;
                currentProcess.push_back(turnAroundTime);
                currentProcess.push_back(responseTime);
                result.push_back(currentProcess);
                processStack.pop_front();
                previousProcess.clear();
            }
            else
            {

                --currentProcess[3];
                processStack.pop_front();
                processStack.push_back(currentProcess);
                previousProcess = currentProcess;
                clock++;
            }
        }
    }
    else
    {
        while (!processStack.empty() || visited < processes.size())
        {
            // check whether processes have arrived during execution of previous process
            for (int i = visited; i < processes.size() && processes[i][1] <= clock; i++)
            {
                processStack.push_back(processes[i]);
                visited++;
            }
            processStack.sort(sortByRemainingTime);
            if (processStack.empty())
            {
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
vector<vector<int>> roundRobin(vector<vector<int>> processes, int quanta)
{
    vector<vector<int>> result;
    sort(processes.begin(), processes.end(), sortByArrivalTime);
    // processStack[Process[0: ProcessNumber, 1: ArrivalTime, 2: OriginalBurstTime, 3: RemainingBurstTime, 4: ResponseTime]](the last 2 elements are only for preemptive)
    list<vector<int>> processStack;
    vector<int> currentProcess;

    int completionTime = 0;
    int turnAroundTime, waitingTime, responseTime;
    int clock = 0, visited = 0;

    processStack.push_front(processes[0]);
    clock = processes[0][1];

    while (!processStack.empty() || visited < processes.size())
    {
        // check if processes arrived
        for (int i = visited; i < processes.size() && processes[i][1] <= clock; i++)
        {
            currentProcess = processes[i];
            currentProcess.push_back(currentProcess[2]);
            //  duplicate burst time, so it can be used to calculate remaining burst time
            processStack.push_back(currentProcess);
            visited++;
        }
        if (processStack.empty())
        {
            clock++;
            continue;
        }
        if (currentProcess.size() < 5)
        {
            // set third variable as the response time
            // responseTime = clock - arrivalTimeOfCurrentProcess
            currentProcess.push_back(clock - currentProcess[1]);
        }
        if (currentProcess[3] <= quanta)
        {
            // if process can finish executing
            clock += currentProcess[3];

            responseTime = currentProcess[4];
            // completionTime = previousCompletionTime + burstTime
            completionTime = clock;
            // turnAroundTime = CompletionTime - arrivalTime
            turnAroundTime = completionTime - currentProcess[1];
            // waitingTime = turnAroundTime - burstTime
            waitingTime = turnAroundTime - currentProcess[2];
        }
    }
    return result;
}
