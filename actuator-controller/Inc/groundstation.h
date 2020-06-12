// groundstation.h
// Portland State Aerospace Society
// TSAR Capstone 2019-2020
//
// Change Log
// 	-Creation of Document 2/11/2020 [APJ]
//
//	This is the header file for groundstation.c
//
//	References:
//
//
//  System Risk Factor = 0.33 (Catastrophic, Unlikely)

#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include "states_def.h"
#include "utilities.h"
#include "messages.h"

uint32_t Groundstation(struct StateVars (*));

#endif // GROUNDSTATION_H
