/******************************************************************************/
/*   C O N V E R T   M Q    D E F I N E S   ( T Y P E )   T O   S T R I N G   */
/*                                                                            */
/*  functions:                                                                */
/*   - mqObjType2str                                                          */
/*   - mqmdVer2str                                                            */
/*   - mqodVer2str                                                            */
/*   - mqpmoVer2str                                                           */
/*   - mqgmoVer2str                                                           */
/*   - mqcfhVer2str                        */
/*   - mqReportOption2str                                                     */
/*   - mqMsgTypeId2Str                                                        */
/*   - mqFeedback2str                                                         */
/*   - mqEncondig2str                                                         */
/*   - mqCCSID2str                                                            */
/*   - mqPriority2str                                                         */
/*   - mqPersistence2str                                                      */
/*   - mqPutApplType2str                                                      */
/*   - mqMsgFlag2str                                                          */
/*   - mqItemType2str                                        */
/*   - mqSelector2str                                    */
/*   - itemValue2str                      */
/*   - mqbagType2str                  */
/*                                          */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>

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
/* mqia version 2 string      */
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
   }
  
  return "UNKNOWN MQ ITEM SELECTOR ID" ;
}


/******************************************************************************/
/* item value to string                                                       */
/******************************************************************************/
const char* itemValue2str( MQLONG selector, MQLONG mqlongVal )
{
  char *rc = NULL ;
  
  switch( selector )
  {
    case MQIASY_TYPE :
    {
      rc = (char*) mqbagType2str( mqlongVal );
      break;
    }
    case MQIASY_VERSION :
    {
      rc = (char*) mqcfhVer2str( mqlongVal );
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
/* mq command to string                                                       */
/******************************************************************************/
const char* mqcmd2str( MQLONG id )
{
  switch( id )
  {

