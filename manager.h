#ifndef MANAGER_H
#define MANAGER_H
#include "persons.h"
#include <iostream>
using namespace std;
#include <string>

class manager{
public:
persons* person;
bool updategoal(persons* person);
bool workoutplanbulk(persons* person);
bool workoutplan(persons* person);
bool updateheight(persons* person);
bool updateweight(persons* person);
bool updateage(persons* person);
bool updatebench(persons* person);
bool updatesquat(persons* person);
bool updatedeadlift(persons* person);
bool bench(persons* person);
bool one(persons* person);
bool squat(persons* person);
bool deadlift(persons* person);
bool updatepr(persons* person);
bool update(persons* person);
void save(persons* person);
bool workoutplanlean(persons* person);
bool meal(persons* person);
bool mealbulk(persons* person);
bool meallean(persons* person);
bool strength(persons * person);
persons* storage(string name, string password);
bool play(persons* person);
bool create();
bool login();
bool menu();
bool checkname(persons* person);
bool checkpassword(persons* person);
void add(persons* person);

};
#endif