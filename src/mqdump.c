/******************************************************************************/
/*                      M Q   D U M P   U T I L I T I E S                     */
/*                                                          */
/*  functions:                          */
/*   - dumper                            */
/*   - setDumpItemStr                                */
/*   - setDumpItemInt                  */
/*   - dumpMqObjDscr                                  */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <mqdump.h>
#include <mqtype.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/
#define DUMP_ITEM_CNT  47
#define DUMP_ITEM_SIZE 32

char _gDmpMsg[DUMP_ITEM_CNT*2]
             [DUMP_ITEM_SIZE] ;  // buffer for dump
int  _gDmpMsgIx ;                // index for line in dump buffer 

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define F_KEY       "%-25.25s"    // dump format for key
#define F_STR       "%-48.20s"    // dump format for general string
#define F_MQCHAR4   "%-48.4s"     // dump format for MQCHAR4
#define F_MQCHAR48  "%-48.48s"    // dump format for MQCHAR48
#define F_MQLONG    "%.10d"       // dump format for MQLONG

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
void setDumpItem( const char* frmt, const char* key, char* value )  ;

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/
// void dumpMqStruc( int _type, void* 

/******************************************************************************/
/* dump buffer to stdin                    */
/******************************************************************************/
void dumper( )
{
  int i ;

  for( i=0; i< DUMP_ITEM_CNT; i+=2 )
  {
    if( _gDmpMsg[i][0] == '\0' ) break ;
    printf( "%s: %s\n", _gDmpMsg[i], _gDmpMsg[i+1] ) ;
  }
}

/******************************************************************************/
/* set dump items for key of type strings       */
/******************************************************************************/
void setDumpItemStr( const char* frmt, const char* key, char* value )
{
   
  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;
  snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , value ) ;
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

/******************************************************************************/
/* set dump items for key of type mqlong       */
/******************************************************************************/
void setDumpItemInt( const char* frmt, const char* key, MQLONG value )
{
   
  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;
  snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , value ) ;
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

/******************************************************************************/
/* dump mq object description      */
/*                      */
/* dump MQOD                  */
/******************************************************************************/
void dumpMqObjDscr(  const PMQOD od )
{
  _gDmpMsgIx = 0 ;  

   setDumpItemStr(  F_MQCHAR4 , 
                   "Structure identifier",
                    od->StrucId); 

   setDumpItemStr( F_STR     , 
                   "Structure version"   ,
                   mqodVer2str(  od->Version));

   setDumpItemStr( F_STR     , 
                   "Object type"         ,
                   mqObjType2str(od->ObjectType));

   setDumpItemStr( F_MQCHAR48, 
                   "Object name"         ,   
                   od->ObjectName);

   setDumpItemStr( F_MQCHAR48, 
                   "Object queue manager name",   
                   od->ObjectQMgrName);

   setDumpItemStr( F_MQCHAR48, 
                   "Dynamic queue name",
                    od->DynamicQName);
#if(0)
   MQCHAR12  AlternateUserId;      /* Alternate user identifier */
   /* Ver:1 */
   MQLONG    RecsPresent;          /* Number of object records
                                      present */
   MQLONG    KnownDestCount;       /* Number of local queues opened
                                      successfully */
   MQLONG    UnknownDestCount;     /* Number of remote queues opened
                                      successfully */
   MQLONG    InvalidDestCount;     /* Number of queues that failed to
                                      open */
   MQLONG    ObjectRecOffset;      /* Offset of first object record
                                      from start of MQOD */
   MQLONG    ResponseRecOffset;    /* Offset of first response record
                                      from start of MQOD */
   MQPTR     ObjectRecPtr;         /* Address of first object record */
   MQPTR     ResponseRecPtr;       /* Address of first response
                                      record */
   /* Ver:2 */
   MQBYTE40  AlternateSecurityId;  /* Alternate security identifier */
   MQCHAR48  ResolvedQName;        /* Resolved queue name */
   MQCHAR48  ResolvedQMgrName;     /* Resolved queue manager name */
   /* Ver:3 */
   MQCHARV   ObjectString;         /* Object long name */
   MQCHARV   SelectionString;      /* Message Selector */
   MQCHARV   ResObjectString;      /* Resolved long object name*/
   MQLONG    ResolvedType;         /* Alias queue resolved object type */ 
#endif
  dumper() ;
}

