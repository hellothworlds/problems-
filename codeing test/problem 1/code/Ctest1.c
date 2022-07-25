
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*This is the top level C program that calls the intermediate Fortran code Lasso, and writes the data retrieved from the legacy Fortran code
to a pair of text files named Iondata3-3-2021.txt, and Iondata3-4-2021.txt, */

//this is the declaration required in order to pair a C file to a fortran program, 
extern void lasso_(int*, int*, float*, float*, int*, int*, float*, float*, float*, float*, float[1000][20], float[50]);


void main() {
    //declaration of variables for Fotran program lasso
    int JMAG, IYYYY, MMDD;//year in standard form, month day in days since start of 
    float ALATI, ALONG, DHOUR, HEIBEG, HEIEND, HEISTEP;
    float OUTF[1000][20];
    float OARR[100];
    float times[1000];
    int JF[50];



    //initialization for logic array
    for (int i = 0; i < 49; i++) {
        JF[i] = 1;
    }
    /*this selects a number of logical outputs to try and mimic the behavior of the online web function
    Due to mismatching index(In Fortan an array starts at 1, in C it starts at zero) the indices are one more then expected otherwise*/

    JF[3] = 0;  
    JF[4] = 0;
    JF[5] = 0;
    JF[20] = 0;
    JF[22] = 0;
    JF[23] = 0;
    JF[27] = 0;
    JF[28] = 0;
    JF[29] = 0;
    JF[32] = 0;
    JF[34] = 0;
    JF[38] = 0;
    JF[39] = 0;
    JF[46] = 0;



    ALATI = 37.8;
    ALONG = 75.4;

    JMAG = 0;
    IYYYY = 2021;
    MMDD = -62;
    DHOUR = 11.0;

    HEIBEG = 200.0;
    HEIEND = 1500.0;
    HEISTEP = 2.0;
    int lenth = (int)floor((HEIEND - HEISTEP) / HEISTEP);
    printf("%d", lenth);
    //Calling of the Fortran wrapper program lasso, and returns an array of out puts, in OUtF including Ion density
    lasso_(JF, &JMAG, &ALATI, &ALONG, &IYYYY, &MMDD, &DHOUR, &HEIBEG, &HEIEND, &HEISTEP, OUTF, OARR);



    //this is the declaration that opens and writes the data into a first file data Iondata3-3-2021.txt
    int i = 0;
    float time = 0;
    float reader = 0;
    FILE* fptr;
    fptr = fopen("Iondata3_3_2021.txt", "w");

    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    //writes height and ion density to the file 
    while (i< lenth)
    {
        if (OUTF[i][0]!=-1)
        {
            reader = OUTF[i][0];
            fprintf(fptr, "%f ", reader);
            time = HEIBEG + i * HEISTEP;
            fprintf(fptr, "%f\n", time);
        }
        i = i + 1;
    }
 
    fclose(fptr);

    /*This is the variable defintion for the second time frame.*/
    ALATI = 37.8;
    ALONG = 75.4;

    JMAG = 0;
    IYYYY = 2021;
    MMDD = -63;
    DHOUR = 23.0;
    HEIBEG = 200.0;
    HEIEND = 1500.0;
    HEISTEP = 2.0;
    lenth =(int)floor((HEIEND - HEISTEP) / HEISTEP);


    //Calling of the Fortran wrapper program lasso, and returns an array of out puts, in OUtF including Ion density
    lasso_(JF, &JMAG, &ALATI, &ALONG, &IYYYY, &MMDD, &DHOUR, &HEIBEG, &HEIEND, &HEISTEP, OUTF, OARR);



    //this is the declaration that opens and writes the data into the second data file Iondata3-4-2021.txt
    i = 0;
    time = 0;
    reader = 0;
    FILE* fptr2;
    fptr2 = fopen("Iondata3_4_2021.txt", "w");

    if (fptr2 == NULL)//checks for memory allocation errors  
    {
        printf("Error!");
        exit(1);
    }
    //writes height and ion density to the file 
    while (i < lenth)
    {
        if (OUTF[i][0] != -1)
        {
            reader = OUTF[i][0];
            fprintf(fptr2, "%f ", reader);
            time = HEIBEG + i * HEISTEP;
            fprintf(fptr2, "%f\n ", time);
        }
        i = i + 1;
    }

    fclose(fptr2);
    return;
}