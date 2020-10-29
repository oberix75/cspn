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

// Created by shadow

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

    unsigned int round3;
    
    unsigned int ciphertext;
    
    if (argc == 6)
    {
        Entry = plaintext ^ IV;
        Mod = Entry * 64;
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
        
        printf("This is your ciphertext : %i\n", ciphertext);
    }
    else
    {
        printf ("Usage : First Argument is the Plaintext, Second Argument is the Key, Third Argument is the Initialization vector, Fourth Argument is the Substitution Integer and Fifth Argument is the Permutation Integer\n");
    }
}
