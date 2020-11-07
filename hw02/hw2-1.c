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
// HW 2-1 USING CHAR[][]

#include<stdio.h>
#include<stdlib.h>	// atoi
#include<string.h>	// string library

// maximum number of words
#define MAX_NUM_STR	4096

// maximum length of a single string
#define MAX_STR_LEN	256

/////////////////////////////////////////////////////////////
// print char array array
/////////////////////////////////////////////////////////////
void print_chararr_2dim( FILE *fp, char A[][MAX_STR_LEN], int N )
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
void read_chararr_2dim_textfile( const char infile[], 
    char A[][MAX_STR_LEN], int *pN )
  // returns an array of words, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
  int i;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return;
  }
  else {
    // check for number of elements
    if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
      fprintf(stderr, "cannot read number of elements %s\n",infile);
      return;
    }
    else {
      if ( *pN > MAX_NUM_STR ) {
	fprintf(stderr, "cannot read %d words (%d > %d)\n",*pN,*pN,MAX_NUM_STR);
	return;
      }
      for (i=0; i<(*pN); i++) {
	if ( fscanf(fp, "%s", A[i]) != 1 ) {
	  fprintf(stderr, "cannot read value at %d/%d\n",i+1,(*pN));
	  *pN = i;	// read data items
	  return;
	}
      }
    }
    fclose(fp);
  }
}

/////////////////////////////////////////////////////////////
// write words to a text file
/////////////////////////////////////////////////////////////
void write_chararr_2dim_textfile( const char outfile[], 
    char A[][MAX_STR_LEN], int N )
  // write the given array of int string words, with its sie N
  // to file whose name given by outfile[]
  // uses print_chararr_2dim
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
    print_chararr_2dim(fp,A,N);
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
void insertion_sort_chararr_2dim ( char arr[][MAX_STR_LEN], int n ) {

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
void selection_sort_chararr_2dim(char arr[][MAX_STR_LEN], const int n) {
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
void bubble_sort_chararr_2dim(char arr[][MAX_STR_LEN], int n) {
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
  int numElements;
  char A[MAX_NUM_STR][MAX_STR_LEN];	// to store data to be sorted

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
  read_chararr_2dim_textfile(argv[2], A, &numElements);


  if ( numElements > 0 && numElements <= MAX_NUM_STR ) {
    switch ( method ) {
      case 1:	// insertion sort
	//insertion_sort(A, numElements);
	insertion_sort_chararr_2dim(A, numElements);
	break;
      case 2:	// selection sort
	//selection_sort(A, numElements);
	selection_sort_chararr_2dim(A, numElements);
	break;
      case 3:	// bubble sort
	//bubble_sort(A, numElements);
	bubble_sort_chararr_2dim(A, numElements);
	break;
      default:
	break;
    }

    // save results
    write_chararr_2dim_textfile(argv[3], A, numElements);
  }
}
