Bitcoin Core - SCRIPT execution and verification
=====================================

This is a fork of the Bitcoin Core client, which has been slightly altered to provide an executable that directly applies the script execution machinery.

### Installation
- Execute: ./setup.sh
- Execute: make scrpt-vrfy

### Usage

Execute the scrpt-vrfy executable: ./scrpt-vrfy \<[input script | '0']\> \<output script\>

, where \<input script\> and \<output script\> point to files containing SCRIPT code in bytestring format. See the ins/ and outs/ directories for input and output script examples, respectively.

Optionally, the path to the input script can be omitted by assigning the first argument the character '0'. In this case the input script can be entered manually through the process' standard input (std\_in).
