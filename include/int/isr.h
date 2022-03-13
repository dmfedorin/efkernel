#ifndef ISR_H_k8zanpdxd5vlapjtfgs76w86tscbtppd
#define ISR_H_k8zanpdxd5vlapjtfgs76w86tscbtppd

#include <stdint.h>

struct int_frame {
        uint16_t ip, cs, flags, sp, ss;
};

#endif