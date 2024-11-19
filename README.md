# bitcoinfuzz

Differential Fuzzing of Bitcoin implementations and libraries.
Note this project is a WIP and might be not stable.

# Installation

### rust-bitcoin
```bash
cd modules/rustbitcoin
cd rust_bitcoin_lib && cargo build --release --target=aarch64-apple-darwin
cd .. && make
export CXXFLAGS="$CXXFLAGS -DRUST_BITCOIN"
```

Change the `target` according to your architecture. You may need to modify the Makefile as well.

### rust-miniscript 

```bash
cd modules/rustminiscript
cd rust_miniscript_lib && cargo build --release --target=aarch64-apple-darwin
cd .. && make
export CXXFLAGS="$CXXFLAGS -DRUST_MINISCRIPT"
```

### mako

For the `script_eval` target, we recommend to get Mako from https://github.com/brunoerg/mako/tree/bitcoinfuzz since there are some checks that should be skipped for better fuzzing.

```bash
cd modules/mako
export MAKO_LIB_PATH="path/to/libmako.a"
make
```

### Bitcoin Core

```bash
cd modules/bitcoin
make
export CXXFLAGS="$CXXFLAGS -DBITCOIN_CORE"
```

Once the modules are compiled, you can compile bitcoinfuzz and execute it:
```bash
make
FUZZ=target_name ./bitcoinfuzz
```

-------------------------------------------
### Bugs/inconsistences/mismatches found by Bitcoinfuzz

- sipa/miniscript: https://github.com/sipa/miniscript/issues/140
- rust-miniscript: https://github.com/rust-bitcoin/rust-miniscript/issues/633
- rust-bitcoin: https://github.com/rust-bitcoin/rust-bitcoin/issues/2681
- btcd: https://github.com/btcsuite/btcd/issues/2195 (API mismatch with Bitcoin Core)
- Bitcoin Core: https://github.com/brunoerg/bitcoinfuzz/issues/34
- rust-miniscript: https://github.com/rust-bitcoin/rust-miniscript/issues/696 (not found but reproductive) 
- rust-miniscript: https://github.com/brunoerg/bitcoinfuzz/issues/39
- rust-bitcoin: https://github.com/rust-bitcoin/rust-bitcoin/issues/2891
- rust-bitcoin: https://github.com/rust-bitcoin/rust-bitcoin/issues/2879
- btcd: https://github.com/btcsuite/btcd/issues/2199
- rust-bitcoin: https://github.com/brunoerg/bitcoinfuzz/issues/57
- rust-bitcoin: CVE-2024-44073
