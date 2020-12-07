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

## Sender's Side:
- **DES Encryption:** Secret Message is encrypted using the DES algorithm. Two files containing the key and the cipher text are generated.
<img src="https://lh5.googleusercontent.com/-sIpwRBrv1kW0GiTCdxcypWyU_zTolLjX_G2fT66Inprml6x8ybz9qkmAY2BF9rWilExNkxS2XRvpELBCGEGAG52ImrfvCddM_zgy7DhijRSQOIT1JzDxvZx7pAc8ZQ0zC-xoU6k" width="700" height="200"/>
<img src="https://lh5.googleusercontent.com/jyRje-vCKzfv2Od1pqIa9PLrL30DsUOLqm6dsYQgyAe_ddx02sNQ4nP5tpL7dNAWm_kzTSwRfCIMZnlCC5vwcYFSDyRZayc-flJ4fpCJEQtGRSWorH7k-n7XYIfD4ind-B2wOdGW" width="320" height="125"/>`

- **K-means Clustering:** Given image is clustered into k-segments using K-means algorithm. Clusters and file storing cluster information is generated.
<img src="https://lh4.googleusercontent.com/JjXZmoCBn0QZcuAxPJOwuIZHhIwTSZLebUWxhrxBMr7wapbG9zVbJCQY3COXS0BwB8npmfKIQAGTKby-BAC03p8tKQ07YsEYSO4wlQ8qidcOV1bSj0365ZQhH_Nc5uJQFSCpDOGT" width="700" height="400"/>
<img src="https://lh6.googleusercontent.com/KNzEtx-Epxh-sZ5a9W7NWEeDsP2Kp6No9slCvtNmBEyfYGxPqGbAs5Zg5uyGXv1EC90JXceI9v3hgrrAOm4rOl9n6pnPTWw_nexjKkHcciSwDdajRCK9r12XJxJVPonvTzN4wOtD" width="700" height="125"/>`

- **LSB Encryption:** The cipher text is hidden in the images created above using LSB steganography and new images are stored.
<img src="https://lh6.googleusercontent.com/_PkWPx_k9tPh0LFTOocbLghIc1DAY432ju9JR3zMM7Kw00_2WHhyJNk8XsKMoJUkvGu7gc3r8SlheJr8_rkPiIN43_DInLrO4M3gzD1NK8-RsKUf0sMcFh5xV6KWX_2NYUpS2odN" width="700" height="450"/>
<img src="https://lh4.googleusercontent.com/yMnjKNrG7aOkqg6gTpZdmtutIt1uYYR_3pn2AaB5GbNioajuzUShAfSQ3YDG41f05qmUpmxSnWdDCYgQkNmc4Ea0c-RTYZ6WUFQ98u6MF4jqqvYXCmFwenpyEKNYP5NQeTJBaDrZ" width="600" height="125"/>`

## Receiver's Side:
- **LSB Decryption:** Cipher is extracted from the stego-images and is stored in a file.
<img src="https://lh6.googleusercontent.com/pT6AveLUP6jw6fxozvrI1AuxVnG7ujakXOGDRx0m-bOSh-BF4DM542l1-eom-oMUD1eFKoWhXIKEs5_SUupncbVOEwNDlrwkIIMnGZEns0zvpB0iYFG98YeECyoWhKD7WOLEIzjc" width="700" height="175"/>`

- **DES Decryption:** The cipher text is then decrypted to obtain the secret message. File storing the key is used for decryption.
<img src="https://lh5.googleusercontent.com/u97aOd2Rg3lRkuKxOqj7K1Ahd35Dac4GJhWGTU6x1BcEwLWS6p3fTcH1Wzx-jP2G4jF4U8ZKJ3JGqF9AXMy4dn79oTZhJGN1XcjuMm0qVHw1jpWeesB967ioR47u2NmhcfqmIEYq" width="700" height="175"/>`
