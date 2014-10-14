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
int main( )
{
  int sysRc = NO_ERROR ;

  MQHCONN hConn ;

  sysRc = initLogging( "test/log/t_mqbase_010.log", DBG ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  doIntTest( "connect qmgr"      , \
                0                , \
                mqConn           , \
                "OMEGA", &hConn   ) ;

  MQHBAG adminBag  = MQHB_UNUSABLE_HBAG;  // response bag for mqExecute
  MQHBAG responBag = MQHB_UNUSABLE_HBAG;  // response bag for mqExecute

  doIntTest( "open admin bag" , \
              0               , \
              mqOpenAdminBag  , \
              &adminBag       ) ;

  doIntTest( "open respon bag" , \
              0               , \
              mqOpenAdminBag  , \
              &responBag       ) ;
#if(1)
  doIntTest( "set inquire attribute" ,    \
              0   ,    \
              mqAddInqAttrFunc ,      \
              adminBag,    \
              1 ,         \
              MQIACF_ALL );
#endif

  doIntTest( "exec pcf"                  , \
              0                          , \
              mqExecPcf                  , \
              hConn                      , \
              MQCMD_INQUIRE_Q_MGR_STATUS , \
              adminBag                   , \
              responBag                  );
    

  doIntTest( "disconnect qmgr"   , \
                0                , \
                mqDisc           , \
                &hConn            ) ;

#endif

_door:
  return sysRc ;
}
