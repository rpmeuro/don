#include<iostream>
#include<omp.h>
#include<vector>
#include<stack>

using namespace std;

const int MAX = 10000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int start) {
        stack<int> s;
        s.push(start);

        while(!s.empty()) {
                int node = s.top();
                s.pop();

                if(visited[node]) continue;

                visited[node] = true;
                cout<<node<<" ";

                #pragma critical parallel for
                for(int i=0;i<graph[node].size();i++) {
                        int adj = graph[node][i];
                        if(!visited[adj]) {
                                #pragma omp critical
                                s.push(adj);
                        }
                }
        }
}

int main() {
        int m,n,start;
        cout<<"Enter number of nodes, edges and starting node :\n";
        cin >> n>>m>>start;
        cout<<"Enter edges(u,v): \n";
        for(int i=0;i<m;i++) {
                int u,v;
                cin>>u>>v;

                graph[u].push_back(v);
                graph[v].push_back(u);
        }

        #pragma omp parallel for
        for(int i=0;i<n;i++) {
                visited[i] = false;
        }

        cout<<"DFS Traversal : \n";
        dfs(start);
        return 0;
}
