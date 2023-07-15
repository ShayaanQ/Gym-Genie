#include "manager.h"
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cctype>
#include <vector>
#include <sstream>
#include "persons.h"
#include <iostream>
using namespace std;
#include <string>



bool manager::menu(){
  
  cout << endl << "----------------------------------------========================================== Welcome To Gym Genie ==========================================----------------------------------------" << endl << endl;
  cout << "Enter 1 to create a new account:" << endl << endl;
  cout << "Enter 2 to login:" << endl << endl;
  
  string o;
  cin >> o;

  if(o == "1"){
    if(create()){
        return true;
    }
    else{
        return false;
    }
  }
  else if(o == "2"){
    if(login()){
        return true;
    }
    else{
        return false;
    }
  }
  else{
    cout << endl << "...................................................................................... Invalid Option ...................................................................................." << endl << endl;
  }
  
  return false; 
}

bool manager::create(){
  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "To Create An Account, Please Enter Your User Name:";
  cout << "                                                                                                WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;
  
  string name;
  cin >> name;

  if((name == "q") || (name == "Q")){
    return false;
  }

  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "Please Enter Your Password:";
  cout << "                                                                                                WARNING: DO NOT USE SPACES IN YOUR PASSWORD!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;
  
  string password;
  cin >> password;

  if((password == "q") || (password == "Q")){
    return false;
  }
  
  string goal = "unknown";
  persons* person;
  person = new persons(name, password, goal);
  

  if(!checkname(person)){
    if(!checkpassword(person)){
        cout << endl << "Congratulations, Your Account Has Been Created " << person->getName() << "!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        add(person);
        string key;
        cin >> key;
    }
    else{
        cout << endl << "Sorry But The Password Is Already In Use!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    return false;
  }
  else{
    cout << endl << "Sorry But there Is Already A User Under This Name, Please Enter Any Key To Return To Menu:" << endl << endl;
    string key;
    cin >> key;
    return false;
  }
  
  return false;
}

bool manager::checkpassword(persons* person){
ifstream fin;
  fin.open("DATA.txt");
  string temp;
  string password = person->getPassword();

  if(!fin.is_open()){
    cout << "File Not Found!" << endl;
    return 0;
  }

  while(getline(fin, temp)){
    
    istringstream ins(temp);

    string tempname;
    ins >> tempname;
    string temppassword;
    ins >> temppassword;

   

    
    if(temppassword == password){
      return true;
    }

  }
  
  fin.close();

  return false;
}

bool manager::login(){

  persons* person = nullptr;
  
  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "Please Enter Your User Name To Login: ";
  cout << "                                                                                                              WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;

  string name;
  cin >> name;

  if((name == "q") || (name == "Q")){
    return false;
  }

  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "Please Enter Your Password: ";
  cout << "                                                                                                              WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;

  string password;
  cin >> password;

  if((password == "q") || (password == "Q")){
    return false;
  }
  
    
  person = storage(name, password);
  if(person != nullptr){
    play(person);
    return false;
  }
    
  

  return false;
  
}

void manager::save(persons* person){
  vector<persons*> people1;
  vector<string> data1;
  ifstream fin;
  string temp1;
  
  fin.open("DATA.txt");
  if(!fin.is_open()){
    cout << "File Not Found!" << endl;
  }

  string line;
while (getline(fin, line)) {
    istringstream ins(line);

    string name;
    string password;
    string goal;
    int height;
    int weight;
    int age;
    int bench;
    int squat;
    int deadlift;

    if (ins >> name >> password >> goal >> height >> weight >> age >> bench >> squat >> deadlift) {
        persons* user1 = new persons();
        user1->setName(name);
        user1->setPassword(password);
        user1->setGoal(goal);
        user1->setHeight(height);
        user1->setWeight(weight);
        user1->setAge(age);
        user1->setBench(bench);
        user1->setSquat(squat);
        user1->setDeadlift(deadlift);

        people1.push_back(user1);
    }
}

fin.close();

for (int i = 0; i < people1.size(); i++) {
    if (people1[i]->getName() == person->getName() && people1[i]->getPassword() == person->getPassword()) {
        delete people1[i];
        people1.erase(people1.begin() + i);
        break;
    }
}

// Add the new person to the vector
persons* user1 = new persons();
user1->setName(person->getName());
user1->setPassword(person->getPassword());
user1->setGoal(person->getGoal());
user1->setHeight(person->getHeight());
user1->setWeight(person->getWeight());
user1->setAge(person->getAge());
user1->setBench(person->getBench());
user1->setSquat(person->getSquat());
user1->setDeadlift(person->getDeadlift());

people1.push_back(user1);

ofstream fout;
fout.open("DATA.txt");
if (!fout.is_open()) {
    cout << "File Not Found!" << endl;
} else {
    // Write the updated data to the file
    for (int i = 0; i < people1.size(); i++) {
        fout << people1[i]->getName() << " " << people1[i]->getPassword() << " " << people1[i]->getGoal() << " "
             << people1[i]->getHeight() << " " << people1[i]->getWeight() << " " << people1[i]->getAge() << " "
             << people1[i]->getBench() << " " << people1[i]->getSquat() << " " << people1[i]->getDeadlift() << endl;
    }
}

fout.close();
  
}

persons* manager::storage(string name, string password){
  vector<persons*> people;
  vector<string> tempdata;
  vector<string> data;
  ifstream fin;
  string temp;
  
  fin.open("DATA.txt");
  if(!fin.is_open()){
    cout << "File Not Found!" << endl;
  }

  while(getline(fin, temp)){
    
    istringstream ins(temp);

    string variables;
    
    while(ins >> variables){
      data.push_back(variables);
    }

    for(int i = 0; i < data.size(); i++){
      tempdata.push_back(data[i]);
    }
    

    ins.clear();
    


    persons* user = new persons();
    user->setName(data[0]);
    user->setPassword(data[1]);
    user->setGoal(data[2]);
    user->setHeight(stoi(data[3]));
    user->setWeight(stoi(data[4]));
    user->setAge(stoi(data[5]));
    user->setBench(stoi(data[6]));
    user->setSquat(stoi(data[7]));
    user->setDeadlift(stoi(data[8]));
    people.push_back(user);

    data.clear();
    
  }
  
  
  int index = -1;
  int i = 0;
  
  for(int j = 0; j < tempdata.size(); j+=9){  // up by 9
    if(name == tempdata[j]){
      index = i;  
      break;
    }
    i++;
  }

  
  
  int index2 = -1;
  int k = 0;
  
  for(int l = 1; l < tempdata.size(); l+=9){ //up by 9
    if(password == tempdata[l]){
      index2 = k;  
      break;
    }
    k++;
    
  }

  

  if((index == -1) && (index2 != -1)){
    cout << endl << "Incorrect User Name!" << endl << endl;
    cout << "Enter Any Key To Return To Menu" << endl << endl;
    string key;
    cin >> key;
    return nullptr;
  }

  else if((index == -1) && (index2 == -1)){
    cout << endl << "Incorrect User Name And Password!" << endl << endl;
    cout << "Enter Any Key To Return To Menu" << endl << endl;
    string key;
    cin >> key;
   return nullptr;
  }

  else if((index2 == -1) && (index != -1)){
    cout << endl << "Incorrect Password!" << endl << endl;
    cout << "Enter Any Key To Return To Menu" << endl << endl;
    string key;
    cin >> key;
    return nullptr;

  }


  if(k == i){
  persons* choice = new persons();
  choice = people[index];
   return choice;
  }


  
  return nullptr;
  
}


bool manager::checkname(persons* person){
    
  ifstream fin;
  fin.open("DATA.txt");
  string temp;
  string name = person->getName();

  if(!fin.is_open()){
    cout << "File Not Found!" << endl;
    return 0;
  }

  while(getline(fin, temp)){
    
    istringstream ins(temp);

    string tempname;
    ins >> tempname;

    
    if(tempname == name){
      return true;
    }

  }
  
  fin.close();

  return false;

}

void manager::add(persons* person){
  

  string info = person->getName() + " " + person->getPassword() + " " + person->getGoal() + " " + to_string(person->getHeight()) + " " + to_string(person->getWeight()) + " " + to_string(person->getAge()) + " " + to_string(person->getBench()) + " " + to_string(person->getSquat()) + " " + to_string(person->getDeadlift()); 
  ofstream fout;
  fout.open("DATA.txt", ios_base::app);

  if(!fout.is_open()){
    cout << "File Not Found!" << endl;
  }

  fout << info << endl;

  
  

  fout.close();

}

bool manager::play(persons* person){
  
  cout << endl << "................................................................................. Successfully Logged In! ................................................................................" << endl << endl;
  
  if((person->getHeight() == 0) || (person->getWeight() == 0) ||(person->getAge() == 0) || (person->getGoal() == "unknown")){
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;

        
    int inches;
    cout << endl <<  "Please Enter Your Height In Inches (NOTE: 60 Inches is 5 Feet):" << endl << endl;
    cin >> inches;
    while(!inches){
        cout << endl <<  "Invalid Input, Please Enter Your Height In Inches(NOTE: 60 Inches is 5 Feet):" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> inches;
    }
        
    person->setHeight(inches);

        
    int weight;
    cout << endl <<  "Please Enter Your Weight In Pounds:" << endl << endl;
    cin >> weight;
    while(!weight){
        cout << endl <<  "Invalid Input, Please Enter Your Weight In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> weight;
    }
    person->setWeight(weight);

       
    int age;
    cout << endl <<  "Please Enter Your Age:" << endl << endl;
    cin >> age;
    while(!age){
        cout << endl <<  "Invalid Input, Please Enter Your Age:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> age;
    }
    person->setAge(age);

    bool gun = true;

    while(gun){
    cout << endl << "Is Your Goal To Be Lean Or Bulk?" << endl << endl;
     
    string choice;
    cin >> choice;

    if((choice == "lean") || (choice == "Lean")){
        person->setGoal(choice);
        gun = false;
    }
    else if((choice == "bulk") || (choice == "Bulk")){
        person->setGoal(choice);
        gun = false;
    }
    else{
        cout << endl << "Invalid Choice!" << endl;
        gun = true;
    }
    }

    
        
    save(person);
  }

  bool run = true;

  while(run){
    cout << endl << "...................................................................................... Welcome " << person->getName() << "! ....................................................................................." << endl << endl;

    cout << endl << "Enter 1 For Your Personalized Workout Plan:" << endl << endl;
    cout << "Enter 2 For Your Personalized Meal Plan:" << endl << endl;
    cout << "Enter 3 For Your Strength Test:" << endl << endl;
    cout << "Enter 4 To Update Stats:" << endl << endl;
    cout << "Enter 5 To Exit:" << endl << endl;
    
    string o;
    cin >> o;
    
    
    if(o == "1"){
      workoutplan(person);
      
    }
    else if(o == "2"){
      meal(person);
    }
    else if(o == "3"){
      strength(person);
    }
    else if(o == "4"){
      update(person);
    }
    else if(o == "5"){
        return false;
    }
    else{
        cout << endl << "Invalid Input!" << endl;
    }

  }

  return false;
}

bool manager::strength(persons* person){
    cout << endl << "................................................................................. Successfully Logged In! ................................................................................." << endl << endl;
  
  if((person->getBench() == 0) || (person->getSquat() == 0) ||(person->getDeadlift() == 0)){
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;

        
    int bench;
    cout << endl <<  "Please Enter Your Bench Press PR In Pounds:" << endl << endl;
    cin >> bench;
    while(!bench){
        cout << endl <<  "Invalid Input, Please Enter Your Bench Press PR In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> bench;
    }
        
    person->setBench(bench);

        
    int squat;
    cout << endl <<  "Please Enter Your Squat PR In Pounds:" << endl << endl;
    cin >> squat;
    while(!squat){
        cout << endl <<  "Invalid Input, Please Enter Your Squat PR In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> squat;
    }
    person->setSquat(squat);

       
    int dl;
    cout << endl <<  "Please Enter Your Deadlift PR In Pounds:" << endl << endl;
    cin >> dl;
    while(!dl){
        cout << endl <<  "Invalid Input, Please Enter Your Deadlift PR In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> dl;
    }
    person->setDeadlift(dl);
        
    save(person);
  }

  bool run = true;

  while(run){
    cout << endl << "...................................................................................... Strength Test! ....................................................................................." << endl << endl;

    cout << endl << "Enter 1 To Test Your Bench Press PR Ranking:" << endl << endl;
    cout << "Enter 2 To Test Your Squat PR Ranking:" << endl << endl;
    cout << "Enter 3 To Test Your Deadlift PR Ranking:" << endl << endl;
    cout << "Enter 4 To To Take The 1% Test:" << endl << endl;
    cout << "Enter 5 To Update Your Information:" << endl << endl;
    cout << "Enter 6 To Exit:" << endl << endl;
    
    string o;
    cin >> o;
    
    
    if(o == "1"){
      bench(person);
      
    }
    else if(o == "2"){
      squat(person);
    }
    else if(o == "3"){
      deadlift(person);
    }
    else if(o == "4"){
      one(person);
    }
    else if(o == "5"){
        updatepr(person);
    }
    else if(o == "6"){
        return false;
    }
    else{
        cout << endl << "Invalid Input!" << endl;
    }

  }

    return false;
}

bool manager::bench(persons* person){

    cout << endl << "................................................................................ Bench Press PR Ranking: ................................................................................." << endl << endl;
    

        
        
    cout << "Here Are Your Stats:" << endl << endl;  
    cout << "----User Name----: " << person->getName() << endl << endl;
    cout << "----Bench Press PR----: " << person->getBench() << endl << endl;
    cout << "----Weight----: " << person->getWeight() << endl << endl;
    
    cout << "Enter Any Key To Test Your Bench Press PR Ranking Or Enter Q to Quit:" << endl << endl;

      
    string choice;
    cin >> choice;

    if((choice =="q") || (choice == "Q")){
        return false;
    }

    cout << endl << "Calculating Your Bench Press PR Ranking Please Wait....." << endl << endl;
    sleep(3);

    //110-below beginner
    if((person->getWeight() <= 110) && (person->getBench() <= 80)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 80 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 81 Pounds To 119 Pounds!" << endl << endl;
        cout << "----Intermediate----: 120 Pounds To 165 Pounds!" << endl << endl;
        cout << "----Advaced----: 166 Pounds To 217 Pounds!" << endl << endl;
        cout << "----Elite----: 218 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below novice
    else if((person->getWeight() <= 110) && ((person->getBench() >= 81) && person->getBench() <= 119)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 80 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 81 Pounds To 119 Pounds!" << endl << endl;
        cout << "----Intermediate----: 120 Pounds To 165 Pounds!" << endl << endl;
        cout << "----Advaced----: 166 Pounds To 217 Pounds!" << endl << endl;
        cout << "----Elite----: 218 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below intermediate
    else if((person->getWeight() <= 110) && ((person->getBench() >= 120) && person->getBench() <= 165)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 80 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 81 Pounds To 119 Pounds!" << endl << endl;
        cout << "----Intermediate----: 120 Pounds To 165 Pounds!" << endl << endl;
        cout << "----Advaced----: 166 Pounds To 217 Pounds!" << endl << endl;
        cout << "----Elite----: 218 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below advanced
    else if((person->getWeight() <= 110) && ((person->getBench() >= 166) && person->getBench() <= 217)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 80 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 81 Pounds To 119 Pounds!" << endl << endl;
        cout << "----Intermediate----: 120 Pounds To 165 Pounds!" << endl << endl;
        cout << "----Advaced----: 166 Pounds To 217 Pounds!" << endl << endl;
        cout << "----Elite----: 218 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below elite
    else if((person->getWeight() <= 110) && ((person->getBench() >= 218))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 80 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 81 Pounds To 119 Pounds!" << endl << endl;
        cout << "----Intermediate----: 120 Pounds To 165 Pounds!" << endl << endl;
        cout << "----Advaced----: 166 Pounds To 217 Pounds!" << endl << endl;
        cout << "----Elite----: 218 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //111-120 beginner
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && (person->getBench() <= 92)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 92 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 93 Pounds To 133 Pounds!" << endl << endl;
        cout << "----Intermediate----: 134 Pounds To 182 Pounds!" << endl << endl;
        cout << "----Advaced----: 183 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Elite----: 237 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 novice
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getBench() >= 93) && person->getBench() <= 133)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 92 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 93 Pounds To 133 Pounds!" << endl << endl;
        cout << "----Intermediate----: 134 Pounds To 182 Pounds!" << endl << endl;
        cout << "----Advaced----: 183 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Elite----: 237 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 intermediate
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getBench() >= 134) && person->getBench() <= 182)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 92 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 93 Pounds To 133 Pounds!" << endl << endl;
        cout << "----Intermediate----: 134 Pounds To 182 Pounds!" << endl << endl;
        cout << "----Advaced----: 183 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Elite----: 237 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 advanced
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getBench() >= 183) && person->getBench() <= 236)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 92 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 93 Pounds To 133 Pounds!" << endl << endl;
        cout << "----Intermediate----: 134 Pounds To 182 Pounds!" << endl << endl;
        cout << "----Advaced----: 183 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Elite----: 237 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 elite
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getBench() >= 237))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 92 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 93 Pounds To 133 Pounds!" << endl << endl;
        cout << "----Intermediate----: 134 Pounds To 182 Pounds!" << endl << endl;
        cout << "----Advaced----: 183 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Elite----: 237 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //121-130 beginner
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && (person->getBench() <= 104)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 104 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 105 Pounds To 147 Pounds!" << endl << endl;
        cout << "----Intermediate----: 148 Pounds To 199 Pounds!" << endl << endl;
        cout << "----Advaced----: 200 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Elite----: 256 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 novice
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getBench() >= 105) && person->getBench() <= 147)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 104 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 105 Pounds To 147 Pounds!" << endl << endl;
        cout << "----Intermediate----: 148 Pounds To 199 Pounds!" << endl << endl;
        cout << "----Advaced----: 200 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Elite----: 256 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 intermediate
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getBench() >= 148) && person->getBench() <= 199)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 104 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 105 Pounds To 147 Pounds!" << endl << endl;
        cout << "----Intermediate----: 148 Pounds To 199 Pounds!" << endl << endl;
        cout << "----Advaced----: 200 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Elite----: 256 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 advanced
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getBench() >= 200) && person->getBench() <= 255)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 104 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 105 Pounds To 147 Pounds!" << endl << endl;
        cout << "----Intermediate----: 148 Pounds To 199 Pounds!" << endl << endl;
        cout << "----Advaced----: 200 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Elite----: 256 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 elite
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getBench() >= 256))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 104 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 105 Pounds To 147 Pounds!" << endl << endl;
        cout << "----Intermediate----: 148 Pounds To 199 Pounds!" << endl << endl;
        cout << "----Advaced----: 200 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Elite----: 256 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //131-140 beginner
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && (person->getBench() <= 115)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 115 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 116 Pounds To 161 Pounds!" << endl << endl;
        cout << "----Intermediate----: 162 Pounds To 215 Pounds!" << endl << endl;
        cout << "----Advaced----: 216 Pounds To 271 Pounds!" << endl << endl;
        cout << "----Elite----: 272 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 novice
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getBench() >= 116) && person->getBench() <= 161)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 115 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 116 Pounds To 161 Pounds!" << endl << endl;
        cout << "----Intermediate----: 162 Pounds To 215 Pounds!" << endl << endl;
        cout << "----Advaced----: 216 Pounds To 271 Pounds!" << endl << endl;
        cout << "----Elite----: 272 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 intermediate
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getBench() >= 162) && person->getBench() <= 215)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 115 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 116 Pounds To 161 Pounds!" << endl << endl;
        cout << "----Intermediate----: 162 Pounds To 215 Pounds!" << endl << endl;
        cout << "----Advaced----: 216 Pounds To 271 Pounds!" << endl << endl;
        cout << "----Elite----: 272 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 advanced
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getBench() >= 216) && person->getBench() <= 271)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
       cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 115 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 116 Pounds To 161 Pounds!" << endl << endl;
        cout << "----Intermediate----: 162 Pounds To 215 Pounds!" << endl << endl;
        cout << "----Advaced----: 216 Pounds To 271 Pounds!" << endl << endl;
        cout << "----Elite----: 272 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 elite
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getBench() >= 274))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 115 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 116 Pounds To 161 Pounds!" << endl << endl;
        cout << "----Intermediate----: 162 Pounds To 215 Pounds!" << endl << endl;
        cout << "----Advaced----: 216 Pounds To 271 Pounds!" << endl << endl;
        cout << "----Elite----: 272 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //141-150 beginner
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && (person->getBench() <= 127)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 127 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 128 Pounds To 174 Pounds!" << endl << endl;
        cout << "----Intermediate----: 175 Pounds To 230 Pounds!" << endl << endl;
        cout << "----Advaced----: 231 Pounds To 290 Pounds!" << endl << endl;
        cout << "----Elite----: 291 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 novice
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getBench() >= 128) && person->getBench() <= 174)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 127 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 128 Pounds To 174 Pounds!" << endl << endl;
        cout << "----Intermediate----: 175 Pounds To 230 Pounds!" << endl << endl;
        cout << "----Advaced----: 231 Pounds To 290 Pounds!" << endl << endl;
        cout << "----Elite----: 291 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 intermediate
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getBench() >= 175) && person->getBench() <= 230)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 127 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 128 Pounds To 174 Pounds!" << endl << endl;
        cout << "----Intermediate----: 175 Pounds To 230 Pounds!" << endl << endl;
        cout << "----Advaced----: 231 Pounds To 290 Pounds!" << endl << endl;
        cout << "----Elite----: 291 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 advanced
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getBench() >= 231) && person->getBench() <= 290)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 127 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 128 Pounds To 174 Pounds!" << endl << endl;
        cout << "----Intermediate----: 175 Pounds To 230 Pounds!" << endl << endl;
        cout << "----Advaced----: 231 Pounds To 290 Pounds!" << endl << endl;
        cout << "----Elite----: 291 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 elite
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getBench() >= 291))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 127 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 128 Pounds To 174 Pounds!" << endl << endl;
        cout << "----Intermediate----: 175 Pounds To 230 Pounds!" << endl << endl;
        cout << "----Advaced----: 231 Pounds To 290 Pounds!" << endl << endl;
        cout << "----Elite----: 291 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //151-160 beginner
    else  if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && (person->getBench() <= 138)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 138 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 139 Pounds To 187 Pounds!" << endl << endl;
        cout << "----Intermediate----: 188 Pounds To 244 Pounds!" << endl << endl;
        cout << "----Advaced----: 245 Pounds To 306 Pounds!" << endl << endl;
        cout << "----Elite----: 307 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 novice
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getBench() >= 139) && person->getBench() <= 187)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 138 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 139 Pounds To 187 Pounds!" << endl << endl;
        cout << "----Intermediate----: 188 Pounds To 244 Pounds!" << endl << endl;
        cout << "----Advaced----: 245 Pounds To 306 Pounds!" << endl << endl;
        cout << "----Elite----: 307 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 intermediate
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getBench() >= 188) && person->getBench() <= 244)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 138 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 139 Pounds To 187 Pounds!" << endl << endl;
        cout << "----Intermediate----: 188 Pounds To 244 Pounds!" << endl << endl;
        cout << "----Advaced----: 245 Pounds To 306 Pounds!" << endl << endl;
        cout << "----Elite----: 307 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 advanced
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getBench() >= 245) && person->getBench() <= 306)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 138 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 139 Pounds To 187 Pounds!" << endl << endl;
        cout << "----Intermediate----: 188 Pounds To 244 Pounds!" << endl << endl;
        cout << "----Advaced----: 245 Pounds To 306 Pounds!" << endl << endl;
        cout << "----Elite----: 307 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 elite
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getBench() >= 307))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 138 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 139 Pounds To 187 Pounds!" << endl << endl;
        cout << "----Intermediate----: 188 Pounds To 244 Pounds!" << endl << endl;
        cout << "----Advaced----: 245 Pounds To 306 Pounds!" << endl << endl;
        cout << "----Elite----: 307 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //161-170 beginner
    else  if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && (person->getBench() <= 148)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 148 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 149 Pounds To 200 Pounds!" << endl << endl;
        cout << "----Intermediate----: 201 Pounds To 259 Pounds!" << endl << endl;
        cout << "----Advaced----: 260 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Elite----: 323 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 novice
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getBench() >= 149) && person->getBench() <= 200)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 148 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 149 Pounds To 200 Pounds!" << endl << endl;
        cout << "----Intermediate----: 201 Pounds To 259 Pounds!" << endl << endl;
        cout << "----Advaced----: 260 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Elite----: 323 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 intermediate
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getBench() >= 201) && person->getBench() <= 259)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 148 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 149 Pounds To 200 Pounds!" << endl << endl;
        cout << "----Intermediate----: 201 Pounds To 259 Pounds!" << endl << endl;
        cout << "----Advaced----: 260 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Elite----: 323 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 advanced
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getBench() >= 260) && person->getBench() <= 322)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 148 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 149 Pounds To 200 Pounds!" << endl << endl;
        cout << "----Intermediate----: 201 Pounds To 259 Pounds!" << endl << endl;
        cout << "----Advaced----: 260 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Elite----: 323 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 elite
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getBench() >= 323))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 148 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 149 Pounds To 200 Pounds!" << endl << endl;
        cout << "----Intermediate----: 201 Pounds To 259 Pounds!" << endl << endl;
        cout << "----Advaced----: 260 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Elite----: 323 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //171-180 beginner
    else  if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && (person->getBench() <= 159)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 159 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 160 Pounds To 212 Pounds!" << endl << endl;
        cout << "----Intermediate----: 213 Pounds To 273 Pounds!" << endl << endl;
        cout << "----Advaced----: 274 Pounds To 337 Pounds!" << endl << endl;
        cout << "----Elite----: 338 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 novice
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getBench() >= 160) && person->getBench() <= 212)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 159 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 160 Pounds To 212 Pounds!" << endl << endl;
        cout << "----Intermediate----: 213 Pounds To 273 Pounds!" << endl << endl;
        cout << "----Advaced----: 274 Pounds To 337 Pounds!" << endl << endl;
        cout << "----Elite----: 338 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 intermediate
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getBench() >= 213) && person->getBench() <= 273)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 159 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 160 Pounds To 212 Pounds!" << endl << endl;
        cout << "----Intermediate----: 213 Pounds To 273 Pounds!" << endl << endl;
        cout << "----Advaced----: 274 Pounds To 337 Pounds!" << endl << endl;
        cout << "----Elite----: 338 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 advanced
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getBench() >= 274) && person->getBench() <= 337)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 159 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 160 Pounds To 212 Pounds!" << endl << endl;
        cout << "----Intermediate----: 213 Pounds To 273 Pounds!" << endl << endl;
        cout << "----Advaced----: 274 Pounds To 337 Pounds!" << endl << endl;
        cout << "----Elite----: 338 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 elite
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getBench() >= 338))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 159 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 160 Pounds To 212 Pounds!" << endl << endl;
        cout << "----Intermediate----: 213 Pounds To 273 Pounds!" << endl << endl;
        cout << "----Advaced----: 274 Pounds To 337 Pounds!" << endl << endl;
        cout << "----Elite----: 338 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //181-190 beginner
    else  if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && (person->getBench() <= 169)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 169 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 170 Pounds To 224 Pounds!" << endl << endl;
        cout << "----Intermediate----: 225 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Advaced----: 287 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Elite----: 354 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 novice
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getBench() >= 170) && person->getBench() <= 224)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 169 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 170 Pounds To 224 Pounds!" << endl << endl;
        cout << "----Intermediate----: 225 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Advaced----: 287 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Elite----: 354 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 intermediate
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getBench() >= 225) && person->getBench() <= 286)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 169 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 170 Pounds To 224 Pounds!" << endl << endl;
        cout << "----Intermediate----: 225 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Advaced----: 287 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Elite----: 354 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 advanced
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getBench() >= 287) && person->getBench() <= 353)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 169 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 170 Pounds To 224 Pounds!" << endl << endl;
        cout << "----Intermediate----: 225 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Advaced----: 287 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Elite----: 354 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 elite
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getBench() >= 354))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 169 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 170 Pounds To 224 Pounds!" << endl << endl;
        cout << "----Intermediate----: 225 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Advaced----: 287 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Elite----: 354 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //191-200 beginner
    else  if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && (person->getBench() <= 179)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 179 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 180 Pounds To 235 Pounds!" << endl << endl;
        cout << "----Intermediate----: 236 Pounds To 299 Pounds!" << endl << endl;
        cout << "----Advaced----: 300 Pounds To 367 Pounds!" << endl << endl;
        cout << "----Elite----: 368 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 novice
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getBench() >= 180) && person->getBench() <= 235)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 179 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 180 Pounds To 235 Pounds!" << endl << endl;
        cout << "----Intermediate----: 236 Pounds To 299 Pounds!" << endl << endl;
        cout << "----Advaced----: 300 Pounds To 367 Pounds!" << endl << endl;
        cout << "----Elite----: 368 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 intermediate
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getBench() >= 236) && person->getBench() <= 299)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 179 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 180 Pounds To 235 Pounds!" << endl << endl;
        cout << "----Intermediate----: 236 Pounds To 299 Pounds!" << endl << endl;
        cout << "----Advaced----: 300 Pounds To 367 Pounds!" << endl << endl;
        cout << "----Elite----: 368 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 advanced
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getBench() >= 300) && person->getBench() <= 367)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 179 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 180 Pounds To 235 Pounds!" << endl << endl;
        cout << "----Intermediate----: 236 Pounds To 299 Pounds!" << endl << endl;
        cout << "----Advaced----: 300 Pounds To 367 Pounds!" << endl << endl;
        cout << "----Elite----: 368 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 elite
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getBench() >= 368))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 179 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 180 Pounds To 235 Pounds!" << endl << endl;
        cout << "----Intermediate----: 236 Pounds To 299 Pounds!" << endl << endl;
        cout << "----Advaced----: 300 Pounds To 367 Pounds!" << endl << endl;
        cout << "----Elite----: 368 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //201-above beginner
    else  if((person->getWeight() >= 201) && (person->getBench() <= 189)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 189 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 190 Pounds To 246 Pounds!" << endl << endl;
        cout << "----Intermediate----: 247 Pounds To 312 Pounds!" << endl << endl;
        cout << "----Advaced----: 313 Pounds To 381 Pounds!" << endl << endl;
        cout << "----Elite----: 382 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above novice
    else if((person->getWeight() >= 201) && ((person->getBench() >= 190) && person->getBench() <= 246)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 189 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 190 Pounds To 246 Pounds!" << endl << endl;
        cout << "----Intermediate----: 247 Pounds To 312 Pounds!" << endl << endl;
        cout << "----Advaced----: 313 Pounds To 381 Pounds!" << endl << endl;
        cout << "----Elite----: 382 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above intermediate
    else if((person->getWeight() >= 201) && ((person->getBench() >= 247) && person->getBench() <= 312)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 189 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 190 Pounds To 246 Pounds!" << endl << endl;
        cout << "----Intermediate----: 247 Pounds To 312 Pounds!" << endl << endl;
        cout << "----Advaced----: 313 Pounds To 381 Pounds!" << endl << endl;
        cout << "----Elite----: 382 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above advanced
    else if((person->getWeight() >= 201) && ((person->getBench() >= 313) && person->getBench() <= 381)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 189 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 190 Pounds To 246 Pounds!" << endl << endl;
        cout << "----Intermediate----: 247 Pounds To 312 Pounds!" << endl << endl;
        cout << "----Advaced----: 313 Pounds To 381 Pounds!" << endl << endl;
        cout << "----Elite----: 382 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above elite
    else if((person->getWeight() >= 201) && ((person->getBench() >= 382))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Bench Press PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getBench()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Bench Press PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 189 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 190 Pounds To 246 Pounds!" << endl << endl;
        cout << "----Intermediate----: 247 Pounds To 312 Pounds!" << endl << endl;
        cout << "----Advaced----: 313 Pounds To 381 Pounds!" << endl << endl;
        cout << "----Elite----: 382 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    


    


    //110-below/ 111-120/ 121-130/ 131-140/ 141-150/ 151-160/ 161-170/ 171-180/ 181-190/ 191-200/ 201-above/

    return false;
}

bool manager::squat(persons* person){

    cout << endl << "..................................................................................... Squat PR Ranking: ..................................................................................." << endl << endl;
    

        
        
    cout << "Here Are Your Stats:" << endl << endl;  
    cout << "----User Name----: " << person->getName() << endl << endl;
    cout << "----Squat PR----: " << person->getSquat() << endl << endl;
    cout << "----Weight----: " << person->getWeight() << endl << endl;
    
    cout << "Enter Any Key To Test Your Squat PR Ranking Or Enter Q To Quit:" << endl << endl;

      
    string choice;
    cin >> choice;

    if((choice =="q") || (choice == "Q")){
        return false;
    }

    cout << endl << "Calculating Your Squat PR Ranking Please Wait....." << endl << endl;
    sleep(3);

    //110-below beginner
    if((person->getWeight() <= 110) && (person->getSquat() <= 109)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 109 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 110 Pounds To 160 Pounds!" << endl << endl;
        cout << "----Intermediate----: 161 Pounds To 220 Pounds!" << endl << endl;
        cout << "----Advaced----: 221 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Elite----: 287 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below novice
    else if((person->getWeight() <= 110) && ((person->getSquat() >= 110) && person->getSquat() <= 160)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 109 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 110 Pounds To 160 Pounds!" << endl << endl;
        cout << "----Intermediate----: 161 Pounds To 220 Pounds!" << endl << endl;
        cout << "----Advaced----: 221 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Elite----: 287 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below intermediate
    else if((person->getWeight() <= 110) && ((person->getSquat() >= 161) && person->getSquat() <= 220)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 109 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 110 Pounds To 160 Pounds!" << endl << endl;
        cout << "----Intermediate----: 161 Pounds To 220 Pounds!" << endl << endl;
        cout << "----Advaced----: 221 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Elite----: 287 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below advanced
    else if((person->getWeight() <= 110) && ((person->getSquat() >= 221) && person->getSquat() <= 286)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 109 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 110 Pounds To 160 Pounds!" << endl << endl;
        cout << "----Intermediate----: 161 Pounds To 220 Pounds!" << endl << endl;
        cout << "----Advaced----: 221 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Elite----: 287 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below elite
    else if((person->getWeight() <= 110) && ((person->getSquat() >= 287))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 109 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 110 Pounds To 160 Pounds!" << endl << endl;
        cout << "----Intermediate----: 161 Pounds To 220 Pounds!" << endl << endl;
        cout << "----Advaced----: 221 Pounds To 286 Pounds!" << endl << endl;
        cout << "----Elite----: 287 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //111-120 beginner
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && (person->getSquat() <= 125)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 125 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 126 Pounds To 178 Pounds!" << endl << endl;
        cout << "----Intermediate----: 179 Pounds To 242 Pounds!" << endl << endl;
        cout << "----Advaced----: 243 Pounds To 311 Pounds!" << endl << endl;
        cout << "----Elite----: 312 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 novice
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getSquat() >= 126) && person->getSquat() <= 178)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 125 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 126 Pounds To 178 Pounds!" << endl << endl;
        cout << "----Intermediate----: 179 Pounds To 242 Pounds!" << endl << endl;
        cout << "----Advaced----: 243 Pounds To 311 Pounds!" << endl << endl;
        cout << "----Elite----: 312 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 intermediate
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getSquat() >= 179) && person->getSquat() <= 242)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 125 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 126 Pounds To 178 Pounds!" << endl << endl;
        cout << "----Intermediate----: 179 Pounds To 242 Pounds!" << endl << endl;
        cout << "----Advaced----: 243 Pounds To 311 Pounds!" << endl << endl;
        cout << "----Elite----: 312 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 advanced
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getSquat() >= 243) && person->getSquat() <= 311)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 125 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 126 Pounds To 178 Pounds!" << endl << endl;
        cout << "----Intermediate----: 179 Pounds To 242 Pounds!" << endl << endl;
        cout << "----Advaced----: 243 Pounds To 311 Pounds!" << endl << endl;
        cout << "----Elite----: 312 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 elite
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getSquat() >= 312))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 125 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 126 Pounds To 178 Pounds!" << endl << endl;
        cout << "----Intermediate----: 179 Pounds To 242 Pounds!" << endl << endl;
        cout << "----Advaced----: 243 Pounds To 311 Pounds!" << endl << endl;
        cout << "----Elite----: 312 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //121-130 beginner
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && (person->getSquat() <= 140)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 140 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 141 Pounds To 197 Pounds!" << endl << endl;
        cout << "----Intermediate----: 198 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 335 Pounds!" << endl << endl;
        cout << "----Elite----: 336 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 novice
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getSquat() >= 141) && person->getSquat() <= 197)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 140 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 141 Pounds To 197 Pounds!" << endl << endl;
        cout << "----Intermediate----: 198 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 335 Pounds!" << endl << endl;
        cout << "----Elite----: 336 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 intermediate
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getSquat() >= 198) && person->getSquat() <= 263)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 140 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 141 Pounds To 197 Pounds!" << endl << endl;
        cout << "----Intermediate----: 198 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 335 Pounds!" << endl << endl;
        cout << "----Elite----: 336 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 advanced
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getSquat() >= 264) && person->getSquat() <= 335)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 140 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 141 Pounds To 197 Pounds!" << endl << endl;
        cout << "----Intermediate----: 198 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 335 Pounds!" << endl << endl;
        cout << "----Elite----: 336 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 elite
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getSquat() >= 336))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 140 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 141 Pounds To 197 Pounds!" << endl << endl;
        cout << "----Intermediate----: 198 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 335 Pounds!" << endl << endl;
        cout << "----Elite----: 336 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //131-140 beginner
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && (person->getSquat() <= 155)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 214 Pounds!" << endl << endl;
        cout << "----Intermediate----: 215 Pounds To 283 Pounds!" << endl << endl;
        cout << "----Advaced----: 284 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Elite----: 359 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 novice
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getSquat() >= 156) && person->getSquat() <= 214)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 214 Pounds!" << endl << endl;
        cout << "----Intermediate----: 215 Pounds To 283 Pounds!" << endl << endl;
        cout << "----Advaced----: 284 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Elite----: 359 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 intermediate
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getSquat() >= 215) && person->getSquat() <= 283)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 214 Pounds!" << endl << endl;
        cout << "----Intermediate----: 215 Pounds To 283 Pounds!" << endl << endl;
        cout << "----Advaced----: 284 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Elite----: 359 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 advanced
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getSquat() >= 284) && person->getSquat() <= 358)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 214 Pounds!" << endl << endl;
        cout << "----Intermediate----: 215 Pounds To 283 Pounds!" << endl << endl;
        cout << "----Advaced----: 284 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Elite----: 359 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 elite
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getSquat() >= 359))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 214 Pounds!" << endl << endl;
        cout << "----Intermediate----: 215 Pounds To 283 Pounds!" << endl << endl;
        cout << "----Advaced----: 284 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Elite----: 359 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //141-150 beginner
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && (person->getSquat() <= 170)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 170 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 171 Pounds To 231 Pounds!" << endl << endl;
        cout << "----Intermediate----: 232 Pounds To 303 Pounds!" << endl << endl;
        cout << "----Advaced----: 304 Pounds To 380 Pounds!" << endl << endl;
        cout << "----Elite----: 381 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 novice
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getSquat() >= 171) && person->getSquat() <= 231)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 170 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 171 Pounds To 231 Pounds!" << endl << endl;
        cout << "----Intermediate----: 232 Pounds To 303 Pounds!" << endl << endl;
        cout << "----Advaced----: 304 Pounds To 380 Pounds!" << endl << endl;
        cout << "----Elite----: 381 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 intermediate
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getSquat() >= 232) && person->getSquat() <= 303)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 170 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 171 Pounds To 231 Pounds!" << endl << endl;
        cout << "----Intermediate----: 232 Pounds To 303 Pounds!" << endl << endl;
        cout << "----Advaced----: 304 Pounds To 380 Pounds!" << endl << endl;
        cout << "----Elite----: 381 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 advanced
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getSquat() >= 304) && person->getSquat() <= 380)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 170 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 171 Pounds To 231 Pounds!" << endl << endl;
        cout << "----Intermediate----: 232 Pounds To 303 Pounds!" << endl << endl;
        cout << "----Advaced----: 304 Pounds To 380 Pounds!" << endl << endl;
        cout << "----Elite----: 381 Pounds And Above!" << endl << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 elite
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getSquat() >= 381))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 170 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 171 Pounds To 231 Pounds!" << endl << endl;
        cout << "----Intermediate----: 232 Pounds To 303 Pounds!" << endl << endl;
        cout << "----Advaced----: 304 Pounds To 380 Pounds!" << endl << endl;
        cout << "----Elite----: 381 Pounds And Above!" << endl << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //151-160 beginner
    else  if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && (person->getSquat() <= 184)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 184 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 185 Pounds To 248 Pounds!" << endl << endl;
        cout << "----Intermediate----: 249 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Advaced----: 323 Pounds To 401 Pounds!" << endl << endl;
        cout << "----Elite----: 402 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 novice
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getSquat() >= 185) && person->getSquat() <= 248)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 184 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 185 Pounds To 248 Pounds!" << endl << endl;
        cout << "----Intermediate----: 249 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Advaced----: 323 Pounds To 401 Pounds!" << endl << endl;
        cout << "----Elite----: 402 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 intermediate
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getSquat() >= 249) && person->getSquat() <= 322)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 184 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 185 Pounds To 248 Pounds!" << endl << endl;
        cout << "----Intermediate----: 249 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Advaced----: 323 Pounds To 401 Pounds!" << endl << endl;
        cout << "----Elite----: 402 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 advanced
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getSquat() >= 323) && person->getSquat() <= 401)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 184 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 185 Pounds To 248 Pounds!" << endl << endl;
        cout << "----Intermediate----: 249 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Advaced----: 323 Pounds To 401 Pounds!" << endl << endl;
        cout << "----Elite----: 402 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 elite
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getSquat() >= 402))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 184 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 185 Pounds To 248 Pounds!" << endl << endl;
        cout << "----Intermediate----: 249 Pounds To 322 Pounds!" << endl << endl;
        cout << "----Advaced----: 323 Pounds To 401 Pounds!" << endl << endl;
        cout << "----Elite----: 402 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //161-170 beginner
    else  if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && (person->getSquat() <= 198)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 198 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 199 Pounds To 264 Pounds!" << endl << endl;
        cout << "----Intermediate----: 265 Pounds To 340 Pounds!" << endl << endl;
        cout << "----Advaced----: 341 Pounds To 421 Pounds!" << endl << endl;
        cout << "----Elite----: 422 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 novice
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getSquat() >= 199) && person->getSquat() <= 264)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 198 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 199 Pounds To 264 Pounds!" << endl << endl;
        cout << "----Intermediate----: 265 Pounds To 340 Pounds!" << endl << endl;
        cout << "----Advaced----: 341 Pounds To 421 Pounds!" << endl << endl;
        cout << "----Elite----: 422 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 intermediate
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getSquat() >= 265) && person->getSquat() <= 340)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 198 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 199 Pounds To 264 Pounds!" << endl << endl;
        cout << "----Intermediate----: 265 Pounds To 340 Pounds!" << endl << endl;
        cout << "----Advaced----: 341 Pounds To 421 Pounds!" << endl << endl;
        cout << "----Elite----: 422 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 advanced
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getSquat() >= 341) && person->getSquat() <= 421)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 198 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 199 Pounds To 264 Pounds!" << endl << endl;
        cout << "----Intermediate----: 265 Pounds To 340 Pounds!" << endl << endl;
        cout << "----Advaced----: 341 Pounds To 421 Pounds!" << endl << endl;
        cout << "----Elite----: 422 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 elite
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getSquat() >= 422))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 198 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 199 Pounds To 264 Pounds!" << endl << endl;
        cout << "----Intermediate----: 265 Pounds To 340 Pounds!" << endl << endl;
        cout << "----Advaced----: 341 Pounds To 421 Pounds!" << endl << endl;
        cout << "----Elite----: 422 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //171-180 beginner
    else  if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && (person->getSquat() <= 211)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 211 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 212 Pounds To 280 Pounds!" << endl << endl;
        cout << "----Intermediate----: 281 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Advaced----: 359 Pounds To 441 Pounds!" << endl << endl;
        cout << "----Elite----: 442 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 novice
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getSquat() >= 212) && person->getSquat() <= 280)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 211 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 212 Pounds To 280 Pounds!" << endl << endl;
        cout << "----Intermediate----: 281 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Advaced----: 359 Pounds To 441 Pounds!" << endl << endl;
        cout << "----Elite----: 442 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 intermediate
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getSquat() >= 281) && person->getSquat() <= 358)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 211 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 212 Pounds To 280 Pounds!" << endl << endl;
        cout << "----Intermediate----: 281 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Advaced----: 359 Pounds To 441 Pounds!" << endl << endl;
        cout << "----Elite----: 442 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 advanced
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getSquat() >= 359) && person->getSquat() <= 441)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 211 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 212 Pounds To 280 Pounds!" << endl << endl;
        cout << "----Intermediate----: 281 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Advaced----: 359 Pounds To 441 Pounds!" << endl << endl;
        cout << "----Elite----: 442 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 elite
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getSquat() >= 442))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 211 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 212 Pounds To 280 Pounds!" << endl << endl;
        cout << "----Intermediate----: 281 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Advaced----: 359 Pounds To 441 Pounds!" << endl << endl;
        cout << "----Elite----: 442 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //181-190 beginner
    else  if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && (person->getSquat() <= 225)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 225 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 226 Pounds To 295 Pounds!" << endl << endl;
        cout << "----Intermediate----: 296 Pounds To 375 Pounds!" << endl << endl;
        cout << "----Advaced----: 376 Pounds To 460 Pounds!" << endl << endl;
        cout << "----Elite----: 461 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 novice
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getSquat() >= 226) && person->getSquat() <= 295)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 225 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 226 Pounds To 295 Pounds!" << endl << endl;
        cout << "----Intermediate----: 296 Pounds To 375 Pounds!" << endl << endl;
        cout << "----Advaced----: 376 Pounds To 460 Pounds!" << endl << endl;
        cout << "----Elite----: 461 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 intermediate
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getSquat() >= 296) && person->getSquat() <= 375)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 225 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 226 Pounds To 295 Pounds!" << endl << endl;
        cout << "----Intermediate----: 296 Pounds To 375 Pounds!" << endl << endl;
        cout << "----Advaced----: 376 Pounds To 460 Pounds!" << endl << endl;
        cout << "----Elite----: 461 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 advanced
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getSquat() >= 376) && person->getSquat() <= 460)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 225 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 226 Pounds To 295 Pounds!" << endl << endl;
        cout << "----Intermediate----: 296 Pounds To 375 Pounds!" << endl << endl;
        cout << "----Advaced----: 376 Pounds To 460 Pounds!" << endl << endl;
        cout << "----Elite----: 461 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 elite
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getSquat() >= 461))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 225 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 226 Pounds To 295 Pounds!" << endl << endl;
        cout << "----Intermediate----: 296 Pounds To 375 Pounds!" << endl << endl;
        cout << "----Advaced----: 376 Pounds To 460 Pounds!" << endl << endl;
        cout << "----Elite----: 461 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //191-200 beginner
    else  if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && (person->getSquat() <= 238)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 238 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 239 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Intermediate----: 311 Pounds To 392 Pounds!" << endl << endl;
        cout << "----Advaced----: 393 Pounds To 478 Pounds!" << endl << endl;
        cout << "----Elite----: 479 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 novice
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getSquat() >= 239) && person->getSquat() <= 310)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 238 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 239 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Intermediate----: 311 Pounds To 392 Pounds!" << endl << endl;
        cout << "----Advaced----: 393 Pounds To 478 Pounds!" << endl << endl;
        cout << "----Elite----: 479 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 intermediate
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getSquat() >= 311) && person->getSquat() <= 392)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 238 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 239 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Intermediate----: 311 Pounds To 392 Pounds!" << endl << endl;
        cout << "----Advaced----: 393 Pounds To 478 Pounds!" << endl << endl;
        cout << "----Elite----: 479 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 advanced
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getSquat() >= 393) && person->getSquat() <= 478)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 238 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 239 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Intermediate----: 311 Pounds To 392 Pounds!" << endl << endl;
        cout << "----Advaced----: 393 Pounds To 478 Pounds!" << endl << endl;
        cout << "----Elite----: 479 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 elite
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getSquat() >= 479))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 238 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 239 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Intermediate----: 311 Pounds To 392 Pounds!" << endl << endl;
        cout << "----Advaced----: 393 Pounds To 478 Pounds!" << endl << endl;
        cout << "----Elite----: 479 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //201-above beginner
    else  if((person->getWeight() >= 201) && (person->getSquat() <= 250)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 324 Pounds!" << endl << endl;
        cout << "----Intermediate----: 325 Pounds To 408 Pounds!" << endl << endl;
        cout << "----Advaced----: 409 Pounds To 499 Pounds!" << endl << endl;
        cout << "----Elite----: 500 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above novice
    else if((person->getWeight() >= 201) && ((person->getSquat() >= 251) && person->getSquat() <= 324)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 324 Pounds!" << endl << endl;
        cout << "----Intermediate----: 325 Pounds To 408 Pounds!" << endl << endl;
        cout << "----Advaced----: 409 Pounds To 499 Pounds!" << endl << endl;
        cout << "----Elite----: 500 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above intermediate
    else if((person->getWeight() >= 201) && ((person->getSquat() >= 325) && person->getSquat() <= 408)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 324 Pounds!" << endl << endl;
        cout << "----Intermediate----: 325 Pounds To 408 Pounds!" << endl << endl;
        cout << "----Advaced----: 409 Pounds To 499 Pounds!" << endl << endl;
        cout << "----Elite----: 500 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above advanced
    else if((person->getWeight() >= 201) && ((person->getSquat() >= 409) && person->getSquat() <= 499)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 324 Pounds!" << endl << endl;
        cout << "----Intermediate----: 325 Pounds To 408 Pounds!" << endl << endl;
        cout << "----Advaced----: 409 Pounds To 499 Pounds!" << endl << endl;
        cout << "----Elite----: 500 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above elite
    else if((person->getWeight() >= 201) && ((person->getSquat() >= 500))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Squat PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getSquat()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Squat PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 324 Pounds!" << endl << endl;
        cout << "----Intermediate----: 325 Pounds To 408 Pounds!" << endl << endl;
        cout << "----Advaced----: 409 Pounds To 499 Pounds!" << endl << endl;
        cout << "----Elite----: 500 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }


    return false;
}

bool manager::deadlift(persons* person){

    cout << endl << "................................................................................ Deadlift PR Ranking: ................................................................................" << endl << endl;
    

        
        
    cout << "Here Are Your Stats:" << endl << endl;  
    cout << "----User Name----: " << person->getName() << endl << endl;
    cout << "----Deadlift PR----: " << person->getDeadlift() << endl << endl;
    cout << "----Weight----: " << person->getWeight() << endl << endl;
    
    cout << "Enter Any Key To Test Your Deadlift PR Ranking Or Enter Q To Quit:" << endl << endl;

      
    string choice;
    cin >> choice;

    if((choice =="q") || (choice == "Q")){
        return false;
    }

    cout << endl << "Calculating Your Deadlift PR Ranking Please Wait....." << endl << endl;
    sleep(3);

    //110-below beginner
    if((person->getWeight() <= 110) && (person->getDeadlift() <= 137)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 137 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 138 Pounds To 195 Pounds!" << endl << endl;
        cout << "----Intermediate----: 196 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 338 Pounds!" << endl << endl;
        cout << "----Elite----: 339 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below novice
    else if((person->getWeight() <= 110) && ((person->getDeadlift() >= 138) && person->getDeadlift() <= 195)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 137 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 138 Pounds To 195 Pounds!" << endl << endl;
        cout << "----Intermediate----: 196 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 338 Pounds!" << endl << endl;
        cout << "----Elite----: 339 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below intermediate
    else if((person->getWeight() <= 110) && ((person->getDeadlift() >= 196) && person->getDeadlift() <= 263)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 137 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 138 Pounds To 195 Pounds!" << endl << endl;
        cout << "----Intermediate----: 196 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 338 Pounds!" << endl << endl;
        cout << "----Elite----: 339 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below advanced
    else if((person->getWeight() <= 110) && ((person->getDeadlift() >= 264) && person->getDeadlift() <= 338)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 137 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 138 Pounds To 195 Pounds!" << endl << endl;
        cout << "----Intermediate----: 196 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 338 Pounds!" << endl << endl;
        cout << "----Elite----: 339 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //110-below elite
    else if((person->getWeight() <= 110) && ((person->getDeadlift() >= 339))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 137 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 138 Pounds To 195 Pounds!" << endl << endl;
        cout << "----Intermediate----: 196 Pounds To 263 Pounds!" << endl << endl;
        cout << "----Advaced----: 264 Pounds To 338 Pounds!" << endl << endl;
        cout << "----Elite----: 339 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //111-120 beginner
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && (person->getDeadlift() <= 155)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 216 Pounds!" << endl << endl;
        cout << "----Intermediate----: 217 Pounds To 287 Pounds!" << endl << endl;
        cout << "----Advaced----: 288 Pounds To 365 Pounds!" << endl << endl;
        cout << "----Elite----: 366 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 novice
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getDeadlift() >= 156) && person->getDeadlift() <= 216)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 216 Pounds!" << endl << endl;
        cout << "----Intermediate----: 217 Pounds To 287 Pounds!" << endl << endl;
        cout << "----Advaced----: 288 Pounds To 365 Pounds!" << endl << endl;
        cout << "----Elite----: 366 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 intermediate
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getDeadlift() >= 217) && person->getDeadlift() <= 287)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 216 Pounds!" << endl << endl;
        cout << "----Intermediate----: 217 Pounds To 287 Pounds!" << endl << endl;
        cout << "----Advaced----: 288 Pounds To 365 Pounds!" << endl << endl;
        cout << "----Elite----: 366 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 advanced
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getDeadlift() >= 288) && person->getDeadlift() <= 365)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 216 Pounds!" << endl << endl;
        cout << "----Intermediate----: 217 Pounds To 287 Pounds!" << endl << endl;
        cout << "----Advaced----: 288 Pounds To 365 Pounds!" << endl << endl;
        cout << "----Elite----: 366 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //111-120 elite
    else if(((person->getWeight() >= 111) && (person->getWeight() <= 120)) && ((person->getDeadlift() >= 366))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 155 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 156 Pounds To 216 Pounds!" << endl << endl;
        cout << "----Intermediate----: 217 Pounds To 287 Pounds!" << endl << endl;
        cout << "----Advaced----: 288 Pounds To 365 Pounds!" << endl << endl;
        cout << "----Elite----: 366 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //121-130 beginner
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && (person->getDeadlift() <= 172)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 172 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 173 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Intermediate----: 237 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Advaced----: 311 Pounds To 390 Pounds!" << endl << endl;
        cout << "----Elite----: 391 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 novice
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getDeadlift() >= 173) && person->getDeadlift() <= 236)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 172 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 173 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Intermediate----: 237 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Advaced----: 311 Pounds To 390 Pounds!" << endl << endl;
        cout << "----Elite----: 391 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 intermediate
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getDeadlift() >= 237) && person->getDeadlift() <= 310)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 172 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 173 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Intermediate----: 237 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Advaced----: 311 Pounds To 390 Pounds!" << endl << endl;
        cout << "----Elite----: 391 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 advanced
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getDeadlift() >= 311) && person->getDeadlift() <= 390)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 172 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 173 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Intermediate----: 237 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Advaced----: 311 Pounds To 390 Pounds!" << endl << endl;
        cout << "----Elite----: 391 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //121-130 elite
    else if(((person->getWeight() >= 121) && (person->getWeight() <= 130)) && ((person->getDeadlift() >= 391))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 172 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 173 Pounds To 236 Pounds!" << endl << endl;
        cout << "----Intermediate----: 237 Pounds To 310 Pounds!" << endl << endl;
        cout << "----Advaced----: 311 Pounds To 390 Pounds!" << endl << endl;
        cout << "----Elite----: 391 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //131-140 beginner
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && (person->getDeadlift() <= 188)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 188 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 189 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Intermediate----: 256 Pounds To 332 Pounds!" << endl << endl;
        cout << "----Advaced----: 333 Pounds To 415 Pounds!" << endl << endl;
        cout << "----Elite----: 416 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 novice
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getDeadlift() >= 189) && person->getDeadlift() <= 255)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 188 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 189 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Intermediate----: 256 Pounds To 332 Pounds!" << endl << endl;
        cout << "----Advaced----: 333 Pounds To 415 Pounds!" << endl << endl;
        cout << "----Elite----: 416 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 intermediate
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getDeadlift() >= 256) && person->getDeadlift() <= 332)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 188 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 189 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Intermediate----: 256 Pounds To 332 Pounds!" << endl << endl;
        cout << "----Advaced----: 333 Pounds To 415 Pounds!" << endl << endl;
        cout << "----Elite----: 416 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 advanced
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getDeadlift() >= 333) && person->getDeadlift() <= 415)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 188 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 189 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Intermediate----: 256 Pounds To 332 Pounds!" << endl << endl;
        cout << "----Advaced----: 333 Pounds To 415 Pounds!" << endl << endl;
        cout << "----Elite----: 416 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //131-140 elite
    else if(((person->getWeight() >= 131) && (person->getWeight() <= 140)) && ((person->getDeadlift() >= 416))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 188 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 189 Pounds To 255 Pounds!" << endl << endl;
        cout << "----Intermediate----: 256 Pounds To 332 Pounds!" << endl << endl;
        cout << "----Advaced----: 333 Pounds To 415 Pounds!" << endl << endl;
        cout << "----Elite----: 416 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //141-150 beginner
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && (person->getDeadlift() <= 204)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 204 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 205 Pounds To 274 Pounds!" << endl << endl;
        cout << "----Intermediate----: 275 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Advaced----: 354 Pounds To 439 Pounds!" << endl << endl;
        cout << "----Elite----: 440 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 novice
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getDeadlift() >= 205) && person->getDeadlift() <= 274)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 204 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 205 Pounds To 274 Pounds!" << endl << endl;
        cout << "----Intermediate----: 275 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Advaced----: 354 Pounds To 439 Pounds!" << endl << endl;
        cout << "----Elite----: 440 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 intermediate
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getDeadlift() >= 275) && person->getDeadlift() <= 353)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 204 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 205 Pounds To 274 Pounds!" << endl << endl;
        cout << "----Intermediate----: 275 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Advaced----: 354 Pounds To 439 Pounds!" << endl << endl;
        cout << "----Elite----: 440 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 advanced
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getDeadlift() >= 354) && person->getDeadlift() <= 439)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 204 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 205 Pounds To 274 Pounds!" << endl << endl;
        cout << "----Intermediate----: 275 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Advaced----: 354 Pounds To 439 Pounds!" << endl << endl;
        cout << "----Elite----: 440 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //141-150 elite
    else if(((person->getWeight() >= 141) && (person->getWeight() <= 150)) && ((person->getDeadlift() >= 440))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 204 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 205 Pounds To 274 Pounds!" << endl << endl;
        cout << "----Intermediate----: 275 Pounds To 353 Pounds!" << endl << endl;
        cout << "----Advaced----: 354 Pounds To 439 Pounds!" << endl << endl;
        cout << "----Elite----: 440 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //151-160 beginner
    else  if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && (person->getDeadlift() <= 220)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 220 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 221 Pounds To 292 Pounds!" << endl << endl;
        cout << "----Intermediate----: 293 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Advaced----: 374 Pounds To 461 Pounds!" << endl << endl;
        cout << "----Elite----: 462 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 novice
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getDeadlift() >= 221) && person->getDeadlift() <= 292)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 220 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 221 Pounds To 292 Pounds!" << endl << endl;
        cout << "----Intermediate----: 293 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Advaced----: 374 Pounds To 461 Pounds!" << endl << endl;
        cout << "----Elite----: 462 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 intermediate
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getDeadlift() >= 293) && person->getDeadlift() <= 374)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 220 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 221 Pounds To 292 Pounds!" << endl << endl;
        cout << "----Intermediate----: 293 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Advaced----: 374 Pounds To 461 Pounds!" << endl << endl;
        cout << "----Elite----: 462 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 advanced
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getDeadlift() >= 375) && person->getDeadlift() <= 461)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 220 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 221 Pounds To 292 Pounds!" << endl << endl;
        cout << "----Intermediate----: 293 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Advaced----: 374 Pounds To 461 Pounds!" << endl << endl;
        cout << "----Elite----: 462 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //151-160 elite
    else if(((person->getWeight() >= 151) && (person->getWeight() <= 160)) && ((person->getDeadlift() >= 462))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 220 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 221 Pounds To 292 Pounds!" << endl << endl;
        cout << "----Intermediate----: 293 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Advaced----: 374 Pounds To 461 Pounds!" << endl << endl;
        cout << "----Elite----: 462 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //161-170 beginner
    else  if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && (person->getDeadlift() <= 235)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 235 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 236 Pounds To 309 Pounds!" << endl << endl;
        cout << "----Intermediate----: 310 Pounds To 393 Pounds!" << endl << endl;
        cout << "----Advaced----: 394 Pounds To 483 Pounds!" << endl << endl;
        cout << "----Elite----: 484 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 novice
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getDeadlift() >= 236) && person->getDeadlift() <= 309)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 235 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 236 Pounds To 309 Pounds!" << endl << endl;
        cout << "----Intermediate----: 310 Pounds To 393 Pounds!" << endl << endl;
        cout << "----Advaced----: 394 Pounds To 483 Pounds!" << endl << endl;
        cout << "----Elite----: 484 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 intermediate
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getDeadlift() >= 310) && person->getDeadlift() <= 393)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 235 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 236 Pounds To 309 Pounds!" << endl << endl;
        cout << "----Intermediate----: 310 Pounds To 393 Pounds!" << endl << endl;
        cout << "----Advaced----: 394 Pounds To 483 Pounds!" << endl << endl;
        cout << "----Elite----: 484 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 advanced
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getDeadlift() >= 394) && person->getDeadlift() <= 483)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 235 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 236 Pounds To 309 Pounds!" << endl << endl;
        cout << "----Intermediate----: 310 Pounds To 393 Pounds!" << endl << endl;
        cout << "----Advaced----: 394 Pounds To 483 Pounds!" << endl << endl;
        cout << "----Elite----: 484 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //161-170 elite
    else if(((person->getWeight() >= 161) && (person->getWeight() <= 170)) && ((person->getDeadlift() >= 484))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 235 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 236 Pounds To 309 Pounds!" << endl << endl;
        cout << "----Intermediate----: 310 Pounds To 393 Pounds!" << endl << endl;
        cout << "----Advaced----: 394 Pounds To 483 Pounds!" << endl << endl;
        cout << "----Elite----: 484 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //171-180 beginner
    else  if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && (person->getDeadlift() <= 250)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 326 Pounds!" << endl << endl;
        cout << "----Intermediate----: 327 Pounds To 412 Pounds!" << endl << endl;
        cout << "----Advaced----: 413 Pounds To 504 Pounds!" << endl << endl;
        cout << "----Elite----: 505 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 novice
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getDeadlift() >= 251) && person->getDeadlift() <= 326)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 326 Pounds!" << endl << endl;
        cout << "----Intermediate----: 327 Pounds To 412 Pounds!" << endl << endl;
        cout << "----Advaced----: 413 Pounds To 504 Pounds!" << endl << endl;
        cout << "----Elite----: 505 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 intermediate
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getDeadlift() >= 327) && person->getDeadlift() <= 412)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 326 Pounds!" << endl << endl;
        cout << "----Intermediate----: 327 Pounds To 412 Pounds!" << endl << endl;
        cout << "----Advaced----: 413 Pounds To 504 Pounds!" << endl << endl;
        cout << "----Elite----: 505 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 advanced
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getDeadlift() >= 413) && person->getDeadlift() <= 504)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 326 Pounds!" << endl << endl;
        cout << "----Intermediate----: 327 Pounds To 412 Pounds!" << endl << endl;
        cout << "----Advaced----: 413 Pounds To 504 Pounds!" << endl << endl;
        cout << "----Elite----: 505 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //171-180 elite
    else if(((person->getWeight() >= 171) && (person->getWeight() <= 180)) && ((person->getDeadlift() >= 505))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 250 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 251 Pounds To 326 Pounds!" << endl << endl;
        cout << "----Intermediate----: 327 Pounds To 412 Pounds!" << endl << endl;
        cout << "----Advaced----: 413 Pounds To 504 Pounds!" << endl << endl;
        cout << "----Elite----: 505 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //181-190 beginner
    else  if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && (person->getDeadlift() <= 264)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 264 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 265 Pounds To 342 Pounds!" << endl << endl;
        cout << "----Intermediate----: 343 Pounds To 431 Pounds!" << endl << endl;
        cout << "----Advaced----: 432 Pounds To 524 Pounds!" << endl << endl;
        cout << "----Elite----: 525 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 novice
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getDeadlift() >= 265) && person->getDeadlift() <= 342)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 264 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 265 Pounds To 342 Pounds!" << endl << endl;
        cout << "----Intermediate----: 343 Pounds To 431 Pounds!" << endl << endl;
        cout << "----Advaced----: 432 Pounds To 524 Pounds!" << endl << endl;
        cout << "----Elite----: 525 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 intermediate
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getDeadlift() >= 343) && person->getDeadlift() <= 431)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 264 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 265 Pounds To 342 Pounds!" << endl << endl;
        cout << "----Intermediate----: 343 Pounds To 431 Pounds!" << endl << endl;
        cout << "----Advaced----: 432 Pounds To 524 Pounds!" << endl << endl;
        cout << "----Elite----: 525 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 advanced
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getDeadlift() >= 432) && person->getDeadlift() <= 524)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 264 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 265 Pounds To 342 Pounds!" << endl << endl;
        cout << "----Intermediate----: 343 Pounds To 431 Pounds!" << endl << endl;
        cout << "----Advaced----: 432 Pounds To 524 Pounds!" << endl << endl;
        cout << "----Elite----: 525 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //181-190 elite
    else if(((person->getWeight() >= 181) && (person->getWeight() <= 190)) && ((person->getDeadlift() >= 525))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 264 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 265 Pounds To 342 Pounds!" << endl << endl;
        cout << "----Intermediate----: 343 Pounds To 431 Pounds!" << endl << endl;
        cout << "----Advaced----: 432 Pounds To 524 Pounds!" << endl << endl;
        cout << "----Elite----: 525 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //191-200 beginner
    else  if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && (person->getDeadlift() <= 278)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 278 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 279 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Intermediate----: 359 Pounds To 448 Pounds!" << endl << endl;
        cout << "----Advaced----: 449 Pounds To 544 Pounds!" << endl << endl;
        cout << "----Elite----: 545 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 novice
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getDeadlift() >= 279) && person->getDeadlift() <= 358)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 278 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 279 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Intermediate----: 359 Pounds To 448 Pounds!" << endl << endl;
        cout << "----Advaced----: 449 Pounds To 544 Pounds!" << endl << endl;
        cout << "----Elite----: 545 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 intermediate
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getDeadlift() >= 359) && person->getDeadlift() <= 448)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 278 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 279 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Intermediate----: 359 Pounds To 448 Pounds!" << endl << endl;
        cout << "----Advaced----: 449 Pounds To 544 Pounds!" << endl << endl;
        cout << "----Elite----: 545 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 advanced
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getDeadlift() >= 449) && person->getDeadlift() <= 544)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 278 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 279 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Intermediate----: 359 Pounds To 448 Pounds!" << endl << endl;
        cout << "----Advaced----: 449 Pounds To 544 Pounds!" << endl << endl;
        cout << "----Elite----: 545 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //191-200 elite
    else if(((person->getWeight() >= 191) && (person->getWeight() <= 200)) && ((person->getDeadlift() >= 545))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 278 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 279 Pounds To 358 Pounds!" << endl << endl;
        cout << "----Intermediate----: 359 Pounds To 448 Pounds!" << endl << endl;
        cout << "----Advaced----: 449 Pounds To 544 Pounds!" << endl << endl;
        cout << "----Elite----: 545 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }

    //201-above beginner
    else  if((person->getWeight() >= 201) && (person->getDeadlift() <= 291)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Beginner!" << endl << endl;
        cout << "You Are Stronger Than 5% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 291 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 292 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Intermediate----: 374 Pounds To 466 Pounds!" << endl << endl;
        cout << "----Advaced----: 467 Pounds To 563 Pounds!" << endl << endl;
        cout << "----Elite----: 564 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above novice
    else if((person->getWeight() >= 201) && ((person->getDeadlift() >= 292) && person->getDeadlift() <= 373)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Novice!" << endl << endl;
        cout << "You Are Stronger Than 20% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 291 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 292 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Intermediate----: 374 Pounds To 466 Pounds!" << endl << endl;
        cout << "----Advaced----: 467 Pounds To 563 Pounds!" << endl << endl;
        cout << "----Elite----: 564 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above intermediate
    else if((person->getWeight() >= 201) && ((person->getDeadlift() >= 374) && person->getDeadlift() <= 466)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Intermediate!" << endl << endl;
        cout << "You Are Stronger Than 50% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 291 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 292 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Intermediate----: 374 Pounds To 466 Pounds!" << endl << endl;
        cout << "----Advaced----: 467 Pounds To 563 Pounds!" << endl << endl;
        cout << "----Elite----: 564 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above advanced
    else if((person->getWeight() >= 201) && ((person->getDeadlift() >= 467) && person->getDeadlift() <= 563)){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Advanced!" << endl << endl;
        cout << "You Are Stronger Than 80% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 291 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 292 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Intermediate----: 374 Pounds To 466 Pounds!" << endl << endl;
        cout << "----Advaced----: 467 Pounds To 563 Pounds!" << endl << endl;
        cout << "----Elite----: 564 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    //201-above elite
    else if((person->getWeight() >= 201) && ((person->getDeadlift() >= 564))){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "Your Deadlift PR Ranking Is: Elite!" << endl << endl;
        cout << "You Are Stronger Than 95% Of People At " << person->getWeight() << " Pounds!" << endl << endl;
        double result = static_cast<double>(person->getDeadlift()) / person->getWeight();
        cout << fixed << setprecision(1) << "You Can Lift " << result << " Times Your Body Weight" << endl << endl;
        cout << "Here Are All Of The Deadlift PR Rankings At " << person->getWeight() << " Pounds:" << endl << endl;
        cout << "----Beginner----: 291 Pounds And Below!" << endl << endl;
        cout << "----Novice----: 292 Pounds To 373 Pounds!" << endl << endl;
        cout << "----Intermediate----: 374 Pounds To 466 Pounds!" << endl << endl;
        cout << "----Advaced----: 467 Pounds To 563 Pounds!" << endl << endl;
        cout << "----Elite----: 564 Pounds And Above!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }


    return false;
}

bool manager::one(persons* person){

    cout << endl << "....................................................................................... The 1% Test: ......................................................................................" << endl << endl;
    cout << "To Be In The Top 1% Of Humanity, You Need To Be Able To Bench Press 1.5X Your Body Weight, Squat 2.5X Your Body Weight, And Deadlift 3X Your Body Weight." << endl << endl;

    cout << "Let's See If You Qualify For This Incredible Achievment!" << endl << endl;

    cout << "Here Are Your Lift PR's:" << endl << endl;
    cout << "----Bench Press PR----: " << person->getBench() << endl << endl;
    cout << "----Squat PR----: " << person->getSquat() << endl << endl;
    cout << "----Deadlift PR----: " << person->getDeadlift() << endl << endl;

    double b = static_cast<double>(person->getBench()) / person->getWeight();
    double s = static_cast<double>(person->getSquat()) / person->getWeight();
    double d = static_cast<double>(person->getDeadlift()) / person->getWeight();


    cout << "Enter Any Key To See If You Are In The Top 1% Of All Of Man Kind Or Enter Q To Quit" << endl << endl;

    string o;
    cin >> o;

    if((o =="q") || (o == "Q")){
        return false;
    }

    int count = 0;

    cout << endl << "Checking If You Are In The Top 1% In The Bench Press..." << endl << endl;
    sleep(3);

    if(b >= 1.5){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Wow, You Are In The Top 1% In The Bench Press!---" << endl << endl;
        cout << fixed << setprecision(1) << "---You Can Bench Press " << b << " Times Your Own Body Weight!---" << endl << endl;
        cout << "Enter Any Key To Continue:" << endl << endl;
        count++;
        string key;
        cin >> key;
    }
    else{
        cout << ".........................................................................................................................................................................................." << endl << endl;;
        cout << "---Unfortunately, You Are Not In The Top 1% In The Bench Press---" << endl << endl;
        cout << fixed << setprecision(1) << "---You Can Bench Press " << b << " Times Your Own Body Weight!---" << endl << endl;
        cout << "Enter Any Key To Continue:" << endl << endl;

        string key;
        cin >> key;
    }

    cout << endl << "Checking If You Are In The Top 1% In The Squat..." << endl << endl;
    sleep(3);

    if(s >= 2.5){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Wow, You Are In The Top 1% In The Squat!---" << endl << endl;
        cout << fixed << setprecision(1) << "---You Can Squat " << s << " Times Your Own Body Weight!---" << endl << endl;
        count++;
        cout << "Enter Any Key To Continue:" << endl << endl;
        string key;
        cin >> key;
    }
    else{
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Unfortunately, You Are Not In The Top 1% In The Squat---" << endl << endl;
        cout << fixed << setprecision(1) << "---You Can Squat " << s << " Times Your Own Body Weight!---" << endl << endl;
        cout << "Enter Any Key To Continue:" << endl << endl;
        string key;
        cin >> key;
    }

    cout << endl << "Checking If You Are In The Top 1% In The Deadlift..." << endl << endl;
    sleep(3);

    if(d >= 3.0){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Wow, You Are In The Top 1% In The Deadlift!---" << endl << endl;
        cout << fixed << setprecision(1) << "---You Can Deadlift " << d << " Times Your Own Body Weight!---" << endl << endl;
        count++;
        cout << "Enter Any Key To Continue:" << endl << endl;
        string key;
        cin >> key;
    }
    else{
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Unfortunately, You Are Not In The Top 1% In The Deadlift---" << endl << endl;
        cout << fixed << setprecision(1) << "---You Can Deadlift " << s << " Times Your Own Body Weight!---" << endl << endl;
        cout << "Enter Any Key To Continue:" << endl << endl;
        string key;
        cin >> key;
    }

    cout << endl << "Calculating Final Results..." << endl << endl;
    sleep(3);

    if(count == 3){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Congratulations, You Are In The Top 1% In All 3 Of Your Lifts!---" << endl << endl;
        cout << "---This Incredible Achievment Means That You Are In The Top 1% Of All Of Humanity!---" << endl << endl;
        
    }
    else if(count == 2){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Congratulations, You Are In The Top 1% In 2 Of Your Lifts!---" << endl << endl;
        cout << "---You Are Really Close To Being In The Top 1% Of All Of Humanity, Keep Grinding!---" << endl << endl;
        
    }
    else if(count == 1){
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---You Are In The Top 1% In 1 Of Your Lifts!---" << endl << endl;
        cout << "---Keep Working, And Stay Consistent, You Will Get There!---" << endl << endl;
    }
    else{
        cout << ".........................................................................................................................................................................................." << endl << endl;
        cout << "---Unfortunately, You Are Not In The Top 1% In Any Of Your Lifts!---" << endl << endl;
        cout << "---Keep Working, Staying Consistent, And Do Not Let This Bring You Down!---" << endl << endl;
    }

    cout << "Enter Any Key To Return To Menu:" << endl << endl;

    string key;
    cin >> key;
    

    return false;
}

bool manager::updatepr(persons* person){


    bool run = true;

    while(run){
        cout << endl << "................................................................................... Information Update! ................................................................................." << endl << endl;
        cout << "Enter 1 To Update Bench Press PR:" << endl << endl;
        cout << "Enter 2 To Update Squat PR:" << endl << endl;
        cout << "Enter 3 To Update Deadlift PR:" << endl << endl;
        cout << "Enter 4 To Exit:" << endl << endl;

        string o;
        cin >> o;

        if(o == "1"){
            updatebench(person);
        }
        else if(o == "2"){
            updatesquat(person);
        }
        else if(o == "3"){
            updatedeadlift(person);
        }
        else if(o == "4"){
            return false;
        }
        else{
            cout << endl << "Invalid Option!" << endl << endl;
        }
    }

        
    
       
    

    return false;
}

bool manager::updatebench(persons* person){

    cout << endl << "...................................................................................... Bench Update! ...................................................................................." << endl << endl;
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;

        
    int bench;
    cout << endl <<  "Please Enter Your Bench Press PR In Pounds:" << endl << endl;
    cin >> bench;
    while(!bench){
        cout << endl <<  "Invalid Input, Please Enter Your Bench Press PR In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> bench;
    }
        
    person->setBench(bench);

    save(person);

    cout << endl << "Bench Press PR Successfully Updated!" << endl << endl;

    cout << "Enter Any Key To Return To Menu" << endl << endl;

    string key;
    cin >> key;


    return false;
}

bool manager::updatesquat(persons* person){

    cout << endl << "...................................................................................... Squat Update! ...................................................................................." << endl << endl;
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;
    int squat;
    cout << endl <<  "Please Enter Your Squat PR In Pounds:" << endl << endl;
    cin >> squat;
    while(!squat){
        cout << endl <<  "Invalid Input, Please Enter Your Squat PR In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> squat;
    }
    person->setSquat(squat);

    save(person);

    cout << endl << "Squat PR Successfully Updated!" << endl << endl;

    cout << "Enter Any Key To Return To Menu" << endl << endl;

    string key;
    cin >> key;


    return false;
}

bool manager::updatedeadlift(persons* person){
    cout << endl << "..................................................................................... Deadlift Update! .................................................................................." << endl << endl;
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;

    int dl;
    cout << endl <<  "Please Enter Your Deadlift PR In Pounds:" << endl << endl;
    cin >> dl;
    while(!dl){
        cout << endl <<  "Invalid Input, Please Enter Your Deadlift PR In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> dl;
    }
    person->setDeadlift(dl);
        
    save(person);

    cout << endl << "Deadlift PR Successfully Updated!" << endl << endl;

    cout << "Enter Any Key To Return To Menu" << endl << endl;

    string key;
    cin >> key;

    return false;
}

bool manager::update(persons* person){

    bool run = true;

    while(run){
        cout << endl << "................................................................................... Information Update! ................................................................................." << endl << endl;

        cout << "Enter 1 To Update Height:" << endl << endl;
        cout << "Enter 2 To Update Weight:" << endl << endl;
        cout << "Enter 3 To Update Age:" << endl << endl;
        cout << "Enter 4 To Update Goal:" << endl << endl;
        cout << "Enter 5 To Exit:" << endl << endl;

        string o;
        cin >> o;

        if(o == "1"){
            updateheight(person);
        }
        else if(o == "2"){
            updateweight(person);
        }
        else if(o == "3"){
            updateage(person);
        }
        else if(o == "4"){
            updategoal(person);
        }
        else if(o == "5"){
            return false;
        }
        else{
            cout << endl << "Invalid Option!" << endl;
        }
    }

        
    
       
    
  

    return false;
}

bool manager::updategoal(persons* person){

    cout << endl << "....................................................................................... Goal Update! ...................................................................................." << endl << endl;


    bool gun = true;

    while(gun){
    cout << endl << "Is Your Goal To Be Lean Or Bulk?" << endl << endl;
     
    string choice;
    cin >> choice;

    if((choice == "lean") || (choice == "Lean")){
        person->setGoal(choice);
        gun = false;
    }
    else if((choice == "bulk") || (choice == "Bulk")){
        person->setGoal(choice);
        gun = false;
    }
    else{
        cout << endl << "Invalid Choice!" << endl;
        gun = true;
    }
    }

    save(person);
    cout << endl << "Goal Updated Successfully!" << endl << endl;

    
    cout << "Enter Any Key To Return To Menu" << endl << endl;

    string key;
    cin >> key;

    return false;
}

bool manager::updateheight(persons* person){

    cout << endl << "...................................................................................... Height Update! ..................................................................................." << endl << endl;
  
  
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;

        
    int inches;
    cout << endl <<  "Please Enter Your New Height In Inches (NOTE: 60 Inches is 5 Feet):" << endl << endl;
    cin >> inches;
    while(!inches){
        cout << endl <<  "Invalid Input, Please Enter Your New Height In Inches(NOTE: 60 Inches is 5 Feet):" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> inches;
    }
        
    person->setHeight(inches);

    save(person);

    cout << endl << "Height Updated Successfully!" << endl << endl;

    cout << "Enter Any Key To Return To Menu" << endl << endl;

    string key;
    cin >> key;

    return false;
}

bool manager::updateweight(persons* person){
    cout << endl << "...................................................................................... Weight Update! ..................................................................................." << endl << endl;
  
  
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;

    int weight;
    cout << endl <<  "Please Enter Your New Weight In Pounds:" << endl << endl;
    cin >> weight;
    while(!weight){
        cout << endl <<  "Invalid Input, Please Enter Your New Weight In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> weight;
    }
    person->setWeight(weight);

    save(person);

    cout << endl << "Weight Updated Successfully!" << endl << endl;

    cout << "Enter Any Key To Return To Menu" << endl << endl;

    string key;
    cin >> key;


    return false;
}

bool manager::updateage(persons* person){
    cout << endl << "....................................................................................... Age Update! ....................................................................................." << endl << endl;
  
  
    cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;

    int age;
    cout << endl <<  "Please Enter Your New Age:" << endl << endl;
    cin >> age;
    while(!age){
        cout << endl <<  "Invalid Input, Please Enter Your New Age:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> age;
    }
    person->setAge(age);
        
    save(person);

    cout << endl << "Age Updated Successfully!" << endl << endl;

    cout << "Enter Any Key To Return To Menu" << endl << endl;

    string key;
    cin >> key;

    return false;
}

bool manager::workoutplan(persons* person){
    
    
    if((person->getGoal() == "lean") || (person->getGoal() == "Lean")){
        workoutplanlean(person);
    }
    else if((person->getGoal() == "bulk") || (person->getGoal() == "Bulk")){
        workoutplanbulk(person);
    }

    return false;
}

bool manager::workoutplanbulk(persons* person){

    cout << endl << ".................................................................................. Bulk Workout Plan: ..................................................................................." << endl << endl;
    cout << "Here Are Your Stats:" << endl << endl;  
    cout << "----User Name----: " << person->getName() << endl << endl;
    cout << "----Height----: " << person->getHeight() << endl << endl;
    cout << "----Weight----: " << person->getWeight() << endl << endl;
    cout << "----Age----: " << person->getAge() << endl << endl;
    cout << "Enter Any Key To Get Your Workout Plan Or Enter Q To Quit!" << endl << endl;

    string o;
    cin >> o;

    if((o == "q") || (o == "Q")){
        return false;
    }

    cout << endl << "Calculating Your Personalized Workout Plan Please Wait....." << endl << endl;
    sleep(3);

    if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //cout << "low age /low weight /low height";
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body Strength Training" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Plank: Hold for 1 minute" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio such as jogging, cycling, or swimming" << endl << endl;

    cout << "Day 3: Lower Body Strength Training" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Calf raises: 3 sets of 12-15 reps" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Russian twists: 3 sets of 12-15 reps per side" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full-Body Circuit Training" << endl << endl;
    cout << "- Jumping jacks: 3 sets of 15 reps" << endl;
    cout << "- Push-ups: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell squats: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Plank: Hold for 1 minute" << endl;
    cout << "- Mountain climbers: 3 sets of 15 reps per leg" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) such as sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body Strength Training" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Plank: Hold for 1 minute" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Lower Body Strength Training" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Calf raises: 3 sets of 12-15 reps" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Russian twists: 3 sets of 12-15 reps per side" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full-Body Circuit Training" << endl << endl;
    cout << "- Jumping jacks: 3 sets of 15 reps" << endl;
    cout << "- Push-ups: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell squats: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Plank: Hold for 1 minute" << endl;
    cout << "- Mountain climbers: 3 sets of 15 reps per leg" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises such as sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //low age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell flyes: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as running, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Seated cable rows: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Leg curls: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 8-10 reps" << endl;
    cout << "- Front raises: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises such as sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //low age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body Strength Training" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Plank: Hold for 1 minute" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Lower Body Strength Training" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Calf raises: 3 sets of 12-15 reps" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Russian twists: 3 sets of 12-15 reps per side" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full-Body Circuit Training" << endl << endl;
    cout << "- Jumping jacks: 3 sets of 15 reps" << endl;
    cout << "- Push-ups: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell squats: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Plank: Hold for 1 minute" << endl;
    cout << "- Mountain climbers: 3 sets of 15 reps per leg" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises such as sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell flyes: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Seated cable rows: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Leg curls: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 8-10 reps" << endl;
    cout << "- Front raises: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises such as sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //low age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Cable flyes: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 10-12 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell curls: 3 sets of 10-12 reps" << endl;
    cout << "- Hammer curls: 3 sets of 10-12 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 10-12 reps" << endl;
    cout << "- Front raises: 3 sets of 10-12 reps" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //low age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell flyes: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 8-10 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Leg curls: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 8-10 reps" << endl;
    cout << "- Front raises: 3 sets of 8-10 reps" << endl << endl; 

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Cable flyes: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 10-12 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell curls: 3 sets of 10-12 reps" << endl;
    cout << "- Hammer curls: 3 sets of 10-12 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 10-12 reps" << endl;
    cout << "- Front raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises such as sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
          //low age /high weight /tall height
          cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell flyes: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 8-10 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 8-10 reps" << endl;
    cout << "- Front raises: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
            
        //med age
            
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //med age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Cable flyes: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 10-12 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell curls: 3 sets of 10-12 reps" << endl;
    cout << "- Hammer curls: 3 sets of 10-12 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 10-12 reps" << endl;
    cout << "- Front raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell flyes: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 8-10 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 8-10 reps" << endl;
    cout << "- Front raises: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //med age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Cable flyes: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 10-12 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Hammer curls: 3 sets of 10-12 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 10-12 reps" << endl;
    cout << "- Front raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //med age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell flyes: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 8-10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 8-10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 8-10 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 8-10 reps" << endl;
    cout << "- Front raises: 3 sets of 8-10 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Cable flyes: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 10-12 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 10-12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Hammer curls: 3 sets of 10-12 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 10-12 reps" << endl;
    cout << "- Front raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
           //med age /med weight /tall height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 8-10 reps" << endl;
    cout << "- Cable flyes: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 10-12 reps" << endl;
    cout << "- Overhead dumbbell tricep extension: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 10-12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Hammer curls: 3 sets of 10-12 reps" << endl;
    cout << "- Reverse flyes: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 10-12 reps" << endl;
    cout << "- Front raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
           //med age /high weight /low height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead press: 3 sets of 8-10 reps" << endl;
    cout << "- Dumbbell curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or using the elliptical machine" << endl << endl;

    cout << "Day 3: Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Romanian deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Walking lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Calf raises: 3 sets of 10-12 reps" << endl;
    cout << "- Leg press: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full Body" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 10-12 reps" << endl;
    cout << "- Leg curls: 3 sets of 10-12 reps" << endl;
    cout << "- Push-ups: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 6: Cardiovascular Exercise" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), incorporating exercises like sprints, burpees, or jump rope" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
  cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
  cout << "- Dumbbell shoulder press: 3 sets of 8-10 reps" << endl;
  cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
  cout << "- Dumbbell bicep curls: 3 sets of 10-12 reps" << endl;
  cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
  cout << "- Plank: 3 sets of 30 seconds" << endl << endl;

  cout << "Day 2: Cardio" << endl << endl;
  cout << "- 30-45 minutes of moderate-intensity cardio exercises (e.g., brisk walking, cycling, or swimming)" << endl << endl;

  cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
  cout << "- Squats: 3 sets of 8-10 reps" << endl;
  cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
  cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
  cout << "- Leg press: 3 sets of 10-12 reps" << endl;
  cout << "- Calf raises: 3 sets of 10-12 reps" << endl;
  cout << "- Bicycle crunches: 3 sets of 15-20 reps" << endl << endl;

  cout << "Day 4: Cardio" << endl << endl;
  cout << "- 30-45 minutes of moderate-intensity cardio exercises (e.g., elliptical, stair climbing, or rowing)" << endl << endl;

  cout << "Day 5: Weightlifting - Full Body" << endl << endl;
  cout << "- Barbell squats: 3 sets of 8-10 reps" << endl;
  cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
  cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
  cout << "- Dumbbell shoulder press: 3 sets of 8-10 reps" << endl;
  cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
  cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
  cout << "- Russian twists: 3 sets of 15-20 reps" << endl << endl;

  cout << "Day 6: Active Rest" << endl << endl;
  cout << "- Engage in a low-intensity activity like yoga, stretching, or leisurely walking to promote recovery and relaxation." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //med age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
  cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
  cout << "- Dumbbell shoulder press: 3 sets of 8-10 reps" << endl;
  cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
  cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
  cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
  cout << "- Plank: 3 sets of 30 seconds" << endl << endl;

  cout << "Day 2: Cardio" << endl << endl;
  cout << "- 30 minutes of high-intensity interval training (HIIT) on the treadmill or outdoor sprints" << endl << endl;

  cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
  cout << "- Squats: 3 sets of 8-10 reps" << endl;
  cout << "- Lunges: 3 sets of 8-10 reps per leg" << endl;
  cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
  cout << "- Leg press: 3 sets of 10-12 reps" << endl;
  cout << "- Calf raises: 3 sets of 10-12 reps" << endl;
  cout << "- Bicycle crunches: 3 sets of 15-20 reps" << endl << endl;

  cout << "Day 4: Cardio" << endl << endl;
  cout << "- 30 minutes of steady-state cardio on the stationary bike or elliptical machine" << endl << endl;

  cout << "Day 5: Weightlifting - Full Body" << endl << endl;
  cout << "- Barbell squats: 3 sets of 8-10 reps" << endl;
  cout << "- Barbell bench press: 3 sets of 8-10 reps" << endl;
  cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
  cout << "- Dumbbell shoulder press: 3 sets of 8-10 reps" << endl;
  cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
  cout << "- Tricep dips: 3 sets of 10-12 reps" << endl;
  cout << "- Russian twists: 3 sets of 15-20 reps" << endl << endl;

  cout << "Day 6: Active Rest" << endl << endl;
  cout << "- Engage in a low-impact activity such as swimming, yoga, or hiking to promote recovery and flexibility." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }

        //high age
            
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //high age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
  cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
  cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
  cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
  cout << "- Walking on the treadmill or outdoor walking: 20-30 minutes" << endl << endl;

  cout << "Day 2: Rest and Recovery" << endl << endl;

  cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
  cout << "- Leg press: 3 sets of 12 reps" << endl;
  cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
  cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
  cout << "- Stationary bike or recumbent bike: 20-30 minutes" << endl << endl;

  cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
  cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
  cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
  cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
  cout << "- Walking on the treadmill or outdoor walking: 20-30 minutes" << endl << endl;

  cout << "Day 2: Rest and Recovery" << endl << endl;

  cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
  cout << "- Leg press: 3 sets of 12 reps" << endl;
  cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
  cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
  cout << "- Stationary bike or recumbent bike: 20-30 minutes" << endl << endl;

  cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
          else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //high age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
    cout << "- Walking on the treadmill or outdoor walking: 20-30 minutes" << endl << endl;

    cout << "Day 2: Rest and Recovery" << endl << endl;

    cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
    cout << "- Stationary bike or recumbent bike: 20-30 minutes" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //high age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
    cout << "- Walking on the treadmill or outdoor walking: 20-30 minutes" << endl << endl;

    cout << "Day 2: Rest and Recovery" << endl << endl;

    cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
    cout << "- Stationary bike or recumbent bike: 20-30 minutes" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
    cout << "- Walking on the treadmill or outdoor walking: 20-30 minutes" << endl << endl;

    cout << "Day 2: Rest and Recovery" << endl << endl;

    cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
    cout << "- Stationary bike or recumbent bike: 20-30 minutes" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //high age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
    cout << "- Walking on the treadmill or outdoor walking: 20-30 minutes" << endl << endl;

    cout << "Day 2: Rest and Recovery" << endl << endl;

    cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
    cout << "- Stationary bike or elliptical: 20-30 minutes" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //high age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
    cout << "- Walking on the treadmill or outdoor walking: 20-30 minutes" << endl << endl;

    cout << "Day 2: Rest and Recovery" << endl << endl;

    cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
    cout << "- Stationary bike or elliptical: 20-30 minutes" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl; 

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
    cout << "- 20-30 minutes of walking on the treadmill or outdoor walking" << endl << endl;

    cout << "Day 2: Rest and Recovery" << endl << endl; 

    cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
    cout << "- 20-30 minutes of stationary bike or elliptical" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //high age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell tricep kickbacks: 3 sets of 12 reps" << endl;
    cout << "- 20-30 minutes of walking on the treadmill or outdoor walking" << endl << endl;

    cout << "Day 2: Rest and Recovery" << endl << endl;

    cout << "Day 3: Light Weightlifting and Cardio" << endl << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Dumbbell chest press: 3 sets of 12 reps" << endl;
    cout << "- 20-30 minutes of stationary bike or elliptical" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        
        
        }

        //lean or bulk
    //18-35  36-55   56-and up
    //5'6- and below  5'7-6'0  6'1-and up
    //130- and below  131-180  181-and up

    return false;
}

bool manager::workoutplanlean(persons* person){
     
    cout << endl << ".................................................................................. Lean Workout Plan: ..................................................................................." << endl << endl;
    cout << "Here Are Your Stats:" << endl << endl;  
    cout << "----User Name----: " << person->getName() << endl << endl;
    cout << "----Height----: " << person->getHeight() << endl << endl;
    cout << "----Weight----: " << person->getWeight() << endl << endl;
    cout << "----Age----: " << person->getAge() << endl << endl;
   
    cout << "Enter Any Key To Get Your Workout Plan Or Enter Q To Quit!" << endl << endl;

    string o;
    cin >> o;

    if((o == "q") || (o == "Q")){
        return false;
    }
        cout << endl << "Calculating Your Personalized Workout Plan Please Wait....." << endl << endl;
        sleep(3);
          
        if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //cout << "low age /low weight /low height";
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Exercise Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body Strength Training" << endl << endl;
            cout << "Barbell bench press: 3 sets of 8-10 reps" << endl;
            cout << "Bent-over rows: 3 sets of 8-10 reps" << endl;
            cout << "Shoulder press: 3 sets of 8-10 reps" << endl;
            cout << "Bicep curls: 3 sets of 8-10 reps" << endl;
            cout << "Tricep dips: 3 sets of 8-10 reps" << endl;
            cout << "20 minutes of moderate-intensity cardio (e.g., treadmill or stationary bike)" << endl << endl;
            cout << "Day 2: Lower Body Strength Training" << endl << endl;
            cout << "Squats: 3 sets of 8-10 reps" << endl;
            cout << "Deadlifts: 3 sets of 8-10 reps" << endl;
            cout << "Lunges: 3 sets of 8-10 reps per leg" << endl;
            cout << "Leg press: 3 sets of 8-10 reps" << endl;
            cout << "Calf raises: 3 sets of 12-15 reps" << endl;
            cout << "20 minutes of moderate-intensity cardio" << endl;
            cout << "Day 3: Cardio and Abs" << endl;
            cout << "30 minutes of high-intensity interval training (HIIT) on the treadmill, alternating between sprinting and recovery periods" << endl;
            cout << "Abdominal exercises: Planks (3 sets, holding for 30-60 seconds), Russian twists (3 sets of 12-15 reps), bicycle crunches (3 sets of 12-15 reps)" << endl << endl;
            cout << "Day 4: Upper Body Strength Training" << endl << endl;
            cout << "Incline dumbbell press: 3 sets of 8-10 reps" << endl;
            cout << "Lat pulldowns: 3 sets of 8-10 reps" << endl;
            cout << "Shoulder lateral raises: 3 sets of 8-10 reps" << endl;
            cout << "Hammer curls: 3 sets of 8-10 reps" << endl;
            cout << "Skull crushers: 3 sets of 8-10 reps" << endl;
            cout << "20 minutes of moderate-intensity cardio" << endl << endl;
            cout << "Day 5: Lower Body Strength Training" << endl << endl;
            cout << "Bulgarian split squats: 3 sets of 8-10 reps per leg" << endl;
            cout << "Romanian deadlifts: 3 sets of 8-10 reps" << endl;
            cout << "Step-ups: 3 sets of 8-10 reps per leg" << endl;
            cout << "Glute bridges: 3 sets of 12-15 reps" << endl;
            cout << "Seated calf raises: 3 sets of 12-15 reps" << endl;
            cout << "20 minutes of moderate-intensity cardio" << endl << endl;
            cout << "Day 6: Active Rest Day" << endl << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
    cout << "- Bench press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl << endl;

    // Day 2: Cardio
    cout << "Day 2: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or swimming" << endl << endl;

    // Day 3: Weightlifting - Lower Body
    cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps (each leg)" << endl;
    cout << "- Calf raises: 3 sets of 10-12 reps" << endl << endl;

    // Day 4: Cardio
    cout << "Day 4: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), such as sprint intervals or circuit training" << endl << endl;

    // Day 5: Weightlifting - Full Body
    cout << "Day 5: Weightlifting - Full Body" << endl << endl;
    cout << "- Pull-ups or lat pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Push-ups or chest press machine: 3 sets of 8-10 reps" << endl;
    cout << "- Leg press: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips or tricep pushdowns: 3 sets of 10-12 reps" << endl << endl;

    // Day 6: Active Rest
    cout << "Day 6: Active Rest" << endl << endl;
    cout << "- Engage in a low-impact activity you enjoy, such as yoga, hiking, or swimming" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //low age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
    cout << "- Bench Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over Rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or swimming" << endl;
    cout << endl;

    cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps (each leg)" << endl;
    cout << "- Calf Raises: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 4: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), such as sprint intervals or circuit training" << endl;
    cout << endl;

    cout << "Day 5: Weightlifting - Full Body" << endl << endl;
    cout << "- Pull-ups or Lat Pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Push-ups or Chest Press Machine: 3 sets of 8-10 reps" << endl;
    cout << "- Leg Press: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips or Tricep Pushdowns: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 6: Active Rest" << endl << endl;
    cout << "- Engage in a low-impact activity you enjoy, such as yoga, hiking, or swimming" << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //low age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
    cout << "- Bench Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over Rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or swimming" << endl;
    cout << endl;

    cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps (each leg)" << endl;
    cout << "- Calf Raises: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 4: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), such as sprint intervals or circuit training" << endl;
    cout << endl;

    cout << "Day 5: Weightlifting - Full Body" << endl << endl;
    cout << "- Pull-ups or Lat Pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Push-ups or Chest Press Machine: 3 sets of 8-10 reps" << endl;
    cout << "- Leg Press: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips or Tricep Pushdowns: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 6: Active Rest" << endl << endl;
    cout << "- Engage in a low-impact activity you enjoy, such as yoga, hiking, or swimming" << endl;
    cout << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
    cout << "- Bench Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over Rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or swimming" << endl;
    cout << endl;

    cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps (each leg)" << endl;
    cout << "- Calf Raises: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 4: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), such as sprint intervals or circuit training" << endl;
    cout << endl;

    cout << "Day 5: Weightlifting - Full Body" << endl << endl;
    cout << "- Pull-ups or Lat Pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Push-ups or Chest Press Machine: 3 sets of 8-10 reps" << endl;
    cout << "- Leg Press: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips or Tricep Pushdowns: 3 sets of 10-12 reps" << endl;
    cout << endl;

    cout << "Day 6: Active Rest" << endl << endl;
    cout << "- Engage in a low-impact activity you enjoy, such as yoga, hiking, or swimming" << endl;
    cout << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //low age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
    cout << "- Bench Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over Rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips: 3 sets of 10-12 reps" << endl;

    cout << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or swimming" << endl;

    cout << endl;

    cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps (each leg)" << endl;
    cout << "- Calf Raises: 3 sets of 10-12 reps" << endl;

    cout << endl;

    cout << "Day 4: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), such as sprint intervals or circuit training" << endl;

    cout << endl;

    cout << "Day 5: Weightlifting - Full Body" << endl << endl;
    cout << "- Pull-ups or Lat Pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Push-ups or Chest Press Machine: 3 sets of 8-10 reps" << endl;
    cout << "- Leg Press: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips or Tricep Pushdowns: 3 sets of 10-12 reps" << endl;

    cout << endl;

    cout << "Day 6: Active Rest" << endl << endl;
    cout << "- Engage in a low-impact activity you enjoy, such as yoga, hiking, or swimming" << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //low age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Weightlifting - Upper Body" << endl << endl;
    cout << "- Bench Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bent-over Rows: 3 sets of 8-10 reps" << endl;
    cout << "- Shoulder Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as jogging, cycling, or swimming" << endl << endl;

    cout << "Day 3: Weightlifting - Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 8-10 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8-10 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps (each leg)" << endl;
    cout << "- Calf Raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT), such as sprint intervals or circuit training" << endl << endl;

    cout << "Day 5: Weightlifting - Full Body" << endl << endl;
    cout << "- Pull-ups or Lat Pulldowns: 3 sets of 8-10 reps" << endl;
    cout << "- Push-ups or Chest Press Machine: 3 sets of 8-10 reps" << endl;
    cout << "- Leg Press: 3 sets of 8-10 reps" << endl;
    cout << "- Overhead Press: 3 sets of 8-10 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep Dips or Tricep Pushdowns: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 6: Active Rest" << endl << endl;
    cout << "- Engage in a low-impact activity you enjoy, such as yoga, hiking, or swimming" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
          //low age /high weight /tall height
          cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body Strength Training" << endl << endl;
    cout << "- Bench press: 4 sets x 8 reps" << endl;
    cout << "- Bent-over rows: 4 sets x 10 reps" << endl;
    cout << "- Overhead press: 3 sets x 10 reps" << endl;
    cout << "- Bicep curls: 3 sets x 12 reps" << endl;
    cout << "- Tricep dips: 3 sets x 12 reps" << endl << endl;

    // Day 2
    cout << "Day 2: Cardio and Core" << endl << endl;
    cout << "- 30 minutes of moderate-intensity treadmill running or cycling" << endl;
    cout << "- Plank: 3 sets, hold for 1 minute each" << endl;
    cout << "- Russian twists: 3 sets x 20 reps" << endl;
    cout << "- Leg raises: 3 sets x 15 reps" << endl << endl;

    // Day 3
    cout << "Day 3: Lower Body Strength Training" << endl << endl;
    cout << "- Squats: 4 sets x 8 reps" << endl;
    cout << "- Deadlifts: 4 sets x 6 reps" << endl;
    cout << "- Lunges: 3 sets x 10 reps per leg" << endl;
    cout << "- Leg press: 3 sets x 12 reps" << endl;
    cout << "- Calf raises: 3 sets x 15 reps" << endl << endl;

    // Day 4
    cout << "Day 4: Rest day" << endl << endl;

    // Day 5
    cout << "Day 5: Cardio and Upper Body" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) on the elliptical or rowing machine" << endl;
    cout << "- Pull-ups or assisted pull-ups: 3 sets x 8 reps" << endl;
    cout << "- Push-ups: 3 sets x 15 reps" << endl;
    cout << "- Lateral raises: 3 sets x 12 reps" << endl << endl;

    // Day 6
    cout << "Day 6: Lower Body and Core" << endl << endl;
    cout << "- Romanian deadlifts: 4 sets x 8 reps" << endl;
    cout << "- Glute bridges: 3 sets x 12 reps" << endl;
    cout << "- Side lunges: 3 sets x 10 reps per leg" << endl;
    cout << "- Bicycle crunches: 3 sets x 20 reps" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
            
        //med age
            
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //med age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body Strength Training" << endl << endl;
    cout << "- Bench press: 4 sets x 8 reps" << endl;
    cout << "- Bent-over rows: 4 sets x 10 reps" << endl;
    cout << "- Overhead press: 3 sets x 10 reps" << endl;
    cout << "- Bicep curls: 3 sets x 12 reps" << endl;
    cout << "- Tricep dips: 3 sets x 12 reps" << endl << endl;

    // Day 2
    cout << "Day 2: Cardio and Core" << endl << endl; 
    cout << "- 30 minutes of moderate-intensity treadmill running or cycling" << endl;
    cout << "- Plank: 3 sets, hold for 1 minute each" << endl;
    cout << "- Russian twists: 3 sets x 20 reps" << endl;
    cout << "- Leg raises: 3 sets x 15 reps" << endl << endl;

    // Day 3
    cout << "Day 3: Lower Body Strength Training" << endl << endl;
    cout << "- Squats: 4 sets x 8 reps" << endl;
    cout << "- Deadlifts: 4 sets x 6 reps" << endl;
    cout << "- Lunges: 3 sets x 10 reps per leg" << endl;
    cout << "- Leg press: 3 sets x 12 reps" << endl;
    cout << "- Calf raises: 3 sets x 15 reps" << endl << endl;

    // Day 4
    cout << "Day 4: Rest day" << endl << endl;

    // Day 5
    cout << "Day 5: Cardio and Upper Body" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) on the elliptical or rowing machine" << endl;
    cout << "- Pull-ups or assisted pull-ups: 3 sets x 8 reps" << endl;
    cout << "- Push-ups: 3 sets x 15 reps" << endl;
    cout << "- Lateral raises: 3 sets x 12 reps" << endl << endl;

    // Day 6
    cout << "Day 6: Lower Body and Core" << endl << endl;
    cout << "- Romanian deadlifts: 4 sets x 8 reps" << endl;
    cout << "- Glute bridges: 3 sets x 12 reps" << endl;
    cout << "- Side lunges: 3 sets x 10 reps per leg" << endl;
    cout << "- Bicycle crunches: 3 sets x 20 reps" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Full-Body Strength Training" << endl << endl;
    cout << "- Barbell squats: 4 sets x 8 reps" << endl;
    cout << "- Dumbbell bench press: 4 sets x 10 reps" << endl;
    cout << "- Bent-over rows: 4 sets x 10 reps" << endl;
    cout << "- Dumbbell shoulder press: 3 sets x 10 reps" << endl;
    cout << "- Dumbbell lunges: 3 sets x 12 reps per leg" << endl;
    cout << "- Plank: 3 sets, hold for 1 minute each" << endl << endl;

    // Day 2
    cout << "Day 2: Cardiovascular Training" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) on the treadmill or stationary bike" << endl;
    cout << "- Jumping jacks: 3 sets x 30 seconds" << endl;
    cout << "- Mountain climbers: 3 sets x 12 reps per leg" << endl;
    cout << "- Bicycle crunches: 3 sets x 15 reps" << endl << endl;

    // Day 3
    cout << "Day 3: Upper Body Strength Training" << endl << endl;
    cout << "- Barbell bench press: 4 sets x 8 reps" << endl;
    cout << "- Pull-ups or lat pull-downs: 4 sets x 10 reps" << endl;
    cout << "- Dumbbell shoulder press: 3 sets x 10 reps" << endl;
    cout << "- Barbell bicep curls: 3 sets x 12 reps" << endl;
    cout << "- Tricep dips: 3 sets x 12 reps" << endl << endl;

    // Day 4
    cout << "Day 4: Rest day" << endl << endl;

    // Day 5
    cout << "Day 5: Lower Body Strength Training" << endl << endl;
    cout << "- Deadlifts: 4 sets x 8 reps" << endl;
    cout << "- Bulgarian split squats: 4 sets x 10 reps per leg" << endl;
    cout << "- Leg press: 3 sets x 10 reps" << endl;
    cout << "- Romanian deadlifts: 3 sets x 12 reps" << endl;
    cout << "- Standing calf raises: 3 sets x 15 reps" << endl << endl;

    // Day 6
    cout << "Day 6: Cardiovascular Training and Core" << endl << endl;
    cout << "- 30 minutes of steady-state cardio on the elliptical or rowing machine" << endl;
    cout << "- Plank: 3 sets, hold for 1 minute each" << endl;
    cout << "- Russian twists: 3 sets x 20 reps" << endl;
    cout << "- Leg raises: 3 sets x 15 reps" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //med age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 4 sets x 8 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets x 10 reps" << endl;
    cout << "- Cable flyes: 3 sets x 12 reps" << endl;
    cout << "- Tricep dips: 3 sets x 10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets x 12 reps" << endl << endl;

    // Day 2
    cout << "Day 2: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 4 sets x 8 reps" << endl;
    cout << "- Wide-grip pull-ups: 3 sets x 10 reps" << endl;
    cout << "- Bent-over rows: 3 sets x 10 reps" << endl;
    cout << "- Barbell curls: 3 sets x 12 reps" << endl;
    cout << "- Hammer curls: 3 sets x 12 reps" << endl << endl;

    // Day 3
    cout << "Day 3: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 4 sets x 8 reps" << endl;
    cout << "- Lunges: 3 sets x 10 reps per leg" << endl;
    cout << "- Leg press: 3 sets x 10 reps" << endl;
    cout << "- Shoulder press: 4 sets x 10 reps" << endl;
    cout << "- Lateral raises: 3 sets x 12 reps" << endl << endl;

    // Day 4
    cout << "Day 4: Cardiovascular Training" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio exercise (e.g., jogging, cycling, elliptical)" << endl << endl;

    // Day 5
    cout << "Day 5: Full-Body Workout" << endl << endl;
    cout << "- Barbell squats: 4 sets x 8 reps" << endl;
    cout << "- Barbell bench press: 4 sets x 8 reps" << endl;
    cout << "- Bent-over rows: 4 sets x 8 reps" << endl;
    cout << "- Shoulder press: 4 sets x 8 reps" << endl;
    cout << "- Bicep curls: 3 sets x 10 reps" << endl;
    cout << "- Tricep dips: 3 sets x 10 reps" << endl;
    cout << "- Leg press: 3 sets x 10 reps" << endl << endl;

    // Day 6
    cout << "Day 6: Active Rest or Yoga" << endl << endl;
    cout << "- Engage in light activities such as walking, stretching, or practicing yoga." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //med age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets x 10 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets x 12 reps" << endl;
    cout << "- Chest flyes: 3 sets x 12 reps" << endl;
    cout << "- Tricep dips: 3 sets x 10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets x 12 reps" << endl << endl;

    cout << "Day 2: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets x 10 reps" << endl;
    cout << "- Wide-grip pull-ups: 3 sets x 10 reps" << endl;
    cout << "- Bent-over rows: 3 sets x 12 reps" << endl;
    cout << "- Barbell curls: 3 sets x 12 reps" << endl;
    cout << "- Hammer curls: 3 sets x 12 reps" << endl << endl;

    cout << "Day 3: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 3 sets x 10 reps" << endl;
    cout << "- Lunges: 3 sets x 10 reps per leg" << endl;
    cout << "- Leg press: 3 sets x 12 reps" << endl;
    cout << "- Shoulder press: 3 sets x 10 reps" << endl;
    cout << "- Lateral raises: 3 sets x 12 reps" << endl << endl;

    cout << "Day 4: Cardiovascular Training" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) or any cardio exercise of your choice" << endl << endl;

    cout << "Day 5: Full-Body Workout" << endl << endl;
    cout << "- Barbell squats: 3 sets x 10 reps" << endl;
    cout << "- Barbell bench press: 3 sets x 10 reps" << endl;
    cout << "- Bent-over rows: 3 sets x 10 reps" << endl;
    cout << "- Shoulder press: 3 sets x 10 reps" << endl;
    cout << "- Bicep curls: 3 sets x 12 reps" << endl;
    cout << "- Tricep dips: 3 sets x 10 reps" << endl;
    cout << "- Leg press: 3 sets x 12 reps" << endl << endl;

    cout << "Day 6: Active Rest or Yoga" << endl << endl;
    cout << "- Engage in light activities such as walking, stretching, or practicing yoga." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body - Strength Training" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8 reps" << endl;
    cout << "- Overhead press: 3 sets of 10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 12 reps" << endl << endl;
    
    cout << "Day 2: Lower Body - Strength Training" << endl << endl;
    cout << "- Squats: 3 sets of 8 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8 reps" << endl;
    cout << "- Lunges: 3 sets of 10 reps per leg" << endl;
    cout << "- Calf raises: 3 sets of 12 reps" << endl;
    cout << "- Leg press: 3 sets of 10 reps" << endl << endl;
    
    cout << "Day 3: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) on the treadmill, alternating between sprints and walking/jogging" << endl << endl;
    
    cout << "Day 4: Back and Shoulders - Strength Training" << endl << endl;
    cout << "- Lat pulldowns: 3 sets of 10 reps" << endl;
    cout << "- Seated cable rows: 3 sets of 10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 12 reps" << endl;
    cout << "- Rear delt flyes: 3 sets of 12 reps" << endl  << endl;
    
    cout << "Day 5: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as cycling or using the elliptical machine" << endl << endl;
    
    cout << "Day 6: Full Body - Strength Training" << endl << endl;
    cout << "- Squats: 3 sets of 8 reps" << endl;
    cout << "- Bench press: 3 sets of 8 reps" << endl;
    cout << "- Romanian deadlifts: 3 sets of 8 reps" << endl;
    cout << "- Overhead press: 3 sets of 10 reps" << endl;
    cout << "- Lunges: 3 sets of 10 reps per leg" << endl << endl;
    
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
           //med age /med weight /tall height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body - Strength Training" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 8 reps" << endl;
    cout << "- Overhead press: 3 sets of 10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 12 reps" << endl << endl;

    cout << "Day 2: Lower Body - Strength Training" << endl << endl;
    cout << "- Squats: 3 sets of 8 reps" << endl;
    cout << "- Deadlifts: 3 sets of 8 reps" << endl;
    cout << "- Lunges: 3 sets of 10 reps per leg" << endl;
    cout << "- Calf raises: 3 sets of 12 reps" << endl;
    cout << "- Leg press: 3 sets of 10 reps" << endl << endl;

    cout << "Day 3: Cardio" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) on the treadmill, alternating between sprints and walking/jogging" << endl << endl;

    cout << "Day 4: Back and Shoulders - Strength Training" << endl << endl;
    cout << "- Lat pulldowns: 3 sets of 10 reps" << endl;
    cout << "- Seated cable rows: 3 sets of 10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 12 reps" << endl;
    cout << "- Rear delt flyes: 3 sets of 12 reps" << endl << endl;

    cout << "Day 5: Cardio" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio, such as cycling or using the elliptical machine" << endl << endl;

    cout << "Day 6: Full Body - Strength Training" << endl << endl;
    cout << "- Squats: 3 sets of 8 reps" << endl;
    cout << "- Bench press: 3 sets of 8 reps" << endl;
    cout << "- Romanian deadlifts: 3 sets of 8 reps" << endl;
    cout << "- Overhead press: 3 sets of 10 reps" << endl;
    cout << "- Lunges: 3 sets of 10 reps per leg" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
           //med age /high weight /low height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 4 sets of 8 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 12 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 10 reps" << endl << endl;

    cout << "Day 2: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 4 sets of 8 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10 reps" << endl << endl;

    cout << "Day 3: Legs and Shoulders" << endl << endl;
    cout << "- Squats: 4 sets of 8 reps" << endl;
    cout << "- Lunges: 3 sets of 10 reps per leg" << endl;
    cout << "- Shoulder press: 3 sets of 10 reps" << endl;
    cout << "- Lateral raises: 3 sets of 12 reps" << endl << endl;

    cout << "Day 4: Cardio and Abs" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio (e.g., jogging, cycling, or using the elliptical machine)" << endl;
    cout << "- Plank: 3 sets of 1 minute" << endl;
    cout << "- Russian twists: 3 sets of 10 reps per side" << endl;
    cout << "- Leg raises: 3 sets of 12 reps" << endl << endl;

    cout << "Day 5: Arms" << endl << endl;
    cout << "- Barbell curls: 3 sets of 10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 10 reps" << endl;
    cout << "- Tricep overhead extensions: 3 sets of 10 reps" << endl;
    cout << "- Skull crushers: 3 sets of 10 reps" << endl << endl;

    cout << "Day 6: Full Body - Strength Training" << endl << endl;
    cout << "- Squats: 4 sets of 8 reps" << endl;
    cout << "- Romanian deadlifts: 3 sets of 10 reps" << endl;
    cout << "- Bench press: 4 sets of 8 reps" << endl;
    cout << "- Overhead press: 3 sets of 10 reps" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body - Strength Training" << endl << endl;
    cout << "- Barbell bench press: 4 sets of 8 reps" << endl;
    cout << "- Bent-over rows: 4 sets of 10 reps" << endl;
    cout << "- Overhead press: 3 sets of 10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 12 reps" << endl << endl;

    cout << "Day 2: Cardio and Core" << endl << endl;
    cout << "- 30 minutes of moderate-intensity cardio (running, cycling, or elliptical)" << endl;
    cout << "- Plank: 3 sets of 1 minute" << endl;
    cout << "- Russian twists: 3 sets of 10 reps per side" << endl;
    cout << "- Leg raises: 3 sets of 12 reps" << endl << endl;

    cout << "Day 3: Lower Body - Strength Training" << endl << endl;
    cout << "- Squats: 4 sets of 8 reps" << endl;
    cout << "- Deadlifts: 4 sets of 8 reps" << endl;
    cout << "- Lunges: 3 sets of 10 reps per leg" << endl;
    cout << "- Calf raises: 3 sets of 12 reps" << endl << endl;

    cout << "Day 4: Cardio and Abs" << endl << endl;
    cout << "- 30 minutes of high-intensity interval training (HIIT) cardio (running, cycling, or jumping rope)" << endl;
    cout << "- Bicycle crunches: 3 sets of 15 reps" << endl;
    cout << "- Plank with leg lifts: 3 sets of 10 reps per side" << endl;
    cout << "- Mountain climbers: 3 sets of 15 reps per leg" << endl << endl;

    cout << "Day 5: Full Body - Strength Training" << endl << endl;
    cout << "- Dumbbell chest press: 4 sets of 10 reps" << endl;
    cout << "- Lat pulldowns: 4 sets of 10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 10 reps" << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Bicep curls: 3 sets of 12 reps" << endl << endl;

    cout << "Day 6: Active Rest Day" << endl << endl; 
    cout << "- Engage in a low-intensity activity such as yoga, hiking, or swimming to promote recovery and relaxation." << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //med age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Chest and Triceps" << endl << endl;
    cout << "- Barbell bench press: 3 sets of 8 reps" << endl;
    cout << "- Incline dumbbell press: 3 sets of 10 reps" << endl;
    cout << "- Cable flyes: 3 sets of 12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10 reps" << endl;
    cout << "- Tricep pushdowns: 3 sets of 12 reps" << endl;
    cout << endl;

    cout << "Day 2: Back and Biceps" << endl << endl;
    cout << "- Deadlifts: 3 sets of 8 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 10 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 12 reps" << endl;
    cout << "- Barbell curls: 3 sets of 10 reps" << endl;
    cout << "- Hammer curls: 3 sets of 12 reps" << endl;
    cout << endl;

    cout << "Day 3: Legs" << endl << endl;
    cout << "- Squats: 3 sets of 8 reps" << endl;
    cout << "- Lunges: 3 sets of 10 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Leg curls: 3 sets of 10 reps" << endl;
    cout << "- Calf raises: 3 sets of 12 reps" << endl;
    cout << endl;

    cout << "Day 4: Shoulders and Abs" << endl << endl;
    cout << "- Shoulder press: 3 sets of 8 reps" << endl;
    cout << "- Lateral raises: 3 sets of 10 reps" << endl;
    cout << "- Front raises: 3 sets of 12 reps" << endl;
    cout << "- Russian twists: 3 sets of 10 reps per side" << endl;
    cout << "- Plank: 3 sets of 30 seconds" << endl;
    cout << endl;

    cout << "Day 5: Cardio" << endl << endl;
    cout << "- Choose your preferred cardio exercise (running, cycling, swimming, etc.) and perform it for 30-45 minutes at a moderate intensity." << endl;
    cout << endl;

    cout << "Day 6: Full Body" << endl << endl;
    cout << "- Squats: 3 sets of 8 reps" << endl;
    cout << "- Bench press: 3 sets of 10 reps" << endl;
    cout << "- Bent-over rows: 3 sets of 10 reps" << endl;
    cout << "- Shoulder press: 3 sets of 10 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10 reps" << endl;
    cout << "- Leg press: 3 sets of 12 reps" << endl;
    cout << "- Calf raises: 3 sets of 12 reps" << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }

        //high age
            
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //high age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
             cout << "Day 1: Upper Body" << endl << endl;
    cout << "- Dumbbell bench press: 3 sets of 12 reps" << endl;
    cout << "- Seated rows: 3 sets of 12 reps" << endl;
    cout << "- Dumbbell shoulder press: 3 sets of 12 reps" << endl;
    cout << "- Bicep curls: 3 sets of 12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 12 reps" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Choose low-impact cardio exercises such as brisk walking, cycling, or swimming for 30 minutes at a moderate intensity." << endl << endl;

    cout << "Day 3: Lower Body" << endl << endl; 
    cout << "- Bodyweight squats: 3 sets of 12 reps" << endl;
    cout << "- Lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Leg press machine or wall sit: 3 sets of 12 reps" << endl;
    cout << "- Standing calf raises: 3 sets of 12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full Body" << endl << endl;
    cout << "- Push-ups: 3 sets of 12 reps" << endl;
    cout << "- Lat pulldowns or assisted pull-ups: 3 sets of 12 reps" << endl;
    cout << "- Leg extensions: 3 sets of 12 reps" << endl;
    cout << "- Leg curls: 3 sets of 12 reps" << endl;
    cout << "- Plank: Hold for 30 seconds, repeat 3 times" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body" << endl << endl;
    cout << "- Dumbbell bench press: 3 sets of 10-12 reps" << endl;
    cout << "- Seated rows: 3 sets of 10-12 reps" << endl;
    cout << "- Shoulder press: 3 sets of 10-12 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Choose low-impact cardio exercises such as brisk walking, cycling, or swimming for 30 minutes." << endl << endl;

    cout << "Day 3: Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 10-12 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 10-12 reps" << endl;
    cout << "- Calf raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full Body" << endl << endl;
    cout << "- Push-ups: 3 sets of 10-12 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 10-12 reps" << endl;
    cout << "- Leg extensions: 3 sets of 10-12 reps" << endl;
    cout << "- Hamstring curls: 3 sets of 10-12 reps" << endl;
    cout << "- Plank: Hold for 30 seconds, repeat 3 times" << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
          else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //high age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body" << endl << endl;
    cout << "- Dumbbell bench press: 3 sets of 10-12 reps" << endl;
    cout << "- Seated rows: 3 sets of 10-12 reps" << endl;
    cout << "- Shoulder press: 3 sets of 10-12 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Choose low-impact cardio exercises such as brisk walking, cycling, or swimming for 30 minutes." << endl << endl;

    cout << "Day 3: Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 10-12 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 10-12 reps" << endl;
    cout << "- Calf raises: 3 sets of 10-12 reps" << endl;
    cout << "- Plank: Hold for 30 seconds, repeat 3 times" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full Body" << endl << endl;
    cout << "- Push-ups: 3 sets of 10-12 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 10-12 reps" << endl;
    cout << "- Leg extensions: 3 sets of 10-12 reps" << endl;
    cout << "- Hamstring curls: 3 sets of 10-12 reps" << endl;
    cout << "- Plank: Hold for 30 seconds, repeat 3 times" << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //high age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Upper Body" << endl << endl;
    cout << "- Dumbbell bench press: 3 sets of 10-12 reps" << endl;
    cout << "- Seated rows: 3 sets of 10-12 reps" << endl;
    cout << "- Shoulder press: 3 sets of 10-12 reps" << endl;
    cout << "- Bicep curls: 3 sets of 10-12 reps" << endl;
    cout << "- Tricep dips: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Choose low-impact cardio exercises such as brisk walking, cycling, or swimming for 30 minutes." << endl << endl;

    cout << "Day 3: Lower Body" << endl << endl;
    cout << "- Squats: 3 sets of 10-12 reps" << endl;
    cout << "- Lunges: 3 sets of 10-12 reps per leg" << endl;
    cout << "- Leg press: 3 sets of 10-12 reps" << endl;
    cout << "- Calf raises: 3 sets of 10-12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Full Body" << endl << endl;
    cout << "- Push-ups: 3 sets of 10-12 reps" << endl;
    cout << "- Lat pulldowns: 3 sets of 10-12 reps" << endl;
    cout << "- Leg extensions: 3 sets of 10-12 reps" << endl;
    cout << "- Hamstring curls: 3 sets of 10-12 reps" << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting" << endl << endl;
    cout << "- Squats: 3 sets of 12 reps" << endl;
    cout << "- Chest Press: 3 sets of 12 reps" << endl;
    cout << "- Lat Pulldowns: 3 sets of 12 reps" << endl;
    cout << "- Shoulder Press: 3 sets of 12 reps" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Brisk Walking: 30 minutes" << endl;
    cout << "- Stationary Bike: 20 minutes" << endl << endl;

    cout << "Day 3: Light Weightlifting" << endl << endl;
    cout << "- Lunges: 3 sets of 12 reps per leg" << endl;
    cout << "- Bent-Over Rows: 3 sets of 12 reps" << endl;
    cout << "- Bicep Curls: 3 sets of 12 reps" << endl;
    cout << "- Tricep Dips: 3 sets of 12 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Cardio" << endl << endl;
    cout << "- Elliptical Trainer: 30 minutes" << endl;
    cout << "- Jumping Jacks: 3 sets of 20 reps" << endl;
    cout << "- Mountain Climbers: 3 sets of 12 reps" << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //high age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting" << endl << endl;
    cout << "- Exercise 1: Chest Press - 3 sets of 12 reps" << endl;
    cout << "- Exercise 2: Lat Pulldowns - 3 sets of 12 reps" << endl;
    cout << "- Exercise 3: Shoulder Press - 3 sets of 12 reps" << endl;
    cout << "- Exercise 4: Leg Press - 3 sets of 12 reps" << endl;
    cout << "- Exercise 5: Plank - 3 sets of 30 seconds" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Exercise 1: Treadmill Running - 30 minutes" << endl;
    cout << "- Exercise 2: Stationary Bike - 20 minutes" << endl << endl;

    cout << "Day 3: Light Weightlifting" << endl << endl;
    cout << "- Exercise 1: Squats - 3 sets of 12 reps" << endl;
    cout << "- Exercise 2: Bent-Over Rows - 3 sets of 12 reps" << endl;
    cout << "- Exercise 3: Bicep Curls - 3 sets of 12 reps" << endl;
    cout << "- Exercise 4: Tricep Dips - 3 sets of 12 reps" << endl;
    cout << "- Exercise 5: Bicycle Crunches - 3 sets of 15 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Cardio" << endl << endl;
    cout << "- Exercise 1: Elliptical Trainer - 30 minutes" << endl;
    cout << "- Exercise 2: Jumping Jacks - 3 sets of 20 reps" << endl;
    cout << "- Exercise 3: Mountain Climbers - 3 sets of 12 reps" << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //high age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting" << endl << endl;
    cout << "- Exercise 1: Dumbbell Bench Press - 3 sets of 12 reps" << endl;
    cout << "- Exercise 2: Seated Rows - 3 sets of 12 reps" << endl;
    cout << "- Exercise 3: Shoulder Press - 3 sets of 12 reps" << endl;
    cout << "- Exercise 4: Leg Press - 3 sets of 12 reps" << endl;
    cout << "- Exercise 5: Plank - 3 sets of 30 seconds" << endl << endl;

    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Exercise 1: Treadmill Jogging - 30 minutes" << endl;
    cout << "- Exercise 2: Stationary Bike - 20 minutes" << endl << endl;

    cout << "Day 3: Light Weightlifting" << endl << endl;
    cout << "- Exercise 1: Squats - 3 sets of 12 reps" << endl;
    cout << "- Exercise 2: Lat Pulldowns - 3 sets of 12 reps" << endl;
    cout << "- Exercise 3: Bicep Curls - 3 sets of 12 reps" << endl;
    cout << "- Exercise 4: Tricep Dips - 3 sets of 12 reps" << endl;
    cout << "- Exercise 5: Bicycle Crunches - 3 sets of 15 reps" << endl << endl;

    cout << "Day 4: Rest and Recovery" << endl << endl;

    cout << "Day 5: Cardio" << endl << endl;
    cout << "- Exercise 1: Elliptical Trainer - 30 minutes" << endl;
    cout << "- Exercise 2: Jumping Jacks - 3 sets of 20 reps" << endl;
    cout << "- Exercise 3: Mountain Climbers - 3 sets of 12 reps" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting" << endl << endl;
    cout << "- Exercise 1: Barbell Squats - 3 sets of 10 reps" << endl;
    cout << "- Exercise 2: Dumbbell Bench Press - 3 sets of 10 reps" << endl;
    cout << "- Exercise 3: Lat Pulldowns - 3 sets of 10 reps" << endl;
    cout << "- Exercise 4: Leg Press - 3 sets of 10 reps" << endl;
    cout << "- Exercise 5: Plank - 3 sets of 30 seconds" << endl;
    cout << endl;
    
    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Exercise 1: Treadmill - 30 minutes of moderate intensity" << endl;
    cout << "- Exercise 2: Stationary Bike - 20 minutes of interval training" << endl;
    cout << "- Exercise 3: Jumping Jacks - 3 sets of 15 reps" << endl;
    cout << "- Exercise 4: Mountain Climbers - 3 sets of 12 reps" << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //high age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Workout Program To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Day 1: Light Weightlifting" << endl << endl;
    cout << "- Exercise 1: Barbell Squats - 3 sets of 10 reps" << endl;
    cout << "- Exercise 2: Dumbbell Bench Press - 3 sets of 10 reps" << endl;
    cout << "- Exercise 3: Lat Pulldowns - 3 sets of 10 reps" << endl;
    cout << "- Exercise 4: Leg Press - 3 sets of 10 reps" << endl;
    cout << "- Exercise 5: Plank - 3 sets of 30 seconds" << endl;
    cout << endl;
    
    cout << "Day 2: Cardio" << endl << endl;
    cout << "- Exercise 1: Treadmill - 30 minutes of moderate intensity" << endl;
    cout << "- Exercise 2: Stationary Bike - 20 minutes of interval training" << endl;
    cout << "- Exercise 3: Jumping Jacks - 3 sets of 15 reps" << endl;
    cout << "- Exercise 4: Mountain Climbers - 3 sets of 12 reps" << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        
          
    
        
      
    //lean or bulk
    //18-35  36-55   56-and up
    //5'6- and below  5'7-6'0  6'1-and up
    //130- and below  131-180  181-and up
        }
  return false;
}

bool manager::meal(persons* person){

    if((person->getGoal() == "lean") || (person->getGoal() == "Lean")){
        meallean(person);
    }
    else if((person->getGoal() == "bulk") || (person->getGoal() == "Bulk")){
        mealbulk(person);
    }
    return false;
}

bool manager::mealbulk(persons* person){
    cout << endl << ".................................................................................... Bulk Meal Plan: ...................................................................................." << endl << endl;
    cout << "Here Are Your Stats:" << endl << endl;  
    cout << "----User Name----: " << person->getName() << endl << endl;
    cout << "----Height----: " << person->getHeight() << endl << endl;
    cout << "----Weight----: " << person->getWeight() << endl << endl;
    cout << "----Age----: " << person->getAge() << endl << endl;
    cout << "Enter Any Key To Get Your Meal Plan Or Enter Q To Quit!" << endl << endl;

    string o;
    cin >> o;

    if((o == "q") || (o == "Q")){
        return false;
    }
    
    
          
    cout << endl << "Cooking Your Personalized Meal Plan Please Wait....." << endl << endl;
    sleep(3);

    if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //cout << "low age /low weight /low height";
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites scrambled with spinach and bell peppers" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- A handful of almonds and a piece of fruit (e.g., apple or banana)" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- Steamed broccoli and quinoa" << endl;
    cout << "- Mixed green salad with olive oil and lemon dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Protein shake with your choice of protein powder, almond milk, and a tablespoon of almond butter" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- Roasted sweet potatoes and asparagus" << endl;
    cout << "- Side salad with mixed greens, cherry tomatoes, and balsamic vinegar dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Cottage cheese with sliced cucumbers and cherry tomatoes" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, carrots) and brown rice" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Greek yogurt with a drizzle of honey and a sprinkle of granola" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of mixed berries" << endl;
    cout << "- 1 cup of low-fat Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein smoothie: Blend 1 scoop of whey protein powder, 1 cup of almond milk, 1 tablespoon of almond butter, and 1 medium banana." << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- Quinoa with mixed vegetables (broccoli, bell peppers, and carrots)" << endl;
    cout << "- Side salad with mixed greens, cherry tomatoes, and balsamic vinaigrette dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small handful of almonds" << endl;
    cout << "- 1 medium apple" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- 1 cup of roasted sweet potatoes" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- 1 serving of low-fat cottage cheese" << endl;
    cout << "- Sliced cucumber and carrot sticks" << endl << endl; 

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with broccoli, snow peas, and brown rice" << endl;
    cout << "- 1 cup of mixed fruit salad" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- 1 serving of Greek yogurt with a drizzle of honey and a sprinkle of granola" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //low age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- Scrambled egg whites with spinach, tomatoes, and onions" << endl;
    cout << "- Whole-grain toast with almond butter" << endl;
    cout << "- Fresh fruit salad" << endl;
    cout << "- Greek yogurt with a sprinkle of granola" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake: Blend whey protein powder, almond milk, a banana, and a handful of spinach" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with herbs and spices" << endl;
    cout << "- Quinoa pilaf with mixed vegetables (broccoli, bell peppers, and zucchini)" << endl;
    cout << "- Mixed green salad with a drizzle of olive oil and lemon dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs with carrot and celery sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon fillet with dill" << endl;
    cout << "- Roasted sweet potatoes and steamed asparagus" << endl;
    cout << "- Quinoa and mixed green salad with cherry tomatoes and balsamic vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Cottage cheese with sliced cucumbers and cherry tomatoes" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with broccoli, bell peppers, and brown rice" << endl;
    cout << "- Sautéed kale with garlic and olive oil" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Greek yogurt topped with sliced almonds and a drizzle of honey" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //low age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 scrambled eggs with spinach, mushrooms, and onions" << endl;
    cout << "- 2 slices of whole-grain toast with avocado" << endl;
    cout << "- 1 cup of mixed berries" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake: Blend 1 scoop of whey protein powder, 1 cup of almond milk, 1 tablespoon of almond butter, and 1 medium banana." << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- Quinoa with mixed vegetables (broccoli, bell peppers, and carrots)" << endl;
    cout << "- Mixed green salad with olive oil and balsamic vinegar dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small handful of almonds" << endl;
    cout << "- 1 medium apple" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Side salad with mixed greens, cherry tomatoes, and lemon vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Cottage cheese with sliced cucumbers and cherry tomatoes" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with broccoli, snow peas, and quinoa" << endl << endl;
    cout << "- Roasted sweet potatoes" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Greek yogurt with a drizzle of honey and a sprinkle of granola" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- Scrambled egg whites with spinach, tomatoes, and onions" << endl;
    cout << "- Whole-grain toast with almond butter" << endl;
    cout << "- Fresh fruit salad" << endl;
    cout << "- Greek yogurt with a sprinkle of granola" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake: Blend whey protein powder, almond milk, a banana, and a handful of spinach" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with herbs and spices" << endl;
    cout << "- Quinoa pilaf with mixed vegetables (broccoli, bell peppers, and zucchini)" << endl;
    cout << "- Mixed green salad with a drizzle of olive oil and balsamic vinegar dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs with carrot and celery sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon fillet with dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Side salad with mixed greens, cherry tomatoes, and lemon vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Cottage cheese with sliced cucumbers and cherry tomatoes" << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with broccoli, snow peas, and brown rice" << endl;
    cout << "- Roasted sweet potatoes" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Greek yogurt with a drizzle of honey and a sprinkle of granola" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //low age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast seasoned with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Side salad with leafy greens and a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //low age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites with spinach and mushroom omelette" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Mixed green salad with a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon fillet with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Side salad with mixed greens and cherry tomatoes" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Roasted sweet potatoes" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast seasoned with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Side salad with leafy greens and a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
          //low age /high weight /tall height
          cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 scrambled egg whites with spinach and mushrooms" << endl;
    cout << "- 1 cup of cooked oatmeal with berries and a tablespoon of almond butter" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of low-fat Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a handful of almonds" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with herbs and spices" << endl;
    cout << "- Quinoa or brown rice" << endl;
    cout << "- Steamed broccoli and roasted sweet potatoes" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Cottage cheese with sliced cucumbers and cherry tomatoes" << endl << endl; 

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Whole wheat pasta or quinoa" << endl;
    cout << "- Sautéed asparagus and mixed bell peppers" << endl << endl; 

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with a sprinkle of granola and mixed berries" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, carrots, snap peas)" << endl;
    cout << "- Brown rice or quinoa" << endl;
    cout << "- Mixed green salad with a light dressing" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
            
        //med age
            
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //med age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl; 
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast seasoned with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Side salad with leafy greens and a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl; 
    cout << "- Grilled chicken breast seasoned with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Side salad with leafy greens and a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //med age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl; 
    cout << "- Grilled chicken breast seasoned with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Side salad with leafy greens and a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //med age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 4 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl; 
    cout << "- Grilled chicken breast seasoned with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Side salad with leafy greens and a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 4 egg whites scrambled with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole-grain toast with avocado" << endl;
    cout << "- 1 small fruit of your choice" << endl;
    cout << "- 1 cup of Greek yogurt" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast seasoned with herbs and spices" << endl;
    cout << "- Quinoa salad with mixed vegetables (broccoli, bell peppers, and cucumbers)" << endl;
    cout << "- Side salad with leafy greens and a light dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs and carrot sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Steamed asparagus and brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef steak or tofu stir-fry with mixed vegetables (broccoli, bell peppers, and snap peas)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
           //med age /med weight /tall height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- Scrambled eggs with spinach and bell peppers" << endl;
    cout << "- Whole-grain toast with avocado" << endl;
    cout << "- Fresh fruit salad" << endl;
    cout << "- Greek yogurt with almonds" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake with whey protein, mixed berries, and almond milk" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with quinoa and steamed broccoli" << endl;
    cout << "- Mixed green salad with cherry tomatoes and balsamic vinaigrette" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs with carrot sticks and hummus" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Brown rice with roasted vegetables (zucchini, bell peppers, and onions)" << endl;
    cout << "- Spinach salad with walnuts and feta cheese" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Cottage cheese with sliced peaches and a sprinkle of cinnamon" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef or tofu stir-fry with mixed stir-fried vegetables (broccoli, snap peas, and mushrooms)" << endl;
    cout << "- Sweet potato wedges baked with olive oil and spices" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Protein bar with nuts and seeds" << endl << endl; 

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
           //med age /high weight /low height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and mushrooms" << endl;
    cout << "- 2 slices of whole-grain toast with avocado" << endl;
    cout << "- 1 cup of Greek yogurt with berries" << endl << endl;

    cout << "Snack 1:" << endl << endl; 
    cout << "- Protein smoothie made with whey protein, almond milk, and a banana" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with quinoa and steamed broccoli" << endl;
    cout << "- Mixed green salad with cherry tomatoes and a light vinaigrette dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hard-boiled eggs with carrot sticks and hummus" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with lemon and dill" << endl;
    cout << "- Brown rice with roasted vegetables (such as Brussels sprouts, bell peppers, and onions)" << endl;
    cout << "- Side of mixed greens with a drizzle of olive oil and vinegar" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Greek yogurt with sliced almonds and a drizzle of honey" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Lean beef or tofu stir-fry with mixed vegetables (such as broccoli, snap peas, and mushrooms)" << endl;
    cout << "- Quinoa or whole-grain pasta as a side" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with fresh berries" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
  cout << "- 4-6 egg whites with 1 whole egg" << endl;
  cout << "- 1 cup of oatmeal with a sprinkle of cinnamon" << endl;
  cout << "- 1 medium-sized fruit (e.g., apple, banana, or orange)" << endl << endl;

  cout << "Snack 1:" << endl << endl;
  cout << "- 1 serving of Greek yogurt with mixed berries" << endl << endl;

  cout << "Meal 2:" << endl << endl;
  cout << "- Grilled chicken breast (6-8 ounces)" << endl;
  cout << "- 1 cup of brown rice or quinoa" << endl;
  cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

  cout << "Snack 2:" << endl << endl;
  cout << "- 1 small handful of mixed nuts (almonds, walnuts, and cashews)" << endl << endl;

  cout << "Meal 3:" << endl << endl;
  cout << "- Grilled salmon or lean steak (6-8 ounces)" << endl;
  cout << "- Large mixed green salad with a variety of vegetables (spinach, tomatoes, cucumbers)" << endl;
  cout << "- 2 tablespoons of olive oil and vinegar dressing" << endl << endl;

  cout << "Snack 3:" << endl << endl;
  cout << "- 1 small protein shake or a protein bar" << endl << endl;

  cout << "Meal 4:" << endl << endl;
  cout << "- Grilled turkey breast or tofu (6-8 ounces)" << endl;
  cout << "- 1 medium sweet potato or 1 cup of quinoa" << endl;
  cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

  cout << "Snack 4:" << endl << endl;
  cout << "- 1 small handful of cherry tomatoes or baby carrots" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //med age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
  cout << "- 3 scrambled eggs with vegetables (spinach, bell peppers, and mushrooms)" << endl;
  cout << "- 2 slices of whole grain toast with avocado spread" << endl;
  cout << "- 1 medium-sized fruit (e.g., a banana or an apple)" << endl << endl;

  cout << "Snack 1:" << endl << endl;
  cout << "- Greek yogurt with a handful of mixed nuts (almonds, walnuts, and cashews)" << endl << endl;

  cout << "Meal 2:" << endl << endl;
  cout << "- Grilled chicken breast (8 ounces)" << endl;
  cout << "- 1 cup of quinoa or brown rice" << endl;
  cout << "- Steamed broccoli and carrots" << endl << endl;

  cout << "Snack 2:" << endl << endl;
  cout << "- Protein shake with almond milk and a tablespoon of almond butter" << endl << endl;

  cout << "Meal 3:" << endl << endl;
  cout << "- Grilled salmon (8 ounces)" << endl;
  cout << "- Large mixed green salad with tomatoes, cucumbers, and a drizzle of olive oil and lemon juice" << endl;
  cout << "- 1 medium sweet potato" << endl << endl;

  cout << "Snack 3:" << endl << endl;
  cout << "- Cottage cheese with sliced pineapple or mixed berries" << endl << endl;

  cout << "Meal 4:" << endl << endl;
  cout << "- Lean beef steak (8 ounces)" << endl;
  cout << "- Baked sweet potato fries" << endl;
  cout << "- Grilled asparagus" << endl << endl;

  cout << "Snack 4:" << endl << endl;
  cout << "- Hard-boiled eggs with cherry tomatoes" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }

        //high age
            
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //high age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
  cout << "- 1 cup of oatmeal with a sprinkle of cinnamon" << endl;
  cout << "- 2 boiled eggs" << endl;
  cout << "- 1 small apple" << endl << endl; 

  cout << "Snack 1:" << endl << endl;
  cout << "- Greek yogurt with mixed berries" << endl << endl;

  cout << "Meal 2:" << endl << endl;
  cout << "- Grilled chicken breast (4 ounces)" << endl;
  cout << "- 1/2 cup of brown rice or quinoa" << endl;
  cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

  cout << "Snack 2:" << endl << endl;
  cout << "- Hummus with baby carrots and celery sticks" << endl << endl;

  cout << "Meal 3:" << endl << endl;
  cout << "- Baked salmon (4 ounces)" << endl;
  cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
  cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl;

  cout << "Snack 3:" << endl << endl;
  cout << "- A handful of almonds or walnuts" << endl << endl;

  cout << "Meal 4:" << endl << endl;
  cout << "- Grilled tofu or lean turkey (4 ounces)" << endl;
  cout << "- 1 small sweet potato" << endl;
  cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

  cout << "Snack 4:" << endl << endl;
  cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
  cout << "- 1 cup of oatmeal with a sprinkle of cinnamon" << endl;
  cout << "- 3 boiled eggs (2 whites, 1 whole egg)" << endl;
  cout << "- 1 small apple" << endl << endl;

  cout << "Snack 1:" << endl << endl;
  cout << "- Greek yogurt with mixed berries" << endl << endl;

  cout << "Meal 2:" << endl << endl;
  cout << "- Grilled chicken breast (4 ounces)" << endl;
  cout << "- 1/2 cup of brown rice or quinoa" << endl;
  cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

  cout << "Snack 2:" << endl << endl;
  cout << "- Hummus with carrot and celery sticks" << endl << endl;

  cout << "Meal 3:" << endl << endl;
  cout << "- Baked salmon (4 ounces)" << endl;
  cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
  cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl;

  cout << "Snack 3:" << endl << endl;
  cout << "- A handful of almonds or walnuts" << endl << endl; 

  cout << "Meal 4:" << endl << endl;
  cout << "- Grilled tofu or lean turkey (4 ounces)" << endl;
  cout << "- 1 small sweet potato" << endl;
  cout << "- Steamed asparagus or Brussels sprouts" << endl << endl; 

  cout << "Snack 4:" << endl << endl;
  cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
          else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //high age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 1 cup of oatmeal with a sprinkle of cinnamon" << endl;
    cout << "- 3 boiled eggs (2 egg whites, 1 whole egg)" << endl;
    cout << "- 1 small apple" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Greek yogurt with mixed berries" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast (4 ounces)" << endl;
    cout << "- 1/2 cup of brown rice or quinoa" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;
 
    cout << "Snack 2:" << endl << endl;
    cout << "- Hummus with carrot and celery sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon (4 ounces)" << endl;
    cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
    cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- A handful of almonds or walnuts" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Grilled tofu or lean turkey (4 ounces)" << endl;
    cout << "- 1 small sweet potato" << endl;
    cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //high age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 1 cup of cooked steel-cut oats with a sprinkle of cinnamon" << endl;
    cout << "- 3 boiled eggs (2 egg whites, 1 whole egg)" << endl;
    cout << "- 1 small apple" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Greek yogurt with mixed berries" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast (4 ounces)" << endl;
    cout << "- 1/2 cup of quinoa or brown rice" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hummus with carrot and celery sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon (4 ounces)" << endl;
    cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
    cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- A handful of almonds or walnuts" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Grilled tofu or lean turkey (4 ounces)" << endl;
    cout << "- 1 small sweet potato" << endl;
    cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 1 cup of cooked steel-cut oats with a sprinkle of cinnamon" << endl;
    cout << "- 3 boiled eggs (2 egg whites, 1 whole egg)" << endl;
    cout << "- 1 small apple" << endl << endl;

    cout << "Snack 1:" << endl << endl ;
    cout << "- Greek yogurt with mixed berries" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast (4 ounces)" << endl;
    cout << "- 1/2 cup of quinoa or brown rice" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hummus with carrot and celery sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon (4 ounces)" << endl;
    cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
    cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- A handful of almonds or walnuts" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Grilled tofu or lean turkey (4 ounces)" << endl;
    cout << "- 1 small sweet potato" << endl;
    cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //high age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 1 cup of cooked quinoa with a sprinkle of herbs and spices" << endl;
    cout << "- 3 egg whites and 1 whole egg, scrambled" << endl;
    cout << "- 1 small banana" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Greek yogurt with mixed berries" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast (4 ounces)" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Hummus with cucumber and bell pepper slices" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon (4 ounces)" << endl;
    cout << "- Mixed green salad with tomatoes and avocado" << endl;
    cout << "- 1 tablespoon of olive oil and lemon dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Handful of almonds or walnuts" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Grilled tofu or lean beef (4 ounces)" << endl;
    cout << "- 1 small sweet potato" << endl;
    cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with sliced strawberries or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //high age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 1 cup of cooked oatmeal with added protein powder" << endl;
    cout << "- 3 boiled eggs (2 egg whites, 1 whole egg)" << endl;
    cout << "- 1 small apple" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Greek yogurt with mixed berries" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast (4 ounces)" << endl;
    cout << "- 1/2 cup of quinoa or brown rice" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl;

    cout << "Snack 2:" << endl;
    cout << "- Hummus with carrot and celery sticks" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon (4 ounces)" << endl;
    cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
    cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- A handful of almonds or walnuts" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Grilled tofu or lean turkey (4 ounces)" << endl;
    cout << "- 1 small sweet potato" << endl;
    cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites and 1 whole egg scrambled" << endl;
    cout << "- 1 cup of cooked oatmeal with added protein powder" << endl;
    cout << "- 1 small apple" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Greek yogurt with mixed berries" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast (6 ounces)" << endl;
    cout << "- 1/2 cup of quinoa or brown rice" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Protein shake with almond milk" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon (6 ounces)" << endl;
    cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
    cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Handful of almonds or walnuts" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Grilled tofu or lean beef (6 ounces)" << endl;
    cout << "- 1 small sweet potato" << endl;
    cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //high age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Bulk Up Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 egg whites and 1 whole egg scrambled" << endl;
    cout << "- 1 cup of cooked oatmeal with added protein powder" << endl;
    cout << "- 1 small apple" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Greek yogurt with mixed berries" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast (6 ounces)" << endl;
    cout << "- 1/2 cup of quinoa or brown rice" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and green beans)" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Protein shake with almond milk" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon (6 ounces)" << endl;
    cout << "- Mixed green salad with tomatoes and cucumbers" << endl;
    cout << "- 1 tablespoon of olive oil and vinegar dressing" << endl << endl; 

    cout << "Snack 3:" << endl << endl;
    cout << "- Handful of almonds or walnuts" << endl << endl;

    cout << "Meal 4:" << endl << endl;
    cout << "- Grilled tofu or lean beef (6 ounces)" << endl;
    cout << "- 1 small sweet potato" << endl;
    cout << "- Steamed asparagus or Brussels sprouts" << endl << endl;

    cout << "Snack 4:" << endl << endl;
    cout << "- Cottage cheese with sliced peaches or pineapple" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        
        
        }

    return false;
}

bool manager::meallean(persons* person){

    cout << endl << ".................................................................................... Lean Meal Plan: ...................................................................................." << endl << endl;
    cout << "Here Are Your Stats:" << endl << endl;  
    cout << "----User Name----: " << person->getName() << endl << endl;
    cout << "----Height----: " << person->getHeight() << endl << endl;
    cout << "----Weight----: " << person->getWeight() << endl << endl;
    cout << "----Age----: " << person->getAge() << endl << endl;
    cout << "Enter Any Key To Get Your Meal Plan Or Enter Q To Quit!" << endl << endl;

    string o;
    cin >> o;

    if((o == "q") || (o == "Q")){
        return false;
    }
          
        cout << endl << "Cooking Your Personalized Meal Plan Please Wait....." << endl << endl;
        sleep(3);
          
        if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //cout << "low age /low weight /low height";
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl << endl; 

    // Snack 1
      cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl << endl;

    // Meal 2 (Lunch)
    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl << endl;

    // Snack 2
    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl << endl;

    // Meal 3 (Dinner)
    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl << endl;

    // Snack 3
    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl << endl;

    // Hydration
    cout << "Hydration:" << endl << endl;
    cout << "- Drink at least 8-10 cups of water per day" << endl;
    cout << "- Green tea or herbal tea can be included for added variety" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl << endl;

    // Snack 1
    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl << endl;

    // Meal 2 (Lunch)
    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl << endl;

    // Snack 2
    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl << endl;

    // Meal 3 (Dinner)
    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl << endl;

    // Snack 3
    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl << endl;

    // Hydration
    cout << "Hydration:" << endl << endl;
    cout << "- Drink at least 8-10 cups of water per day" << endl;
    cout << "- Green tea or herbal tea can be included for added variety" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;

        }
        else if((person->getAge() <= 35) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //1ow age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl << endl;

    // Snack 1
    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl << endl;

    // Meal 2 (Lunch)
    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl << endl;

    // Snack 2
    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl << endl;

    // Meal 3 (Dinner)
    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl << endl;

    // Snack 3
    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl << endl;

    // Hydration
    cout << "Hydration:" << endl << endl;
    cout << "- Drink at least 8-10 cups of water per day" << endl;
    cout << "- Green tea or herbal tea can be included for added variety" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //111low age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl;
    cout << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl;
    cout << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl;
    cout << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl;
    cout << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl;
    cout << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl;
    cout << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl;
    cout << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl;
    cout << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl;
    cout << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl;
    cout << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //low age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl;

    cout << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl;

    cout << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl;

    cout << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl;

    cout << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl;

    cout << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //low age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //low age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 slice of whole-grain toast" << endl;
    cout << "- 1 cup of Greek yogurt with mixed berries" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium apple" << endl;
    cout << "- 1 ounce of almonds" << endl << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed broccoli and carrots" << endl;
    cout << "- Mixed green salad with olive oil and vinegar dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- 1 small container of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl;
    cout << "- Carrot sticks" << endl << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon fillet" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Roasted asparagus and bell peppers" << endl;
    cout << "- Spinach salad with lemon-tahini dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- 1 protein shake with almond milk" << endl;
    cout << "- 1 small handful of baby carrots" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() <= 35) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
          //low age /high weight /tall height
          cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 Scrambled eggs with spinach and tomatoes" << endl;
    cout << "- 1 cup of Greek yogurt with a handful of mixed berries" << endl;
    cout << "- 1 slice of whole-grain toast" << endl << endl;

    // Snack 1
    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium-sized apple" << endl;
    cout << "- 1 ounce of almonds" << endl << endl;

    // Meal 2
    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with quinoa and steamed vegetables (broccoli, carrots, and asparagus)" << endl;
    cout << "- 1 small sweet potato" << endl << endl;

    // Snack 2
    cout << "Snack 2:" << endl << endl;
    cout << "- 1 serving of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural peanut butter" << endl << endl;

    // Meal 3
    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with brown rice and sautéed kale" << endl;
    cout << "- 1/2 avocado" << endl << endl;

    // Snack 3
    cout << "Snack 3:" << endl << endl;
    cout << "- 1 small banana" << endl;
    cout << "- 1/2 cup of low-fat Greek yogurt" << endl << endl;

    // Hydration
    cout << "Hydration:" << endl << endl;
    cout << "- Aim to drink at least 3 liters of water per day." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
            
        //med age
            
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //med age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 Egg whites scrambled with spinach and tomatoes" << endl;
    cout << "- 1 small serving of oatmeal with berries and almond slices" << endl;
    cout << "- 1 cup of green tea" << endl << endl;

    // Snack 1
    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium-sized apple" << endl;
    cout << "- 1 serving of low-fat Greek yogurt" << endl << endl;

    // Meal 2
    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with quinoa and mixed vegetables (broccoli, carrots, and bell peppers)" << endl;
    cout << "- 1/2 avocado" << endl << endl;

    // Snack 2
    cout << "Snack 2:" << endl << endl;
    cout << "- 1 serving of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural almond butter" << endl << endl;

    // Meal 3
    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with brown rice and steamed asparagus" << endl;
    cout << "- 1 cup of herbal tea" << endl << endl;

    // Snack 3
    cout << "Snack 3:" << endl << endl;
    cout << "- 1 small banana" << endl;
    cout << "- 1/4 cup of mixed nuts (almonds, walnuts, and pistachios)" << endl << endl;

    // Hydration
    cout << "Hydration:" << endl << endl;
    cout << "- Aim to drink at least 2.5 to 3 liters of water per day." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 Egg whites scrambled with spinach and tomatoes" << endl;
    cout << "- 1 small serving of oatmeal with berries and almond slices" << endl;
    cout << "- 1 cup of green tea" << endl << endl;

    // Snack 1
    cout << "Snack 1:" << endl << endl;
    cout << "- 1 medium-sized apple" << endl;
    cout << "- 1 serving of low-fat Greek yogurt" << endl << endl;

    // Meal 2
    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast with quinoa and mixed vegetables (broccoli, carrots, and bell peppers)" << endl;
    cout << "- 1/2 avocado" << endl << endl;

    // Snack 2
    cout << "Snack 2:" << endl << endl;
    cout << "- 1 serving of cottage cheese" << endl;
    cout << "- 1 tablespoon of natural almond butter" << endl << endl;

    // Meal 3
    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon with brown rice and steamed asparagus" << endl;
    cout << "- 1 cup of herbal tea" << endl << endl;

    // Snack 3
    cout << "Snack 3:" << endl << endl;
    cout << "- 1 small banana" << endl;
    cout << "- 1/4 cup of mixed nuts (almonds, walnuts, and pistachios)" << endl << endl;

    // Hydration
    cout << "Hydration:" << endl << endl;
    cout << "- Aim to drink at least 2.5 to 3 liters of water per day." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //med age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and mushrooms" << endl;
    cout << "- 1 slice of whole wheat toast" << endl;
    cout << "- 1 cup of mixed berries" << endl << endl;

    // Snack 1
    cout << "Snack 1:" << endl << endl;
    cout << "- 1 small Greek yogurt" << endl;
    cout << "- 1 tablespoon of almond butter" << endl << endl;

    // Meal 2
    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- Quinoa or brown rice" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and bell peppers)" << endl << endl;

    // Snack 2
    cout << "Snack 2:" << endl << endl;
    cout << "- Protein shake with mixed berries" << endl;
    cout << "- Handful of almonds" << endl << endl;

    // Meal 3
    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon" << endl;
    cout << "- Sweet potatoes" << endl;
    cout << "- Sautéed spinach or asparagus" << endl << endl;

    // Snack 3
    cout << "Snack 3:" << endl << endl;
    cout << "- Cottage cheese with sliced cucumbers" << endl;
    cout << "- 1 small apple" << endl << endl;

    // Hydration
    cout << "Hydration:" << endl << endl;
    cout << "- Aim to drink at least 2-3 liters of water throughout the day." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //med age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- 3 scrambled eggs with vegetables (spinach, bell peppers, mushrooms)" << endl;
    cout << "- 1 slice of whole wheat toast" << endl;
    cout << "- 1 cup of mixed berries" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Greek yogurt with a handful of almonds" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Grilled chicken breast" << endl;
    cout << "- Quinoa or brown rice" << endl;
    cout << "- Steamed broccoli and carrots" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Protein shake with mixed berries and almond milk" << endl;
    cout << "- 1 medium apple" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Baked salmon" << endl;
    cout << "- Sweet potatoes" << endl;
    cout << "- Sautéed asparagus" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Cottage cheese with sliced cucumbers" << endl;
    cout << "- 1 small orange" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- Scrambled eggs (3 eggs) with vegetables (spinach, bell peppers, mushrooms)" << endl;
    cout << "- Whole-grain toast" << endl;
    cout << "- A serving of Greek yogurt with berries" << endl << endl;
    
    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake with almond milk and a small handful of mixed nuts (e.g., almonds, walnuts, and cashews)" << endl << endl;
    
    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast or tofu" << endl;
    cout << "- Quinoa or brown rice" << endl;
    cout << "- Steamed broccoli and carrots" << endl << endl;
    
    cout << "Snack 2:" << endl << endl;
    cout << "- Sliced apple with natural peanut butter" << endl << endl;
    
    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon or lean beef" << endl;
    cout << "- Sweet potato" << endl;
    cout << "- Mixed green salad with cherry tomatoes and balsamic vinaigrette" << endl << endl;
    
    cout << "Snack 3:" << endl << endl;
    cout << "- Celery sticks with hummus or a small handful of edamame" << endl << endl;
    
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
           //med age /med weight /tall height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- Scrambled eggs (3 eggs) with vegetables (spinach, bell peppers, mushrooms)" << endl;
    cout << "- Whole-grain toast" << endl;
    cout << "- A serving of Greek yogurt with berries" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake with almond milk and a small handful of mixed nuts (e.g., almonds, walnuts, and cashews)" << endl << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast or tofu" << endl;
    cout << "- Quinoa or brown rice" << endl;
    cout << "- Steamed broccoli and carrots" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Sliced apple with natural peanut butter" << endl << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon or lean beef" << endl;
    cout << "- Sweet potato" << endl;
    cout << "- Mixed green salad with cherry tomatoes and balsamic vinaigrette" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Celery sticks with hummus or a small handful of edamame" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
           //med age /high weight /low height
           cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- Omelette made with 4 egg whites, spinach, mushrooms, and diced chicken breast" << endl;
    cout << "- 1 cup of cooked quinoa" << endl;
    cout << "- 1 small apple" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake with almond milk and a tablespoon of almond butter" << endl << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast or lean beef" << endl;
    cout << "- 1 cup of steamed broccoli" << endl;
    cout << "- 1/2 cup of brown rice" << endl;
    cout << "- Mixed green salad with cherry tomatoes and balsamic vinaigrette dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Greek yogurt with a handful of mixed berries" << endl << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon or tofu" << endl;
    cout << "- 1 cup of roasted sweet potatoes" << endl;
    cout << "- Steamed asparagus" << endl;
    cout << "- Quinoa and vegetable stir-fry" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Protein bar or a handful of almonds" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //med age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast):" << endl << endl;
    cout << "- 3 scrambled eggs with spinach and diced chicken breast" << endl;
    cout << "- 1 cup of oatmeal with berries" << endl;
    cout << "- 1 small banana" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein shake with almond milk and a handful of almonds" << endl << endl;

    cout << "Meal 2 (Lunch):" << endl << endl;
    cout << "- Grilled chicken breast or lean steak" << endl;
    cout << "- 1 cup of quinoa" << endl;
    cout << "- Steamed vegetables (broccoli, carrots, and cauliflower)" << endl;
    cout << "- Side salad with mixed greens and balsamic vinaigrette dressing" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Greek yogurt with sliced strawberries and a drizzle of honey" << endl << endl;

    cout << "Meal 3 (Dinner):" << endl << endl;
    cout << "- Baked salmon or tofu" << endl;
    cout << "- 1 cup of brown rice" << endl;
    cout << "- Stir-fried vegetables (bell peppers, snap peas, and mushrooms)" << endl;
    cout << "- Side salad with mixed greens and lemon-tahini dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Protein bar or a handful of mixed nuts and dried fruits" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if(((person->getAge() >= 36) && (person->getAge() <= 55)) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //med age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "- Meal 1 (Breakfast): 3 scrambled eggs with spinach and diced chicken breast, 1 cup of oatmeal with berries, and 1 small banana." << endl << endl;
    cout << "- Snack 1: Protein shake with almond milk and a handful of almonds." << endl << endl;
    cout << "- Meal 2 (Lunch): Grilled chicken breast or lean steak, 1 cup of quinoa, steamed vegetables (broccoli, carrots, and cauliflower), and a side salad with mixed greens and balsamic vinaigrette dressing." << endl << endl;
    cout << "- Snack 2: Greek yogurt with sliced strawberries and a drizzle of honey." << endl << endl;
    cout << "- Meal 3 (Dinner): Baked salmon or tofu, 1 cup of brown rice, stir-fried vegetables (bell peppers, snap peas, and mushrooms), and a side salad with mixed greens and lemon-tahini dressing." << endl << endl;
    cout << "- Snack 3: Protein bar or a handful of mixed nuts and dried fruits." << endl << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }

        //high age
            
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() <= 66)){
            //high age /low weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "- Meal 1 (Breakfast): Egg white omelet with spinach and tomatoes, a slice of whole-grain toast, and a cup of green tea." << endl << endl;
    cout << "- Snack 1: Greek yogurt with a sprinkle of nuts and berries." << endl << endl;
    cout << "- Meal 2 (Lunch): Grilled chicken breast with a side of mixed vegetables and quinoa." << endl << endl;
    cout << "- Snack 2: A handful of almonds and a small piece of fruit." << endl << endl;
    cout << "- Meal 3 (Dinner): Baked salmon with steamed asparagus and brown rice." << endl << endl;
    cout << "- Snack 3: Carrot sticks with hummus." << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() <= 130) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /low weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "- Meal 1 (Breakfast): Egg white omelet with vegetables and whole-grain toast." << endl << endl;
    cout << "- Snack 1: Greek yogurt with berries and a handful of almonds." << endl << endl;
    cout << "- Meal 2 (Lunch): Grilled chicken breast with a side of mixed greens and quinoa." << endl << endl;
    cout << "- Snack 2: Protein shake with a small piece of fruit." << endl << endl;
    cout << "- Meal 3 (Dinner): Baked fish or tofu with steamed vegetables and brown rice." << endl << endl;
    cout << "- Snack 3: Celery sticks with hummus or a handful of mixed nuts." << endl << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
          else if((person->getAge() >= 56) && (person->getWeight() <= 130) && (person->getHeight() >= 73)){
            //high age /low weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "- Meal 1 (Breakfast): Egg white omelet with vegetables and whole-grain toast." << endl << endl;
    cout << "- Snack 1: Greek yogurt with berries and a handful of almonds." << endl << endl;
    cout << "- Meal 2 (Lunch): Grilled chicken breast with a side of mixed greens and quinoa." << endl << endl;
    cout << "- Snack 2: Protein shake with a small piece of fruit." << endl << endl;
    cout << "- Meal 3 (Dinner): Baked fish or tofu with steamed vegetables and brown rice." << endl << endl;
    cout << "- Snack 3: Celery sticks with hummus or a handful of mixed nuts." << endl << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() <= 66)){
            //high age /med weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "- Meal 1 (Breakfast): Egg white omelet with spinach and whole wheat toast." << endl << endl;
    cout << "- Snack 1: Greek yogurt with berries." << endl << endl;
    cout << "- Meal 2 (Lunch): Grilled chicken breast with mixed vegetables and quinoa." << endl << endl;
    cout << "- Snack 2: Protein shake with a small handful of almonds." << endl << endl;
    cout << "- Meal 3 (Dinner): Baked salmon with steamed asparagus and brown rice." << endl << endl;
    cout << "- Snack 3: Celery sticks with peanut butter." << endl << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /med weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1 (Breakfast): Spinach and mushroom omelette with whole wheat toast" << endl << endl;
    cout << "Snack 1: Greek yogurt with berries and a handful of almonds" << endl << endl;
    cout << "Meal 2 (Lunch): Grilled chicken breast with quinoa and roasted vegetables" << endl << endl;
    cout << "Snack 2: Protein shake with a small apple" << endl << endl;
    cout << "Meal 3 (Dinner): Baked salmon with steamed broccoli and brown rice" << endl << endl;
    cout << "Snack 3: Celery sticks with almond butter" << endl << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && ((person->getWeight() >= 131) && (person->getWeight() <= 180)) && (person->getHeight() >= 73)){
            //high age /med weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- Protein: 4 oz of grilled chicken breast" << endl;
    cout << "- Carbohydrates: 1/2 cup of brown rice" << endl;
    cout << "- Vegetables: 1 cup of steamed broccoli" << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein: 1 scoop of protein powder mixed with water" << endl;
    cout << "- Fruits: 1 medium apple" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Protein: 4 oz of grilled salmon" << endl;
    cout << "- Carbohydrates: 1/2 cup of quinoa" << endl;
    cout << "- Vegetables: 1 cup of roasted asparagus" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Protein: 1 Greek yogurt" << endl;
    cout << "- Nuts: 1 handful of almonds" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Protein: 4 oz of lean beef" << endl;
    cout << "- Carbohydrates: 1 small sweet potato" << endl;
    cout << "- Vegetables: 1 cup of mixed greens with vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Protein: 1 hard-boiled egg" << endl;
    cout << "- Vegetables: 1 cup of baby carrots" << endl;

    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() <= 66)){
            //high age /high weight /low height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl;
    cout << "- Protein: 4 oz of grilled chicken breast" << endl << endl;
    cout << "- Carbohydrates: 1/2 cup of brown rice" << endl;
    cout << "- Vegetables: 1 cup of steamed broccoli" << endl << endl << endl;

    cout << "Snack 1:" << endl << endl;
    cout << "- Protein: 1 scoop of protein powder mixed with water" << endl;
    cout << "- Fruits: 1 medium apple" << endl << endl;

    cout << "Meal 2:" << endl << endl;
    cout << "- Protein: 4 oz of grilled salmon" << endl;
    cout << "- Carbohydrates: 1/2 cup of quinoa" << endl;
    cout << "- Vegetables: 1 cup of roasted asparagus" << endl << endl;

    cout << "Snack 2:" << endl << endl;
    cout << "- Protein: 1 Greek yogurt" << endl;
    cout << "- Nuts: 1 handful of almonds" << endl << endl;

    cout << "Meal 3:" << endl << endl;
    cout << "- Protein: 4 oz of lean beef" << endl;
    cout << "- Carbohydrates: 1 small sweet potato" << endl;
    cout << "- Vegetables: 1 cup of mixed greens with vinaigrette dressing" << endl << endl;

    cout << "Snack 3:" << endl << endl;
    cout << "- Protein: 1 hard-boiled egg" << endl;
    cout << "- Vegetables: 1 cup of baby carrots" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && ((person->getHeight() >= 67) && (person->getHeight() <= 72))){
            //high age /high weight /med height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- Protein Source: Chicken Breast" << endl;
    cout << "- Vegetable: Broccoli" << endl;
    cout << "- Carbohydrate: Brown Rice" << endl << endl;

    // Meal 2
    cout << "Meal 2:" << endl << endl;
    cout << "- Protein Source: Salmon" << endl;
    cout << "- Vegetable: Spinach" << endl;
    cout << "- Carbohydrate: Sweet Potato" << endl << endl;

    // Meal 3
    cout << "Meal 3:" << endl << endl;
    cout << "- Protein Source: Lean Beef" << endl;
    cout << "- Vegetable: Green Beans" << endl;
    cout << "- Carbohydrate: Quinoa" << endl << endl;

            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        }
        else if((person->getAge() >= 56) && (person->getWeight() >= 181) && (person->getHeight() >= 73)){
            //high age /high weight /tall height
            cout << ".........................................................................................................................................................................................." << endl << endl;
            cout << "Here Is A Personalized Meal Plan To Help You Gain Muscle And Maintain Your Leanness Based On The Data You Provided:" << endl << endl;
            cout << "Meal 1:" << endl << endl;
    cout << "- Protein Source: Grilled Chicken Breast" << endl;
    cout << "- Vegetable: Steamed Broccoli" << endl;
    cout << "- Carbohydrate: Quinoa" << endl;
    cout << endl;
    
    cout << "Snack 1:" << endl << endl;
    cout << "- Greek Yogurt with Berries" << endl;
    cout << endl;
    
    cout << "Meal 2:" << endl << endl;
    cout << "- Protein Source: Baked Salmon" << endl;
    cout << "- Vegetable: Roasted Asparagus" << endl;
    cout << "- Carbohydrate: Brown Rice" << endl;
    cout << endl;
    
    cout << "Snack 2:" << endl << endl;
    cout << "- Protein Shake with Almond Milk" << endl;
    cout << endl;
    
    cout << "Meal 3:" << endl << endl;
    cout << "- Protein Source: Lean Beef Steak" << endl;
    cout << "- Vegetable: Mixed Salad Greens" << endl;
    cout << "- Carbohydrate: Sweet Potato" << endl;
    cout << endl;
    
    cout << "Snack 3:" << endl << endl;
    cout << "- Hard-boiled Eggs with Sliced Cucumbers" << endl;
    cout << endl;
            cout << "To assist your body in relaxing and recovering, take part in active recovery exercises like yoga, gentle stretching, or a leisurely walk." << endl << endl;
            cout << "Enter Any Key To Return To Menu" << endl << endl;
            cout << ".........................................................................................................................................................................................." << endl << endl;
            string key;
            cin >> key;
        
        }

    return false;
}