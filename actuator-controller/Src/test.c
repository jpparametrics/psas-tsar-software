// tsar_test.c
// Portland State Aerospace Society
// TSAR Capstone 2019-2020
// TODO Update Test header fiel
// Change Log
// 	-Creation of Document 5/17/2020 [APJ]
//
//	This file contains methods for the TEST
//  state.
//  Test has two verification Methods
//  It first checks that both current and previous states are valid
//  It then checks if the expected state is the state passed
//  At this point the valves are opened and a log entry is created
//
//	References:
//
//
//  System Risk Factor = 0.33 (Catastrophic, Unlikely)
#include "test.h"

uint32_t Test(struct StateVars *ctrl)
{
	uint32_t success = FALSE;
	ctrl->valveConfiguration = StateConfiguration();
	ctrl->valveTarget  = ((uint16_t)VV1 	\
			 |(uint16_t)VV2);
    if(VerifyState(ctrl->currentState) && VerifyState(ctrl->lastState))
    {
    	if((ctrl->currentState & TEST) == TEST){
    		// PV1 PV2 PV3 VV1 VV2 IV1 IV2 MV1 MV2
    		// | 0| 0|  0|  1|  1|  0|  0|  0|  0

    	    // If this is the first time, initialize state
    		if(ctrl->currentState != ctrl->lastState)
    	    {
    			success = StateInitialize(ctrl);
    	    }

    		// OnTick
    		success = SendStatusMessage(ctrl);

    		// Increment state counter
			ctrl->stateCounter++;
			if(ctrl->stateCounter >= 4294967295) ctrl->stateCounter = 0;
    	}else{
    		//Log Expected State != Passed State
    		Get_State_Disagree_Error_Msg(TxMessageBuffer1, TEST, ctrl->currentState);
    		UART_SendMessage(&hlpuart1,TxMessageBuffer1);

    	}
    }else{
    	// Log Invalid State
    	Get_Invalid_State_Error_Msg(TxMessageBuffer1, ctrl->currentState, ctrl->lastState);
    	UART_SendMessage(&hlpuart1, TxMessageBuffer1);
    }
	return success;
}
