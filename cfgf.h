/*                               -*- Mode: C -*- 
 * Copyright (C) 2024, Mats Bergstrom
 * 
 * File name       : cfgf.h
 * Description     : Config file parser
 * 
 * Author          : Mats Bergstrom
 * Created On      : Sun Feb 11 09:48:01 2024
 * 
 * Last Modified By: Mats Bergstrom
 * Last Modified On: Mon Feb 12 18:36:59 2024
 * Update Count    : 5
 */


#ifndef __CFGF_H__
#define __CFGF_H__ (1)

typedef int cfgf_tagf_t( int argc, const char** argv );

typedef struct {
    const char*		tag;
    int			argc;
    cfgf_tagf_t*	func;
} cfgf_tagtab_t;

int cfgf_read_file(const char* cfg, const cfgf_tagtab_t* tab);

#endif
