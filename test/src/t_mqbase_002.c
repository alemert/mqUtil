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

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  MQHCONN hConn   ;
  MQOD    odQueue = {MQOD_DEFAULT} ;
  MQHOBJ  ohQueue ;

  sysRc = initLogging( "test/log/t_mqbase_002.log", DBG ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  doIntTest( "connect qmgr"       , \
              0                   , \
              mqConn              , \
             "TEST"               , \
              &hConn              ) ;


  memset( odQueue.ObjectName, (int) ' ', MQ_Q_NAME_LENGTH ) ;
  memcpy( odQueue.ObjectName, "TEST.MQBASE", MQ_Q_NAME_LENGTH ) ;

  doIntTest( "open queue"         , \
              0                   , \
              mqOpenObject        , \
              hConn               , \
              &odQueue            , \
              MQOO_INPUT_AS_Q_DEF   |
              MQOO_FAIL_IF_QUIESCING,
              &ohQueue            ) ;

  doIntTest( "put message err" ,
      0      ,
      mqPut ) ;

  doIntTest( "disconnect qmgr"    , \
              0                   , \
              mqDisc              , \
              &hConn              ) ;
#endif

_door:
  return sysRc ;
}
