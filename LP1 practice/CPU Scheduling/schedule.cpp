#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Process
{
public:
    int id;
    int pr;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;

    Process()
    {
        id = at = bt = ct = tat = wt = rt = pr = 0;
    }

    Process(int i, int a, int b, int p)
    {
        id = i;
        at = a;
        bt = b;
        ct = tat = wt = rt = 0;
        pr = p;
    }

    print()
    {
        cout << "P" << id << ": AT = " << at << ", BT = " << bt << ", CT = " << ct << ", TAT = " << tat << ", WT = " << wt << ", RT = " << rt << endl;
    }
};

void FCFS(vector<Process> ReadyQueue)
{
    vector<Process> Schedule;

    while (!ReadyQueue.empty())
    {
        int minAT = 999;
        int minProcessIndex;
        for (int i = 0; i < ReadyQueue.size(); i++)
        {
            if (ReadyQueue[i].at < minAT)
            {
                minAT = ReadyQueue[i].at;
                minProcessIndex = i;
            }
        }
        Schedule.push_back(ReadyQueue[minProcessIndex]);
        ReadyQueue.erase(ReadyQueue.begin() + minProcessIndex);
    }

    int currTime = 0;

    for (int i = 0; i < Schedule.size(); i++)
    {
        if (currTime >= Schedule[i].at)
        {
            Schedule[i].ct = currTime + Schedule[i].bt;
            Schedule[i].tat = Schedule[i].ct - Schedule[i].at;
            Schedule[i].wt = Schedule[i].tat - Schedule[i].bt;
            Schedule[i].rt = currTime - Schedule[i].at;
            currTime = Schedule[i].ct;
        }
        else if (Schedule[i].at > currTime)
        { // case of idle state
            currTime = Schedule[i].at;
            Schedule[i].ct = currTime + Schedule[i].bt;
            Schedule[i].tat = Schedule[i].ct - Schedule[i].at;
            Schedule[i].wt = Schedule[i].tat - Schedule[i].bt;
            Schedule[i].rt = currTime - Schedule[i].at;
            currTime = Schedule[i].ct;
        }
    }

    cout << "\nFCFS:\n";
    for (int i = 0; i < Schedule.size(); i++)
    {
        Schedule[i].print();
    }
}

bool compareArrivalTime(Process P1, Process P2)
{
    return P1.at < P2.at;
}

void SJF_preemptive(vector<Process> ReadyQueue)
{
    int n = ReadyQueue.size();
    int remainingTime[n];

    for (Process P : ReadyQueue)
    {
        remainingTime[P.id] = P.bt;
    }

    sort(ReadyQueue.begin(), ReadyQueue.end(), compareArrivalTime);

    int currTimer = 0;
    int completed = 0;

    cout << "\nSJF Gantt Chart:\n";
    cout << "(0) ";

    while (completed < n)
    {
        int shortest = -1;
        int shortestTime = 999;

        for (int i = 0; i < n; i++)
        {
            int pid = ReadyQueue[i].id;
            if (ReadyQueue[i].at <= currTimer && remainingTime[pid] < shortestTime && remainingTime[pid] > 0)
            {
                shortest = i;
                shortestTime = remainingTime[pid];
            }
        }

        if (shortest == -1)
        {
            // no job, idle CPU
            currTimer++;
            cout << " -- (" << currTimer << ")";
            continue;
        }

        remainingTime[ReadyQueue[shortest].id]--;
        currTimer++;
        cout << "P" << ReadyQueue[shortest].id << " (" << currTimer << ")";

        if (remainingTime[ReadyQueue[shortest].id] == 0)
        {
            completed++;
            ReadyQueue[shortest].ct = currTimer;
            ReadyQueue[shortest].tat = ReadyQueue[shortest].ct - ReadyQueue[shortest].at;
            ReadyQueue[shortest].wt = ReadyQueue[shortest].tat - ReadyQueue[shortest].bt;
        }
    }

    cout << "\nSJF Calculations:\n";
    for (int i = 0; i < n; i++)
    {
        ReadyQueue[i].print();
    }
}

void RoundRobin(vector<Process> processes, int quantum)
{
    int n = processes.size();
    int remaining_time[n];
    int completed = 0;

    for (Process P : processes)
    {
        remaining_time[P.id] = P.bt;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    queue<Process> ready_queue;
    int currTime = 0;
    cout << "\nRound Robin Gantt Chart:\n(0) ";

    currTime = processes[0].at;
    cout << "(" << currTime << ") "; 
    ready_queue.push(processes[0]);

    while(completed < n){
        Process p = ready_queue.front();
        ready_queue.pop();

        int executionTime = min(p.bt, quantum);
        remaining_time[p.id] -= executionTime;
        currTime += executionTime;

        cout << "P" << p.id << " (" << currTime << ")";

        for(auto P : processes){
            if(P.at <= currTime && remaining_time[P.id] > 0 && P.id != p.id){
                ready_queue.push(P);
            }
        }

        if(remaining_time[p.id] > 0){
            ready_queue.push(p);
        }
        else {
            completed++;
            vector<Process> :: iterator pr;
            for(pr = processes.begin(); pr != processes.end(); pr++){
                if(pr->id == p.id){
                    pr->ct = currTime;
                    pr->tat = pr->ct - pr->at;
                    pr->wt = pr->tat - pr->bt;
                }
            }
        }
    }

    cout << "\nRound Robin Calculations:\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].print();
    }

}

bool comparePriority(Process P1, Process P2){
    return P1.pr > P2.pr;
}

void PriorityScheduling_non_preemptive(vector<Process> processes){
    sort(processes.begin(), processes.end(), comparePriority);

    int currTime = 0;
    cout << "\nPriority Scheduling Gantt Chart:\n(0) ";

    vector<Process> :: iterator p;
    for(p = processes.begin(); p != processes.end(); p++){
        currTime += p->bt;
        p->ct = currTime;
        cout << "P" << p->id << " (" << p->ct << ")";

        p->tat = p->ct - p->at;
        p->wt = p->tat - p->bt;
    }
}

int main()
{
    int n;
    vector<Process> ReadyQueue;
    cout << "Enter no. of processes: ";
    cin >> n;

    // input processes
    for (int i = 0; i < n; i++)
    {
        Process P;
        P.id = i + 1;
        cout << "Enter Process " << (i + 1) << " (AT): ";
        cin >> P.at;
        cout << "Enter Process " << (i + 1) << " (BT): ";
        cin >> P.bt;
        cout << "Enter Process " << (i + 1) << " (Priority): ";
        cin >> P.pr;
        ReadyQueue.push_back(P);
        cout << endl;
    }

    cout << "\nReady Queue:\n";
    for (int i = 0; i < n; i++)
    {
        ReadyQueue[i].print();
    }

    FCFS(ReadyQueue);

    SJF_preemptive(ReadyQueue);

    int quantum;
    cout << "\nEnter quantum: ";
    cin >> quantum;
    RoundRobin(ReadyQueue, quantum);

    PriorityScheduling_non_preemptive(ReadyQueue);

    return 0;
}