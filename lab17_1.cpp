#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    const char* cfile = filename.c_str();
    ifstream source(cfile);
    string text;
    char Name[100];
    char format[]="%[^:]: %d %d %d";
    int k=0;
    while(getline(source,text))
    {
        int Score = 0,x,y,z;
        const char * ctext = text.c_str();
        sscanf(ctext,format,Name,&x,&y,&z);
        Score+=(x+y+z);
        names.push_back(Name);
        scores.push_back(Score);
        grades.push_back(score2grade(scores.at(k)));
        k++;
    }
}

void getCommand(string &command,string &key){
    string key2;
    char ch;
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command)=="EXIT" or toUpperStr(command)=="NAME" or toUpperStr(command)=="GRADE")
        {
            cin >> ch;
            getline(cin,key);
        }
    key2 = ch+key;
    key = key2;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool found = true;
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<names.size();i++)
    {
        if(key==toUpperStr(names.at(i)))
        {
            cout << names.at(i) << "'s " << "score = " << scores.at(i) << '\n';
            cout << names.at(i) << "'s " << "grade = " << grades.at(i) << '\n';
            found = false;
        }
    }
    if(found)
    {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool found = true;
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<names.size();i++)
    {
        if(key[0]== grades.at(i))
        {
            cout << names.at(i) << ' ' << '(' << scores.at(i) << ")\n";
            found = false;
        }
    }
    if(found)
    {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
