use std::os::raw::c_char;
use std::ffi::CStr;
use std::str::{FromStr, Utf8Error};

use miniscript::{policy, Miniscript, Segwitv0};
use miniscript::policy::Liftable;

type Script = Miniscript<String, Segwitv0>;
type Policy = policy::Concrete<miniscript::bitcoin::PublicKey>;

unsafe fn c_str_to_str<'a>(input: *const c_char) -> Result<&'a str, Utf8Error> {
    CStr::from_ptr(input).to_str()
}

#[no_mangle]
pub unsafe extern "C" fn rust_miniscript_descriptor_parse(input: *const c_char) -> bool {
    let Ok(desc) = c_str_to_str(input) else {
        return false;
    };

    match Policy::from_str(desc) {
        Err(_) => false,
        Ok(pol) => {
            // Use compile like in the fuzz target
            match pol.compile::<Segwitv0>() {
                Ok(_) => true,
                Err(_) => false,
            }
        }
    }
}