#include<stdio.h>
#include<stdlib.h>
#include "../headerFiles/types.h"

int landData(double purchasePrice[],double baseRents[])
{
    FILE *fp = fopen("csv/Rent.csv","r");
    if(fp==NULL)
    {
        printf("Failed to open file\n");
        exit(1);
    }

    char group[50];
    char property[50];

    //read and discard the header line
    char header[256];
    fgets(header, sizeof(header), fp);
    
    int row = 0;
    while(row<MAX_ROWS && fscanf(fp,"%49[^,],%49[^,],%lf,%lf\n",group,property,&purchasePrice[row],&baseRents[row])==4)
    {
        row++;
    }
    fclose(fp);
    return row;
}
