#include<bits/stdc++.h>

using namespace std;
vector<int>reference_string;

void showSimulation(int arr[],int no_frames,int value){
    cout << "Adding "<<value << ": ";
    for(int i=0;i <no_frames; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}
bool search_Value(int arr[],int no_frames,int value)
{
    for(int i=0; i<no_frames; i++){
        if(arr[i]==value){
            return true;
        }
    }
    return false;
}
int find_max(int arr[],int Size){
    int maximum = -1,index=-1;
    for(int i=0; i<Size; i++){
        if(arr[i]==-1){     ///checking value which is not available in the remaining reference array
            return i;
        }
        if(arr[i] > maximum){
            maximum = arr[i];
            index = i;
        }
    }

    return (index==-1)? 0:index;

}
int find_min(int arr[],int Size){
    int minimum = INT_MAX,index=-1;
    for(int i=0; i<Size; i++){
        if(arr[i]==-1){     ///checking value which is not available in the remaining reference array
            return i;
        }
        if(arr[i] < minimum){
            minimum = arr[i];
            index = i;
        }
    }

    return (index==-1)? 0:index;

}

void FIFO(int no_frames,int no_references){
    int frames[no_frames];
    for(int i=0; i<no_frames; i++){
        frames[i] = -1;
    }
    int page_faults=0;
    queue<int>q;    ///for storing index

    cout << "________FIFO_______" << endl;
    for(int i=0,frame=0; i<no_references; i++){
        if(i<no_frames){
            if(search_Value(frames,no_frames,reference_string[i])){     ///if found in the frame
                cout << "found : "<<reference_string[i] <<endl;
                continue;
            }else{
                frames[frame] = reference_string[i];
                q.push(frame);
                frame++;
                page_faults++;
                showSimulation(frames,no_frames,reference_string[i]);
            }

        }else{
            if(search_Value(frames,no_frames,reference_string[i])){     ///if found in the frame
                cout << "found : "<<reference_string[i] <<endl;
                continue;
            }else{
                int f = q.front();
                q.pop();
                q.push(f);
                frames[f] = reference_string[i];
                page_faults++;
                showSimulation(frames,no_frames,reference_string[i]);
            }
        }

    }
    cout << "\nPage Faults : "<< page_faults << endl;
    cout << "Page Faults Rate : "<< (page_faults/(float)no_references)*100 << "%" << endl;

}
void Optimal(int no_frames,int no_references){
    int frames[no_frames];
    for(int i=0; i<no_frames; i++){
        frames[i] = -1;
    }
    int page_faults=0;
    cout << "\n_______Optimal______"<<endl;

    for(int i=0,frame=0; i<no_references; i++){
        if(i<no_frames){
           if(search_Value(frames,no_frames,reference_string[i])){     ///if found in the frame
                cout << "found : "<<reference_string[i] <<endl;
                continue;
            }else{
                frames[frame] = reference_string[i];
                frame++;
                page_faults++;
                showSimulation(frames,no_frames,reference_string[i]);
            }
        }else{
            if(search_Value(frames,no_frames,reference_string[i])){     ///if found in the frame
                cout << "found : "<<reference_string[i] <<endl;
                continue;
            }else{
                int isFound[no_frames];
                for(int in=0; in<no_frames; in++)
                    isFound[in] = -1;

                for(int j=0; j<no_frames; j++){         ///loop of page frame array
                    for(int k=i+1; k<no_references; k++){         ///loop of remaining references string
                        if(frames[j] == reference_string[k] && isFound[j] ==-1){
                            isFound[j] = k;
                        }
                    }
                }
                int index = find_max(isFound,no_frames);
                frames[index] = reference_string[i];
                page_faults++;
                showSimulation(frames,no_frames,reference_string[i]);
            }
        }
    }

    cout << "\nPage Faults : "<< page_faults << endl;
    cout << "Page Faults Rate : "<< (page_faults/(float)no_references)*100 << "%" << endl;
}

void LRU(int no_frames,int no_references)
{
    int frames[no_frames];
    for(int i=0; i<no_frames; i++){
        frames[i] = -1;
    }
    int page_faults=0;
    cout << "\n_______LRU______"<<endl;

    for(int i=0,frame=0; i<no_references; i++){
        if(i<no_frames){
           if(search_Value(frames,no_frames,reference_string[i])){     ///if found in the frame
                cout << "found : "<<reference_string[i] <<endl;
                continue;
            }else{
                frames[frame] = reference_string[i];
                frame++;
                page_faults++;
                showSimulation(frames,no_frames,reference_string[i]);
            }
        }else{
            if(search_Value(frames,no_frames,reference_string[i])){     ///if found in the frame
                cout << "found : "<<reference_string[i] <<endl;
                continue;
            }else{
                int isFound[no_frames];
                for(int in=0; in<no_frames; in++)
                    isFound[in] = -1;

                for(int j=0; j<no_frames; j++){         ///loop of page frame array
                    for(int k=i-1; k>=0; k--){         ///loop of remaining references string
                        if(frames[j] == reference_string[k] && isFound[j] ==-1){
                            isFound[j] = k;
                        }
                    }
                }
                int index = find_min(isFound,no_frames);
                frames[index] = reference_string[i];
                page_faults++;
                showSimulation(frames,no_frames,reference_string[i]);
            }
        }
    }

    cout << "\nPage Faults : "<< page_faults << endl;
    cout << "Page Faults Rate : "<< (page_faults/(float)no_references)*100 << "%" << endl;
}


int main(){
    int no_of_pages,no_of_page_frame,no_of_reference;

    cout << "Enter the number of pages : ";
    cin >> no_of_pages;
    cout << "Enter the number of page references : ";
    cin >> no_of_reference;

    cout << "Reference String : ";
    for(int i=0; i<no_of_reference; i++){
        int value;
        cin >> value;
        reference_string.push_back(value);
    }
    cout << "Enter number of page frames : ";
    cin >> no_of_page_frame;

    while(true){
        cout<<"\n\n_________Page Replacement Algorithm_________"<<endl;
        cout << "1. FIFO\n2. Optimal\n3. LRU" << endl;
        cout <<"\nEnter Your Response : ";
        int response;
        cin >> response;
        switch(response){
            case 1: FIFO(no_of_page_frame,no_of_reference);
                    break;
            case 2: Optimal(no_of_page_frame,no_of_reference);
                    break;
            case 3: LRU(no_of_page_frame,no_of_reference);
                    break;
            default: return 0;
        }
    }
    return 0;
}

/**
Input 0:
8
22
7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
3

Output 0:
________FIFO_______

Page Faults : 15
Page Faults Rate : 68.1818%

_______Optimal______

Page Faults : 9
Page Faults Rate : 40.9091%

_______LRU______

Page Faults : 12
Page Faults Rate : 54.5455%

Input 1:
8
15
7 0 1 2 0 3 0 4 2 3 0 3 1 2 0
3

OutPut 1:
________FIFO_______

Page Faults : 12
Page Faults Rate : 80%

_______Optimal______

Page Faults : 8
Page Faults Rate : 53.3333%

_______LRU______

Page Faults : 12
Page Faults Rate : 80%


Input 2:
8
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
3

Output 2:
________FIFO_______

Page Faults : 15
Page Faults Rate : 75%

_______Optimal______

Page Faults : 9
Page Faults Rate : 45%

_______LRU______

Page Faults : 12
Page Faults Rate : 60%
*/
