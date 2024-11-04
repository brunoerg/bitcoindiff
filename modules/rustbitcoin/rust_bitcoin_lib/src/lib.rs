use std::slice;
use std::os::raw::c_char;
use std::ffi::CString;

use bitcoin::Block;
use bitcoin::consensus::{deserialize_partial, encode};


/// Creates a C string from a Rust str.
///
/// # Safety
/// The caller must ensure that this memory is deallocated after the C string
/// is no longer used. `into_raw` consumes the string and leaks the memory,
/// making this allocation invisible to Rust's memory management.
///
/// This function panics if the input contains an internal null byte.
unsafe fn str_to_c_string(input: &str) -> *mut c_char {
    CString::new(input).unwrap().into_raw()
}

#[no_mangle]
pub unsafe extern "C" fn rust_bitcoin_des_block(data: *const u8, len: usize) -> *mut c_char {
    let data_slice = std::slice::from_raw_parts(data, len);
    let res = deserialize_partial::<Block>(data_slice);

    match res {
        Ok(block) => str_to_c_string(&block.0.block_hash().to_string()),
        Err(err) => {
            if err.to_string().starts_with("unsupported segwit version") {
                return str_to_c_string("unsupported segwit version")
            }
            str_to_c_string("")
        },
    }
}

#[no_mangle]
pub unsafe extern "C" fn rust_bitcoin_script(data: *const u8, len: usize) -> bool {
    // Safety: Ensure that the data pointer is valid for the given length
    let data_slice = slice::from_raw_parts(data, len);

    let script: Result<(bitcoin::script::ScriptBuf, usize), encode::Error> = encode::deserialize_partial(data_slice);
    match script {
        Err(_) => false,
        Ok(s) => {
            if s.0.is_op_return() || s.0.len() > 10_000 { 
                return false
            }
            true
        }
    }
}
