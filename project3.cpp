// DABBAWALA ALGORITHM

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<queue>

using namespace std;

struct Node{
    string name;
    vector<string> neighbors;
};

unordered_map<string,Node> graph;

void addNode(const string& nodeName){
    if(graph.find(nodeName)==graph.end()){
        graph[nodeName]= Node{nodeName,{}};
    }
}

void addEdge(const string& fromNode, const string& toNode ){
    graph[fromNode].neighbors.push_back(toNode);
}

// addding nodes to graph

void graphNodes(){

// 3 AREAS
    vector<string> localareas={"Area21","Area22","Area23"};
// 6 TRIANLINES
    vector<string> trainlines={"trainUA","trainUB","trainPA","trainPB","trainPH","trainPD"};
//12 STATIONS
    vector<string> stations={"stationMA","stationCY","stationPH","stationAB","stationCD","stationDE","stationEF","stationFG","stationGH","stationHI","stationJK","stationLM"};
 //24 BUILDINGS   
    vector<string> building={"building01","building02","building03","building04","building05","building06","building07","building08","building09","building10","building11","building12","building13","building14","building15","building16","building17","building18","building19","building20","building21","building22","building23","building24"};

    for(auto it : localareas){
        addNode(it);
    }


    for(auto it : trainlines){
        addNode(it);
    }

    for(auto it : stations){
        addNode(it);
    }
     
    for(auto it : building){
        addNode(it);
    }

//Area to train
    addEdge("Area21","trainUA");
    addEdge("Area21","trainUB");
    addEdge("Area21","trainPH");
    addEdge("Area22","trainPA");
    addEdge("Area22","trainPB");
    addEdge("Area23","trainPD");

  // TRAIN TO STATIONS
  addEdge("trainUA","stationMA");
  addEdge("trainUA","stationCY");
  addEdge("trainUA","stationPH");
  addEdge("trainPH","stationAB");
  addEdge("trainUB","stationCD");
  addEdge("trainUB","stationDE");
  addEdge("trainPH","stationEF");
  addEdge("trainUA","stationFG");
  addEdge("trainPA","stationGH");
  addEdge("trainPB","stationHI");
  addEdge("trainPB","stationJK");
  addEdge("trainPD","stationLM");

  // STATIONS TO BUILDINGS
  addEdge("stationMA","buiding01");
  addEdge("stationMA","buiding02"); 
  addEdge("stationMA","buiding03");
  addEdge("stationMA","buiding04"); 
  addEdge("stationMA","buiding05");
  addEdge("stationCY","buiding06"); 
  addEdge("stationCY","buiding07");
  addEdge("stationCY","buiding08");
  addEdge("stationCY","buiding09"); 
  addEdge("stationLM","buiding10");
  addEdge("stationLM","buiding11"); 
  addEdge("stationLM","buiding12");
  addEdge("stationJK","buiding13"); 
  addEdge("stationJK","buiding14");
  addEdge("stationJK","buiding15"); 
  addEdge("stationHI","buiding16");
  addEdge("stationHI","buiding17"); 
  addEdge("stationGH","buiding18");
  addEdge("stationGH","buiding19"); 
  addEdge("stationFG","buiding20");
  addEdge("stationPH","buiding21"); 
  addEdge("stationAB","buiding22");
  addEdge("stationCD","buiding23");
  addEdge("stationDE","buiding24"); 

}

// the  main logic of code, to traversea and sort

vector<string> traverseGraph(const string& code){
    vector<string> path;

    string areacode=code.substr(0,2);
    string traincode=code.substr(2,2);
    string stationcode=code.substr(4,2);
    string buildingcode=code.substr(6,2);
    string floorcode=code.substr(8,1);


    string currentnode="Area"+areacode;
    path.push_back(currentnode);

    auto sortandTraverse=[&](const string& nextcodeSegment){
        if(graph.find(currentnode)==graph.end()){
            cout<<"Error: Node"<<currentnode<<"not found in graph";
            return false;
        }

        vector<string> sortedNeighbors=graph[currentnode].neighbors;
        sort(sortedNeighbours.begin(),sortedNeighbours.end(), [&](const string& a, const string& b){
            return a.substr(a.size()-2)<b.substr(b.size()-2);
        });


        for(const auto& neighbor: sortedNeighbors){
            if(neighbor.find(nextcodeSegment)!= strin::npos){
                currentnode=neighbor;
                path.push_back(currentnode);
                return true;
            }
        }

        coutt<<"Error : No matching node for code segemnt"<<nextcodeSegment<<endl;
        return false;
    };

    if(!sortandTraverse(traincode)) return {};

    if(!sortandTraverse(stationcode)) return {};

    if(!sortandTraverse(buildingcode)) return {};

    path.push_back("Floor"+ floorcode);

    return path;

}


int main() {
    // Initialize the graph with nodes and edges
    graphNodes();

    // Example input code
    string code = "22UAMA016";

    // Traverse the graph based on the input code
    vector<string> path = traverseGraph(code);

    // Output the traversal path
    if (!path.empty()) {
        cout << "Traversal path: ";
        for (const string& node : path) {
            cout << node << " -> ";
        }
        cout << "End" << endl;
    } else {
        cout << "Error: Could not complete the traversal." << endl;
    }

    return 0;
}