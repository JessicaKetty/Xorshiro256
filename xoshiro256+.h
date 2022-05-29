//
//  xoshiro256+.h
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 06/05/2022.
//

#ifndef xoshiro256__h
#define xoshiro256__h

#include <stdio.h>
#include <stdint.h>

struct xoshiro256p_state {
    uint64_t s[4];
};

uint64_t xoshiro256p(struct xoshiro256p_state *state);
#endif /* xoshiro256__h */
