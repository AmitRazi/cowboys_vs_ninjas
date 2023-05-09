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
#include <random>
#include <chrono>


using namespace std;

#include "sources/Team.hpp" //no need for other includes

using namespace ariel;

double random_float(double min = -100, double max = 100) {
    std::default_random_engine generator(
            static_cast<std::default_random_engine::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
};

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

Character *random_char(double x = random_float(), double y = random_float()) {
    int flag = rand() % 4;

    if (flag == 0) return create_cowboy(x, y);

    if (flag == 1) return create_yninja(x, y);

    if (flag == 2) return create_tninja(x, y);

    return create_oninja(x, y);
};

auto simulate_battle = [](Team &team, Team &team2) {
    while (team.stillAlive() > 0 && team2.stillAlive() > 0) {
        team.attack(&team2);
        team2.attack(&team);
    }
};

int main() {

    OldNinja old{"Bob", Point{0, 0}};
    YoungNinja young{"Bob", Point{0, 0}};
    Cowboy cowboy{"Bob", Point{0, 0}};
    TrainedNinja trained("Bob",Point{0,0});
    OldNinja old2{"Bob", Point{0, 0}};
    YoungNinja young2{"Bob", Point{0, 0}};
    Cowboy cowboy2{"Bob", Point{0, 0}};
    TrainedNinja trained2("Bob",Point{0,0});

    while(old2.isAlive()){
        young.slash(&old2);
    }

    while(young2.isAlive()){
        young.slash(&young2);
    }

    while(trained2.isAlive()){
        young.slash(&trained2);
    }

    while(cowboy2.isAlive()){
        young.slash(&cowboy2);
    }

    cowboy.shoot(&old2);

}