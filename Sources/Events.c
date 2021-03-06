/* ###################################################################
**     Filename    : Events.c
**     Project     : project3
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-03-13, 11:06, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "rtos_main_task.h"
#include "os_tasks.h"

#ifdef __cplusplus
extern "C" {
#endif 


extern _pool_id char_message_pool;
/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Callback    : myUART_RxCallback
**     Description : This callback occurs when data are received.
**     Parameters  :
**       instance - The UART instance number.
**       uartState - A pointer to the UART driver state structure
**       memory.
**     Returns : Nothing
** ===================================================================
*/
void myUART_RxCallback(uint32_t instance, void * uartState)
{

		CHAR_MESSAGE_PTR msg_ptr;
		_queue_id          client_qid;
		bool            result = FALSE;


		msg_ptr = ( CHAR_MESSAGE_PTR )_msg_alloc( char_message_pool );
		if ( msg_ptr == NULL ){printf( "\nCould not allocate a message for RxCall back\n" );_task_block();}

		msg_ptr->HEADER.SOURCE_QID = client_qid;
		msg_ptr->HEADER.TARGET_QID = _msgq_get_id( 0, TRANSMIT_QUEUE );
		msg_ptr->HEADER.SIZE = sizeof(MESSAGE_HEADER_STRUCT) +
		         strlen((char *)msg_ptr->DATA) + 1;

		msg_ptr->DATA[0] = (myRxBuff[0]);
		msg_ptr->DATA[1] = 0;

		result = _msgq_send(msg_ptr);

		if (result != TRUE) {
			printf("\nCould not send a message\n");
		 	 _task_block();
	  	}


}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
