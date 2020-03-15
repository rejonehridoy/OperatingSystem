#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int processName;
    int arrivalTime;
    int cpuTime;
    int waitingTime;
    int priority;
    int responseTime;
    int turnAroundTime;
};
vector<Process> process;
int timer[10];
int noOfProcess;
bool SortArrivalTime(Process p1, Process p2)
{
    return  p1.arrivalTime < p2.arrivalTime;
}
bool SortPriority(Process p1, Process p2)
{
    return p1.priority < p2.priority;
}

void GanttChart_NonPreemtive()
{
    timer[0] = process[0].arrivalTime;
    sort(process.begin()+1,process.end(),SortPriority);
    for(int i=0; i<noOfProcess; i++){
        timer[i+1]= timer[i]+process[i].cpuTime;
        process[i].responseTime = timer[i];
        process[i].waitingTime = process[i].responseTime - process[i].arrivalTime;
        process[i].turnAroundTime = process[i].waitingTime + process[i].cpuTime;
        cout << "|---" << "P" << process[i].processName << "---";
    }
    cout <<  "|" << endl;

    for(int i=0; i<=noOfProcess; i++){
        cout << timer[i] << "\t";
    }
    double avgWT=0.0,avgTAT=0.0;
    cout << endl <<endl<< "Process\tCPUTime\tA.T\tpriority  W.T\tT.A.T" << endl;
    for(int i=0; i<noOfProcess; i++){
        avgWT += (double)process[i].waitingTime;
        avgTAT += (double)process[i].turnAroundTime;
        cout <<"P" << process[i].processName << "\t" << process[i].cpuTime << "\t" <<process[i].arrivalTime <<
        "\t" << process[i].priority <<"\t "<<process[i].waitingTime << "\t" << process[i].turnAroundTime << endl;
    }
    cout << endl << "Average Waiting Time : " << avgWT/noOfProcess << endl
    << "Average Turn Around Time : " << avgTAT/noOfProcess << endl;

}
int main()
{
    cout << "Enter no of process : ";
    cin >> noOfProcess;
    cout << "Enter CPU Time " << endl;
    for(int i=0; i<noOfProcess; i++){
        Process p;
        cin >> p.cpuTime;
        p.processName = i+1;
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
    GanttChart_NonPreemtive();

    return 0;
}
///didnt handle if a process havent come in the cpu
/**
Sample Input 0:
3
5 7 9
y
4 0 2
0 2 1
Sample Output 0:
|---P2---|---P1---|---P3---|
0       7       12      21

Process CPUTime A.T     priority  W.T   T.A.T
P2      7       0       2        0      7
P1      5       4       0        3      8
P3      9       2       1        10     19

Average Waiting Time : 4.33333
Average Turn Around Time : 11.3333
*/
