#ifndef TIMEDOCTOR_H
#define TIMEDOCTOR_H

#include <stdint.h>

#include "TimeDoctor_config.h"



////////////////// Tracing control functions //////////////////

// starts a new TimeDoctor trace session
// place as soon as possible
// well before the first OS object is created
// but after the clocks are set up
void TimeDoctor_START();

// stops the current TimeDoctor trace session
void TimeDoctor_STOP();

// outputs the TimeDoctor trace session char by char via the supplied putchar_function
// may take a while, think about watchdogs etc..
void TimeDoctor_SAVE( int (*putchar_function)(int) );



////////////////////// User Agents //////////////////////////

// a flag is used to mark the duration of a user defined event in the trace

// creates a new user agent with a unique uxFlagNumber and a name.
void TimeDoctor_UserAgentCreate( uint32_t uxUserAgentNumber, char *name);

// adds the beginning of user agent uxUserAgentNumber into the trace.
void TimeDoctor_UserAgentBegin( uint32_t uxUserAgentNumber );

// adds the end of user agent uxUserAgentNumber into the trace.
void TimeDoctor_UserAgentEnd( uint32_t uxUserAgentNumber );



////////////////////// Flags //////////////////////////

// a flag is used to mark the timestamp of a user defined event in the trace

// creates a new flag with a unique uxFlagNumber and a name.
void TimeDoctor_FlagCreate( uint32_t uxFlagNumber, char *name);

// Adds the occurrence of flag uxFlagNumber into the trace.
void TimeDoctor_Flag( uint32_t uxFlagNumber );



////////////////// adding a string, number, or color to a flag or user agent block //////////////////

// these are optional immediately after the begin of a user agent or the occurrence of a flag

// draw the user agent block in a certain color (0..7)
void TimeDoctor_AddColor( int color );

// add a string message to the flag / user agent block
// visible when mouse hovering
void TimeDoctor_AddString( char *msg );

// add a number to the flag / user agent block
// visible when mouse hovering
void TimeDoctor_AddNumber( int number );




////////////////// FreeRTOS tracing support //////////////////

#if defined(TD_USE_FREERTOS) && (TD_USE_FREERTOS==1)

// The FreeRTOS related API functions will be automatically 
// called by the FreeRTOS trace facility when enabled and
// TimeDoctor_FreeRTOS.h is included in FreeRTOSConfig.h

#include "TimeDoctor_FreeRTOS.h"

#endif // defined(TD_USE_FREERTOS) && (TD_USE_FREERTOS==1)

#endif
