//
//  xoshiro256**.h
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 09/04/2022.
//

#ifndef xoshiro256___h
#define xoshiro256___h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// ################################## xochiro256** ##################################
struct xoshiro256ss_state {
    uint64_t s[4];
};

uint64_t rol64(uint64_t x, int k);

uint64_t xoshiro256ss(struct xoshiro256ss_state *state);

#endif /* xoshiro256___h */
