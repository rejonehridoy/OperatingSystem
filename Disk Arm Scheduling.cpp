#include<bits/stdc++.h>

using namespace std;
vector<int>requests;
void FCFS(int head)
{
    vector<int>r;
    int movement=0;
    r = requests;
    cout << "_______FCFS_______" <<endl<<endl;
    cout << "Cylinder Serving Order : "<<head;
    for(int i=0; i<r.size(); i++){
        movement+= abs(head-r[i]);
        head = r[i];
        cout << " -> "<<r[i];
    }
    cout << endl << "Total Cylinder Movement : "<<movement << endl<<endl;
}
void SSTF(int head)
{
    vector<int> r;
    int index;
    int movement=0;
    r = requests;
    r.push_back(head);
    sort(r.begin(),r.end());
    cout << "_______SSTF_______" <<endl<<endl;
    cout << "Cylinder Serving Order : "<<head;
    //get current head position
    for(int i=0; i<r.size(); i++){
        if(head==r[i]){
            index = i;
            break;
        }
    }

    while(r.size()>1){
        if(index-1>-1 && index+1<r.size()){
            int prev = head - r[index-1];
            int next = r[index+1] - head;
            if(prev<next){
                movement+=prev;
                r.erase(r.begin()+index);
                head = r[index-1];
                index--;
                cout << " -> " << head;
            }else{
                movement+=next;
                r.erase(r.begin()+index);
                head = r[index];
                cout << " -> " << head;
            }
        }else if(index<1){
            int next = r[index+1] - head;
            r.erase(r.begin()+index);
            head=r[index];
            movement+=next;
            cout << " -> " << head;
        }else{
            int prev = head - r[index-1];
            movement+=prev;
            r.erase(r.begin()+index);
            head = r[index-1];
            index--;
            cout << " -> " << head;
        }
    }
    cout << endl << "Total Cylinder Movement : "<<movement << endl<<endl;
}
void CSCAN(int head,int no_of_heads)
{
    vector<int> r;
    int index;
    int movement=0;
    r = requests;
    r.push_back(head);
    r.push_back(0);
    r.push_back(no_of_heads-1);
    sort(r.begin(),r.end());

    //get current head position
    for(int i=0; i<r.size(); i++){
        if(head==r[i]){
            index = i;
            break;
        }
    }
    cout << "_______CSACN_______" <<endl<<endl;
    cout << "Cylinder Serving Order : "<<head;
    for(int i=index; i<r.size()-1; i++){
        movement+=(r[i+1] - r[i]);
        cout << " -> "<<r[i+1];
    }
    movement+=(no_of_heads-1);
    cout << " -> " << r[0];
    for(int i=0; i<index-1; i++){
        movement+= (r[i+1] - r[i]);
        cout << " -> "<<r[i+1];
    }

    cout << endl << "Total Cylinder Movement : "<<movement << endl<<endl;


}
int main()
{
    int no_of_heads,min_head,max_head,no_of_requests,Head;
    cout << "Number of Heads : ";
    cin >> no_of_heads;
    cout << "Number of Cylinder Requests : ";
    cin >> no_of_requests;

    cout << "Cylinder Requests : ";
    for (int i = 0; i < no_of_requests; ++i) {
        int value;
        cin >> value;
        requests.push_back(value);
    }
    cout << "Current Head : ";
    cin >> Head;


    FCFS(Head);
    SSTF(Head);
    CSCAN(Head,no_of_heads);

    return  0;
}

/**
Input 0:
200
8
98 183 37 122 14 124 65 67
53

Output 0:
_______FCFS_______

Cylinder Serving Order : 53 -> 98 -> 183 -> 37 -> 122 -> 14 -> 124 -> 65 -> 67
Total Cylinder Movement : 640

_______SSTF_______

Cylinder Serving Order : 53 -> 65 -> 67 -> 37 -> 14 -> 98 -> 122 -> 124 -> 183
Total Cylinder Movement : 236

_______CSACN_______

Cylinder Serving Order : 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 0 -> 14 -> 37
Total Cylinder Movement : 382
*/
