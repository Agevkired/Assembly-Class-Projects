/* 
  encrypt.cpp - This file contains the code to encrypt and decrypt an input string
                and output the modified string.
*/
#include "stdafx.h"
#include "key.h"	/* Okay to use the 3 symbolic names inside key.h */
#include <string.h>

__declspec(dllexport) int s_encrypt (char *src, char* dest, int en_flag);


__declspec(dllexport) int s_encrypt (char *src, char* dest, int en_flag)
{
  /* !! Put your __asm code here !! */

  __asm
{
	mov eax, 0		; zero out the result
	mov esi, src		; move the source string pointer to ESI
				; fill in your code here
	xor ecx, ecx	;start of strlen
	mov edi, src	;set to source
	not ecx			;set to -1
	sub al, al		;0 out al
	cld				;clear direction flag
repnz scasb			;scan until it hits 0
	not ecx			;to get positive number
	dec ecx			;result end of strlen
	mov edi, ecx	;use edi to count what was changed
	mov ebx, direction
	sub ebx, en_flag;determine which way to shift
	xor edx, edx 	;initialize counter
	xor eax, eax	;initialize eax
crypt: ;begin cryptography loop
	mov al, byte ptr [esi+edx] ;load character
	mov ah, al		  ;start letter check
	or ah, 20h 		  ;to lower, has more bits so no mistakes
	cmp ah, 01100001b ;compare to a
	jb endcrypt		  ;jump to end if not a letter
	cmp ah, 01111010b ;compare to z
	ja endcrypt		  ;end letter check
	cmp ebx, 0					;begin shift
	je switchshift 				;change shift direction
	sub ah, byte ptr shiftcount	;src[n] -= shiftcount
	jmp endshift
switchshift: 					
	add ah, byte ptr shiftcount ;src[n] += shiftcount
endshift:						;end shift
	cmp ah, 01100001b ;begin wrap check, compare to a
	jb wraptoend	  ;+26 if less than a
	cmp ah, 01111010b ;compare to z
	ja wraptobeg	  ;-26 if less than z
	jmp endwrap		  ;exit wrap check if within range
wraptoend:
	add ah, 26		  ;a->z+1 in a way
	cmp ah, 01100001b ;compare to a, in case shift was more than 26
	jb wraptoend	  ;repeat +26 until within range
	jmp endwrap
wraptobeg:
	sub ah, 26		  ;z->a-1 in a way
	cmp ah, 01111010b ;compare to z, in case shift was more than 26
	ja wraptobeg	  ;repeat -26 until within range
endwrap:			  ;end wrap check
	and al, 01100000b ;preserve case, remove letter
	and ah, 00011111b ;get only the letter
	or al, ah		  ;insert letter to al
	cmp invertcase, 1    ;begin switch letter case
	je casechange
	jmp endchange		 ;exit if not enabled
casechange:	
	cmp al, 97			 ;check if upper
	jae toupper
	or al, 20h 			 ;to lower
	jmp endchange		 ;exit switch letter case
toupper:
	and al, 0xdf 		 ;to upper
	jmp endchange        ;end switch letter case				 
endcrypt:
	sub edi, 1		;decrement when no letter
endchange:
	push edi					;push letter change counter
	mov edi, dest				;set to out
	mov byte ptr [edi+edx], al  ;insert result to out
	pop edi						;restore letter change counter value
	add edx, 1					;increment counter
	cmp edx, ecx				;check if it went beyond
	jl crypt
	push edi					;push letter change counter
	mov edi, dest				;set to out
	mov [edi+edx], 0			;set final+1 of out to null
	pop edi						;restore letter change counter value
	mov eax, edi				;return letter change counter
}

}