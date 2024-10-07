#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "Flow.h"
#include <semaphore.h>
#include "Structs/Boat.h"
#include "Structs/Node.h"
#include "Structs/NodeList.h"
#include "Structs/Canal.h"
#include "Structs/BoatFactory.h"
#include "Structs/NodeFactory.h"0
#include "Structs/BoatList.h"

void main() {
   struct Canal canal;
   canal = setup(5, 'T', 2, 2, 2, 2);
   printf(canal.control);

}