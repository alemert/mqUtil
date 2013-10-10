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

  sysRc = initLogging( "test/log/t_mqbase_005.log", DBG ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // put test
  // -------------------------------------------------------
#if(1)
  mqConn( "ALFA", &hConn );

  memset( odQueue.ObjectName, (int) ' ', MQ_Q_NAME_LENGTH ) ;
  memcpy( odQueue.ObjectName, "NOT.EXISTS.ON.OMEGA", MQ_Q_NAME_LENGTH ) ;

  mqOpenObject( hConn, &odQueue, MQOO_OUTPUT           |
                                 MQOO_FAIL_IF_QUIESCING, &ohQueue ) ;

  mqPut( hConn, ohQueue, &md, NULL, "go to dlq", 0 ) ;

  mqCloseObject( hConn, &ohQueue ) ;
  mqDisc( &hConn ) ;
#endif

  // -------------------------------------------------------
  // get test
  // -------------------------------------------------------
#if(1)

  mqConn( NULL, &hConn );
  memset( odQueue.ObjectName, (int) ' ', MQ_Q_NAME_LENGTH ) ;
  memcpy( odQueue.ObjectName, "SYSTEM.ADMIN.QMGR.EVENT", MQ_Q_NAME_LENGTH ) ;

  mqOpenObject( hConn, &odQueue, 
              MQOO_INPUT_AS_Q_DEF   |
              MQOO_FAIL_IF_QUIESCING,
              &ohQueue            ) ;

  MQHBAG bag;

  doIntTest( "open bag" ,
              0         ,
              mqOpenBag ,
              &bag     );

  MQGMO gmo ={MQGMO_DEFAULT} ;
#if(0)
  gmo.Options = MQGMO_WAIT              // wait for new messages
              + MQGMO_FAIL_IF_QUIESCING // fail if quiesching
              + MQGMO_CONVERT           // convert if necessary
              + MQGMO_BROWSE_NEXT;      // browse messages
#endif


  doIntTest( "read bag" ,
              0         ,
              mqReadBag ,
              hConn     ,
              ohQueue  ,
              &md       ,  
              &gmo,
              bag      );

  doIntTest( "open bag" ,
              0         ,
              mqCloseBag ,
              &bag     );

  mqCloseObject( hConn, &ohQueue ) ;

  mqDisc( &hConn ) ;

#endif

_door:
  return sysRc ;
}
