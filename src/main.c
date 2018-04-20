#include "rtcdriver.h"
#include "uartdrv.h"
#include <stddef.h>

// Define receive/transmit operation queues
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS, sbe49_rxBufferQueue);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS, sbe49_txBufferQueue);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS, vecNav_rxBufferQueue);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS, vecNav_txBufferQueue);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS, eco_rxBufferQueue);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS, eco_txBufferQueue);

// Configuration for USART0, location 0
#define SBE49_UART                                      \
  {                                                     \
    USART0,                                             \
    115200,                                             \
    _USART_ROUTELOC0_TXLOC_LOC0,                        \
    _USART_ROUTELOC0_RXLOC_LOC0,                        \
    usartStopbits1,                                     \
    usartNoParity,                                      \
    usartOVS16,                                         \
    false,                                              \
    uartdrvFlowControlNone,                             \
    gpioPortA,                                          \
    4,                                                  \
    gpioPortA,                                          \
    5,                                                  \
    (UARTDRV_Buffer_FifoQueue_t *)&sbe49_rxBufferQueue, \
    (UARTDRV_Buffer_FifoQueue_t *)&sbe49_txBufferQueue, \
    _USART_ROUTELOC1_CTSLOC_LOC0,                       \
    _USART_ROUTELOC1_RTSLOC_LOC0                        \
  }

// Configuration for USART0, location 0
#define VECNAV_UART                                      \
  {                                                      \
    USART5,                                              \
    115200,                                              \
    _USART_ROUTELOC0_TXLOC_LOC0,                         \
    _USART_ROUTELOC0_RXLOC_LOC0,                         \
    usartStopbits1,                                      \
    usartNoParity,                                       \
    usartOVS16,                                          \
    false,                                               \
    uartdrvFlowControlNone,                              \
    gpioPortA,                                           \
    4,                                                   \
    gpioPortA,                                           \
    5,                                                   \
    (UARTDRV_Buffer_FifoQueue_t *)&vecNav_rxBufferQueue, \
    (UARTDRV_Buffer_FifoQueue_t *)&vecNav_txBufferQueue, \
    _USART_ROUTELOC1_CTSLOC_LOC0,                        \
    _USART_ROUTELOC1_RTSLOC_LOC0                         \
  }

// Configuration for USART0, location 0
#define ECO_UART                                      \
  {                                                   \
    USART4,                                           \
    115200,                                           \
    _USART_ROUTELOC0_TXLOC_LOC2,                      \
    _USART_ROUTELOC0_RXLOC_LOC2,                      \
    usartStopbits1,                                   \
    usartNoParity,                                    \
    usartOVS16,                                       \
    false,                                            \
    uartdrvFlowControlNone,                           \
    gpioPortA,                                        \
    4,                                                \
    gpioPortA,                                        \
    5,                                                \
    (UARTDRV_Buffer_FifoQueue_t *)&eco_rxBufferQueue, \
    (UARTDRV_Buffer_FifoQueue_t *)&eco_txBufferQueue, \
    _USART_ROUTELOC1_CTSLOC_LOC0,                     \
    _USART_ROUTELOC1_RTSLOC_LOC0                      \
  }

UARTDRV_HandleData_t sbe49_handleData;
UARTDRV_Handle_t sbe49_handle = &sbe49_handleData;
UARTDRV_HandleData_t vecNav_handleData;
UARTDRV_Handle_t vecNav_handle = &vecNav_handleData;
UARTDRV_HandleData_t eco_handleData;
UARTDRV_Handle_t eco_handle = &eco_handleData;
uint8_t buffer[64];

RTCDRV_TimerID_t sbe49_rtc_id;
RTCDRV_TimerID_t vecNav_rtc_id;
RTCDRV_TimerID_t eco_rtc_id;

void sbe49_callback_UARTTX(UARTDRV_Handle_t handle,
                           Ecode_t transferStatus,
                           uint8_t *data,
                           UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)transferStatus;
  (void)data;
  (void)transferCount;
}

void sbe49_callback_UARTRX(UARTDRV_Handle_t handle,
                           Ecode_t transferStatus,
                           uint8_t *data,
                           UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)transferStatus;
  (void)data;
  (void)transferCount;
}

void vecNav_callback_UARTTX(UARTDRV_Handle_t handle,
                            Ecode_t transferStatus,
                            uint8_t *data,
                            UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)transferStatus;
  (void)data;
  (void)transferCount;
}

void vecNav_callback_UARTRX(UARTDRV_Handle_t handle,
                            Ecode_t transferStatus,
                            uint8_t *data,
                            UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)transferStatus;
  (void)data;
  (void)transferCount;
}

void eco_callback_UARTTX(UARTDRV_Handle_t handle,
                         Ecode_t transferStatus,
                         uint8_t *data,
                         UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)transferStatus;
  (void)data;
  (void)transferCount;
}

void eco_callback_UARTRX(UARTDRV_Handle_t handle,
                         Ecode_t transferStatus,
                         uint8_t *data,
                         UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)transferStatus;
  (void)data;
  (void)transferCount;
}

void sbe49_callback_RTC( RTCDRV_TimerID_t id, void * user )
{
  (void) user; // unused argument in this example

  buffer[0] = 's';
  UARTDRV_Transmit(sbe49_handle, buffer, 1, sbe49_callback_UARTTX);
}

void vecNav_callback_RTC( RTCDRV_TimerID_t id, void * user )
{
  (void) user; // unused argument in this example

  buffer[0] = 'v';
  UARTDRV_Transmit(vecNav_handle, buffer, 1, vecNav_callback_UARTTX);
}

void eco_callback_RTC( RTCDRV_TimerID_t id, void * user )
{
  (void) user; // unused argument in this example

  buffer[0] = 'e';
  UARTDRV_Transmit(eco_handle, buffer, 1, eco_callback_UARTTX);
}

int main( void )
{
  UARTDRV_InitUart_t sbe49_initData = SBE49_UART;
  UARTDRV_InitUart(sbe49_handle, &sbe49_initData);

  UARTDRV_InitUart_t vecNav_initData = VECNAV_UART;
  UARTDRV_InitUart(vecNav_handle, &vecNav_initData);
  UARTDRV_InitUart_t eco_initData = ECO_UART;
  UARTDRV_InitUart(eco_handle, &eco_initData);

  // Initialization of RTCDRV driver
  RTCDRV_Init();
  // Reserve a timer
  Ecode_t sbe = RTCDRV_AllocateTimer( &sbe49_rtc_id );
  Ecode_t vec = RTCDRV_AllocateTimer( &vecNav_rtc_id );
  Ecode_t eco = RTCDRV_AllocateTimer( &eco_rtc_id );

  // Start a periodic timer with 1000 millisecond timeout
  RTCDRV_StartTimer( sbe49_rtc_id, rtcdrvTimerTypePeriodic, 5000, sbe49_callback_RTC, NULL );
  RTCDRV_StartTimer( vecNav_rtc_id, rtcdrvTimerTypePeriodic, 100, vecNav_callback_RTC, NULL );
  RTCDRV_StartTimer( eco_rtc_id, rtcdrvTimerTypePeriodic, 1000, eco_callback_RTC, NULL );

  return 0;
}
