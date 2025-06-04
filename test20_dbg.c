#include "test20_dbg.h"
#include <stdlib.h>
#include <stdio.h>


void test_debug(){
    debug("I have Brown Hair.");

    debug("I am %d years old.",37);
}


int main(){

    test_debug();

    return 0;
}

