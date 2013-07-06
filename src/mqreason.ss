/******************************************************************************/
/*                                                                            */
/*                             M Q   R E A S O N S                            */
/*                                                                            */
/******************************************************************************/

#include <cmqc.h>

#include <mqreason.h>

#define convert( str) case str : return #str  ;

const char* mqrc2str( int reason )
{
  switch( reason )
  {    

