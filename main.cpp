#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "classes/game_field.h"
#include "classes/loader_and_checker.h"
using namespace std;

int main(){
    Game_field i_love_trains;
    if(Load().load_game_field("name",i_love_trains) && Check().check_game_field(i_love_trains))
    while (!i_love_trains.empty()){
        //this_thread::sleep_for(chrono::microseconds(2000));
        i_love_trains.simulate();
    }
}