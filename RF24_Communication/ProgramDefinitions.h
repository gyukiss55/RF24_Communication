// ProgramDefinitions.h

#pragma once

//#define _RF24_STREAMING_
//#define _RF24_SEND_
//#define _RF24_RECEIVE_
//#define _RF24_SCANNER_

#if defined (_RF24_STREAMING_) || \
(_RF24_SEND_) || \
(_RF24_RECEIVE_) || \
(_RF24_SCANNER_)
#define _RF24_INIT_
#endif

#define _MUTEX_TEST_
//#define _SEMAPHORE_TEST_
#define _RFM8X_TXR_
