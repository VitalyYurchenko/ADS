//
//  spell.h
//  ADS
//
//  Created by Vitaly Yurchenko on 9/1/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_spell_h
#define ADS_spell_h

// ********************************************************************************************************************************************************** //

/* Define the maximum size for words in the dictionary. */
#define SPELL_SIZE 31

/* Public Interface. */
int spell(char (*dictionary)[SPELL_SIZE], int size, const char *word);

// ********************************************************************************************************************************************************** //

#endif
