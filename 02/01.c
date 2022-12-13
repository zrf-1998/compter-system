#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
	size_t i;
	for(i = 0; i < len; ++i)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_int(int x)
{
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x)
{
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x)
{
	show_bytes((byte_pointer)&x, sizeof(void *));
}

void test_show_bytes(int val)
{
	int ival = val;
	float fval = (float)ival;
	int *pval = &ival;
	show_int(ival);
	show_float(fval);
	show_pointer(pval);
}

int main()
{
	test_show_bytes(12345);
	show_bytes("12345", 6);

	short x = 12345;
	short mx = -x;

	show_bytes((byte_pointer)&x, sizeof(short));
	show_bytes((byte_pointer)&mx, sizeof(short));

	short int v = -12345;
	unsigned short uv = (unsigned short)v;
	printf("v = %d, uv = %u\n", v, uv);
	show_bytes((byte_pointer)&v, sizeof(short int));
	show_bytes((byte_pointer)&uv, sizeof(unsigned short));

	unsigned u = 4294967295u;
	int tu = (int)u;
	printf("u = %u, tu = %d\n", u, tu);
	show_bytes((byte_pointer)&u, sizeof(unsigned));
	show_bytes((byte_pointer)&tu, sizeof(int));
	return 0;
}
