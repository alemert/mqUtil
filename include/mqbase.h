/******************************************************************************/
/* change title on for new project                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <string.h>

// ---------------------------------------------------------
// MQ
// ---------------------------------------------------------
#include <cmqc.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <msgcat/lgmqm.h>
#include <mqreason.h>
#include <mqdump.h>

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   G L O B A L E S                                                          */
/******************************************************************************/
#ifdef C_MODULE_MQ_BASE
  MQGMO _gDefGMO = {MQGMO_DEFAULT} ;
#else
  extern MQGMO _gDefGMO ;
#endif

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
#define logMQCall( lev, call, reason ) logger( LMQM_ ##lev ##_CALL       , \
                                                call                     , \
                                                (char*) mqrc2str( reason ) )

#if(0)
#define mqOpenQueue( queue, hConn, ObjDesc, opt, pHobj )           \
        {                                            \
          memcpy( ObjDesc.ObjectName, queue, MQ_Q_NAME_LENGTH ) ; \
          mqOpenObject( hConn, &ObjDesc, opt, pHobj ) ;           \
        }
#endif

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
int mqConn( char* qmName, PMQHCONN pHconn ) ;
int mqDisc( PMQHCONN pHconn ) ;

int mqOpenObject( MQHCONN hConn    , // connection handle
                  PMQOD   pObjDesc , // pointer to object descriptor
                  MQLONG  options  , // options for MQOPEN
                  PMQHOBJ pHobj  ) ; // pointer to object handle
                                  //
int mqCloseObject( MQHCONN hConn   , // connection handle
                   PMQHOBJ pHobj ) ; // pointer to object handle
                                     //
int mqPut( MQHCONN _hConn      ,     // connection handle
           MQHOBJ  _hQueue     ,     // pointer to queue handle
           PMQMD   _msgDscr    ,     // msg Desriptor
           PMQPMO  _pPutMsgOpt ,     // Options controling MQPUT
           PMQVOID _buffer     ,     // message buffer
           MQLONG  _msgLng    );     // message length (buffer length)
                                     //
int mqGet( MQHCONN _hConn      ,     // connection handle
           MQHOBJ  _hQueue     ,     // pointer to queue handle
           PMQVOID _buffer     ,     // message buffer
           PMQLONG _bufLng     ,     // buffer length
           PMQMD   _msgDscr    ,     // msg Desriptor
           MQGMO   _getMsgOpt  ,     // wait interval
           MQLONG  _wait      );     // get message option

PMQVOID resizeMqMessageBuffer( PMQVOID message, PMQLONG newSize );

