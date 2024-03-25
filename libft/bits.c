#include <stdio.h>

unsigned char reverse_bits(unsigned char octet)
{
	unsigned char ans;
	int i;

	ans = 0;
	i = 7;
	while (i >= 0)
	{
		ans = ans << 1;
		if (octet & (1 << i))
			ans += 1;
		i--;
	}

	return (ans);	
}

unsigned char swap_bits(unsigned char octet)
{
	return ((octet << 4) | (octet >> 4));
}

void print_bits(unsigned char octet)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		if (octet & (1 << i))
			printf("1");
		else
			printf("0");
		i--;
	}
}

int main()
{
	unsigned char ch;

	ch = 255;
	print_bits(ch);
}