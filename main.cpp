#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "classes/game_field.h"
#include "classes/loader_and_checker.h"
using namespace std;

int main(){
    Game_field i_love_trains(false);
    Load("name")(i_love_trains);
    Check()(i_love_trains);
    while (true){
        this_thread::sleep_for(chrono::microseconds(2000));
        i_love_trains.simulate();
    }
}