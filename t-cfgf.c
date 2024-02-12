/*                               -*- Mode: C -*- 
 * Copyright (C) 2024, Mats Bergstrom
 * 
 * File name       : t-cfgf.c
 * Description     : Test of config file parser
 * 
 * Author          : Mats Bergstrom
 * Created On      : Sun Feb 11 09:48:55 2024
 * 
 * Last Modified By: Mats Bergstrom
 * Last Modified On: Mon Feb 12 18:38:05 2024
 * Update Count    : 27
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <cfgf.h>



int
tagf( int argc, const char** argv)
{
    int i;
    printf("%d : ",argc);
    for ( i = 0; i < argc;++i ) {
	printf(" \"%s\"",argv[i]);
    }
    printf("\n");
    return 0;
}


cfgf_tagtab_t ttab[] = {
			{ "abc",	0, tagf },
			{ "abcdef",	1, tagf },
			{ "abcxxx",	0, tagf },
			{ 0,0,0 }
};


int
main(int argc, const char** argv)
{
    setbuf(stdout,0);
    ++argv;
    --argc;

    if ( !argv || !*argv || !**argv ) {
	fprintf(stderr,"Usage: t-cfgf <input-file>\n");
	exit( EXIT_FAILURE );
    }

    cfgf_read_file( *argv, ttab );
}
