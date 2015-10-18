#include <stdio.h>
const int max_length = 20;
const int max_remainder_size = 7;
long long table[max_remainder_size][max_length][max_length][max_length] = {{{{0}}}}; // remainder length number_of_7 number_of_4 
int remainder_table[max_length] = {0};
//storing number less than digits
long long ans;
// be careful of 0
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
						long long now_value = table[remainder][length][num_7][num_4];
                        if(pick_num == 4)
							table[new_remainder][length + 1][num_7][num_4 + 1] += now_value;
						else if(pick_num == 7)
							table[new_remainder][length + 1][num_7 + 1][num_4] += now_value;
						else
							table[new_remainder][length + 1][num_7][num_4] += now_value;
					}
				}
			}
		}
	}
}	
void find_lucky(int now_4, int now_7, int now_remainder, int length, int *bound)
{
    if(length == -1)
    {
        if(now_7 >= 3 && now_remainder == 0 && now_7 > now_4)
            ans++;
        return;
    }
	int pick_num;
	for(pick_num = 0; pick_num < bound[length]; pick_num++)
	{
		int need_remainder = (70 - now_remainder - pick_num * remainder_table[length]) % 7;
		int num_7, num_4;
        if(pick_num == 4)
		{
			int new_4 = now_4 + 1;
            int need_7 = 3 - now_7;
            if(need_7 < 0)
                need_7 = 0;
			for(num_7 = need_7; num_7 <= length; num_7++)
			{
			    // now_7 + num_7 > new_4 + num_4
                int max_4 = now_7 + num_7 - new_4 - 1;
                if(max_4 > length)
                    max_4 = length;
				for(num_4 = 0; num_4 <= max_4; num_4++)
						ans += table[need_remainder][length][num_7][num_4];
			}
		}
		else if(pick_num == 7)
		{
			int new_7 = now_7 + 1;
            int need_7 = 3 - new_7;
            if(need_7 < 0)
                need_7 = 0;
			for(num_7 = need_7; num_7 <= length; num_7++)
			{
			    // new_7 + num_7 > now_4 + num_4
                int max_4 = new_7 + num_7 - now_4 - 1;
                if(max_4 > length)
                    max_4 = length;
				for(num_4 = 0; num_4 <= max_4; num_4++)
					ans += table[need_remainder][length][num_7][num_4];
			}
		}
		else 
		{
            int need_7 = 3 - now_7;
            if(need_7 < 0)
                need_7 = 0;
			for(num_7 = need_7; num_7 <= length; num_7++)
			{
                int max_4 = now_7 + num_7 - now_4 - 1;
                if(max_4 > length)
                    max_4 = length;
				for(num_4 = 0; num_4 <= max_4; num_4++)
					ans += table[need_remainder][length][num_7][num_4];
			}
		}
	}
    int new_remainder = now_remainder + bound[length] * remainder_table[length];
    new_remainder %= 7;
    if(bound[length] == 4)
        find_lucky(now_4 + 1, now_7, new_remainder, length - 1, bound);
    else if(bound[length] == 7)
        find_lucky(now_4, now_7 + 1, new_remainder, length - 1, bound);
    else
        find_lucky(now_4, now_7, new_remainder, length - 1, bound);
}
int main()
{
    int i, j, digitl, digitr, digit, ld[max_length], rd[max_length], t;
    build_remainder_table();
    build_table();
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
        ans = 0;
        digit = 0;
        l--;
        while(l > 0)
        {
            ld[digit] = l % 10;
            l /= 10;
            digit++;
        }
        digitl = digit - 1;
        find_lucky(0, 0, 0, digitl, ld);
        long long ansl = ans;
        ans = 0;
        digit = 0;
        while(r > 0)
        {
            rd[digit] = r % 10;
            r /= 10;
            digit++;
        }
        digitr = digit - 1;
        find_lucky(0, 0, 0, digitr, rd);
        long long ansr = ans;
        long long final_ans = ansr - ansl;
        printf("%lld\n", final_ans);
    }
	return 0;
}
