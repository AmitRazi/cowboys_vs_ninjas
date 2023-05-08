/*
#include "../SP_4/doctest.h"

#include "sources/Character.hpp"
#include "sources/OldNinja.hpp"
#include "sources/YoungNinja.hpp"
#include "sources/TrainedNinja.hpp"
#include "sources/Cowboy.hpp"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include <numeric>
#include <random>
#include <chrono>

double random(double min = -100, double max = 100) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
};

auto create_yninja = [](double x = random(), double y = random()) {
    return new YoungNinja{"Bob", Point{x, y}};
};

auto create_tninja = [](double x = random(), double y = random()) {
    return new TrainedNinja{"Bob", Point{x, y}};
};

auto create_oninja = [](double x = random(), double y = random()) {
    return new OldNinja{"Bob", Point{x, y}};
};

auto create_cowboy = [](double x = random(), double y = random()) {
    return new Cowboy{"Bob", Point{x, y}};
};

Character *random_char(double x = random(), double y = random()) {
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

const int MAX_TEAM = 10;

TEST_SUITE("Point class tests") {
    Point p1{1, 1};
    Point p2{2, 3};
    Point n1{-1, 1};
    Point n2{1, -9};
    Point n3{-1, -1};

    TEST_CASE("Distance method") {
        CHECK_EQ(p1.distance(p2), p2.distance(p1));
        CHECK_EQ(n1.distance(n2), n2.distance(n1));
        CHECK_EQ(n3.distance(p1), p1.distance(n3));

        CHECK_EQ(n2.distance(p1), 10);
        CHECK_EQ(p2.distance(n3), 5);
        CHECK_EQ(p1.distance(p1), 0);
    }

    TEST_CASE("moveTowards method") {
        double distance = p1.distance(p2);
        double half_p = distance / 2;
        double third_p = distance / 3;

        Point p3{p1.moveTowards(p1, p2, half_p)};
        CHECK_EQ(p3.distance(p2), doctest::Approx(half_p).epsilon(0.001));

        Point p4{p1.moveTowards(p1, p2, third_p)};
        CHECK_EQ(p4.distance(p2), doctest::Approx(third_p).epsilon(0.001));

        // There is no such a thing as negative distance
        CHECK_THROWS(Point {Point::moveTowards(p1,p2,-1)});
    }

}

TEST_SUITE("Classes initialization tests and Team modification( add(),stillAlive() )") {
    Cowboy cowboy{"Bob", Point{2, 3}};
    YoungNinja ninja{"Bob", Point{2, 3}};

    TEST_CASE("Cowboy initialization") {
        CHECK(cowboy.hasboolets());
        CHECK_EQ(cowboy.getName(), "Bob");
        CHECK_EQ(cowboy.getLocation().distance(Point{2, 3}), 0);
        CHECK(cowboy.isAlive());
    }

    TEST_CASE("YoungNinja initialization") {
        CHECK_EQ(ninja.getName(), "Bob");
        CHECK_EQ(ninja.getLocation().distance(Point{2, 3}), 0);
        CHECK(ninja.isAlive());
    }

    TEST_CASE("OldNinja initialization") {
        OldNinja old_ninja{"Bob", Point(2, 3)};
        CHECK_EQ(old_ninja.getName(), "Bob");
        CHECK_EQ(old_ninja.getLocation().distance(Point{2, 3}), 0);
        CHECK(old_ninja.isAlive());
    }

    TEST_CASE("TrainedNinja initialization") {
        TrainedNinja trained_ninja{"Bob", Point{2, 3}};
        CHECK_EQ(trained_ninja.getName(), "Bob");
        CHECK_EQ(trained_ninja.getLocation().distance(Point{2, 3}), 0);
        CHECK(trained_ninja.isAlive());
    }

    TEST_CASE("Team initialization") {
        Team team{&cowboy};
        CHECK_EQ(team.stillAlive(), 1);

        Team2 team2{&ninja};
        CHECK_EQ(team2.stillAlive(), 1);

        CHECK_THROWS(Team{&ninja});
        CHECK_THROWS(Team2{&cowboy});
    }

    TEST_CASE("Team class add() and stillAlive() methods") {
        auto captain1 = create_oninja();
        auto captain2 = create_yninja();

        Team team1{captain1};
        Team2 team2{captain2};

        for (int i = 0; i < MAX_TEAM - 1; i++) {
            if (i % 2 == 0) {
                auto cur1 = create_tninja();
                auto cur2 = create_cowboy();
                team1.add(cur1);
                team2.add(cur2);
                CHECK_EQ(team1.stillAlive(), i + 2);
                CHECK_EQ(team2.stillAlive(), i + 2);
            }
        }

        auto over = create_cowboy();
        CHECK_THROWS(team1.add(over));
        CHECK_THROWS(team2.add(over));
    }

    TEST_CASE("Appointing the same leader to different teams") {
        auto captain = create_cowboy();
        auto captain2 = create_yninja();

        Team team1{captain};
        CHECK_THROWS(Team{captain});
        CHECK_THROWS(Team2{captain});

        Team team2{captain2};
        CHECK_THROWS(Team{captain2});
        CHECK_THROWS(Team2{captain2});
    }

    TEST_CASE("Adding the same regular character to different teams") {
        auto captain1 = create_tninja();
        auto captain2 = create_oninja();
        auto captain3 = create_yninja();

        Team team1{captain1};
        Team team2{captain2};
        Team2 team3{captain3};

        auto over = create_cowboy();
        team1.add(over);
        CHECK_THROWS(team2.add(over));
        CHECK_THROWS(team3.add(over));
    }
}


TEST_SUITE("Battle related methods") {

    TEST_CASE("Cowboy shoot() are reload() methods") {
        auto cowboy = create_cowboy();
        auto target = create_oninja();

        auto shoot = [&](int times) {
            for (int i = 0; i < times; i++) {
                cowboy->shoot(target);
            }
        };

        shoot(6);
        CHECK_FALSE(cowboy->hasboolets());
        CHECK_THROWS(cowboy->shoot(target)); // The magazine should be empty
        cowboy->reload();

        shoot(3);
        cowboy->reload();
        shoot(5);
        CHECK(target->isAlive()); // Target should still be alive with 10 hit points if the cowboys damage is 10
        shoot(1);
        CHECK_THROWS(shoot(1)); // Reloading when the magazine isn't empty shouldn't result in more than 6 _bullets
        CHECK_FALSE(target->isAlive()); // Target should be dead

    }

    TEST_CASE("Not all ninjas are created equal") {

        SUBCASE("Ninjas hit points are different") {
            auto old = create_oninja();
            auto trained = create_tninja();
            auto young = create_yninja();
            auto cowboy = create_cowboy();
            for (int i = 0; i < 15; i++) {
                CHECK(old->isAlive());
                CHECK(trained->isAlive());
                CHECK(young->isAlive());
                cowboy->reload();
                if (i < 10) {
                    cowboy->shoot(young);
                }
                if (i < 12) {
                    cowboy->shoot(trained);
                }
                cowboy->shoot(old);
            }

            CHECK_FALSE((old->isAlive() || young->isAlive() || trained->isAlive()));
        }

        SUBCASE("Ninjas speeds are different") {
            OldNinja old{"Bob", Point{random() + 15, random() + 15}};
            TrainedNinja trained{"Kung fu panda", Point{random() + 15, random() + 15}};
            YoungNinja young{"Karate kid", Point{random() + 15, random() + 15}};
            Cowboy cowboy{"Clint", Point{0, 0}};

            double old_distance = old.distance(&cowboy);
            double young_distance = trained.distance(&cowboy);
            double trained_distance = trained.distance(&cowboy);

            old.move(&cowboy);
            trained.move(&cowboy);
            young.move(&cowboy);

            CHECK_EQ(old.distance(&cowboy),
                     doctest::Approx(old_distance - 8).epsilon(0.001));
            CHECK_EQ(trained.distance(&cowboy),
                     doctest::Approx(trained_distance - 12).epsilon(0.001));
            CHECK_EQ(young.distance(&cowboy),
                     doctest::Approx(young_distance - 14).epsilon(0.001));
        }

        SUBCASE("Ninja is too far away from move() destination") {
            double edge1 = std::numeric_limits<double>::max();
            double edge2 = std::numeric_limits<double>::min();

            YoungNinja ninja{"Bob", Point{edge1, edge1}};
            OldNinja ninja2{"Bob", Point{edge2, edge2}};
            TrainedNinja ninja3{"Yet another bob", Point{edge1, edge2}};

            CHECK_THROWS_AS(ninja.move(&ninja2),std::runtime_error);
            CHECK_THROWS_AS(ninja2.move(&ninja3),std::runtime_error);
            CHECK_THROWS_AS(ninja3.move(&ninja),std::runtime_error);
        }


        SUBCASE("Ninjas can only slash when distance is less than 1") {
            OldNinja old{"Bob", Point{0, 0}};
            TrainedNinja trained{"Kung fu panda", Point{0, 0}};
            YoungNinja young{"Karate kid", Point{0.5, 0.5}};
            Cowboy cowboy{"Clint", Point{0.5, 0.5}};

            old.slash(&cowboy);
            young.slash(&cowboy);
            trained.slash(&cowboy);

            CHECK(cowboy.isAlive());

            old.slash(&cowboy);
            CHECK_FALSE(cowboy.isAlive());

            YoungNinja ninja{"Bob", Point{-0.5, 0.5}};
            OldNinja ninja2{"Bob", Point{1, 1}};
            CHECK_THROWS_AS(young.slash(&ninja),std::runtime_error); // distance is exactly one
            CHECK_THROWS_AS(old.slash(&ninja2),std::runtime_error); // distance is more than one
        }
    }

    TEST_CASE("Dead characters cannot attack and characters cannot attack a dead enemy") {
        OldNinja old{"Bob", Point{0, 0}};
        YoungNinja young{"Bob", Point{0, 0}};
        Cowboy cowboy{"Bob", Point{0, 0}};

        while (young.isAlive()) {
            old.slash(&young);
            old.slash(&cowboy);
        }

        CHECK_THROWS_AS(young.slash(&old),std::runtime_error);
        CHECK_THROWS_AS(cowboy.shoot(&old),std::runtime_error);
        CHECK_THROWS_AS(old.slash(&cowboy),std::runtime_error);
    }

    TEST_CASE("Sending nullptr to the attack() method") {
        auto cowboy = create_cowboy();
        auto ninja = create_tninja();
        Team team{cowboy};
        Team2 team2{ninja};

        CHECK_THROWS_AS(team.attack(nullptr),std::invalid_argument);
        CHECK_THROWS_AS(team2.attack(nullptr),std::invalid_argument);
    }

    TEST_CASE("Sending negative value to hit()"){
        auto cowboy = create_cowboy();
        auto yninja = create_yninja();
        auto oninja = create_oninja();
        auto tninja = create_tninja();

        CHECK_THROWS_AS(cowboy->hit(-random(1,100)),std::invalid_argument);
        CHECK_THROWS_AS(yninja->hit(-random(1,100)),std::invalid_argument);
        CHECK_THROWS_AS(oninja->hit(-random(1,100)),std::invalid_argument);
        CHECK_THROWS_AS(tninja->hit(-random(1,100)),std::invalid_argument);
    }

    TEST_CASE("Dead cowboy can not reload"){
        auto cowboy = create_cowboy();
        auto cowboy2 = create_cowboy();

        cowboy->shoot(cowboy2);
        while(cowboy2->isAlive()){
            cowboy2->shoot(cowboy);
            cowboy->reload();
        }

        CHECK_THROWS_AS(cowboy->reload(),std::runtime_error);
    }

    TEST_CASE("No self harm"){
        auto cowboy = create_cowboy();
        auto yninja = create_yninja();
        auto oninja = create_oninja();
        auto tninja = create_tninja();

        CHECK_THROWS_AS(cowboy->shoot(cowboy),std::runtime_error);
        CHECK_THROWS_AS(yninja->slash(yninja),std::runtime_error);
        CHECK_THROWS_AS(oninja->slash(oninja),std::runtime_error);
        CHECK_THROWS_AS(tninja->slash(tninja),std::runtime_error);
    }
}

TEST_SUITE("Battle simulations") {

    auto multi_attack = [](int n, Team &attacker, Team &defender) {
        for (int i = 0; i < n; i++) {
            attacker.attack(&defender);
        }
    };

    TEST_CASE("Characters attack the closest enemy to the captain and ignore dead enemies ") {
        Team team{create_cowboy(-1, -1)};
        team.add(create_yninja(0, 0));
        team.add(create_oninja(-0.5, -0.5));
        team.add(create_tninja(0.5, 0.5));
        team.add(create_cowboy());

        CHECK_EQ(team.stillAlive(), 5);

        auto young_ninja = create_yninja(0, 0);
        auto trained_ninja = create_tninja(1, 1);
        auto old_ninja = create_oninja(2, 2);
        auto young_ninja2 = create_yninja(3, 3);
        auto cowboy = create_cowboy(-5, -5);
        Team team2{young_ninja};
        team2.add(old_ninja);
        team2.add(trained_ninja);
        team2.add(cowboy);
        CHECK_EQ(team2.stillAlive(), 4);

        team.attack(&team2);
        CHECK_FALSE(young_ninja->isAlive()); // Young ninja should be dead
        CHECK((trained_ninja->isAlive() && old_ninja->isAlive() &&
               young_ninja2->isAlive())); // Everyone else should still be alive

        team.attack(&team2);
        CHECK((trained_ninja->isAlive() && old_ninja->isAlive() &&
               young_ninja2->isAlive())); // No one should die in the attack

        team.attack(&team2);
        CHECK_FALSE(trained_ninja->isAlive()); // Trained ninja should be dead
        CHECK((old_ninja->isAlive() && young_ninja2->isAlive()));

        team.attack(&team2);
        CHECK_FALSE(old_ninja->isAlive()); // Old ninja should be dead
        CHECK(young_ninja2->isAlive());

        CHECK_NOTHROW(team.attack(&team2)); // The entire enemy team will be dead before every cowboy shoots, the attack should stop and not throw an exception
        CHECK_FALSE(young_ninja2->isAlive()); // Young ninja should be dead
        CHECK_THROWS_AS(team.attack(&team2),std::runtime_error); // Attacking a dead team should throw an exception
    }


 In this test only cowboys are used because they are stationary. This allows us to better keep track of everyone's position to better test for captain assignment.

    The characters are organized as such:
    2-1--2-[C1]-[C2]--2--1
    A hyphen (-) denotes a distance of one.



    TEST_CASE("The closest teammate to the captain is appointed as captain") {

        auto team_c1 = create_cowboy(0, 0);
        auto team2_c1 = create_cowboy(-2, 0);
        auto team_c2 = create_cowboy(-3, 0);
        auto team2_c2 = create_cowboy(1, 0);
        auto team2_c3 = create_cowboy(3, 0);
        auto team_c3 = create_cowboy(5, 0);
        auto team2_c4 = create_cowboy(-5, 0);

        Team team1{team_c1};
        Team2 team2{team2_c2};

        multi_attack(4, team1, team2);

        // The captain of team2 is the closest enemy to the captain of team1, and therefore should be dead.
        CHECK((!team2_c2->isAlive() && team2_c1->isAlive() && team2_c3->isAlive() && team2_c4->isAlive()));

        // At this point, the captain should be team2_c3; hence, the next enemy to be attacked by team2 should team_c3.
        multi_attack(6, team2, team1);
        CHECK((!team_c3->isAlive() && team_c1->isAlive() && team_c2->isAlive()));


        // Killing the new captain
        team_c1->reload();
        team_c2->reload();
        while (team2_c3->isAlive()) {
            team_c1->shoot(team2_c3);
            team_c2->shoot(team2_c3);
        }
        CHECK((!team2_c2->isAlive() && team2_c1->isAlive() && !team2_c3->isAlive() && team2_c4->isAlive()));

        team2_c1->reload();
        team2_c4->reload();

        //Next captain should be team2_c1, hence, the next enemy to be attacked by team2 should team_c1.
        multi_attack(6, team2, team1);
        CHECK((!team_c3->isAlive() && !team_c1->isAlive() && team_c2->isAlive()));
        CHECK_NOTHROW(simulate_battle(team1,team2));

    }


    // In this test the attacking team is again composed of cowboys, this is because cowboys are stationary, and we can predict the damage done in every attack.
    TEST_CASE("If several enemies are equidistant from the captain, only a single enemy should still be targeted.") {
        auto cowboy = create_cowboy();
        Team team{cowboy};
        for (int i = 0; i < 4; i++) {
            team.add(create_cowboy());
        }

        auto char1 = create_yninja(0, 0);
        auto char2 = create_yninja(0, 0);
        auto char3 = create_yninja(0, 0);
        auto char4 = create_yninja(0, 0);

        Team team2{char1};
        team2.add(char2);
        team2.add(char3);
        team2.add(char4);

        // Young ninjas have 100 hit points. 2 attacks should result in 10 shots, killing only one, if they all target the same enemy
        multi_attack(2, team, team2);
        CHECK_EQ(team.stillAlive(), 3);

        // Two more attacks should result in another single casualty
        multi_attack(2, team, team2);
        CHECK_EQ(team.stillAlive(), 2);

        // Two more attacks should result in another single casualty
        multi_attack(2, team, team2);
        CHECK_EQ(team.stillAlive(), 1);

        team.attack(&team2);
        CHECK_EQ(team.stillAlive(), 1);

        team.attack(&team2);
        CHECK_EQ(team.stillAlive(), 0);

    }

    TEST_CASE("When the captain moves, a different enemy should be targeted") {
        auto t11 = create_yninja(random(1.0,1.9), random(1.0,1.9));
        auto t12 = create_oninja(random(2.0,2.9), random(2.0,2.9));
        auto t13 = create_tninja(random(3.0,3.9), random(3.0,3.9));
        auto t14 = create_cowboy();
        Team team{t11};
        team.add(t11);
        team.add(t12);
        team.add(t13);
        team.add(t14);

        auto t21 = create_cowboy(random(-1.0,-1.9), random(-1.0,-1.9));
        auto t22 = create_yninja(random(-2.0,-2.9), random(-2.0,-2.9));
        auto t23 = create_tninja(random(-3.0,-3.9), random(-3.0,-3.9));
        Team team2{t21};
        team.add(t22);
        team.add(t23);

        team.attack(&team2);
        CHECK_EQ(t11->distance(t21), doctest::Approx(0).epsilon(0.001));
        CHECK_EQ(t12->distance(t21), doctest::Approx(0).epsilon(0.001));
        CHECK_EQ(t13->distance(t21), doctest::Approx(0).epsilon(0.001));
        CHECK(t21->isAlive());
        multi_attack(2,team,team2);
        CHECK_FALSE(t21->isAlive()); // The first move in the attack should be a shot by the cowboy that kills t21

        // After the cowboy kills t21, all the ninja should move towards t22.
        CHECK_EQ(t11->distance(t22), doctest::Approx(0).epsilon(0.001));
        CHECK_EQ(t12->distance(t22), doctest::Approx(0).epsilon(0.001));
        CHECK_EQ(t13->distance(t22), doctest::Approx(0).epsilon(0.001));

        // Moving the captain behind t23, making t23 the new closest enemy.
        Point::moveTowards(t11->getLocation(),Point{-4,-4},14);
        multi_attack(3,team,team2);
        CHECK_EQ(t11->distance(t23), doctest::Approx(0).epsilon(0.001));
        CHECK_EQ(t12->distance(t23), doctest::Approx(0).epsilon(0.001));
        CHECK_EQ(t13->distance(t23), doctest::Approx(0).epsilon(0.001));

        CHECK((!t21->isAlive() && t22->isAlive() && !t23->isAlive()));

        CHECK_NOTHROW(simulate_battle(team,team2));
    }

    TEST_CASE("Run full battles with random teams to ensure full functionality") {
        SUBCASE("Team vs Team") {
            Team team{random_char()};
            Team team2{random_char()};
            for (int i = 0; i < MAX_TEAM - 1; i++) {
                team.attack(&team2);
                team2.attack(&team);
            }

            simulate_battle(team, team2);

            CHECK(((team.stillAlive() && !team2.stillAlive()) || (!team.stillAlive() && team2.stillAlive())));
        }

        SUBCASE("Team vs Team2") {
            Team team{random_char()};
            Team2 team2{random_char()};
            for (int i = 0; i < MAX_TEAM - 1; i++) {
                team.attack(&team2);
                team2.attack(&team);
            }

            simulate_battle(team, team2);

            CHECK(((team.stillAlive() && !team2.stillAlive()) || (!team.stillAlive() && team2.stillAlive())));
        }

        SUBCASE("Team2 vs Team2") {
            Team2 team{random_char()};
            Team2 team2{random_char()};
            for (int i = 0; i < MAX_TEAM - 1; i++) {
                team.attack(&team2);
                team2.attack(&team);
            }

            simulate_battle(team, team2);

            CHECK(((team.stillAlive() && !team2.stillAlive()) || (!team.stillAlive() && team2.stillAlive())));
        }
    }
}
*/