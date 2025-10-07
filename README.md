# A C++ implementation of a Feistel network.

## Note:

Currently, the key must be an 8-bit integer (`std::uint8_t`) and the plaintext must be a 16-bit integer (`std::uint16_t`).  
I am working on modifying the implementation to allow for plaintext of arbitrary size.  

I am also working on modifying it to be a template class, with the substitution function as a template argument.  
