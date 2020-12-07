# Project Camouflage
In this project, we use DES encryption to encrypt the text message and pixels of the cover image are clustered using the K-means clustering algorithm. Cluster-wise steganography is then performed and the stego-image, along with the DES key is transferred. On the receiver’s end, the ciphertext is extracted from the cover images and then decrypted using DES algorithm to obtain the message.

The entire implementation of this project can be summarized in the following steps:
- **Step 1:** Encrypting the message entered by sender using DES encryption algorithm.
- **Step 2:** Dividing the cover image into K clusters using K-means clustering algorithm.
- **Step 3:** Using LSB technique to perform cluster wise steganography to hide cipher text in the image clusters.
- **Step 4:** Sending the stego-image clusters and the DES key to the receiver.
- **Step 5:** Extracting cipher text from the stego-images.
- **Step 6:** Decrypting the cipher text at the receiver's end using the key to obtain the original message.

<br> </br>
![Flow chart for overall methology](https://lh5.googleusercontent.com/Qo2_dHTKihjns4J1iUx5ZmU6MBe7MlIuxiKpq_8z9RUdeOsO5jESz6SjYqbCkJoVWZeQ_RwVGppU1E9LOjYC0vMRtkgeQayyLWjRFq2AkAXlr-G2HN4PW34mkDWHBSn7t3aAIXmGz94)

<br> </br>
Below given data flow diagram describes the use of files and information through the entire project.
<br> </br>
![DFD](https://lh4.googleusercontent.com/_pgW1jmxvUswDgNPVa3QIpMH2Ad_obtueTixBgtfi-CtATIOBuG5Ov6KOnKTpcWmffCPGoKvBYR_nvLgu_DIwNYkoLXN8rVquZ1RPxcj1MV-n9cpopnjMEqZ4gp-uUGZ1NDCqCo4)
