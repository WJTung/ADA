// This is b03902062 WJ's code
// reference : http://stackoverflow.com/questions/15720155/find-all-critical-edges-of-an-mst and http://www.csie.ntnu.edu.tw/~u91029/Component.html
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
const int m_max = 100000;
const int n_max = 100001 + 1;
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
void DFS(int root, std::vector<int> *adjacent, int *parent, int *now_num, int *low, int *visit, int *t)
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
int find_root(int n, int *parent)
{
	if(parent[n] == n)
		return n;
	else 
	{
		int root = find_root(parent[n], parent);
		parent[n] = root;
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
		int parent[n_max]; // disjoint set to see if two nodes are in same component, smallest one is root
		int must_num = 0, must_sum = 0;
		E edges[m_max];
		scanf("%d%d", &n, &m);
		for(j = 1; j <= n; j++)
			parent[j] = j;
		for(j = 0; j < m; j++)
			scanf("%d%d%d", &edges[j].node1, &edges[j].node2, &edges[j].weight);
		std::sort(edges, edges + m, cmp);
		int now_position = 0;
		while(now_position < m)
		{
			int now_weight = edges[now_position].weight;
			int now_start = now_position;
            std::vector<int> adjacent[n_max];
			while(edges[now_position].weight == now_weight)
			{
				int root1 = find_root(edges[now_position].node1, parent), root2 = find_root(edges[now_position].node2, parent); // each set is a component
                if(root1 != root2)
				{
					adjacent[root1].push_back(root2);
					adjacent[root2].push_back(root1);
				}
				now_position++;
			}
			int k;
			for(k = now_start; k < now_position; k++)
			{
				int root1 = find_root(edges[k].node1, parent), root2 = find_root(edges[k].node2, parent);
				if(root1 != root2) // union
				{
					if(root1 < root2)
						parent[root2] = root1;
					else
						parent[root1] = root2;
				}
			}
			int DFS_root = edges[now_start].node1;
			int now_num = 0; // must edge num of now weight
			int DFS_parent[n_max] = {0};
			DFS_parent[DFS_root] = DFS_root;
			int low[n_max] = {0}, visit[n_max] = {0}, DFS_t = 0;
			DFS(DFS_root, adjacent, DFS_parent, &now_num, low, visit, &DFS_t);
			must_num += now_num;
			must_sum += now_weight * now_num;
        }
		printf("%d %d\n", must_num, must_sum);
	}
}
			
			
