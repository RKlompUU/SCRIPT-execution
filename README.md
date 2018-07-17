Bitcoin Core - SCRIPT execution and verification
=====================================

This is a fork of the Bitcoin Core client, which has been slightly altered to provide an executable that directly applies the script execution machinery. Additionally, the execution machinery itself has been slightly modified to include verbose logging.

![Alt text](.imgs/intro.png?raw=true "Example")

### Installation
- Execute: ./setup.sh
- Execute: make scrpt-vrfy

### Usage

Execute the scrpt-vrfy executable: ./src/scrpt-vrfy [ \<input script\> | '0' ] \<output script\>

, where \<input script\> and \<output script\> point to files containing SCRIPT code in bytestring format (i.e. in the same format as they are present inside the transactions of Bitcoin's protocol). See the ins/ and outs/ directories for input and output script examples, respectively.

Optionally, the path to the input script can be omitted by assigning the first argument the character '0'. In this case the input script shall be entered manually through the process' standard input (std\_in). The script must be entered in bytestring format, press enter to conclude it.

### Description of output

![Alt text](.imgs/example.png?raw=true "Example")

The tool first prints the composed script (the input script concatenated with the output script) in hexadecimal bytestring format, and then starts evaluation.

After each processed command the resulting intermediate stack is printed. The head of the stack is shown at the bottom. Each entry has 3 columns, respectively: index number (with tail: 0, and head: size of the stack - 1), bytestring value, length of the bytestring value.

Finally, the verdict is printed, including the reason for failure if evaluation was not successful.
