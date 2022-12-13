#ifndef __VEC_H__
#define __VEC_H__

typedef long data_t;

typedef struct
{
	long len;
	data_t *data;
}vec_rec, *vec_ptr;

vec_ptr new_vec(long len);
int get_vec_element(vec_ptr v, long index, data_t *dest);
long vec_length(vec_ptr v);
data_t *get_vec_start(vec_ptr v);

#endif
