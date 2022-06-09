/**
 * Copyright 2022 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
/**
 * @file xmidtsend_rbus.h
 *
 * @description This header defines functions required to manage xmidt send messages via rbus.
 *
 */
 
#ifndef _XMIDTSEND_RBUS_H_
#define _XMIDTSEND_RBUS_H_
#include <rbus.h>
#include "config.h"
#include <uuid/uuid.h>
#ifdef __cplusplus
extern "C" {
#endif

#define XMIDT_SEND_METHOD "Device.X_RDK_Xmidt.SendData"
#define MAX_QUEUE_SIZE (int) get_parodus_cfg()->max-queue-size
#define INPARAMS_PATH   "/tmp/inparams.txt"
/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
typedef struct XmidtMsg__
{
	wrp_msg_t *msg;
	rbusMethodAsyncHandle_t asyncHandle;
	struct XmidtMsg__ *next;
} XmidtMsg;

typedef enum
{
    DELIVERED_SUCCESS = 0,
    INVALID_MSG_TYPE,
    MISSING_SOURCE,
    MISSING_DEST,
    MISSING_CONTENT_TYPE,
    MISSING_PAYLOAD,
    MISSING_PAYLOADLEN,
    INVALID_CONTENT_TYPE,
    ENQUEUE_FAILURE = 100,
    CLIENT_DISCONNECT = 101,
    QUEUE_SIZE_EXCEEDED = 102,
    WRP_ENCODE_FAILURE = 103,
    MSG_PROCESSING_FAILED = 104
} XMIDT_STATUS;
/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/

rbusHandle_t get_parodus_rbus_Handle(void);
void addToXmidtUpstreamQ(wrp_msg_t * msg, rbusMethodAsyncHandle_t asyncHandle);
void* processXmidtUpstreamMsg();
void processXmidtData();
int processData(wrp_msg_t * msg, rbusMethodAsyncHandle_t asyncHandle);
void sendXmidtEventToServer(wrp_msg_t * msg, rbusMethodAsyncHandle_t asyncHandle);
int checkInputParameters(rbusObject_t inParams);
char* generate_transaction_uuid();
void parseRbusInparamsToWrp(rbusObject_t inParams, char *trans_id, wrp_msg_t **eventMsg);
void createOutParamsandSendAck(wrp_msg_t *msg, rbusMethodAsyncHandle_t asyncHandle, char *errorMsg, int statuscode, rbusError_t error);
int validateXmidtData(wrp_msg_t * eventMsg, char **errorMsg, int *statusCode);
void xmidtQDequeue();
bool highQosValueCheck(int qos);
void waitTillConnectionIsUp();
void printRBUSParams(rbusObject_t params, char* file_path);
#ifdef __cplusplus
}
#endif


#endif /* _XMIDTSEND_RBUS_H_ */

