#include <stdio.h>

int main(){
    int numero=200;
    int ptrnumero;
    ptrnumero = &numero ;
    ptrnumero=350;
printf("El apuntador esta apuntando a : %d\n",numero);
printf("%d\n",ptrnumero);

    return 0;
}
