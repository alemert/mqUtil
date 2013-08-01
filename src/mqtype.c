/******************************************************************************/
/*   C O N V E R T   M Q    D E F I N E S   ( T Y P E )   T O   S T R I N G   */
/*                                                                            */
/*  functions:                                                                */
/*   - mqObjType2str                                                          */
/*   - mqmdVer2str                                                            */
/*   - mqodVer2str                                                            */
/*   - mqpmoVer2str                        */
/*   - mqReportOption2str                                                     */
/*   - mqMsgTypeId2Str                                                        */
/*   - mqFeedback2str                                                         */
/*   - mqEncondig2str                                              */
/*   - mqCCSID2str                                          */
/*   - mqPriority2str                                      */ 
/*   - mqPersistence2str                            */
/*   - mqPutApplType2str                                  */
/*   - mqMsgFlag2str                                  */
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
/* mq object description to string                                            */
/******************************************************************************/
const char* mqodVer2str( int id )
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
/* mq message description to string                                           */
/******************************************************************************/
const char* mqmdVer2str( int id )
{
  switch( id )
  {
    convert( MQMD_VERSION_1 ) ;
    convert( MQMD_VERSION_2 ) ;
  }
  return "UNKNOWN MQMD VERSION" ;
}

/******************************************************************************/
/* mq message put message options to string                                   */
/******************************************************************************/
const char* mqpmoVer2str( int id )
{
  switch( id )
  {
    convert( MQPMO_VERSION_1 ) ;
    convert( MQPMO_VERSION_2 ) ;
    convert( MQPMO_VERSION_3 ) ;
  }
  return "UNKNOWN MQPMO VERSION" ;
}

/******************************************************************************/
/* mq object type to string                                                   */
/******************************************************************************/
const char* mqObjType2str( int id )
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

/******************************************************************************/
/* mq report options to string                                                */
/******************************************************************************/
const char* mqReportOption2str( int id )
{
  switch( id )
  {
    convert( MQRO_NONE                      ) ;
    convert( MQRO_EXCEPTION                 ) ;
    convert( MQRO_EXCEPTION_WITH_DATA       ) ;
    convert( MQRO_EXCEPTION_WITH_FULL_DATA  ) ;
    convert( MQRO_EXPIRATION                ) ;
    convert( MQRO_EXPIRATION_WITH_DATA      ) ;
    convert( MQRO_EXPIRATION_WITH_FULL_DATA ) ;
    convert( MQRO_COA                       ) ;
    convert( MQRO_COA_WITH_DATA             ) ;
    convert( MQRO_COA_WITH_FULL_DATA        ) ;
    convert( MQRO_COD                       ) ;
    convert( MQRO_COD_WITH_DATA             ) ;
    convert( MQRO_COD_WITH_FULL_DATA        ) ;
    convert( MQRO_PAN                       ) ;
    convert( MQRO_NAN                       ) ;
    convert( MQRO_ACTIVITY                  ) ;
  //convert( MQRO_NEW_MSG_ID                ) ;
    convert( MQRO_PASS_MSG_ID               ) ;
  //convert( MQRO_COPY_MSG_ID_TO_CORREL_ID  ) ;
    convert( MQRO_PASS_CORREL_ID            ) ;
  //convert( MQRO_DEAD_LETTER_Q             ) ;
    convert( MQRO_DISCARD_MSG               ) ;
    convert( MQRO_PASS_DISCARD_AND_EXPIRY   ) ;
    convert( MQRO_REJECT_UNSUP_MASK         ) ;
    convert( MQRO_ACCEPT_UNSUP_MASK         ) ;
    convert( MQRO_ACCEPT_UNSUP_IF_XMIT_MASK ) ;
  }

  return "UNKNOWN MQ REPORT OPTION" ;
}

/******************************************************************************/
/* mq message type to string                                                  */
/******************************************************************************/
const char* mqMsgType2str( int id )
{
  switch( id )
  {
  //convert( MQMT_SYSTEM_FIRST        ) ;
    convert( MQMT_REQUEST             ) ;
    convert( MQMT_REPLY               ) ;
    convert( MQMT_DATAGRAM            ) ;
    convert( MQMT_REPORT              ) ;
    convert( MQMT_MQE_FIELDS_FROM_MQE ) ;
    convert( MQMT_MQE_FIELDS          ) ;
    convert( MQMT_SYSTEM_LAST         ) ;
    convert( MQMT_APPL_FIRST          ) ;
    convert( MQMT_APPL_LAST           ) ;
  }

  return "UNKNOWN MQ MESSAGE TYPE" ;
}

/******************************************************************************/
/* mq feedback to string                                                      */
/******************************************************************************/
const char* mqFeedback2str( int id )
{
  switch( id )
  {
    convert( MQFB_NONE                   ) ;
    convert( MQFB_SYSTEM_FIRST           ) ;
    convert( MQFB_QUIT                   ) ;
    convert( MQFB_EXPIRATION             ) ;
    convert( MQFB_COA                    ) ;
    convert( MQFB_COD                    ) ;
    convert( MQFB_CHANNEL_COMPLETED      ) ;
    convert( MQFB_CHANNEL_FAIL_RETRY     ) ;
    convert( MQFB_CHANNEL_FAIL           ) ;
    convert( MQFB_APPL_CANNOT_BE_STARTED ) ;
    convert( MQFB_TM_ERROR               ) ;
    convert( MQFB_APPL_TYPE_ERROR        ) ;
    convert( MQFB_STOPPED_BY_MSG_EXIT    ) ;
    convert( MQFB_ACTIVITY               ) ;
    convert( MQFB_XMIT_Q_MSG_ERROR       ) ;
    convert( MQFB_PAN                    ) ;
    convert( MQFB_NAN                    ) ;
    convert( MQFB_STOPPED_BY_CHAD_EXIT   ) ;
    convert( MQFB_STOPPED_BY_PUBSUB_EXIT ) ;
    convert( MQFB_NOT_A_REPOSITORY_MSG   ) ;
    convert( MQFB_BIND_OPEN_CLUSRCVR_DEL ) ;
    convert( MQFB_MAX_ACTIVITIES         ) ;
    convert( MQFB_NOT_FORWARDED          ) ;
    convert( MQFB_NOT_DELIVERED          ) ;
    convert( MQFB_UNSUPPORTED_FORWARDING ) ;
    convert( MQFB_UNSUPPORTED_DELIVERY   ) ;
    convert( MQFB_DATA_LENGTH_ZERO       ) ;
    convert( MQFB_DATA_LENGTH_NEGATIVE   ) ;
    convert( MQFB_DATA_LENGTH_TOO_BIG    ) ;
    convert( MQFB_BUFFER_OVERFLOW        ) ;
    convert( MQFB_LENGTH_OFF_BY_ONE      ) ;
    convert( MQFB_IIH_ERROR              ) ;
    convert( MQFB_NOT_AUTHORIZED_FOR_IMS ) ;
    convert( MQFB_IMS_ERROR              ) ;
    convert( MQFB_IMS_FIRST              ) ;
    convert( MQFB_IMS_LAST               ) ;
    convert( MQFB_CICS_INTERNAL_ERROR    ) ;
    convert( MQFB_CICS_NOT_AUTHORIZED    ) ;
    convert( MQFB_CICS_BRIDGE_FAILURE    ) ;
    convert( MQFB_CICS_CORREL_ID_ERROR   ) ;
    convert( MQFB_CICS_CCSID_ERROR       ) ;
  }

  return "UNKNOWN MQ FEEDBACK" ;
}

/******************************************************************************/
/* mq encondig to string                                                      */
/******************************************************************************/
const char* mqEncondig2str( int id )
{
  switch( id )
  {
    convert( MQENC_NATIVE              ) ;
    convert( MQENC_INTEGER_MASK        ) ;
    convert( MQENC_DECIMAL_MASK        ) ;
    convert( MQENC_FLOAT_MASK          ) ;
    convert( MQENC_RESERVED_MASK       ) ;
    convert( MQENC_INTEGER_UNDEFINED   ) ;
    convert( MQENC_INTEGER_NORMAL      ) ;
    convert( MQENC_INTEGER_REVERSED    ) ;
  //convert( MQENC_DECIMAL_UNDEFINED   ) ;
    convert( MQENC_DECIMAL_NORMAL      ) ;
    convert( MQENC_DECIMAL_REVERSED    ) ;
  //convert( MQENC_FLOAT_UNDEFINED     ) ;
    convert( MQENC_FLOAT_IEEE_NORMAL   ) ;
    convert( MQENC_FLOAT_IEEE_REVERSED ) ;
    convert( MQENC_FLOAT_S390          ) ;
    convert( MQENC_FLOAT_TNS           ) ;
  }

  return "UNKNOWN MQ ENCONDING" ;
}

/******************************************************************************/
/* mq CCSID to string                                                         */
/******************************************************************************/
const char* mqCCSID2str( int id )
{
  switch( id )
  {
  //convert( MQCCSI_UNDEFINED  );
  //convert( MQCCSI_DEFAULT    );
    convert( MQCCSI_Q_MGR      );
    convert( MQCCSI_INHERIT    );
    convert( MQCCSI_EMBEDDED   );
  }

  return "UNKNOWN MQ CCSID" ;
}

/******************************************************************************/
/* mq priority to string                                                      */
/******************************************************************************/
const char* mqPriority2str( int id )
{
  switch( id )
  {
    convert( MQPRI_PRIORITY_AS_Q_DEF     ) ;
    convert( MQPRI_PRIORITY_AS_PARENT    ) ;
    convert( MQPRI_PRIORITY_AS_PUBLISHED ) ;
  //convert( MQPRI_PRIORITY_AS_TOPIC_DEF ) ;
    case 0 : return "0" ;
    case 1 : return "1" ;
    case 2 : return "2" ;
    case 3 : return "3" ;
    case 4 : return "4" ;
    case 5 : return "5" ;
    case 6 : return "6" ;
    case 7 : return "7" ;
    case 8 : return "8" ;
    case 9 : return "9" ;
  }

  return "UNKNOWN MQ PRIORITY" ;
}

/******************************************************************************/
/* mq persitance to string                                                    */
/******************************************************************************/
const char* mqPersistence2str( int id )
{
  switch( id )
  {
    convert( MQPER_PERSISTENCE_AS_PARENT    ) ;
    convert( MQPER_NOT_PERSISTENT           ) ;
    convert( MQPER_PERSISTENT               ) ;
    convert( MQPER_PERSISTENCE_AS_Q_DEF     ) ;
  //convert( MQPER_PERSISTENCE_AS_TOPIC_DEF ) ;
  }

  return "UNKNOWN MQ PERSISTENCE" ;
}

/******************************************************************************/
/* mq put application type to string                                          */
/******************************************************************************/
const char* mqPutApplType2str( int id )
{
  switch( id )
  {
    convert( MQAT_UNKNOWN           );
    convert( MQAT_NO_CONTEXT        );
    convert( MQAT_CICS              );
  //convert( MQAT_MVS               );
  //convert( MQAT_OS390             );
    convert( MQAT_ZOS               );
    convert( MQAT_IMS               );
    convert( MQAT_OS2               );
    convert( MQAT_DOS               );
   //onvert( MQAT_AIX               );
    convert( MQAT_UNIX              );
    convert( MQAT_QMGR              );
    convert( MQAT_OS400             );
    convert( MQAT_WINDOWS           );
    convert( MQAT_CICS_VSE          );
    convert( MQAT_WINDOWS_NT        );
    convert( MQAT_VMS               );
    convert( MQAT_GUARDIAN          );
  //convert( MQAT_NSK               );
    convert( MQAT_VOS               );
    convert( MQAT_OPEN_TP1          );
    convert( MQAT_VM                );
    convert( MQAT_IMS_BRIDGE        );
    convert( MQAT_XCF               );
    convert( MQAT_CICS_BRIDGE       );
    convert( MQAT_NOTES_AGENT       );
    convert( MQAT_TPF               );
    convert( MQAT_USER              );
    convert( MQAT_BROKER            );
  //convert( MQAT_QMGR_PUBLISH      );
    convert( MQAT_JAVA              );
    convert( MQAT_DQM               );
    convert( MQAT_CHANNEL_INITIATOR );
    convert( MQAT_WLM               );
    convert( MQAT_BATCH             );
    convert( MQAT_RRS_BATCH         );
    convert( MQAT_SIB               );
    convert( MQAT_SYSTEM_EXTENSION  );
  //convert( MQAT_DEFAULT           );
    convert( MQAT_USER_FIRST        );
    convert( MQAT_USER_LAST         );
  }

  return "UNKNOWN MQ PUT APPL TYPE" ;
}

/******************************************************************************/
/* mq message flag to string                                    */
/******************************************************************************/
const char* mqMsgFlag2str( int id )
{
  switch( id )
  {
  //convert( MQMF_SEGMENTATION_INHIBITED    );
    convert( MQMF_SEGMENTATION_ALLOWED      );
    convert( MQMF_MSG_IN_GROUP              );
    convert( MQMF_LAST_MSG_IN_GROUP         );
    convert( MQMF_SEGMENT                   );
    convert( MQMF_LAST_SEGMENT              );
    convert( MQMF_NONE                      );
    convert( MQMF_REJECT_UNSUP_MASK         );
    convert( MQMF_ACCEPT_UNSUP_MASK         );
    convert( MQMF_ACCEPT_UNSUP_IF_XMIT_MASK );
  }

  return "UNKNOWN MQ MESSAGE FLAG" ;
}

/******************************************************************************/
/* mq put msg options to string              */
/******************************************************************************/
const char* mqPutMsgOpt2str( int id )
{
  switch( id )
  {
    convert( MQPMO_SYNCPOINT                );
    convert( MQPMO_NO_SYNCPOINT             );
    convert( MQPMO_DEFAULT_CONTEXT          );
    convert( MQPMO_NEW_MSG_ID               );
    convert( MQPMO_NEW_CORREL_ID            );
    convert( MQPMO_PASS_IDENTITY_CONTEXT    );
    convert( MQPMO_PASS_ALL_CONTEXT         );
    convert( MQPMO_SET_IDENTITY_CONTEXT     );
    convert( MQPMO_SET_ALL_CONTEXT          );
    convert( MQPMO_ALTERNATE_USER_AUTHORITY );
    convert( MQPMO_FAIL_IF_QUIESCING        );
    convert( MQPMO_NO_CONTEXT               );
    convert( MQPMO_LOGICAL_ORDER            );
    convert( MQPMO_ASYNC_RESPONSE           );
    convert( MQPMO_SYNC_RESPONSE            );
    convert( MQPMO_RESOLVE_LOCAL_Q          );
    convert( MQPMO_WARN_IF_NO_SUBS_MATCHED  );
    convert( MQPMO_RETAIN                   );
    convert( MQPMO_MD_FOR_OUTPUT_ONLY       );
    convert( MQPMO_SCOPE_QMGR               );
    convert( MQPMO_SUPPRESS_REPLYTO         );
    convert( MQPMO_NOT_OWN_SUBS             );
  //convert( MQPMO_RESPONSE_AS_Q_DEF        );
  //convert( MQPMO_RESPONSE_AS_TOPIC_DEF    );
    convert( MQPMO_NONE                     );
  //convert( MQPMO_PUB_OPTIONS_MASK         );
  }

  return "UNKNOWN MQ MESSAGE FLAG" ;
}
