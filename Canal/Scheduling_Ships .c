#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Structs/Boat.h"
#include "Structs/Node.h"
#include "Structs/NodeList.h"
#include "Structs/Canal.h"
#include "Structs/BoatFactory.h"
#include "Structs/NodeFactory.h"
#include "Structs/BoatList.h"

sem_t *sem;

