/*
 * SCH_Schedual.h
 *
 *  Created on: May 13, 2024
 *      Author: Admin
 */
#include "stm32f1xx_hal.h"

#ifndef INC_SCH_SCHEDUAL_H_
#define INC_SCH_SCHEDUAL_H_

// Define a structure for tasks
typedef struct {
    // Pointer to the task (must be a 'void(void)' function)
    void (*pTask)(void);
    // Delay (ticks) until the function will (next) be run
    uint32_t Delay;
    // Interval (ticks) between subsequent runs
    uint32_t Period;
    // Incremented (by scheduler) when task is due to execute
    uint8_t RunMe;
    // This is a hint to solve the question below.
    uint32_t TaskID;
} Task;

/// Global variables
#define MAX_TASKS 40
#define NO_TASK_ID 0
extern Task tasks[MAX_TASKS];                  // Declare tasks array as extern
extern unsigned char Error_code_G;             // Declare Error_code_G as extern
extern unsigned char Last_error_code_G;        // Declare Last_error_code_G as extern
#define ERROR_SCH_TOO_MANY_TASKS 1
#define ERROR_SCH_CANNOT_DELETE_TASK 2
#define RETURN_ERROR 1
#define RETURN_NORMAL 0
extern uint32_t Error_tick_count_G;            // Declare Error_tick_count_G as extern

// Function prototypes
void SCH_Init(void);
void SCH_Update(void);
unsigned char SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD);
unsigned char SCH_Delete_Task(const uint8_t TASK_INDEX);
void SCH_Report_Status(void);
void MX_IWDG_Init(void);
void Watchdog_Refresh(void);
unsigned char Is_Watchdog_Reset(void);
void Watchdog_Counting(void);
void Reset_Watchdog_Counting(void);
void SCH_Dispatch_Tasks(void);
void SCH_Go_To_Sleep(void);
#endif /* INC_SCH_SCHEDUAL_H_ */
