/* Rearrange two vectors so that for each i, b[i] >= a[i] */
void minmax1(long a[], long b[], long n)
{
	long i;

	for(i = 0; i < n; i++)
	{
		if(a[i] > b[i])
		{
			long t = a[i];
			a[i] = b[i];
			b[i] = t;
		}
	}
}

/* Rearrange two vectors so that for each i,  b[i] >= a[i]*/
void minmax2(long a[], long b[], long n)
{
	long i;
	
	for(i = 0; i < n; i++)
	{
		long min = a[i] < b[i] ? a[i] : b[i];
		long max = a[i] < b[i] ? b[i] : a[i];
		a[i] = min;
		b[i] = max;
	}
}

/* Rearrange two vectors so that for each i,  b[i] >= a[i]*/
void minmax3(long a[], long b[], long n)
{
	long i;
	long min;
	long max;

	for(i = 0; i < n; i++)
	{
		min = a[i] < b[i] ? a[i] : b[i];
		max = a[i] < b[i] ? b[i] : a[i];
		a[i] = min;
		b[i] = max;
	}
}
