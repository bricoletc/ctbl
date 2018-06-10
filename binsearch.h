#include <string.h>

int binsearch(char *w, char *vocab_array[], int lim){
	int cond;
	int low,high,mid;
	low = 0;
	high = lim-1;
	while (low <= high){
		mid = (low + high) /2;
		if ((cond = strcmp(w, vocab_array[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}
