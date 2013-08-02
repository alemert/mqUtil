/******************************************************************************/
/*                                                                            */
/*                      M Q   B A S E   F U N C T I O N S                     */
/*                                                                            */
/*  funstions:                                                                */
/*    - mqConn                                                                */
/*    - mqDisc                                                                */
/*    - mqOpenObject                                                          */
/*    - mqCloseObject                          */
/*    - mqPut                                                              */
/*    - mqGet                          */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
#define C_MODULE_MQ_BASE

// ---------------------------------------------------------
// system
// ---------------------------------------------------------

// ---------------------------------------------------------
// MQ
// ---------------------------------------------------------
#include <cmqc.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <mqbase.h>
#include <ctl.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* mq connect                                                                 */
/******************************************************************************/
int mqConn( char* qmName, PMQHCONN pHconn )
{
  logFuncCall( ) ;

  int sysRc = 0 ;

  MQLONG compCode ;
  MQLONG reason   ;

  // -------------------------------------------------------
  // connect to queue manager
  // -------------------------------------------------------
  MQCONN( (PMQCHAR) qmName    ,  // queue manager name
                    pHconn    ,  // pointer to connection handle
                    &compCode ,  // completion code
                    &reason  );  // reason code

  if( compCode == MQCC_FAILED )
  {
    logMQCall( ERR, "MQCONN", reason ) ;
    sysRc = reason ;
    goto _door ;
  }

 logMQCall( INF, "MQCONN", reason ) ;

  _door :
  logFuncExit( ) ;

  return sysRc ;
}

/******************************************************************************/
/* mq disconnect                                                              */
/******************************************************************************/
int mqDisc( PMQHCONN pHconn )
{
  logFuncCall( ) ;

  int sysRc = 0 ;

  MQLONG compCode ;
  MQLONG reason   ;

  // -------------------------------------------------------
  // connect to queue manager
  // -------------------------------------------------------
  MQDISC( (PMQHCONN) pHconn   ,    // pointer to connection handle
                    &compCode ,    // completion code
                    &reason  );    // reason code

  if( compCode == MQCC_FAILED )
  {
    logMQCall( ERR, "MQCONN", reason ) ;
    sysRc = reason ;
    goto _door ;
  }

 logMQCall( INF, "MQDISC", reason ) ;

  _door :
  logFuncExit( ) ;

  return sysRc ;
}

/******************************************************************************/
/*   M Q   O P E N   Q U E U E                                                */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  open options:                                                             */
/*    MQOO_INPUT_AS_Q_DEF           open object for get                       */
/*    MQOO_INPUT_SHARED             open object with shared access            */
/*    MQOO_INPUT_EXCLUSIVE          open object with exlusive access          */
/*    MQOO_BROWSE                   open object for browse                    */
/*    MQOO_OUTPUT                   open object for put                       */
/*    MQOO_INQUIRE                  open object for inquire                   */
/*    MQOO_SET                      open queue for MQSET                      */
/*    MQOO_BIND_ON_OPEN             local qmgr binds the queue handle to      */
/*                                  a particular instance of the destination  */
/*                                  queue                                     */
/*    MQOO_BIND_NOT_FIXED           stops local queue manage binding the      */
/*                                  queue handle to a particular instnce of   */
/*                                  the destination queue                     */
/*    MQOO_BIND_AS_Q_DEF            local queue manager binds the queue       */
/*                                  handle in the way defined by the DefBind  */
/*                                 queue atribute                             */
/*    MQOO_SAVE_ALL_CONTEXT         context information is associated with    */
/*                                 this queue handle                          */
/*    MQOO_PASS_IDENTITY_CONTEXT    allows the context to be specified in the */
/*                                 PutMsgOpts when a message is put on a      */
/*                                 queue                                      */
/*    MQOO_PASS_ALL_CONTEXT         allows the context to be specified in the */
/*                                 PutMsgOpts parameter when a messee is put  */
/*                                 on a queue                                 */
/*    MQOO_SET_IDENTITY_CONTEXT     allows the context to be specified in the */
/*                                 PutMsgOpts parameter when a messee is put  */
/*                                 on a queue                                 */
/*    MQOO_SET_ALL_CONTEXT          allows the context to be specified in the */
/*                                  PutMsgOpts parameter when a messee is put */
/*                                  on a queue                                */
/*    MQOO_ALTERNATE_USER_AUTHORITY contains a user identifier to use to      */
/*                                  validate MQOPEN call                      */
/*    MQOO_FAIL_IF_QUIESCING        MQOPEN Call fails if the queue manager is */
/*                                  in quiscing state                         */
/*                                                                            */
/******************************************************************************/
int mqOpenObject( MQHCONN hConn   , // connection handle
                  PMQOD   pObjDesc, // pointer to object descriptor
                  MQLONG  options , // options for MQOPEN
                  PMQHOBJ pHobj   ) // pointer to object handle
{
  logFuncCall( ) ;

  MQLONG compCode ;                 // Completion code
  MQLONG reason   ;                 // Reason code qualifying CompCode

  // -------------------------------------------------------
  // open mq object
  // -------------------------------------------------------
   MQOPEN( hConn    ,        // connection handle
           pObjDesc ,        // object descriptor for queue
           options  ,        // open options
           pHobj    ,        // object handle
           &compCode,        // completion code
           &reason );        // reason code


  dumpMqStruct( "OD  ", pObjDesc, NULL  ) ;

  if( compCode == MQCC_FAILED )
  {
    logMQCall( ERR, "MQOPEN", reason ) ;
    goto _door ;
  }

  logMQCall( INF, "MQOPEN", reason ) ;

  _door :

  logFuncExit() ;

  return reason ;
}

/******************************************************************************/
/*   M Q   C L O S E   Q U E U E                                              */
/* -------------------------------------------------------------------------- */
/*   Dscr: close queue given by pHobj                                         */
/******************************************************************************/
int mqCloseObject( MQHCONN hConn   ,   // connection handle
                   PMQHOBJ pHobj   )   // pointer to object handle
{
  logFuncCall() ;

  MQLONG compCode ;                     // Completion code
  MQLONG reason   ;                     // Reason code qualifying CompCode

  // -------------------------------------------------------
  // open mq object
  // -------------------------------------------------------
   MQCLOSE( hConn    ,        // connection handle
            pHobj    ,        // object handle
            MQCO_NONE ,       // options
            &compCode,        // completion code
            &reason );        // reason code

  // -------------------------------------------------------
  // check Return Code and log it into log file
  // -------------------------------------------------------

  if( compCode == MQCC_FAILED )
  {
    logMQCall( ERR, "MQCLOSE", reason ) ;
    goto _door ;
  }

  logMQCall( INF, "MQCLOSE", reason ) ;

  _door :

  return (int) reason ;
}

/******************************************************************************/
/*   M Q    P U T                                                             */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Descrip: write messages to a queue                                       */
/*                                                                            */
/******************************************************************************/
int mqPut( MQHCONN _hConn      ,         // connection handle
           MQHOBJ  _hQueue     ,         // pointer to queue handle
           PMQMD   _msgDscr    ,         // msg Desriptor
           PMQPMO  _pPutMsgOpt ,         // Options controling MQPUT
           PMQVOID _buffer     ,         // message buffer
           MQLONG  _msgLng     )         // message length (buffer length)
{                                        //
  logFuncCall( ) ;

  MQPMO  putMsgOpt = {MQPMO_DEFAULT} ;  // Options controling MQPUT
                                        //
  MQLONG compCode ;                     // Completion code
  MQLONG reason   ;                     // Reason code qualifying CompCode

  // -------------------------------------------------------
  // set put messages options
  // -------------------------------------------------------
  if( _pPutMsgOpt == NULL )                       //
  {                                               //
    putMsgOpt.Options = MQPMO_NO_SYNCPOINT      | //
                        MQPMO_FAIL_IF_QUIESCING ; //
    _pPutMsgOpt = &putMsgOpt ;                    //
                                                  //
    memcpy( _msgDscr->MsgId          ,            // reset message id
            MQMI_NONE                ,            //
            sizeof(_msgDscr->MsgId) );            //
                                                  //
    memcpy( _msgDscr->CorrelId          ,         // reset correlation id
            MQCI_NONE                   ,         //
            sizeof(_msgDscr->CorrelId) );         //
                                                  //
    memcpy( _msgDscr->Format          ,           // character string format
            MQFMT_STRING              ,           //
            (size_t)MQ_FORMAT_LENGTH );           //
  }                                               //
                                                  //
  // -------------------------------------------------------
  // set buffer length if neccesary
  // -------------------------------------------------------
  if( _msgLng == 0 )                              //
  {                                               //
    _msgLng = (MQLONG) strlen( _buffer );         //
  }                                               //
                                                  //
  // -------------------------------------------------------
  // put a message to a queue
  // -------------------------------------------------------
  dumpMqStruct( "PMO  ", _pPutMsgOpt, NULL );     //
  dumpMqStruct( "MD   ", _msgDscr   , NULL );     //
                                                  //
  MQPUT( _hConn      ,                            // connection handle
         _hQueue     ,                            // object handle
         _msgDscr    ,                            // message descriptor
         _pPutMsgOpt ,                            // default options (datagram)
         _msgLng     ,                            // message length
         _buffer     ,                            // message buffer
         &compCode   ,                            // completion code
         &reason     );                           // reason code
                                                  //
  dumpMqStruct( "PMO  ", _pPutMsgOpt, NULL );     //
  dumpMqStruct( "MD   ", _msgDscr   , NULL );     //
                                                  //
  // -------------------------------------------------------
  // check Return Code and log it into log file
  // -------------------------------------------------------
  if( compCode == MQCC_FAILED )                   //
  {                                               //
    logMQCall( ERR, "MQPUT", reason ) ;           //
    goto _door ;                                  //
  }                                               //
                                                  //
  logMQCall( INF, "MQPUT", reason ) ;             //
                                                  //
  _door :                                         //
                                                  //
  logFuncExit() ;

  return reason ;
}

/******************************************************************************/
/*   M Q    G E T                                                             */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Descrip: read messages from the queue,                                   */
/*            read options were set by calling mqOpen                         */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
int mqGet( MQHCONN _hConn     ,      // connection handle
           MQHOBJ  _hQueue    ,      // pointer to queue handle
           PMQVOID _buffer    ,      // message buffer
           int     _bufLng    ,      // buffer length
           PMQMD   _msgDscr   ,      // msg Desriptor
           MQGMO   _getMsgOpt ,      // get message option 
           MQLONG  _wait      )      // wait interval
{                                    //
  logFuncCall() ;

  MQLONG compCode ;                    // Completion code
  MQLONG reason   ;                    // Reason code qualifying CompCode

//MQGMO   getMsgOpt = {MQGMO_DEFAULT}; // Options controling MQGET
  MQLONG  msgLng    ;                  // Length of the message

  // -------------------------------------------------------
  // set get messages options
  // -------------------------------------------------------
  _getMsgOpt.Options = MQGMO_WAIT              // wait for new messages
                     + MQGMO_FAIL_IF_QUIESCING // fail if quiesching
                     + MQGMO_CONVERT;          // convert if necessary
                                               //
  // -------------------------------------------------------
  // set msgDscr
  // -------------------------------------------------------
#if(0)
  memcpy(msgDscr->MsgId   , MQMI_NONE, sizeof(msgDscr->MsgId)    );
  memcpy(msgDscr->CorrelId, MQCI_NONE, sizeof(msgDscr->CorrelId) );
#endif
  _msgDscr->Encoding       = MQENC_NATIVE;     //
  _msgDscr->CodedCharSetId = MQCCSI_Q_MGR;     //
                                               //
  memset( _buffer, ' ', _bufLng-1 );           //
                                               //
  dumpMqStruct( "GMO  ", &_getMsgOpt, NULL );  //
  dumpMqStruct( "MD   ", _msgDscr   , NULL );  //
                                               //
  MQGET( _hConn      ,                         // connection handle
         _hQueue     ,                         // object handle
         _msgDscr    ,                         // message descriptor
         &_getMsgOpt ,                         // get message options
         _bufLng     ,                         // buffer length
         _buffer     ,                         // message buffer
         &msgLng     ,                         // message length
         &compCode   ,                         // completion code
         &reason    );                         // reason code
                                               //
  dumpMqStruct( "GMO  ", &_getMsgOpt, NULL );  //
  dumpMqStruct( "MD   ", _msgDscr   , NULL );  //
                                               //
  // -------------------------------------------------------
  // check Return Code and log it into log file
  // -------------------------------------------------------
  if( compCode == MQCC_FAILED )                //
  {                                            //
    switch( reason )                           //
    {                                          //
      case MQRC_NO_MSG_AVAILABLE:              // not finding a message is not
      {                                        //  an error per default
        logMQCall( DBG, "MQPUT", reason );     //
        break ;                                //
      }                                        //
      default :                                // error
      {                                        //
        logMQCall( ERR, "MQPUT", reason );     //
        goto _door ;                           //
      }                                        //
    }                                          //
    return (int) reason ;                      //
  }                                            //
                                               //
  logMQCall( INF, "MQPUT", reason );           //
                                               //
  _door :                                      //  
                                               //
  logFuncExit() ;                              //
                                               //
  return reason ;                              //
}

