/* This is b03902062 WJ's code 7.cpp */
#include <stdio.h>
#include <vector>
const int n_max = 10000;
const int m_max = 10000;
typedef struct edge
{
	int vertex1;
	int vertex2;
} E;
E edges1[m_max];
E edges2[m_max];
int n, m;
int ans[n_max];
int used[n_max];
int check_ans(void)
{
	int i, j, adjacent_matrix[n][n];
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			adjacent_matrix[i][j] = 0;
	for(i = 0; i < m; i++)
	{
		adjacent_matrix[edges1[i].vertex1][edges1[i].vertex2]++;
		adjacent_matrix[edges1[i].vertex2][edges1[i].vertex1]++;
	}
	for(i = 0; i < m; i++)
	{
		adjacent_matrix[ans[edges2[i].vertex1]][ans[edges2[i].vertex2]]--;
		adjacent_matrix[ans[edges2[i].vertex2]][ans[edges2[i].vertex1]]--;
		if(adjacent_matrix[ans[edges2[i].vertex1]][ans[edges2[i].vertex2]] < 0)
			return 0;
		if(adjacent_matrix[ans[edges2[i].vertex2]][ans[edges2[i].vertex1]] < 0)
			return 0;
	}
	for(i = 0; i < n; i++)
		printf("%d ", ans[i] + 1);
	putchar('\n');
	return 1;
}
int fill_ans(int now)
{
	if(now == n)
		return check_ans();
	int i;
	for(i = 0; i < n; i++)
	{
		if(!used[i])
		{
			ans[now] = i;
			used[i] = 1;
			if(fill_ans(now + 1))
				return 1;
			used[i] = 0;
		}
	}
	return 0;
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
		for(j = 0; j < m; j++)
		{
			scanf("%d%d", &edges1[j].vertex1, &edges1[j].vertex2);
			edges1[j].vertex1--;
			edges1[j].vertex2--;
		}
		for(j = 0; j < m; j++)
		{
			scanf("%d%d", &edges2[j].vertex1, &edges2[j].vertex2);
			edges2[j].vertex1--;
			edges2[j].vertex2--;
		}
		for(j = 0; j < n; j++)
			used[j] = 0;
		fill_ans(0);
	}
	return 0;
}
