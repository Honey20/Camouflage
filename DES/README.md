
# <center> DES Algorithm </center>

DES (**Data Encryption Standard**) is a symmetric-key block cipher which is an implementation of Feistel Cipher. DES works by using the same private key to encrypt and decrypt a message, so both the sender and the receiver must use the same private key. This project uses C language for implementation of DES algorithm.

Below flow chart describes the working of DES algorithm:
<br> </br>
**![](https://lh6.googleusercontent.com/XELDXGhg5QfViJi6vrDuoPMhmkY_lfWqFCjP_IbKVM58P7b3bv6jOGvbeDUi82IDRmTYaDKfG0isZKUtx7NANZIGMD5SDe7Ua0QoEuLR5Ae1TQtT-495inaRN-zCZ3OPCuFLwzxK)**
<br> </br>

Description of codes given above:
- **des.c:** This is the complete program for DES encryption and decryption.
- **des_encryption.c:** This is the program to encrypt the given text.
- **des_decryption.c:** This is the program to decrypt the given text.
- **round_key_generation.c:** This is the program to generate 16 round keys needed for encryption and decryption.



## Compile and Run
    gcc filename.c -lm
    ./a.out
