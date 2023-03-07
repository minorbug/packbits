# PackBits for C++

This is a simple [PackBits](https://en.wikipedia.org/wiki/PackBits) implementation (the one Apple used for compressing MacPaint files, however this can be used on any byte vector).

## Example

```C++
const vector<uint8_t> unpackedBytes = {
    0xAA, 0xAA, 0xAA, 0x80, 0x00, 0x2A, 0xAA, 0xAA, 0xAA, 0xAA, 0x80, 0x00, 0x2A, 0x22, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
};
vector<uint8_t> packedBytes = packbits::pack(unpackedBytes); // Returns '0xFE, 0xAA, 0x02, 0x80, 0x00, 0x2A, 0xFD, 0xAA, 0x03, 0x80, 0x00, 0x2A, 0x22, 0xF7, 0xAA'
```


## Running tests (both of them)

### Using `clang`:
```
clang++ -fcolor-diagnostics -fansi-escape-codes -std=c++11 -g packbits/src/test_packbits.cpp -o test_packbits

./test_packbits
```