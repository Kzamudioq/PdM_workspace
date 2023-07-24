#ifndef API_DEBOUNCE_H
#define API_DEBOUNCE_H

#include "main.h"
#include "API_delay.h"

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING
} debounceState_t;

void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue);
void debounceFSM_update(debounceState_t *currentState, delay_t *delay);
bool_t readKey(void);

#endif /* API_DEBOUNCE_H */
