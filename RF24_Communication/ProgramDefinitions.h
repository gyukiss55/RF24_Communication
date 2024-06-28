// ProgramDefinitions.h

#pragma once

//#define _RF24_STREAMING_
//#define _RF24_SEND_
#define _RF24_RECEIVE_
//#define _RF24_SCANNER_
//#define _RF24_ACKNOWLEDGEMENTPAYLOAD_TEST_
//#define _RF24_MULTICEIVERDEMO_

#if defined(_RF24_STREAMING_) || \
defined(_RF24_SEND_) || \
defined(_RF24_RECEIVE_) || \
defined(_RF24_SCANNER_)
#define _RF24_INIT_
#endif

//#define _MUTEX_TEST_
//#define _SEMAPHORE_TEST_
//#define _RFM8X_TXR_
