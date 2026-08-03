#include <stdio.h>


typedef struct {
    char name[50];
    double purchasePrice;
    int id;
}ddd;



int main()
{
    ddd arr[4];
    arr[0] = (ddd){"dineth",50.50,3};
    arr[1] = (ddd){.name = "Dineth", .id=5};
    printf("%s",arr[0].name);
    printf("%s",arr[1].name);

    return 0;
}
