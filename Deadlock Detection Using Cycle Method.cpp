#include<bits/stdc++.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
using namespace std;

int noOfNodes,noOfEdges;
vector<int >adj[15];
bool isFoundDeadlock = false;
int isMarked[15];
int L[20];
int Size = 0;
map < string ,int> node;
map <int , string > reveseNode;
stack < int > cycleElements;

void print()
{
    cout << "cycles are : ";
    while(!cycleElements.empty()){
        cout << reveseNode[cycleElements.top()] << " ";
        cycleElements.pop();
    }
    cout << endl;
    isFoundDeadlock = true;
}

void Detection(int startingNode)
{
    isMarked[startingNode] = GRAY;
    L[Size++] = startingNode;

    for(int i=0; i<adj[startingNode].size(); i++){
        int v = adj[startingNode][i];
        //cout << "adj : " << reveseNode[v] << endl;
        if(isMarked[v] == WHITE){
            Detection(v);
        }else if(isMarked[v] == GRAY){
            for(int j=Size-1; j>=0; j--){
                if(v == L[j]){
                    cycleElements.push(v);
                    break;
                }else{
                    cycleElements.push(L[j]);
                    Size--;
                }
            }
            print();
        }
    }
    isMarked[startingNode] = BLACK;
}

int main()
{
    cout << "Enter number of nodes & Edges : ";
    cin >> noOfNodes >> noOfEdges;

    cout << "Nodes Name : ";
    for(int i=0; i<noOfNodes; i++){
        string name;
        cin >> name;
        node[name] = i;
        reveseNode[i] = name;
        isMarked[i] = WHITE;
    }
    for(int i=0; i<noOfEdges; i++){
        string u,v;
        cin >> u >> v;
        //adj[u].push_back(v);
        adj[node[u]].push_back(node[v]);
    }

    cout << "Enter staring Nodes : ";
    string startingNode;
    cin >> startingNode;

    Detection(node[startingNode]);
    for(int i=0; i<noOfNodes; i++){
        if(isMarked[i] == WHITE){
            Detection(i);
        }
    }
    isFoundDeadlock ? cout << "Deadlock Found" << endl : cout << "No Deadlock Found" << endl;

    return 0;
}

/**
Sample Input:
13 13
R A C S D T B E F U V W G
R A
A S
C S
D T
D S
F S
W F
U D
B T
T E
E V
V G
G U
R

Sample Output:
cycles are : D T E V G U
Deadlock Found
*/
