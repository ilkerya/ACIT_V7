
/********************************************************************
 FileName:     	Acit.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Select one target compiler if Panasonic is selected abs function is included not found in math.h!!
        Acit Memory and Functions optins to realize Memory Usage Only!!
		while using .net environment be sure that .net CLI exists on the target computer!
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
  1.2   11.09.2012

  *********************************************************************/
 #define  VERSION_NO  11111111
//#define MANAGED_DOTNET_COMPILER   // default 1. priority  SELECT ONLY ONE
//#define MICROCHIP_COMPILER    //  2. priority  PIC32
//#define PANASONIC_COMPILER     //  3. priority MN103S 32 BIT

//#define ACIT_INCLUDED  // TO ADD  INITIAL MEMORY USAGE WITHOUT ANY ACIT LIBRARY
//#define ACIT_MEMORY     // TO ADD  ONLY ACIT  MEMORY USAGE
//#define ACIT_FUNCTIONS  // TO ADD  TOTAL  ACIT  MEMORY USAGE

#if (defined MANAGED_DOTNET_COMPILER) // TO BE SURE IF ONLY ONE COMPILER SELECTED
				#define BOOL bool
			/* bool is appropriate for .net however bool type is appropriate for MICROCHIP and most other cross-compilers
			In order to keep consistency we define BOOL as bool*/
	#if (defined MICROCHIP_COMPILER || defined PANASONIC_COMPILER )
		#error  SELECT APPROPRIATE COMPILER !!
	#endif
#endif
#if (defined MICROCHIP_COMPILER) // TO BE SURE IF ONLY ONE COMPILER SELECTED
	#if (defined MANAGED_DOTNET_COMPILER || defined PANASONIC_COMPILER )
		#error  SELECT APPROPRIATE COMPILER !!
	#endif
#endif
#if (defined PANASONIC_COMPILER) // TO BE SURE IF ONLY ONE COMPILER SELECTED
	#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER )
		#error  SELECT APPROPRIATE COMPILER !!
	#endif
		signed char abs(signed char Data){ // no any abs function !! fix for bug at panasonic
			if (Data >= 0 )return Data;
			else return (Data *= -1);
		}
#endif

#if (defined ACIT_INCLUDED && defined ACIT_MEMORY)

		#include "Definitions.h"
		#include "Prototype.h"
		#include "Structures.h"	// Compresor Drive (cycle) Functions
		#include "Tables_General.h"	// Compresor Drive (cycle) Functions
		#include "Tables_Comp.h"	// Compresor Drive (cycle) Functions
		#include "MemoryCom.h" //
		#if !(defined MANAGED_DOTNET_COMPILER)  // NO NEED FOR PC OPERATION
				#include "LookupTables.h" // 4620 K // INCLUDES DRIVER LOOKUPTABLES
		#endif
#endif
#if (defined ACIT_INCLUDED && defined ACIT_FUNCTIONS)

 		#include "Compressor.h"
 		#include "Reliability.h"
 		#include "Mode.h"
		#include "Decisions.h" // for all decisions
		#include "Defrost.h" //
		#include "EEV_Comp.h"
		#include "EEV.h" //
		#include "Fan.h" //    11117 bytes
		#include "Errors.h" //

#endif
