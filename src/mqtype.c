/******************************************************************************/
/*   C O N V E R T   M Q    D E F I N E S   ( T Y P E )   T O   S T R I N G   */
/*                          */
/*  functions:              */
/*   - mqObjType2str        */
/*   - mqodVer2str            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------

// ---------------------------------------------------------
// mq
// ---------------------------------------------------------
#include <cmqc.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
#define convert( str ) case str : return #str ;

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* mq object description to string      */
/******************************************************************************/
const char* mqodVer2str( id )
{
  switch( id )
  {
    convert( MQOD_VERSION_1 ) ;
    convert( MQOD_VERSION_2 ) ;
    convert( MQOD_VERSION_3 ) ;
    convert( MQOD_VERSION_4 ) ;
  }

  return "UNKNOWN MQOD VERSION" ;
}

/******************************************************************************/
/* mq object type to string            */
/******************************************************************************/
const char* mqObjType2str( id )
{
  switch( id )
  {
    convert( MQOT_NONE              ) ;
    convert( MQOT_Q                 ) ;
    convert( MQOT_NAMELIST          ) ;
    convert( MQOT_PROCESS           ) ;
    convert( MQOT_STORAGE_CLASS     ) ;
    convert( MQOT_Q_MGR             ) ;
    convert( MQOT_CHANNEL           ) ;
    convert( MQOT_AUTH_INFO         ) ;
    convert( MQOT_TOPIC             ) ;
    convert( MQOT_CF_STRUC          ) ;
    convert( MQOT_LISTENER          ) ;
    convert( MQOT_SERVICE           ) ;
    convert( MQOT_RESERVED_1        ) ;
    convert( MQOT_ALL               ) ;
    convert( MQOT_ALIAS_Q           ) ;
    convert( MQOT_MODEL_Q           ) ;
    convert( MQOT_LOCAL_Q           ) ;
    convert( MQOT_REMOTE_Q          ) ;
    convert( MQOT_SENDER_CHANNEL    ) ;
    convert( MQOT_SERVER_CHANNEL    ) ;
    convert( MQOT_REQUESTER_CHANNEL ) ;
    convert( MQOT_RECEIVER_CHANNEL  ) ;
    convert( MQOT_CURRENT_CHANNEL   ) ;
    convert( MQOT_SAVED_CHANNEL     ) ;
    convert( MQOT_SVRCONN_CHANNEL   ) ;
    convert( MQOT_CLNTCONN_CHANNEL  ) ;
    convert( MQOT_SHORT_CHANNEL     ) ;
  }

  return "UNKNOWN MQ OBJECT TYPE" ;
}
