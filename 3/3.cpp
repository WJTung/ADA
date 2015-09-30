// This is b03902062 WJ's code, discussed with Jojorge (b03902061)
#include <stdio.h>
const int N_max = 2E5;
long long bigmod(long long b, long long p, long long m)
{
	if(p == 0)
		return 1;
	long long tmp = bigmod(b, p/2, m);
	if(p % 2 == 0)
		return ((tmp * tmp) % m);
	else
		return ((b * tmp *tmp) % m);
}
bool cal_result(long long i, long long j, long long c, long long e, long long p)
{
	long long residue = 1;
	residue *= (c * (i - j));
	residue *= bigmod((i + j), e, p);
	residue %= p;
	if(residue > (p / 2))
		return 1;
	else
		return 0;
}
void swap(long long *a, long long *b)
{
	long long tmp = (*a);
	(*a) = (*b);
	(*b) = tmp;
}
void quicksort(long long *ans, long long left, long long right, long long c, long long e, long long p)
{
	if(left >= right)
		return;
	long long pivot = ans[left], i, j = left;
	for(i = left + 1; i <= right; i++)
	{
		if(cal_result(ans[i], pivot, c, e, p) == 1)
		{
			j++;
			swap(ans + i, ans + j);
		}
	}
	swap(ans + left, ans + j);
	quicksort(ans, left, j - 1, c, e, p);
	quicksort(ans, j + 1, right, c, e, p);
}
int main()
{
	long long t, n, c, e, p, i, j, ans[N_max];
	scanf("%lld", &t);
	for(i = 1; i <= t; i++)
	{
		scanf("%lld%lld%lld%lld", &n, &c, &e, &p);
		e %= (p - 1); // Fermat's little theorem a ^ (p - 1) = 1 (mod p)
		for(j = 1; j <= n; j++)
			ans[j] = j;
		quicksort(ans, 1, n, c, e, p);
		for(j = 1; j <= n; j++)
			printf("%lld ", ans[j]);
		putchar('\n');
	}
	return 0;
}

			
		