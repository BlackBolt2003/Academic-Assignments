// Sequencial and Parallel BFS and DFS

/*
Design and implement Parallel Breadth First Search and Depth First Search based on 
existing algorithms using OpenMP. Use a Tree or an undirected graph for BFS and DFS .  
Measure the performance of sequential and parallel algorithms. 

*/

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void generateLargeGraph(int V, int E_per_node, vector<int> adj[])
{
    srand(time(NULL));

    // Step 1: Ensure connectivity with a chain
    for (int i = 0; i < V - 1; i++)
    {
        adj[i].push_back(i + 1);
        adj[i + 1].push_back(i);
    }

    // Step 2: Add random edges
    for (int i = 0; i < V; i++)
    {
        unordered_set<int> added(adj[i].begin(), adj[i].end());

        while (adj[i].size() < E_per_node)
        {
            int neighbor = rand() % V;
            if (neighbor != i && !added.count(neighbor))
            {
                adj[i].push_back(neighbor);
                adj[neighbor].push_back(i);
                added.insert(neighbor);
            }
        }
    }
}

void BFS_sequencial(int start, int V, vector<int> adj[])
{
    queue<int> q;
    vector<bool> visited(V, false);

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        printf("%d ", node);

        for (int neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void BFS_parallel(int start, int V, vector<int> adj[])
{
    queue<int> q;
    vector<bool> visited(V, false);

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
            int node = q.front();
            q.pop();
            printf("%d ", node);
        

        #pragma omp parallel for
        for (int neighbor : adj[node])
        {
            // Prevent data races on visited[]
            // #pragma omp critical
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
        
    }
}

void DFS_sequencial_util(int node, vector<bool> &visited, vector<int> adj[])
{
    visited[node] = true;
    printf("%d ", node);

    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
            DFS_sequencial_util(neighbor, visited, adj);
    }
}

void DFS_sequencial(int start, int V, vector<int> adj[])
{
    vector<bool> visited(V, false);
    DFS_sequencial_util(start, visited, adj);
}

void DFS_parallel_util(int node, vector<int> &visited, vector<int> adj[])
{
    visited[node] = 1;
    printf("%d ", node);

    #pragma omp parallel for
    for (int neighbor : adj[node])
    {        
        if (!visited[neighbor])
        {
            DFS_parallel_util(neighbor, visited, adj);
        }  
    }
}

void DFS_parallel(int start, int V, vector<int> adj[])
{
    vector<int> visited(V, 0);
    DFS_parallel_util(start, visited, adj);
}

int main()
{
    // Sample Graph

    int V = 6;
    vector<int> *adj = new vector<int>[V];
    
    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0, 5};
    adj[3] = {1};
    adj[4] = {1, 5};
    adj[5] = {2, 4};

    // Large Graph
    
    // int V = 100;
    // int E_per_node = 6;
    // vector<int> *adj = new vector<int>[V];
    
    // generateLargeGraph(V, E_per_node, adj);
    
    
    double t1, t2;

    // BFS
    printf("\nSequencial BFS: ");
    t1 = omp_get_wtime();
    BFS_sequencial(0, V, adj);
    t2 = omp_get_wtime();
    printf("\nSequencial BFS Time: %lf\n", t2 - t1);

    printf("\nParallel BFS: ");
    t1 = omp_get_wtime();
    BFS_parallel(0, V, adj);
    t2 = omp_get_wtime();
    printf("\nParallel BFS Time: %lf\n", t2 - t1);

    // DFS
    printf("\nSequencial DFS: ");
    t1 = omp_get_wtime();
    DFS_sequencial(0, V, adj);
    t2 = omp_get_wtime();
    printf("\nSequencial DFS Time: %lf\n", t2 - t1);

    printf("\nParallel DFS: ");
    t1 = omp_get_wtime();
    DFS_parallel(0, V, adj);
    t2 = omp_get_wtime();
    printf("\nParallel DFS Time: %lf\n", t2 - t1);

    return 0;
}