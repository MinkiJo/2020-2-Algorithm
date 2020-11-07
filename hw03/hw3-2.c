/* ID: 2016115921		>>> REPLACE WITH YOUR ID
 * NAME: JoMinki	>>> REPLACE WITH YOUR NAME
 * OS: linux, Ubuntu 16.04 
 * Compiler version: gcc 5.4.0 20160609
 */

// no memcpy, memccpy, memmove, wmemmove, or other direct memory copy/move functions
//  these functions performs 'BLOCKED' operations so that large chunk of memory 
//  operations are efficiently implemented, so they break UNIT TIME assumption
//  in algorithm design
// string functions: strcpy, strncpy, strlen, strcmp are alied, but not strdup

// >>> (10/100) pts
// >>> IN THE TOP 4-LINES COMMENTS 
// >>> LINE 1: REPLACE WITH YOUR ID (IF YOU HAVE NON-NUMERIC, IGNORE IT)
// >>> Line 2: REPLACE WITH YOUR NAME (NO HANGUL)
// >>> DO NOT CHANGE OS AND Compiler
// >>> COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

// HOMEWORK PROGRAMMING ASSIGNMENT 3
// IMPLEMENTATION OF SORTING ALGORITHMS FOR CHAR ARRAY STRINGS

#include<stdio.h>
#include<stdlib.h>	// atoi, malloc, free
#include<string.h>	// string library
#include<stdint.h>	// fixed-width integers, since C99 --- 1999 ISO standards

#define MEASURE_TIME	// to measure execution time

#define MEASURE_MEMORY	// to measure required memory
// from GJANG: free is not considered
// just counts the amount of memory required by malloc_c

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

/////////////////////////////////////////////////////////////////////
// to compute used memory
// use malloc_c defined bei, instead of malloc, calloc, realloc, etc.
// malloc_c accumulates the size of the dynamically allocated memory to
// global/static variable used_memory, so that we can measure the 
// used amount of memory exactly.
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_MEMORY
static size_t used_memory = 0;
void *malloc_c(size_t size)
{
  if ( size > 0 ) {
    // increase the required memory count
    used_memory += size;
    return malloc(size);
  }
  else return NULL;
}
#else
void *malloc_c(size_t size) { return malloc(size); }
#endif


/////////////////////////////////////////////////////////////
// read whole file into memory
/////////////////////////////////////////////////////////////
char* read_bytes( const char infile[], long *pNbytes )
  // returns an char array with its size stored in
  // the memory indicated by integer pointer variable pNbytes
  // the retured memory should freed by the caller
{
  char *B;
  long n;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL input file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s for read\n",infile);
    return NULL;
  }
  else {
    // find the file size
    fseek(fp,0,SEEK_END);	// move to the end of file
    *pNbytes = ftell(fp);	// file size = end loc from the start
    if ( *pNbytes <= 0 ) return NULL;	// no element

    // to the beginning again
    rewind(fp);

    // allocate memory and read the file
    B = (char*)malloc_c(*pNbytes+1);
    n = fread(B,1,*pNbytes,fp);
    if ( n != *pNbytes ) {
      fprintf(stderr, "file %s, %ld/%ld bytes read\n",infile,n,*pNbytes);
    }
    B[*pNbytes] = '\0';
    //fprintf(stderr, "file %s, %ld/%ld bytes read\n",infile,n,*pNbytes);

    // close file 
    fclose(fp);
    return B;
  }
}

/////////////////////////////////////////////////////////////
// write memory to a text file 
/////////////////////////////////////////////////////////////
void write_bytes( const char outfile[], const char B[], long Nbytes )
  // write the char array of size Nbytes
  // to file whose name given by outfile[]
{
  FILE *fp;
  long n;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL output file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s for write\n",outfile);
  }
  else {
    n = fwrite(B,1,Nbytes,fp);
    if ( n != Nbytes ) {
      fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);
    }
    //fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);

    // close file 
    fclose(fp);
  }
}


//////////////////////////////////////////////
///merge sort reference : lecture materials
///quick sort reference : https://coding-factory.tistory.com/137
//////////////////////////////////////////////

void swap(char**arr, int a, int b) 
{
    char* temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
void merge(char ** list,int strcount,int left, int mid, int right){

	int i, j, k, l;
	//char *tmp[100000];
	char ** tmp = (char**)malloc(sizeof(char*)*strcount);
	i = left; j = mid+1; k = left;

	while(i<=mid && j<=right){
	
		if(strcmp(list[i],list[j]) <= 0) tmp[k++] = list[i++];
		else tmp[k++] = list[j++];
	}

	if(i>mid){
		for(l=j; l<=right; l++) tmp[k++] = list[l];
	}

	else{
		for(l=i; l<=mid; l++) tmp[k++] = list[l];
	}

	for(l=left; l<=right; l++){
		list[l] = tmp[l];
	}
	free(tmp);
}

void merge_sort(char**list,int strcount,int left, int right){
	int mid;
	if(left<right){
	mid = (left+right)/2;

	merge_sort(list,strcount, left, mid);

	merge_sort(list,strcount, mid+1, right);

	merge(list,strcount, left, mid, right);

	}
}

int partition(char**arr, int left, int right)
{
    char*pivot = arr[left]; 
    int i = left + 1;
    int j = right;
 
    while (i <= j) 
    {
        while (i <= right && (strcmp(pivot,arr[i]) >=0))
        {
            i++; 
        }
        while (j >= (left+1)  && (strcmp(pivot,arr[j]) <=0)) 
        {
            j--; 
        }
        if (i <= j)
        {
            swap(arr, i, j); 
        }
    }
    swap(arr, left, j); 
    return j; 
 
}
void quick_sort(char**arr, int left, int right)
{
    if (left <= right)
    {
        int pivot = partition(arr, left, right); 
        quick_sort(arr, left, pivot - 1); 
        quick_sort(arr, pivot + 1, right); 
    }
}



/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
 int temp;
  long numBytes;
  char ** A;
  char *B;	// to store data to be sorted
  int method;	// which sorting method
  int fixdotwordsize;
  int strcount; //num of string
  int k = 0;
  int maxstr = 0;
#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
#endif

  if ( argc != 4 ) {
    fprintf(stderr, "usage: %s method valwordsize infile outfile\n",argv[0]);
    fprintf(stderr, " method 1: mergesort, 2: quick_sort\n");
    exit(0);
  }

  method = atoi(argv[1]);
  B = read_bytes(argv[2], &numBytes);

  temp = 0;
  strcount = 0;
  for(int i=0;i<numBytes;i++){
	temp++;
	if(B[i] == '.') {
		if(temp > maxstr) maxstr = temp;
		strcount++;
		temp = 0;
	}
  }

  A = (char**)malloc(sizeof(char*)*strcount);
  for(int i=0;i< strcount;i++){
	A[i] = (char*)malloc(sizeof(char)*maxstr);
  }
  
  for(int i=0;i<strcount;i++){
	
	int j = 0;
	
	do{A[i][j++] = B[k++];}while(B[k] != '.');
	A[i][j] = B[k++];
  }

#ifdef MEASURE_TIME
  start = clock();
#endif
  if ( B != NULL && numBytes > 0 ) {
    switch ( method ) {
      case 1:	// merge sort 
	merge_sort(A,strcount,0,strcount-1);
	break;
      case 2:	// quick sort
	quick_sort(A,0,strcount-1);
	break;
      default:
	break;
    }


k = 0;
for(int i=0;i<strcount;i++){

	for(int j=0;A[i][j] != '.';j++){
		B[k++] = A[i][j];

	}
	B[k++] = '.';
}


#ifdef MEASURE_TIME
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stdout,"%.5f seconds\n",cpu_time_used);
#endif
#ifdef MEASURE_MEMORY
    fprintf(stdout,"%lu bytes ( %.3f x %ld )\n",
	used_memory,(double)used_memory/(double)numBytes,numBytes);
	//used_memory,(double)used_memory/(double)(numBytes-1),numBytes-1);
#endif

    // save results
    write_bytes(argv[3], B, numBytes);

    // once allocated, should be freed after use
    for(int i=0;i<strcount;i++) free(A[i]);
    free(A);
    free(B);
  }
}
