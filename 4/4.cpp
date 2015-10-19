// This is b03902062 WJ's code
#include <stdio.h>
const int max_length = 18 + 1;
const int max_remainder_size = 7;
long long table[max_length][max_remainder_size][max_length][max_length] = {{{{0}}}}; //  length remainder number_of_7 number_of_4
// storing number <= length digit 
long long sum_table[max_length][max_remainder_size][max_length][max_length] = {{{{0}}}}; // length need_remainder now_7 now_4
// storing num of lucky number with given length (length digit to fill), need remainder, now_7, now_4
int remainder_table[max_length] = {0};
void build_remainder_table(void)
{
    int i;
    remainder_table[0] = 1;
    for(i = 0; i < (max_length - 1); i++)
        remainder_table[i + 1] = (remainder_table[i] * 3) % 7;
}
void build_table(void)
{
    table[0][0][0][0] = 1;
    int length, num_4, num_7, remainder, pick_num;
	for(length = 0; length < (max_length - 1); length++)
	{
		for(pick_num = 0; pick_num <= 9; pick_num++)
	    {
            for(remainder = 0; remainder < max_remainder_size; remainder++)
		    {
		        int new_remainder = (remainder + pick_num * remainder_table[length]) % 7;
				for(num_7 = 0; num_7 <= length; num_7++) // at most #length 7 or 4
				{
					for(num_4 = 0; num_4 <= length; num_4++)
					{
						long long now_value = table[length][remainder][num_7][num_4];
                        if(pick_num == 4)
							table[length + 1][new_remainder][num_7][num_4 + 1] += now_value;
						else if(pick_num == 7)
							table[length + 1][new_remainder][num_7 + 1][num_4] += now_value;
						else
							table[length + 1][new_remainder][num_7][num_4] += now_value;
					}
				}
			}
		}
	}
}	
void build_sum_table(void)
{
	int length, remainder, now_7, now_4, num_7, num_4;
	for(length = 0; length < max_length; length++)
	{
		int now_max_num = (max_length - 1) - length;
		for(remainder = 0; remainder < max_remainder_size; remainder++)
		{
			for(now_7 = 0; now_7 <= now_max_num; now_7++)
			{
				int need_7 = 3 - now_7;
				if(need_7 < 0)
					need_7 = 0;
				for(now_4 = 0; now_4 <= now_max_num; now_4++)
				{
					for(num_7 = need_7; num_7 <= length; num_7++)
					{
						int max_4 = now_7 + num_7 - now_4 - 1;
						if(max_4 > length)
							max_4 = length;
						for(num_4 = 0; num_4 <= max_4; num_4++)
							sum_table[length][remainder][now_7][now_4] += table[length][remainder][num_7][num_4];
					}
				}
			}
		}
	}
}
long long find_lucky(int now_4, int now_7, int now_remainder, int length, int *bound, long long ans)
{
    if(length == -1)
    {
        if(now_7 >= 3 && now_remainder == 0 && now_7 > now_4)
			ans++;
		return ans;
    }
	int pick_num;
	for(pick_num = 0; pick_num < bound[length]; pick_num++)
	{
		int need_remainder = (70 - now_remainder - pick_num * remainder_table[length]) % 7;
		if(pick_num == 4)
			ans += sum_table[length][need_remainder][now_7][now_4 + 1];
		else if(pick_num == 7)
			ans += sum_table[length][need_remainder][now_7 + 1][now_4];
		else
			ans += sum_table[length][need_remainder][now_7][now_4];
	}
	int new_remainder = now_remainder + bound[length] * remainder_table[length];
    new_remainder %= 7;
    // pick the same number as bound[length]
    if(bound[length] == 4)
		return find_lucky(now_4 + 1, now_7, new_remainder, length - 1, bound, ans);
    else if(bound[length] == 7)
        return find_lucky(now_4, now_7 + 1, new_remainder, length - 1, bound, ans);
    else
        return find_lucky(now_4, now_7, new_remainder, length - 1, bound, ans);
}
int main()
{
    int i, j, digit, ld[max_length], rd[max_length], t;
    build_remainder_table();
    build_table();
    build_sum_table();
    scanf("%d", &t);
    for(i = 0; i < t; i++)
    {
        long long l, r;
        scanf("%lld%lld", &l, &r);
        for(j = 0; j < max_length; j++)
        {
            ld[j] = 0;
            rd[j] = 0;
        }
        digit = 0;
        l--;
        while(l > 0)
        {
            ld[digit] = l % 10;
            l /= 10;
            digit++;
        }
        long long ansl = find_lucky(0, 0, 0, digit - 1, ld, 0);
        digit = 0;
        while(r > 0)
        {
            rd[digit] = r % 10;
            r /= 10;
            digit++;
        }
        long long ansr = find_lucky(0, 0, 0, digit - 1, rd, 0);
        long long final_ans = ansr - ansl;
        printf("%lld\n", final_ans);
    }
	return 0;
}
