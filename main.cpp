void dijkstra(int graph[V][V], int src) 

{ 

    int dist[V]; 

    bool sptSet[V];

    for (int i = 0; i < V; i++) 

        dist[i] = INT_MAX, sptSet[i] = false; 

     dist[src] = 0; 

  for (int count = 0; count < V - 1; count++)

 { 

        int u = minDistance(dist, sptSet); 

        sptSet[u] = true; 

    for (int v = 0; v < V; v++) 

     if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 

                && dist[u] + graph[u][v] < dist[v]) 

                dist[v] = dist[u] + graph[u][v]; 

    } 

  printSolution(dist); 

} 
