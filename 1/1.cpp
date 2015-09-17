#include<stdio.h>
int main()
{
	long long t, a, b;
	scanf("%lld", &t);
	while(t--)
	{
		scanf("%lld%lld", &a, &b);
		printf("%lld\n", a + b);
	}
	return 0;
}