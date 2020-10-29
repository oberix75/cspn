#include <stdio.h>

void main(int argc, int argv[])
{
    int plaintext = argv[1];
    int key = argv[2];
    int IV = argv[3];
    int SubBits = -argv[4];
    int PerBits = argv[5];
    
    unsigned int Entry;
    
    unsigned int cipher1;
    unsigned int Sbox1;
    unsigned int Pbox1;
    unsigned int cipher2;
    unsigned int Sbox2;
    unsigned int Pbox2;
    unsigned int cipher3;
    unsigned int AND;
    
    unsigned int ciphertext;
    
    if (argc == 6)
    {
        Entry = plaintext ^ IV;
        // Fisrt XOR
        cipher1 = Entry ^ key;
        Sbox1 = ~(cipher1, SubBits);
        Pbox1 = Sbox1 >> PerBits;
        // First Round
        cipher2 = Pbox1 ^ key;
        Sbox2 = ~(cipher2, SubBits);
        Pbox2 = Sbox2 >> PerBits;
        //Second Round
        cipher3 = Pbox2 ^ key;
        AND = cipher3 & key;
        // MDS
        ciphertext = AND ^ key;
        // Ciphertext
        
        printf("This is your ciphertext with SPN : %i", ciphertext);
    }
    else
    {
        printf ("Usage : First Argument is the Plaintext, Second Argument is the Key, Third Argument is the Initialization vector, Fourth Argument is the Substitution Integer and Fifth Argument is the Permutation Integer");
    }
}
