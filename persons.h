#ifndef PERSONS_H
#define PERSONS_H

#include <iostream>
using namespace std;
#include <string>

class persons{
    private:
    string name;
    string password;
    string goal;
    int height;
    int weight;
    int age;
    int bench;
    int squat;
    int deadlift;
    public:
    persons(){
        name = "unknown";
        password = "unknown";
        goal = "unknown";
        height = 0;
        weight = 0;
        age = 0;
        bench = 0;
        squat = 0;
        deadlift = 0;
    }
    persons(string n, string p, string g){
        name = n;
        password = p;
        goal = g;
    }
    void setName(string n){
        name = n;
    }
    string getName(){
        return name;
    }
    void setPassword(string p){
        password = p;
    }
    string getPassword(){
        return password;
    }
    void setGoal(string g){
        goal = g;
    }
    string getGoal(){
        return goal;
    }
    void setSquat(int s){
        squat = s;
    }
    int getSquat(){
        return squat;
    }
    void setBench(int b){
        bench = b;
    }
    int getBench(){
        return bench;
    }
    void setDeadlift(int d){
        deadlift = d;
    }
    int getDeadlift(){
        return deadlift;
    }
    void setHeight(int h){
        height = h;
    }
    int getHeight(){
        return height;
    }
    void setWeight(int w){
        weight = w;
    }
    int getWeight(){
        return weight;
    }
    void setAge(int a){
      age = a;
    }
    int getAge(){
      return age;
    }
    

};
#endif