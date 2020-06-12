// pre_chill.h
// Portland State Aerospace Society
// TSAR Capstone 2019-2020
//
// Change Log
// 	-Creation of Document 2/11/2020 [APJ]
//
//	This is the header file for pre_chill.c
//
//	References:
//
//
//  System Risk Factor = 0.33 (Catastrophic, Unlikely)

#ifndef PRE_CHILL_H
#define PRE_CHILL_H

#include "states_def.h"
#include "utilities.h"
#include "messages.h"

uint32_t PreChill(struct StateVars (*));

#endif // PRE_CHILL_H
