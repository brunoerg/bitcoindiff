use std::os::raw::c_char;
use std::ffi::CStr;
use std::str::Utf8Error;

use miniscript::Descriptor;
use miniscript::bitcoin::secp256k1;


unsafe fn c_str_to_str<'a>(input: *const c_char) -> Result<&'a str, Utf8Error> {
    CStr::from_ptr(input).to_str()
}

#[no_mangle]
pub unsafe extern "C" fn rust_miniscript_descriptor_parse(input: *const c_char) -> bool {
    let Ok(desc) = c_str_to_str(input) else {
        return false;
    };

    let secp = &secp256k1::Secp256k1::signing_only();
    match Descriptor::parse_descriptor(secp, desc) {
        Err(_) => false,
        Ok((d, _)) => d.sanity_check().is_ok()
    }
}