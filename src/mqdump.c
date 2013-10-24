/******************************************************************************/
/*                      M Q   D U M P   U T I L I T I E S                     */
/*                                                                            */
/*  functions:                                                                */
/*   - dumpMqStruct                                                           */
/*   - mqDumper                                                               */
/*   - setDumpItemStr                                                         */
/*   - setDumpItemInt                                                         */
/*   - setDumpItemPtr                                                         */
/*   - setDumpItemByte                                                        */
/*   - setDumpItemCharV                                                       */
/*   - dumpMqObjDscr                                                          */
/*   - dumpMqMsgDscr                                                          */
/*   - dumpMqPutMsgOpt                                        */
/*   - dumpMqGetMsgOpt                                    */
/*   - dumpMqBag            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// mq
// ---------------------------------------------------------
#include <cmqc.h>
#include <cmqcfc.h>
#include <cmqbc.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <mqdump.h>
#include <mqtype.h>
#include <mqbase.h>

#include <ctl.h>
#include <lgmqm.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/
#define DUMP_ITEM_CNT  48
#define DUMP_ITEM_SIZE DMP_ITEM_LEN  // DMP_ITEM_LEN defined in "ctl.h"

char _gDmpMsg[DUMP_ITEM_CNT*2]
             [DUMP_ITEM_SIZE] ;      // buffer for dump
int  _gDmpMsgIx ;                    // index for line in dump buffer 

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define ITEM_STRING_LENGTH    500

#define F_KEY       "%-35.35s"    // dump format for key
#define F_STR       "%-48.25s"    // dump format for general string
#define F_MQPTR     "%-48.8s"     // dump format for general pointer
#define F_MQCHAR    "%c"          // dump format for MQCHAR4
#define F_MQCHAR4   "%-48.4s"     // dump format for MQCHAR4
#define F_MQCHAR8   "%-48.8s"     // dump format for MQCHAR8
#define F_MQCHAR12  "%-48.12"     // dump format for MQCHAR12
#define F_MQCHAR28  "%-48.28s"    // dump format for MQCHAR28
#define F_MQCHAR32  "%-48.32s"    // dump format for MQCHAR32
#define F_MQCHAR48  "%-48.48s"    // dump format for MQCHAR48
#define F_MQCHARV   "%-48.20s"    // dump format for MQCHARV dummy
#define F_MQLONG    "%.10d"       // dump format for MQLONG
#define F_MQHMSG    "%.10d"       // dump format for MQHMSG
#define F_MQBYTE16     16         // length of hex string
#define F_MQBYTE24     24         // length of hex string
#define F_MQBYTE32     32         // length of hex string
#define F_MQBYTE40     40         // length of hex string

/******************************************************************************/
/*   T Y P E S                                                                */
/******************************************************************************/
typedef enum   tagItemType   tItemType   ;

/******************************************************************************/
/*   S T R U C T S                                                            */
/******************************************************************************/
enum tagItemType { UNKNOWN, STRING, DIGIT } ;


/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
#define setDumpItemCharV( frmt, \
                          key , \
                          value )   setDumpItemStr( frmt, \
                                                    key , \
                                                   "MQCHARV Struct" ) ;

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
void setDumpItemStr(  const char* frmt, const char* key, char*   value ) ;
void setDumpItemInt(  const char* frmt, const char* key, MQLONG  value ) ;
void setDumpItemPtr(  const char* frmt, const char* key, MQPTR   value ) ;
void setDumpItemByte(         int frmt, const char* key, PMQBYTE value ) ;

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/
void dumpMqStruct( const char* _type, void* _pStruct, FILE* output  )
{

  // -------------------------------------------------------
  // Object description dump
  // -------------------------------------------------------
  if( memcmp( _type, MQOD_STRUC_ID, 4 ) == 0 )
  {
    dumpMqObjDscr(  (PMQOD) _pStruct ) ;
    goto _output ; 
  }

  // -------------------------------------------------------
  // Message description dump
  // -------------------------------------------------------
  if( memcmp( _type, MQMD_STRUC_ID, 4 ) == 0 )
  {
    dumpMqMsgDscr(  (PMQMD) _pStruct ) ;
    goto _output ; 
  }

  // -------------------------------------------------------
  // Put message option dump
  // -------------------------------------------------------
  if( memcmp( _type, MQPMO_STRUC_ID, 4 ) == 0 )
  {
    dumpMqPutMsgOpt( (PMQPMO) _pStruct ) ;
    goto _output ; 
  }

  // -------------------------------------------------------
  // Put message option dump
  // -------------------------------------------------------
  if( memcmp( _type, MQGMO_STRUC_ID, 4 ) == 0 )
  {
    dumpMqGetMsgOpt( (PMQGMO) _pStruct ) ;
    goto _output ; 
  }

  // -------------------------------------------------------
  // Bag
  // -------------------------------------------------------
  if( memcmp( _type, "MQBAG", 4 ) == 0 )
  {
    dumpMqBag( *((PMQHBAG) _pStruct) ) ;
    goto _output ; 
  }

  // -------------------------------------------------------
  // if you get that far, then it has to be unkonwn struct
  // -------------------------------------------------------
  logger( LMQM_UNKNOWN_DMP_STRUCT, _type ) ;
  goto _door ;

  _output :

  if( output == NULL )
  {
    if( getLogFP() != NULL ) 
    {
      dumper( "| ", _type, _gDmpMsg ) ;
    }
    else
    {
      output = stderr ;
    }
  }

  if( output == stderr )
  {
    mqDumper( stderr ) ;
    goto _door ;
  }
  
  if( output == stdout )
  {
    mqDumper( stderr ) ;
    goto _door ;
  }

  _door :

  return ;
}

/******************************************************************************/
/* dump buffer to stdin                                                       */
/******************************************************************************/
void mqDumper( FILE *output )
{
  int i ;

  for( i=0; i< DUMP_ITEM_CNT; i+=2 )
  {
    if( _gDmpMsg[i][0] == '\0' ) break ;
    fprintf( output, "%s: %s\n", _gDmpMsg[i], _gDmpMsg[i+1] ) ;
  }
}

/******************************************************************************/
/* set dump items for key of type strings                                   */
/******************************************************************************/
void setDumpItemStr( const char* frmt, const char* key, char* value )
{
   
  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;
  snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , value ) ;
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

/******************************************************************************/
/* set dump items for key of type mqlong                               */
/******************************************************************************/
void setDumpItemInt( const char* frmt, const char* key, MQLONG value )
{
   
  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;
  snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , value ) ;
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

/******************************************************************************/
/* set dump items for key of type pointer                          */
/******************************************************************************/
void setDumpItemPtr( const char* frmt, const char* key, MQPTR value )  
{

  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;
 
  if( value == NULL ) 
  {
    snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , "null" ) ;
  }
  else
  {
    snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , "pointer" ) ;
  }
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

#if(0)
/******************************************************************************/
/* set dump items for key of type mqcahrv (Variable-length string)            */
/******************************************************************************/
void setDumpItemCharV( const char* frmt, const char* key, MQPTR value )  
{

  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;

  snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt, "MQCHARV Struct" ) ;

  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}
#endif

/******************************************************************************/
/* set dump items for key of type mqbyte                                */
/******************************************************************************/
void setDumpItemByte( int frmt, const char* key, PMQBYTE value ) 
{
  int i ;

  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;

  sprintf( _gDmpMsg[_gDmpMsgIx*2+1], "0x" ) ;
  for( i=0; i<frmt; i++ )
  {
    sprintf( &(_gDmpMsg[_gDmpMsgIx*2+1][3*i+2]), " %.2x", value[i] ) ;
  }
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

/******************************************************************************/
/* dump mq object description                                                 */
/*                                                                            */
/* dump MQOD                                                                  */
/******************************************************************************/
void dumpMqObjDscr(  const PMQOD od )
{
  _gDmpMsgIx = 0 ;  

   setDumpItemStr(  F_MQCHAR4             ,
                   "Structure identifier" ,
                    od->StrucId          ); 

   setDumpItemStr(  F_STR               ,
                   "Structure version"  ,
                   (char*) mqodVer2str( od->Version ) );

   setDumpItemStr(  F_STR           ,
                   "Object type"    ,
                   (char*) mqObjType2str(od->ObjectType) ) ;

   setDumpItemStr(  F_MQCHAR48     ,
                   "Object name"   ,   
                    od->ObjectName );

   setDumpItemStr( F_MQCHAR48                  ,
                   "Object queue manager name" ,   
                    od->ObjectQMgrName       ) ;

   setDumpItemStr(  F_MQCHAR48          ,
                   "Dynamic queue name" ,
                    od->DynamicQName  ) ;

   setDumpItemStr(  F_MQCHAR12          ,
                   "Alternate user id"  ,
                    od->AlternateUserId ) ;      

  // -------------------------------------------------------
  // version 2 or higher
  // -------------------------------------------------------
  if( od->Version < MQOD_VERSION_2 ) goto _door ;
   
  setDumpItemInt(  F_MQLONG                   ,
                  "Nr of obj records present" ,
                   od->RecsPresent          ) ;

  setDumpItemInt(  F_MQLONG                ,
                  "Nr of qlocal opened ok" ,
                   od->KnownDestCount    ) ;

  setDumpItemInt(  F_MQLONG                 ,
                  "Nr of qremote opened ok" ,
                   od->UnknownDestCount   ) ;

  setDumpItemInt(  F_MQLONG                     ,
                  "Nr of queues failed to open" ,
                   od->InvalidDestCount       ) ;

  setDumpItemInt(  F_MQLONG                      ,
                  "Offset MQOD start to 1st obj" ,
                   od->ObjectRecOffset         ) ;

  setDumpItemInt(  F_MQLONG                           ,
                  "Offset MQOD start to 1st response" ,
                   od->ResponseRecOffset            ) ;

  setDumpItemPtr(  F_MQPTR                       ,
                  "Address of 1st object record" ,
                   od->ObjectRecPtr            ) ;

  setDumpItemPtr(  F_MQPTR                           ,
                  "Address of first response record" ,
                   od->ResponseRecPtr              ) ;

  // -------------------------------------------------------
  // version 3 or higher
  // -------------------------------------------------------
  if( od->Version < MQOD_VERSION_3 ) goto _door ;

  setDumpItemByte(  F_MQBYTE40           ,
                   "Alternate security identifier" ,
                    od->AlternateSecurityId      ) ;

   setDumpItemStr(  F_MQCHAR48           ,
                   "Resolved queue name" ,
                    od->ResolvedQName  ) ;

   setDumpItemStr(  F_MQCHAR48                   ,
                   "Resolved queue manager name" ,
                    od->ResolvedQMgrName       ) ;

  // -------------------------------------------------------
  // version 4 or higher
  // -------------------------------------------------------
  if( od->Version < MQOD_VERSION_4 ) goto _door ;

   setDumpItemCharV(  F_MQCHARV          ,
                     "Object long name"  ,
                      od->ObjectString ) ;

   setDumpItemCharV(  F_MQCHARV             ,
                     "Message Selector"     ,
                      od->SelectionString ) ;

   setDumpItemCharV(  F_MQCHARV                  ,
                     "Resolved long object name" ,
                      od->ResObjectString      ) ;

   setDumpItemStr(  F_STR                                    ,
                   "qalias resolved object type"             ,
                   (char*) mqObjType2str(od->ResolvedType) ) ;
  _door :

  return ;
}

/******************************************************************************/
/* dump mq message description                                                */
/*                                                                            */
/* dump MQMD                                                                  */
/******************************************************************************/
void dumpMqMsgDscr(  const PMQMD md )
{
  _gDmpMsgIx = 0 ;  
  
  setDumpItemStr(  F_MQCHAR4             ,
                  "Structure identifier" ,
                   md->StrucId           );           
 
  setDumpItemStr(  F_STR                 ,
                  "Structure version"    ,
                  (char*) mqmdVer2str(md->Version) );

  setDumpItemStr(  F_STR                ,
                  "Report msgs options" ,
                   (char*) mqReportOption2str(md->Report) );

  setDumpItemStr(  F_STR                ,
                   "Msg type"           ,
                   (char*) mqMsgType2str(md->MsgType) );           

  setDumpItemInt(  F_MQLONG             ,
                  "Msg lifetime"        ,
                   md->Expiry           );

  setDumpItemStr(  F_STR                ,
                  "Feedback code"       ,
                  (char*) mqFeedback2str( md->Feedback) );

  setDumpItemStr(  F_STR                      ,
                  "Msg data numeric encoding" ,
                  (char*) mqEncondig2str(md->Encoding) );

  setDumpItemStr(  F_STR           ,
                  "Msg data CCSID" ,
                  (char*) mqCCSID2str(md->CodedCharSetId) );
  
  setDumpItemStr(  F_MQCHAR8             ,
                  "Msg data Format name" ,
                   md->Format            );            
    
  setDumpItemStr(  F_STR                 ,
                  "Message priority"     ,
                  (char*) mqPriority2str(md->Priority) );          
      
  setDumpItemStr(  F_STR                 ,
                  "Message persistence"  ,
                  (char*)mqPersistence2str(md->Persistence) );
      
  setDumpItemByte(  F_MQBYTE24           ,
                   "Message identifier"  ,
                    md->MsgId            );
      
  setDumpItemByte(  F_MQBYTE24              ,
                   "Correlation identifier" ,
                    md->CorrelId            );
      
  setDumpItemInt(  F_MQLONG                 ,
                  "Backout counter"         ,
                   md->BackoutCount         );
    
  setDumpItemStr(  F_MQCHAR48               ,
                  "Name of reply queue"     ,
                   md->ReplyToQ             );
    
  setDumpItemStr(  F_MQCHAR48               ,
                  "Name of reply qmgr"      ,
                   md->ReplyToQMgr          );
     
  setDumpItemStr(  F_MQCHAR12               ,
                  "User identifier"         ,
                   md->UserIdentifier       );
    
  setDumpItemByte(  F_MQBYTE32              ,
                   "Accounting token"       ,
                    md->AccountingToken     );
    
  setDumpItemStr(  F_MQCHAR32                   ,
                  "Appl data relating identity" ,
                   md->ApplIdentityData         );
  
  setDumpItemStr(  F_STR          ,
                  "Appl Put Type" ,
                  (char*) mqPutApplType2str(md->PutApplType) );

  setDumpItemStr(  F_MQCHAR28         ,
                  "Putting appl name" ,
                   md->PutApplName    );       

  setDumpItemStr(  F_MQCHAR8          ,
                  "Put Date"          ,
                   md->PutDate        );
    
  setDumpItemStr(  F_MQCHAR8          ,
                  "Put time"          ,
                   md->PutTime        );

  setDumpItemStr(  F_MQCHAR4                     ,
                  "Appl data relating to origin" ,
                   md->ApplOriginData            );

  // -------------------------------------------------------
  // msg dscr version 2 or higher
  // -------------------------------------------------------
  if( md->Version < MQMD_VERSION_2 ) goto _door ;

  setDumpItemByte(  F_MQBYTE24        , 
                   "Group identifier" , 
                    md->GroupId       );

  setDumpItemInt(  F_MQLONG                       , 
                  "SeqNr of logical msg in group" , 
                   md->MsgSeqNumber               );

  setDumpItemInt(  F_MQLONG                         , 
                  "PhysMsg Offset from logic start" , 
                   md->Offset                       );

  setDumpItemStr(  F_STR          , 
                  "Message flags" , 
                   (char*) mqMsgFlag2str(md->MsgFlags) );

  setDumpItemInt(  F_MQLONG                    , 
                  "Length of original message" ,
                   md->OriginalLength          );

  _door :

  return ;
}

/******************************************************************************/
/* dump mq put message options                                                */
/*                                                                            */
/* dump MQPMO                                                                 */
/******************************************************************************/
void dumpMqPutMsgOpt(  const PMQPMO pmo )
{
  _gDmpMsgIx = 0 ;  

  setDumpItemStr(  F_MQCHAR4             ,
                  "Structure identifier" ,
                   pmo->StrucId          );           

  setDumpItemStr(  F_STR                 ,
                  "Structure version"    ,
                  (char*) mqpmoVer2str(pmo->Version) );

  setDumpItemInt(  F_MQLONG          ,
                  "MQPUT Options"  ,
                   pmo->Options    );

  setDumpItemInt(  F_MQLONG           ,
                  "Timout Reserved" ,
                   pmo->Timeout     );

  setDumpItemInt(  F_MQLONG     ,
                  "Obj handle"  ,
                   pmo->Context );      

  setDumpItemInt(  F_MQLONG         ,
                  "Nr of msgs put on qlocal" ,
                   pmo->KnownDestCount );

  setDumpItemInt(  F_MQLONG                   ,
                  "Nr of msgs put on qremote" ,
                   pmo->UnknownDestCount      );

  setDumpItemInt(  F_MQLONG              ,
                  "Nr of puts failed"    ,
                   pmo->InvalidDestCount );
                                   
 
   setDumpItemStr(  F_MQCHAR48           ,
                   "Resolved queue name" ,
                    pmo->ResolvedQName   ) ;

   setDumpItemStr(  F_MQCHAR48            ,
                   "Resolved qmgr name"   ,
                    pmo->ResolvedQMgrName ) ;

  // -------------------------------------------------------
  // msg dscr version 2 or higher
  // -------------------------------------------------------
  if( pmo->Version < MQPMO_VERSION_2 ) goto _door ;

  setDumpItemInt(  F_MQLONG                    ,
                  "Nr of put or response records present" ,
                   pmo->RecsPresent ); 

  setDumpItemInt(  F_MQLONG             ,
                  "MQPMR flags"         ,
                   pmo->PutMsgRecFields );
   
  setDumpItemInt(  F_MQLONG                   ,
                  "Offset of 1st put record from MQPMO" ,
                   pmo->PutMsgRecOffset );    

  setDumpItemInt(  F_MQLONG                   ,
                  "Offset of 1st response record from MQPMO" ,
                   pmo->ResponseRecOffset );  

  setDumpItemPtr(  F_MQPTR,     
                  "Address of first put message"  ,
                   pmo->PutMsgRecPtr );       
                   
  setDumpItemPtr(  F_MQPTR,     
                  "Address of first response record"  ,
                   pmo->ResponseRecPtr  );     
  
  // -------------------------------------------------------
  // msg dscr version 3 or higher
  // -------------------------------------------------------
  if( pmo->Version < MQPMO_VERSION_3 ) goto _door ;
    
   setDumpItemInt( F_MQHMSG  ,
                  "Original message handle" ,
                   pmo->OriginalMsgHandle );

   setDumpItemInt( F_MQHMSG             ,
                  "New message handle"  ,
                   pmo->NewMsgHandle    );  

  setDumpItemInt(  F_MQLONG                    ,
                  "The action being performed" ,
                   pmo->Action                 );             

  setDumpItemInt(  F_MQLONG           ,
                  "Publication level" ,
                   pmo->PubLevel      );

  _door :

  return ;
}

/******************************************************************************/
/* dump mq get message options                                                */
/*                                                                            */
/* dump MQGMO                                                                 */
/******************************************************************************/
void dumpMqGetMsgOpt(  const PMQGMO gmo )
{
  _gDmpMsgIx = 0 ;  

  setDumpItemStr(  F_MQCHAR4             ,
                  "Structure identifier" ,
                   gmo->StrucId          );           

  setDumpItemStr(  F_STR                 ,
                  "Structure version"    ,
                  (char*) mqgmoVer2str(gmo->Version) );

  setDumpItemInt(  F_MQLONG          ,
                  "MQGET Options"    ,
                   gmo->Options      );

  setDumpItemInt(  F_MQLONG          ,
                  "Wait interval"    ,
                   gmo->WaitInterval );

  setDumpItemInt(  F_MQLONG       ,
                  "Signal1"       ,
                   gmo->Signal1  );

  setDumpItemInt(  F_MQLONG      ,
                  "Signal1"      ,
                   gmo->Signal2  );

   setDumpItemStr(  F_MQCHAR48   ,
                   "Resolved destination q name" ,
                    gmo->ResolvedQName          );

  // -------------------------------------------------------
  // get message option version 2 or higher
  // -------------------------------------------------------
  if( gmo->Version < MQGMO_VERSION_2 ) goto _door ;

  setDumpItemInt(  F_MQLONG                  ,
                  "Selection MQGET criteria" ,
                   gmo->MatchOptions         );

  setDumpItemInt(  F_MQCHAR              ,
                  "Flag if msg in group" ,
                   gmo->GroupStatus      );

  setDumpItemInt(  F_MQCHAR                      ,
                  "msg logical or physical flag" ,
                   gmo->SegmentStatus           );

  setDumpItemInt(  F_MQCHAR                       ,
                  "flag for further segmentation" ,
                   gmo->Segmentation             );

#if(0)
   MQCHAR    Reserved1;       /* Reserved */
#endif
  // -------------------------------------------------------
  // get message option version 2 or higher
  // -------------------------------------------------------
  if( gmo->Version < MQGMO_VERSION_3 ) goto _door ;
  setDumpItemByte(  F_MQBYTE16     ,
                   "message token" ,
                    gmo->MsgToken  );

  setDumpItemInt(  F_MQLONG                         ,
                  "Length of message data returned" ,
                   gmo->ReturnedLength              );

  // -------------------------------------------------------
  // get message option version 3 or higher
  // -------------------------------------------------------
  if( gmo->Version < MQGMO_VERSION_4 ) goto _door ;

#if(0)
   MQLONG    Reserved2;       /* Reserved */
#endif

   setDumpItemInt( F_MQHMSG         ,
                   "Message handle" ,
                   gmo->MsgHandle   );       

  _door :
  return ;
}

/******************************************************************************/
/* dump mq get message options                                                */
/*                                                                            */
/* dump MQGMO                                                                 */
/******************************************************************************/
void dumpMqBag( MQHBAG bag )
{
  _gDmpMsgIx = 0 ;  

  MQLONG itemCount;
  MQLONG itemType ;
  MQLONG selector ;

  MQINT32 iVal ;

  MQCHAR itemStrBuffer[ITEM_STRING_LENGTH+1];
  MQLONG itemStrLength;
  MQLONG iCCSID;

  MQLONG mqlongVal ;
  char  *mqstrVal  ;

  MQLONG compCode;
  MQLONG reason  ;
  int    i       ;

  // -------------------------------------------------------
  // count items in the bag
  // -------------------------------------------------------
  mqCountItems( bag                ,                 // 
                MQSEL_ALL_SELECTORS,                 //
                &itemCount         ,                 //
                &compCode          ,                 //
                &reason           );                 //
                                                     //
  switch( reason )                                   // handle error count items
  {                                                  //
    case MQRC_NONE : break;                          //
    default :                                        //
    {                                                //
      logMQCall(DBG,"mqCountItems",reason);          //
      goto _door;                                    //
    }                                                //
  }                                                  //
  logger( LMQM_ITEM_COUNT, itemCount );              //
                                                     //
  // -------------------------------------------------------
  // go through all items
  // -------------------------------------------------------
  for( i=0; i<itemCount; i++ )                       // mqstrVal will stay NULL
  {                                                  // if item type is intiger
    mqstrVal = NULL;                                 // which can not be 
                                                     // converted to string
    // -----------------------------------------------------
    // get item type
    // -----------------------------------------------------
    mqInquireItemInfo( bag               ,           // get selector(id)
                       MQSEL_ANY_SELECTOR,           //  and item type
                       i                 ,           //
                       &selector         ,           //
                       &itemType         ,           //
                       &compCode         ,           //
                       &reason          );           //
                                                     //
    switch( reason )                                 //
    {                                                //
      case MQRC_NONE : break;                        //
      default :                                      //
      {                                              //
        logMQCall(DBG,"mqCountItems",reason);        //
        goto _door;                                  //
      }                                              //
    }                                                //
    logger(LMQM_ITEM_TYPE,mqItemType2str(itemType)); //
                                                     //
    // -----------------------------------------------------
    // analyse the item type
    // -----------------------------------------------------
    switch( itemType )                               //
    {                                                //
      // ---------------------------------------------------
      //  handle INTIGER item 
      // ---------------------------------------------------
      case MQITEM_INTEGER :                          //
      {                                              //
        mqInquireInteger( bag               ,        //
                          MQSEL_ANY_SELECTOR,        //
                          i                 ,        //
                          &iVal             ,        //
                          &compCode         ,        //
                          &reason          );        //
        mqlongVal = (MQLONG) iVal;                   //
        mqstrVal = (char*) itemValue2str(selector  , // try to convert to string
                                         mqlongVal); //
        break;                                       //
      }                                              //
      // ---------------------------------------------------
      //  handle STRING item 
      // ---------------------------------------------------
      case MQITEM_STRING :                           //
      {                                              //
        mqInquireString( bag               ,         //
                         MQSEL_ANY_SELECTOR,         //
                         i                 ,         //
                         ITEM_STRING_LENGTH,         //
                         itemStrBuffer     ,         //
                         &itemStrLength    ,         //
                         &iCCSID           ,         //
                         &compCode         ,         //
                         &reason          );         //
        mqstrVal = (char*) itemStrBuffer   ;         //
        break;                                       //
      }                                              //
      case MQITEM_BAG :                              //
      {                                              //
        break;                                       //
      }                                              //
      case MQITEM_BYTE_STRING :                      //
      {                                              //
        break;                                       //
      }                                              //
      case MQITEM_INTEGER_FILTER :                   //
      {                                              //
        break;                                       //
      }                                              //
      case MQITEM_STRING_FILTER :                    //
      {                                              //
        break;                                       //
      }                                              //
      case MQITEM_INTEGER64 :                        //
      {                                              //
        break;                                       //
      }                                              //
      case MQITEM_BYTE_STRING_FILTER :               //
      {                                              //
        break;                                       //
      }                                              //
    }                                                //
                                                     //
    switch( reason )                                 //
    {                                                //
      case MQRC_NONE : break;                        //
      default :                                      //
      {                                              //
        logMQCall(DBG,"mqInquire???",reason);        //
        goto _door;                                  //
      }                                              //
    }                                                //
                                                     //
    if( mqstrVal )                                   //
    {                                                //
      setDumpItemStr(  F_STR                  ,      //
                      mqSelector2str(selector),      //
                      mqstrVal               );      //
    }                                //
    else                      //
    {                                            //
      setDumpItemInt( F_MQLONG                ,      //
                      mqSelector2str(selector),  //
                      mqlongVal ) ;        //
    }                                            //
                            //
  }                                                //
                                                     //  
  _door:
  return; 
}
