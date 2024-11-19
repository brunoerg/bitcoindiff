use std::os::raw::c_char;
use std::ffi::CStr;
use std::str::{FromStr, Utf8Error};

use miniscript::DescriptorPublicKey;

/// Creates a Rust str from a C string.
///
/// # Safety
/// The caller must ensure that the pointer points to a zero-terminated C string.
/// If the pointer is null, this function will panic. A non-zero terminated string
/// will trigger undefined behavior.
unsafe fn c_str_to_str<'a>(input: *const c_char) -> Result<&'a str, Utf8Error> {
    CStr::from_ptr(input).to_str()
}

#[no_mangle]
pub unsafe extern "C" fn rust_miniscript_descriptor_parse(input: *const c_char) -> bool {
    let Ok(desc) = c_str_to_str(input) else {
        return false;
    };

    match DescriptorPublicKey::from_str(desc) {
        Err(_) => false,
        Ok(_) => true,
    }
}