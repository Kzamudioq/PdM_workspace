#ifndef API_UART2_H
#define API_UART2_H

#include "main.h"

void API_UART2_Init(void);
void API_UART2_SendSemaphoreInitMessage(void);
void API_UART2_SendMessage(const char *message);

#endif /* API_UART2_H */
