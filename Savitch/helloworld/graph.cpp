#include <iostream>
#include <vector>

using namespace std;

class Graph
{
public:
    Graph()
    {
        size = 1;
        edges = {};
    }
    Graph(int num_nodes, vector<vector<int>> distances)
    {
        size = num_nodes;
        edges = distances;
    }
    int get_number_vertices()
    {
        return size;
    }
    void add_vertex(vector<int> newone)
    {
        if (newone.size() == size + 1)
        {
            edges.push_back(newone);
        }
        size++;
    }
    vector<int> get_neighbors(int vertex)
    {
        vector<int> results;
        for (int i = 0; i < size; i++)
        {
            if (i != vertex && edges[vertex][i] != 0)
            {
                results.push_back(i);
            }
        }
        return results;
    }
    int get_distance(int a, int b)
    {
        if(a == b)
        {
            return 0;
        }
        else
        {
            int tentative = edges[a][b];
            if(tentative == 0)
            {
                exit(1);
            }
            else
            {
                return tentative;
            }
            
        }
        
    }
    int get_closest_neighbor(int vertex)
    {
        vector<int> neighborhood = get_neighbors(vertex);
        int closest = neighborhood[0];
        for (int neighbor : neighborhood)
        {
            if (edges[vertex][neighbor] < edges[vertex][closest])
            {
                closest = neighbor;
            }
        }
        return closest;
    }
    bool broken()
    {
        bool broken = false;
        if (size == edges.size())
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (edges[j][i] != edges[i][j])
                    {
                        broken = true;
                    }
                }
            }
        }
        else
        {
            broken = true;
        }
        return broken;
    }
    vector<int> quickest_path(int origin, int destination)
    {
        int distances[size];
        vector<int> visited;

        for (int i = 0; i < size; i++)
        {
            distances[i] = INT16_MAX;
            visited[i] = false;
        }
        distances[origin] = 0;

        int current = origin;
        
        for(int reached=1;reached < size;reached++)
        {
            vector<int> neighborhood = get_neighbors(current);
            int closest_unvisited = neighborhood[0];
            for (int neighbor : neighborhood)
            {
                if (!visited[neighbor])
                {
                    if(edges[current][closest_unvisited] > edges[current][neighbor] || visited[closest_unvisited])
                    {
                        closest_unvisited = neighbor;
                    }
                    if(distances[neighbor] == INT16_MAX)
                    {
                        distances[neighbor] = edges[current][neighbor];
                    }
                    int alt = distances[current] + edges[current][neighbor];
                    if(alt < distances[neighbor])
                    {
                        distances[neighbor] = alt;
                    }
                }
            }
            visited[current] = true;
            current = closest_unvisited;
        }
        cout << distances[3];
        vector<int> x;
        return x;
    }
    static void print_edges(vector<int> list)
    {
        for (int each : list)
        {
            cout << each << " ";
        }
        cout << endl;
    }
    friend ostream &operator<<(ostream &out, Graph &g)
    {
        out << "This is a graph with " << g.size << " vertices." << endl;
        for (int i = 0; i < g.size; i++)
        {
            out << "Vertex " << i << " is connected with ";
            print_edges(g.get_neighbors(i));
        }
        return out;
    }

private:
    int size;
    std::vector<std::vector<int>> edges;
};

int main()
{
    vector<vector<int>> distances{{0, 7, 9, 0, 0, 14}, {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2}, {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9}, {14, 0, 2, 0, 9, 0}};
    Graph g = Graph(6, distances);
    g.quickest_path(0, 4);
    //cout << g.distance(0, 1);
}