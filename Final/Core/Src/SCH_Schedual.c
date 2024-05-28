/*
 * SCH_Schedual.c
 *
 *  Created on: May 13, 2024
 *      Author: Admin
 */

#include "SCH_Schedual.h"
#include "stm32f1xx_hal.h"
#include "main.h"
Task tasks[MAX_TASKS];
unsigned char Error_code_G = 0;
unsigned char Last_error_code_G = 0;
uint32_t Error_tick_count_G = 0;
unsigned char Index = 0;

void SCH_Go_To_Sleep(){

}
// Function definitions

void SCH_Init(void) {
    unsigned char i;
    for (i = 0; i < MAX_TASKS; i++) {
        SCH_Delete_Task(i);
    }
    Error_code_G = 0;
    //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    // Initialize timer and watchdog
    //Timer_init();
    //Watchdog_init();
}

void SCH_Update(void) {
    unsigned char Index;
    for (Index = 0; Index < MAX_TASKS; Index++) {
        if (tasks[Index].pTask) {
            if (tasks[Index].Delay == 0) {

                tasks[Index].RunMe += 1;
                if (tasks[Index].Period) {
                    tasks[Index].Delay = tasks[Index].Period;

                }
            } else {
                tasks[Index].Delay--;
            }
        }
    }
}

unsigned char SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD) {

    while ((tasks[Index].pTask != 0) && (Index < MAX_TASKS)) {
        Index++;
    }
    if (Index == MAX_TASKS) {
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        return MAX_TASKS;
    }
    tasks[Index].pTask = pFunction;

    tasks[Index].Delay = DELAY;
    tasks[Index].Period = PERIOD;
    tasks[Index].RunMe = 0;
    return Index;
}

unsigned char SCH_Delete_Task(const uint8_t TASK_INDEX) {
    unsigned char Return_code;
    if (tasks[TASK_INDEX].pTask == 0) {
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
        Return_code = RETURN_ERROR;
    } else {
        Return_code = RETURN_NORMAL;
    }
    tasks[TASK_INDEX].pTask = 0;
    tasks[TASK_INDEX].Delay = 0;
    tasks[TASK_INDEX].Period = 0;
    tasks[TASK_INDEX].RunMe = 0;
    return Return_code;
}

// The dispatch function
void SCH_Dispatch_Tasks(void) {
    unsigned char Index;
    // Dispatches (runs) the next task (if one is ready)
    for (Index = 0; Index < MAX_TASKS; Index++) {
        if (tasks[Index].RunMe > 0) {
            (*tasks[Index].pTask)();  // Run the task
            tasks[Index].RunMe -= 1;  // Reset / reduce RunMe flag

            // Periodic tasks will automatically run again
            // - if this is a 'one-shot' task, remove it from the array
            if (tasks[Index].Period == 0) {
                SCH_Delete_Task(Index);

            }
        }
    }
    // Report system status
    SCH_Report_Status();
    // The scheduler enters idle mode at this point
    SCH_Go_To_Sleep();
}

void SCH_Report_Status(void) {
#ifdef SCH_REPORT_ERRORS
    if (Error_code_G != Last_error_code_G) {
        Error_port = 255 - Error_code_G;
        Last_error_code_G = Error_code_G;
        if (Error_code_G != 0) {
            Error_tick_count_G = 60000;
        } else {
            Error_tick_count_G = 0;
        }
    } else {
        if (Error_tick_count_G != 0) {
            if (--Error_tick_count_G == 0) {
                Error_code_G = 0;
            }
        }
    }
#endif
}

/*
// Watchdog related functions
IWDG_HandleTypeDef hiwdg;
static uint32_t counter_for_watchdog = 0;

void MX_IWDG_Init(void) {
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
    hiwdg.Init.Reload = 4095;
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
        Error_Handler();
    }
}

void Watchdog_Refresh(void) {
    HAL_IWDG_Refresh(&hiwdg);
}

unsigned char Is_Watchdog_Reset(void) {
    if (counter_for_watchdog > 3) {
        return 1;
    }
    return 0;
}

void Watchdog_Counting(void) {
    counter_for_watchdog++;
}

void Reset_Watchdog_Counting(void) {
    counter_for_watchdog = 0;
}
*/
