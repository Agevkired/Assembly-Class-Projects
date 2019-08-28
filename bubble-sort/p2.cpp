// p2.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

int sorter (int* list, int count, int opcode)
{
__asm
{
	mov eax, 0			; zero out the result
	mov ebx, opcode		; move opcode to ebx for comparison
						; fill in your code here
	mov eax, list	;eax holds list

begin_sort:
	mov ecx, 0 ;COUNTER
cont:
	mov edx, [eax+(4*ecx)] ;load list[n]
	inc ecx 			   ;n+1
	cmp ebx, 1 			   ;check to see if asc or dsc
	jne dsc_comp
	cmp edx, [eax+(4*ecx)] ;if n>n+1  start asc comparison
	jle skip_swap
	jmp swap
dsc_comp:
	cmp edx, [eax+(4*ecx)] ;if n<n+1  start dsc comparison
	jge skip_swap
swap:
	push edx 				;push n
	mov edx, [eax+(4*ecx)]  ;n+1 -> edx
	dec ecx 				;n
	mov [eax+(4*ecx)], edx  ;edx -> n
	pop edx 				;previous n -> edx
	inc ecx 				;n+1
	mov [eax+(4*ecx)], edx  ;edx ->n+1
skip_swap:			
	mov edx, count  ;check if counter hit array size, inc for next round
	dec edx
	cmp ecx, edx 	;if last element was touched, go to check order
	jne cont
	mov ecx, 0 		;counter to 0 for checking
	cmp ebx, 1 		;check which order to use
	jne test_dsc
test_asc:
	mov edx, [eax+(4*ecx)] ;load list[n]
	inc ecx
	cmp edx, [eax+(4*ecx)] ;redo sort if [i]>[i+1]
	jg begin_sort
	mov edx, count		   ;check if counter hit array size
	dec edx
	cmp ecx, edx		   ;if counter hit array size, end sort
	jne test_asc
	jmp end_sort
test_dsc:
	mov edx, [eax+(4*ecx)] ;load list[n]
	inc ecx
	cmp edx, [eax+(4*ecx)] ;redo sort if [i]>[i+1]
	jl begin_sort	
	mov edx, count		   ;check if counter hit array size
	dec edx
	cmp ecx, edx		   ;if counter hit array size, end sort
	jne test_dsc
	jmp end_sort
end_sort:
}

}

int main(int argc, char** argv)
{
	int testarr[4] = {1, 2, 4, 3};
	int n=4;
	int testarr2[10] = {10, -20, 5, 12, 30, -5, -22, 55, 52, 0};
	int m=10;
	int numlist[1000], asc;
	FILE *fptr;

	int i = 0;
	
	if (argc != 3)
	{
		printf("Usage: %s filename asc_des\n", argv[0]);
		return 1;
	}

	asc = atoi (argv[2]);
	asc = (asc == 1) ? 1 : 2; //if asc==1, then asc = 1, else asc = 2

	printf("\n");

	fptr = fopen((argv[1]), "rtc");
	if (fptr == NULL){
      printf( "File %s was not opened\n",argv[1] );
		return 9;}
	else
   {
      /* Set pointer to beginning of file: */
      fseek( fptr, 0L, SEEK_SET );

      /* Read data from file: */
	  while ( fscanf(fptr, "%d", &numlist[i]) != EOF )
	  {
          printf( "%d ", numlist[i] );
		  i++;
	  }

      printf( "\n\nNumber of integer = %d\n", i );
      printf( "Ascend_or_Descend = %d\n\n", asc );
      fclose( fptr );
   }

   sorter( numlist, i, asc);
   //sorter( testarr, n, 1);
   //sorter( testarr2, m, 1);

   for (int j = 0; j < i; j++)
          printf( "%d ", numlist[j] );

/*   for (int j = 0; j < n; j++)
	   printf( "%d ", testarr[j] );
   printf("\n");
   for (int j = 0; j < m; j++)
	   printf( "%d ", testarr2[j] );
   printf("\n");
*/
   return 0;
}
