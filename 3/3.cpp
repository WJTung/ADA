// This is b03902062 WJ's code, discussed with JoJorge (b03902061)
#include <stdio.h>
#include <stdlib.h>
const int N_max = 2E5;
long long c, e, p, table[2 * N_max] = {0};
long long bigmod(long long base, long long power, long long mod)
{
	if(power == 0)
		return 1;
	long long tmp = bigmod(base, power/2, mod);
	tmp *= tmp;
	tmp %= mod;
	if(power % 2 == 0)
		return tmp;
	else
		return ((base * tmp) % mod);
}
void build_table(long long n) // build a table to access (i + j) ^ e fast
{
	long long i, j, max_sum = 2 * n - 1;
	for(i = 1; i <= max_sum; i++)
		table[i] = 0;
	for(i = 2; i <= max_sum; i++)
	{
		if(table[i] == 0)
		{
			table[i] = bigmod(i, e, p);
			for(j = (i * i); j <= max_sum; j+=i)
					table[j] = i;
		}
		else
		{
			long long factor_1, factor_2;
			factor_1 = table[i];
			factor_2 = i / table[i];
			table[i] = (table[factor_1] * table[factor_2]) % p;
		}
	}
}
bool cal_result(long long i, long long j)
{
	long long residue = 1;
	residue *= (c * (i - j));
	residue %= p;
	if(residue < 0)
		residue += p;
	residue *= table[i + j];
	residue %= p;
	if((residue * 2) > p)
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
		build_table(n);
		for(j = 0; j < n; j++)
			ans[j] = j + 1;
		qsort(ans, n, sizeof(long long), compare);
		for(j = 0; j < n; j++)
			printf("%lld ", ans[j]);
		putchar('\n');
	}
	return 0;
}

			
		