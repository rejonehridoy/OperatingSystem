#include<bits/stdc++.h>

using namespace std;

struct Process
{
    int processName;
    vector<int> allocation;
    vector<int> Max;
    vector<int> need;
};
int noOfProcess,noOfResource;
vector<int>resources,available;
vector<Process> process;
queue<int>q;
void Available()
{
    cout << endl << "Available : ";
    for(int j=0; j<noOfResource; j++){
        int r=0;
        for(int i=0; i<noOfProcess; i++){
            r+= process[i].allocation[j];
        }
        available.push_back(resources[j] - r);
        cout << available[j] << " ";
    }

}
bool SortControl(Process p1, Process p2)
{
    int P1=0,P2=0;
    for(int j=0; j<noOfResource; j++){
        P1 += p1.need[j];
        P2 += p2.need[j];
    }
    return (P1<P2) ? true: false;
}

void Bankers()
{
    int countPush = 0;
    for(int i=0; i<noOfProcess; i++){
        bool canAllocate = true;
        for(int j=0; j<noOfResource; j++){
            if(process[i].need[j] > available[j]){
                canAllocate = false;
                break;
            }
        }
        if(canAllocate){
            for(int j=0; j<noOfResource; j++){
                available[j] += process[i].allocation[j];
            }
            q.push(process[i].processName);
            countPush++;
        }
    }
    if(countPush == noOfProcess){
        cout << "The system is currently in safe state\nThe Safe Sequence is : < ";
        while(!q.empty()){
            cout << "P" << q.front() << " ";
            q.pop();
        }
        cout << ">" <<endl;
    }else{
        cout << "The system is currently not in safe state" << endl;
    }

}
int main()
{
    //freopen("input_bankers_Algorithm.txt","r",stdin);
    cout << "Enter No of Process : ";
    cin >> noOfProcess;
    cout << "Enter no of resources : ";
    cin >> noOfResource;
    cout << "enter the amount of resources : " << endl;

    for(int i=0; i<noOfResource; i++){
        int r;
        cin >> r;
        resources.push_back(r);
    }
    for(int i=0; i< noOfProcess; i++){
        Process p;
        cout << "Process " << i << " :" << endl;
        p.processName = i;
        cout << "Allocated resources :" ;
        for(int j=0; j<noOfResource; j++){
            int r;
            cin >> r;
            p.allocation.push_back(r);
        }
        cout << "Max resources : ";
        for(int j=0; j<noOfResource; j++){
            int r;
            cin >> r;
            p.Max.push_back(r);
            p.need.push_back(p.Max[j]-p.allocation[j]);
        }
        process.push_back(p);
    }

    cout << "\nName\tAllocation\tMax\tNeed" << endl;
    for(int i=0; i<noOfProcess; i++){
        cout << "P" << process[i].processName << "\t";
        for(int j=0; j<noOfResource; j++){
            cout << process[i].allocation[j] << " ";
        }
        cout << "\t\t";
        for(int j=0; j<noOfResource; j++){
            cout << process[i].Max[j] << " ";
        }
        cout << "\t";
        for(int j=0; j<noOfResource; j++){
            cout << process[i].need[j] << " ";
        }
        cout << endl;
    }
    sort(process.begin(),process.end(),SortControl);
    Available();
    cout << endl;
    Bankers();

    return 0;
}
/**
Sample Input 0:
5 3
10 5 7
0 1 0 7 5 3
2 0 0 3 2 2
3 0 2 9 0 2
2 1 1 2 2 2
0 0 2 4 3 3

Sample Output 0:
Name    Allocation      Max     Need
P0      0 1 0           7 5 3   7 4 3
P1      2 0 0           3 2 2   1 2 2
P2      3 0 2           9 0 2   6 0 0
P3      2 1 1           2 2 2   0 1 1
P4      0 0 2           4 3 3   4 3 1

Available : 3 3 2
The system is currently in safe state
The Safe Sequence is : < P3 P1 P2 P4 P0 >

Sample Input 1:
7 3
20 19 16
1 1 1 7 5 6
2 3 3 5 8 5
3 0 5 9 2 8
2 2 0 8 8 6
3 1 0 14 4 5
1 2 1 4 6 3
1 1 1 2 9 2

Sample Output 1:
Name    Allocation      Max     Need
P1      1 1 1           7 5 6   6 4 5
P2      2 3 3           5 8 5   3 5 2
P3      3 0 5           9 2 8   6 2 3
P4      2 2 0           8 8 6   6 6 6
P5      3 1 0           14 4 5  11 3 5
P6      1 2 1           4 6 3   3 4 2
P7      1 1 1           2 9 2   1 8 1

Available : 7 9 5
The system is currently in safe state
The Safe Sequence is : < P6 P2 P7 P3 P1 P4 P5 >
*/
