use std::slice;
use std::os::raw::c_char;
use std::ffi::{CStr, CString};
use std::str::{FromStr, Utf8Error};

use bitcoin::consensus::encode;

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
