#include<bits/stdc++.h>

using namespace std;
vector<string>files;    //store only filename
int total_number_of_blocks,remaining_size;
void create_file(string data_table[])
{
    int file_size;
    string file_name;
    cout << "Enter File name: ";
    cin >> file_name;

    cout << "Enter File Size : ";
    cin >> file_size;

    if(file_size <= remaining_size){
        int file_location;
        remaining_size-= file_size;
        for(int i=0; i<file_size; i++){
            bool isLocationFound = false;
            do{
                file_location = rand()%total_number_of_blocks;
                if(data_table[file_location] == "$"){
                    data_table[file_location] = file_name;
                    isLocationFound = true;
                }
            }while(!isLocationFound);
        }
        files.push_back(file_name);
        cout << "File "<<file_name<< " created" << endl;
    }else{
        cout << "File "<<file_name<<" cannot be created (not enough free blocks)" <<endl;
    }

}

void search_file(string data_table[])
{
    string file_name;
    cout << "Search Filename: ";
    cin >> file_name;
    bool is_file_found = false;
    for(int i=0; i<files.size(); i++){
        if(files[i] == file_name){
            is_file_found = true;
            break;
        }
    }
    if(is_file_found){
        cout << "File Found in the blocks : ";
        for(int i=0; i<total_number_of_blocks; i++){
            if(data_table[i] == file_name){
                cout << i << " ";
            }
        }
        cout << endl;
    }else{
        cout << "File Not Found"<<endl;
    }
}

int main()
{
    cout << "Enter total number of blocks : ";
    cin >> total_number_of_blocks;
    remaining_size = total_number_of_blocks;

    string data_table[total_number_of_blocks];
    for(int i=0; i<total_number_of_blocks; i++){    //initialize array with $
        data_table[i] = "$";
    }


    while(true){
        cout << "\n1. Store  2. Search"<<endl;
        cout << "Enter your Response: ";
        int control;
        cin >> control;
        switch(control){
            case 1: create_file(data_table);
                    break;

            case 2: search_file(data_table);
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
File Found in the blocks : 4 11 21 27 35 36 47 64 69 73 78 81 91 92 94 95 99 102 103 105 112 116 118 122 124 126
133 138 141 142 145 153 158 161 162 169 171 182 191 195

*/
