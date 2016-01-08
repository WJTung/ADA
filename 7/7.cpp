/* This is b03902062 WJ's code 7.cpp */
#include <stdio.h>
#include <vector>
const int n_max = 100; //10000;
const int m_max = 100; //100000;
int visited1[n_max];
int visited2[n_max];
int is_start[n_max];
typedef struct edge
{
	int vertex1;
	int vertex2;
} E;
E edges1[m_max];
E edges2[m_max];
// 0 = degree 1 = degree2 2 = selfedge
int vertices1[n_max][3];
int vertices2[n_max][3];
int visit_order_1[n_max];
int visit_order_2[n_max];
int t1, n, m;
void DFS(int, std::vector<int> *);
int find_new(std::vector<int> *, int);
int visit2(int, std::vector<int> *, int);
int check_ans(void)
{
	// puts("check ans");
	int i, ans[n_max];
	for(i = 0; i < n; i++)
		ans[visit_order_2[i]] = visit_order_1[i];
	for(i = 0; i < n; i++)
		printf("%d ", ans[i] + 1);
	putchar('\n');
	return 1;
}
bool is_equal(int v1, int v2)
{
	int i;
	for(i = 0; i < 3; i++)
		if(vertices1[v1][i] != vertices2[v2][i])
			return 0;
	return 1;
}
int main()
{
	int T, i;
	std::vector<int> adjacent_list1[n_max];
	std::vector<int> adjacent_list2[n_max];
	scanf("%d", &T);
	for(i = 1; i <= T; i++)
	{
		scanf("%d%d", &n, &m);
		int j;
		for(j = 0; j < n; j++)
		{
			int k;
			for(k = 0; k < 3; k++)
			{
				vertices1[j][k] = 0;
				vertices2[j][k] = 0;
			}
			visited1[j] = 0;
			visited2[j] = 0;
			is_start[j] = 0;
		}
		for(j = 0; j < m; j++)
		{
			scanf("%d%d", &edges1[j].vertex1, &edges1[j].vertex2);
			edges1[j].vertex1--;
			edges1[j].vertex2--;
			adjacent_list1[edges1[j].vertex1].push_back(edges1[j].vertex2);
			adjacent_list1[edges1[j].vertex2].push_back(edges1[j].vertex1);
			vertices1[edges1[j].vertex1][0]++;
			vertices1[edges1[j].vertex2][0]++;
			if(edges1[j].vertex1 == edges1[j].vertex2)
				vertices1[edges1[j].vertex1][2]++;
		}
		for(j = 0; j < m; j++)
		{
			scanf("%d%d", &edges2[j].vertex1, &edges2[j].vertex2);
			edges2[j].vertex1--;
			edges2[j].vertex2--;
			adjacent_list2[edges2[j].vertex1].push_back(edges2[j].vertex2);
			adjacent_list2[edges2[j].vertex2].push_back(edges2[j].vertex1);
			vertices2[edges2[j].vertex1][0]++;
			vertices2[edges2[j].vertex2][0]++;
			if(edges2[j].vertex1 == edges2[j].vertex2)
				vertices2[edges2[j].vertex1][2]++;
		}
		for(j = 0; j < m; j++)
		{
			vertices1[edges1[j].vertex1][1] += vertices1[edges1[j].vertex2][0];
			vertices1[edges1[j].vertex2][1] += vertices1[edges1[j].vertex1][0];
			vertices2[edges2[j].vertex1][1] += vertices2[edges2[j].vertex2][0];
			vertices2[edges2[j].vertex2][1] += vertices2[edges2[j].vertex1][0];
		}
		t1 = 0;
		for(j = 0; j < n; j++)
		{
			if(!visited1[j])
			{
				is_start[t1] = 1;
				DFS(j, adjacent_list1);
			}
		}
		find_new(adjacent_list2, 0);
	}
	return 0;
}
void DFS(int now, std::vector<int> *adjacent_list)
{
	// printf("G1 DFS now is %d\n", now);
	visit_order_1[t1] = now;
	visited1[now] = 1;
	t1++;
	int size = adjacent_list[now].size();
	int i;
	for(i = 0; i < size; i++)
	{
		if(!visited1[adjacent_list[now][i]])
			DFS(adjacent_list[now][i], adjacent_list);
	}
	return;
}
int find_new(std::vector<int> *adjacent_list, int t2)
{
	int i;
	for(i = 0; i < n; i++)
	{
		if(!visited2[i] && is_equal(visit_order_1[t2], i)) // find same property vertex to start new DFS 
			if(visit2(i, adjacent_list, t2))
				return 1;
	}
	return 0;
}
int visit2(int now, std::vector<int> *adjacent_list, int t2)
{
	// printf("G2 now visit %d\n", now);
	if(!is_equal(visit_order_1[t2], now))
		return 0;
	visit_order_2[t2] = now;
	visited2[now] = 1;
	t2++;
	if(t2 == n)
		return check_ans();
	int size = adjacent_list[now].size();
	int i;
	if(is_start[t2])
	{
		for(i = 0; i < size; i++)
		{	
			if(!visited2[adjacent_list[now][i]])
			{	
				visited2[now] = 0;
				return 0;
			}
		}
		if(find_new(adjacent_list, t2))
			return 1;
		visited2[now] = 0;
		return 0;
	}
	else	
	{
		for(i = 0; i < size; i++)
		{
			if(!visited2[adjacent_list[now][i]])
				if(visit2(adjacent_list[now][i], adjacent_list, t2))
					return 1;
		}
		visited2[now] = 0;
		return 0;
	}
}