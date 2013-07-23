/******************************************************************************/
/*                      M Q   D U M P   U T I L I T I E S                     */
/*                                                                            */
/*  functions:                                                                */
/*   - dumpMqStruct                                                      */
/*   - mqDumper                                                               */
/*   - setDumpItemStr                                                         */
/*   - setDumpItemInt                                                         */
/*   - setDumpItemPtr                                                         */
/*   - setDumpItemByte                                                        */
/*   - setDumpItemCharV                                                       */
/*   - dumpMqObjDscr                                                          */
/*   - dumpMqMsgDscr                  */
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
// own 
// ---------------------------------------------------------
#include <mqdump.h>
#include <mqtype.h>

#include <ctl.h>
#include <lgmqm.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/
#define DUMP_ITEM_CNT  47
#define DUMP_ITEM_SIZE DMP_ITEM_LEN   // DMP_ITEM_LEN defined in "ctl.h"

char _gDmpMsg[DUMP_ITEM_CNT*2]
             [DUMP_ITEM_SIZE] ;  // buffer for dump
int  _gDmpMsgIx ;                // index for line in dump buffer 

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define F_KEY       "%-30.30s"    // dump format for key
#define F_STR       "%-48.20s"    // dump format for general string
#define F_MQPTR     "%-48.8s"     // dump format for general pointer
#define F_MQCHAR4   "%-48.4s"     // dump format for MQCHAR4
#define F_MQCHAR12  "%-48.12"     // dump format for MQCHAR12
#define F_MQCHAR48  "%-48.48s"    // dump format for MQCHAR48
#define F_MQCHARV   "%-48.20s"    // dump format for MQCHARV dummy
#define F_MQLONG    "%.10d"       // dump format for MQLONG
#define F_MQBYTE40     40         // length of hex string

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
void setDumpItemInt(  const char* frmt, const char* key, int     value ) ;
void setDumpItemPtr(  const char* frmt, const char* key, MQPTR   value ) ;
void setDumpItemByte(         int frmt, const char* key, PMQBYTE value ) ;

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/
void dumpMqStruct( const char* _type, void* _pStruct, FILE* output  )
{

  if( memcmp( _type, MQOD_STRUC_ID, 4 ) == 0 )
  {
    dumpMqObjDscr(  (PMQOD) _pStruct ) ;
    goto _output ; 
  }

  if( memcmp( _type, MQMD_STRUC_ID, 4 ) == 0 )
  {
    dumpMqMsgDscr(  (PMQMD) _pStruct ) ;
    goto _output ; 
  }

  logger( LMQM_UNKNOWN_DMP_STRUCT, _type ) ;
  goto _door ;

  _output :

  if( output == NULL )
  {
    if( getLogFP() != NULL ) 
    {
      dumper( "  ", _type, _gDmpMsg ) ;
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
/* set dump items for key of type mqbyte                              */
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

   setDumpItemStr(  F_MQCHAR12                 ,
                   "Alternate user identifier" ,
                    od->AlternateUserId      ) ;      

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

  setDumpItemStr(  F_MQCHAR4            ,
                  "Structure identifier",
                   md->StrucId          );           


   setDumpItemStr(  F_STR               ,
                   "Structure version"  ,
                   (char*) mqmdVer2str( md->Version ) );

// MQRO in einer endlos && auf einzelne teile aufbrechen
#if(0)
  F_MQLONG    
Report;            
"Options for report messages"

  F_MQLONG    
MsgType;           
"Message type"

  F_MQLONG    
Expiry;            
"Message lifetime"

  F_MQLONG    
Feedback;          
"Feedback or reason code"

  F_MQLONG    
Encoding;          
"Numeric encoding of message data"

  F_MQLONG    
CodedCharSetId;    
"Character set identifier of message data"

  F_MQCHAR8   
Format;            
"Format name of message data"

  F_MQLONG    
Priority;          
"Message priority"

  F_MQLONG    
Persistence;       
"Message persistence"

  F_MQBYTE24  
MsgId;             
"Message identifier"

  F_MQBYTE24  
CorrelId;          
"Correlation identifier"

  F_MQLONG    
BackoutCount;      
"Backout counter"

  F_MQCHAR48  
ReplyToQ;          
"Name of reply queue"

  F_MQCHAR48  
ReplyToQMgr;       
"Name of reply queue manager"

  F_MQCHAR12  
UserIdentifier;    
"User identifier"

  F_MQBYTE32  
AccountingToken;   
"Accounting token"

  F_MQCHAR32  
ApplIdentityData;  
"Application data relating to identity"

  F_MQLONG    
PutApplType;      
 "Type of application that put the message"

  F_MQCHAR28  
PutApplName;       
"Name of application that put the message"

  F_MQCHAR8   
PutDate;           
"Date when message was put"

  F_MQCHAR8   
PutTime;           
"Time when message was put"

  F_MQCHAR4   
ApplOriginData;    
"Application data relating to origin"

   /* Ver:1 */
  F_MQBYTE24  
GroupId;           
"Group identifier"

  F_MQLONG    
MsgSeqNumber;      
"Sequence number of logical message within group"

  F_MQLONG    
Offset;            
"Offset of data in physical message from start of logical message"

  F_MQLONG    
MsgFlags;          
"Message flags"

  F_MQLONG    
OriginalLength;    
"Length of original message"

   /* Ver:2 */
#endif

  _door :

  return ;
}
