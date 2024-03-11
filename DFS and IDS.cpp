#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <limits>

class Graph
{
public:
    struct Edge
    {
        int vertex, weight;

        Edge(int v, int w) : vertex(v), weight(w) {}

        friend std::ostream &operator<<(std::ostream &os, const Edge &edge)
        {
            return os << "(" << edge.vertex << "," << edge.weight << ")";
        }
    };

    Graph(int v) : V(v), adj(v) {}

    void addEdge(int v, int dest, int weight)
    {
        Edge e(dest, weight);
        adj[v].push_back(e);
    }

    void DFS(int s, int goal)
    {
        std::vector<bool> visited(V, false);
        std::stack<int> stack;
        std::stack<int> stack1;
        stack.push(s);
        stack1.push(0);
        int cost = 0, c;

        while (!stack.empty())
        {
            s = stack.top();
            c = stack1.top();
            stack.pop();
            stack1.pop();
            cost += c;

            if (!visited[s])
            {
                std::cout << s << " ";
                visited[s] = true;
            }

            if (s == goal)
                break;

            for (const auto &e : adj[s])
            {
                int v = e.vertex;
                if (!visited[v])
                {
                    stack.push(v);
                    stack1.push(e.weight);
                }
            }
        }
        std::cout << "\nPath cost: " << cost << std::endl;
    }

    // Iterative Deepening Search (IDS) Algorithm
    void IDS(int start, int goal)
    {
        int depth = 0;
        while (true)
        {
            std::vector<bool> visited(V, false);
            int cost = 0;
            if (DLS(start, goal, depth, visited, cost))
            {
                std::cout << "\nPath cost: " << cost << std::endl;
                return;
            }
            ++depth;
        }
    }

    bool DLS(int node, int goal, int depth, std::vector<bool> &visited, int &cost)
    {
        if (node == goal)
        {
            return true;
        }

        if (depth <= 0)
        {
            return false;
        }

        visited[node] = true;
        bool found = false;

        for (const auto &e : adj[node])
        {
            int v = e.vertex;
            int w = e.weight;
            if (!visited[v])
            {
                cost += w;
                found = DLS(v, goal, depth - 1, visited, cost);
                if (found)
                {
                    std::cout << node << " ";
                    break;
                }
                cost -= w;
            }
        }

        visited[node] = false;
        return found;
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        for (int i = 0; i < graph.adj.size(); ++i)
        {
            os << i << "=>";
            for (const auto &edge : graph.adj[i])
            {
                os << edge << " ";
            }
            os << "\n";
        }
        return os;
    }

private:
    int V;
    std::vector<std::list<Edge>> adj;
};

int main()
{
    Graph RomaniaMap(20);

    // Add edges
    RomaniaMap.addEdge(0, 1, 118);
    RomaniaMap.addEdge(0, 2, 140);
    RomaniaMap.addEdge(0, 3, 75);
    RomaniaMap.addEdge(1, 0, 118);
    RomaniaMap.addEdge(1, 4, 111);
    RomaniaMap.addEdge(2, 0, 140);
    RomaniaMap.addEdge(2, 5, 80);
    RomaniaMap.addEdge(2, 6, 99);
    RomaniaMap.addEdge(2, 7, 151);
    RomaniaMap.addEdge(3, 0, 75);
    RomaniaMap.addEdge(3, 7, 71);
    RomaniaMap.addEdge(4, 1, 111);
    RomaniaMap.addEdge(4, 8, 70);
    RomaniaMap.addEdge(5, 2, 80);
    RomaniaMap.addEdge(5, 9, 146);
    RomaniaMap.addEdge(5, 10, 97);
    RomaniaMap.addEdge(6, 2, 99);
    RomaniaMap.addEdge(6, 11, 211);
    RomaniaMap.addEdge(7, 3, 71);
    RomaniaMap.addEdge(7, 2, 151);
    RomaniaMap.addEdge(8, 4, 70);
    RomaniaMap.addEdge(8, 12, 75);
    RomaniaMap.addEdge(9, 12, 120);
    RomaniaMap.addEdge(9, 10, 138);
    RomaniaMap.addEdge(9, 5, 146);
    RomaniaMap.addEdge(10, 9, 138);
    RomaniaMap.addEdge(10, 11, 101);
    RomaniaMap.addEdge(10, 5, 97);
    RomaniaMap.addEdge(11, 10, 101);
    RomaniaMap.addEdge(11, 6, 211);
    RomaniaMap.addEdge(11, 13, 90);
    RomaniaMap.addEdge(11, 14, 85);
    RomaniaMap.addEdge(12, 8, 75);
    RomaniaMap.addEdge(12, 9, 120);
    RomaniaMap.addEdge(13, 11, 90);
    RomaniaMap.addEdge(14, 11, 85);
    RomaniaMap.addEdge(14, 15, 98);
    RomaniaMap.addEdge(14, 17, 142);
    RomaniaMap.addEdge(15, 14, 98);
    RomaniaMap.addEdge(15, 16, 86);
    RomaniaMap.addEdge(16, 15, 86);
    RomaniaMap.addEdge(17, 14, 142);
    RomaniaMap.addEdge(17, 18, 92);
    RomaniaMap.addEdge(18, 17, 92);
    RomaniaMap.addEdge(18, 19, 87);
    RomaniaMap.addEdge(19, 18, 87);

    std::cout << "ROMANIA MAP ADJACENCY LIST:\n";
    std::cout << RomaniaMap;

    std::cout << "\nEnter the starting state (0-19): ";
    int start;
    std::cin >> start;

    std::cout << "Enter the goal state (0-19): ";
    int goal;
    std::cin >> goal;

    std::cout << "\nFollowing is Depth First Traversal "
              << "\n(starting from vertex " << start << " to reach goal i.e. vertex " << goal << ")" << std::endl;

    RomaniaMap.DFS(start, goal);

    std::cout << "\nFollowing is Iterative Deepening Search Traversal "
              << "\n(starting from vertex " << start << " to reach goal i.e. vertex " << goal << ")" << std::endl;

    RomaniaMap.IDS(start, goal);

    return 0;
}
