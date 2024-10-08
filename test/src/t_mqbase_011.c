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

  sysRc = initLogging( "test/log/t_mqbase_011.log", DBG ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
  doIntTest( "connect qmgr"      , \
                0                , \
                mqConn           , \
                "OMEGA", &hConn  ) ;

  MQHBAG cmdBag = MQHB_UNUSABLE_HBAG ;
  MQHBAG respBag  =  MQHB_UNUSABLE_HBAG ;

  doIntTest( "open admin bag" , \
              0               , \
              mqOpenAdminBag  , \
              &cmdBag       ) ;

  doIntTest( "open respon bag" , \
              0                , \
              mqOpenAdminBag   , \
              &respBag         ) ;

  doIntTest( "set inquire attribute" , \
              0                      , \
              mqSetInqAttr       , \
              cmdBag                 , \
              MQIACF_ALL             ) ; 

  doIntTest( "exec pcf"                  , \
              0                          , \
              mqExecPcf                  , \
              hConn                      , \
              MQCMD_INQUIRE_Q_MGR_STATUS , \
              cmdBag                     , \
              respBag                    ) ;

  doIntTest( "count items"         , \
              -10                  , \
              mqBagCountItem       , \
               respBag             , \
              MQSEL_ALL_SELECTORS );

  MQLONG compCode ;
  MQLONG mqrc ;
  MQLONG strlen ;
  char buff[255];


 
// mqInquireString(qAttrsBag, MQCA_Q_NAME, 0, MQ_Q_NAME_LENGTH, qName, &qNameLength, NULL, &compCode, &reason);
      

  mqInquireString( respBag, MQCA_INSTALLATION_PATH, MQIND_NONE, 255, buff, &strlen, NULL, &compCode, &mqrc );

  doIntTest( "disconnect qmgr"   , \
                0                , \
                mqDisc           , \
                &hConn           ) ;

_door:
  return sysRc ;
}
