///Successfully Approved by Rejone E Rasul Hridoy
///@copyright of Rejone E Rasul Hridoy, all rights reserved
#include<bits/stdc++.h>
using namespace std;

struct Process{
    int processName;
    int cpuTime;
    int remainingTime;
    int arrivalTime;
    int waitingTime;
    int turnAroundTime;
};
vector <Process> process;
vector<int> timer,ganttProcess;
queue<int> readyQueue;
int timeQuantum,noOfProcess;

bool SortControl(Process p1, Process p2){
    return p1.arrivalTime < p2.arrivalTime;
}

void GanttChart()
{
    readyQueue.push(0);
    timer.push_back(process[0].arrivalTime);
    int latestIndex = -1;
    cout << "Process in ready queue: ";
    while(!readyQueue.empty()){
        int proccessIndex = readyQueue.front();
        cout << "P" << process[proccessIndex].processName+1 << " ";
        readyQueue.pop();
        if(process[proccessIndex].remainingTime > timeQuantum){
            timer.push_back(timer.back()+timeQuantum);
            process[proccessIndex].remainingTime -= timeQuantum;
            for(int i=proccessIndex+1; i<noOfProcess; i++){
                if( i > latestIndex && timer.back() >=process[i].arrivalTime){
                    latestIndex = i;
                    readyQueue.push(i);
                }
            }
            readyQueue.push(proccessIndex);
            ganttProcess.push_back(process[proccessIndex].processName);
        }else if(process[proccessIndex].remainingTime <= timeQuantum && process[proccessIndex].remainingTime >0){
            timer.push_back(timer.back()+process[proccessIndex].remainingTime);
            process[proccessIndex].remainingTime = 0;
            ganttProcess.push_back(process[proccessIndex].processName);
        }
    }
    cout << endl << endl << "Gantt Chart : " << endl;
    for(int i=0; i<ganttProcess.size(); i++){
        cout << "---" << ganttProcess[i]+1 << "---|";
    }
    cout << endl;
    for(int i=0; i<timer.size(); i++){
        cout << timer[i] << "\t";
    }
    /// calculate waiting time
    /// waiting time = start time - last completion time,arrival time
    for(int i=0; i<noOfProcess; i++){
        int lastCompletionTime = process[i].arrivalTime;
        process[i].waitingTime = 0;
        for(int j=0; j<ganttProcess.size(); j++){
            if(process[i].processName == ganttProcess[j]){
                process[i].waitingTime += timer[j] - lastCompletionTime;
                lastCompletionTime = timer[j+1];
            }
        }
    }
    ///calculate turn around time, avg waiting time,avg turn around time
    /// turn around time = waiting time + cpu time
    double avgWT = 0.0,avgTAT = 0.0;
    cout << endl << "\nName\tA.T.\tCPUTime\tW.T\tT.A.T" <<endl;
    for(int i=0; i<noOfProcess; i++){
        process[i].turnAroundTime = process[i].waitingTime + process[i].cpuTime;
        avgWT +=(double) process[i].waitingTime;
        avgTAT +=(double)process[i].turnAroundTime;
        cout << "P" <<process[i].processName+1 << "\t" << process[i].arrivalTime
        << "\t" << process[i].cpuTime << "\t" << process[i].waitingTime <<
        "\t" << process[i].turnAroundTime << endl;
    }
    cout << endl << "Average waiting Time : " << avgWT/noOfProcess << endl;
    cout << "Average turn around Time : " << avgTAT/noOfProcess << endl;
}

int main()
{
    cout << "Enter the number of process : ";
    cin >> noOfProcess;
    cout << "Enter the CPU Time : " << endl;
    for(int i=0; i<noOfProcess; i++){
        Process p;
        cin >> p.cpuTime;
        p.remainingTime = p.cpuTime;
        p.processName = i;
        process.push_back(p);
    }

    char c;
    cout << "Have arrival time? press Y/N: ";
    cin >> c;
    if(c == 'Y' || c == 'y'){
        cout << "Enter arrival time : " <<endl;
        for(int i=0; i<noOfProcess; i++){
            cin >> process[i].arrivalTime;
        }
    }else if(c == 'N' || c == 'n'){
        for(int i=0; i<noOfProcess; i++)
            process[i].arrivalTime = 0;
    }
    cout << "Enter time quantum : ";
    cin >> timeQuantum;

    sort(process.begin(),process.end(),SortControl);
    GanttChart();

    return 0;
}
/**
Sample Input 0:
4
5 4 1 6
y
0 2 4 5
2
Sample Output 0:

Process in ready queue: P1 P2 P1 P3 P2 P4 P1 P4 P4

Gantt Chart :
---1---|---2---|---1---|---3---|---2---|---4---|---1---|---4---|---4---|
0       2       4       6       7       9       11      12      14      16

Name    A.T.    CPUTime W.T     T.A.T
P1      0       5       7       12
P2      2       4       3       7
P3      4       1       2       3
P4      5       6       5       11

Average waiting Time : 4.25
Average turn around Time : 8.25

Sample Input 1:
4
5 7 9 9
y
4 0 6 10
3

Sample Output 1:
Process in ready queue: P2 P2 P1 P3 P2 P1 P4 P3 P4 P3 P4

---P2---|---P2---|---P1---|---P3---|---P2---|---P1---|---P4---|---P3---|---P4---|---P3---|---P4---|
0       3        6        9       12       13       15       18       21       24       27       30

Name    A.T.    CPUTime W.T     T.A.T
P2      0       7       6       13
P1      4       5       6       11
P3      6       9       12      21
P4      10      9       11      20

Average waiting Time : 8.75
Average turn around Time : 16.25
*/
