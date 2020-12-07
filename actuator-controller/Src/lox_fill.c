// tsar_lox_fill.c
// Portland State Aerospace Society
// TSAR Capstone 2019-2020
// TODO  UPDATE THIS
// Change Log
// 	-Creation of Document 5/17/2020 [APJ]
//
//	This file contains methods for the Lox Fill
//  state.
//  LoxFill has two verification Methods
//  It first checks that both current and previous states are valid
//  It then checks if the expected state is the state passed
//  At this point the valves are opened and a log entry is created
//
//	References:
//
//
//  System Risk Factor = 0.33 (Catastrophic, Unlikely)
#include "lox_fill.h"

uint32_t LoxFill(struct StateVars *ctrl)
{
	uint32_t success = FALSE;
	ctrl->valveConfiguration = StateConfiguration();
	ctrl->valveTarget  =

	

    if(VerifyState(ctrl->currentState) && VerifyState(ctrl->lastState))
    {
    	if((ctrl->currentState & LOX_FILL) == LOX_FILL){
    		// PV1 PV2 PV3 VV1 VV2 IV1 IV2 MV1 MV2
    		// | 0| 1| 1 | 0 | 0 | 1 | 1 | 1 | 10
    		valve_target |= ((uint16_t)PV2	\
    					 |(uint16_t)PV3		\
						 |(uint16_t)IV1		\
						 |(uint16_t)IV2		\
						 |(uint16_t)MV1		\
						 |(uint16_t)MV2);

    		valve_configuration = StateConfiguration();

    		// Change State conditions
    		ctrl->lastState = ctrl->currentState;
    		ctrl->currentState =LOX_FILL;
    		success = (valve_configuration == valve_target ? TRUE : FALSE);
    		// Create Message and Transmit
    		Get_Valve_State_Status_Msg(TxMessageBuffer1,valve_configuration,success);
    		UART_SendMessage(&hlpuart1, TxMessageBuffer1);
    	}else{
    		// Log Expected State != Passed State
    		Get_State_Disagree_Error_Msg(TxMessageBuffer1, LOX_FILL, ctrl->currentState);
    		UART_SendMessage(&hlpuart1, TxMessageBuffer1);
    	}
    }else{
    	// Log Invalid State
    	Get_Invalid_State_Error_Msg(TxMessageBuffer1, ctrl->currentState, ctrl->lastState);
    	UART_SendMessage(&hlpuart1, TxMessageBuffer1);
    }
	return success;
}
