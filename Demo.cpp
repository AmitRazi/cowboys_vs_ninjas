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
using namespace std;

#include "sources/Team.hpp" //no need for other includes
#include "sources/SmartTeam.hpp"

using namespace ariel;


int main() {
    Point a(32.3,44),b(1.3,3.5);
    assert(a.distance(b) == b.distance(a));
    Cowboy *tom = new Cowboy("Tom", a);
    OldNinja *sushi = new OldNinja("sushi", b);

    Cowboy *tom2 = new Cowboy("Tom", a);
    OldNinja *sushi2 = new OldNinja("sushi", b);


    Team team_A(tom);
    team_A.add(sushi);
    team_A.print();
    // Team b(tom); should throw tom is already in team a
    Team team_B(tom2);
    team_B.add(sushi2);

    while(team_A.stillAlive() > 0 && team_B.stillAlive() > 0){
        team_A.attack(&team_B);
        if(team_B.stillAlive() >0) {
            team_B.attack(&team_A);
        }
        team_A.print();
        team_B.print();
    }

    if (team_A.stillAlive() > 0) cout << "winner is team_A" << endl;
    else cout << "winner is team_B" << endl;

    return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.

}