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
#include<math.h>
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
int main(int argc, char* argv[]) {
	FILE* fp;
	int i, num, * A;
	
	fp = fopen(argv[1], "r");
	
	fscanf(fp, "%d", &num);
	
	A = (int*)malloc(sizeof(int) * num);	
	for (i = 0; i < num; i++) fscanf(fp, "%d", A + i);
	quickSort(A, 0, num);
	printf("#data\tmin\tmax\tmean\tvariance\n");
	int min = A[0];
	int max = A[num - 1];
	double mean = 0;
	for (int i = 0;i < num;i++) {
		mean += A[i];
	}
	mean /= num;

	double var = 0;
	for (int i = 0;i < num;i++) {
		var += pow(A[i]-mean,2);
	}
	var /= num;
	printf("%-d\t%-d\t%-d\t%.1f\t%.1f\t\n",num,min, max, mean, var);

	free(A);
	fclose(fp);
}
