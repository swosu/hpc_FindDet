#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include <time.h>
#include <math.h>
#include "mpfr.h"
#define size 5000
int main(){
    double max;
    double tmp;
    double resDet;
    mpfr_t det;
    double mulTmp; 
    mpfr_t tmp1;
    mpfr_t tmp2;
    mpfr_t logAbsDet;
    int i,j,k,maxRow,sign;
    char f_name[50];
    double* buffer;
    mpfr_init(det);
    mpfr_init(tmp1);
    mpfr_init(tmp2);
    mpfr_init(logAbsDet);
    buffer = malloc(size*size*sizeof(double));
    sprintf(f_name,"m5000x5000.bin");
    FILE *datafile=fopen(f_name,"rb");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            *(buffer+size*i+j)=0; 
        }
    }
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            fread(buffer+(size*i+j),sizeof(double),1,datafile);
        }
    }
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("%lf\t",*(buffer+(size*i+j)));
        }
        printf("\n");
    }
    for(i=0;i<size-1;i++){
        maxRow = i;
        max = *(buffer+(size*i+i));
        for(j=i+1;j<size;j++){
            if(fabs(max)<fabs(*(buffer+size*j+i))){
                max = *(buffer+size*j+i);
                maxRow=j;
            }
        }
        if(fabs(max)<0.000001){
            resDet =0;
            printf("det=%e\n",resDet);
            exit(1);
        }
        if(maxRow!=i){
            sign++;
            for(j=i;j<size;j++){
                tmp = *(buffer + size*i+j);
                *(buffer+size*i+j) = *(buffer + size*maxRow+j);
                *(buffer+size*maxRow+j) = tmp;
            }
        }
        for(j=i+1;j<size;j++){
            mulTmp = *(buffer+size*j+i) / *(buffer+size*i+i);
            for(k=i;k<size;k++){

                *(buffer+size*j+k) = *(buffer+size*j+k)-*(buffer + size*i+k)*mulTmp;
            }
        }
    }
    mpfr_set_d(tmp1,1.0,GMP_RNDN);
    for(i=0;i<size;i++){
        mpfr_set_d(tmp2,*(buffer+size*i+i),GMP_RNDN);
        mpfr_mul(tmp1,tmp2,tmp1,GMP_RNDN);
    }
    if(sign%2==0){
        mpfr_set(det,tmp1,GMP_RNDN);
        resDet=mpfr_get_d(det,GMP_RNDN);
        mpfr_log10(logAbsDet,det,GMP_RNDN);
    }
    else{
        mpfr_neg(tmp1,tmp1,GMP_RNDN);
        mpfr_set(det,tmp1,GMP_RNDN);

        resDet=mpfr_get_d(det,GMP_RNDN);
        mpfr_log10(logAbsDet,det,GMP_RNDN);
    }

    //mpf_abs(absDet,det);
    //    mpf_set(logAbsDet, mpfr_log10(absDet));
   // mpfr_printf("det= %Fe\n",det);
    printf("det= %e\n",resDet);
    mpfr_printf("log(abs(det))= %Fe\n",logAbsDet);
    //gmp_printf("log(abs(det)= %e\n",logAbsDet);
    double END = clock();
    printf("%f\n",END/CLOCKS_PER_SEC);

    mpfr_clear(det);
    mpfr_clear(tmp1);
    mpfr_clear(tmp2);
    mpfr_clear(logAbsDet);
    free(buffer);
    return 0;
}
