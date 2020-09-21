#include<bits/stdc++.h>

using namespace std;
vector<int>Holes,Requests;

void ShowSimulation(vector<int>temp,int value){
    cout << "Allocated "<<value << " : ";
    for(int i=0; i<temp.size(); i++){
        cout << temp[i] << " ";
    }
    cout << endl;
}
void Memory_Management(int control)
{
    vector<int>r;
    r = Holes;
    if(control ==1){
        cout << "________First Fit_______"<<endl<<endl;
    }
    else if(control == 2){
        sort(r.begin(),r.end());
        cout << "________Best Fit_______"<<endl<<endl;
    }else if(control ==3){
        sort(r.begin(),r.end(),greater<int>());
        cout << "________Worst Fit_______"<<endl<<endl;
    }


    int countRequest = 0;
    for(int i=0; i<Requests.size(); i++){
        bool isAllocated = false;
        if(control ==2){
            sort(r.begin(),r.end());
        }else if(control==3){
            sort(r.begin(),r.end(),greater<int>());
        }
        for(int j=0; j<r.size(); j++){
            if(Requests[i]<=r[j]){
                r[j]-= Requests[i];
                isAllocated=true;
                countRequest++;
                ShowSimulation(r,Requests[i]);
                break;
            }
        }
        if(!isAllocated){
            cout << "Could not added "<<Requests[i] << endl;
            break;
        }
    }

    if(countRequest == Requests.size()){
        cout << endl << "No External Fragmentation" <<endl;
    }else{
        int sum=0;
        for(int i=0; i<r.size(); i++){
            sum+= r[i];
        }
        cout <<endl << "External Fragmentation : "<<sum<<endl<<endl;
    }

}


int main()
{
    int no_of_holes,no_of_requests;

    cout << "Enter number of Holes : ";
    cin >> no_of_holes;
    cout << "Enter number of Requests : ";
    cin >> no_of_requests;

    cout << "Memory Holes : ";
    for(int i=0; i<no_of_holes; i++){
        int hole;
        cin >> hole;
        Holes.push_back(hole);
    }
    for(int i=0; i<no_of_requests; i++){
        int request;
        cin >> request;
        Requests.push_back(request);
    }

    Memory_Management(1);
    Memory_Management(2);
    Memory_Management(3);

    return 0;
}

/**
Input 0:
5
10
50 200 70 115 15
100 10 35 15 23 6 25 55 88 40

Output 0:
________First Fit_______
Could not added 40

External Fragmentation : 93

________Best Fit_______
No External Fragmentation

________Worst Fit_______
Could not added 88

External Fragmentation : 181
*/

