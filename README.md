# XOR

A simple command-line utility for encoding, decoding, and verifying strings and files using a custom 64-bit hash mechanism.

---

## Usage

```sh
xor [OPTION] [SUB-OPTION] [FILE|STRING]
```

---

## Options

- `-s` | `--string`  
  Switches to string based operation

- `-f` | `--file`  
  Switches to file based operation

---

## Sub-options

- `-e` | `--encode`  
  Encodes the given string and passes the encoded hash as output

- `-d` | `--decode`  
  Decodes the given encoded-string and passes the decoded string as output

- `-f` | `--file`  
  Generates a 64bit hash for file verification

---

## To Build:
```sh
make xor KEY=<any 8-Bit unsigned char value here, ex: 0xAB>
```

## Notes
- The encoded value depends on the key.
- This thing is not safe to use btw, consider using sha512sum or md5sum for file verification.
- This thing is kinda like how base64/32 works. as i mentioned b4, this thing is not safe to use for file verification!

---