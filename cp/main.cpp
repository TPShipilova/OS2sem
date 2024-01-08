#include <iostream>
#include <fstream>
#include "dag.hpp"

using namespace std;

int main() {
    ifstream configFile("conf.ini");
    vector<int> startNodes;
    vector<int> endNodes;
    Node *job_node_now;
    int ID;
    string line;
    myF["FIRST"] = FIRST;
    myF["SECOND"] = SECOND;
    myF["THIRD"] = THIRD;
    myF["FORTH"] = FORTH;
    myF["FIFTH"] = FIFTH;
    myF["SIXTH"] = SIXTH;
    while (getline(configFile, line)) {
        if (line.find('=') != string::npos) {
            istringstream is(line);
            string key, value;
            if (getline(is, key, '=') && getline(is, value)) {
                if (key == "NODE") {
                    Node node;
                    ID = stoi(value);
                    graph[stoi(value)] = node;
                } else 
                if (key == "CONNECTION") {
                    int from, to;
                    istringstream(value) >> from >> to;
                    graph[from].heirs.push_back(to);
                } else 
                if (key == "START_NODE") {
                    startNodes.push_back(stoi(value));
                } else 
                if (key == "END_NODE") {
                    endNodes.push_back(stoi(value));
                } else 
                if (key == "JOB") {
                    job_node_now = &(graph.find(ID) -> second);
                    job_node_now->job = value;
                }
            }
        }
    }
    configFile.close();
    if (!is_Connected(endNodes)) {
        cout << "Граф не связан или пересвязан" << endl;
        return 1;
        }
    if (is_Cyclic()) {
        cout << "Граф содержит циклы" << endl;
        return 1;
        }
    if (startNodes.empty() || endNodes.empty()) {
        cout << "Отсутствуют стартовые или завершающие узлы" << endl;   
        return 1;
        }
    all_job(startNodes);
    return 0;
}