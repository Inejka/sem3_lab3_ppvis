//
// Created by inejka on 16.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_LOADER_AND_CHECKER_H
#define SEM3_LAB3_PPVIS_LOADER_AND_CHECKER_H
#include "game_field.h"
#include <iostream>
#include "stations.h"
#include <fstream>
#include <string>
struct Load{
    std::string file_name;
    Load(std::string tmp){file_name=tmp;}
    void operator ()(Game_field &to_load){
        std::fstream file;
        file.open(file_name.data());
        int kolvo;
        file >> kolvo;
        for(int i = 0 ; i < kolvo ; i++){
            int type;
            file >> type ;
            Station *tmp;
            switch (type) {
                case 0:
                    tmp = new Passenger_station(i);
                    break;
                case 1:
                    tmp = new Cargo_station(i);
                    break;
                case 2:
                    tmp = new Passenger_and_Cargo_station(i);
                    break;
            }
            std::pair<std::vector<std::pair<int, int>>, Station *> tmp1 ;
            tmp1.second = tmp;
            to_load.its_graph.push_back(tmp1);
        }
        file >> kolvo;
        for(int i = 0 ; i < kolvo ; i++){
            int first , second , weight ;
            file >> first >> second >> weight ;
            to_load.its_graph[first].first.push_back(std::make_pair(second,weight));
        }
        file >> kolvo ;
        for(int i = 0 ; i < kolvo ; i++) {
            int lifetime,force,cargo,passanger;
            file >> lifetime >> force >> cargo >> passanger ;
            std::pair<std::pair<std::vector<int>, std::pair<int, int>>, Train *> tmp;
            tmp.second = new Train(lifetime, force, cargo, passanger);
            tmp.first.second={0,0};
            to_load.its_trains.push_back(tmp);
        }
        for(int  i = 0 ; i < kolvo ; i++){
           int kolvo1 ;
           file >> kolvo1 ;
           for(int j = 0 ; j < kolvo1 ; j++){
               int tmp2 ;
               file >> tmp2 ;
                to_load.its_trains[i].first.first.push_back(tmp2);
           }
        }
        for(int i = 0 ; i < 2000 ; i++)
        to_load.its_graph[1].second->add();
        std::cout << "Load completed\n" ;
        file.close();
    }
};


struct Check{
    Check(){}
    bool is_edge_between1( std::vector<std::pair<int,int>> its_graph, int second){
        for(int i = 0 ; i < its_graph.size(); i++)
            if(its_graph[i].first==second)return true;
        return false;
    }
    void operator () (Game_field &to_check){
        for(auto &i:to_check.its_trains){
            for(int j = 0 ; j < i.first.first.size() - 1  ; j++)
                if(!is_edge_between1(to_check.its_graph[i.first.first[i.first.first[j]]].first,i.first.first[j+1]))std::exit(123);
        if(!is_edge_between1(to_check.its_graph[i.first.first[i.first.first.size()-1]].first,i.first.first[0]))std::exit(123);
        }
        std::cout << "Check complete\n";
    }
};

#endif //SEM3_LAB3_PPVIS_LOADER_AND_CHECKER_H
