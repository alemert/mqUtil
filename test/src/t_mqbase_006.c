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
#include <unistd.h>

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
int main( )
{
  int sysRc = NO_ERROR ;

  MQHCONN hConn   ;
  MQOD    odSrc = {MQOD_DEFAULT} ;
  MQHOBJ  ohSrc ;

  MQOD    odGoal = {MQOD_DEFAULT} ;
  MQHOBJ  ohGoal ;

  MQBYTE24 msgId ;

  sysRc = initLogging( "test/log/t_mqbase_006.log", DBG ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  doIntTest( "connect qmgr"       , \
              0                   , \
              mqConn              , \
             "OMEGA"               , \
              &hConn              ) ;


  memset( odSrc.ObjectName, (int) ' ', MQ_Q_NAME_LENGTH ) ;
  memcpy( odSrc.ObjectName, "SOURCE.4.MOVE", MQ_Q_NAME_LENGTH ) ;

  {
    doIntTest( "open source queue"  , \
                0                   , \
                mqOpenObject        , \
                hConn               , \
                &odSrc              , \
                MQOO_INPUT_AS_Q_DEF   |
                MQOO_OUTPUT |
                MQOO_FAIL_IF_QUIESCING,
                &ohSrc            ) ;
    MQPMO pmo = {MQPMO_DEFAULT}; 
    MQMD  md  = {MQMD_DEFAULT} ;
  
    doIntTest( "put message err" , \
                0                , \
                mqPut            , \
                hConn            , \
                ohSrc            , \
                &md              , \
                &pmo             , \
                "hello world"    , \
                0 ) ;

    memcpy( &msgId, &md.MsgId, sizeof(MQBYTE24) );

    doIntTest( "close source queue" ,\
                0  ,\
                mqCloseObject, \
                hConn, \
                &ohSrc );
  }

  doIntTest( "open source queue"  , \
              0                   , \
              mqOpenObject        , \
              hConn               , \
              &odSrc              , \
              MQOO_INPUT_AS_Q_DEF   |
              MQOO_FAIL_IF_QUIESCING,
              &ohSrc            ) ;

  memset( odGoal.ObjectName, (int) ' ', MQ_Q_NAME_LENGTH ) ;
  memcpy( odGoal.ObjectName, "GOAL.4.MOVE", MQ_Q_NAME_LENGTH ) ;
 
  doIntTest( "open goal queue"  , \
              0                   , \
              mqOpenObject        , \
              hConn               , \
              &odGoal              , \
              MQOO_OUTPUT |
              MQOO_FAIL_IF_QUIESCING,
              &ohGoal            ) ;
 
  doIntTest( "open transaction" , \
	      2121      , \
              mqBegin   , \
              hConn     ) ;

  MQGMO gmo = {MQGMO_DEFAULT}; 
  MQMD  md  = {MQMD_DEFAULT} ;
  char  buffer[128] ;
  MQLONG lng = 128 ;

  memcpy( md.MsgId, msgId, sizeof(MQBYTE24) );

  doIntTest( "read source queue" , \
              0                  , \
              mqGet              , \
              hConn              , \
              ohSrc              , \
              &buffer            , \
              &lng               , \
              &md                , \
              gmo                , \
              1                  ) ;
  goto _door ;
  sleep(5) ;

  doIntTest ( "commit transaction",
	       0   ,
	       mqCommit     ,
	       hConn );

  doIntTest( "close source queue" ,\
              0  ,\
              mqCloseObject, \
              hConn, \
              &ohSrc );

  doIntTest( "disconnect qmgr"       , \
              0                   , \
              mqDisc              , \
              &hConn              ) ;
#endif

_door:
  return sysRc ;
}
