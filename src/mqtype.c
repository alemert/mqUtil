/******************************************************************************/
/*   C O N V E R T   M Q    D E F I N E S   ( T Y P E )   T O   S T R I N G   */
/*                                                                            */
/*  functions:                                                                */
/*   - unknownReason                                    */
/*   - mqObjType2str                                                          */
/*   - mqmdVer2str                                                            */
/*   - mqodVer2str                                                            */
/*   - mqpmoVer2str                                                           */
/*   - mqgmoVer2str                                                           */
/*   - mqcfhVer2str                                                           */
/*   - mqReportOption2str                                                     */
/*   - mqMsgTypeId2Str                                                        */
/*   - mqFeedback2str                                                         */
/*   - mqEncondig2str                                                         */
/*   - mqCCSID2str                                                            */
/*   - mqPriority2str                                                         */
/*   - mqPersistence2str                                                      */
/*   - mqPutApplType2str                                                      */
/*   - mqMsgFlag2str                                                          */
/*   - mqItemType2str                                                         */
/*   - mqSelector2str                                                         */
/*   - itemValue2str                                                */
/*   - mqbagType2str                                            */
/*   - mqcmd2str                                            */
/*   - mqcfc2str                                    */
/*   - mqcompCode2str                                */
/*   - mqrcQualifier2str                        */
/*   - str2mqSelector                    */
/*                                                          */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
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
#include <mqtype.h>
#include <mqreason.h>

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
#define rconv( str, def ) if( strcmp( str, #def ) == 0 ) return def ;

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* unknown reason                  */
/******************************************************************************/
const char* unknownReason( const char* txt, int id )
{
  #define UR_MAX_MEM_IX  8
  #define UR_MEM_LNG    32 

  static int memIx = 0;
  static char buff[UR_MAX_MEM_IX][UR_MEM_LNG+1];

  memIx++;
  if( memIx >= UR_MAX_MEM_IX )
  {
    memIx = 0 ;
  }
  snprintf( buff[memIx], UR_MEM_LNG, "%d %s", id, txt );
  
  return buff[memIx] ;
  
}

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
/* mq message get message options to string                                   */
/******************************************************************************/
const char* mqgmoVer2str( int id )
{
  switch( id )
  {
    convert( MQGMO_VERSION_1 ) ;
    convert( MQGMO_VERSION_2 ) ;
    convert( MQGMO_VERSION_3 ) ;
    convert( MQGMO_VERSION_4 ) ;
  }
  return "UNKNOWN MQGMO VERSION" ;
}

/******************************************************************************/
/* MQCFH version 2 string                  */
/******************************************************************************/
const char* mqcfhVer2str( int id )
{
  switch( id )
  {
    convert( MQCFH_VERSION_1 ) ;
    convert( MQCFH_VERSION_2 ) ;
    convert( MQCFH_VERSION_3 ) ;
  }
  return "UNKNOWN MQCFH VERSION" ;
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
/* mq message flag to string                                                  */
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
/* mq put msg options to string                                               */
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

/******************************************************************************/
/* mq convert item type to string                                             */
/******************************************************************************/
const char* mqItemType2str( MQLONG id ) 
{
  switch( id )
  {
    convert( MQITEM_INTEGER             );
    convert( MQITEM_STRING              );
    convert( MQITEM_BAG                 );
    convert( MQITEM_BYTE_STRING         );
    convert( MQITEM_INTEGER_FILTER      );
    convert( MQITEM_STRING_FILTER       );
    convert( MQITEM_INTEGER64           );
    convert( MQITEM_BYTE_STRING_FILTER  );
  }

  return "UNKNOWN MQ ITEM TYPE" ;
}

/******************************************************************************/
/* mq selector to string                                                      */
/******************************************************************************/
const char* mqSelector2str( MQLONG id )
{
  switch( id )
  {
//  convert( MQIASY_FIRST                     );
    convert( MQIASY_CODED_CHAR_SET_ID         );
    convert( MQIASY_TYPE                      );
    convert( MQIASY_COMMAND                   );
    convert( MQIASY_MSG_SEQ_NUMBER            );
    convert( MQIASY_CONTROL                   );
    convert( MQIASY_COMP_CODE                 );
    convert( MQIASY_REASON                    );
    convert( MQIASY_BAG_OPTIONS               );
    convert( MQIASY_VERSION                   );
//  convert( MQIASY_LAST_USED                 );
    convert( MQIASY_LAST                      );
    convert( MQCA_ADMIN_TOPIC_NAME            );
    convert( MQCA_ALTERATION_DATE             );
    convert( MQCA_ALTERATION_TIME             );
    convert( MQCA_APPL_ID                     );
    convert( MQCA_AUTH_INFO_CONN_NAME         );
    convert( MQCA_AUTH_INFO_DESC              );
    convert( MQCA_AUTH_INFO_NAME              );
//  convert( MQCA_AUTH_INFO_OCSP_URL          );
    convert( MQCA_AUTO_REORG_CATALOG          );
    convert( MQCA_AUTO_REORG_START_TIME       );
    convert( MQCA_BACKOUT_REQ_Q_NAME          );
    convert( MQCA_BASE_OBJECT_NAME            );
//  convert( MQCA_BASE_Q_NAME                 );
    convert( MQCA_BATCH_INTERFACE_ID          );
    convert( MQCA_CF_STRUC_DESC               );
    convert( MQCA_CF_STRUC_NAME               );
    convert( MQCA_CHANNEL_AUTO_DEF_EXIT       );
    convert( MQCA_CHILD                       );
    convert( MQCA_CHINIT_SERVICE_PARM         );
    convert( MQCA_CICS_FILE_NAME              );
    convert( MQCA_CLUSTER_DATE                );
    convert( MQCA_CLUSTER_NAME                );
    convert( MQCA_CLUSTER_NAMELIST            );
    convert( MQCA_CLUSTER_Q_MGR_NAME          );
    convert( MQCA_CLUSTER_TIME                );
    convert( MQCA_CLUSTER_WORKLOAD_DATA       );
    convert( MQCA_CLUSTER_WORKLOAD_EXIT       );
    convert( MQCA_COMMAND_INPUT_Q_NAME        );
    convert( MQCA_COMMAND_REPLY_Q_NAME        );
    convert( MQCA_CREATION_DATE               );
    convert( MQCA_CREATION_TIME               );
    convert( MQCA_DEAD_LETTER_Q_NAME          );
    convert( MQCA_DEF_XMIT_Q_NAME             );
    convert( MQCA_DNS_GROUP                   );
    convert( MQCA_ENV_DATA                    );
//  convert( MQCA_FIRST                       );
    convert( MQCA_IGQ_USER_ID                 );
    convert( MQCA_INITIATION_Q_NAME           );
//  convert( MQCA_LAST                        );
    convert( MQCA_LAST_USED                   );
    convert( MQCA_LDAP_PASSWORD               );
    convert( MQCA_LDAP_USER_NAME              );
    convert( MQCA_LU_GROUP_NAME               );
    convert( MQCA_LU_NAME                     );
    convert( MQCA_LU62_ARM_SUFFIX             );
    convert( MQCA_MODEL_DURABLE_Q             );
    convert( MQCA_MODEL_NON_DURABLE_Q         );
    convert( MQCA_MONITOR_Q_NAME              );
    convert( MQCA_NAMELIST_DESC               );
    convert( MQCA_NAMELIST_NAME               );
    convert( MQCA_NAMES                       );
    convert( MQCA_PARENT                      );
    convert( MQCA_PASS_TICKET_APPL            );
    convert( MQCA_PROCESS_DESC                );
    convert( MQCA_PROCESS_NAME                );
    convert( MQCA_Q_DESC                      );
    convert( MQCA_Q_MGR_DESC                  );
    convert( MQCA_Q_MGR_IDENTIFIER            );
    convert( MQCA_Q_MGR_NAME                  );
    convert( MQCA_Q_NAME                      );
    convert( MQCA_QSG_NAME                    );
    convert( MQCA_REMOTE_Q_MGR_NAME           );
    convert( MQCA_REMOTE_Q_NAME               );
    convert( MQCA_REPOSITORY_NAME             );
    convert( MQCA_REPOSITORY_NAMELIST         );
    convert( MQCA_RESUME_DATE                 );
    convert( MQCA_RESUME_TIME                 );
    convert( MQCA_SERVICE_DESC                );
    convert( MQCA_SERVICE_NAME                );
    convert( MQCA_SERVICE_START_ARGS          );
    convert( MQCA_SERVICE_START_COMMAND       );
    convert( MQCA_SERVICE_STOP_ARGS           );
    convert( MQCA_SERVICE_STOP_COMMAND        );
    convert( MQCA_STDERR_DESTINATION          );
    convert( MQCA_STDOUT_DESTINATION          );
    convert( MQCA_SSL_CRL_NAMELIST            );
    convert( MQCA_SSL_CRYPTO_HARDWARE         );
    convert( MQCA_SSL_KEY_LIBRARY             );
    convert( MQCA_SSL_KEY_MEMBER              );
    convert( MQCA_SSL_KEY_REPOSITORY          );
    convert( MQCA_STORAGE_CLASS               );
    convert( MQCA_STORAGE_CLASS_DESC          );
    convert( MQCA_SYSTEM_LOG_Q_NAME           );
    convert( MQCA_TCP_NAME                    );
    convert( MQCA_TOPIC_DESC                  );
    convert( MQCA_TOPIC_NAME                  );
    convert( MQCA_TOPIC_STRING                );
    convert( MQCA_TOPIC_STRING_FILTER         );
    convert( MQCA_TPIPE_NAME                  );
    convert( MQCA_TRIGGER_CHANNEL_NAME        );
    convert( MQCA_TRIGGER_DATA                );
    convert( MQCA_TRIGGER_PROGRAM_NAME        );
    convert( MQCA_TRIGGER_TERM_ID             );
    convert( MQCA_TRIGGER_TRANS_ID            );
    convert( MQCA_USER_DATA                   );
    convert( MQCA_USER_LIST                   );
    convert( MQCA_XCF_GROUP_NAME              );
    convert( MQCA_XCF_MEMBER_NAME             );
    convert( MQCA_XMIT_Q_NAME                 );
    convert( MQIA_ACCOUNTING_CONN_OVERRIDE    );
    convert( MQIA_ACCOUNTING_INTERVAL         );
    convert( MQIA_ACCOUNTING_MQI              );
    convert( MQIA_ACCOUNTING_Q                );
    convert( MQIA_ACTIVE_CHANNELS             );
    convert( MQIA_ACTIVITY_RECORDING          );
    convert( MQIA_ADOPTNEWMCA_CHECK           );
    convert( MQIA_ADOPTNEWMCA_TYPE            );
    convert( MQIA_ADOPTNEWMCA_INTERVAL        );
    convert( MQIA_APPL_TYPE                   );
    convert( MQIA_ARCHIVE                     );
    convert( MQIA_AUTH_INFO_TYPE              );
    convert( MQIA_AUTHORITY_EVENT             );
    convert( MQIA_AUTO_REORG_INTERVAL         );
    convert( MQIA_AUTO_REORGANIZATION         );
    convert( MQIA_BACKOUT_THRESHOLD           );
    convert( MQIA_BASE_TYPE                   );
    convert( MQIA_BATCH_INTERFACE_AUTO        );
    convert( MQIA_BRIDGE_EVENT                );
    convert( MQIA_CF_LEVEL                    );
    convert( MQIA_CF_RECOVER                  );
    convert( MQIA_CHANNEL_AUTO_DEF            );
    convert( MQIA_CHANNEL_AUTO_DEF_EVENT      );
    convert( MQIA_CHANNEL_EVENT               );
    convert( MQIA_CHINIT_ADAPTERS             );
    convert( MQIA_CHINIT_CONTROL              );
    convert( MQIA_CHINIT_DISPATCHERS          );
    convert( MQIA_CHINIT_TRACE_AUTO_START     );
    convert( MQIA_CHINIT_TRACE_TABLE_SIZE     );
    convert( MQIA_CLUSTER_Q_TYPE              );
    convert( MQIA_CLUSTER_WORKLOAD_LENGTH     );
    convert( MQIA_CLWL_MRU_CHANNELS           );
    convert( MQIA_CLWL_Q_RANK                 );
    convert( MQIA_CLWL_Q_PRIORITY             );
    convert( MQIA_CLWL_USEQ                   );
    convert( MQIA_CMD_SERVER_AUTO             );
    convert( MQIA_CMD_SERVER_CONTROL          );
    convert( MQIA_CMD_SERVER_CONVERT_MSG      );
    convert( MQIA_CMD_SERVER_DLQ_MSG          );
    convert( MQIA_CODED_CHAR_SET_ID           );
    convert( MQIA_COMMAND_EVENT               );
    convert( MQIA_COMMAND_LEVEL               );
    convert( MQIA_CONFIGURATION_EVENT         );
    convert( MQIA_CPI_LEVEL                   );
    convert( MQIA_CURRENT_Q_DEPTH             );
    convert( MQIA_DEF_BIND                    );
    convert( MQIA_DEF_INPUT_OPEN_OPTION       );
    convert( MQIA_DEF_PERSISTENCE             );
    convert( MQIA_DEF_PRIORITY                );
    convert( MQIA_DEF_PUT_RESPONSE_TYPE       );
    convert( MQIA_DEF_READ_AHEAD              );
    convert( MQIA_DEFINITION_TYPE             );
    convert( MQIA_DIST_LISTS                  );
    convert( MQIA_DNS_WLM                     );
    convert( MQIA_DURABLE_SUB                 );
    convert( MQIA_EXPIRY_INTERVAL             );
//  convert( MQIA_FIRST                       );
    convert( MQIA_GROUP_UR                    );
    convert( MQIA_HARDEN_GET_BACKOUT          );
    convert( MQIA_HIGH_Q_DEPTH                );
    convert( MQIA_IGQ_PUT_AUTHORITY           );
    convert( MQIA_INDEX_TYPE                  );
    convert( MQIA_INHIBIT_EVENT               );
    convert( MQIA_INHIBIT_GET                 );
    convert( MQIA_INHIBIT_PUB                 );
    convert( MQIA_INHIBIT_PUT                 );
    convert( MQIA_INHIBIT_SUB                 );
    convert( MQIA_INTRA_GROUP_QUEUING         );
    convert( MQIA_IP_ADDRESS_VERSION          );
//  convert( MQIA_LAST                        );
//  convert( MQIA_LAST_USED                   );
    convert( MQIA_LISTENER_PORT_NUMBER        );
    convert( MQIA_LISTENER_TIMER              );
    convert( MQIA_LOGGER_EVENT                );
    convert( MQIA_LU62_CHANNELS               );
    convert( MQIA_LOCAL_EVENT                 );
    convert( MQIA_MSG_MARK_BROWSE_INTERVAL    );
    convert( MQIA_MASTER_ADMIN                );
    convert( MQIA_MAX_CHANNELS                );
    convert( MQIA_MAX_CLIENTS                 );
    convert( MQIA_MAX_GLOBAL_LOCKS            );
    convert( MQIA_MAX_HANDLES                 );
    convert( MQIA_MAX_LOCAL_LOCKS             );
    convert( MQIA_MAX_MSG_LENGTH              );
    convert( MQIA_MAX_OPEN_Q                  );
    convert( MQIA_MAX_PRIORITY                );
    convert( MQIA_MAX_PROPERTIES_LENGTH       );
    convert( MQIA_MAX_Q_DEPTH                 );
    convert( MQIA_MAX_Q_TRIGGERS              );
    convert( MQIA_MAX_RECOVERY_TASKS          );
    convert( MQIA_MAX_UNCOMMITTED_MSGS        );
    convert( MQIA_MONITOR_INTERVAL            );
    convert( MQIA_MONITORING_AUTO_CLUSSDR     );
    convert( MQIA_MONITORING_CHANNEL          );
    convert( MQIA_MONITORING_Q                );
    convert( MQIA_MSG_DELIVERY_SEQUENCE       );
    convert( MQIA_MSG_DEQ_COUNT               );
    convert( MQIA_MSG_ENQ_COUNT               );
    convert( MQIA_NAME_COUNT                  );
    convert( MQIA_NAMELIST_TYPE               );
    convert( MQIA_NPM_CLASS                   );
    convert( MQIA_NPM_DELIVERY                );
    convert( MQIA_OPEN_INPUT_COUNT            );
    convert( MQIA_OPEN_OUTPUT_COUNT           );
    convert( MQIA_OUTBOUND_PORT_MAX           );
    convert( MQIA_OUTBOUND_PORT_MIN           );
    convert( MQIA_PAGESET_ID                  );
    convert( MQIA_PERFORMANCE_EVENT           );
    convert( MQIA_PLATFORM                    );
    convert( MQIA_PM_DELIVERY                 );
    convert( MQIA_PROPERTY_CONTROL            );
    convert( MQIA_PROXY_SUB                   );
    convert( MQIA_PUB_COUNT                   );
    convert( MQIA_PUB_SCOPE                   );
    convert( MQIA_PUBSUB_MAXMSG_RETRY_COUNT   );
    convert( MQIA_PUBSUB_MODE                 );
    convert( MQIA_PUBSUB_NP_MSG               );
    convert( MQIA_PUBSUB_NP_RESP              );
    convert( MQIA_PUBSUB_SYNC_PT              );
    convert( MQIA_Q_DEPTH_HIGH_EVENT          );
    convert( MQIA_Q_DEPTH_HIGH_LIMIT          );
    convert( MQIA_Q_DEPTH_LOW_EVENT           );
    convert( MQIA_Q_DEPTH_LOW_LIMIT           );
    convert( MQIA_Q_DEPTH_MAX_EVENT           );
    convert( MQIA_Q_SERVICE_INTERVAL          );
    convert( MQIA_Q_SERVICE_INTERVAL_EVENT    );
    convert( MQIA_Q_TYPE                      );
    convert( MQIA_Q_USERS                     );
    convert( MQIA_QMOPT_CONS_COMMS_MSGS       );
    convert( MQIA_QMOPT_CONS_CRITICAL_MSGS    );
    convert( MQIA_QMOPT_CONS_ERROR_MSGS       );
    convert( MQIA_QMOPT_CONS_INFO_MSGS        );
    convert( MQIA_QMOPT_CONS_REORG_MSGS       );
    convert( MQIA_QMOPT_CONS_SYSTEM_MSGS      );
    convert( MQIA_QMOPT_CONS_WARNING_MSGS     );
    convert( MQIA_QMOPT_CSMT_ON_ERROR         );
    convert( MQIA_QMOPT_INTERNAL_DUMP         );
    convert( MQIA_QMOPT_LOG_COMMS_MSGS        );
    convert( MQIA_QMOPT_LOG_CRITICAL_MSGS     );
    convert( MQIA_QMOPT_LOG_ERROR_MSGS        );
    convert( MQIA_QMOPT_LOG_INFO_MSGS         );
    convert( MQIA_QMOPT_LOG_REORG_MSGS        );
    convert( MQIA_QMOPT_LOG_SYSTEM_MSGS       );
    convert( MQIA_QMOPT_LOG_WARNING_MSGS      );
    convert( MQIA_QMOPT_TRACE_COMMS           );
    convert( MQIA_QMOPT_TRACE_CONVERSION      );
    convert( MQIA_QMOPT_TRACE_REORG           );
    convert( MQIA_QMOPT_TRACE_MQI_CALLS       );
    convert( MQIA_QMOPT_TRACE_SYSTEM          );
    convert( MQIA_QSG_DISP                    );
    convert( MQIA_READ_AHEAD                  );
    convert( MQIA_RECEIVE_TIMEOUT             );
    convert( MQIA_RECEIVE_TIMEOUT_MIN         );
    convert( MQIA_RECEIVE_TIMEOUT_TYPE        );
    convert( MQIA_REMOTE_EVENT                );
    convert( MQIA_RETENTION_INTERVAL          );
    convert( MQIA_SCOPE                       );
    convert( MQIA_SECURITY_CASE               );
    convert( MQIA_SERVICE_CONTROL             );
    convert( MQIA_SERVICE_TYPE                );
    convert( MQIA_SHAREABILITY                );
    convert( MQIA_SHARED_Q_Q_MGR_NAME         );
    convert( MQIA_SSL_EVENT                   );
    convert( MQIA_SSL_FIPS_REQUIRED           );
    convert( MQIA_SSL_RESET_COUNT             );
    convert( MQIA_SSL_TASKS                   );
    convert( MQIA_START_STOP_EVENT            );
    convert( MQIA_STATISTICS_CHANNEL          );
    convert( MQIA_STATISTICS_AUTO_CLUSSDR     );
    convert( MQIA_STATISTICS_INTERVAL         );
    convert( MQIA_STATISTICS_MQI              );
    convert( MQIA_STATISTICS_Q                );
    convert( MQIA_SUB_COUNT                   );
    convert( MQIA_SUB_SCOPE                   );
    convert( MQIA_SYNCPOINT                   );
    convert( MQIA_TCP_CHANNELS                );
    convert( MQIA_TCP_KEEP_ALIVE              );
    convert( MQIA_TCP_STACK_TYPE              );
    convert( MQIA_TIME_SINCE_RESET            );
    convert( MQIA_TOPIC_DEF_PERSISTENCE       );
    convert( MQIA_TOPIC_TYPE                  );
    convert( MQIA_TRACE_ROUTE_RECORDING       );
    convert( MQIA_TREE_LIFE_TIME              );
    convert( MQIA_TRIGGER_CONTROL             );
    convert( MQIA_TRIGGER_DEPTH               );
    convert( MQIA_TRIGGER_INTERVAL            );
    convert( MQIA_TRIGGER_MSG_PRIORITY        );
    convert( MQIA_TRIGGER_TYPE                );
    convert( MQIA_TRIGGER_RESTART             );
    convert( MQIA_UR_DISP                     );
    convert( MQIA_USAGE                       );
    convert( MQIA_USER_LIST                   );
    convert( MQIA_WILDCARD_OPERATION          );
//  convert( MQCACF_FIRST                     );
    convert( MQCACF_FROM_Q_NAME               );
    convert( MQCACF_TO_Q_NAME                 );
    convert( MQCACF_FROM_PROCESS_NAME         );
    convert( MQCACF_TO_PROCESS_NAME           );
    convert( MQCACF_FROM_NAMELIST_NAME        );
    convert( MQCACF_TO_NAMELIST_NAME          );
    convert( MQCACF_FROM_CHANNEL_NAME         );
    convert( MQCACF_TO_CHANNEL_NAME           );
    convert( MQCACF_FROM_AUTH_INFO_NAME       );
    convert( MQCACF_TO_AUTH_INFO_NAME         );
    convert( MQCACF_Q_NAMES                   );
    convert( MQCACF_PROCESS_NAMES             );
    convert( MQCACF_NAMELIST_NAMES            );
    convert( MQCACF_ESCAPE_TEXT               );
    convert( MQCACF_LOCAL_Q_NAMES             );
    convert( MQCACF_MODEL_Q_NAMES             );
    convert( MQCACF_ALIAS_Q_NAMES             );
    convert( MQCACF_REMOTE_Q_NAMES            );
    convert( MQCACF_SENDER_CHANNEL_NAMES      );
    convert( MQCACF_SERVER_CHANNEL_NAMES      );
    convert( MQCACF_REQUESTER_CHANNEL_NAMES   );
    convert( MQCACF_RECEIVER_CHANNEL_NAMES    );
    convert( MQCACF_OBJECT_Q_MGR_NAME         );
    convert( MQCACF_APPL_NAME                 );
    convert( MQCACF_USER_IDENTIFIER           );
    convert( MQCACF_AUX_ERROR_DATA_STR_1      );
    convert( MQCACF_AUX_ERROR_DATA_STR_2      );
    convert( MQCACF_AUX_ERROR_DATA_STR_3      );
    convert( MQCACF_BRIDGE_NAME               );
    convert( MQCACF_STREAM_NAME               );
    convert( MQCACF_TOPIC                     );
    convert( MQCACF_PARENT_Q_MGR_NAME         );
    convert( MQCACF_CORREL_ID                 );
    convert( MQCACF_PUBLISH_TIMESTAMP         );
    convert( MQCACF_STRING_DATA               );
    convert( MQCACF_SUPPORTED_STREAM_NAME     );
    convert( MQCACF_REG_TOPIC                 );
    convert( MQCACF_REG_TIME                  );
    convert( MQCACF_REG_USER_ID               );
    convert( MQCACF_CHILD_Q_MGR_NAME          );
    convert( MQCACF_REG_STREAM_NAME           );
    convert( MQCACF_REG_Q_MGR_NAME            );
    convert( MQCACF_REG_Q_NAME                );
    convert( MQCACF_REG_CORREL_ID             );
    convert( MQCACF_EVENT_USER_ID             );
    convert( MQCACF_OBJECT_NAME               );
    convert( MQCACF_EVENT_Q_MGR               );
    convert( MQCACF_AUTH_INFO_NAMES           );
    convert( MQCACF_EVENT_APPL_IDENTITY       );
    convert( MQCACF_EVENT_APPL_NAME           );
    convert( MQCACF_EVENT_APPL_ORIGIN         );
    convert( MQCACF_SUBSCRIPTION_NAME         );
    convert( MQCACF_REG_SUB_NAME              );
    convert( MQCACF_SUBSCRIPTION_IDENTITY     );
    convert( MQCACF_REG_SUB_IDENTITY          );
    convert( MQCACF_SUBSCRIPTION_USER_DATA    );
    convert( MQCACF_REG_SUB_USER_DATA         );
    convert( MQCACF_APPL_TAG                  );
    convert( MQCACF_DATA_SET_NAME             );
    convert( MQCACF_UOW_START_DATE            );
    convert( MQCACF_UOW_START_TIME            );
    convert( MQCACF_UOW_LOG_START_DATE        );
    convert( MQCACF_UOW_LOG_START_TIME        );
    convert( MQCACF_UOW_LOG_EXTENT_NAME       );
    convert( MQCACF_PRINCIPAL_ENTITY_NAMES    );
    convert( MQCACF_GROUP_ENTITY_NAMES        );
    convert( MQCACF_AUTH_PROFILE_NAME         );
    convert( MQCACF_ENTITY_NAME               );
    convert( MQCACF_SERVICE_COMPONENT         );
    convert( MQCACF_RESPONSE_Q_MGR_NAME       );
    convert( MQCACF_CURRENT_LOG_EXTENT_NAME   );
    convert( MQCACF_RESTART_LOG_EXTENT_NAME   );
    convert( MQCACF_MEDIA_LOG_EXTENT_NAME     );
    convert( MQCACF_LOG_PATH                  );
    convert( MQCACF_COMMAND_MQSC              );
    convert( MQCACF_Q_MGR_CPF                 );
    convert( MQCACF_USAGE_LOG_RBA             );
    convert( MQCACF_USAGE_LOG_LRSN            );
    convert( MQCACF_COMMAND_SCOPE             );
    convert( MQCACF_ASID                      );
    convert( MQCACF_PSB_NAME                  );
    convert( MQCACF_PST_ID                    );
    convert( MQCACF_TASK_NUMBER               );
    convert( MQCACF_TRANSACTION_ID            );
    convert( MQCACF_Q_MGR_UOW_ID              );
    convert( MQCACF_ORIGIN_NAME               );
    convert( MQCACF_ENV_INFO                  );
    convert( MQCACF_SECURITY_PROFILE          );
    convert( MQCACF_CONFIGURATION_DATE        );
    convert( MQCACF_CONFIGURATION_TIME        );
    convert( MQCACF_FROM_CF_STRUC_NAME        );
    convert( MQCACF_TO_CF_STRUC_NAME          );
    convert( MQCACF_CF_STRUC_NAMES            );
    convert( MQCACF_FAIL_DATE                 );
    convert( MQCACF_FAIL_TIME                 );
    convert( MQCACF_BACKUP_DATE               );
    convert( MQCACF_BACKUP_TIME               );
    convert( MQCACF_SYSTEM_NAME               );
    convert( MQCACF_CF_STRUC_BACKUP_START     );
    convert( MQCACF_CF_STRUC_BACKUP_END       );
    convert( MQCACF_CF_STRUC_LOG_Q_MGRS       );
    convert( MQCACF_FROM_STORAGE_CLASS        );
    convert( MQCACF_TO_STORAGE_CLASS          );
    convert( MQCACF_STORAGE_CLASS_NAMES       );
    convert( MQCACF_DSG_NAME                  );
    convert( MQCACF_DB2_NAME                  );
    convert( MQCACF_SYSP_CMD_USER_ID          );
    convert( MQCACF_SYSP_OTMA_GROUP           );
    convert( MQCACF_SYSP_OTMA_MEMBER          );
    convert( MQCACF_SYSP_OTMA_DRU_EXIT        );
    convert( MQCACF_SYSP_OTMA_TPIPE_PFX       );
    convert( MQCACF_SYSP_ARCHIVE_PFX1         );
    convert( MQCACF_SYSP_ARCHIVE_UNIT1        );
    convert( MQCACF_SYSP_LOG_CORREL_ID        );
    convert( MQCACF_SYSP_UNIT_VOLSER          );
    convert( MQCACF_SYSP_Q_MGR_TIME           );
    convert( MQCACF_SYSP_Q_MGR_DATE           );
    convert( MQCACF_SYSP_Q_MGR_RBA            );
    convert( MQCACF_SYSP_LOG_RBA              );
    convert( MQCACF_SYSP_SERVICE              );
    convert( MQCACF_FROM_LISTENER_NAME        );
    convert( MQCACF_TO_LISTENER_NAME          );
    convert( MQCACF_FROM_SERVICE_NAME         );
    convert( MQCACF_TO_SERVICE_NAME           );
    convert( MQCACF_LAST_PUT_DATE             );
    convert( MQCACF_LAST_PUT_TIME             );
    convert( MQCACF_LAST_GET_DATE             );
    convert( MQCACF_LAST_GET_TIME             );
    convert( MQCACF_OPERATION_DATE            );
    convert( MQCACF_OPERATION_TIME            );
    convert( MQCACF_ACTIVITY_DESC             );
    convert( MQCACF_APPL_IDENTITY_DATA        );
    convert( MQCACF_APPL_ORIGIN_DATA          );
    convert( MQCACF_PUT_DATE                  );
    convert( MQCACF_PUT_TIME                  );
    convert( MQCACF_REPLY_TO_Q                );
    convert( MQCACF_REPLY_TO_Q_MGR            );
    convert( MQCACF_RESOLVED_Q_NAME           );
    convert( MQCACF_STRUC_ID                  );
    convert( MQCACF_VALUE_NAME                );
    convert( MQCACF_SERVICE_START_DATE        );
    convert( MQCACF_SERVICE_START_TIME        );
    convert( MQCACF_SYSP_OFFLINE_RBA          );
    convert( MQCACF_SYSP_ARCHIVE_PFX2         );
    convert( MQCACF_SYSP_ARCHIVE_UNIT2        );
    convert( MQCACF_TO_TOPIC_NAME             );
    convert( MQCACF_FROM_TOPIC_NAME           );
    convert( MQCACF_TOPIC_NAMES               );
    convert( MQCACF_SUB_NAME                  );
    convert( MQCACF_DESTINATION_Q_MGR         );
    convert( MQCACF_DESTINATION               );
    convert( MQCACF_SUB_USER_ID               );
    convert( MQCACF_SUB_USER_DATA             );
    convert( MQCACF_SUB_SELECTOR              );
    convert( MQCACF_LAST_PUB_DATE             );
    convert( MQCACF_LAST_PUB_TIME             );
    convert( MQCACF_FROM_SUB_NAME             );
    convert( MQCACF_TO_SUB_NAME               );
    convert( MQCACF_LAST_MSG_TIME             );
    convert( MQCACF_LAST_MSG_DATE             );
    convert( MQCACF_SUBSCRIPTION_POINT        );
    convert( MQCACF_FILTER                    );
    convert( MQCACF_NONE                      );
    convert( MQCACF_ADMIN_TOPIC_NAMES         );
    convert( MQCACF_ROUTING_FINGER_PRINT      );
    convert( MQCACF_APPL_DESC                 );
//  convert( MQCACF_LAST_USED                 );
//  convert( MQCACH_FIRST                     );
    convert( MQCACH_CHANNEL_NAME              );
    convert( MQCACH_DESC                      );
    convert( MQCACH_MODE_NAME                 );
    convert( MQCACH_TP_NAME                   );
    convert( MQCACH_XMIT_Q_NAME               );
    convert( MQCACH_CONNECTION_NAME           );
    convert( MQCACH_MCA_NAME                  );
    convert( MQCACH_SEC_EXIT_NAME             );
    convert( MQCACH_MSG_EXIT_NAME             );
    convert( MQCACH_SEND_EXIT_NAME            );
    convert( MQCACH_RCV_EXIT_NAME             );
    convert( MQCACH_CHANNEL_NAMES             );
    convert( MQCACH_SEC_EXIT_USER_DATA        );
    convert( MQCACH_MSG_EXIT_USER_DATA        );
    convert( MQCACH_SEND_EXIT_USER_DATA       );
    convert( MQCACH_RCV_EXIT_USER_DATA        );
    convert( MQCACH_USER_ID                   );
    convert( MQCACH_PASSWORD                  );
    convert( MQCACH_LOCAL_ADDRESS             );
    convert( MQCACH_LOCAL_NAME                );
    convert( MQCACH_LAST_MSG_TIME             );
    convert( MQCACH_LAST_MSG_DATE             );
    convert( MQCACH_MCA_USER_ID               );
    convert( MQCACH_CHANNEL_START_TIME        );
    convert( MQCACH_CHANNEL_START_DATE        );
    convert( MQCACH_MCA_JOB_NAME              );
    convert( MQCACH_LAST_LUWID                );
    convert( MQCACH_CURRENT_LUWID             );
    convert( MQCACH_FORMAT_NAME               );
    convert( MQCACH_MR_EXIT_NAME              );
    convert( MQCACH_MR_EXIT_USER_DATA         );
    convert( MQCACH_SSL_CIPHER_SPEC           );
    convert( MQCACH_SSL_PEER_NAME             );
    convert( MQCACH_SSL_HANDSHAKE_STAGE       );
    convert( MQCACH_SSL_SHORT_PEER_NAME       );
    convert( MQCACH_REMOTE_APPL_TAG           );
    convert( MQCACH_SSL_CERT_USER_ID          );
    convert( MQCACH_SSL_CERT_ISSUER_NAME      );
    convert( MQCACH_LU_NAME                   );
    convert( MQCACH_IP_ADDRESS                );
    convert( MQCACH_TCP_NAME                  );
    convert( MQCACH_LISTENER_NAME             );
    convert( MQCACH_LISTENER_DESC             );
    convert( MQCACH_LISTENER_START_DATE       );
    convert( MQCACH_LISTENER_START_TIME       );
    convert( MQCACH_SSL_KEY_RESET_DATE        );
    convert( MQCACH_SSL_KEY_RESET_TIME        );
//  convert( MQCACH_LAST_USED                 );
//  convert( MQIACH_FIRST                     );
    convert( MQIACH_XMIT_PROTOCOL_TYPE        );
    convert( MQIACH_BATCH_SIZE                );
    convert( MQIACH_DISC_INTERVAL             );
    convert( MQIACH_SHORT_TIMER               );
    convert( MQIACH_SHORT_RETRY               );
    convert( MQIACH_LONG_TIMER                );
    convert( MQIACH_LONG_RETRY                );
    convert( MQIACH_PUT_AUTHORITY             );
    convert( MQIACH_SEQUENCE_NUMBER_WRAP      );
    convert( MQIACH_MAX_MSG_LENGTH            );
    convert( MQIACH_CHANNEL_TYPE              );
    convert( MQIACH_DATA_COUNT                );
    convert( MQIACH_NAME_COUNT                );
    convert( MQIACH_MSG_SEQUENCE_NUMBER       );
    convert( MQIACH_DATA_CONVERSION           );
    convert( MQIACH_IN_DOUBT                  );
    convert( MQIACH_MCA_TYPE                  );
    convert( MQIACH_SESSION_COUNT             );
    convert( MQIACH_ADAPTER                   );
    convert( MQIACH_COMMAND_COUNT             );
    convert( MQIACH_SOCKET                    );
    convert( MQIACH_PORT                      );
    convert( MQIACH_CHANNEL_INSTANCE_TYPE     );
    convert( MQIACH_CHANNEL_INSTANCE_ATTRS    );
    convert( MQIACH_CHANNEL_ERROR_DATA        );
    convert( MQIACH_CHANNEL_TABLE             );
    convert( MQIACH_CHANNEL_STATUS            );
    convert( MQIACH_INDOUBT_STATUS            );
//  convert( MQIACH_LAST_SEQ_NUMBER           );
    convert( MQIACH_LAST_SEQUENCE_NUMBER      );
    convert( MQIACH_CURRENT_MSGS              );
//  convert( MQIACH_CURRENT_SEQ_NUMBER        );
    convert( MQIACH_CURRENT_SEQUENCE_NUMBER   );
    convert( MQIACH_SSL_RETURN_CODE           );
    convert( MQIACH_MSGS                      );
    convert( MQIACH_BYTES_SENT                );
//  convert( MQIACH_BYTES_RCVD                );
    convert( MQIACH_BYTES_RECEIVED            );
    convert( MQIACH_BATCHES                   );
    convert( MQIACH_BUFFERS_SENT              );
//  convert( MQIACH_BUFFERS_RCVD              );
    convert( MQIACH_BUFFERS_RECEIVED          );
    convert( MQIACH_LONG_RETRIES_LEFT         );
    convert( MQIACH_SHORT_RETRIES_LEFT        );
    convert( MQIACH_MCA_STATUS                );
    convert( MQIACH_STOP_REQUESTED            );
    convert( MQIACH_MR_COUNT                  );
    convert( MQIACH_MR_INTERVAL               );
    convert( MQIACH_NPM_SPEED                 );
    convert( MQIACH_HB_INTERVAL               );
    convert( MQIACH_BATCH_INTERVAL            );
    convert( MQIACH_NETWORK_PRIORITY          );
    convert( MQIACH_KEEP_ALIVE_INTERVAL       );
    convert( MQIACH_BATCH_HB                  );
    convert( MQIACH_SSL_CLIENT_AUTH           );
    convert( MQIACH_ALLOC_RETRY               );
    convert( MQIACH_ALLOC_FAST_TIMER          );
    convert( MQIACH_ALLOC_SLOW_TIMER          );
    convert( MQIACH_DISC_RETRY                );
    convert( MQIACH_PORT_NUMBER               );
    convert( MQIACH_HDR_COMPRESSION           );
    convert( MQIACH_MSG_COMPRESSION           );
    convert( MQIACH_CLWL_CHANNEL_RANK         );
    convert( MQIACH_CLWL_CHANNEL_PRIORITY     );
    convert( MQIACH_CLWL_CHANNEL_WEIGHT       );
    convert( MQIACH_CHANNEL_DISP              );
    convert( MQIACH_INBOUND_DISP              );
    convert( MQIACH_CHANNEL_TYPES             );
    convert( MQIACH_ADAPS_STARTED             );
    convert( MQIACH_ADAPS_MAX                 );
    convert( MQIACH_DISPS_STARTED             );
    convert( MQIACH_DISPS_MAX                 );
    convert( MQIACH_SSLTASKS_STARTED          );
    convert( MQIACH_SSLTASKS_MAX              );
    convert( MQIACH_CURRENT_CHL               );
    convert( MQIACH_CURRENT_CHL_MAX           );
    convert( MQIACH_CURRENT_CHL_TCP           );
    convert( MQIACH_CURRENT_CHL_LU62          );
    convert( MQIACH_ACTIVE_CHL                );
    convert( MQIACH_ACTIVE_CHL_MAX            );
    convert( MQIACH_ACTIVE_CHL_PAUSED         );
    convert( MQIACH_ACTIVE_CHL_STARTED        );
    convert( MQIACH_ACTIVE_CHL_STOPPED        );
    convert( MQIACH_ACTIVE_CHL_RETRY          );
    convert( MQIACH_LISTENER_STATUS           );
    convert( MQIACH_SHARED_CHL_RESTART        );
    convert( MQIACH_LISTENER_CONTROL          );
    convert( MQIACH_BACKLOG                   );
    convert( MQIACH_XMITQ_TIME_INDICATOR      );
    convert( MQIACH_NETWORK_TIME_INDICATOR    );
    convert( MQIACH_EXIT_TIME_INDICATOR       );
    convert( MQIACH_BATCH_SIZE_INDICATOR      );
    convert( MQIACH_XMITQ_MSGS_AVAILABLE      );
    convert( MQIACH_CHANNEL_SUBSTATE          );
    convert( MQIACH_SSL_KEY_RESETS            );
    convert( MQIACH_COMPRESSION_RATE          );
    convert( MQIACH_COMPRESSION_TIME          );
    convert( MQIACH_MAX_XMIT_SIZE             );
    convert( MQIACH_DEF_CHANNEL_DISP          );
    convert( MQIACH_SHARING_CONVERSATIONS     );
    convert( MQIACH_MAX_SHARING_CONVS         );
    convert( MQIACH_CURRENT_SHARING_CONVS     );
    convert( MQIACH_MAX_INSTANCES             );
    convert( MQIACH_MAX_INSTS_PER_CLIENT      );
    convert( MQIACH_CLIENT_CHANNEL_WEIGHT     );
    convert( MQIACH_CONNECTION_AFFINITY       );
//  convert( MQIACH_LAST_USED                 );
//  convert( MQIACF_FIRST                     );
    convert( MQIACF_Q_MGR_ATTRS               );
    convert( MQIACF_Q_ATTRS                   );
    convert( MQIACF_PROCESS_ATTRS             );
    convert( MQIACF_NAMELIST_ATTRS            );
    convert( MQIACF_FORCE                     );
    convert( MQIACF_REPLACE                   );
    convert( MQIACF_PURGE                     );
    convert( MQIACF_QUIESCE                   );
//  convert( MQIACF_MODE                      );
    convert( MQIACF_ALL                       );
    convert( MQIACF_EVENT_APPL_TYPE           );
    convert( MQIACF_EVENT_ORIGIN              );
    convert( MQIACF_PARAMETER_ID              );
    convert( MQIACF_ERROR_ID                  );
//  convert( MQIACF_ERROR_IDENTIFIER          );
    convert( MQIACF_SELECTOR                  );
    convert( MQIACF_CHANNEL_ATTRS             );
    convert( MQIACF_OBJECT_TYPE               );
    convert( MQIACF_ESCAPE_TYPE               );
    convert( MQIACF_ERROR_OFFSET              );
    convert( MQIACF_AUTH_INFO_ATTRS           );
    convert( MQIACF_REASON_QUALIFIER          );
    convert( MQIACF_COMMAND                   );
    convert( MQIACF_OPEN_OPTIONS              );
    convert( MQIACF_OPEN_TYPE                 );
    convert( MQIACF_PROCESS_ID                );
    convert( MQIACF_THREAD_ID                 );
    convert( MQIACF_Q_STATUS_ATTRS            );
    convert( MQIACF_UNCOMMITTED_MSGS          );
    convert( MQIACF_HANDLE_STATE              );
    convert( MQIACF_AUX_ERROR_DATA_INT_1      );
    convert( MQIACF_AUX_ERROR_DATA_INT_2      );
    convert( MQIACF_CONV_REASON_CODE          );
    convert( MQIACF_BRIDGE_TYPE               );
    convert( MQIACF_INQUIRY                   );
    convert( MQIACF_WAIT_INTERVAL             );
    convert( MQIACF_OPTIONS                   );
    convert( MQIACF_BROKER_OPTIONS            );
    convert( MQIACF_REFRESH_TYPE              );
    convert( MQIACF_SEQUENCE_NUMBER           );
    convert( MQIACF_INTEGER_DATA              );
    convert( MQIACF_REGISTRATION_OPTIONS      );
    convert( MQIACF_PUBLICATION_OPTIONS       );
    convert( MQIACF_CLUSTER_INFO              );
    convert( MQIACF_Q_MGR_DEFINITION_TYPE     );
    convert( MQIACF_Q_MGR_TYPE                );
    convert( MQIACF_ACTION                    );
    convert( MQIACF_SUSPEND                   );
    convert( MQIACF_BROKER_COUNT              );
    convert( MQIACF_APPL_COUNT                );
    convert( MQIACF_ANONYMOUS_COUNT           );
    convert( MQIACF_REG_REG_OPTIONS           );
    convert( MQIACF_DELETE_OPTIONS            );
    convert( MQIACF_CLUSTER_Q_MGR_ATTRS       );
    convert( MQIACF_REFRESH_INTERVAL          );
    convert( MQIACF_REFRESH_REPOSITORY        );
    convert( MQIACF_REMOVE_QUEUES             );
    convert( MQIACF_OPEN_INPUT_TYPE           );
    convert( MQIACF_OPEN_OUTPUT               );
    convert( MQIACF_OPEN_SET                  );
    convert( MQIACF_OPEN_INQUIRE              );
    convert( MQIACF_OPEN_BROWSE               );
    convert( MQIACF_Q_STATUS_TYPE             );
    convert( MQIACF_Q_HANDLE                  );
    convert( MQIACF_Q_STATUS                  );
    convert( MQIACF_SECURITY_TYPE             );
    convert( MQIACF_CONNECTION_ATTRS          );
    convert( MQIACF_CONNECT_OPTIONS           );
    convert( MQIACF_CONN_INFO_TYPE            );
    convert( MQIACF_CONN_INFO_CONN            );
    convert( MQIACF_CONN_INFO_HANDLE          );
    convert( MQIACF_CONN_INFO_ALL             );
    convert( MQIACF_AUTH_PROFILE_ATTRS        );
    convert( MQIACF_AUTHORIZATION_LIST        );
    convert( MQIACF_AUTH_ADD_AUTHS            );
    convert( MQIACF_AUTH_REMOVE_AUTHS         );
    convert( MQIACF_ENTITY_TYPE               );
    convert( MQIACF_COMMAND_INFO              );
    convert( MQIACF_CMDSCOPE_Q_MGR_COUNT      );
    convert( MQIACF_Q_MGR_SYSTEM              );
    convert( MQIACF_Q_MGR_EVENT               );
    convert( MQIACF_Q_MGR_DQM                 );
    convert( MQIACF_Q_MGR_CLUSTER             );
    convert( MQIACF_QSG_DISPS                 );
    convert( MQIACF_UOW_STATE                 );
    convert( MQIACF_SECURITY_ITEM             );
    convert( MQIACF_CF_STRUC_STATUS           );
    convert( MQIACF_UOW_TYPE                  );
    convert( MQIACF_CF_STRUC_ATTRS            );
    convert( MQIACF_EXCLUDE_INTERVAL          );
    convert( MQIACF_CF_STATUS_TYPE            );
    convert( MQIACF_CF_STATUS_SUMMARY         );
    convert( MQIACF_CF_STATUS_CONNECT         );
    convert( MQIACF_CF_STATUS_BACKUP          );
    convert( MQIACF_CF_STRUC_TYPE             );
    convert( MQIACF_CF_STRUC_SIZE_MAX         );
    convert( MQIACF_CF_STRUC_SIZE_USED        );
    convert( MQIACF_CF_STRUC_ENTRIES_MAX      );
    convert( MQIACF_CF_STRUC_ENTRIES_USED     );
    convert( MQIACF_CF_STRUC_BACKUP_SIZE      );
    convert( MQIACF_MOVE_TYPE                 );
    convert( MQIACF_MOVE_TYPE_MOVE            );
    convert( MQIACF_MOVE_TYPE_ADD             );
    convert( MQIACF_Q_MGR_NUMBER              );
    convert( MQIACF_Q_MGR_STATUS              );
    convert( MQIACF_DB2_CONN_STATUS           );
    convert( MQIACF_SECURITY_ATTRS            );
    convert( MQIACF_SECURITY_TIMEOUT          );
    convert( MQIACF_SECURITY_INTERVAL         );
    convert( MQIACF_SECURITY_SWITCH           );
    convert( MQIACF_SECURITY_SETTING          );
    convert( MQIACF_STORAGE_CLASS_ATTRS       );
    convert( MQIACF_USAGE_TYPE                );
    convert( MQIACF_BUFFER_POOL_ID            );
    convert( MQIACF_USAGE_TOTAL_PAGES         );
    convert( MQIACF_USAGE_UNUSED_PAGES        );
    convert( MQIACF_USAGE_PERSIST_PAGES       );
    convert( MQIACF_USAGE_NONPERSIST_PAGES    );
    convert( MQIACF_USAGE_RESTART_EXTENTS     );
    convert( MQIACF_USAGE_EXPAND_COUNT        );
    convert( MQIACF_PAGESET_STATUS            );
    convert( MQIACF_USAGE_TOTAL_BUFFERS       );
    convert( MQIACF_USAGE_DATA_SET_TYPE       );
    convert( MQIACF_USAGE_PAGESET             );
    convert( MQIACF_USAGE_DATA_SET            );
    convert( MQIACF_USAGE_BUFFER_POOL         );
    convert( MQIACF_MOVE_COUNT                );
    convert( MQIACF_EXPIRY_Q_COUNT            );
    convert( MQIACF_CONFIGURATION_OBJECTS     );
    convert( MQIACF_CONFIGURATION_EVENTS      );
    convert( MQIACF_SYSP_TYPE                 );
    convert( MQIACF_SYSP_DEALLOC_INTERVAL     );
    convert( MQIACF_SYSP_MAX_ARCHIVE          );
    convert( MQIACF_SYSP_MAX_READ_TAPES       );
    convert( MQIACF_SYSP_IN_BUFFER_SIZE       );
    convert( MQIACF_SYSP_OUT_BUFFER_SIZE      );
    convert( MQIACF_SYSP_OUT_BUFFER_COUNT     );
    convert( MQIACF_SYSP_ARCHIVE              );
    convert( MQIACF_SYSP_DUAL_ACTIVE          );
    convert( MQIACF_SYSP_DUAL_ARCHIVE         );
    convert( MQIACF_SYSP_DUAL_BSDS            );
    convert( MQIACF_SYSP_MAX_CONNS            );
    convert( MQIACF_SYSP_MAX_CONNS_FORE       );
    convert( MQIACF_SYSP_MAX_CONNS_BACK       );
    convert( MQIACF_SYSP_EXIT_INTERVAL        );
    convert( MQIACF_SYSP_EXIT_TASKS           );
    convert( MQIACF_SYSP_CHKPOINT_COUNT       );
    convert( MQIACF_SYSP_OTMA_INTERVAL        );
    convert( MQIACF_SYSP_Q_INDEX_DEFER        );
    convert( MQIACF_SYSP_DB2_TASKS            );
    convert( MQIACF_SYSP_RESLEVEL_AUDIT       );
    convert( MQIACF_SYSP_ROUTING_CODE         );
    convert( MQIACF_SYSP_SMF_ACCOUNTING       );
    convert( MQIACF_SYSP_SMF_STATS            );
    convert( MQIACF_SYSP_SMF_INTERVAL         );
    convert( MQIACF_SYSP_TRACE_CLASS          );
    convert( MQIACF_SYSP_TRACE_SIZE           );
    convert( MQIACF_SYSP_WLM_INTERVAL         );
    convert( MQIACF_SYSP_ALLOC_UNIT           );
    convert( MQIACF_SYSP_ARCHIVE_RETAIN       );
    convert( MQIACF_SYSP_ARCHIVE_WTOR         );
    convert( MQIACF_SYSP_BLOCK_SIZE           );
    convert( MQIACF_SYSP_CATALOG              );
    convert( MQIACF_SYSP_COMPACT              );
    convert( MQIACF_SYSP_ALLOC_PRIMARY        );
    convert( MQIACF_SYSP_ALLOC_SECONDARY      );
    convert( MQIACF_SYSP_PROTECT              );
    convert( MQIACF_SYSP_QUIESCE_INTERVAL     );
    convert( MQIACF_SYSP_TIMESTAMP            );
    convert( MQIACF_SYSP_UNIT_ADDRESS         );
    convert( MQIACF_SYSP_UNIT_STATUS          );
    convert( MQIACF_SYSP_LOG_COPY             );
    convert( MQIACF_SYSP_LOG_USED             );
    convert( MQIACF_SYSP_LOG_SUSPEND          );
    convert( MQIACF_SYSP_OFFLOAD_STATUS       );
    convert( MQIACF_SYSP_TOTAL_LOGS           );
    convert( MQIACF_SYSP_FULL_LOGS            );
    convert( MQIACF_LISTENER_ATTRS            );
    convert( MQIACF_LISTENER_STATUS_ATTRS     );
    convert( MQIACF_SERVICE_ATTRS             );
    convert( MQIACF_SERVICE_STATUS_ATTRS      );
    convert( MQIACF_Q_TIME_INDICATOR          );
    convert( MQIACF_OLDEST_MSG_AGE            );
    convert( MQIACF_AUTH_OPTIONS              );
    convert( MQIACF_Q_MGR_STATUS_ATTRS        );
    convert( MQIACF_CONNECTION_COUNT          );
    convert( MQIACF_Q_MGR_FACILITY            );
    convert( MQIACF_CHINIT_STATUS             );
    convert( MQIACF_CMD_SERVER_STATUS         );
    convert( MQIACF_ROUTE_DETAIL              );
    convert( MQIACF_RECORDED_ACTIVITIES       );
    convert( MQIACF_MAX_ACTIVITIES            );
    convert( MQIACF_DISCONTINUITY_COUNT       );
    convert( MQIACF_ROUTE_ACCUMULATION        );
    convert( MQIACF_ROUTE_DELIVERY            );
    convert( MQIACF_OPERATION_TYPE            );
    convert( MQIACF_BACKOUT_COUNT             );
    convert( MQIACF_COMP_CODE                 );
    convert( MQIACF_ENCODING                  );
    convert( MQIACF_EXPIRY                    );
    convert( MQIACF_FEEDBACK                  );
    convert( MQIACF_MSG_FLAGS                 );
    convert( MQIACF_MSG_LENGTH                );
    convert( MQIACF_MSG_TYPE                  );
    convert( MQIACF_OFFSET                    );
    convert( MQIACF_ORIGINAL_LENGTH           );
    convert( MQIACF_PERSISTENCE               );
    convert( MQIACF_PRIORITY                  );
    convert( MQIACF_REASON_CODE               );
    convert( MQIACF_REPORT                    );
    convert( MQIACF_VERSION                   );
    convert( MQIACF_UNRECORDED_ACTIVITIES     );
    convert( MQIACF_MONITORING                );
    convert( MQIACF_ROUTE_FORWARDING          );
    convert( MQIACF_SERVICE_STATUS            );
    convert( MQIACF_Q_TYPES                   );
    convert( MQIACF_USER_ID_SUPPORT           );
    convert( MQIACF_INTERFACE_VERSION         );
    convert( MQIACF_AUTH_SERVICE_ATTRS        );
    convert( MQIACF_USAGE_EXPAND_TYPE         );
    convert( MQIACF_SYSP_CLUSTER_CACHE        );
    convert( MQIACF_SYSP_DB2_BLOB_TASKS       );
    convert( MQIACF_SYSP_WLM_INT_UNITS        );
    convert( MQIACF_TOPIC_ATTRS               );
    convert( MQIACF_PUBSUB_PROPERTIES         );
    convert( MQIACF_DESTINATION_CLASS         );
    convert( MQIACF_DURABLE_SUBSCRIPTION      );
    convert( MQIACF_SUBSCRIPTION_SCOPE        );
    convert( MQIACF_VARIABLE_USER_ID          );
    convert( MQIACF_REQUEST_ONLY              );
    convert( MQIACF_PUB_PRIORITY              );
    convert( MQIACF_SUB_ATTRS                 );
    convert( MQIACF_WILDCARD_SCHEMA           );
    convert( MQIACF_SUB_TYPE                  );
    convert( MQIACF_MESSAGE_COUNT             );
    convert( MQIACF_Q_MGR_PUBSUB              );
    convert( MQIACF_Q_MGR_VERSION             );
    convert( MQIACF_SUB_STATUS_ATTRS          );
    convert( MQIACF_TOPIC_STATUS              );
    convert( MQIACF_TOPIC_SUB                 );
    convert( MQIACF_TOPIC_PUB                 );
    convert( MQIACF_RETAINED_PUBLICATION      );
    convert( MQIACF_TOPIC_STATUS_ATTRS        );
    convert( MQIACF_TOPIC_STATUS_TYPE         );
    convert( MQIACF_SUB_OPTIONS               );
    convert( MQIACF_PUBLISH_COUNT             );
    convert( MQIACF_CLEAR_TYPE                );
    convert( MQIACF_CLEAR_SCOPE               );
    convert( MQIACF_SUB_LEVEL                 );
    convert( MQIACF_ASYNC_STATE               );
    convert( MQIACF_SUB_SUMMARY               );
    convert( MQIACF_OBSOLETE_MSGS             );
    convert( MQIACF_PUBSUB_STATUS             );
    convert( MQIACF_PS_STATUS_TYPE            );
    convert( MQIACF_PUBSUB_STATUS_ATTRS       );
    convert( MQIACF_SELECTOR_TYPE             );
    convert( MQIACF_LOG_COMPRESSION           );
    convert( MQIACF_GROUPUR_CHECK_ID          );
    convert( MQIACF_MULC_CAPTURE              );
    convert( MQIACF_PERMIT_STANDBY            );
    convert( MQIACF_OPERATION_MODE            );
//  convert( MQIACF_LAST_USED                 );
//  convert( MQHA_FIRST                       );
    convert( MQHA_BAG_HANDLE                  );
//  convert( MQHA_LAST_USED                   );
  }
 
  return unknownReason( "UNKNOWN MQ ITEM SELECTOR ID", (int)id );
}


/******************************************************************************/
/* item value to string                                                       */
/******************************************************************************/
const char* itemValue2str( MQLONG selector, MQLONG id )
{
  char *rc = NULL ;
  
  switch( selector )
  {
    case MQIASY_TYPE      :{rc=(char*)mqbagType2str(    id);break;}
    case MQIASY_VERSION   :{rc=(char*)mqcfhVer2str(     id);break;}
    case MQIASY_COMMAND   :{rc=(char*)mqcmd2str(        id);break;}
    case MQIASY_CONTROL   :{rc=(char*)mqcfc2str(        id);break;}
    case MQIASY_COMP_CODE :{rc=(char*)mqcompCode2str(   id);break;}
    case MQIASY_REASON    :{rc=(char*)mqrc2str(         id);break;}
    case MQIA_APPL_TYPE   :{rc=(char*)mqPutApplType2str(id);break;}
    case MQIA_BASE_TYPE   :{rc=(char*)mqObjType2str(    id);break;}
    case MQIACF_REASON_QUALIFIER:{rc=(char*)mqrcQualifier2str(id);break;}

    case MQIASY_MSG_SEQ_NUMBER :
    {
      break ;
    }
  }

  return (const char*) rc;
}

/******************************************************************************/
/* mqbag type 2 string (mqiasy_type to string)                                */
/******************************************************************************/
const char* mqbagType2str( MQLONG id )
{
  switch( id )
  {
    convert( MQCFT_NONE                );
    convert( MQCFT_COMMAND             );
    convert( MQCFT_RESPONSE            );
    convert( MQCFT_INTEGER             );
    convert( MQCFT_STRING              );
    convert( MQCFT_INTEGER_LIST        );
    convert( MQCFT_STRING_LIST         );
    convert( MQCFT_EVENT               );
    convert( MQCFT_USER                );
    convert( MQCFT_BYTE_STRING         );
    convert( MQCFT_TRACE_ROUTE         );
    convert( MQCFT_REPORT              );
    convert( MQCFT_INTEGER_FILTER      );
    convert( MQCFT_STRING_FILTER       );
    convert( MQCFT_BYTE_STRING_FILTER  );
    convert( MQCFT_COMMAND_XR          );
    convert( MQCFT_XR_MSG              );
    convert( MQCFT_XR_ITEM             );
    convert( MQCFT_XR_SUMMARY          );
    convert( MQCFT_GROUP               );
    convert( MQCFT_STATISTICS          );
    convert( MQCFT_ACCOUNTING          );
    convert( MQCFT_INTEGER64           );
    convert( MQCFT_INTEGER64_LIST      );
  }
  
  return "UNKNOWN MQ BAG TYPE " ;
}

/******************************************************************************/
/* MQ command to string                                                       */
/******************************************************************************/
const char* mqcmd2str( MQLONG id )
{
  switch( id )
  {
    convert(MQCMD_NONE                    );
    convert(MQCMD_CHANGE_Q_MGR            );
    convert(MQCMD_INQUIRE_Q_MGR           );
    convert(MQCMD_CHANGE_PROCESS          );
    convert(MQCMD_COPY_PROCESS            );
    convert(MQCMD_CREATE_PROCESS          );
    convert(MQCMD_DELETE_PROCESS          );
    convert(MQCMD_INQUIRE_PROCESS         );
    convert(MQCMD_CHANGE_Q                );
    convert(MQCMD_CLEAR_Q                 );
    convert(MQCMD_COPY_Q                  );
    convert(MQCMD_CREATE_Q                );
    convert(MQCMD_DELETE_Q                );
    convert(MQCMD_INQUIRE_Q               );
    convert(MQCMD_REFRESH_Q_MGR           );
    convert(MQCMD_RESET_Q_STATS           );
    convert(MQCMD_INQUIRE_Q_NAMES         );
    convert(MQCMD_INQUIRE_PROCESS_NAMES   );
    convert(MQCMD_INQUIRE_CHANNEL_NAMES   );
    convert(MQCMD_CHANGE_CHANNEL          );
    convert(MQCMD_COPY_CHANNEL            );
    convert(MQCMD_CREATE_CHANNEL          );
    convert(MQCMD_DELETE_CHANNEL          );
    convert(MQCMD_INQUIRE_CHANNEL         );
    convert(MQCMD_PING_CHANNEL            );
    convert(MQCMD_RESET_CHANNEL           );
    convert(MQCMD_START_CHANNEL           );
    convert(MQCMD_STOP_CHANNEL            );
    convert(MQCMD_START_CHANNEL_INIT      );
    convert(MQCMD_START_CHANNEL_LISTENER  );
    convert(MQCMD_CHANGE_NAMELIST         );
    convert(MQCMD_COPY_NAMELIST           );
    convert(MQCMD_CREATE_NAMELIST         );
    convert(MQCMD_DELETE_NAMELIST         );
    convert(MQCMD_INQUIRE_NAMELIST        );
    convert(MQCMD_INQUIRE_NAMELIST_NAMES  );
    convert(MQCMD_ESCAPE                  );
    convert(MQCMD_RESOLVE_CHANNEL         );
    convert(MQCMD_PING_Q_MGR              );
    convert(MQCMD_INQUIRE_Q_STATUS        );
    convert(MQCMD_INQUIRE_CHANNEL_STATUS  );
    convert(MQCMD_CONFIG_EVENT            );
    convert(MQCMD_Q_MGR_EVENT             );
    convert(MQCMD_PERFM_EVENT             );
    convert(MQCMD_CHANNEL_EVENT           );
    convert(MQCMD_DELETE_PUBLICATION      );
    convert(MQCMD_DEREGISTER_PUBLISHER    );
    convert(MQCMD_DEREGISTER_SUBSCRIBER   );
    convert(MQCMD_PUBLISH                 );
    convert(MQCMD_REGISTER_PUBLISHER      );
    convert(MQCMD_REGISTER_SUBSCRIBER     );
    convert(MQCMD_REQUEST_UPDATE          );
    convert(MQCMD_BROKER_INTERNAL         );
    convert(MQCMD_ACTIVITY_MSG            );
    convert(MQCMD_INQUIRE_CLUSTER_Q_MGR   );
    convert(MQCMD_RESUME_Q_MGR_CLUSTER    );
    convert(MQCMD_SUSPEND_Q_MGR_CLUSTER   );
    convert(MQCMD_REFRESH_CLUSTER         );
    convert(MQCMD_RESET_CLUSTER           );
    convert(MQCMD_TRACE_ROUTE             );
    convert(MQCMD_REFRESH_SECURITY        );
    convert(MQCMD_CHANGE_AUTH_INFO        );
    convert(MQCMD_COPY_AUTH_INFO          );
    convert(MQCMD_CREATE_AUTH_INFO        );
    convert(MQCMD_DELETE_AUTH_INFO        );
    convert(MQCMD_INQUIRE_AUTH_INFO       );
    convert(MQCMD_INQUIRE_AUTH_INFO_NAMES );
    convert(MQCMD_INQUIRE_CONNECTION      );
    convert(MQCMD_STOP_CONNECTION         );
    convert(MQCMD_INQUIRE_AUTH_RECS       );
    convert(MQCMD_INQUIRE_ENTITY_AUTH     );
    convert(MQCMD_DELETE_AUTH_REC         );
    convert(MQCMD_SET_AUTH_REC            );
    convert(MQCMD_LOGGER_EVENT            );
    convert(MQCMD_RESET_Q_MGR             );
    convert(MQCMD_CHANGE_LISTENER         );
    convert(MQCMD_COPY_LISTENER           );
    convert(MQCMD_CREATE_LISTENER         );
    convert(MQCMD_DELETE_LISTENER         );
    convert(MQCMD_INQUIRE_LISTENER        );
    convert(MQCMD_INQUIRE_LISTENER_STATUS );
    convert(MQCMD_COMMAND_EVENT           );
    convert(MQCMD_CHANGE_SECURITY         );
    convert(MQCMD_CHANGE_CF_STRUC         );
    convert(MQCMD_CHANGE_STG_CLASS        );
    convert(MQCMD_CHANGE_TRACE            );
    convert(MQCMD_ARCHIVE_LOG             );
    convert(MQCMD_BACKUP_CF_STRUC         );
    convert(MQCMD_CREATE_BUFFER_POOL      );
    convert(MQCMD_CREATE_PAGE_SET         );
    convert(MQCMD_CREATE_CF_STRUC         );
    convert(MQCMD_CREATE_STG_CLASS        );
    convert(MQCMD_COPY_CF_STRUC           );
    convert(MQCMD_COPY_STG_CLASS          );
    convert(MQCMD_DELETE_CF_STRUC         );
    convert(MQCMD_DELETE_STG_CLASS        );
    convert(MQCMD_INQUIRE_ARCHIVE         );
    convert(MQCMD_INQUIRE_CF_STRUC        );
    convert(MQCMD_INQUIRE_CF_STRUC_STATUS );
    convert(MQCMD_INQUIRE_CMD_SERVER      );
    convert(MQCMD_INQUIRE_CHANNEL_INIT    );
    convert(MQCMD_INQUIRE_QSG             );
    convert(MQCMD_INQUIRE_LOG             );
    convert(MQCMD_INQUIRE_SECURITY        );
    convert(MQCMD_INQUIRE_STG_CLASS       );
    convert(MQCMD_INQUIRE_SYSTEM          );
    convert(MQCMD_INQUIRE_THREAD          );
    convert(MQCMD_INQUIRE_TRACE           );
    convert(MQCMD_INQUIRE_USAGE           );
    convert(MQCMD_MOVE_Q                  );
    convert(MQCMD_RECOVER_BSDS            );
    convert(MQCMD_RECOVER_CF_STRUC        );
    convert(MQCMD_RESET_TPIPE             );
    convert(MQCMD_RESOLVE_INDOUBT         );
    convert(MQCMD_RESUME_Q_MGR            );
    convert(MQCMD_REVERIFY_SECURITY       );
    convert(MQCMD_SET_ARCHIVE             );
    convert(MQCMD_SET_LOG                 );
    convert(MQCMD_SET_SYSTEM              );
    convert(MQCMD_START_CMD_SERVER        );
    convert(MQCMD_START_Q_MGR             );
    convert(MQCMD_START_TRACE             );
    convert(MQCMD_STOP_CHANNEL_INIT       );
    convert(MQCMD_STOP_CHANNEL_LISTENER   );
    convert(MQCMD_STOP_CMD_SERVER         );
    convert(MQCMD_STOP_Q_MGR              );
    convert(MQCMD_STOP_TRACE              );
    convert(MQCMD_SUSPEND_Q_MGR           );
    convert(MQCMD_INQUIRE_CF_STRUC_NAMES  );
    convert(MQCMD_INQUIRE_STG_CLASS_NAMES );
    convert(MQCMD_CHANGE_SERVICE          );
    convert(MQCMD_COPY_SERVICE            );
    convert(MQCMD_CREATE_SERVICE          );
    convert(MQCMD_DELETE_SERVICE          );
    convert(MQCMD_INQUIRE_SERVICE         );
    convert(MQCMD_INQUIRE_SERVICE_STATUS  );
    convert(MQCMD_START_SERVICE           );
    convert(MQCMD_STOP_SERVICE            );
    convert(MQCMD_DELETE_BUFFER_POOL      );
    convert(MQCMD_DELETE_PAGE_SET         );
    convert(MQCMD_CHANGE_BUFFER_POOL      );
    convert(MQCMD_CHANGE_PAGE_SET         );
    convert(MQCMD_INQUIRE_Q_MGR_STATUS    );
    convert(MQCMD_CREATE_LOG              );
    convert(MQCMD_STATISTICS_MQI          );
    convert(MQCMD_STATISTICS_Q            );
    convert(MQCMD_STATISTICS_CHANNEL      );
    convert(MQCMD_ACCOUNTING_MQI          );
    convert(MQCMD_ACCOUNTING_Q            );
    convert(MQCMD_INQUIRE_AUTH_SERVICE    );
    convert(MQCMD_CHANGE_TOPIC            );
    convert(MQCMD_COPY_TOPIC              );
    convert(MQCMD_CREATE_TOPIC            );
    convert(MQCMD_DELETE_TOPIC            );
    convert(MQCMD_INQUIRE_TOPIC           );
    convert(MQCMD_INQUIRE_TOPIC_NAMES     );
    convert(MQCMD_INQUIRE_SUBSCRIPTION    );
    convert(MQCMD_CREATE_SUBSCRIPTION     );
    convert(MQCMD_CHANGE_SUBSCRIPTION     );
    convert(MQCMD_DELETE_SUBSCRIPTION     );
    convert(MQCMD_COPY_SUBSCRIPTION       );
    convert(MQCMD_INQUIRE_SUB_STATUS      );
    convert(MQCMD_INQUIRE_TOPIC_STATUS    );
    convert(MQCMD_CLEAR_TOPIC_STRING      );
    convert(MQCMD_INQUIRE_PUBSUB_STATUS   );
  }

//return "UNKNOWN MQ CMD TYPE " ;
  return unknownReason( "UNKNOWN MQ CMD TYPE", id) ;
}

/******************************************************************************/
/*  mq control options to string                                 */
/******************************************************************************/
const char* mqcfc2str( MQLONG id )
{
  switch( id )
  {
    convert( MQCFC_LAST     );
    convert( MQCFC_NOT_LAST );
  }

  return "UNKNOWN MQIA CONTROL OPTION" ;
}

/******************************************************************************/
/*  mq comp code to string                                     */
/******************************************************************************/
const char* mqcompCode2str( MQLONG id )
{
  switch( id )
  {
    convert( MQCC_OK      );
    convert( MQCC_WARNING );
    convert( MQCC_FAILED  );
    convert( MQCC_UNKNOWN );
  }

  return "UNKNOWN COMP CODE" ;
}

/******************************************************************************/
/*  mq reason qualifier to string                                             */
/******************************************************************************/
const char* mqrcQualifier2str( MQLONG id )
{
  switch( id )
  {
    convert( MQRQ_CONN_NOT_AUTHORIZED       );
    convert( MQRQ_OPEN_NOT_AUTHORIZED       );
    convert( MQRQ_CLOSE_NOT_AUTHORIZED      );
    convert( MQRQ_CMD_NOT_AUTHORIZED        );
    convert( MQRQ_Q_MGR_STOPPING            );
    convert( MQRQ_Q_MGR_QUIESCING           );
    convert( MQRQ_CHANNEL_STOPPED_OK        );
    convert( MQRQ_CHANNEL_STOPPED_ERROR     );
    convert( MQRQ_CHANNEL_STOPPED_RETRY     );
    convert( MQRQ_CHANNEL_STOPPED_DISABLED  );
    convert( MQRQ_BRIDGE_STOPPED_OK         );
    convert( MQRQ_BRIDGE_STOPPED_ERROR      );
    convert( MQRQ_SSL_HANDSHAKE_ERROR       );
    convert( MQRQ_SSL_CIPHER_SPEC_ERROR     );
    convert( MQRQ_SSL_CLIENT_AUTH_ERROR     );
    convert( MQRQ_SSL_PEER_NAME_ERROR       );
    convert( MQRQ_SUB_NOT_AUTHORIZED        );
    convert( MQRQ_SUB_DEST_NOT_AUTHORIZED   );
    convert( MQRQ_SSL_UNKNOWN_REVOCATION    );
    convert( MQRQ_SYS_CONN_NOT_AUTHORIZED   );
  }

  return unknownReason( "UNKNOWN COMP CODE", id );
}
/******************************************************************************/
/* string to mq selector                                                      */
/******************************************************************************/
MQLONG str2mqSelector( const char* str )
{
  rconv( str, MQIASY_FIRST                     );
  rconv( str, MQIASY_CODED_CHAR_SET_ID         );
  rconv( str, MQIASY_TYPE                      );
  rconv( str, MQIASY_COMMAND                   );
  rconv( str, MQIASY_MSG_SEQ_NUMBER            );
  rconv( str, MQIASY_CONTROL                   );
  rconv( str, MQIASY_COMP_CODE                 );
  rconv( str, MQIASY_REASON                    );
  rconv( str, MQIASY_BAG_OPTIONS               );
  rconv( str, MQIASY_VERSION                   );
  rconv( str, MQIASY_LAST_USED                 );
  rconv( str, MQIASY_LAST                      );
  rconv( str, MQCA_ADMIN_TOPIC_NAME            );
  rconv( str, MQCA_ALTERATION_DATE             );
  rconv( str, MQCA_ALTERATION_TIME             );
  rconv( str, MQCA_APPL_ID                     );
  rconv( str, MQCA_AUTH_INFO_CONN_NAME         );
  rconv( str, MQCA_AUTH_INFO_DESC              );
  rconv( str, MQCA_AUTH_INFO_NAME              );
  rconv( str, MQCA_AUTH_INFO_OCSP_URL          );
  rconv( str, MQCA_AUTO_REORG_CATALOG          );
  rconv( str, MQCA_AUTO_REORG_START_TIME       );
  rconv( str, MQCA_BACKOUT_REQ_Q_NAME          );
  rconv( str, MQCA_BASE_OBJECT_NAME            );
  rconv( str, MQCA_BASE_Q_NAME                 );
  rconv( str, MQCA_BATCH_INTERFACE_ID          );
  rconv( str, MQCA_CF_STRUC_DESC               );
  rconv( str, MQCA_CF_STRUC_NAME               );
  rconv( str, MQCA_CHANNEL_AUTO_DEF_EXIT       );
  rconv( str, MQCA_CHILD                       );
  rconv( str, MQCA_CHINIT_SERVICE_PARM         );
  rconv( str, MQCA_CICS_FILE_NAME              );
  rconv( str, MQCA_CLUSTER_DATE                );
  rconv( str, MQCA_CLUSTER_NAME                );
  rconv( str, MQCA_CLUSTER_NAMELIST            );
  rconv( str, MQCA_CLUSTER_Q_MGR_NAME          );
  rconv( str, MQCA_CLUSTER_TIME                );
  rconv( str, MQCA_CLUSTER_WORKLOAD_DATA       );
  rconv( str, MQCA_CLUSTER_WORKLOAD_EXIT       );
  rconv( str, MQCA_COMMAND_INPUT_Q_NAME        );
  rconv( str, MQCA_COMMAND_REPLY_Q_NAME        );
  rconv( str, MQCA_CREATION_DATE               );
  rconv( str, MQCA_CREATION_TIME               );
  rconv( str, MQCA_DEAD_LETTER_Q_NAME          );
  rconv( str, MQCA_DEF_XMIT_Q_NAME             );
  rconv( str, MQCA_DNS_GROUP                   );
  rconv( str, MQCA_ENV_DATA                    );
  rconv( str, MQCA_FIRST                       );
  rconv( str, MQCA_IGQ_USER_ID                 );
  rconv( str, MQCA_INITIATION_Q_NAME           );
  rconv( str, MQCA_LAST                        );
  rconv( str, MQCA_LAST_USED                   );
  rconv( str, MQCA_LDAP_PASSWORD               );
  rconv( str, MQCA_LDAP_USER_NAME              );
  rconv( str, MQCA_LU_GROUP_NAME               );
  rconv( str, MQCA_LU_NAME                     );
  rconv( str, MQCA_LU62_ARM_SUFFIX             );
  rconv( str, MQCA_MODEL_DURABLE_Q             );
  rconv( str, MQCA_MODEL_NON_DURABLE_Q         );
  rconv( str, MQCA_MONITOR_Q_NAME              );
  rconv( str, MQCA_NAMELIST_DESC               );
  rconv( str, MQCA_NAMELIST_NAME               );
  rconv( str, MQCA_NAMES                       );
  rconv( str, MQCA_PARENT                      );
  rconv( str, MQCA_PASS_TICKET_APPL            );
  rconv( str, MQCA_PROCESS_DESC                );
  rconv( str, MQCA_PROCESS_NAME                );
  rconv( str, MQCA_Q_DESC                      );
  rconv( str, MQCA_Q_MGR_DESC                  );
  rconv( str, MQCA_Q_MGR_IDENTIFIER            );
  rconv( str, MQCA_Q_MGR_NAME                  );
  rconv( str, MQCA_Q_NAME                      );
  rconv( str, MQCA_QSG_NAME                    );
  rconv( str, MQCA_REMOTE_Q_MGR_NAME           );
  rconv( str, MQCA_REMOTE_Q_NAME               );
  rconv( str, MQCA_REPOSITORY_NAME             );
  rconv( str, MQCA_REPOSITORY_NAMELIST         );
  rconv( str, MQCA_RESUME_DATE                 );
  rconv( str, MQCA_RESUME_TIME                 );
  rconv( str, MQCA_SERVICE_DESC                );
  rconv( str, MQCA_SERVICE_NAME                );
  rconv( str, MQCA_SERVICE_START_ARGS          );
  rconv( str, MQCA_SERVICE_START_COMMAND       );
  rconv( str, MQCA_SERVICE_STOP_ARGS           );
  rconv( str, MQCA_SERVICE_STOP_COMMAND        );
  rconv( str, MQCA_STDERR_DESTINATION          );
  rconv( str, MQCA_STDOUT_DESTINATION          );
  rconv( str, MQCA_SSL_CRL_NAMELIST            );
  rconv( str, MQCA_SSL_CRYPTO_HARDWARE         );
  rconv( str, MQCA_SSL_KEY_LIBRARY             );
  rconv( str, MQCA_SSL_KEY_MEMBER              );
  rconv( str, MQCA_SSL_KEY_REPOSITORY          );
  rconv( str, MQCA_STORAGE_CLASS               );
  rconv( str, MQCA_STORAGE_CLASS_DESC          );
  rconv( str, MQCA_SYSTEM_LOG_Q_NAME           );
  rconv( str, MQCA_TCP_NAME                    );
  rconv( str, MQCA_TOPIC_DESC                  );
  rconv( str, MQCA_TOPIC_NAME                  );
  rconv( str, MQCA_TOPIC_STRING                );
  rconv( str, MQCA_TOPIC_STRING_FILTER         );
  rconv( str, MQCA_TPIPE_NAME                  );
  rconv( str, MQCA_TRIGGER_CHANNEL_NAME        );
  rconv( str, MQCA_TRIGGER_DATA                );
  rconv( str, MQCA_TRIGGER_PROGRAM_NAME        );
  rconv( str, MQCA_TRIGGER_TERM_ID             );
  rconv( str, MQCA_TRIGGER_TRANS_ID            );
  rconv( str, MQCA_USER_DATA                   );
  rconv( str, MQCA_USER_LIST                   );
  rconv( str, MQCA_XCF_GROUP_NAME              );
  rconv( str, MQCA_XCF_MEMBER_NAME             );
  rconv( str, MQCA_XMIT_Q_NAME                 );
  rconv( str, MQIA_ACCOUNTING_CONN_OVERRIDE    );
  rconv( str, MQIA_ACCOUNTING_INTERVAL         );
  rconv( str, MQIA_ACCOUNTING_MQI              );
  rconv( str, MQIA_ACCOUNTING_Q                );
  rconv( str, MQIA_ACTIVE_CHANNELS             );
  rconv( str, MQIA_ACTIVITY_RECORDING          );
  rconv( str, MQIA_ADOPTNEWMCA_CHECK           );
  rconv( str, MQIA_ADOPTNEWMCA_TYPE            );
  rconv( str, MQIA_ADOPTNEWMCA_INTERVAL        );
  rconv( str, MQIA_APPL_TYPE                   );
  rconv( str, MQIA_ARCHIVE                     );
  rconv( str, MQIA_AUTH_INFO_TYPE              );
  rconv( str, MQIA_AUTHORITY_EVENT             );
  rconv( str, MQIA_AUTO_REORG_INTERVAL         );
  rconv( str, MQIA_AUTO_REORGANIZATION         );
  rconv( str, MQIA_BACKOUT_THRESHOLD           );
  rconv( str, MQIA_BASE_TYPE                   );
  rconv( str, MQIA_BATCH_INTERFACE_AUTO        );
  rconv( str, MQIA_BRIDGE_EVENT                );
  rconv( str, MQIA_CF_LEVEL                    );
  rconv( str, MQIA_CF_RECOVER                  );
  rconv( str, MQIA_CHANNEL_AUTO_DEF            );
  rconv( str, MQIA_CHANNEL_AUTO_DEF_EVENT      );
  rconv( str, MQIA_CHANNEL_EVENT               );
  rconv( str, MQIA_CHINIT_ADAPTERS             );
  rconv( str, MQIA_CHINIT_CONTROL              );
  rconv( str, MQIA_CHINIT_DISPATCHERS          );
  rconv( str, MQIA_CHINIT_TRACE_AUTO_START     );
  rconv( str, MQIA_CHINIT_TRACE_TABLE_SIZE     );
  rconv( str, MQIA_CLUSTER_Q_TYPE              );
  rconv( str, MQIA_CLUSTER_WORKLOAD_LENGTH     );
  rconv( str, MQIA_CLWL_MRU_CHANNELS           );
  rconv( str, MQIA_CLWL_Q_RANK                 );
  rconv( str, MQIA_CLWL_Q_PRIORITY             );
  rconv( str, MQIA_CLWL_USEQ                   );
  rconv( str, MQIA_CMD_SERVER_AUTO             );
  rconv( str, MQIA_CMD_SERVER_CONTROL          );
  rconv( str, MQIA_CMD_SERVER_CONVERT_MSG      );
  rconv( str, MQIA_CMD_SERVER_DLQ_MSG          );
  rconv( str, MQIA_CODED_CHAR_SET_ID           );
  rconv( str, MQIA_COMMAND_EVENT               );
  rconv( str, MQIA_COMMAND_LEVEL               );
  rconv( str, MQIA_CONFIGURATION_EVENT         );
  rconv( str, MQIA_CPI_LEVEL                   );
  rconv( str, MQIA_CURRENT_Q_DEPTH             );
  rconv( str, MQIA_DEF_BIND                    );
  rconv( str, MQIA_DEF_INPUT_OPEN_OPTION       );
  rconv( str, MQIA_DEF_PERSISTENCE             );
  rconv( str, MQIA_DEF_PRIORITY                );
  rconv( str, MQIA_DEF_PUT_RESPONSE_TYPE       );
  rconv( str, MQIA_DEF_READ_AHEAD              );
  rconv( str, MQIA_DEFINITION_TYPE             );
  rconv( str, MQIA_DIST_LISTS                  );
  rconv( str, MQIA_DNS_WLM                     );
  rconv( str, MQIA_DURABLE_SUB                 );
  rconv( str, MQIA_EXPIRY_INTERVAL             );
  rconv( str, MQIA_FIRST                       );
  rconv( str, MQIA_GROUP_UR                    );
  rconv( str, MQIA_HARDEN_GET_BACKOUT          );
  rconv( str, MQIA_HIGH_Q_DEPTH                );
  rconv( str, MQIA_IGQ_PUT_AUTHORITY           );
  rconv( str, MQIA_INDEX_TYPE                  );
  rconv( str, MQIA_INHIBIT_EVENT               );
  rconv( str, MQIA_INHIBIT_GET                 );
  rconv( str, MQIA_INHIBIT_PUB                 );
  rconv( str, MQIA_INHIBIT_PUT                 );
  rconv( str, MQIA_INHIBIT_SUB                 );
  rconv( str, MQIA_INTRA_GROUP_QUEUING         );
  rconv( str, MQIA_IP_ADDRESS_VERSION          );
  rconv( str, MQIA_LAST                        );
  rconv( str, MQIA_LAST_USED                   );
  rconv( str, MQIA_LISTENER_PORT_NUMBER        );
  rconv( str, MQIA_LISTENER_TIMER              );
  rconv( str, MQIA_LOGGER_EVENT                );
  rconv( str, MQIA_LU62_CHANNELS               );
  rconv( str, MQIA_LOCAL_EVENT                 );
  rconv( str, MQIA_MSG_MARK_BROWSE_INTERVAL    );
  rconv( str, MQIA_MASTER_ADMIN                );
  rconv( str, MQIA_MAX_CHANNELS                );
  rconv( str, MQIA_MAX_CLIENTS                 );
  rconv( str, MQIA_MAX_GLOBAL_LOCKS            );
  rconv( str, MQIA_MAX_HANDLES                 );
  rconv( str, MQIA_MAX_LOCAL_LOCKS             );
  rconv( str, MQIA_MAX_MSG_LENGTH              );
  rconv( str, MQIA_MAX_OPEN_Q                  );
  rconv( str, MQIA_MAX_PRIORITY                );
  rconv( str, MQIA_MAX_PROPERTIES_LENGTH       );
  rconv( str, MQIA_MAX_Q_DEPTH                 );
  rconv( str, MQIA_MAX_Q_TRIGGERS              );
  rconv( str, MQIA_MAX_RECOVERY_TASKS          );
  rconv( str, MQIA_MAX_UNCOMMITTED_MSGS        );
  rconv( str, MQIA_MONITOR_INTERVAL            );
  rconv( str, MQIA_MONITORING_AUTO_CLUSSDR     );
  rconv( str, MQIA_MONITORING_CHANNEL          );
  rconv( str, MQIA_MONITORING_Q                );
  rconv( str, MQIA_MSG_DELIVERY_SEQUENCE       );
  rconv( str, MQIA_MSG_DEQ_COUNT               );
  rconv( str, MQIA_MSG_ENQ_COUNT               );
  rconv( str, MQIA_NAME_COUNT                  );
  rconv( str, MQIA_NAMELIST_TYPE               );
  rconv( str, MQIA_NPM_CLASS                   );
  rconv( str, MQIA_NPM_DELIVERY                );
  rconv( str, MQIA_OPEN_INPUT_COUNT            );
  rconv( str, MQIA_OPEN_OUTPUT_COUNT           );
  rconv( str, MQIA_OUTBOUND_PORT_MAX           );
  rconv( str, MQIA_OUTBOUND_PORT_MIN           );
  rconv( str, MQIA_PAGESET_ID                  );
  rconv( str, MQIA_PERFORMANCE_EVENT           );
  rconv( str, MQIA_PLATFORM                    );
  rconv( str, MQIA_PM_DELIVERY                 );
  rconv( str, MQIA_PROPERTY_CONTROL            );
  rconv( str, MQIA_PROXY_SUB                   );
  rconv( str, MQIA_PUB_COUNT                   );
  rconv( str, MQIA_PUB_SCOPE                   );
  rconv( str, MQIA_PUBSUB_MAXMSG_RETRY_COUNT   );
  rconv( str, MQIA_PUBSUB_MODE                 );
  rconv( str, MQIA_PUBSUB_NP_MSG               );
  rconv( str, MQIA_PUBSUB_NP_RESP              );
  rconv( str, MQIA_PUBSUB_SYNC_PT              );
  rconv( str, MQIA_Q_DEPTH_HIGH_EVENT          );
  rconv( str, MQIA_Q_DEPTH_HIGH_LIMIT          );
  rconv( str, MQIA_Q_DEPTH_LOW_EVENT           );
  rconv( str, MQIA_Q_DEPTH_LOW_LIMIT           );
  rconv( str, MQIA_Q_DEPTH_MAX_EVENT           );
  rconv( str, MQIA_Q_SERVICE_INTERVAL          );
  rconv( str, MQIA_Q_SERVICE_INTERVAL_EVENT    );
  rconv( str, MQIA_Q_TYPE                      );
  rconv( str, MQIA_Q_USERS                     );
  rconv( str, MQIA_QMOPT_CONS_COMMS_MSGS       );
  rconv( str, MQIA_QMOPT_CONS_CRITICAL_MSGS    );
  rconv( str, MQIA_QMOPT_CONS_ERROR_MSGS       );
  rconv( str, MQIA_QMOPT_CONS_INFO_MSGS        );
  rconv( str, MQIA_QMOPT_CONS_REORG_MSGS       );
  rconv( str, MQIA_QMOPT_CONS_SYSTEM_MSGS      );
  rconv( str, MQIA_QMOPT_CONS_WARNING_MSGS     );
  rconv( str, MQIA_QMOPT_CSMT_ON_ERROR         );
  rconv( str, MQIA_QMOPT_INTERNAL_DUMP         );
  rconv( str, MQIA_QMOPT_LOG_COMMS_MSGS        );
  rconv( str, MQIA_QMOPT_LOG_CRITICAL_MSGS     );
  rconv( str, MQIA_QMOPT_LOG_ERROR_MSGS        );
  rconv( str, MQIA_QMOPT_LOG_INFO_MSGS         );
  rconv( str, MQIA_QMOPT_LOG_REORG_MSGS        );
  rconv( str, MQIA_QMOPT_LOG_SYSTEM_MSGS       );
  rconv( str, MQIA_QMOPT_LOG_WARNING_MSGS      );
  rconv( str, MQIA_QMOPT_TRACE_COMMS           );
  rconv( str, MQIA_QMOPT_TRACE_CONVERSION      );
  rconv( str, MQIA_QMOPT_TRACE_REORG           );
  rconv( str, MQIA_QMOPT_TRACE_MQI_CALLS       );
  rconv( str, MQIA_QMOPT_TRACE_SYSTEM          );
  rconv( str, MQIA_QSG_DISP                    );
  rconv( str, MQIA_READ_AHEAD                  );
  rconv( str, MQIA_RECEIVE_TIMEOUT             );
  rconv( str, MQIA_RECEIVE_TIMEOUT_MIN         );
  rconv( str, MQIA_RECEIVE_TIMEOUT_TYPE        );
  rconv( str, MQIA_REMOTE_EVENT                );
  rconv( str, MQIA_RETENTION_INTERVAL          );
  rconv( str, MQIA_SCOPE                       );
  rconv( str, MQIA_SECURITY_CASE               );
  rconv( str, MQIA_SERVICE_CONTROL             );
  rconv( str, MQIA_SERVICE_TYPE                );
  rconv( str, MQIA_SHAREABILITY                );
  rconv( str, MQIA_SHARED_Q_Q_MGR_NAME         );
  rconv( str, MQIA_SSL_EVENT                   );
  rconv( str, MQIA_SSL_FIPS_REQUIRED           );
  rconv( str, MQIA_SSL_RESET_COUNT             );
  rconv( str, MQIA_SSL_TASKS                   );
  rconv( str, MQIA_START_STOP_EVENT            );
  rconv( str, MQIA_STATISTICS_CHANNEL          );
  rconv( str, MQIA_STATISTICS_AUTO_CLUSSDR     );
  rconv( str, MQIA_STATISTICS_INTERVAL         );
  rconv( str, MQIA_STATISTICS_MQI              );
  rconv( str, MQIA_STATISTICS_Q                );
  rconv( str, MQIA_SUB_COUNT                   );
  rconv( str, MQIA_SUB_SCOPE                   );
  rconv( str, MQIA_SYNCPOINT                   );
  rconv( str, MQIA_TCP_CHANNELS                );
  rconv( str, MQIA_TCP_KEEP_ALIVE              );
  rconv( str, MQIA_TCP_STACK_TYPE              );
  rconv( str, MQIA_TIME_SINCE_RESET            );
  rconv( str, MQIA_TOPIC_DEF_PERSISTENCE       );
  rconv( str, MQIA_TOPIC_TYPE                  );
  rconv( str, MQIA_TRACE_ROUTE_RECORDING       );
  rconv( str, MQIA_TREE_LIFE_TIME              );
  rconv( str, MQIA_TRIGGER_CONTROL             );
  rconv( str, MQIA_TRIGGER_DEPTH               );
  rconv( str, MQIA_TRIGGER_INTERVAL            );
  rconv( str, MQIA_TRIGGER_MSG_PRIORITY        );
  rconv( str, MQIA_TRIGGER_TYPE                );
  rconv( str, MQIA_TRIGGER_RESTART             );
  rconv( str, MQIA_UR_DISP                     );
  rconv( str, MQIA_USAGE                       );
  rconv( str, MQIA_USER_LIST                   );
  rconv( str, MQIA_WILDCARD_OPERATION          );
  rconv( str, MQCACF_FIRST                     );
  rconv( str, MQCACF_FROM_Q_NAME               );
  rconv( str, MQCACF_TO_Q_NAME                 );
  rconv( str, MQCACF_FROM_PROCESS_NAME         );
  rconv( str, MQCACF_TO_PROCESS_NAME           );
  rconv( str, MQCACF_FROM_NAMELIST_NAME        );
  rconv( str, MQCACF_TO_NAMELIST_NAME          );
  rconv( str, MQCACF_FROM_CHANNEL_NAME         );
  rconv( str, MQCACF_TO_CHANNEL_NAME           );
  rconv( str, MQCACF_FROM_AUTH_INFO_NAME       );
  rconv( str, MQCACF_TO_AUTH_INFO_NAME         );
  rconv( str, MQCACF_Q_NAMES                   );
  rconv( str, MQCACF_PROCESS_NAMES             );
  rconv( str, MQCACF_NAMELIST_NAMES            );
  rconv( str, MQCACF_ESCAPE_TEXT               );
  rconv( str, MQCACF_LOCAL_Q_NAMES             );
  rconv( str, MQCACF_MODEL_Q_NAMES             );
  rconv( str, MQCACF_ALIAS_Q_NAMES             );
  rconv( str, MQCACF_REMOTE_Q_NAMES            );
  rconv( str, MQCACF_SENDER_CHANNEL_NAMES      );
  rconv( str, MQCACF_SERVER_CHANNEL_NAMES      );
  rconv( str, MQCACF_REQUESTER_CHANNEL_NAMES   );
  rconv( str, MQCACF_RECEIVER_CHANNEL_NAMES    );
  rconv( str, MQCACF_OBJECT_Q_MGR_NAME         );
  rconv( str, MQCACF_APPL_NAME                 );
  rconv( str, MQCACF_USER_IDENTIFIER           );
  rconv( str, MQCACF_AUX_ERROR_DATA_STR_1      );
  rconv( str, MQCACF_AUX_ERROR_DATA_STR_2      );
  rconv( str, MQCACF_AUX_ERROR_DATA_STR_3      );
  rconv( str, MQCACF_BRIDGE_NAME               );
  rconv( str, MQCACF_STREAM_NAME               );
  rconv( str, MQCACF_TOPIC                     );
  rconv( str, MQCACF_PARENT_Q_MGR_NAME         );
  rconv( str, MQCACF_CORREL_ID                 );
  rconv( str, MQCACF_PUBLISH_TIMESTAMP         );
  rconv( str, MQCACF_STRING_DATA               );
  rconv( str, MQCACF_SUPPORTED_STREAM_NAME     );
  rconv( str, MQCACF_REG_TOPIC                 );
  rconv( str, MQCACF_REG_TIME                  );
  rconv( str, MQCACF_REG_USER_ID               );
  rconv( str, MQCACF_CHILD_Q_MGR_NAME          );
  rconv( str, MQCACF_REG_STREAM_NAME           );
  rconv( str, MQCACF_REG_Q_MGR_NAME            );
  rconv( str, MQCACF_REG_Q_NAME                );
  rconv( str, MQCACF_REG_CORREL_ID             );
  rconv( str, MQCACF_EVENT_USER_ID             );
  rconv( str, MQCACF_OBJECT_NAME               );
  rconv( str, MQCACF_EVENT_Q_MGR               );
  rconv( str, MQCACF_AUTH_INFO_NAMES           );
  rconv( str, MQCACF_EVENT_APPL_IDENTITY       );
  rconv( str, MQCACF_EVENT_APPL_NAME           );
  rconv( str, MQCACF_EVENT_APPL_ORIGIN         );
  rconv( str, MQCACF_SUBSCRIPTION_NAME         );
  rconv( str, MQCACF_REG_SUB_NAME              );
  rconv( str, MQCACF_SUBSCRIPTION_IDENTITY     );
  rconv( str, MQCACF_REG_SUB_IDENTITY          );
  rconv( str, MQCACF_SUBSCRIPTION_USER_DATA    );
  rconv( str, MQCACF_REG_SUB_USER_DATA         );
  rconv( str, MQCACF_APPL_TAG                  );
  rconv( str, MQCACF_DATA_SET_NAME             );
  rconv( str, MQCACF_UOW_START_DATE            );
  rconv( str, MQCACF_UOW_START_TIME            );
  rconv( str, MQCACF_UOW_LOG_START_DATE        );
  rconv( str, MQCACF_UOW_LOG_START_TIME        );
  rconv( str, MQCACF_UOW_LOG_EXTENT_NAME       );
  rconv( str, MQCACF_PRINCIPAL_ENTITY_NAMES    );
  rconv( str, MQCACF_GROUP_ENTITY_NAMES        );
  rconv( str, MQCACF_AUTH_PROFILE_NAME         );
  rconv( str, MQCACF_ENTITY_NAME               );
  rconv( str, MQCACF_SERVICE_COMPONENT         );
  rconv( str, MQCACF_RESPONSE_Q_MGR_NAME       );
  rconv( str, MQCACF_CURRENT_LOG_EXTENT_NAME   );
  rconv( str, MQCACF_RESTART_LOG_EXTENT_NAME   );
  rconv( str, MQCACF_MEDIA_LOG_EXTENT_NAME     );
  rconv( str, MQCACF_LOG_PATH                  );
  rconv( str, MQCACF_COMMAND_MQSC              );
  rconv( str, MQCACF_Q_MGR_CPF                 );
  rconv( str, MQCACF_USAGE_LOG_RBA             );
  rconv( str, MQCACF_USAGE_LOG_LRSN            );
  rconv( str, MQCACF_COMMAND_SCOPE             );
  rconv( str, MQCACF_ASID                      );
  rconv( str, MQCACF_PSB_NAME                  );
  rconv( str, MQCACF_PST_ID                    );
  rconv( str, MQCACF_TASK_NUMBER               );
  rconv( str, MQCACF_TRANSACTION_ID            );
  rconv( str, MQCACF_Q_MGR_UOW_ID              );
  rconv( str, MQCACF_ORIGIN_NAME               );
  rconv( str, MQCACF_ENV_INFO                  );
  rconv( str, MQCACF_SECURITY_PROFILE          );
  rconv( str, MQCACF_CONFIGURATION_DATE        );
  rconv( str, MQCACF_CONFIGURATION_TIME        );
  rconv( str, MQCACF_FROM_CF_STRUC_NAME        );
  rconv( str, MQCACF_TO_CF_STRUC_NAME          );
  rconv( str, MQCACF_CF_STRUC_NAMES            );
  rconv( str, MQCACF_FAIL_DATE                 );
  rconv( str, MQCACF_FAIL_TIME                 );
  rconv( str, MQCACF_BACKUP_DATE               );
  rconv( str, MQCACF_BACKUP_TIME               );
  rconv( str, MQCACF_SYSTEM_NAME               );
  rconv( str, MQCACF_CF_STRUC_BACKUP_START     );
  rconv( str, MQCACF_CF_STRUC_BACKUP_END       );
  rconv( str, MQCACF_CF_STRUC_LOG_Q_MGRS       );
  rconv( str, MQCACF_FROM_STORAGE_CLASS        );
  rconv( str, MQCACF_TO_STORAGE_CLASS          );
  rconv( str, MQCACF_STORAGE_CLASS_NAMES       );
  rconv( str, MQCACF_DSG_NAME                  );
  rconv( str, MQCACF_DB2_NAME                  );
  rconv( str, MQCACF_SYSP_CMD_USER_ID          );
  rconv( str, MQCACF_SYSP_OTMA_GROUP           );
  rconv( str, MQCACF_SYSP_OTMA_MEMBER          );
  rconv( str, MQCACF_SYSP_OTMA_DRU_EXIT        );
  rconv( str, MQCACF_SYSP_OTMA_TPIPE_PFX       );
  rconv( str, MQCACF_SYSP_ARCHIVE_PFX1         );
  rconv( str, MQCACF_SYSP_ARCHIVE_UNIT1        );
  rconv( str, MQCACF_SYSP_LOG_CORREL_ID        );
  rconv( str, MQCACF_SYSP_UNIT_VOLSER          );
  rconv( str, MQCACF_SYSP_Q_MGR_TIME           );
  rconv( str, MQCACF_SYSP_Q_MGR_DATE           );
  rconv( str, MQCACF_SYSP_Q_MGR_RBA            );
  rconv( str, MQCACF_SYSP_LOG_RBA              );
  rconv( str, MQCACF_SYSP_SERVICE              );
  rconv( str, MQCACF_FROM_LISTENER_NAME        );
  rconv( str, MQCACF_TO_LISTENER_NAME          );
  rconv( str, MQCACF_FROM_SERVICE_NAME         );
  rconv( str, MQCACF_TO_SERVICE_NAME           );
  rconv( str, MQCACF_LAST_PUT_DATE             );
  rconv( str, MQCACF_LAST_PUT_TIME             );
  rconv( str, MQCACF_LAST_GET_DATE             );
  rconv( str, MQCACF_LAST_GET_TIME             );
  rconv( str, MQCACF_OPERATION_DATE            );
  rconv( str, MQCACF_OPERATION_TIME            );
  rconv( str, MQCACF_ACTIVITY_DESC             );
  rconv( str, MQCACF_APPL_IDENTITY_DATA        );
  rconv( str, MQCACF_APPL_ORIGIN_DATA          );
  rconv( str, MQCACF_PUT_DATE                  );
  rconv( str, MQCACF_PUT_TIME                  );
  rconv( str, MQCACF_REPLY_TO_Q                );
  rconv( str, MQCACF_REPLY_TO_Q_MGR            );
  rconv( str, MQCACF_RESOLVED_Q_NAME           );
  rconv( str, MQCACF_STRUC_ID                  );
  rconv( str, MQCACF_VALUE_NAME                );
  rconv( str, MQCACF_SERVICE_START_DATE        );
  rconv( str, MQCACF_SERVICE_START_TIME        );
  rconv( str, MQCACF_SYSP_OFFLINE_RBA          );
  rconv( str, MQCACF_SYSP_ARCHIVE_PFX2         );
  rconv( str, MQCACF_SYSP_ARCHIVE_UNIT2        );
  rconv( str, MQCACF_TO_TOPIC_NAME             );
  rconv( str, MQCACF_FROM_TOPIC_NAME           );
  rconv( str, MQCACF_TOPIC_NAMES               );
  rconv( str, MQCACF_SUB_NAME                  );
  rconv( str, MQCACF_DESTINATION_Q_MGR         );
  rconv( str, MQCACF_DESTINATION               );
  rconv( str, MQCACF_SUB_USER_ID               );
  rconv( str, MQCACF_SUB_USER_DATA             );
  rconv( str, MQCACF_SUB_SELECTOR              );
  rconv( str, MQCACF_LAST_PUB_DATE             );
  rconv( str, MQCACF_LAST_PUB_TIME             );
  rconv( str, MQCACF_FROM_SUB_NAME             );
  rconv( str, MQCACF_TO_SUB_NAME               );
  rconv( str, MQCACF_LAST_MSG_TIME             );
  rconv( str, MQCACF_LAST_MSG_DATE             );
  rconv( str, MQCACF_SUBSCRIPTION_POINT        );
  rconv( str, MQCACF_FILTER                    );
  rconv( str, MQCACF_NONE                      );
  rconv( str, MQCACF_ADMIN_TOPIC_NAMES         );
  rconv( str, MQCACF_ROUTING_FINGER_PRINT      );
  rconv( str, MQCACF_APPL_DESC                 );
  rconv( str, MQCACF_LAST_USED                 );
  rconv( str, MQCACH_FIRST                     );
  rconv( str, MQCACH_CHANNEL_NAME              );
  rconv( str, MQCACH_DESC                      );
  rconv( str, MQCACH_MODE_NAME                 );
  rconv( str, MQCACH_TP_NAME                   );
  rconv( str, MQCACH_XMIT_Q_NAME               );
  rconv( str, MQCACH_CONNECTION_NAME           );
  rconv( str, MQCACH_MCA_NAME                  );
  rconv( str, MQCACH_SEC_EXIT_NAME             );
  rconv( str, MQCACH_MSG_EXIT_NAME             );
  rconv( str, MQCACH_SEND_EXIT_NAME            );
  rconv( str, MQCACH_RCV_EXIT_NAME             );
  rconv( str, MQCACH_CHANNEL_NAMES             );
  rconv( str, MQCACH_SEC_EXIT_USER_DATA        );
  rconv( str, MQCACH_MSG_EXIT_USER_DATA        );
  rconv( str, MQCACH_SEND_EXIT_USER_DATA       );
  rconv( str, MQCACH_RCV_EXIT_USER_DATA        );
  rconv( str, MQCACH_USER_ID                   );
  rconv( str, MQCACH_PASSWORD                  );
  rconv( str, MQCACH_LOCAL_ADDRESS             );
  rconv( str, MQCACH_LOCAL_NAME                );
  rconv( str, MQCACH_LAST_MSG_TIME             );
  rconv( str, MQCACH_LAST_MSG_DATE             );
  rconv( str, MQCACH_MCA_USER_ID               );
  rconv( str, MQCACH_CHANNEL_START_TIME        );
  rconv( str, MQCACH_CHANNEL_START_DATE        );
  rconv( str, MQCACH_MCA_JOB_NAME              );
  rconv( str, MQCACH_LAST_LUWID                );
  rconv( str, MQCACH_CURRENT_LUWID             );
  rconv( str, MQCACH_FORMAT_NAME               );
  rconv( str, MQCACH_MR_EXIT_NAME              );
  rconv( str, MQCACH_MR_EXIT_USER_DATA         );
  rconv( str, MQCACH_SSL_CIPHER_SPEC           );
  rconv( str, MQCACH_SSL_PEER_NAME             );
  rconv( str, MQCACH_SSL_HANDSHAKE_STAGE       );
  rconv( str, MQCACH_SSL_SHORT_PEER_NAME       );
  rconv( str, MQCACH_REMOTE_APPL_TAG           );
  rconv( str, MQCACH_SSL_CERT_USER_ID          );
  rconv( str, MQCACH_SSL_CERT_ISSUER_NAME      );
  rconv( str, MQCACH_LU_NAME                   );
  rconv( str, MQCACH_IP_ADDRESS                );
  rconv( str, MQCACH_TCP_NAME                  );
  rconv( str, MQCACH_LISTENER_NAME             );
  rconv( str, MQCACH_LISTENER_DESC             );
  rconv( str, MQCACH_LISTENER_START_DATE       );
  rconv( str, MQCACH_LISTENER_START_TIME       );
  rconv( str, MQCACH_SSL_KEY_RESET_DATE        );
  rconv( str, MQCACH_SSL_KEY_RESET_TIME        );
  rconv( str, MQCACH_LAST_USED                 );
  rconv( str, MQIACH_FIRST                     );
  rconv( str, MQIACH_XMIT_PROTOCOL_TYPE        );
  rconv( str, MQIACH_BATCH_SIZE                );
  rconv( str, MQIACH_DISC_INTERVAL             );
  rconv( str, MQIACH_SHORT_TIMER               );
  rconv( str, MQIACH_SHORT_RETRY               );
  rconv( str, MQIACH_LONG_TIMER                );
  rconv( str, MQIACH_LONG_RETRY                );
  rconv( str, MQIACH_PUT_AUTHORITY             );
  rconv( str, MQIACH_SEQUENCE_NUMBER_WRAP      );
  rconv( str, MQIACH_MAX_MSG_LENGTH            );
  rconv( str, MQIACH_CHANNEL_TYPE              );
  rconv( str, MQIACH_DATA_COUNT                );
  rconv( str, MQIACH_NAME_COUNT                );
  rconv( str, MQIACH_MSG_SEQUENCE_NUMBER       );
  rconv( str, MQIACH_DATA_CONVERSION           );
  rconv( str, MQIACH_IN_DOUBT                  );
  rconv( str, MQIACH_MCA_TYPE                  );
  rconv( str, MQIACH_SESSION_COUNT             );
  rconv( str, MQIACH_ADAPTER                   );
  rconv( str, MQIACH_COMMAND_COUNT             );
  rconv( str, MQIACH_SOCKET                    );
  rconv( str, MQIACH_PORT                      );
  rconv( str, MQIACH_CHANNEL_INSTANCE_TYPE     );
  rconv( str, MQIACH_CHANNEL_INSTANCE_ATTRS    );
  rconv( str, MQIACH_CHANNEL_ERROR_DATA        );
  rconv( str, MQIACH_CHANNEL_TABLE             );
  rconv( str, MQIACH_CHANNEL_STATUS            );
  rconv( str, MQIACH_INDOUBT_STATUS            );
  rconv( str, MQIACH_LAST_SEQ_NUMBER           );
  rconv( str, MQIACH_LAST_SEQUENCE_NUMBER      );
  rconv( str, MQIACH_CURRENT_MSGS              );
  rconv( str, MQIACH_CURRENT_SEQ_NUMBER        );
  rconv( str, MQIACH_CURRENT_SEQUENCE_NUMBER   );
  rconv( str, MQIACH_SSL_RETURN_CODE           );
  rconv( str, MQIACH_MSGS                      );
  rconv( str, MQIACH_BYTES_SENT                );
  rconv( str, MQIACH_BYTES_RCVD                );
  rconv( str, MQIACH_BYTES_RECEIVED            );
  rconv( str, MQIACH_BATCHES                   );
  rconv( str, MQIACH_BUFFERS_SENT              );
  rconv( str, MQIACH_BUFFERS_RCVD              );
  rconv( str, MQIACH_BUFFERS_RECEIVED          );
  rconv( str, MQIACH_LONG_RETRIES_LEFT         );
  rconv( str, MQIACH_SHORT_RETRIES_LEFT        );
  rconv( str, MQIACH_MCA_STATUS                );
  rconv( str, MQIACH_STOP_REQUESTED            );
  rconv( str, MQIACH_MR_COUNT                  );
  rconv( str, MQIACH_MR_INTERVAL               );
  rconv( str, MQIACH_NPM_SPEED                 );
  rconv( str, MQIACH_HB_INTERVAL               );
  rconv( str, MQIACH_BATCH_INTERVAL            );
  rconv( str, MQIACH_NETWORK_PRIORITY          );
  rconv( str, MQIACH_KEEP_ALIVE_INTERVAL       );
  rconv( str, MQIACH_BATCH_HB                  );
  rconv( str, MQIACH_SSL_CLIENT_AUTH           );
  rconv( str, MQIACH_ALLOC_RETRY               );
  rconv( str, MQIACH_ALLOC_FAST_TIMER          );
  rconv( str, MQIACH_ALLOC_SLOW_TIMER          );
  rconv( str, MQIACH_DISC_RETRY                );
  rconv( str, MQIACH_PORT_NUMBER               );
  rconv( str, MQIACH_HDR_COMPRESSION           );
  rconv( str, MQIACH_MSG_COMPRESSION           );
  rconv( str, MQIACH_CLWL_CHANNEL_RANK         );
  rconv( str, MQIACH_CLWL_CHANNEL_PRIORITY     );
  rconv( str, MQIACH_CLWL_CHANNEL_WEIGHT       );
  rconv( str, MQIACH_CHANNEL_DISP              );
  rconv( str, MQIACH_INBOUND_DISP              );
  rconv( str, MQIACH_CHANNEL_TYPES             );
  rconv( str, MQIACH_ADAPS_STARTED             );
  rconv( str, MQIACH_ADAPS_MAX                 );
  rconv( str, MQIACH_DISPS_STARTED             );
  rconv( str, MQIACH_DISPS_MAX                 );
  rconv( str, MQIACH_SSLTASKS_STARTED          );
  rconv( str, MQIACH_SSLTASKS_MAX              );
  rconv( str, MQIACH_CURRENT_CHL               );
  rconv( str, MQIACH_CURRENT_CHL_MAX           );
  rconv( str, MQIACH_CURRENT_CHL_TCP           );
  rconv( str, MQIACH_CURRENT_CHL_LU62          );
  rconv( str, MQIACH_ACTIVE_CHL                );
  rconv( str, MQIACH_ACTIVE_CHL_MAX            );
  rconv( str, MQIACH_ACTIVE_CHL_PAUSED         );
  rconv( str, MQIACH_ACTIVE_CHL_STARTED        );
  rconv( str, MQIACH_ACTIVE_CHL_STOPPED        );
  rconv( str, MQIACH_ACTIVE_CHL_RETRY          );
  rconv( str, MQIACH_LISTENER_STATUS           );
  rconv( str, MQIACH_SHARED_CHL_RESTART        );
  rconv( str, MQIACH_LISTENER_CONTROL          );
  rconv( str, MQIACH_BACKLOG                   );
  rconv( str, MQIACH_XMITQ_TIME_INDICATOR      );
  rconv( str, MQIACH_NETWORK_TIME_INDICATOR    );
  rconv( str, MQIACH_EXIT_TIME_INDICATOR       );
  rconv( str, MQIACH_BATCH_SIZE_INDICATOR      );
  rconv( str, MQIACH_XMITQ_MSGS_AVAILABLE      );
  rconv( str, MQIACH_CHANNEL_SUBSTATE          );
  rconv( str, MQIACH_SSL_KEY_RESETS            );
  rconv( str, MQIACH_COMPRESSION_RATE          );
  rconv( str, MQIACH_COMPRESSION_TIME          );
  rconv( str, MQIACH_MAX_XMIT_SIZE             );
  rconv( str, MQIACH_DEF_CHANNEL_DISP          );
  rconv( str, MQIACH_SHARING_CONVERSATIONS     );
  rconv( str, MQIACH_MAX_SHARING_CONVS         );
  rconv( str, MQIACH_CURRENT_SHARING_CONVS     );
  rconv( str, MQIACH_MAX_INSTANCES             );
  rconv( str, MQIACH_MAX_INSTS_PER_CLIENT      );
  rconv( str, MQIACH_CLIENT_CHANNEL_WEIGHT     );
  rconv( str, MQIACH_CONNECTION_AFFINITY       );
  rconv( str, MQIACH_LAST_USED                 );
  rconv( str, MQIACF_FIRST                     );
  rconv( str, MQIACF_Q_MGR_ATTRS               );
  rconv( str, MQIACF_Q_ATTRS                   );
  rconv( str, MQIACF_PROCESS_ATTRS             );
  rconv( str, MQIACF_NAMELIST_ATTRS            );
  rconv( str, MQIACF_FORCE                     );
  rconv( str, MQIACF_REPLACE                   );
  rconv( str, MQIACF_PURGE                     );
  rconv( str, MQIACF_QUIESCE                   );
  rconv( str, MQIACF_MODE                      );
  rconv( str, MQIACF_ALL                       );
  rconv( str, MQIACF_EVENT_APPL_TYPE           );
  rconv( str, MQIACF_EVENT_ORIGIN              );
  rconv( str, MQIACF_PARAMETER_ID              );
  rconv( str, MQIACF_ERROR_ID                  );
  rconv( str, MQIACF_ERROR_IDENTIFIER          );
  rconv( str, MQIACF_SELECTOR                  );
  rconv( str, MQIACF_CHANNEL_ATTRS             );
  rconv( str, MQIACF_OBJECT_TYPE               );
  rconv( str, MQIACF_ESCAPE_TYPE               );
  rconv( str, MQIACF_ERROR_OFFSET              );
  rconv( str, MQIACF_AUTH_INFO_ATTRS           );
  rconv( str, MQIACF_REASON_QUALIFIER          );
  rconv( str, MQIACF_COMMAND                   );
  rconv( str, MQIACF_OPEN_OPTIONS              );
  rconv( str, MQIACF_OPEN_TYPE                 );
  rconv( str, MQIACF_PROCESS_ID                );
  rconv( str, MQIACF_THREAD_ID                 );
  rconv( str, MQIACF_Q_STATUS_ATTRS            );
  rconv( str, MQIACF_UNCOMMITTED_MSGS          );
  rconv( str, MQIACF_HANDLE_STATE              );
  rconv( str, MQIACF_AUX_ERROR_DATA_INT_1      );
  rconv( str, MQIACF_AUX_ERROR_DATA_INT_2      );
  rconv( str, MQIACF_CONV_REASON_CODE          );
  rconv( str, MQIACF_BRIDGE_TYPE               );
  rconv( str, MQIACF_INQUIRY                   );
  rconv( str, MQIACF_WAIT_INTERVAL             );
  rconv( str, MQIACF_OPTIONS                   );
  rconv( str, MQIACF_BROKER_OPTIONS            );
  rconv( str, MQIACF_REFRESH_TYPE              );
  rconv( str, MQIACF_SEQUENCE_NUMBER           );
  rconv( str, MQIACF_INTEGER_DATA              );
  rconv( str, MQIACF_REGISTRATION_OPTIONS      );
  rconv( str, MQIACF_PUBLICATION_OPTIONS       );
  rconv( str, MQIACF_CLUSTER_INFO              );
  rconv( str, MQIACF_Q_MGR_DEFINITION_TYPE     );
  rconv( str, MQIACF_Q_MGR_TYPE                );
  rconv( str, MQIACF_ACTION                    );
  rconv( str, MQIACF_SUSPEND                   );
  rconv( str, MQIACF_BROKER_COUNT              );
  rconv( str, MQIACF_APPL_COUNT                );
  rconv( str, MQIACF_ANONYMOUS_COUNT           );
  rconv( str, MQIACF_REG_REG_OPTIONS           );
  rconv( str, MQIACF_DELETE_OPTIONS            );
  rconv( str, MQIACF_CLUSTER_Q_MGR_ATTRS       );
  rconv( str, MQIACF_REFRESH_INTERVAL          );
  rconv( str, MQIACF_REFRESH_REPOSITORY        );
  rconv( str, MQIACF_REMOVE_QUEUES             );
  rconv( str, MQIACF_OPEN_INPUT_TYPE           );
  rconv( str, MQIACF_OPEN_OUTPUT               );
  rconv( str, MQIACF_OPEN_SET                  );
  rconv( str, MQIACF_OPEN_INQUIRE              );
  rconv( str, MQIACF_OPEN_BROWSE               );
  rconv( str, MQIACF_Q_STATUS_TYPE             );
  rconv( str, MQIACF_Q_HANDLE                  );
  rconv( str, MQIACF_Q_STATUS                  );
  rconv( str, MQIACF_SECURITY_TYPE             );
  rconv( str, MQIACF_CONNECTION_ATTRS          );
  rconv( str, MQIACF_CONNECT_OPTIONS           );
  rconv( str, MQIACF_CONN_INFO_TYPE            );
  rconv( str, MQIACF_CONN_INFO_CONN            );
  rconv( str, MQIACF_CONN_INFO_HANDLE          );
  rconv( str, MQIACF_CONN_INFO_ALL             );
  rconv( str, MQIACF_AUTH_PROFILE_ATTRS        );
  rconv( str, MQIACF_AUTHORIZATION_LIST        );
  rconv( str, MQIACF_AUTH_ADD_AUTHS            );
  rconv( str, MQIACF_AUTH_REMOVE_AUTHS         );
  rconv( str, MQIACF_ENTITY_TYPE               );
  rconv( str, MQIACF_COMMAND_INFO              );
  rconv( str, MQIACF_CMDSCOPE_Q_MGR_COUNT      );
  rconv( str, MQIACF_Q_MGR_SYSTEM              );
  rconv( str, MQIACF_Q_MGR_EVENT               );
  rconv( str, MQIACF_Q_MGR_DQM                 );
  rconv( str, MQIACF_Q_MGR_CLUSTER             );
  rconv( str, MQIACF_QSG_DISPS                 );
  rconv( str, MQIACF_UOW_STATE                 );
  rconv( str, MQIACF_SECURITY_ITEM             );
  rconv( str, MQIACF_CF_STRUC_STATUS           );
  rconv( str, MQIACF_UOW_TYPE                  );
  rconv( str, MQIACF_CF_STRUC_ATTRS            );
  rconv( str, MQIACF_EXCLUDE_INTERVAL          );
  rconv( str, MQIACF_CF_STATUS_TYPE            );
  rconv( str, MQIACF_CF_STATUS_SUMMARY         );
  rconv( str, MQIACF_CF_STATUS_CONNECT         );
  rconv( str, MQIACF_CF_STATUS_BACKUP          );
  rconv( str, MQIACF_CF_STRUC_TYPE             );
  rconv( str, MQIACF_CF_STRUC_SIZE_MAX         );
  rconv( str, MQIACF_CF_STRUC_SIZE_USED        );
  rconv( str, MQIACF_CF_STRUC_ENTRIES_MAX      );
  rconv( str, MQIACF_CF_STRUC_ENTRIES_USED     );
  rconv( str, MQIACF_CF_STRUC_BACKUP_SIZE      );
  rconv( str, MQIACF_MOVE_TYPE                 );
  rconv( str, MQIACF_MOVE_TYPE_MOVE            );
  rconv( str, MQIACF_MOVE_TYPE_ADD             );
  rconv( str, MQIACF_Q_MGR_NUMBER              );
  rconv( str, MQIACF_Q_MGR_STATUS              );
  rconv( str, MQIACF_DB2_CONN_STATUS           );
  rconv( str, MQIACF_SECURITY_ATTRS            );
  rconv( str, MQIACF_SECURITY_TIMEOUT          );
  rconv( str, MQIACF_SECURITY_INTERVAL         );
  rconv( str, MQIACF_SECURITY_SWITCH           );
  rconv( str, MQIACF_SECURITY_SETTING          );
  rconv( str, MQIACF_STORAGE_CLASS_ATTRS       );
  rconv( str, MQIACF_USAGE_TYPE                );
  rconv( str, MQIACF_BUFFER_POOL_ID            );
  rconv( str, MQIACF_USAGE_TOTAL_PAGES         );
  rconv( str, MQIACF_USAGE_UNUSED_PAGES        );
  rconv( str, MQIACF_USAGE_PERSIST_PAGES       );
  rconv( str, MQIACF_USAGE_NONPERSIST_PAGES    );
  rconv( str, MQIACF_USAGE_RESTART_EXTENTS     );
  rconv( str, MQIACF_USAGE_EXPAND_COUNT        );
  rconv( str, MQIACF_PAGESET_STATUS            );
  rconv( str, MQIACF_USAGE_TOTAL_BUFFERS       );
  rconv( str, MQIACF_USAGE_DATA_SET_TYPE       );
  rconv( str, MQIACF_USAGE_PAGESET             );
  rconv( str, MQIACF_USAGE_DATA_SET            );
  rconv( str, MQIACF_USAGE_BUFFER_POOL         );
  rconv( str, MQIACF_MOVE_COUNT                );
  rconv( str, MQIACF_EXPIRY_Q_COUNT            );
  rconv( str, MQIACF_CONFIGURATION_OBJECTS     );
  rconv( str, MQIACF_CONFIGURATION_EVENTS      );
  rconv( str, MQIACF_SYSP_TYPE                 );
  rconv( str, MQIACF_SYSP_DEALLOC_INTERVAL     );
  rconv( str, MQIACF_SYSP_MAX_ARCHIVE          );
  rconv( str, MQIACF_SYSP_MAX_READ_TAPES       );
  rconv( str, MQIACF_SYSP_IN_BUFFER_SIZE       );
  rconv( str, MQIACF_SYSP_OUT_BUFFER_SIZE      );
  rconv( str, MQIACF_SYSP_OUT_BUFFER_COUNT     );
  rconv( str, MQIACF_SYSP_ARCHIVE              );
  rconv( str, MQIACF_SYSP_DUAL_ACTIVE          );
  rconv( str, MQIACF_SYSP_DUAL_ARCHIVE         );
  rconv( str, MQIACF_SYSP_DUAL_BSDS            );
  rconv( str, MQIACF_SYSP_MAX_CONNS            );
  rconv( str, MQIACF_SYSP_MAX_CONNS_FORE       );
  rconv( str, MQIACF_SYSP_MAX_CONNS_BACK       );
  rconv( str, MQIACF_SYSP_EXIT_INTERVAL        );
  rconv( str, MQIACF_SYSP_EXIT_TASKS           );
  rconv( str, MQIACF_SYSP_CHKPOINT_COUNT       );
  rconv( str, MQIACF_SYSP_OTMA_INTERVAL        );
  rconv( str, MQIACF_SYSP_Q_INDEX_DEFER        );
  rconv( str, MQIACF_SYSP_DB2_TASKS            );
  rconv( str, MQIACF_SYSP_RESLEVEL_AUDIT       );
  rconv( str, MQIACF_SYSP_ROUTING_CODE         );
  rconv( str, MQIACF_SYSP_SMF_ACCOUNTING       );
  rconv( str, MQIACF_SYSP_SMF_STATS            );
  rconv( str, MQIACF_SYSP_SMF_INTERVAL         );
  rconv( str, MQIACF_SYSP_TRACE_CLASS          );
  rconv( str, MQIACF_SYSP_TRACE_SIZE           );
  rconv( str, MQIACF_SYSP_WLM_INTERVAL         );
  rconv( str, MQIACF_SYSP_ALLOC_UNIT           );
  rconv( str, MQIACF_SYSP_ARCHIVE_RETAIN       );
  rconv( str, MQIACF_SYSP_ARCHIVE_WTOR         );
  rconv( str, MQIACF_SYSP_BLOCK_SIZE           );
  rconv( str, MQIACF_SYSP_CATALOG              );
  rconv( str, MQIACF_SYSP_COMPACT              );
  rconv( str, MQIACF_SYSP_ALLOC_PRIMARY        );
  rconv( str, MQIACF_SYSP_ALLOC_SECONDARY      );
  rconv( str, MQIACF_SYSP_PROTECT              );
  rconv( str, MQIACF_SYSP_QUIESCE_INTERVAL     );
  rconv( str, MQIACF_SYSP_TIMESTAMP            );
  rconv( str, MQIACF_SYSP_UNIT_ADDRESS         );
  rconv( str, MQIACF_SYSP_UNIT_STATUS          );
  rconv( str, MQIACF_SYSP_LOG_COPY             );
  rconv( str, MQIACF_SYSP_LOG_USED             );
  rconv( str, MQIACF_SYSP_LOG_SUSPEND          );
  rconv( str, MQIACF_SYSP_OFFLOAD_STATUS       );
  rconv( str, MQIACF_SYSP_TOTAL_LOGS           );
  rconv( str, MQIACF_SYSP_FULL_LOGS            );
  rconv( str, MQIACF_LISTENER_ATTRS            );
  rconv( str, MQIACF_LISTENER_STATUS_ATTRS     );
  rconv( str, MQIACF_SERVICE_ATTRS             );
  rconv( str, MQIACF_SERVICE_STATUS_ATTRS      );
  rconv( str, MQIACF_Q_TIME_INDICATOR          );
  rconv( str, MQIACF_OLDEST_MSG_AGE            );
  rconv( str, MQIACF_AUTH_OPTIONS              );
  rconv( str, MQIACF_Q_MGR_STATUS_ATTRS        );
  rconv( str, MQIACF_CONNECTION_COUNT          );
  rconv( str, MQIACF_Q_MGR_FACILITY            );
  rconv( str, MQIACF_CHINIT_STATUS             );
  rconv( str, MQIACF_CMD_SERVER_STATUS         );
  rconv( str, MQIACF_ROUTE_DETAIL              );
  rconv( str, MQIACF_RECORDED_ACTIVITIES       );
  rconv( str, MQIACF_MAX_ACTIVITIES            );
  rconv( str, MQIACF_DISCONTINUITY_COUNT       );
  rconv( str, MQIACF_ROUTE_ACCUMULATION        );
  rconv( str, MQIACF_ROUTE_DELIVERY            );
  rconv( str, MQIACF_OPERATION_TYPE            );
  rconv( str, MQIACF_BACKOUT_COUNT             );
  rconv( str, MQIACF_COMP_CODE                 );
  rconv( str, MQIACF_ENCODING                  );
  rconv( str, MQIACF_EXPIRY                    );
  rconv( str, MQIACF_FEEDBACK                  );
  rconv( str, MQIACF_MSG_FLAGS                 );
  rconv( str, MQIACF_MSG_LENGTH                );
  rconv( str, MQIACF_MSG_TYPE                  );
  rconv( str, MQIACF_OFFSET                    );
  rconv( str, MQIACF_ORIGINAL_LENGTH           );
  rconv( str, MQIACF_PERSISTENCE               );
  rconv( str, MQIACF_PRIORITY                  );
  rconv( str, MQIACF_REASON_CODE               );
  rconv( str, MQIACF_REPORT                    );
  rconv( str, MQIACF_VERSION                   );
  rconv( str, MQIACF_UNRECORDED_ACTIVITIES     );
  rconv( str, MQIACF_MONITORING                );
  rconv( str, MQIACF_ROUTE_FORWARDING          );
  rconv( str, MQIACF_SERVICE_STATUS            );
  rconv( str, MQIACF_Q_TYPES                   );
  rconv( str, MQIACF_USER_ID_SUPPORT           );
  rconv( str, MQIACF_INTERFACE_VERSION         );
  rconv( str, MQIACF_AUTH_SERVICE_ATTRS        );
  rconv( str, MQIACF_USAGE_EXPAND_TYPE         );
  rconv( str, MQIACF_SYSP_CLUSTER_CACHE        );
  rconv( str, MQIACF_SYSP_DB2_BLOB_TASKS       );
  rconv( str, MQIACF_SYSP_WLM_INT_UNITS        );
  rconv( str, MQIACF_TOPIC_ATTRS               );
  rconv( str, MQIACF_PUBSUB_PROPERTIES         );
  rconv( str, MQIACF_DESTINATION_CLASS         );
  rconv( str, MQIACF_DURABLE_SUBSCRIPTION      );
  rconv( str, MQIACF_SUBSCRIPTION_SCOPE        );
  rconv( str, MQIACF_VARIABLE_USER_ID          );
  rconv( str, MQIACF_REQUEST_ONLY              );
  rconv( str, MQIACF_PUB_PRIORITY              );
  rconv( str, MQIACF_SUB_ATTRS                 );
  rconv( str, MQIACF_WILDCARD_SCHEMA           );
  rconv( str, MQIACF_SUB_TYPE                  );
  rconv( str, MQIACF_MESSAGE_COUNT             );
  rconv( str, MQIACF_Q_MGR_PUBSUB              );
  rconv( str, MQIACF_Q_MGR_VERSION             );
  rconv( str, MQIACF_SUB_STATUS_ATTRS          );
  rconv( str, MQIACF_TOPIC_STATUS              );
  rconv( str, MQIACF_TOPIC_SUB                 );
  rconv( str, MQIACF_TOPIC_PUB                 );
  rconv( str, MQIACF_RETAINED_PUBLICATION      );
  rconv( str, MQIACF_TOPIC_STATUS_ATTRS        );
  rconv( str, MQIACF_TOPIC_STATUS_TYPE         );
  rconv( str, MQIACF_SUB_OPTIONS               );
  rconv( str, MQIACF_PUBLISH_COUNT             );
  rconv( str, MQIACF_CLEAR_TYPE                );
  rconv( str, MQIACF_CLEAR_SCOPE               );
  rconv( str, MQIACF_SUB_LEVEL                 );
  rconv( str, MQIACF_ASYNC_STATE               );
  rconv( str, MQIACF_SUB_SUMMARY               );
  rconv( str, MQIACF_OBSOLETE_MSGS             );
  rconv( str, MQIACF_PUBSUB_STATUS             );
  rconv( str, MQIACF_PS_STATUS_TYPE            );
  rconv( str, MQIACF_PUBSUB_STATUS_ATTRS       );
  rconv( str, MQIACF_SELECTOR_TYPE             );
  rconv( str, MQIACF_LOG_COMPRESSION           );
  rconv( str, MQIACF_GROUPUR_CHECK_ID          );
  rconv( str, MQIACF_MULC_CAPTURE              );
  rconv( str, MQIACF_PERMIT_STANDBY            );
  rconv( str, MQIACF_OPERATION_MODE            );
  rconv( str, MQIACF_LAST_USED                 );
 
  return MQ_UNKNOWN_SELECTOR ;
}


