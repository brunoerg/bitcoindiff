/*!
 * buffer.h - buffer for mako
 * Copyright (c) 2020, Christopher Jeffrey (MIT License).
 * https://github.com/chjj/mako
 */

#ifndef BTC_BUFFER_H
#define BTC_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include "common.h"
#include "impl.h"
#include "types.h"

/*
 * Buffer
 */

BTC_DEFINE_SERIALIZABLE_REFOBJ(btc_buffer, BTC_SCOPE_EXTERN)

BTC_EXTERN void
btc_buffer_init(btc_buffer_t *z);

BTC_EXTERN void
btc_buffer_clear(btc_buffer_t *z);

BTC_EXTERN void
btc_buffer_reset(btc_buffer_t *z);

BTC_EXTERN uint8_t *
btc_buffer_grow(btc_buffer_t *z, size_t zn);

BTC_EXTERN uint8_t *
btc_buffer_resize(btc_buffer_t *z, size_t zn);

BTC_EXTERN void
btc_buffer_set(btc_buffer_t *z, const uint8_t *xp, size_t xn);

BTC_EXTERN void
btc_buffer_copy(btc_buffer_t *z, const btc_buffer_t *x);

BTC_EXTERN void
btc_buffer_roset(btc_buffer_t *z, const uint8_t *xp, size_t xn);

BTC_EXTERN void
btc_buffer_rocopy(btc_buffer_t *z, const btc_buffer_t *x);

BTC_EXTERN void
btc_buffer_rwset(btc_buffer_t *z, uint8_t *zp, size_t zn);

BTC_EXTERN uint32_t
btc_buffer_hash(const btc_buffer_t *x);

BTC_EXTERN int
btc_buffer_equal(const btc_buffer_t *x, const btc_buffer_t *y);

BTC_EXTERN int
btc_buffer_compare(const btc_buffer_t *x, const btc_buffer_t *y);

BTC_EXTERN void
btc_buffer_push(btc_buffer_t *z, int x);

BTC_EXTERN size_t
btc_buffer_size(const btc_buffer_t *x);

BTC_EXTERN uint8_t *
btc_buffer_write(uint8_t *zp, const btc_buffer_t *x);

BTC_EXTERN int
btc_buffer_read(btc_buffer_t *z, const uint8_t **xp, size_t *xn);

BTC_EXTERN void
btc_buffer_update(btc__hash256_t *ctx, const btc_buffer_t *x);

BTC_EXTERN void
btc_buffer_inspect(const btc_buffer_t *item);

#ifdef __cplusplus
}
#endif

#endif /* BTC_BUFFER_H */
