#include <stdio.h>
#include <stdlib.h>
#define MAX_ROWS 22

typedef struct {
    char name[50];
    double purchasePrice;
    int id;
}ddd;



int main()
{
    int purchasePrice[MAX_ROWS];
    int baseRents[MAX_ROWS];
    FILE *fp = fopen("Rent.csv","r");
    if(fp!=NULL)
    {
        printf("File open sucess\n");
    }
    else
    {
        printf("Failed to open file\n");
        exit(0);
    }

    char group[50];
    char property[50];

    //read and discard the header line
    char header[256];
    fgets(header, sizeof(header), fp);
    
    int row = 0;
    while(row<MAX_ROWS && fscanf(fp,"%49[^,],%49[^,],%d,%d\n",group,property,&purchasePrice[row],&baseRents[row])==4)
    {
        row++;
    }
    // ddd arr[4];
    // arr[0] = (ddd){"dineth",50.50,3};
    // arr[1] = (ddd){.name = "Dineth", .id=5};
    // printf("%s",arr[0].name);
    // printf("%s",arr[1].name);

    printf("\n----successfully sored data----\n");
    for (int i = 0; i < row; i++)
    {
        printf("%d. Purchase Price: %d | Base Rent: %d\n",i,purchasePrice[i],baseRents[i]);
    }
    
    fclose(fp);
    return 0;
}
