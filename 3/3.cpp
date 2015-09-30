// This is b03902062 WJ's code, discussed with JoJorge (b03902061)
#include <stdio.h>
#include <stdlib.h>
const int N_max = 2E5 + 1;
long long c, e, p;
long long bigmod(long long base, long long power, long long mod)
{
	if(power == 0)
		return 1;
	long long tmp = bigmod(base, power/2, mod);
	if(power % 2 == 0)
		return ((tmp * tmp) % mod);
	else
		return ((base * tmp * tmp) % mod);
}
bool cal_result(long long i, long long j)
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
int compare(const void *a, const void *b)
{
	if(cal_result((*(long long*)a), (*(long long*)b)))
		return -1;
	else
		return 1;
}
int main()
{
	long long t, n, i, j, ans[N_max];
	scanf("%lld", &t);
	for(i = 1; i <= t; i++)
	{
		scanf("%lld%lld%lld%lld", &n, &c, &e, &p);
		e %= (p - 1); // Fermat's little theorem a ^ (p - 1) = 1 (mod p)
		for(j = 0; j < n; j++)
			ans[j] = j + 1;
		qsort(ans, n, sizeof(long long), compare);
		for(j = 0; j < n; j++)
			printf("%lld ", ans[j]);
		putchar('\n');
	}
	return 0;
}

			
		