/******************************************************************************/
/*                      M Q   D U M P   U T I L I T I E S                     */
/*                                                                            */
/*  functions:                                                                */
/*   - dumper                                                                 */
/*   - setDumpItemStr                                                         */
/*   - setDumpItemInt                                                         */
/*   - setDumpItemPtr                                */
/*   - setDumpItemByte                                */
/*   - setDumpItemCharV              */
/*   - dumpMqObjDscr                                                          */
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
#define DUMP_ITEM_SIZE 50

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
#define F_MQLONG    "%.10d"       // dump format for MQLONG
#define F_MQBYTE40     40         // length of hex string

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
void setDumpItemStr(  const char* frmt, const char* key, char*   value ) ;
void setDumpItemInt(  const char* frmt, const char* key, int     value ) ;
void setDumpItemPtr(  const char* frmt, const char* key, MQPTR   value ) ;
void setDumpItemByte(         int frmt, const char* key, PMQBYTE value ) ;
void setDumpItemCharV(        int frmt, const char* key, MQCHARV value ) ;

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/
// void dumpMqStruc( int _type, void* 

/******************************************************************************/
/* dump buffer to stdin                                                */
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
/* set dump items for key of type strings                 */
/******************************************************************************/
void setDumpItemStr( const char* frmt, const char* key, char* value )
{
   
  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;
  snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , value ) ;
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

/******************************************************************************/
/* set dump items for key of type mqlong         */
/******************************************************************************/
void setDumpItemInt( const char* frmt, const char* key, MQLONG value )
{
   
  snprintf( _gDmpMsg[_gDmpMsgIx*2  ], DUMP_ITEM_SIZE, F_KEY, key ) ;
  snprintf( _gDmpMsg[_gDmpMsgIx*2+1], DUMP_ITEM_SIZE, frmt , value ) ;
  
  if( _gDmpMsgIx < DUMP_ITEM_CNT ) _gDmpMsgIx ++ ;  

  _gDmpMsg[_gDmpMsgIx*2][0] = '\0' ;
}

/******************************************************************************/
/* set dump items for key of type pointer            */
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

/******************************************************************************/
/* set dump items for key of type mqbyte      */
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
/* dump mq object description                            */
/*                                                                        */
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
//if( od->Version < MQOD_VERSION_2 ) goto _door ;
   
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
//if( od->Version < MQOD_VERSION_3 ) goto _door ;

  setDumpItemByte(  F_MQBYTE40           ,
                   "Alternate security identifier" ,
                    od->AlternateSecurityId      ) ;

   setDumpItemStr(  F_MQCHAR48           ,
                   "Resolved queue name" ,
                    od->ResolvedQName  ) ;

   setDumpItemStr(  F_MQCHAR48                   ,
                   "Resolved queue manager name" ,
                    od->ResolvedQMgrName       ) ;

#if(0)
  // -------------------------------------------------------
  // version 4 or higher
  // -------------------------------------------------------
//if( od->Version < MQOD_VERSION_4 ) goto _door ;

   MQCHARV   ObjectString;         /* Object long name */
   MQCHARV   SelectionString;      /* Message Selector */
   MQCHARV   ResObjectString;      /* Resolved long object name*/
   MQLONG    ResolvedType;         /* Alias queue resolved object type */ 
#endif

  _door :

  dumper() ;
}

