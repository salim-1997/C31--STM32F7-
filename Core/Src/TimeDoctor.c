#include <stdio.h>

#include "TimeDoctor.h"



char buffer[TIMEDOCTOR_BUFFER_SIZE];
int buffer_used;

uint32_t lock;	// 0: avail 1: taken

// see https://developer.arm.com/documentation/dht0008/a/arm-synchronization-primitives/practical-uses/implementing-a-mutex
// and https://electronics.stackexchange.com/questions/141673/how-to-implement-critical-sections-on-arm-cortex-a9

int32_t atomic_swap(uint32_t *dest, uint32_t new_value)
{
	int32_t old_value;
	do
	{
		__CLREX();
		old_value = __LDREXW(dest);
	} while(__STREXW(new_value,dest));
	__DMB();
	return old_value;
}

int lock_acquire(uint32_t* lock)
{
	while( atomic_swap(lock, 1)!=0 ) {
		__WFE();
	}
	return 1;
}

void lock_release(uint32_t* lock)
{
	*lock = 0;
	__DMB();
	__SEV();
}



#define PROLOG0()	uint32_t prim = __get_PRIMASK(); __set_PRIMASK(1); {
#define PROLOG()	uint32_t prim = __get_PRIMASK(); __set_PRIMASK(1); if(buffer_used < sizeof(buffer)-64) {
#define EPILOG()	} __set_PRIMASK(prim);




void TimeDoctor_START()
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "SPEED %lu\r\n", TD_GET_TICK_FREQ() );
	buffer_used += sprintf( buffer+buffer_used, "MEMSPEED %lu\r\n", TD_GET_TICK_FREQ() );
	buffer_used += sprintf( buffer+buffer_used, "TIME %lu\r\n", TD_GET_TICK_FREQ() );

	TD_INIT_TICK();

	EPILOG();
}

void TimeDoctor_STOP()
{
	PROLOG0();

	EPILOG();
}

void TimeDoctor_SAVE( int(*putchar_function)(int) )
{

	for( int i=0; i<buffer_used; ++i ) {
		putchar_function(buffer[i]);
	}
	putchar_function('E');
	putchar_function('N');
	putchar_function('D');
	putchar_function('\n');
}



////////////////////// User Agent //////////////////////////

void TimeDoctor_UserAgentCreate ( uint32_t uxUserAgentNumber, char *name)
{
	PROLOG();

//	buffer_used += sprintf( buffer+buffer_used, "CRE 8 %lu %lu\r\n", uxUserAgentNumber, TD_GET_TICK() );
	buffer_used += sprintf( buffer+buffer_used, "NAM 8 %lu %s\r\n", uxUserAgentNumber, name );

	EPILOG();
}

void TimeDoctor_UserAgentBegin( uint32_t uxUserAgentNumber )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STA 8 %lu %lu\r\n", uxUserAgentNumber, TD_GET_TICK() );

	EPILOG();
}

void TimeDoctor_UserAgentEnd( uint32_t uxUserAgentNumber )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STO 8 %lu %lu\r\n", uxUserAgentNumber, TD_GET_TICK() );

	EPILOG();
}




void TimeDoctor_FlagCreate( uint32_t uxFlagNumber, char *name)
{
	PROLOG();

//	buffer_used += sprintf( buffer+buffer_used, "CRE 7 %lu %lu\r\n", uxFlagNumber, TD_GET_TICK() );
	buffer_used += sprintf( buffer+buffer_used, "NAM 7 %lu %s\r\n", uxFlagNumber, name );

	EPILOG();
}

void TimeDoctor_Flag( uint32_t uxFlagNumber )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "OCC 7 %lu %lu\r\n", uxFlagNumber, TD_GET_TICK() );

	EPILOG();
}


void TimeDoctor_AddString( char *msg )
{
	//TODO: make this atomic to the Flag / UserAgent
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "DSC 0 0 %s\r\n", msg );

	EPILOG();
}

void TimeDoctor_AddNumber( int number )
{
	//TODO: make this atomic to the Flag / UserAgent
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "DSC 1 1 %i\r\n", number );

	EPILOG();
}

void TimeDoctor_AddColor( int color )
{
	//TODO: make this atomic to the Flag / UserAgent
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "DSC 3 3 %i\r\n", color );

	EPILOG();
}


