/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <chrono>

using namespace std;

#include "sources/Team.hpp" //no need for other includes
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"

using namespace ariel;
double random_float(double min = -100, double max = 100) {
    std::default_random_engine generator(
            static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

auto create_yninja = [](double x = random_float(), double y = random_float()) {
    return new YoungNinja{"Bob", Point{x, y}};
};

auto create_tninja = [](double x = random_float(), double y = random_float()) {
    return new TrainedNinja{"Bob", Point{x, y}};
};

auto create_oninja = [](double x = random_float(), double y = random_float()) {
    return new OldNinja{"Bob", Point{x, y}};
};

auto create_cowboy = [](double x = random_float(), double y = random_float()) {
    return new Cowboy{"Bob", Point{x, y}};
};

auto random_char(double x = random_float(), double y = random_float()) -> Character * {
    int flag = static_cast<int>(random_float()) % 4;

    if (flag == 0) return create_cowboy(x, y);

    if (flag == 1) return create_yninja(x, y);

    if (flag == 2) return create_tninja(x, y);

    return create_oninja(x, y);
}

int main() {
    int i;
    int win1 = 0;
    int win2 = 0;
    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        Team team_A(captain1);
        Team team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"Team wins: "<<win1<<" Team wins: "<<win2<<"\n";

    win1 = 0;
    win2 = 0;

    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        SmartTeam team_A(captain1);
        Team team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"SmartTeam wins: "<<win1<<" Team wins: "<<win2<<"\n";

    win1 = 0;
    win2 = 0;

    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        Team team_A(captain1);
        SmartTeam team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"Team wins: "<<win1<<" SmartTeam wins: "<<win2<<"\n";

    win1 = 0;
    win2 = 0;

    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        Team2 team_A(captain1);
        Team team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"Team2 wins: "<<win1<<" Team wins: "<<win2<<"\n";

    win1 = 0;
    win2 = 0;

    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        Team team_A(captain1);
        Team2 team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"Team wins: "<<win1<<" Team2 wins: "<<win2<<"\n";

    win1 = 0;
    win2 = 0;

    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        Team2 team_A(captain1);
        Team2 team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"Team2 wins: "<<win1<<" Team2 wins: "<<win2<<"\n";

    win1 = 0;
    win2 = 0;

    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        SmartTeam team_A(captain1);
        Team2 team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"SmartTeam wins: "<<win1<<" Team wins: "<<win2<<"\n";

    win1 = 0;
    win2 = 0;

    for(int i = 0 ; i < 10000 ; i++) {
        auto captain1 = random_char();
        auto captain2 = random_char();


        Team2 team_A(captain1);
        SmartTeam team_B(captain2);
        for (int i = 0; i < 9; i++) {
            team_A.add(random_char());
            team_B.add(random_char());
        }
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            team_A.attack(&team_B);
            if (team_B.stillAlive() > 0) {
                team_B.attack(&team_A);
            }
        }

        if (team_A.stillAlive() > 0){
            win1++;
        } else{
            win2++;
        }

    }
    std::cout<<"Team2 wins: "<<win1<<" SmartTeam wins: "<<win2<<"\n";
    return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.

}