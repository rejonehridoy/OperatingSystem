#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int processName;
    int arrivalTime;
    int cpuTime;
    int waitingTime;
    int priority;
    int turnAroundTime;
    int remainingTime;
};
vector<Process> process;
queue<int> readyQueue;
vector<int> timer,ganttProcess;
int noOfProcess;
bool SortArrivalTime(Process p1,Process p2){
    return (p1.arrivalTime == p2.arrivalTime)? p1.priority<p2.priority : p1.arrivalTime < p2.arrivalTime;
}
bool SortPriority(Process p1,Process p2)
{
    return p1.priority < p2.priority;
}
void GanttChart_Preemtive()
{
    readyQueue.push(0);
    timer.push_back(process[0].arrivalTime);
    cout << "Process in ready queue: ";
    while(!readyQueue.empty()){
        int processIndex = readyQueue.front();
        cout << "P" << process[processIndex].processName+1 << " ";
        readyQueue.pop();
        if(timer.back() < process[processIndex+1].arrivalTime && process[processIndex].priority > process[processIndex+1].priority){
            process[processIndex].remainingTime -= process[processIndex+1].arrivalTime - timer.back();
            timer.push_back(process[processIndex+1].arrivalTime);
            readyQueue.push(processIndex+1);
            ganttProcess.push_back(process[processIndex].processName);
        }else{
            timer.push_back(timer.back()+process[processIndex].remainingTime);
            process[processIndex].remainingTime = 0;
            ganttProcess.push_back(process[processIndex].processName);
        }
    }
    sort(process.begin(),process.end(),SortPriority);
    for(int i=0; i<noOfProcess; i++){
        if(process[i].remainingTime !=0){
            timer.push_back(timer.back()+process[i].remainingTime);
            ganttProcess.push_back(process[i].processName);
            process[i].remainingTime = 0;
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
    cout << endl << "\nName\tA.T.\tCPUTime\tpriority  W.T\tT.A.T" <<endl;
    for(int i=0; i<noOfProcess; i++){
        process[i].turnAroundTime = process[i].waitingTime + process[i].cpuTime;
        avgWT +=(double) process[i].waitingTime;
        avgTAT +=(double)process[i].turnAroundTime;
        cout << "P" <<process[i].processName+1 << "\t" << process[i].arrivalTime
        << "\t" << process[i].cpuTime <<"\t" << process[i].priority << "\t  " << process[i].waitingTime <<
        "\t" << process[i].turnAroundTime << endl;
    }
    cout << endl << "Average waiting Time : " << avgWT/noOfProcess << endl;
    cout << "Average turn around Time : " << avgTAT/noOfProcess << endl;

}
int main()
{
    cout << "Enter no of process : ";
    cin >> noOfProcess;
    cout << "Enter CPU Time " << endl;
    for(int i=0; i<noOfProcess; i++){
        Process p;
        cin >> p.cpuTime;
        p.processName = i;
        p.remainingTime = p.cpuTime;
        process.push_back(p);
    }
    cout << "Have Arrival Time? press Y/N: ";
    char c;
    cin >> c;
    if(c == 'Y' || c == 'y'){
        cout << "Enter Arrival Time : " << endl;
        for(int i=0; i<noOfProcess; i++){
            cin >> process[i].arrivalTime;
        }

    }else if(c == 'N' || c == 'n'){
        for(int i=0; i<noOfProcess; i++){
            process[i].arrivalTime = 0;
        }
    }
    cout << "Enter the priority :" << endl;
    for(int i=0; i<noOfProcess; i++){
        cin >> process[i].priority;
    }
    sort(process.begin(),process.end(),SortArrivalTime);
    GanttChart_Preemtive();

    return 0;
}
/**
Sample Input 0:
3
5 7 9
y
4 0 2
0 2 1

Sample Output 1:
Process in ready queue: P2 P3 P1

Gantt Chart :
---P2---|---P3---|---P1---|---P3---|---P2---|
0       2        4        9        16      21

Name    A.T.    CPUTime W.T     T.A.T
P1      4       5       0       5
P3      2       9       5       14
P2      0       7       14      21

Average waiting Time : 6.33333
Average turn around Time : 13.3333
*/
