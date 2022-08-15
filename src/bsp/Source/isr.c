#include "stm32f4xx_hal.h"

volatile uint8_t FatFsCnt = 0;
volatile uint8_t Timer1, Timer2;

void SDTimer_Handler(void)
{
  if(Timer1 > 0)
    Timer1--;

  if(Timer2 > 0)
    Timer2--;
}

void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
    /* These are volatile to try and prevent the compiler/linker optimising them
        away as the variables never actually get used.  If the debugger won't show the
        values of the variables, make them global my moving their declaration outside
        of this function. */
    volatile uint32_t r0, r1, r2, r3, r12, lr, pc, psr;

    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr = pulFaultStackAddress[ 5 ];  /* Link register */
    pc = pulFaultStackAddress[ 6 ];  /* Program counter. */
    psr = pulFaultStackAddress[ 7 ]; /* Program status register. */

    (void)(r0);
    (void)(r1);
    (void)(r2);
    (void)(r3);
    (void)(r12);
    (void)(lr);
    (void)(pc);
    (void)(psr);

    /* When the following line is hit, the variables contain the register values. */
    while(1);
}

/** HardFault handler wrapper in assembly
* It extracts the location of stack frame and passes it to handler
* in C as a pointer. We also extract the LR value as second
* parameter.
*/
__weak void cpu_fault_handler()
{
#if defined (__GNUC__)
    __asm
    (
    " tst lr, #4                                                \n"
    " ite eq                                                    \n"
    " mrseq r0, msp                                             \n"
    " mrsne r0, psp                                             \n"
    " ldr r1, [r0, #24]                                         \n"
    " ldr r2, handler2_address_const                            \n"
    " bx r2                                                     \n"
    " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
#elif defined(__ICCARM__)
    __asm
    (
            " tst lr, #4                                                \n"
            " ite eq                                                    \n"
            " mrseq r0, msp                                             \n"
            " mrsne r0, psp                                             \n"
            " ldr r1, [r0, #24]                                         \n"
            " bl prvGetRegistersFromStack                               \n"
    );
#else
#error "Unsupported compiler"
#endif
}

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
    while (1)
    {
    }
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
    cpu_fault_handler();
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
    cpu_fault_handler();
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
    cpu_fault_handler();
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
    cpu_fault_handler();
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{

}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{

}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	SDTimer_Handler();
    HAL_IncTick();
}

/**
  * @brief  This function is executed in case of error occurrence.
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1) {
    }
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/


