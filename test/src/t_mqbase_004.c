/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*                                                                            */
/* testing functions :                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// std
// ---------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <errno.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include "tutl.h"
#include <ctl.h>
#include <mqbase.h>

#include <cmqc.h>

#include <stdlib.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  MQHCONN hConn   ;
  MQOD    odQueue = {MQOD_DEFAULT} ;
  MQMD    md      = {MQMD_DEFAULT} ;
  MQHOBJ  ohQueue ;

  sysRc = initLogging( "test/log/t_mqbase_004.log", DBG ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // put test
  // -------------------------------------------------------
#if(1)
  mqConn( "TEST", &hConn );

  memset( odQueue.ObjectName, (int) ' ', MQ_Q_NAME_LENGTH ) ;
  memcpy( odQueue.ObjectName, "TEST.MQBASE", MQ_Q_NAME_LENGTH ) ;

  mqOpenObject( hConn, &odQueue, MQOO_OUTPUT           |
                                 MQOO_INPUT_AS_Q_DEF   |
                                 MQOO_FAIL_IF_QUIESCING, &ohQueue ) ;

  mqPut( hConn, ohQueue, &md, NULL, "a long hello world to evrybody", 0 ) ;

  mqCloseObject( hConn, &ohQueue ) ;
#endif

  // -------------------------------------------------------
  // get test
  // -------------------------------------------------------
#if(1)

  memset( odQueue.ObjectName, (int) ' ', MQ_Q_NAME_LENGTH ) ;
  memcpy( odQueue.ObjectName, "TEST.MQBASE", MQ_Q_NAME_LENGTH ) ;

  mqOpenObject( hConn, &odQueue, 
              MQOO_OUTPUT           |
              MQOO_INPUT_AS_Q_DEF   |
              MQOO_FAIL_IF_QUIESCING,
              &ohQueue            ) ;

  char *buffer = (char*) malloc( 10 ) ;
  MQLONG bufLen = 10 ;

  doIntTest( "get message err" ,
              2080        ,
              mqGet    ,
              hConn    ,
              ohQueue  ,
              buffer   ,
              &bufLen  ,
              &md      ,
              _gDefGMO ,
              0    );

//printf( "%s\n", buffer ) ;

  mqCloseObject( hConn, &ohQueue ) ;

  mqDisc( &hConn ) ;

#endif

_door:
  return sysRc ;
}
