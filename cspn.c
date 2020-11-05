/* 

   THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
   APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
   HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
   OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
   IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
   ALL NECESSARY SERVICING, REPAIR OR CORRECTION.


   cspn
   Copyright (C) 2020  shadow

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

contact : shadowPGP@protonmail.com

*/

#include <stdio.h>
#include <strings.h>

int k128[] = {
    0x9F, 0x58, 0x9F, 0x5C, 0xF6, 0x12, 0x2C, 0x32,
    0xB6, 0xBF, 0xEC, 0x2F, 0x2A, 0xE8, 0xC3, 0x5A,
};
int p128[] = {
    0xD4, 0x91, 0xDB, 0x16, 0xE7, 0xB1, 0xC3, 0x9E,
    0x86, 0xCB, 0x08, 0x6B, 0x78, 0x9F, 0x54, 0x19
};
int c128[] = {
    0x01, 0x9F, 0x98, 0x09, 0xDE, 0x17, 0x11, 0x85,
    0x8F, 0xAA, 0xC3, 0xA3, 0xBA, 0x20, 0xFB, 0xC3
};

int k192[] = {
    0x88, 0xB2, 0xB2, 0x70, 0x6B, 0x10, 0x5E, 0x36,
    0xB4, 0x46, 0xBB, 0x6D, 0x73, 0x1A, 0x1E, 0x88,
    0xEF, 0xA7, 0x1F, 0x78, 0x89, 0x65, 0xBD, 0x44
};
int p192[] = {
    0x39, 0xDA, 0x69, 0xD6, 0xBA, 0x49, 0x97, 0xD5,
    0x85, 0xB6, 0xDC, 0x07, 0x3C, 0xA3, 0x41, 0xB2
};
int c192[] = {
    0x18, 0x2B, 0x02, 0xD8, 0x14, 0x97, 0xEA, 0x45,
    0xF9, 0xDA, 0xAC, 0xDC, 0x29, 0x19, 0x3A, 0x65
};
int k256[] = {
    0xD4, 0x3B, 0xB7, 0x55, 0x6E, 0xA3, 0x2E, 0x46,
    0xF2, 0xA2, 0x82, 0xB7, 0xD4, 0x5B, 0x4E, 0x0D,
    0x57, 0xFF, 0x73, 0x9D, 0x4D, 0xC9, 0x2C, 0x1B,
    0xD7, 0xFC, 0x01, 0x70, 0x0C, 0xC8, 0x21, 0x6F
};
int p256[] = {
    0x90, 0xAF, 0xE9, 0x1B, 0xB2, 0x88, 0x54, 0x4F,
    0x2C, 0x32, 0xDC, 0x23, 0x9B, 0x26, 0x35, 0xE6
};
int c256[] = {
    0x6C, 0xB4, 0x56, 0x1C, 0x40, 0xBF, 0x0A, 0x97,
    0x05, 0x93, 0x1C, 0xB6, 0xD4, 0x08, 0xE7, 0xFA
};

void main(int argc, int argv[])
{
    int i;

    int plaintext = argv[1];
    int key = argv[2];
    int IV = argv[3];
    int SubBits = -argv[4];
    int PerBits = argv[5];

    unsigned int Entry;
    unsigned int Mod;

    unsigned int cipher1;
    unsigned int Sbox1;
    unsigned int Pbox1;
    unsigned int cipher2;
    unsigned int Sbox2;
    unsigned int Pbox2;
    unsigned int cipher3;
    unsigned int AND;

    unsigned int round3;

    unsigned int ciphertext;

    if (argc == 6)
    {
        for( i=0; i<256; i++ ) 
        {
            Entry = plaintext ^ IV;
            Mod = Entry * 128;
            // Modulo for MDS
            // Fisrt XOR
            cipher1 = Mod ^ key;
            Sbox1 = ~(cipher1, SubBits);
            Pbox1 = Sbox1 & PerBits;
            // First Round
            cipher2 = Pbox1 ^ key;
            Sbox2 = ~(cipher2, SubBits);
            Pbox2 = Sbox2 & PerBits;
            //Second Round
            cipher3 = Pbox2 ^ key;
            AND = cipher3 & key;
            // an AND
            round3 = AND ^ key;
            // Third Round
            ciphertext = (round3 % 64) ^ key;
            // Ciphertext and MDS

            /* 
            TODO : CBC for Back to block, and logical sequence in MDS.
            */
        }

        printf("This is your ciphertext : %i\n", ciphertext);
    }
    else
    {
        printf ("Usage : First Argument is the Plaintext, Second Argument is the Key, Third Argument is the Initialization vector, Fourth Argument is the Substitution Integer and Fifth Argument is the Permutation Integer\n");
    }
}
