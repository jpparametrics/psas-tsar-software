// tsar_setup_ops.c
// Portland State Aerospace Society
// TSAR Capstone 2019-2020
//
// Change Log
// 	-Creation of Document 2/11/2020 [APJ]
//
//	This file contains methods for the Setup Operations
//  state.
//  SetupOps has two verification Methods
//  It first checks that both current and previous states are valid
//  It then checks if the expected state is the state passed
//  At this point the valves are opened and a log entry is created
//
//	References:
//
//
//  System Risk Factor = 0.33 (Catastrophic, Unlikely)
#include "setup_ops.h"

uint32_t SetupOps(struct StateVars *ctrl)
{
	uint32_t success = FALSE;
	uint32_t valve_configuration = 0;
	uint32_t valve_target = 0;
	uint32_t now = HAL_GetTick();
	uint32_t TIMEOUT = 2000;
	char message[256];
	char *msgPtr = message;

    if(ctrl->currentState != ctrl->lastState)
    {
    	ctrl->timeStarted = HAL_GetTick();
    }

    if(VerifyState(ctrl->currentState) && VerifyState(ctrl->lastState))
    {
    	if((ctrl->currentState & SETUP_OPS) == SETUP_OPS){
    		// PV1 PV2 PV3 VV1 VV2 IV1 IV2 MV1 MV2
    		// 11 |11 |11 |11 |11 |11 |11 |11 |11

    		// Set Valve States
    		valve_target |= ((uint16_t)VV1 	\
						 |(uint16_t)VV2);
    		// Timestamp and Log
    		ValveStateSetter(valve_target);
    		valve_configuration = StateConfiguration();

    		// Change State conditions
    		ctrl->lastState = ctrl->currentState;
    		ctrl->currentState =SETUP_OPS;
    		success = (valve_configuration == valve_target ? TRUE : FALSE);
    		// Create Message and Transmit
    		Get_Valve_State_Status_Msg(msgPtr,valve_configuration,success);
    		UART_SendMessage(&hlpuart1, msgPtr);

    		//TODO Specify time frame
    		if(now - ctrl->timeStarted > TIMEOUT)
    		{
        		ctrl->currentState=SITE_CLEAR_AND_START_UP;
    		}

    	}else{
    		//Log Expected State != Passed State
    		Get_State_Disagree_Error_Msg(msgPtr, SETUP_OPS, ctrl->currentState);
    		UART_SendMessage(&hlpuart1,msgPtr);

    	}
    }else{
    	    	// Log Invalid State
    	Get_Invalid_State_Error_Msg(msgPtr, ctrl->currentState, ctrl->lastState);
    	UART_SendMessage(&hlpuart1, msgPtr);
    }
	return success;
}
