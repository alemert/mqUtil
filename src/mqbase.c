/******************************************************************************/
/*                                                                            */
/*                      M Q   B A S E   F U N C T I O N S                     */
/*                                                                            */
/*  functions:                                                                */
/*    - mqConn                                                                */
/*    - mqDisc                                                                */
/*    - mqOpenObject                                                          */
/*    - mqCloseObject                                                         */
/*    - mqPut                                                                 */
/*    - mqGet                                                                 */
/*    - mqBegin                                                               */
/*    - mqCommit                                                              */
/*    - mqRollback                                                            */
/*    - resizeMqMessageBuffer                                                 */
/*    - mqSetTrigger                                                          */
/*    - mqOpenBagAPI                                                          */
/*    - mqReadBag                                                             */
/*    - mqCloseBag                                                            */
/*    - mqResetQmgrLog                                                        */
/*    - mqExecPcf                                                             */
/*    - mqAddInqAttrFunc                                              */
/*    - mqAddString                                                    */
/*    - mqAddInt                              */
/*    - mqInquireErrBag                                            */
/*    - mqBagCountItem                                            */
/*    - mqBagInq                          */
/*    - mqStrInq                      */
/*                                                                            */
/*  macros:                                                                   */
/*    - mqOpenUserBag                                                         */
/*    - mqOpenAdminBag                                                        */
/*    - mqSetInqAttr                                                */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
#define C_MODULE_MQ_BASE

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdlib.h>
#include <stdarg.h>

// ---------------------------------------------------------
// MQ
// ---------------------------------------------------------
#include <cmqc.h>
#include <cmqcfc.h>
#include <cmqbc.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <mqbase.h>
#include <ctl.h>
#include <msgcat/lgstd.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/
const char gDefaultQmgr[] = "\0" ;

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
MQLONG mqInquireErrBag( MQHBAG _resBag );

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* MQ connect                                                                 */
/******************************************************************************/
MQLONG mqConn( char* _qmName, PMQHCONN pHconn )
{
  logFuncCall( ) ;

  int sysRc = 0 ;

  MQCHAR qmName[MQ_Q_MGR_NAME_LENGTH+1] ;
  MQLONG compCode ;
  MQLONG reason   ;

  memset( qmName, ' ', MQ_Q_MGR_NAME_LENGTH );
  if( _qmName != NULL )
  {
    strncpy( qmName, _qmName, strlen(_qmName) );
  }

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
  logger( LMQM_QMGR_CONNECTED, qmName[0] == '\0' ? "default" : _qmName );

  _door :
  logFuncExit( ) ;

  return sysRc ;
}

/******************************************************************************/
/* MQ disconnect                                                              */
/******************************************************************************/
MQLONG mqDisc( PMQHCONN pHconn )
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
    logMQCall( ERR, "MQDISC", reason ) ;
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
MQLONG mqOpenObject( MQHCONN hConn   , // connection handle
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
  logger( LMQM_Q_OPENED, pObjDesc->ObjectName );

  _door :

  logFuncExit() ;

  return reason ;
}

/******************************************************************************/
/*   M Q   C L O S E   Q U E U E                                              */
/* -------------------------------------------------------------------------- */
/*   Dscr: close queue given by pHobj                                         */
/******************************************************************************/
MQLONG mqCloseObject( MQHCONN hConn   ,   // connection handle
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
MQLONG mqPut( MQHCONN _hConn      ,         // connection handle
              MQHOBJ  _hQueue     ,         // pointer to queue handle
              PMQMD   _msgDscr    ,         // msg Desriptor
              PMQPMO  _pPutMsgOpt ,         // Options controling MQPUT
              PMQVOID _buffer     ,         // message buffer
              MQLONG  _msgLng     )         // message length (buffer length)
{                                           //
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
/*   Description: read messages from the queue,                               */
/*                read options were set by calling mqOpen                     */
/*                                                                            */
/*   Comment: function will add:                                              */
/*             - MQGMO_FAIL_IF_QUIESCING,                                     */
/*             - MQGMO_CONVERT                                                */
/*            to get message options as default settings                      */
/*                                                                            */
/******************************************************************************/
MQLONG mqGet( MQHCONN _hConn     ,      // connection handle
              MQHOBJ  _hQueue    ,      // pointer to queue handle
              PMQVOID _buffer    ,      // message buffer
              PMQLONG  _bufLng   ,      // buffer length
              PMQMD   _msgDscr   ,      // message descriptor
              MQGMO   _getMsgOpt ,      // get message option 
              MQLONG  _wait      )      // wait interval to adjust _getMsgOpt
{                                       //
  logFuncCall() ;                       //
                                        //
  MQLONG compCode ;                     // Completion code
  MQLONG reason   ;                     // Reason code qualifying CompCode
                                        //
  MQLONG  msgLng  ;                     // Length of the message
                                        //
//int loop = 0 ;                        // flag breaking loop

  // -------------------------------------------------------
  // set the get messages options
  // -------------------------------------------------------
  _getMsgOpt.Options |= MQGMO_FAIL_IF_QUIESCING    // fail if quiescing    
                     +  MQGMO_CONVERT;             // convert if necessary
  if( _wait > 0 )                                  //
  {                                                // set wait for messages
    _getMsgOpt.Options |= MQGMO_WAIT ;             // 
  }                                                //
   _getMsgOpt.WaitInterval = _wait ;               //
                                                   //
  // -------------------------------------------------------
  // set msgDscr
  // -------------------------------------------------------
#if(0)
  memcpy(msgDscr->MsgId   , MQMI_NONE, sizeof(msgDscr->MsgId)    );
  memcpy(msgDscr->CorrelId, MQCI_NONE, sizeof(msgDscr->CorrelId) );
#endif
  _msgDscr->Encoding       = MQENC_NATIVE;         //
  _msgDscr->CodedCharSetId = MQCCSI_Q_MGR;         //
                                                   //
                                                   //
  dumpMqStruct( "GMO  ", &_getMsgOpt, NULL );      //
  dumpMqStruct( "MD   ", _msgDscr   , NULL );      //
                                                   //
  memset( _buffer, ' ', (*_bufLng) - 1 );          //
                                                   //
  MQGET( _hConn      ,                             // connection handle
         _hQueue     ,                             // object handle
         _msgDscr    ,                             // message descriptor
         &_getMsgOpt ,                             // get message options
         *_bufLng    ,                             // buffer length
         _buffer     ,                             // message buffer
         &msgLng     ,                             // message length
         &compCode   ,                             // completion code
         &reason    );                             // reason code
                                                   //
    dumpMqStruct( "GMO  ", &_getMsgOpt, NULL );    //
    dumpMqStruct( "MD   ", _msgDscr   , NULL );    //
                                                   //
  // -------------------------------------------------------
  // check Return Code and log it into log file
  // -------------------------------------------------------
  switch( reason )                                 //
  {                                                //
    case MQRC_NONE :                               // message found,
    {                                              //  break out of loop
      *_bufLng = msgLng;                           //
      break ;                                      //
    }                                              //
                                                   //
    case MQRC_TRUNCATED_MSG_ACCEPTED:              //
    case MQRC_NO_MSG_AVAILABLE:                    // finding no message is not
    {                                              //  an error per default
      logMQCall( DBG, "MQGET", reason );           //
      break;                                       //
    }                                              //
                                                   //
    case MQRC_TRUNCATED_MSG_FAILED :               // message buffer to small
    {                                              //  resize (reallocate)
      *_bufLng = msgLng;                           //  message buffer
      logMQCall( WAR, "MQGET", reason );           //
      break ;                                      //
    }                                              //
                                                   //
    default :                                      // error
    {                                              //
      logMQCall( ERR, "MQGET", reason );           //
      goto _door ;                                 //
    }                                              //
  }                                                //
                                                   //
  logMQCall( INF, "MQGET", reason );               //
                                                   //
  _door :                                          //  
                                                   //
  logFuncExit() ;                                  //
                                                   //
  return reason ;                                  //
}

/******************************************************************************/
/*   M Q   B E G I N                                                          */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: api to MQBEGIN call                                         */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqBegin( MQHCONN _hConn )   // connection handle
{
  logFuncCall() ;

  MQLONG compCode;
  MQLONG reason = MQRC_NONE;

  MQBO bo = { MQBO_DEFAULT };

  MQBEGIN( _hConn   ,
           &bo      ,
           &compCode,
           &reason );

  switch( reason )
  {
    case MQRC_NO_EXTERNAL_PARTICIPANTS :  // no external transactional manager
    case MQRC_NONE :                        
    {                                      
      logMQCall(DBG,"MQBEGIN",reason);
      break;                             
    }                                   
    default :                          
    {                                 
      logMQCall(ERR,"MQBEGIN",reason);  
      goto _door;                   
    }                              
  }

  _door:
  logFuncExit() ; 
  return reason ; 
}

/******************************************************************************/
/*   M Q   C O M M I T                                                        */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: api to MQCMIT call                                          */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqCommit( MQHCONN _hConn )   // connection handle
{
  logFuncCall() ;

  MQLONG compCode;
  MQLONG reason = MQRC_NONE;

  MQCMIT( _hConn,
          &compCode,
          &reason );

  switch( reason )
  {
    case MQRC_NONE :                        
    {                                      
      logMQCall(DBG,"MQCMIT",reason);
      break;                             
    }                                   
    default :                          
    {                                 
      logMQCall(ERR,"MQCMIT",reason);  
      goto _door;                   
    }                              
  }

  _door:
  logFuncExit() ; 
  return reason ; 
}

/******************************************************************************/
/*   M Q   R O L L B A C K                                                    */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: api to MQBACK call                                          */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqRollback( MQHCONN _hConn )   // connection handle
{
  logFuncCall() ;

  MQLONG compCode;
  MQLONG reason = MQRC_NONE;

  MQBACK( _hConn,
          &compCode,
          &reason );

  switch( reason )
  {
    case MQRC_NONE :                        
    {                                      
      logMQCall(DBG,"MQCMIT",reason);
      break;                             
    }                                   
    default :                          
    {                                 
      logMQCall(ERR,"MQCMIT",reason);  
      goto _door;                   
    }                              
  }

  _door:
  logFuncExit() ; 
  return reason ; 
}

/******************************************************************************/
/*   M Q    R E S I Z E   M E S S A G E                                       */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: resize message buffer                                       */
/*                if the buffer is to short for reading                       */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
PMQVOID resizeMqMessageBuffer( PMQVOID message, PMQLONG newSize )
{
  logFuncCall() ;

  message = (PMQVOID) realloc( message, sizeof(void)*(*newSize) );
  logger(LMQM_INCR_MSG_BUFF,(int)*newSize ); //
  if( message == NULL )                      //
  {                                          //
    logger( LSTD_MEM_ALLOC_ERROR ) ;         //
    goto _door ;                             //
  }                                          //

  _door:

  logFuncExit() ;                            

  return message;
}

/******************************************************************************/
/*   M Q   S E T   T R I G G E R   O N                                        */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   this function process following:                                         */
/*   ALTER QLOCAL (QUEUE.NAME) TRIGGER                                        */
/******************************************************************************/
MQLONG mqSetTrigger( MQHCONN Hconn   ,   // connection handle
                     MQHOBJ  Hqueue  )   // queue handle
{
  logFuncCall() ;

  MQLONG compCode      ;              // Completion code
  MQLONG reason = MQRC_NONE ;         // Reason code qualifying CompCode

  MQLONG select[1]     ;              // attribute selector(s)
  MQLONG intAttrArr[1] ;              // integer attribute count

  // -------------------------------------------------------
  // set attributes for alter
  // -------------------------------------------------------
  select[0]     = MQIA_TRIGGER_CONTROL ;
  intAttrArr[0] = MQTC_ON              ;

  // -------------------------------------------------------
  // MQ alter
  // -------------------------------------------------------
  MQSET( Hconn      ,    // connection handle
         Hqueue     ,    // object handle
         1          ,    // selector count
         select     ,    // selector array
         1          ,    // integer attribute count
         intAttrArr ,    // integer attribute array
         0          ,    // char attribute count
         NULL       ,    // char attribute array
         &compCode  ,    // completion code
         &reason   );    // reason code

  // -------------------------------------------------------
  // check Return Code and log it into the log file
  // -------------------------------------------------------
  switch( reason )
  {
    case MQRC_NONE :                        
    {                                      
      logMQCall(DBG,"MQSET",reason);
      break;                             
    }                                   
    default :                          
    {                                 
      logMQCall(ERR,"MQSET",reason);  
      goto _door;                   
    }                              
  }
  
  _door:
  logFuncExit() ; 
  return reason ;
}

/******************************************************************************/
/*   M Q    O P E N   B A G   A P I                                           */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: interface to mqCreateBag                                    */
/*                                                                            */
/*   Comment: macros mqOpenAdminBag and mqOpenUserBag should be used          */
/*                                                                            */
/******************************************************************************/
MQLONG mqOpenBagAPI( MQLONG opt, PMQHBAG bag )
{
  MQLONG compCode;
  MQLONG reason  ;

  mqCreateBag( opt, bag, &compCode, &reason );

  switch( reason )                            
  {                                          
    case MQRC_NONE :                        
    {                                      
      logMQCall(DBG,"mqCreateBag",reason);
      break;                             
    }                                   
    default :                          
    {                                 
      logMQCall(ERR,"mqCreateBag",reason);  
      goto _door;                   
    }                              
  }                               

  _door:
  return reason;

}

/******************************************************************************/
/*   M Q    R E A D   B A G                                                   */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: interface to mqGetBag                                       */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqReadBag( MQHCONN hConn, 
                  MQHOBJ odQueue, 
                  PMQMD msgDscr ,
                  PMQGMO getMsgOpt, 
                  MQHBAG bag )
{
  MQLONG compCode;
  MQLONG reason  ;

  if( getMsgOpt->Version < MQGMO_VERSION_2 )
  {
    getMsgOpt->Version = MQGMO_VERSION_2 ;
  }
  if( msgDscr->Version < MQMD_VERSION_2 )
  {
    msgDscr->Version = MQMD_VERSION_2 ;
  }

  getMsgOpt->Options |= MQGMO_WAIT              // wait for new messages
                     +  MQGMO_FAIL_IF_QUIESCING // fail if quiesching
                     +  MQGMO_CONVERT ;         // convert if necessary

  mqGetBag( hConn    ,     // global (qmgr) connect handle
            odQueue  ,     // globale (queue) open handle
            msgDscr  ,     // message descriptor
            getMsgOpt,     // get message options
            bag      ,     // event bag
            &compCode,     // compelition code
            &reason );     // mq reason

  dumpMqStruct( "GMO  ", getMsgOpt , NULL );  
  dumpMqStruct( "MD   ", msgDscr, NULL ); 

  switch( reason )                          
  {                                        
    case MQRC_NONE :                      
    {                                    
      logMQCall( DBG, "mqGetBag", reason ); 
      dumpMqStruct( "MQBAG", &bag, NULL );
      break;                         
    }                                  
    case MQRC_NO_MSG_AVAILABLE :      
    {                                
      logMQCall( DBG, "mqGetBag", reason );
      break;                     
    }                              
    default :                     
    {                            
      logMQCall( ERR, "mqGetBag", reason ); 
      goto _door;
      break ;
    }                         
  }                          

  _door:
  return reason;
}

/******************************************************************************/
/*   M Q    C L O S E   B A G                                                 */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: interface to mqDeleteBag                                    */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqCloseBag( PMQHBAG bag )
{
  MQLONG compCode;
  MQLONG reason  = MQRC_NONE ;

  if( *bag != MQHB_UNUSABLE_HBAG ) 
  {
    mqDeleteBag( bag, &compCode, &reason );

    switch( reason )                            
    {                                          
      case MQRC_NONE :                        
      {                                      
        logMQCall(DBG,"mqCreateBag",reason);
        break;                             
      }                                   
      default :                          
      {                                 
        logMQCall(ERR,"mqCreateBag",reason);  
        goto _door;                   
      }                              
    }                               
  }                               

  _door:
  return reason;
}

/******************************************************************************/
/*   M Q   R E S E T   Q M G R   A D V A N C E   L O G                        */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   Description: this function process:                                      */
/*                RESET QMGR TYPE(ADVANCELOG)                                 */
/*                      */
/******************************************************************************/
MQLONG mqResetQmgrLog( MQHCONN Hconn ) // connection handle
{
  logFuncCall() ;

  MQHBAG adminBag  = MQHB_UNUSABLE_HBAG;  // admin bag for mqExecute
  MQHBAG responBag = MQHB_UNUSABLE_HBAG;  // response bag for mqExecute
  MQHBAG resultBag = MQHB_UNUSABLE_HBAG;  // response bag for mqExecute

  MQLONG compCode     ;  // Completion code
  MQLONG reason       ;  // Reason code qualifying CompCode
  MQLONG execCompCode ;  // Completion code for mqExec
  MQLONG execReason   ;  // Reason code for mqExec qualifying execCompCode

  int sysRc ;

  // -------------------------------------------------------
  // create an admin bag for the mqExecute call
  // -------------------------------------------------------
  sysRc = mqOpenAdminBag( &adminBag ) ;
  if( sysRc != MQRC_NONE ) goto _door;

  // -------------------------------------------------------
  // create an admin bag for the mqExecute call
  // -------------------------------------------------------
  sysRc = mqOpenAdminBag( &responBag ) ;
  if( sysRc != MQRC_NONE ) goto _door;

  // -------------------------------------------------------
  // SET TYPE(ADVANCELOG)
  // -------------------------------------------------------
  mqAddInteger(adminBag, MQIACF_ACTION    ,
                         MQACT_ADVANCE_LOG,
                         &compCode        ,
                         &reason         );

  switch( reason )
  {
    case MQRC_NONE :                        
    {                                      
      logMQCall(DBG,"mqAddInteger",reason);
      break;                             
    }                                   
    default :                          
    {                                 
      logMQCall(ERR,"mqAddInteger",reason);  
      goto _door;
    }                              
  }

  // -------------------------------------------------------
  // execute bag
  // -------------------------------------------------------
  mqExecute( Hconn            , // queue manager connection handle
             MQCMD_RESET_Q_MGR, // command to be executed
             MQHB_NONE        , // no options bag
             adminBag         , // handle to bag containing attributes
             responBag        , // handle to bag to receive response
             MQHO_NONE        , // put msg on SYSTEM.ADMIN.COMMAND.QUEUE
             MQHO_NONE        , // create a dynamic q for response
             &execCompCode    , // completion code
             &execReason     ); // reason code

  if( execCompCode == MQCC_FAILED)
  {
    logMQCall(ERR,"RC(mqExec)",execReason);  

    // ---------------------------------------------------
    // analyze answer from mqExecute if NOK
    // ---------------------------------------------------
    mqInquireBag( responBag, MQHA_BAG_HANDLE,
                             0              ,
                             &resultBag     ,
                             &compCode      ,
                             &reason       );

    logMQCall(DBG,"mqInquireBag",reason);  

    mqInquireInteger( resultBag, MQIASY_COMP_CODE,
                                 MQIND_NONE      ,
                                 &execCompCode   ,
                                 &compCode       ,
                                 &reason        );

    logMQCall(DBG,"mqInquireInteger",reason);  

    reason = execReason;
    goto _door;
  }

  _door:

  logFuncExit( ) ;
  return (int) reason ;
}

/******************************************************************************/
/*   M Q   E X E C U T E   P C F   C O M M A N D                              */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   Description: execute PCF command                   */
/*                                  */
/******************************************************************************/
MQLONG mqExecPcf( MQHCONN _hConn   ,   // connection handle
                  MQLONG  _pcfCmd  ,   // PCF command
                  MQHBAG  _cmdBag  ,   // command bag
                  MQHBAG  _resBag  )   // response bag 
{
  logFuncCall() ;

  MQLONG mqExecRc = MQRC_NONE ;
  MQLONG mqrc     ;
  MQLONG compCode ;

  mqExecute( _hConn   ,                  // MQ connection handle   
             _pcfCmd  ,                  // Command to be executed    
             MQHB_NONE,                  // No options bag 
             _cmdBag  ,                  // Handle to bag containing commands   
             _resBag  ,                  // Handle to bag receiving the response
             MQHO_NONE,                  // Write SYSTEM.ADMIN.COMMAND.QUEUE
             MQHO_NONE,                  // Create a dynamic q for the response
             &compCode,                  // Completion code from the mqexecute
             &mqrc   );                  // Reason code from mqexecute call
                                         //
  switch( mqrc )                         //
  {                                      //
    case MQRC_NONE : break;              //
    case MQRC_NO_MSG_AVAILABLE:          // Some reply messages received, but 
    {                                    // not all. Reply bag contains
      logMQCall(ERR,"mqExecute",mqrc);   // syste-generated bags for messages 
      mqExecRc=mqInquireErrBag(_resBag); // that were received
      goto _door;                        //
    }                                    //
    case MQRCCF_COMMAND_FAILED :         // PCF Command failed
    {                                    //
      logMQCall(ERR,"mqExecute",mqrc);   // Reply bag conatins syste-generated 
      mqExecRc=mqInquireErrBag(_resBag); // bags for messages that were received
      goto _door;                        //
    }                                    //
    default:                             //
    {                                    //
      logMQCall(ERR,"mqExecute",mqrc);   //
      goto _door;                        //
    }                                    //
  }                                      //
                                         //
  logMQCall(DBG,"mqExecute",mqrc);       //
                                         //
  _door:

  logFuncExit( ) ;

  if( mqExecRc == MQRC_NONE ) return mqrc ;
  return mqExecRc ;
}

/******************************************************************************/
/*   M Q   A D D   I N Q U I R E   A T T R I B U T E                          */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   Description: add attribute to inquire command                            */
/*                                                                            */
/*   Comment: this functions accept a list of inquire attributes.             */
/*            The nummber of inquire attributes is argc.                      */
/*            In order to set argc automaticly this function should           */
/*            be called ba mqSetInqAttr macro                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqAddInqAttrFunc( MQHBAG bag, int argc, ... )
{
  logFuncCall() ;

  MQLONG mqrc = MQRC_NONE ;
  MQLONG compCode ;

  va_list argp ;

  MQLONG attr ;

  int i;

  va_start( argp, argc );

  for( i=0; i<argc; i++ ) 
  {
    attr = va_arg( argp, MQLONG );
    mqAddInquiry( bag, attr, &compCode, &mqrc );

    switch( mqrc )
    {
      case MQRC_NONE : break ;
      default :
      {
        logMQCall( ERR, "mqAddInquiry", mqrc );  
	goto _door;
      }
    }
    logMQCall( DBG, "mqAddInquiry", mqrc);  
  }

  _door:

  va_end( argp );
  logFuncExit( ) ;
  return mqrc ;
}

/******************************************************************************/
/*   M Q   A D D   S T R I N G                                                */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   Description: add a string to the admin bag                               */
/*                                                                            */
/*   Comment: this functions is API for mqAddString                           */
/*                                                                            */
/*   Attributes:                                                              */
/*     @bag          : admin bag handle                                       */
/*     @selector     : selector for added string                              */
/*     @buffer length: the length of the buffer   or                          */
/*                     MQBL_NULL_TERMINATED if the string is null terminated  */
/*     @buffer       : the string to be added                                 */
/*     @comp code    :                                                        */
/*     @reason       :                                                        */
/*                                                                            */
/******************************************************************************/
MQLONG mqAddStr( MQHBAG _bag     , 
		 MQLONG _selector,
		 MQLONG _buffLng ,
		 PMQCHAR _buffer  )
{
  logFuncCall() ;

  MQLONG mqrc = MQRC_NONE ;
  MQLONG compCode ;

  mqAddString( _bag, _selector, _buffLng, _buffer, &compCode, &mqrc );

  switch( mqrc )
  {
    case MQRC_NONE : break ;
    default :
    {
      logMQCall( ERR, "mqAddString", mqrc );  
      goto _door;
    }
  }
  logMQCall( DBG, "mqAddString", mqrc);  

  _door:

  logFuncExit( ) ;
  return mqrc ;
}

/******************************************************************************/
/*   M Q   A D D   I N T E G E R                                              */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   Description: add an integer to the admin bag                             */
/*                                                                            */
/*   Comment: this functions is API for mqAddInteger                          */
/*                                                                            */
/*   Attributes:                                                              */
/*     @bag       : admin bag handle                                          */
/*     @selector  : selector for added string                                 */
/*     @item value: the integer value to be placed in the bag                 */
/*     @comp code :                                                           */
/*     @reason    :                                                           */
/*                                                                            */
/******************************************************************************/
MQLONG mqAddInt( MQHBAG _bag     , 
		 MQLONG _selector,
		 MQLONG _value )
{
  logFuncCall() ;

  MQLONG mqrc = MQRC_NONE ;
  MQLONG compCode ;

  mqAddInteger( _bag, _selector, _value, &compCode, &mqrc );

  switch( mqrc )
  {
    case MQRC_NONE : break ;
    default :
    {
      logMQCall( ERR, "mqAddInteger", mqrc );  
      goto _door;
    }
  }
  logMQCall( DBG, "mqAddInteger", mqrc);  

  _door:

  logFuncExit( ) ;
  return mqrc ;
}
/******************************************************************************/
/*   M Q   I N Q U I R E   R E S P O N S E   B A G                            */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   Description:  If the mqExecute (PCF) command fails get the system bag    */
/*                 handle out of the mqexecute response bag. This bag         */
/*                 contains the reason from the command server why the        */
/*                 command failed.             */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqInquireErrBag( MQHBAG _resBag )
{
  logFuncCall() ;

  MQLONG mqrc = MQRC_NONE ;
  MQLONG compCode ;

  MQHBAG errBag ;
  MQLONG mqExecuteRc ;
  

  // ------------------------------------------------------- 
  // get the error bag from response bag
  // ------------------------------------------------------- 
  mqInquireBag( _resBag        ,     // response bag from mqExecute
                MQHA_BAG_HANDLE,     // 
                0              ,     // index of the item
                &errBag        ,     // error bag
                &compCode      ,     // Completion code 
                &mqrc         );     // reason code
                                     //
  switch( mqrc )                     //
  {                                  //
    case MQRC_NONE : break;          //
    default:                         //
    {                                //
      logMQCall( ERR, "mqInquireBag", mqrc );  
      goto _door;                    //
    }                                //
  }                                  //
  logMQCall( DBG, "mqInquireBag", mqrc );  
                                     //
  // ------------------------------------------------------- 
  // Get the reason code, returned by the command server, 
  //   from the embedded error bag
  // ------------------------------------------------------- 
  mqInquireInteger( errBag       ,   // inquire erro bag
                    MQIASY_REASON,   // search for reason item
                    MQIND_NONE   ,   // dont't care about item index
                    &mqExecuteRc ,   // put the reason into this vara
                    &compCode    ,   // Completion code 
                    &mqrc       );   // general reason code
                                     //
  switch( mqrc )                     //
  {                                  //
    case MQRC_NONE: break ;          //
    default :                        //
    {                                //
      logMQCall( ERR, "mqInquireInteger", mqrc );  
      goto _door;                    //
    }                                //
  }                                  //
  logMQCall( DBG, "mqInquireInteger", mqrc );  

  logMQCall( ERR, "mqExecute-RC", mqExecuteRc );
                                     //
  _door:

  logFuncExit( ) ;

  if( mqrc != MQRC_NONE ) return -mqrc ;
  return mqExecuteRc ; 
}

/******************************************************************************/
/*   M Q   B A G   C O U N T   I T E M                                        */
/*   ----------------------------------------------------------------------   */
/*                                                                            */
/*   Description:  interface to mqCountItem                                   */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/*   Return Code:                                                             */
/*      RC > 0  : error, MQ Reason Code                                       */
/*      RC = 0  : no items found                                              */
/*      RC < 0  : negative noumber of itmes found                             */
/*                                                                            */
/******************************************************************************/
MQLONG mqBagCountItem( MQHBAG _bag, MQLONG _selector )
{
  logFuncCall() ;

  MQLONG compCode ;
  MQLONG mqrc = MQRC_NONE ;
 
  MQLONG itemCount ; 

  mqCountItems( _bag, _selector, &itemCount, &compCode, &mqrc );

  switch( mqrc )
  {
    case MQRC_NONE : 
    {
      mqrc = -itemCount;
      break ;
    }
    default:
    {
      logMQCall( ERR, "mqCountItems", mqrc );  
      goto _door;                    //
    }
  }
  logMQCall( DBG, "mqCountItems", mqrc );  

  _door:

  logFuncExit( ) ;
  return mqrc ;
}

/******************************************************************************/
/*  M Q   B A G   I N Q                                                       */
/*  ------------------------------------------------------------------------  */
/*                                                                            */
/*  Description: interface to mqInquireBag                                    */
/*                                                                            */
/*  Comment:                                                                  */
/*                                                                            */
/*  Return Code:                                                              */
/*                                                                            */
/******************************************************************************/
MQLONG mqBagInq( MQHBAG _inBag, MQLONG _cnt, PMQHBAG _outBag )
{
  logFuncCall() ;
  MQLONG mqrc = MQRC_NONE ;
  MQLONG cc ;

  mqInquireBag( _inBag, MQHA_BAG_HANDLE, _cnt, _outBag, &cc, &mqrc );
  switch( mqrc )
  {
    case MQRC_NONE : break ;
    default:
    {
      logMQCall( ERR, "mqInquireBag", mqrc );  
      goto _door;                    //
    }
  }
  logMQCall( DBG, "mqInquireBag", mqrc );  

  _door:

  logFuncExit( ) ;
  return mqrc ;
}

/******************************************************************************/
/*  M Q   S T R I N G   I N Q U I R E                                         */
/*  ------------------------------------------------------------------------  */
/*                                                                            */
/*  Description: interface to mqInquireString                                 */
/*                                                                            */
/*  Comment:                                                                  */
/*                                                                            */
/*  Return Code:                                                              */
/*                                                                            */
/******************************************************************************/
MQLONG mqStrInq( MQHBAG _bag       ,   // admin bag
                 MQLONG _selector  ,   // selector
                 MQLONG _itemIndex ,   // item index
                 MQLONG _maxBuffLng,   // buffer length
                 PMQCHAR _buffer   ,   // buffer
                 PMQLONG _lng      )   // real buffer length
{
  logFuncCall() ;

  MQLONG mqrc = MQRC_NONE ;
  MQLONG cc   ;

  mqInquireString( _bag       ,      // admin bag
                   _selector  ,      // selector 
                   _itemIndex ,      // item index
                   _maxBuffLng,      // available buffer length
		   _buffer    ,      // buffer
                   _lng       ,      // real buffer length
                   NULL       ,      // CCSID
                   &cc        ,      // comp code
                   &mqrc     );      // reason code
  switch( mqrc )      //
  {
    case MQRC_NONE : break ;
    default:
    {
      logMQCall( ERR, "mqInquireString", mqrc );  
      goto _door;                   
    }
    logMQCall( DBG, "mqInquireString", mqrc );  
  }

  _door:

  logFuncExit( ) ;
  return mqrc ;
}