#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Structs/Boat.h"
#include "Structs/Node.h"
#include "Structs/NodeList.h"

void Equity(int W, char direction) {
    if(direction == 'R') {
        if (list != NULL) {
            //Inicia Semaforo
            int temp = 0;
            for(int i = 0; i < W; i++) {
                //Crea hilos-barcos
            }
            //if ( W semaforo == W){Equity(W, 'L')}
        }else {
            Equity(W, 'L');
        }
    }
    else if(direction == 'L') {
        if(list != NULL) {
            //Inicia Semaforo
            int temp = 0;
            for(int i = 0; i < W; i++) {
                //Crea hilos-barcos
            }
            //if ( W semaforo == W){Equity(W, 'R')}
        }else {
            Equity(W, 'R');
        }
    }
}