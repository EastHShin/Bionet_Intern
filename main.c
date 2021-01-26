#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SAMPLE_RATE	200	/* Sample rate in Hz. */
#define MS_PER_SAMPLE	( (double) 1000/ (double) SAMPLE_RATE)
#define MS25	((int) (25/MS_PER_SAMPLE + 0.5))
#define MS30	((int) (30/MS_PER_SAMPLE + 0.5))
#define LPBUFFER_LGTH ((int) (2*MS30))

int lpfilt(int datum, int init)
{
	static long y1 = 0, y2 = 0;
	static int data[LPBUFFER_LGTH], ptr = 0;
	long y0;
	int output, halfPtr;
	if (init)
	{
		for (ptr = 0; ptr < LPBUFFER_LGTH; ++ptr)
			data[ptr] = 0;
		y1 = y2 = 0;
		ptr = 0;
	}
	halfPtr = ptr - (LPBUFFER_LGTH / 2);	// Use halfPtr to index
	if (halfPtr < 0)							// to x[n-6].
		halfPtr += LPBUFFER_LGTH;
	y0 = (y1 << 1) - y2 + datum - (data[halfPtr] << 1) + data[ptr];
	y2 = y1;
	y1 = y0;
	output = y0 / ((LPBUFFER_LGTH * LPBUFFER_LGTH) / 4);
	data[ptr] = datum;			// Stick most recent sample into
	if (++ptr == LPBUFFER_LGTH)	// the circular buffer and update
		ptr = 0;					// the buffer pointer.
	return output;
}

void delay(int ms) {
	
}
int main()
{
	int n = 0;
	printf("init");
	lpfilt(0, 1);
	printf("\n");
	printf("P sector : ");
	for (int i = 0; i < 20; i++)
		printf("%d ", lpfilt(0, 0));
	printf("\n");
	while (1) {
		printf("%d ", lpfilt(n, 0));
		n += 100;
		if (n > 1500) {
			break;
		}
	}
	printf("\n");
	n = 1500;
	while (1) {
		printf("%d ", lpfilt(n, 0));
		n -= 100;
		if (n < 0)
			break;
	}
	printf("\n");
	for (int i = 0; i < 20; i++)
		printf("%d ", lpfilt(0, 0));

	return 0;
}