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
/*    - mqCommit                                                        */
/*    - mqRollback                                                        */
/*    - resizeMqMessageBuffer                                                 */
/*    - mqSetTrigger                                                    */
/*    - mqOpenBagAPI                                                          */
/*    - mqReadBag                                                             */
/*    - mqCloseBag                                                            */
/*    - mqResetQmgrLog                                                  */
/*                                                                            */
/*  macros:                                          */
/*    - mqOpenUserBag                              */
/*    - mqOpenAdminBag                      */
/*                              */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
#define C_MODULE_MQ_BASE

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdlib.h>

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
  logger( LMQM_QMGR_CONNECTED, qmName[0] == '\0' ? "default" : qmName );

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
/*   Descrip: read messages from the queue,                                   */
/*            read options were set by calling mqOpen                         */
/*                                                                            */
/*   Comment:                                                                 */
/*                                                                            */
/******************************************************************************/
MQLONG mqGet( MQHCONN _hConn     ,      // connection handle
              MQHOBJ  _hQueue    ,      // pointer to queue handle
              PMQVOID _buffer    ,      // message buffer
              PMQLONG  _bufLng   ,      // buffer length
              PMQMD   _msgDscr   ,      // msg Desriptor
              MQGMO   _getMsgOpt ,      // get message option 
              MQLONG  _wait      )      // wait interval
{                                       //
  logFuncCall() ;

  MQLONG compCode ;                  // Completion code
  MQLONG reason   ;                  // Reason code qualifying CompCode
                                     //
  MQLONG  msgLng  ;                  // Length of the message
                                     //
//int loop = 0 ;                     // flag breaking loop

  // -------------------------------------------------------
  // set get messages options
  // -------------------------------------------------------
  _getMsgOpt.Options |= MQGMO_FAIL_IF_QUIESCING    // fail if quiesching
                     +  MQGMO_CONVERT;             // convert if necessary
                                                   //
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
    case MQRC_NO_MSG_AVAILABLE:                    // finding no message is not
    {                                              //  an error per default
      logMQCall( DBG, "MQGET", reason );           //
      break;                                       //
    }                                              //
                                                   //
    case MQRC_TRUNCATED_MSG_FAILED :               // msg buffer to small
    {                                              //  resize (realloc) msg buff
      *_bufLng = msgLng;                           //
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
/*   M Q    R E S I Z E   M E S S A G E                                     */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Description: resize message buffer                                     */
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

  *bag = MQHB_UNUSABLE_HBAG;

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
/*            */
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
  if( sysRc != MQRC_NONE ) return sysRc ;

  // -------------------------------------------------------
  // create an admin bag for the mqExecute call
  // -------------------------------------------------------
  sysRc = mqOpenAdminBag( &responBag ) ;
  if( sysRc != MQRC_NONE ) return sysRc ;

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
      return reason ;
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


  if( compCode == MQCC_FAILED)
  {
    logMQCall(ERR,"mqExecute",reason);  

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
  }

  logMQCall(ERR,"RC(mqExec)",execCompCode);  

  return (int) execReason ;
}

