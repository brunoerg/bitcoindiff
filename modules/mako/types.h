/*!
 * types.h - types for mako
 * Copyright (c) 2020, Christopher Jeffrey (MIT License).
 * https://github.com/chjj/mako
 */

#ifndef BTC_TYPES_H
#define BTC_TYPES_H

#include <stddef.h>
#include <stdint.h>

/*
 * Map
 */

#define BTC_DEFINE_MAP_TYPES(name, key_t, val_t) \
typedef struct kh_##name##_s {                   \
  unsigned int n_buckets;                        \
  unsigned int size;                             \
  unsigned int n_occupied;                       \
  unsigned int upper_bound;                      \
  unsigned int *flags;                           \
  key_t *keys;                                   \
  val_t *vals;                                   \
} kh_##name##_t;                                 \
                                                 \
typedef struct kh_##name##_s name##_t;           \
                                                 \
typedef struct name##iter_s {                    \
  const struct kh_##name##_s *map;               \
  unsigned int it;                               \
  key_t key;                                     \
  val_t val;                                     \
} name##iter_t

typedef unsigned int btc_mapiter_t;

/*
 * Set
 */

#define BTC_DEFINE_SET_TYPES(name, key_t) \
  BTC_DEFINE_MAP_TYPES(name, key_t, char)

/*
 * Types
 */

typedef struct btc_buffer_s {
  uint8_t *data;
  size_t alloc;
  size_t length;
  int _refs;
} btc_buffer_t;

typedef struct btc_array_s {
  int64_t *items;
  size_t alloc;
  size_t length;
} btc_array_t;

typedef struct btc_vector_s {
  void **items;
  size_t alloc;
  size_t length;
} btc_vector_t;

typedef struct btc_stack_s {
  btc_buffer_t **items;
  size_t alloc;
  size_t length;
} btc_stack_t;

typedef struct btc_opcode_s {
  int value;
  const uint8_t *data;
  size_t length;
} btc_opcode_t;

typedef btc_buffer_t btc_script_t;

typedef struct btc_reader_s {
  const uint8_t *data;
  size_t length;
} btc_reader_t;

typedef btc_vector_t btc_writer_t;

typedef struct btc_outpoint_s {
  uint8_t hash[32];
  uint32_t index;
} btc_outpoint_t;

typedef struct btc_input_s {
  btc_outpoint_t prevout;
  btc_script_t script;
  uint32_t sequence;
  btc_stack_t witness;
} btc_input_t;

typedef struct btc_address_s {
  unsigned int type;
  unsigned int version;
  uint8_t hash[40];
  size_t length;
} btc_address_t;

typedef struct btc_output_s {
  int64_t value;
  btc_script_t script;
} btc_output_t;

typedef struct btc_program_s {
  unsigned int version;
  const uint8_t *data;
  size_t length;
} btc_program_t;

typedef struct btc_inpvec_s {
  btc_input_t **items;
  size_t alloc;
  size_t length;
} btc_inpvec_t;

typedef struct btc_outvec_s {
  btc_output_t **items;
  size_t alloc;
  size_t length;
} btc_outvec_t;

typedef struct btc_tx_s {
  uint8_t hash[32];
  uint8_t whash[32];
  uint32_t version;
  btc_inpvec_t inputs;
  btc_outvec_t outputs;
  uint32_t locktime;
  int _index;
  int _refs;
} btc_tx_t;

typedef struct btc_txvec_s {
  btc_tx_t **items;
  size_t alloc;
  size_t length;
} btc_txvec_t;

typedef struct btc_header_s {
  uint32_t version;
  uint8_t prev_block[32];
  uint8_t merkle_root[32];
  int64_t time;
  uint32_t bits;
  uint32_t nonce;
} btc_header_t;

typedef struct btc_block_s {
  btc_header_t header;
  btc_txvec_t txs;
  int _refs;
} btc_block_t;

typedef struct btc_entry_s {
  uint8_t hash[32];
  btc_header_t header;
  int32_t height;
  uint8_t chainwork[32];
  int32_t block_file;
  int32_t block_pos;
  int32_t undo_file;
  int32_t undo_pos;
  struct btc_entry_s *prev;
  struct btc_entry_s *next;
} btc_entry_t;

typedef struct btc_coin_s {
  uint32_t version;
  int32_t height;
  int coinbase : 8;
  int spent : 8;
  int safe : 8;
  int watch : 8;
  btc_output_t output;
  int _refs;
} btc_coin_t;

typedef struct btc_undo_s {
  btc_coin_t **items;
  size_t alloc;
  size_t length;
} btc_undo_t;

typedef struct btc_coins_s btc_coins_t;
typedef struct btc_view_s btc_view_t;

typedef struct btc_multikey_s {
  const uint8_t *data;
  size_t length;
} btc_multikey_t;

typedef struct btc_tx_cache_s {
  uint8_t prevouts[32];
  uint8_t sequences[32];
  uint8_t outputs[32];
  int has_prevouts;
  int has_sequences;
  int has_outputs;
} btc_tx_cache_t;

typedef struct btc_verify_error_s {
  uint8_t hash[32];
  unsigned int code;
  const char *reason;
  int score;
  int malleated;
} btc_verify_error_t;

typedef struct btc_network_s btc_network_t;
typedef struct btc_sha256_s btc__hash256_t;

typedef struct btc_netaddr_s {
  int64_t time;
  uint64_t services;
  uint8_t raw[16];
  int port;
} btc_netaddr_t;

typedef struct btc_bloom_s {
  uint8_t *data;
  size_t size;
  uint32_t n;
  uint32_t tweak;
  uint8_t update;
} btc_bloom_t;

typedef struct btc_filter_s {
  uint64_t *data;
  size_t length;
  int entries;
  int limit;
  int generation;
  int n;
  uint32_t tweak;
} btc_filter_t;

typedef struct btc_mpentry_s {
  const uint8_t *hash;
  const uint8_t *whash;
  btc_tx_t *tx;
  int32_t height;
  uint32_t size;
  uint32_t sigops;
  int64_t fee;
  int64_t delta_fee;
  int64_t time;
  uint8_t coinbase;
  uint8_t locks;
  int64_t desc_fee;
  int64_t desc_size;
} btc_mpentry_t;

/* https://github.com/satoshilabs/slips/blob/master/slip-0132.md */
enum btc_bip32_type {
  BTC_BIP32_STANDARD = 0, /*  xpub/xprv, m/44' */
  BTC_BIP32_NESTED_P2WPKH = 1, /* ypub/yprv, m/49' */
  BTC_BIP32_P2WPKH = 2, /* zpub/zprv, m/84' */
  BTC_BIP32_NESTED_P2WSH = 3, /* Ypub/Yprv */
  BTC_BIP32_P2WSH = 4 /* Zpub/Zprv */
};

typedef struct btc_hdnode_s {
  enum btc_bip32_type type;
  uint8_t depth;
  uint32_t parent;
  uint32_t index;
  uint8_t chain[32];
  uint8_t seckey[32];
  uint8_t pubkey[33];
} btc_hdnode_t;

typedef struct btc_mnemonic_s {
  uint16_t words[48];
  int length;
} btc_mnemonic_t;

enum btc_ipnet {
  BTC_IPNET_NONE,
  BTC_IPNET_IPV4,
  BTC_IPNET_IPV6,
  BTC_IPNET_ONION,
  BTC_IPNET_TEREDO
};

typedef struct _json_value btc_json_t;

/*
 * Maps (Key->Pointer)
 */

BTC_DEFINE_MAP_TYPES(btc_intmap, uint32_t, void *);
BTC_DEFINE_MAP_TYPES(btc_longmap, uint64_t, void *);
BTC_DEFINE_MAP_TYPES(btc_hashmap, uint8_t *, void *);
BTC_DEFINE_MAP_TYPES(btc_outmap, btc_outpoint_t *, void *);
/* BTC_DEFINE_MAP_TYPES(btc_invmap, btc_invitem_t *, void *); */
BTC_DEFINE_MAP_TYPES(btc_netmap, btc_netaddr_t *, void *);
BTC_DEFINE_MAP_TYPES(btc_addrmap, btc_address_t *, void *);

/*
 * Tables (Key->Integer)
 */

/* BTC_DEFINE_MAP_TYPES(btc_inttab, uint32_t, int64_t); */
BTC_DEFINE_MAP_TYPES(btc_longtab, uint64_t, int64_t);
BTC_DEFINE_MAP_TYPES(btc_hashtab, uint8_t *, int64_t);
/* BTC_DEFINE_MAP_TYPES(btc_outtab, btc_outpoint_t *, int64_t); */
/* BTC_DEFINE_MAP_TYPES(btc_invtab, btc_invitem_t *, int64_t); */
/* BTC_DEFINE_MAP_TYPES(btc_nettab, btc_netaddr_t *, uint64_t); */
/* BTC_DEFINE_MAP_TYPES(btc_addrtab, btc_address_t *, uint64_t); */

/*
 * Sets (Key)
 */

/* BTC_DEFINE_SET_TYPES(btc_intset, uint32_t); */
BTC_DEFINE_SET_TYPES(btc_longset, uint64_t);
BTC_DEFINE_SET_TYPES(btc_hashset, uint8_t *);
BTC_DEFINE_SET_TYPES(btc_outset, btc_outpoint_t *);
/* BTC_DEFINE_SET_TYPES(btc_invset, btc_invitem_t *); */
/* BTC_DEFINE_SET_TYPES(btc_netset, btc_netaddr_t *); */
BTC_DEFINE_SET_TYPES(btc_addrset, btc_address_t *);

#endif /* BTC_TYPES_H */
