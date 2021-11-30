## RSA-Cracker

Given a public key pair, this program finds the decryption key and decodes an inputted message

#Input
The first line will have two values, e,n which represent the public key pair needed to decrypt the code.
The second line will have one value m which is the length of the encoded message.
The next m integers will represent the encoded message.

#Output
p, q, phi(n), and d.
The decoded message in integers.
The decoded message in characters

Note: Assuming theres an offset with the integers to characters, that value can be edited on line 139
