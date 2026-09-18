#include <cstdint>
#include <array>
#include <iostream>

using u32 = uint32_t;

/**
 * CPU modes
 * 
 * There are 7, System and User are different modes but they share resources:
 * 
 * - SystemUser,
 * 
 * - Fiq
 * 
 * - Supervisor
 * 
 * - Abort
 * 
 * - Irq
 * 
 * - Undefined
 */
enum CpuMode {
    SystemUser,
    Fiq,
    Supervisor,
    Abort,
    Irq,
    Undefined,
};

/**
 * ARM7TDMI CPU of the GBA
 *
 * Registers are banked per mode: on a mode switch, R13/R14 (R8-R14 in FIQ)
 * are swapped for private copies, so each exception has its own SP/LR 
 * (Stack Pointer/Link Register)
 */
class ARM7Processor {
    public:
        /// R0-R12 general purpose, R13 = SP, R14 = LR, R15 = PC (User/System view)
        std::array<u32, 16> registers{};

        /// FIQ banked R8-R14
        std::array<u32, 7> bank_fiq{};

        /// Banked R13, R14 for each privileged mode
        std::array<u32, 2> bank_svc{};  // Supervisor
        std::array<u32, 2> bank_abt{};  // Abort
        std::array<u32, 2> bank_irq{};  // Interrupt Request
        std::array<u32, 2> bank_und{};  // Undefined instruction

        /// Current Program Status Register
        u32 cpsr{};

        /// Saved PSR of each exception mode: copy of CPSR
        /// User/System have no SPSR
        u32 spsr_fiq{};
        u32 spsr_svc{};
        u32 spsr_abt{};
        u32 spsr_irq{};
        u32 spsr_und{};

        /// Current mode
        CpuMode mode = CpuMode::Supervisor;
    
};

int main() {
    ARM7Processor var = ARM7Processor();
}
