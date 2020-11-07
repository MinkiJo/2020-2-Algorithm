#define _CRT_SECURE_NO_WARNINGS

/* ID: COMP319 >>> 2016115921
* NAME: Algorithms 1 >>> jo minki
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/
// >>> (10/100) pts
// >>> IN THE TOP COMMENTS BLOCK
// >>> LINE 1: REPLACE WITH YOUR ID (IF YOU HAVE NON-NUMERIC, IGNORE IT)
// >>> Line 2: REPLACE WITH YOUR NAME (NO HANGUL)
// >>> DO NOT CHANGE OS AND Compiler, COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

#include<stdio.h>
#include<stdlib.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) =(t))
void quickSort(int* a, int left, int right) {
	int pivot, i, j;
	int temp;
	if (left < right) {
		i = left; j = right + 1;
		pivot = a[left];
		do {

			do i++; while (a[i] < pivot);
			do j--; while (a[j] > pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);

	}
}

int main(int argc, char*argv[]) {

	int arr[3];
	for (int i = 0;i < 3;i++) {arr[i] = atoi(argv[i+1]);}
	quickSort(arr, 0, 2);

	for (int i = 0;i < 3;i++) {printf("%d ", arr[i]);}
	printf("\n");
	return 0;
}
