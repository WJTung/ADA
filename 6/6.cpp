// This is b03902062 WJ's code
// reference : http://stackoverflow.com/questions/15720155/find-all-critical-edges-of-an-mst and http://www.csie.ntnu.edu.tw/~u91029/Component.html
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
const int m_max = 100000;
const int n_max = 50000 + 1;
typedef struct edge
{
	int node1;
	int node2;
	int weight;
} E;
bool cmp(const E &edge1, const E &edge2)
{
	return edge1.weight < edge2.weight;
}
void DFS(int root, std::vector<int> *adjacent, int *parent, long long *now_num, int *low, int *visit, int *t)
{
	(*t)++;
	visit[root] = (*t);
	low[root] = (*t);
	int i;
	int parent_edge = 0;
    int adjacent_size = adjacent[root].size();
	for(i = 0; i < adjacent_size; i++)
	{
		int next = adjacent[root].at(i);
		if(next == parent[root])
			parent_edge++;
		if(visit[next] == 0)
		{
			parent[next] = root;
			DFS(next, adjacent, parent, now_num, low, visit, t);
			if(low[next] < low[root])
				low[root] = low[next];
            if(low[next] > visit[root]) // bridge
				(*now_num)++;
		}
		else if((next == parent[root] && parent_edge > 1) || (next != parent[root] && visit[next] < visit[root])) // back edge 
		{
			if(low[next] < low[root])
				low[root] = low[next];
		}
	}
	return;
}			
int find_component(int n, int *component)
{
	if(component[n] == n) // the symbol of the component is itself
		return n;
	else 
	{
		int root = find_component(component[n], component);
		component[n] = root;
		return root;
	}
}
int main()
{
	int T, i;
	scanf("%d", &T);
	for(i = 0; i < T; i++)
	{
		int n, m, j;
		int component[n_max]; // disjoint set to see if two nodes are in same component
		int component_size[n_max];
        long long must_num = 0, must_sum = 0;
		E edges[m_max];
		scanf("%d%d", &n, &m);
		for(j = 1; j <= n; j++)
        {
			component[j] = j;
            component_size[j] = 1;
        }
		for(j = 0; j < m; j++)
			scanf("%d%d%d", &edges[j].node1, &edges[j].node2, &edges[j].weight);
		std::sort(edges, edges + m, cmp);
		int now_position = 0;
		while(now_position < m)
		{
			long long now_weight = edges[now_position].weight;
			int now_start = now_position;
            std::vector<int> adjacent[n_max];
			while(edges[now_position].weight == now_weight)
			{
				int component1 = find_component(edges[now_position].node1, component), component2 = find_component(edges[now_position].node2, component);
                if(component1 != component2) 
				{
					adjacent[component1].push_back(component2);
					adjacent[component2].push_back(component1);
				}
				now_position++;
			}
			long long now_num = 0; // must edge num of now weight
			int DFS_parent[n_max] = {0};
			int low[n_max] = {0}, visit[n_max] = {0}, DFS_t, k;
			for(k = now_start; k < now_position; k++)
			{
				int component1 = find_component(edges[k].node1, component), component2 = find_component(edges[k].node2, component);
				if(!visit[component1]) // Each component is seem as a node in DFS, this node is still not visited
                {
                    DFS_t = 0;
			        DFS(component1, adjacent, DFS_parent, &now_num, low, visit, &DFS_t);
                }
                if(component1 != component2) // union
				{
					if(component_size[component1] < component_size[component2])
					{	
                        component[component1] = component2;
                        component_size[component2] += component_size[component1];
                    }
					else
					{	
                        component[component2] = component1;
                        component_size[component1] += component_size[component2];
                    }
				}
			}
			must_num += now_num;
			must_sum += now_weight * now_num;
        }
		printf("%lld %lld\n", must_num, must_sum);
	}
}
			
			
