
# Project Camouflage

The entire implementation of this project can be summarized in the following steps:
- **Step 1:** Encrypting the message entered by sender using DES encryption algorithm.
- **Step 2:** Dividing the cover image into K clusters using K-means clustering algorithm.
- **Step 3:** Using LSB technique to perform cluster wise steganography to hide cipher text in the image clusters.
- **Step 4:** Sending the stego-image clusters and the DES key to the receiver.
- **Step 5:** Extracting cipher text from the stego-images.
- **Step 6:** Decrypting the cipher text at the receiver's end using the key to obtain the original message.
<br> </br>
<br> </br>
![Flow chart for overall methology](https://lh5.googleusercontent.com/Qo2_dHTKihjns4J1iUx5ZmU6MBe7MlIuxiKpq_8z9RUdeOsO5jESz6SjYqbCkJoVWZeQ_RwVGppU1E9LOjYC0vMRtkgeQayyLWjRFq2AkAXlr-G2HN4PW34mkDWHBSn7t3aAIXmGz94)
