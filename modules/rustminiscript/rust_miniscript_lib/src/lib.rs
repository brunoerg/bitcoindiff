use std::os::raw::c_char;
use std::ffi::CStr;
use std::str::{FromStr, Utf8Error};

use miniscript::{policy, Miniscript, Segwitv0, Tap, Descriptor};
use miniscript::policy::Liftable;


unsafe fn c_str_to_str<'a>(input: *const c_char) -> Result<&'a str, Utf8Error> {
    CStr::from_ptr(input).to_str()
}

#[no_mangle]
pub unsafe extern "C" fn rust_miniscript_descriptor_parse(input: *const c_char) -> bool {
    let Ok(desc) = c_str_to_str(input) else {
        return false;
    };

    match Descriptor::<miniscript::bitcoin::PublicKey>::from_str(desc) {
        Err(_) => {
            match Descriptor::<miniscript::bitcoin::XOnlyPublicKey>::from_str(desc) {
                Err(_) => {
                    false
                },
                Ok(d) => {
                    return d.sanity_check().is_ok();
                }
            }
        },
        Ok(d) => {
            return d.sanity_check().is_ok();
        }
    }
}