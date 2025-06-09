const int N = 100;  // Adjust as needed for the maximum number of nodes
vector<int> g[N];   // Adjacency list representation of the graph
// Variables for Tarjan's Algorithm
vector<int> low, disc;
vector<bool> inStack;
stack<int> s;
int timeCounter = 0;  // Used to assign discovery times
// Function to perform DFS and find SCCs
void tarjanSCC(int node, vector<vector<int>>& stronglyConnectedComponents) {
  // Initialize discovery time and low value
  disc[node] = low[node] = ++timeCounter;
  s.push(node);
  inStack[node] = true;
  // Explore all adjacent nodes
  for (int neighbor : g[node]) {
    if (disc[neighbor] == -1) {  // If neighbor hasn't been visited
      tarjanSCC(neighbor, stronglyConnectedComponents);
      low[node] = min(low[node], low[neighbor]);   // Update low value
    } else if (inStack[neighbor]) {                // If neighbor is in stack, it's part of the current SCC
      low[node] = min(low[node], disc[neighbor]);  // Update low value
    }
  }
  // If the node is a root node, pop the stack and generate an SCC 
  if (low[node] == disc[node]) {
    vector<int> component;
    while (s.top() != node) {
      component.push_back(s.top());
      inStack[s.top()] = false;  // Mark as not in stack
      s.pop();
    }
    component.push_back(s.top());  // Add the root node
    inStack[s.top()] = false;      // Mark as not in stack
    s.pop();
    stronglyConnectedComponents.push_back(component);  // Add the component to the list
  }
}
int main() {
  int edges, u, v;
  cout << "Enter number of edges: ";
  cin >> edges;
  // Initialize graph and variables
  for (int i = 0; i < edges; i++) {
    cout << "Enter edge (u v): ";
    cin >> u >> v;
    g[u].push_back(v);  // Add edge from u to v
  }
  // Prepare data structures
  low.assign(N, -1);                                // Low values
  disc.assign(N, -1);                               // Discovery times
  inStack.assign(N, false);                         // To track nodes in the stack
  vector<vector<int>> stronglyConnectedComponents;  // To store all SCCs
  // Call Tarjan's algorithm for each node
  for (int i = 1; i <= N; ++i) {              // Adjust the range based on the number of nodes
    if (disc[i] == -1 && g[i].size() != 0) {  // If the node hasn't been visited
      tarjanSCC(i, stronglyConnectedComponents);
    }
  }
  // Output the strongly connected components
  cout << "Strongly Connected Components:" << endl;
  for (const auto& component : stronglyConnectedComponents) {
    cout << "Component: ";
    for (int node : component) {
      cout << node << " ";  // Print each node in the component
    }
    cout << endl;  // New line for each component
  }
  return 0;
}
