/* This is b03902062 WJ's code 7.cpp */
#include <stdio.h>
#include <algorithm>
const int n_max = 10000;
const int m_max = 100000;
typedef struct vertex
{
	int num;
	int degree;
	int degree2;
	int selfedge;
} V;
typedef struct edge
{
	int vertex1;
	int vertex2;
} E;
bool V_compare(V v1, V v2)
{
	if(v1.degree < v2.degree)
		return 1;
	if(v1.degree > v2.degree)
		return 0;
	if(v1.degree2 < v2.degree2)
		return 1;
	if(v1.degree2 > v2.degree2)
		return 0;
	if(v1.selfedge < v2.selfedge)
		return 1;
	if(v1.selfedge > v2.selfedge)
		return 0;
	return 0;
}
int main()
{
	int T, n, m, i;
	V vertices1[n_max];
	V vertices2[n_max];
	E edges1[m_max];
	E edges2[m_max];
	int ans[n_max];
	scanf("%d", &T);
	for(i = 1; i <= T; i++)
	{
		scanf("%d%d", &n, &m);
		//printf("n = %d m = %d\n", n, m);
		int j;
		for(j = 0; j < n; j++)
		{
			vertices1[j].num = j;
			vertices2[j].num = j;
			vertices1[j].degree = 0;
			vertices1[j].degree2 = 0;
			vertices1[j].selfedge = 0;
			vertices2[j].degree = 0;
			vertices2[j].degree2 = 0;
			vertices2[j].selfedge = 0;
		}
		for(j = 0; j < m; j++)
		{
			scanf("%d%d", &edges1[j].vertex1, &edges1[j].vertex2);
			edges1[j].vertex1--;
			edges1[j].vertex2--;
			//printf("v1 = %d v2 = %d\n",  edges1[j].vertex1, edges1[j].vertex2);
			vertices1[edges1[j].vertex1].degree++;
			vertices1[edges1[j].vertex2].degree++;
			if(edges1[j].vertex1 == edges1[j].vertex2)
				vertices1[edges1[j].vertex1].selfedge++;
		}
		for(j = 0; j < m; j++)
		{
			scanf("%d%d", &edges2[j].vertex1, &edges2[j].vertex2);
			edges2[j].vertex1--;
			edges2[j].vertex2--;
			//printf("v1 = %d v2 = %d\n",  edges2[j].vertex1, edges2[j].vertex2);
			vertices2[edges2[j].vertex1].degree++;
			vertices2[edges2[j].vertex2].degree++;
			if(edges2[j].vertex1 == edges2[j].vertex2)
				vertices2[edges2[j].vertex1].selfedge++;
		}
		for(j = 0; j < m; j++)
		{
			vertices1[edges1[j].vertex1].degree2 += vertices1[edges1[j].vertex2].degree;
			vertices1[edges1[j].vertex2].degree2 += vertices1[edges1[j].vertex1].degree;
			vertices2[edges2[j].vertex1].degree2 += vertices2[edges2[j].vertex2].degree;
			vertices2[edges2[j].vertex2].degree2 += vertices2[edges2[j].vertex1].degree;
		}
		std::sort(vertices1, vertices1 + n, V_compare);
		std::sort(vertices2, vertices2 + n, V_compare);
		for(j = 0; j < n; j++)
			ans[vertices2[j].num] = vertices1[j].num;
		for(j = 0; j < n; j++)
			printf("%d ", ans[j] + 1);
		putchar('\n');
	}
	return 0;
}