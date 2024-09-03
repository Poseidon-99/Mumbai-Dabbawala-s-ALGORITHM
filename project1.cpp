#include<string>
#include<map>
#include<algorithm>
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

struct Student{
    string name;
    string id;
    string branch;
    int year;
    string hostel;
    int social_score;
    string club;
    string sport;
    
};

string getBranch(){
    map<string,string> m{

    {"cse", "Computer Science and Engineering"},
    {"me", "Mechanical Engineering"},
    {"ee", "Electrical Engineering"},
    {"ce", "Civil Engineering"},
    {"che", "Chemical Engineering"},
    {"ece", "Electronics and Communication Engineering"},
    {"ei", "Electronics and Instrumentation Engineering"},
    {"bt", "Biotechnology"},
    {"pe", "Production Engineering"},
    {"math", "Mathematics"},
    {"phy", "Physics"},
    {"chem", "Chemistry"}
    

    };

    string input;

    while(true){
        cout<<"Enter branch code";
        cin>>input;

        if(m.find(input)!=m.end()){
            return input;
        }
        else{
            cout<<"Invalid!. TRY AGAIN";
        }
    }

}


string getHostel(){
    map<string,string> mpp{
        {"ARY", "Aryabhatta Hostel"},
        {"RNT"," Rabindranath Tagore Hostel"},
        {"GARGI"," Gargi Hostel"}
    };

    string input;

    while(true){
        cout<<"Enter Hostel code-->ARY,RNT,GARGI";
        cin>>input;
        if(mpp.find(input)!=mpp.end()){
            return input;
        }
        else{
            cout<<"Invalid! TRY AGAIN";
            }
    }
}


Student createID(){

    Student newStudent;

    cout<<" Enter name";
    cin.ignore();
    getline(cin, newStudent.name);

    cout<<"Enter ID";
    getline(cin, newStudent.id);

    cout<<"Enter branch name";
    newStudent.branch=getBranch();

    cout<<"Enter your current year";
    cin>>newStudent.year;

    newStudent.hostel=getHostel();

    cout<<"Enter club name(Just first and last letter)";
    getline(cin,newStudent.club);

    cout<<"Enter sport name(Just first and last letter)";
    getline(cin,newStudent.sport);

    return newStudent;

}


// GRAPH IMPLEMENTATION

struct Node{
    string id;
    vector<string> edges;
};

unordered_map<string,Node> graph;
unordered_map<string,Student> studentData;

void addEdges(const string& studentId, int year, const string& branch, const string & hostel, const string& club, const string& sport){

    string yearId="Y"+ to_string(year);
    if(graph.find(yearId)==graph.end()){
        graph[yearId]=Node{yearId,{}};
    }

    if(graph.find(branch)==graph.end()){
        graph[branch]=Node{branch,{}};
    }

    if(graph.find(hostel)==graph.end()){
        graph[hostel]=Node{hostel,{}};
    }

    if(graph.find(club)==graph.end()){
        graph[club]=Node{club,{}};
    }

    if(graph.find(sport)==graph.end()){
        graph[sport]=Node{sport,{}};
    }


    graph[studentId].edges.push_back(yearId);
    graph[studentId].edges.push_back(branch);
    graph[studentId].edges.push_back(hostel);
    graph[studentId].edges.push_back(sport);
    graph[studentId].edges.push_back(club);

    graph[yearId].edges.push_back(studentId);
    graph[branch].edges.push_back(studentId);
    graph[hostel].edges.push_back(studentId);
    graph[club].edges.push_back(studentId);
    graph[sport].edges.push_back(studentId);


}

void addStudent(const string& id, const string& name, int year, const string& branch, const string& hostel, const string& club, const string& sport) {
    
    studentData[id] = {name, id, branch, year, hostel, 0, club, sport};

    if (graph.find(id) == graph.end()) {
        graph[id] = Node{id, {}};
    }

    addEdges(id, year, branch, hostel, club, sport);
}


// main core

struct Connection{
    string studentId;
    double scoreA;
    double scoreB;
    double totalScore;
};

double calculateConnectionScore(const Student& student1, const Student& student2) {
    double score = 0;
    
    if (student1.branch == student2.branch) score += 0.8;
    if (student1.hostel == student2.hostel) score += 0.6;
    if (student1.year == student2.year) score += 0.5;
    if (student1.club == student2.club) score += 0.7;
    if (student1.sport == student2.sport) score += 0.7;
    
    return score;
}

vector<Connection> findConnections(const string& studentIdA,const string& studentIdB){
    vector<Connection> connection;

    if (studentData.find(studentIdA) == studentData.end() || studentData.find(studentIdB) == studentData.end()) {
        cout << "One or both student IDs not found!\n";
        return connection;
    }

    Student& studentA=studentData[studentIdA];
    Student& studentB=studentData[studentIdB];

    for(const auto& [id,student] : studentData){
        
        if(id!=studentIdA  && id!=studentIdB){
            double scoreA=calculateConnectionScore(studentA,student);
            double scoreB=calculateConnectionScore(studentB,student);

            if(scoreA>1.1  && scoreB>1.1){
                double totalScore=scoreA+scoreB;
                connection.push_back({id,scoreA,scoreB,totalScore});
            }
        }
    }

    sort(connection.begin(), connection.end(),
        [](const Connection& a,const Connection& b){return a.totalScore>b.totalScore;});

        if(connection.size()>30){
            connection.resize(30);
        }

        return connection;
}


int main() {
    // Seed for random number generation
    srand(static_cast<unsigned>(time(nullptr)));

    

    // Sample students
    vector<Student> students = {
        {"Zaid", "005", "ece", 4, "ARY", 50, "Chess", "Football"},
        {"Amit", "006", "cse", 3, "RNT", 60, "Football", "Basketball"},
        {"Bina", "007", "me", 2, "GARGI", 70, "Robotics", "Badminton"},
        {"Chad", "008", "ee", 1, "ARY", 80, "Basketball", "Cricket"},
        {"Dina", "009", "ce", 4, "RNT", 90, "Chess", "Football"},
        {"Ella", "010", "ece", 3, "GARGI", 85, "Football", "Cricket"},
        {"Frank", "011", "cse", 2, "ARY", 75, "Basketball", "Football"},
        {"Grace", "012", "me", 1, "RNT", 65, "Robotics", "Badminton"},
        {"Hank", "013", "ee", 4, "GARGI", 95, "Chess", "Basketball"},
        {"Ivy", "014", "ce", 3, "ARY", 55, "Football", "Cricket"}
    };

    
    for (const auto& student : students) {
        addStudent(student.id, student.name, student.year, student.branch, student.hostel, student.club, student.sport);
    }

    // Example to find connections between two students
    string studentIdA, studentIdB;

    cout << "Enter the ID of the first student: ";
    cin >> studentIdA;

    cout << "Enter the ID of the second student: ";
    cin >> studentIdB;

    vector<Connection> connections = findConnections(studentIdA, studentIdB);

    if (!connections.empty()) {
        cout << "Top connections between students " << studentIdA << " and " << studentIdB << ":\n";
        for (const auto& conn : connections) {
            cout << "Student ID: " << conn.studentId 
                 << ", Total Score: " << conn.totalScore << '\n';
        }
    } else {
        cout << "No significant connections found.\n";
    }

    return 0;
}




