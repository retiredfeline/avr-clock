typedef	unsigned char	uchar;
typedef unsigned int	uint;

#define	TICKSINHALFSEC	(TICKSINSEC/2)
#define	TICK		4			// ms, roughly
#define	DEPMIN		(50 / TICK)		// depress debounce period
#define	RELMIN		(100 / TICK)		// release debounce period
#define	RPTTHRESH	((400 / TICK) + 1)	// repeat threshold after debounce
#define	RPTPERIOD	(250 / TICK)		// repeat period
#define	BUTTON_TIMEOUT	(64000u / TICK)		// revert to Time mode after 64 seconds

#ifdef	AT90S8515
#include "at90s8515.h"
#endif	// AT90S8515

#ifdef	ATMEGA163
#include "atmega163.h"
#endif	// ATMEGA163
