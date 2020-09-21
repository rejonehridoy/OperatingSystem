#include<bits/stdc++.h>

using namespace std;

struct File{
    string file_name;
    int file_size;
    int start_address,end_address;
};
vector<File> files;
int remaining_blocks;

void create_file(int total_number_of_blocks)
{
    File file;
    cout << "\nEnter File Name: ";
    cin >> file.file_name;
    cout << "Enter File size: ";
    cin >> file.file_size;
    if(file.file_size <=remaining_blocks){
        file.start_address = total_number_of_blocks - remaining_blocks;
        file.end_address = file.start_address+file.file_size;
        remaining_blocks-= file.file_size;
        files.push_back(file);
        cout << "File "<<file.file_name <<" created" <<endl;

    }else{
        cout << "File "<<file.file_name<<" cannot be created (not enough free blocks)" <<endl;
    }
}

void search_file()
{
    string search_file_name;
    cout << "\nSearch Filename : ";
    cin >> search_file_name;
    bool isFound = false;
    for(int i=0; i<files.size(); i++){
        if(files[i].file_name == search_file_name){
            cout << "FileFound in the blocks: ";
            isFound = true;
            for(int j=files[i].start_address; j<files[i].end_address; j++){
                cout << j << " ";
            }
            cout << endl;
        }
    }
    if(!isFound){
        cout << "File Not Found" << endl;
    }
}

int main()
{
    int total_number_of_blocks;
    string name;
    cout << "Enter total number of blocks : ";
    cin >> total_number_of_blocks;
    remaining_blocks = total_number_of_blocks;

    while(true){
        cout << "\n1. Store  2. Search"<<endl;
        cout << "Enter your Response: ";
        int control;
        cin >> control;
        switch(control){
            case 1:     create_file(total_number_of_blocks);
                        break;
            case 2:     search_file();
                        break;
            default: return 0;
        }
    }
}
/**
Input 0:
200
1
A
4
1
B
400
1
C
40
2
C

Output 0:
File A created
File B cannot be created (not enough free blocks)
File C created
FileFound in the blocks: 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34
 35 36 37 38 39 40 41 42 43

*/
