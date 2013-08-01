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
  MQMD    md      = {MQMD_DEFAULT} ;
  MQHOBJ  ohQueue ;

  sysRc = initLogging( "test/log/t_mqbase_002.log", DBG ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // put test
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
              MQOO_OUTPUT           |
              MQOO_INPUT_AS_Q_DEF   |
              MQOO_FAIL_IF_QUIESCING,
              &ohQueue            ) ;

  doIntTest( "put message err" ,
              0       ,
              mqPut   ,
              hConn   ,
              ohQueue ,
              &md     ,
              NULL     ,
              "hello world",
              0 ) ;

  doIntTest( "close queue"  ,
              0             ,
              mqCloseObject ,
              hConn         ,
              &ohQueue      ) ;

  doIntTest( "disconnect qmgr"    , \
              0                   , \
              mqDisc              , \
              &hConn              ) ;
#endif

  // -------------------------------------------------------
  // get test
  // -------------------------------------------------------
#if(0)
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
              MQOO_OUTPUT           |
              MQOO_INPUT_AS_Q_DEF   |
              MQOO_FAIL_IF_QUIESCING,
              &ohQueue            ) ;

  doIntTest( "get message err" ,
              0       ,
              mqGet   ,
              hConn   ,
              ohQueue ,
              &md     ,
              NULL     ,
              "hello world",
              0 ) ;

  doIntTest( "close queue"  ,
              0             ,
              mqCloseObject ,
              hConn         ,
              &ohQueue      ) ;

  doIntTest( "disconnect qmgr"    , \
              0                   , \
              mqDisc              , \
              &hConn              ) ;
#endif

_door:
  return sysRc ;
}
