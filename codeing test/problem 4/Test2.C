#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Declaration of the comparison sorter function required for qsort
This function takes float arrays a and b, and returns -1 1 or 0 if t the first element of a is greater than less then or equal to the first element of b*/
static int cmprow0(const void* a, const void* b)
{
    const double* const ia = a, * const ib = b; //variable Declaration
    if (ia[0] < ib[0]) return(-1);//comparison
    if (ia[0] > ib[0]) return(1);
    if (ia[0] == ib[0]) return(0);
}
/*Declaration of the bubble sort used to calculate the median in mediancomb.
It takes a integer n and a float array x, and sorts it from smallest to largest
Consider replacing with qsort for larger, finer data sets, with greater applied smoothing*/
void bubble(int n, float x[])
{
    int i, j;
    float temp;//storage variable to deal with shifting values

    for (i = 0; i < n - 1; ++i)
    {
        for (j = n - 1; j > i; --j)
            if (x[j - 1] > x[j])
            {
                temp = x[j - 1];
                x[j - 1] = x[j];
                x[j] = temp;
            }
    }
    return;
}
/*Declaration of the median function, mediancomb.
Works on three float inputs, returns the median point
Consider for stronger smoothing, replacing bubble sort with qsort*/
float mediancomb(float a, float b, float c)
{
    float d = 0;
    float basket[3];
    int j = 1;
    basket[0] = a;
    basket[1] = b;
    basket[2] = c;
    bubble(3,basket);

    //printf("%f ", basket[1]);
    d = basket[1];
    return(d);
}
/*Declaration of the main function
This routine extracts from the given data file, times, and two data points foF2 and fmF2.
Then orders the data by time, and preforms a median smoothing, on foF2 and fmF2*/
int main()
{
    //declaration of variables
       int year;
       int min;
       int sec;
       int day;  
       int hour;
       char z;
       int wilength = 496;//length of file array. consider changing it to read in file length later. and use malloc instead of a hard-wired array size
       double wilma[wilength][3];
       double *foF2 = 0;
       FILE  *fp;

       fp = fopen("AU930_ROAM.txt", "r");
       if (NULL == fp) {
        printf("file can't be opened \n");
         }
       char* buffer;
       size_t bufsize = 33;
       size_t characters;
       fseek(fp, 0, SEEK_SET);//starts at the start of the file
       fscanf(fp, "%*[^\n]\n");
       fscanf(fp, "%*[^\n]\n");//skips the first two lines
       int ii = 0;
       double a[wilength];
       double b[wilength];
       double time[wilength];
       double dum[wilength];
       int count = 1;
       while (ii < wilength)
       {

           buffer = (char*)malloc(bufsize * sizeof(char));
           if (buffer == NULL)
           {
               //printf("Unable to allocate buffer for %d\n ",ii+1);
           }
           if (buffer!=NULL)
           {
               //printf("Able to allocate buffer for %d\n", ii+1);
           }
           characters = getline(&buffer, &bufsize, fp);

           char* pch;
           pch = strtok(buffer, " (),:");//this command spits up the string by spaces (), and :
           count = 1;
           while (pch != NULL)
           {
               if (count == 2)//copies the day of the year
               {
                   
                    day= strtod(pch, NULL);
               }
               if (count == 3)//copies the hour
               {

                   hour = strtod(pch, NULL);
               }
               if (count == 4)//copies the min
               {

                   min = strtod(pch, NULL);
               }
               if (count == 5)//copies the second
               {

                   sec = strtod(pch, NULL);
               }
               pch = strtok(NULL, " (),:");
               count = count + 1;
               if (count == 7)//copies FoF2
               {
                   a[ii] = strtod(pch, NULL);
               }
               if (count == 12)//copies FmF2
               {
                   b[ii] = strtod(pch, NULL);
               }
           }
           dum[ii] = 24 * 60 * 60 * day + 60 * 60 * hour + 60 * min + sec;
           wilma[ii][0] = dum[ii];
           wilma[ii][1] = a[ii];
           wilma[ii][2] = b[ii];
           ii++;
       };
       qsort(wilma, sizeof wilma / sizeof * wilma, sizeof * wilma, cmprow0); //orders the list by time
        //this is the initialization of the median smoothing prosses it checks the adjacent entries
       int jj=0;
       int kk = 1;
       float van[wilength][3];
       float aa = wilma[jj - 1][kk];
       float bb = wilma[jj][kk];
       float cc = wilma[jj + 1][kk];
       while (jj < wilength)
       {
           van[jj][0] = wilma[jj][0];
           kk = 1;
           while (kk < 3)
           {
               aa = wilma[jj - 1][kk];
               bb = wilma[jj][kk];
               cc = wilma[jj + 1][kk];
               van[jj][kk] = mediancomb(aa, bb, cc);
               kk = kk + 1;
           }
           jj = jj + 1;
       }
       int i = 0;
       float reader = 0;
       FILE* fptr2;
       fptr2 = fopen("sorterd Au930_roam.txt", "w");

       if (fptr2 == NULL)//checks for memory allocation errors  
       {
           printf("Error!");
           exit(1);
       }
       //writes height and ion density to the file 
       while (i < wilength)
       {
           reader = van[i][0];
           fprintf(fptr2, "%lf ", reader);
           reader = van[i][1];
           fprintf(fptr2, "%lf ", reader);
           reader = van[i][2];
           fprintf(fptr2, "%lf \n ", reader);
           i = i + 1;
       }
       return(0);
}