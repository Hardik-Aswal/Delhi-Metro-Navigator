#include <iostream>
#include <vector>
#include <limits.h>
#include <iomanip>
#include <string>

using namespace std;

const int V = 45; // Total number of metro stations (adjust according to actual number)
vector<string> metro_lst(V); // List of metro station names
vector<int> metro_no(V);     // List of metro station numbers

// Function to calculate and display the metro fare based on distance
void metro_fare(double dis) {
    cout << "Expected Metro Fare (Weekdays except Sunday) would be: Rs. ";
    if (dis <= 2.0) {
        cout << fixed << setprecision(1) << 10.0 << endl;
    } else if (dis > 2.0 && dis <= 5.0) {
        cout << fixed << setprecision(1) << 20.0 << endl;
    } else if (dis > 5.0 && dis <= 12.0) {
        cout << fixed << setprecision(1) << 30.0 << endl;
    } else if (dis > 12.0 && dis <= 21.0) {
        cout << fixed << setprecision(1) << 40.0 << endl;
    } else if (dis > 21.0 && dis <= 32.0) {
        cout << fixed << setprecision(1) << 50.0 << endl;
    } else if (dis > 32.0) {
        cout << fixed << setprecision(1) << 60.0 << endl;
    } else {
        cout << "Not Known" << endl;
    }
}

// Function to find the station with the minimum distance
int minDistance(vector<double>& dist, vector<bool>& sptSet) {
    double min = 1000.0; // Large value as the initial minimum
    int min_index = -1;

    // Loop to find the station with the minimum distance
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Recursive function to print the shortest path
void printPath(vector<int>& parent, int j, int src, vector<int>& cnt) {
    if (parent[j] == -1) {
        return;
    }

    printPath(parent, parent[j], src, cnt); // Recursively print the path
    cnt.push_back(metro_no[j]);
    cout << " -->> " << metro_lst[metro_no[j]] << endl;
}

// Function to print the final solution
void printSolution(vector<double>& dist, int src, vector<int>& parent, int dest, vector<int>& cnt) {
    // Print the distance between two stations
    cout << "Distance between two stations is: " << fixed << setprecision(1) << dist[dest] << " km " << endl;
    metro_fare(dist[dest]); // Calculate and display the metro fare

    cout << metro_lst[metro_no[src]]; // Print the source station
    cnt.push_back(metro_no[src]);
    printPath(parent, dest, src, cnt); // Print the path to the destination
}

// Dijkstra's algorithm to find the shortest path between stations
void dijkstra(vector<vector<double>>& graph, int src, int dest, vector<int>& cnt) {
    vector<double> dist(V, 1000.0); // Initialize all distances to a large value
    vector<bool> sptSet(V, false);  // Track visited stations
    vector<int> parent(V, -1);      // Parent array to store the shortest path

    dist[src] = 0.0; // Distance to the source is 0

    // Loop through all stations to find the shortest path
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // Get the station with minimum distance
        if (u == -1) break; // If no minimum distance found, break the loop
        sptSet[u] = true; // Mark the station as visited

        // Update distance of adjacent stations
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u; // Update parent of the station
                dist[v] = dist[u] + graph[u][v]; // Update distance
            }
        }
    }

    printSolution(dist, src, parent, dest, cnt); // Print the final solution
}

int main() {
    // Example metro lines and distances
    vector<string> yellow_line = {
        "Samaypur Badli", "Rohini Sector 18,19", "Haiderpur Badli Mor", "Jahangirpuri", 
        "Adarsh Nagar", "Azadpur", "Model Town", "GTB Nagar", "Vishwavidyalaya", 
        "Vidhan Sabha", "Civil Lines", "Kashmere Gate", "Chandni Chowk", "Chawri Bazar", 
        "New Delhi", "Rajiv Chowk", "Patel Chowk", "Central Secretariat", "Udyog Bhawan", 
        "Lok Kalyan Marg", "Jorbagh", "INA", "AIIMS", "Green Park", "Hauz Khas", "Malviya Nagar",
        "Saket", "Qutab Minar", "Chhatarpur", "Sultanpur", "Ghitorni", "Arjangarh", 
        "Guru Dronacharya", "Sikandarpur", "MG Road", "IFFCO Chowk", "Huda City Centre"
    };
    
    vector<double> yl = {
        0.0, 0.8, 1.3, 1.3, 1.7, 1.3, 1.6, 1.5, 1.5, 1.3, 1.4, 1.8, 1.6, 1.0, 
        1.5, 1.0, 1.0, 1.1, 0.8, 1.1, 1.0, 0.8, 1.1, 1.3, 1.4, 1.2, 1.1, 1.2, 
        1.4, 1.3, 1.5, 1.3, 1.0, 0.8, 1.1, 1.5, 1.0
    };

    vector<string> red_line = {
        "Dilshad Garden", "Jhil Mil", "Mansarovar Park", "Shahdara", "Welcome", 
        "Seelampur", "Shastri Park", "Kashmere Gate", "Tis Hazari", "Pul Bangash", 
        "Pratap Nagar", "Shastri Nagar", "Inderlok", "Kanhaiya Nagar", "Keshav Puram", 
        "Netaji Subhash Place", "Kohat Enclave", "Pitampura", "Rohini East", "Rohini West", 
        "Rithala"
    };

    vector<double> rl = {
        0.0, 0.9, 1.1, 1.1, 1.2, 1.3, 1.3, 2.5, 1.5, 1.1, 1.1, 1.3, 1.4, 1.1, 
        1.0, 1.2, 1.4, 1.3, 1.1, 1.2, 1.1
    };

    // Initialize graph (adjacency matrix) for Yellow and Red lines
    vector<vector<double>> graph(V, vector<double>(V, 0));

    // Populate the graph with distances for Yellow Line
    for (size_t i = 0; i < yellow_line.size() - 1; i++) {
        graph[i][i + 1] = yl[i + 1];
        graph[i + 1][i] = yl[i + 1]; // Undirected graph, bidirectional
        metro_lst[i] = yellow_line[i];
        metro_no[i] = i;
    }

    // Populate the graph with distances for Red Line
    int offset = yellow_line.size();
    for (size_t i = 0; i < red_line.size() - 1; i++) {
        graph[offset + i][offset + i + 1] = rl[i + 1];
        graph[offset + i + 1][offset + i] = rl[i + 1]; // Undirected graph
        metro_lst[offset + i] = red_line[i];
        metro_no[offset + i] = offset + i;
    }

    vector<int> cnt; // To store the path
    int source = 0; // Example source (Samaypur Badli)
    int destination = 10; // Example destination (Civil Lines)
    dijkstra(graph, source, destination, cnt); // Find the shortest path

    return 0;
}
