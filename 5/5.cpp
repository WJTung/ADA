// This is b03902062 WJ's code
#include <stdio.h>
#include <string.h>
const int max_n = 2000;
const int max_length = 2000;
int max_digit;
void build_num(int *num, int sum, int sum_need)
{
	int sum_now = sum;
	int sum_difference = 0;
	int change_length, found = 0;
	for(change_length = 1; found != 1; change_length++)
	{
		sum_now -= num[change_length];
		sum_difference = sum_need - sum_now;
		if(num[change_length] != 9)
		{
			if(num[change_length] < sum_difference && sum_difference <= 9 * change_length)
				found = 1;
		}
	}
	change_length--;
	if(change_length > max_digit)
		max_digit = change_length;
	int min_need = sum_difference - 9 * (change_length - 1);
	if(min_need > num[change_length])
		num[change_length] = min_need;
	else
		num[change_length] += 1;
	sum_difference -= num[change_length];
	int length;
	for(length = 1; length < change_length; length++)
	{
		if(sum_difference >= 9)
		{
			num[length] = 9;
			sum_difference -= 9;
		}
		else
		{
			num[length] = sum_difference;
			sum_difference = 0;
		}
	}
	for(length = max_digit; length >= 1; length--)
		putchar(num[length] + '0');
    return;
}
int main()
{
	int T, i;
	scanf("%d", &T);
	for(i = 1; i <= T; i++)
	{
		int n, j, c[max_n];
		scanf("%d", &n);
        int num[max_length] = {0};
		max_digit = 0;
		scanf("%d", &c[0]);
		build_num(num, 0, c[0]);
		for(j = 1; j < n; j++)
		{
            putchar(' ');
			scanf("%d", &c[j]);
			build_num(num, c[j - 1], c[j]);
		}
		putchar('\n');
	}
	return 0;
}
