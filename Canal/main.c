#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Structs/BoatList.h"
#include "Setup.h"
#include "Control.h"
#include "Structs/Boat.h"
#include "Structs/NodeList.h"
#include "Structs/Canal.h"
#include "Passage.h"

int main() {
    struct Canal canal = setup(2,'T', 2, 2, 2, 2);

    int *a = (int *)malloc(sizeof(int));
    *a = 1;
    printf("Valor de a: %d\n", *a);
    
    Tica(canal.right, canal.left, canal.nodes);
    
    return 0;
}
