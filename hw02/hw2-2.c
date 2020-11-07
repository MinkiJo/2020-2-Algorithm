/* ID: COMP319		>>> REPLACE WITH YOUR ID
 * NAME: Algorithms 1	>>> REPLACE WITH YOUR NAME
 * OS: linux, Ubuntu 16.04 
 * Compiler version: gcc 5.4.0 20160609
 */

// NOTE: IN GENERAL, COMMENTED STATEMENTS FOLLOWED BY 
// ">>>" WRITTEN IN CAPITAL LETTERS ARE DIRECTIONS

// >>> (10/100) pts
// >>> IN THE TOP 4-LINES COMMENTS 
// >>> LINE 1: 2016115921
// >>> Line 2: Jo Minki
// >>> DO NOT CHANGE OS AND Compiler
// >>> COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

// HOMEWORK PROGRAMMING ASSIGNMENT 2
// IMPLEMENTATION OF SORTING ALGORITHMS FOR CHAR ARRAY STRINGS
// HW 2-2 USING CHAR**

#include<stdio.h>
#include<stdlib.h>	// atoi, malloc, free
#include<string.h>	// string library

#define MEASURE_TIME	// to measure execution time
// from GJANG: not sure if the time measurement code works with Windows
// If it works, execution time will be printed.
// Otherwise, comment out the line "#define MEASURE_TIME" and compile again.

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

// maximum length of a single string
#define MAX_STR_LEN	256

/////////////////////////////////////////////////////////////
// print char array array
/////////////////////////////////////////////////////////////
void print_chararr_dynamic( FILE *fp, char *A[], int N )
  // A[]: char string array to print
  // N:   size of the array
  // fp:  file pointer, stdout or stderr for screen display
{
  int i;
  fprintf(fp,"%d\n",N);
  for (i=0; i<N; i++) fprintf(fp,"%s ",A[i]);
  fprintf(fp,"\n");
}

/////////////////////////////////////////////////////////////
// read words from a text file
/////////////////////////////////////////////////////////////
char** read_chararr_dynamic_textfile( const char infile[], int *pN )
  // returns an array of words, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
  char **A;
  char tmp[MAX_STR_LEN];
  int i;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return NULL;
  }
  else {
    // check for number of elements
    if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
      fprintf(stderr, "cannot read number of elements %s\n",infile);
      return NULL;
    }
    else {
      A = (char**)malloc(sizeof(char*)*(*pN));
      for (i=0; i<(*pN); i++) {
	if ( fscanf(fp, "%s", tmp) != 1 ) {
	  fprintf(stderr, "cannot read value at %d/%d\n",i+1,(*pN));
	  *pN = i;	// read data items
	  return A;
	}
	else {
	  //A[i] = strdup(tmp);
	  //A[i] = (char*) malloc(sizeof(char)*MAX_STR_LEN);
	  A[i] = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
	  strcpy(A[i],tmp);
	}
      }
    }
    fclose(fp);
    return A;
  }
}

/////////////////////////////////////////////////////////////
// write words to a text file
/////////////////////////////////////////////////////////////
void write_chararr_dynamic_textfile( const char outfile[], char *A[], int N )
  // write the given array of int string words, with its sie N
  // to file whose name given by outfile[]
  // uses print_chararr_dynamic
{
  FILE *fp;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file for write %s\n",outfile);
  }
  else {
    print_chararr_dynamic(fp,A,N);
    fclose(fp);
  }
}
void swap(char **a, char**b){
	char * temp = *a;
	*a =*b;
	*b = temp;
}

/////////////////////////////////////////////////////////////
// insertion sort
/////////////////////////////////////////////////////////////
void insertion_sort_chararr_dynamic ( char* arr[], int n ) {

	char key[MAX_STR_LEN];
	int j;
	for(int i=1;i<n;i++){
		strcpy(key,arr[i]);
		j = i-1;
		while(j>=0 && (strcmp(arr[j],key) > 0)){
			strcpy(arr[j+1],arr[j]);			
			j--;
		}
		strcpy(arr[j+1],key);		
	}
}



/////////////////////////////////////////////////////////////
// selection sort
/////////////////////////////////////////////////////////////
void selection_sort_chararr_dynamic(char* arr[], const int n) {
	int min;
	for(int i=0;i<n-1;i++){
		min = i;
		for(int j=i+1;j<n;j++){
			if(strcmp(arr[min],arr[j])>0)
				min = j;
		}
	swap(&arr[i],&arr[min]);
	}
}

/////////////////////////////////////////////////////////////
// bubble sort
/////////////////////////////////////////////////////////////
void bubble_sort_chararr_dynamic(char* arr[], int n) {
	for(int i=n-1;i>0;i--){
		for(int j=0;j<i;j++){		
			if(strcmp(arr[j],arr[j+1])>0) {swap(&arr[j], &arr[j+1]);}	
		}
	}
}


/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
  /* Input file name by scanf read, typed in the terminal */
{
  int i, numElements;
  char **A;	// to store data to be sorted
#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
#endif

  /* for file name, max length 1023 including path */
  int method;	// which sorting method

  if ( argc != 4 ) {
    fprintf(stderr, "%d\n",argc);
    fprintf(stderr, "usage: %s method infile outfile\n",argv[0]);
    fprintf(stderr, " method 1: insertion, 2: selection, 3: bubble\n");
    exit(0);
  }

  method = atoi(argv[1]);

  /* read text file of words:
   * number_of_intergers word1 word2 ... */
  A = read_chararr_dynamic_textfile(argv[2], &numElements);

#ifdef MEASURE_TIME
  start = clock();
#endif
  if ( A != NULL && numElements > 0 ) {
    switch ( method ) {
      case 1:	// insertion sort
	//insertion_sort(A, numElements);
	insertion_sort_chararr_dynamic(A, numElements);
	break;
      case 2:	// selection sort
	//selection_sort(A, numElements);
	selection_sort_chararr_dynamic(A, numElements);
	break;
      case 3:	// bubble sort
	//bubble_sort(A, numElements);
	bubble_sort_chararr_dynamic(A, numElements);
	break;
      default:
	break;
    }

#ifdef MEASURE_TIME
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,">> Execution time: %.5f seconds\n",cpu_time_used);
#endif

    // save results
    write_chararr_dynamic_textfile(argv[3], A, numElements);

    // once allocated, should be freed after use
    for (i=0; i<numElements; i++) free(A[i]);
    free(A);
  }
}
