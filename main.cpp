#include <chrono>
#include <thread>
#include "classes/game_field.h"
#include "classes/Loader.h"
#include "classes/Checker.h"
#include "classes/Error.h"
using namespace std;
int main(){
    try {
        Game_field i_love_trains;
        Load().load_game_field("name", i_love_trains, 1);
        Check().check_game_field(i_love_trains);
            while (!i_love_trains.empty()) {
                //this_thread::sleep_for(chrono::microseconds(2000));
                i_love_trains.simulate();
                i_love_trains.print_log();
            }
    }
    catch(Error error){
        error.print();
    }
}