/*
You have a business with several offices; you want to lease phone lines to
connect them up with each other; and the phone company charges different
amounts of money to connect different pairs of cities. You want a set of lines that
connects all your offices with a minimum total cost. Solve the problem by
suggesting appropriate data structures.
*/
// ================================================================================================================

# include <iostream>
# include <climits>
using namespace std;

template <class T>
class Graph{
        int V;              // number of vertices
        int** adjMatrix;    // adjacency matrix
    public:
    // default constructor
        Graph(){
            V = 0;
            adjMatrix = NULL;
        }

    // parameterized constructor
        Graph(int v){                         
            this->V = v;
            adjMatrix = new int*[v];        // allocating memory for 2D array
            for(int i=0; i<v; ++i){
                adjMatrix[i] = new int[v];  // allocating memory for rows
                for(int j=0; j<v; ++j){
                    adjMatrix[i][j] = 0;    // initializing all values to 0 - no edge is present
                }
            }
        }

    // setter 
        void set_v(int v){
            this->V = v;

            adjMatrix = new int*[v];        // allocating memory for 2D array
            for(int i=0; i<v; ++i){
                adjMatrix[i] = new int[v];  // allocating memory for rows
                for(int j=0; j<v; ++j){
                    adjMatrix[i][j] = 0;    // initializing all values to 0 - no edge is present
                }
            }
        }

    // methods
        void add_edge(T u, T v, int wt);    // add edge between vertices u and v
        void display();                     // display the adjacency matrix 
        void prims_mst();                   // find minimum spanning tree using Prim's algorithm
        void kruskals_mst();                // find minimum spanning tree using Kruskal's algorithm
};

// Utility Functions ======================================================================

// To find the index of minimum key in the key array
int min_key(int V, int* key, bool* mstSet){
    // Initialize min value
    int min = INT_MAX;
    int minIndex = 0;

    // loop through all vertices and find the minimum key
    for (int v=0; v<V; ++v){
        if (mstSet[v] == false && key[v] < min){
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// To print the MST
void print_mst(int V, int* parent, int** weights){
    cout << "\nEdge \tWeight\n";
    for (int i=1; i<V; ++i){
        // parent[i] - starting vertex
        // i - ending vertex
        // weights[i][parent[i]] - weight of the edge
        cout << parent[i] << " - " << i << "\t" << weights[i][parent[i]] << endl;
    }
}


// Menu Driven Driver code ================================================================
int main(){
    Graph<int> G;
	int choice = -1;
	int temp = 0;

	cout << "# Algorithms for Minimum Spanning Tree\n";
	while(choice){
		cout << "\n---------- MENU ----------\n"
			 << "1. Create graph\n"
			 << "2. Accept Edges (Telephone Lines)\n"
			 << "3. Display graph (Adjacency Matrix)\n"
			 << "4. MST by Prim's Algorithm\n"
			 << "5. MST by Kruskal's Algorithm\n"
			 << "0. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch(choice){
		case 1: // Create graph
		{
			int v=0;
			cout << "Enter no. of Vertices = ";
			cin >> v;
			G.set_v(v);
			break;
		}

		case 2: // Accept Edges (Telephone Lines)
		{
            cout << "Enter no. of Edges = ";
            cin >> temp;
            int u, v, wt;
            cout << "Enter edges (u, v, wt) = " << endl;
            for(int i=0; i<temp; ++i){
                cout << "Enter edge " << i+1 << " = ";
                cin >> u >> v >> wt;
                G.add_edge(u, v, wt);
            }
			break;
		}

		case 3: //  Display graph (Adjacency Matrix)
		{
            cout << "Adjacency Matrix = " << endl;
			G.display();
			break;
		}

		case 4: //  MST by Prim's Algorithm
        {
            cout << "MST by Prim's Algorithm = " << endl;
            G.prims_mst();
            break;
        }

		case 5: //  MST by Kruskal's Algorithm
        {
            cout << "MST by Kruskal's Algorithm = " << endl;
            G.kruskals_mst();
            break;
        }

		case 0: // Exit
		{
			cout << "Thank you :)" << endl;
			break;
		}

		default : // Forced exit
		{
			cout << "# Forced exit due to error" << endl;
			exit(0);
		}
		}
	}

    return 0;
}

// Definitions of methods of Graph class ============================================================

template <class T>
void Graph<T>::add_edge(T u, T v, int wt){
    while(true){
        try {
            if(u<0 || u>=this->V|| v<0 || v>=this->V){
                throw 1;
            }
            adjMatrix[u][v] = wt;
            adjMatrix[v][u] = wt;
            return;
        } catch (int error){
            cout << "# Error : Vertex out of range" << endl;
            cout << "# Enter again : ";
            cin >> u >> v >> wt;
        }
    }
}

template <class T>
void Graph<T>::display(){
    cout << "   \t";
    for(int i=0; i<V; ++i){
        cout << i << "| \t";
    }
    cout << endl;
    for(int i=0; i<V; ++i){
        cout << i << "| \t";
        for(int j=0; j<V; ++j){
            cout << adjMatrix[i][j] << "  \t";
        }
        cout << endl;
    }
}

template <class T>
void Graph<T>::prims_mst(){
    // Array to store constructed MST
    int parent[V];
    // Keys used to pick minimum weight edge in cut
    int key[V];
    // To represent set of vertices included in MST
    bool mstSet[V];

    // initialize all keys as INFINITE and mstSet[] as false
    for(int i=0; i<V; ++i){
        key[i] = INT_MAX;       
        mstSet[i] = false;      
    }

    // to include 0th vertex in MST first, 
    // make its key 0 so that it is picked first
    key[0] = 0;

    // mark first node of mst as root
    parent[0] = -1;

    // repeat till all vertices are included in MST
    for (int i=0; i<V; ++i){
        // pick the adjacent unpicked vertex with minimum key
        int u = min_key(V, key, mstSet);

        // add the picked vertex to MST
        mstSet[u] = true;

        // update key and parent index of adjacent vertices of the picked vertex
        for (int v=0; v<V; ++v){
            // update key[v] only if:
            // 1. v is not in mstSet, 
            // 2. there is an edge from u to v,
            // 3. weight of edge u-v is smaller than current value of key[v]
            if (mstSet[v] == false && adjMatrix[u][v] > 0 && adjMatrix[u][v] < key[v]){
                parent[v] = u;              // update parent index of v to u
                key[v] = adjMatrix[u][v];   // update key value of v to its edge weight
            }
        }
    }

    // print the constructed MST
    print_mst(V, parent, this->adjMatrix);
}

template <class T>
void Graph<T>::kruskals_mst(){
    return;
}