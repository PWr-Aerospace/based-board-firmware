#include "stm32f4xx_hal.h"

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
__weak void cpu_fault_handler() {
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

void MemManage_Handler() {
    cpu_fault_handler();
}

void BusFault_Handler() {
    cpu_fault_handler();
}

void UsageFault_Handler() {
    cpu_fault_handler();
}

void NMI_Handler() {
}

void HardFault_Handler() {
    cpu_fault_handler();
}

__weak void SVC_Handler(void);

__weak void PendSV_Handler(void);

__weak void SysTick_Handler(void);

void SVC_Handler() {
}

void DebugMon_Handler() {
}

void PendSV_Handler() {
}

void Error_Handler(void) {
    __disable_irq();
    while (1) {
    }
}
