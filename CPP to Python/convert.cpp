#include "iostream"
#include "fstream"
using namespace std;




int main(){

    string names;
    cout<<"Enter file name: \n";
    cin>>names;

    ifstream inputFile(names);

    if(!inputFile.is_open()){
        cout<<"Unable to open file"<<endl;
        return 1;
    }

    string line;

    cout<<"file content is as follows: "<<endl;

    while(getline(inputFile,line)){
        cout<<line<<endl;
    }
    inputFile.close();

    return 0;
    //changes made by Yash Desai
}