#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define size 5000
int maxRow;
double max;
double tmp;
double tmp1;
int sign = 0;
double det;
double logAbsDet;
char f_name[50];
double START,END;
int consK=10;
double detK;
int main(){
    int i,j,k;
    double* matrix;
  //  printf("n= \n");
    //scanf("%d",&size);
    matrix = malloc(size*size*sizeof(double));
    sprintf(f_name,"m5000x5000.bin");
    FILE *datafile=fopen(f_name,"rb");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            *(matrix+size*i+j)=0;
           // printf("%.1f\t",*(matrix+(size*i+j)));
        }
        //printf("\n");
    }
    for(i=0;i<size;i++){   
        for(j=0;j<size;j++){
          // printf("Please enter the number:");
            fread(matrix+(size*i+j),sizeof(double),1,datafile);
            //scanf("%lf",(matrix+(size*i+j)));
        //    *(matrix+ (size*i+j)) = *(matrix+(size*i+j))*10;
        }
        
    }
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("%lf\t",*(matrix + (size*i+j)));
        }
        printf("\n");
    }
    for(i=0;i<size-1;i++){
        maxRow = i;
        max = *(matrix+size*i+i);
        for(j=i+1;j<size;j++){
            if(fabs(max)<fabs(*(matrix+size*j+i))){
                max = *(matrix+size*j+i);
                maxRow=j;
            }
        }
        if(fabs(max)<0.000001){
            det =0;
            printf("det=%e\n",det);
            exit(1);
        }
        if(maxRow!=i){
            sign++;
            for(j=i;j<size;j++){
                tmp = *(matrix + size*i+j);
                *(matrix+size*i+j) = *(matrix + size*maxRow+j);
                *(matrix+size*maxRow+j) = tmp;
        
            }
        }
        for(j=i+1;j<size;j++){
            tmp1 = *(matrix+size*j+i) / *(matrix+size*i+i);
            for(k=i;k<size;k++){
                *(matrix+size*j+k) = *(matrix+size*j+k)-*(matrix + size*i+k)*tmp1;
            }
        }
    }
    tmp1 =1;
    for(i=0;i<size;i++){
        tmp1*=*(matrix +size*i+i);
     //   printf("%.1f\n",tmp1);
    }
    if(sign%2==0){
       detK=tmp1;
       det = tmp1;
       // det = tmp1/pow(10,3000);
  //      printf("1%.1f\n",tmp1);
    }
    else{
        detK=-tmp1;
        det=-tmp1;
        // det = -tmp1/pow(10,3000);
    //    printf("2%.1f\n",-tmp1);
    }
    logAbsDet=log10(fabs(det));
    //logAbsDet=log10(fabs(detK))-3000;
    printf("det= %e\n",det);
    printf("log(abs(det)= %e\n",logAbsDet);
    END=clock();
    printf("%f",END/CLOCKS_PER_SEC);
    free(matrix);
    return 0;
}

