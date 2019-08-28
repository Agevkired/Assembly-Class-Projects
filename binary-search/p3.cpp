// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

int b_search (char list[100][20], int count, char* token)
{
__asm
{
	mov eax, 0			; zero out the result
	mov esi, list		; move the list pointer to ESI
						; fill in your code here
	mov eax, token 	;used for token, comparing char
	mov ebx, count 	;used for upper limit, divisor
	sub ebx, 1		;array is -1
	mov ecx, 0 		;used for lower limit, tokencounter
	mov edx, 0 		;temp number holding, and middle limit
binarysearch:
	cmp ebx, ecx
	jl endfail
	mov eax, ebx	;|/begin midpoint| move upper, [edx][eax]/ebx -> eax-quotient edx-remain
	push ebx 		; store upper
	mov ebx, 2		; divisor
	mov edx, 0 		; set upper 32 bit dividend to 0
	sub eax, ecx 	; upper-lower
	div ebx		 	; always set eax to upper-lower and edx to 0 before, result in eax, ignore remainder
	add eax, ecx	; lower+.5*distance between
	mov edx, 20		; set up multiplier
	mul edx			; list[edx][20]
	mov edx, eax 	; move result to edx-middle
	pop ebx 		;|/end midpoint| restore upper value
	mov ah, byte ptr [esi+edx] 		;|/begin comparison| move list[mid][0] to ah
	push ah							; store value from list
	push ebx						; store upper
	mov ebx, token					; eax points to token
	mov al, byte ptr [ebx] 			; move token[0] to al
	pop ebx							; restore upper
	pop ah							; restore value from list
	and ah, 01011111b				; turn both upper
	and al, 01011111b
	cmp al, ah						;|/end comparison| al-token ah-list
	jl lessthan						; token value < list
	jg greaterthan					; token value > list
;\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/	
	push ecx 					;|/start while| store lower, ecx is now list[][ecx], token[ecx]
	mov ecx, 0 					; set to beginning
checknameloop:
	add edx, ecx 				; add middle with tokencounter
	mov ah, byte ptr [esi+edx] 	; move list[mid][tokencounter] to ah
	sub edx, ecx				; subtract tokencounter
	push ah 					; store list value just in case
	push ebx 					; store upper
	mov ebx, token 				; token -> ebx
	mov al, byte ptr [ebx+ecx] 	; move token[tokencounter] to ah
	pop ebx 					; restore upper
	pop ah 						; restore list value
	and ah, 01011111b			; turn both upper
	and al, 01011111b
	cmp al, ah
	jl tokless					;if token value < list value
	jg tokmore					;if token value > list value
	cmp al, 0			;|/if equal| check if last element
	je endsuccess 		; go to success
	add ecx, 1			; increment tokencounter
	jmp checknameloop	;|/end check| restart check loop
tokmore:
	pop ecx 		;|/if token < list| restore lower
	jmp greaterthan
tokless:
	pop ecx 			;|/if token > list| restore lower
	jmp lessthan
;/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
lessthan: ;move top to middle
	mov eax, edx	;|/else| begin division setup, [edx][eax]/ebx -> eax-quotient edx-remain
	push ebx		; store upper
	mov ebx, 20		; divisor
	mov edx, 0 		; set upper 32 bit dividend to 0
	div ebx		 	; always set eax to upper-lower and edx to 0 before, result in eax, ignore remainder
	pop ebx			; restore upper
	mov ebx, eax	; set upper to middle
	sub ebx, 1 		; upper = middle - 1
	jmp binarysearch;|/end less than|
greaterthan:  ;move bottom to middle
	mov eax, edx	;|/less than| begin division setup, [edx][eax]/ebx -> eax-quotient edx-remain
	push ebx		; store upper
	mov ebx, 20		; divisor
	mov edx, 0 		; set upper 32 bit dividend to 0
	div ebx		 	; always set eax to upper-lower and edx to 0 before, result in eax, ignore remainder
	pop ebx			; restore upper
	mov ecx, eax	; set lower to middle
	add ecx, 1 		; lower = middle + 1
	jmp binarysearch;|/end else|

endsuccess: ;return position/20
	pop ecx			;|/success start| restore lower
	mov eax, edx	; begin division setup, [edx][eax]/ebx -> eax-quotient edx-remain
	mov ebx, 20		; divisor
	mov edx, 0 		; set upper 32 bit dividend to 0
	div ebx		 	; always set eax to upper-lower and edx to 0 before, result in eax, ignore remainder
	add eax, 1		; convert from 0-x to 1-x
	jmp endcode
endfail:
	mov eax, 0		; set output to 0
endcode:
	xor ebx, ebx	; clear registers
	xor ecx, ecx
	xor edx, edx					
}

}

int main(int argc, char** argv)
{
	char list[100][20], *token;
	FILE *fptr;
	int id = 0;
	int i = 0;
	
	if (argc != 3)
	{
		printf("Usage: %s filename token\n", argv[0]);
		return 1;
	}

	token = argv[2];

	printf("\n");

	fptr = fopen((argv[1]), "rtc");
	if (fptr == NULL)
      printf( "File %s was not opened\n",argv[1] );
	else
   {
      /* Set pointer to beginning of file: */
      fseek( fptr, 0L, SEEK_SET );

      /* Read data from file: */
	  while ( fscanf(fptr, "%s", &list[i]) != EOF )
	  {
          printf( "%s ", list[i] );
		  i++;
	  }

      printf( "\n\nNumber of names = %d\n", i );
      printf( "Search Token = %s\n", token );
      fclose( fptr );
   }

   id = b_search( list, i, token);

   if (id)
	   printf( "Search token is in the number %d position.\n", id );
   else
     printf( "Search token is not found.\n");

   return 0;
}



	
