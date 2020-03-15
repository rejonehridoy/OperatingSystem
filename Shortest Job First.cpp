#include<bits/stdc++.h>

using namespace std;

struct Process{
    int processName;
    int arrivalTime;
    int cpuTime;
    int waitingTime;
    int turnArroundTime;
    int responseTime;
    bool isProcessed;
};
vector <Process> process;
int noOfProcess,minProcessTime=0,minProcessName,timer[11],minCPUTime;

bool SortControl(Process p1,Process p2)
{
    return (p1.cpuTime == p2.cpuTime) ? p1.arrivalTime < p2.arrivalTime : p1.cpuTime < p2.cpuTime;
}

void GanttChart()
{
    timer[0] = minProcessTime;
    timer[1] = timer[0]+ minCPUTime;
    cout << "|---" << "P" << minProcessName << "---";
    for(int i=0,j=1; i<noOfProcess; i++){
        if(process[i].processName == minProcessName){
            process[i].responseTime = 0;
            process[i].waitingTime = 0;
            process[i].turnArroundTime = process[i].cpuTime;
            continue;
        }

        timer[j+1] = timer[j] + process[i].cpuTime;
        process[i].responseTime = timer[j];
        j++;
        process[i].waitingTime = process[i].responseTime - process[i].arrivalTime;
        process[i].turnArroundTime = process[i].waitingTime + process[i].cpuTime;
        cout << "|---" << "P" << process[i].processName << "---";
    }
    cout << "|" << endl ;
    for(int i=0; i<=noOfProcess; i++){
        cout << timer[i] << "\t";
    }
    double avgWT=0.0,avgTAT=0.0;
    cout << endl <<endl<< "Process\tCPUTime\tA.T\tW.T\tT.A.T" << endl;
    for(int i=0; i<noOfProcess; i++){
        avgWT += (double)process[i].waitingTime;
        avgTAT += (double)process[i].turnArroundTime;
        cout <<"P" << process[i].processName << "\t" << process[i].cpuTime << "\t" <<process[i].arrivalTime <<
        "\t"<<process[i].waitingTime << "\t" << process[i].turnArroundTime << endl;
    }
    cout << endl << "Average Waiting Time : " << avgWT/noOfProcess << endl
    << "Average Turn Around Time : " << avgTAT/noOfProcess << endl;

}

int main()
{
    cout << "Enter no of process :" ;
    cin >> noOfProcess;
    cout << "Enter the CPU time : " << endl;
    for(int i=0; i<noOfProcess; i++){
        Process temp;
        temp.processName = i+1;
        cin >> temp.cpuTime;
        process.push_back(temp);
    }
    cout << "Has any arrival time ? press Y/N: " ;
    char c;
    cin >> c;
    if(c == 'Y' || c == 'y'){
        cout << "Enter the arrival time : " <<endl;
        for(int i=0; i<noOfProcess; i++){
            cin >> process[i].arrivalTime;
            if(minProcessTime >= process[i].arrivalTime){
                minProcessTime = process[i].arrivalTime;
                minCPUTime = minProcessTime + process[i].cpuTime;
                minProcessName = i+1;
            }
        }

    }else if(c == 'N' || c == 'n'){
        for(int i=0; i<noOfProcess; i++){
            process[i].arrivalTime = 0;
        }
    }
    sort(process.begin(),process.end(),SortControl);
    cout << "Gantt Chart :" << endl;
    GanttChart();
    return 0;
}

/**
Sample Input:
3
5 7 9
y
4 0 2

Sample Output:
Gantt Chart :
|---P2---|---P1---|---P3---|
0       7       12      21

Process CPUTime A.T     W.T     T.A.T
P1      5       4       3       8
P2      7       0       0       7
P3      9       2       10      19

Average Waiting Time : 4.33333
Average Turn Around Time : 11.3333
*/
