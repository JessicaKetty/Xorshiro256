//
//  xoshiro256+.c
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 06/05/2022.
//

#include "xoshiro256+.h"
#include "xoshiro256**.h"
#include <stdint.h>

uint64_t xoshiro256p(struct xoshiro256p_state *state)
{
    uint64_t *s = state->s;
    uint64_t const result = s[0] + s[3];
    uint64_t const t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;
    s[3] = rol64(s[3], 45);

    return result;
}


