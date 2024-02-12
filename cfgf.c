/*                               -*- Mode: C -*- 
 * Copyright (C) 2024, Mats Bergstrom
 * 
 * File name       : cfgf.c
 * Description     : Simple config file
 * 
 * Author          : Mats Bergstrom
 * Created On      : Mon Feb 12 18:31:01 2024
 * 
 * Last Modified By: Mats Bergstrom
 * Last Modified On: Mon Feb 12 22:17:21 2024
 * Update Count    : 12
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "cfgf.h"

#define CFGF_FBUF_MAX	(512)
static char	cfgf_fbuf[ CFGF_FBUF_MAX ];
#define CFGF_ARG_MAX		(16)
static char*	cfgf_arg[ CFGF_ARG_MAX ];



static char*
cfgf_skip_ws(char* s)
{
    while ( *s && isspace(*s) )
	++s;
    return s;
}

static char*
cfgf_skip_bs(char* s)
{
    while ( *s && !isspace(*s) )
	++s;
    return s;
}

static void
cfgf_chomp(char* s)
{
    while(*s) {
	if ( (*s == '\n') && !*(s+1) ) {
	    *s = 0;
	    return;
	}
	++s;
    }
}


static int
cfgf_parse_line(char* s,  const cfgf_tagtab_t* tab)
{
    unsigned n = 0;
    int argc = 0;
    char* e;
    size_t sl;

    cfgf_chomp(s);
    
    s = cfgf_skip_ws(s);
    if ( !*s )
	return 0;
    if ( *s == '#' )
	return 0;

    e = cfgf_skip_bs(s);
    sl = e-s;

    for ( n = 0; tab[n].tag; ++n ) {
	size_t tl = strlen( tab[n].tag );
	if ( !tl )
	    return -1;
	if ( tl == sl &&
	     !strncmp(  tab[n].tag, s, sl ) )
	    break;
    }

    /* Did we get a match? */
    if ( !tab[n].tag )
	return -1;			/* Nope.  No match. */


    while ( *s ) {
	cfgf_arg[argc] = s;
	++argc;

	if ( argc > tab[n].argc ) {
	    break;
	}

	if ( !*e )			/* At end, too few arguments */
	    return -1;

	*e = 0;				/* Terminate arg[argc] */
	++e;
	s = cfgf_skip_ws(e);
	if ( !*s )
	    return -1;			/* At end too few arguments */

	e = cfgf_skip_bs(s);
    }

    if ( argc <= tab[n].argc )		/* Too few arguments */
	return -1;

    if ( !tab[n].func )
	return 0;			/* Silent Ignore. */

    return tab[n].func( argc, (const char**)(cfgf_arg) ); /* Dispatch! */
}



int
cfgf_read_file(const char* cfg, const cfgf_tagtab_t* tab)
{
    int bad = 0;
    FILE* f = fopen(cfg,"r");
    unsigned int n = 0;
    int i;
    while ( f && !feof(f) ) {
	char* s = fgets( cfgf_fbuf, CFGF_FBUF_MAX-1, f );
	if ( !s )
	    break;
	++n;
	i = cfgf_parse_line(s,tab);
	if ( i ) {
	    bad = -1;
	    fprintf(stderr,"Bad config line: %u, \"%s\"\n", n, s);
	}
    }
    fclose(f);
    return bad;
}
