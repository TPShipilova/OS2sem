#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
    vector<int> heirs;
    bool busy = false;
    string job = "not job";
};
typedef int (*FnPtr)();
map<int, Node> graph;
map<string, FnPtr> myF;  

bool is_node_Cyclic(int v, bool visited[], bool in_rec_stack[]) {
    if (!visited[v]) {
        visited[v] = true;
        in_rec_stack[v] = true;

        for (int i = 0; i < graph[v].heirs.size(); i++) {
            int n = graph[v].heirs[i];
            if (!visited[n] && is_node_Cyclic(n, visited, in_rec_stack)) {
                return true;
            } else 
            if (in_rec_stack[n]) {
                return true;
            }
        }

    }
    in_rec_stack[v] = false;
    return false;
}

bool is_Cyclic() {
    bool *visited = new bool[graph.size()];
    bool *in_rec_stack = new bool[graph.size()];
    for (int i = 0; i < graph.size(); i++) {
        visited[i] = false;
        in_rec_stack[i] = false;
    }

    for (int i = 0; i < graph.size(); i++) {
        if (is_node_Cyclic(i, visited, in_rec_stack)) {
            return true;
        }
    }
    return false;
}

bool is_Connected(std::vector<int>& endnods) {
    int count_out;
    int id_node;
    bool found;
    for (auto & pair : graph) {
        id_node = pair.first; 
        count_out = pair.second.heirs.size();
        found = std::find(endnods.begin(), endnods.end(), id_node) != endnods.end();
        if (count_out > 1 && found == false)
            return false;
    }
    return true;
}


int FIRST() { return 1; }
int SECOND() { return 10; }
int THIRD() { return 11; }
int FORTH() { 
    int i; 
    cout << "Введите число: "; 
    cin >> i; 
    if(i == -1) 
        return -1; 
    else 
        return i;
    }
int FIFTH() { return 101; }
int SIXTH() { return 110; }

typedef int (*FnPtr)();



void all_job(std::vector<int>& startNodes){
    queue<int> queue;
    int id_job_node, id_job_node_next, size;
    Node *job_node;
    string job;
    Node *next_job_node;
    int res;
    for (int i = 0; i < startNodes.size(); i++){
        queue.push(startNodes[i]);
    }
    for (int i = 0; i < graph.size() - 1 ; i++){
        id_job_node = queue.front();
        cout << "JOB: " << id_job_node << endl;
        queue.pop();
        job_node = &(graph.find(id_job_node) -> second);
        job = job_node->job;
        if(job != "not job"){
            res = myF[job]();
            if (res == -1){
                cout << "error" << endl;
                break;
            }
            cout << res << endl;
        }
        else{
            cout << job << endl;
        }
        job_node->busy = true;
        size = job_node->heirs.size();
        if(size != 0){
            id_job_node_next = job_node->heirs.front();
            next_job_node = &(graph.find(id_job_node_next) -> second);
            if(next_job_node->busy == false){
                next_job_node->busy = true;
                queue.push(id_job_node_next);
            }
        }
    }
        
}