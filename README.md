# immortal-stack
Immortal stack for ISP RAS 
## Description
The stack implementation with "generics", a verification, a canaries checking and a hashing checking

## Installing
```bash
git clone https://github.com/vvdvortsova/immortal-stack.git
```
## Structure
- Source project 
    - src/
- Test project
    - test/
- Log file
    - stack_logs.txt
## Run
By default, the file stack.h has hash and canary protection enabled
```bash
#define CANARY_CHECK/*!< defines canary defence*/
#define HASH_CHECK/*!< defines hash defence*/
```
To use stack with only simple verification, commit the following "defines"
```bash
//#define CANARY_CHECK/*!< defines canary defence*/
//#define HASH_CHECK/*!< defines hash defence*/
```
To use stack with only simple verification and canary, commit the following "define"
```bash
//#define HASH_CHECK/*!< defines hash defence*/
```
To run tests 
```bash
cmake .
make
./immortal_stack
```
## Documentation
You can watch documentation by opening
```docs/html/index.html ``` in browser.

## OS
 KUbuntu 18.04

