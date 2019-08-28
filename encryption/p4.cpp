// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

#include "encrypt.h"

int main(int argc, char** argv)
{
	char *in_string, out_string[128];
	int enc_flag;
	int rc = 0;
	
	if (argc != 3)
	{
		printf("Usage: %s input_string encrypt_flag\n", argv[0]);
		return 1;
	}

	in_string = argv[1];
	enc_flag = atoi(argv[2]);
	enc_flag = (enc_flag == 0) ? 0 : 1;

  rc = s_encrypt( in_string, out_string, enc_flag);
	printf( "Source string = %s\n", in_string);
	printf( "Target string = %s\n", out_string);
 	printf( "Number of characters converted = %d\n", rc );
 
  return rc;
}
