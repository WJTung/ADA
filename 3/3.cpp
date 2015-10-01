// This is b03902062 WJ's code, discussed with JoJorge (b03902061)
#include <stdio.h>
#include <algorithm>
const int N_Max = 2E5;
long long c, e, p, prime_factor[2 * N_Max] = {0}, table[2 * N_Max] = {0};
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
void build_prime_factor()
{
	long long i, j, Max_Sum = 2 * N_Max - 1;
	for(i = 2; (i * i) <= Max_Sum; i++)
	{
		if(prime_factor[i] == 0)
		{
			for(j = (i * i); j <= Max_Sum; j+=i)
				prime_factor[j] = i;
		}
	}
}
void build_table(long long n)
{
	long long i, j, max_sum = 2 * n - 1;
	for(i = 2; i <= max_sum; i++)
	{
		if(prime_factor[i] == 0)
			table[i] = bigmod(i, e, p);
		else
		{
			long long factor_1, factor_2;
			factor_1 = prime_factor[i];
			factor_2 = i / prime_factor[i];
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
int main()
{
	long long t, n, i, j, ans[N_Max];
	scanf("%lld", &t);
	build_prime_factor();
	for(i = 1; i <= t; i++)
	{
		scanf("%lld%lld%lld%lld", &n, &c, &e, &p);
		e %= (p - 1); // Fermat's little theorem a ^ (p - 1) = 1 (mod p)
		build_table(n);
		for(j = 0; j < n; j++)
			ans[j] = j + 1;
		std::sort(ans, ans + n, cal_result);
		for(j = 0; j < n; j++)
			printf("%lld ", ans[j]);
		putchar('\n');
	}
	return 0;
}

			
		