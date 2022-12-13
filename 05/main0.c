#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

void combine1(vec_ptr v, data_t *dest)
{
	long i;
	*dest = IDENT;

	for(i = 0; i < vec_length(v); i++)
	{
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}

void combine2(vec_ptr v, data_t *dest)
{
	long i;
	long length =  vec_length(v);
	*dest = IDENT;

	for(i = 0; i < length; i++)
	{
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}

void combine3(vec_ptr v, data_t *dest)
{
	long i;
	long length =  vec_length(v);
	data_t *data = get_vec_start(v);
	*dest = IDENT;

	for(i = 0; i < length; i++)
	{
		*dest = *dest OP data[i];
	}
}

void combine4(vec_ptr v, data_t *dest)
{
	long i;
	long length =  vec_length(v);
	data_t *data = get_vec_start(v);
	data_t acc = IDENT;
	*dest = IDENT;

	for(i = 0; i < length; i++)
	{
		acc = acc OP data[i];
	}
	*dest = acc;
}

void combine5(vec_ptr v, data_t *dest)
{
	long i;
	long length = vec_length(v);
	long limit = length -1;
	data_t *data = get_vec_start(v);
	data_t acc = IDENT;

	/* Combine 2 element at a time */
	for(i = 0; i < limit; i+=2)
	{
		acc = (acc OP data[i]) OP data[i+1];
	}

	/* Finish any remaining elements */
	for(; i < length; i++)
	{
		acc = acc OP data[i];
	}
	*dest = acc;
}

/* 2 x 2 loop unrolling */
void combine6(vec_ptr v, data_t *dest)
{
	long i;
	long length = vec_length(v);
	long limit = length -1;
	data_t *data = get_vec_start(v);
	data_t acc0 = IDENT;
	data_t acc1 = IDENT;

	/* Combine 2 element at a time */
	for(i = 0; i < limit; i+=2)
	{
		acc0 = acc OP data[i];
		acc1 = acc1 OP data[i+1];
	}

	/* Finish any remaining elements */
	for(; i < length; i++)
	{
		acc = acc OP data[i];
	}
	*dest = acc0 OP acc1;
}

void combine7(vec_ptr v, data_t *dest)
{
	long i;
	long length = vec_length(v);
	long limit = length -1;
	data_t *data = get_vec_start(v);
	data_t acc = IDENT;

	/* Combine 2 element at a time */
	for(i = 0; i < limit; i+=2)
	{
		/* reassociation transformation */
		acc = acc OP (data[i] OP data[i+1]);
	}

	/* Finish any remaining elements */
	for(; i < length; i++)
	{
		acc = acc OP data[i];
	}
	*dest = acc;
}

int main(int argc, char **argv)
{
	if(2 != argc)
	{
		printf("PROC LEN\n");
		return 0;
	}

	data_t dest;
	vec_ptr v = new_vec(atol(argv[1]));
	combine1(v, &dest);
	printf("v->len is %ld, dest is %ld\n", v->len, dest);

	return 0;
}
