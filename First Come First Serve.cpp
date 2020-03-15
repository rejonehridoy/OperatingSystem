#include<bits/stdc++.h>

using namespace std;

struct Process{
    int processName;
    int arrivalTime;
    int cpuTime;
    int waitingTime;
    int turnArroundTime;
    int responseTime;
};
vector <Process> process;
int noOfProcess;
int timer[11];
bool SortControl(Process p1, Process p2){
    return p1.arrivalTime < p2.arrivalTime;
}

void GanttChart()
{
    timer[0] = process[0].arrivalTime;

    for(int i=0; i<noOfProcess; i++){
        timer[i+1] = timer[i] + process[i].cpuTime;
        process[i].responseTime = timer[i];
        process[i].waitingTime = process[i].responseTime - process[i].arrivalTime;
        process[i].turnArroundTime = process[i].waitingTime + process[i].cpuTime;
        cout << "|---" << "P" << process[i].processName << "---";
    }
    cout <<  "|" << endl;

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
        }

    }else if(c == 'N' || c == 'n'){
        for(int i=0; i<noOfProcess; i++){
            process[i].arrivalTime = 0;
        }
    }
    sort(process.begin(),process.end(),SortControl);

    cout << endl  <<"Gantt Chart :"<< endl << endl;
    GanttChart();

    return 0;
}

/**
Sample Input 0:
3
5 7 9
y
4 0 2

Sample Output 0:
Gantt Chart :

|---P2---|---P3---|---P1---|
0       7       16      21

Process CPUTime A.T     W.T     T.A.T
P2      7       0       0       7
P3      9       2       5       14
P1      5       4       12      17

Average Waiting Time : 5.66667
Average Turn Around Time : 12.6667

*/
