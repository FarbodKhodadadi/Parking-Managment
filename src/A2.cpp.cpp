#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

const string REQUSET_COMMAND = "request_spot";
const string ASSIGN_COMMAND = "assign_spot";
const string CHECKOUT_COMMAND = "checkout";
const string PASSTIME_COMMAND = "pass_time";
const string CCTV_TYPE = "CCTV";
const string COVERED_TYPE = "covered";

struct Spots{

    int spotSize;
    string spotType;
    int availabilty = 0;//0 means its empty and 1 means it's occupied
    int numDay =0 ;
    
};

typedef  map<string ,int> carsMap; 
typedef  map<int , Spots> spotsMap; 
typedef  map<int , pair<int,int> > pricesMap;


void FindSpot(vector<string> inputLine ,carsMap &cars ,spotsMap &parkingSpots ,pricesMap &prices){
    
    int carSize;
    for(auto it = cars.begin(); it != cars.end() ; it++){
        if (inputLine[1] == it->first)
            carSize = it->second;
    }
    for(auto it2 =parkingSpots.begin(); it2 != parkingSpots.end() ; it2++){
        if(it2->second.availabilty==0){
            if (carSize == it2->second.spotSize){
                if(parkingSpots[it2->first].spotType == COVERED_TYPE )
                    cout << it2->first << ":" <<' '<< it2->second.spotType << ' ' << prices[carSize].first + 50 <<' '<< prices[carSize].second + 30 << endl;
                else if(parkingSpots[it2->first].spotType == CCTV_TYPE )
                    cout << it2->first << ":" <<' '<< it2->second.spotType << ' ' << prices[carSize].first + 80 <<' '<< prices[carSize].second + 60 << endl;
                else
                    cout << it2->first << ":" <<' '<< it2->second.spotType << ' ' << prices[carSize].first<<' '<< prices[carSize].second<< endl;
            }
        }
    }
}

void AssignSpot(vector<string> inputLine ,carsMap &cars ,spotsMap &parkingSpots ,pricesMap &prices){

    if(parkingSpots[stoi(inputLine[1])].availabilty == 0){
        parkingSpots[stoi(inputLine[1])].availabilty =1;
        cout << "Spot " << inputLine[1] << " is occupied now." << endl ;
    }
}

void Checkout(vector<string> inputLine ,carsMap &cars ,spotsMap &parkingSpots ,pricesMap &prices){
    int totalPrice = 0;
    if(parkingSpots[stoi(inputLine[1])].availabilty == 1){
        parkingSpots[stoi(inputLine[1])].availabilty =0;
        cout << "Spot " << inputLine[1] << " is free now." << endl ;
    }

    if(parkingSpots[stoi(inputLine[1])].spotType == "covered"){
        totalPrice =(prices[parkingSpots[stoi(inputLine[1])].spotSize].first +50) + (parkingSpots[stoi(inputLine[1])].numDay * (prices[parkingSpots[stoi(inputLine[1])].spotSize].second + 30));
        cout << "Total cost: "<< totalPrice <<endl ;
        parkingSpots[stoi(inputLine[1])].numDay=0;
    }
    else if(parkingSpots[stoi(inputLine[1])].spotType == "CCTV"){
        totalPrice = (prices[parkingSpots[stoi(inputLine[1])].spotSize].first + 80) + (parkingSpots[stoi(inputLine[1])].numDay * (prices[parkingSpots[stoi(inputLine[1])].spotSize].second + 60));
        cout << "Total cost: "<< totalPrice <<endl ;
        parkingSpots[stoi(inputLine[1])].numDay=0;
    }
    else{
        totalPrice = prices[parkingSpots[stoi(inputLine[1])].spotSize].first + (parkingSpots[stoi(inputLine[1])].numDay * prices[parkingSpots[stoi(inputLine[1])].spotSize].second);
        cout << "Total cost: "<< totalPrice <<endl ;
        parkingSpots[stoi(inputLine[1])].numDay=0;
    }
}

void PassTime(vector<string> inputLine  ,carsMap &cars ,spotsMap &parkingSpots ,pricesMap &prices){

    for(auto it = parkingSpots.begin() ; it!=parkingSpots.end() ; it++){
        if(it->second.availabilty==1){
            it->second.numDay += stoi(inputLine[1]);
        }
    }
}

void HandleInput(string &input ,carsMap &cars ,spotsMap &parkingSpots ,pricesMap &prices){
    
    stringstream ss(input);
    string token;
    vector<string> inputLine;
    
    while(ss >> token){
        inputLine.push_back(token);
    }

    if(inputLine[0]== REQUSET_COMMAND){

        FindSpot(inputLine , cars ,parkingSpots ,prices);
 
    }
    else if(inputLine[0]== ASSIGN_COMMAND){

        AssignSpot(inputLine, cars ,parkingSpots ,prices);
        
    }
    else if(inputLine[0]== CHECKOUT_COMMAND){
        Checkout(inputLine , cars ,parkingSpots ,prices);
    }
    else if(inputLine[0] == PASSTIME_COMMAND){
        PassTime(inputLine , cars ,parkingSpots ,prices);
    }


}

vector<string> StringToWords(string temp){

    vector<string> result;
    stringstream s(temp);
    string word;
    while(getline(s , word ,',')){
        result.push_back(word);
    }
    return result;

}

void ReadFiles(char* carFileLoc , char* parkingSpotsFileLoc ,char* pricesFileLoc ,carsMap &cars ,spotsMap &parkingSpots ,pricesMap &prices ){

    ifstream carFile(carFileLoc) , parkingSpotsFile(parkingSpotsFileLoc) , pricesFile(pricesFileLoc) ;
    string fileData;
    
    getline( carFile , fileData );
    while (getline( carFile , fileData )){
        
        vector<string> Data = StringToWords(fileData);
        //add csv file's data to a map for cars
        cars[Data[0]] = stoi(Data[1]);
        
    }
    
    getline(parkingSpotsFile,fileData);
    while(getline(parkingSpotsFile,fileData)){
         
        vector<string> Data = StringToWords(fileData);
        //add csv file's data to a map for parkingspots
        parkingSpots[stoi(Data[0])].spotSize = stoi(Data[1]); 
        parkingSpots[stoi(Data[0])].spotType = (Data[2]);

    }

    getline(pricesFile,fileData);

    while(getline(pricesFile,fileData)){

        vector<string> Data = StringToWords(fileData);
        //add csv file's data to a map for prices
        prices[stoi(Data[0])].first = stoi(Data[1]);
        prices[stoi(Data[0])].second = stoi(Data[2]);
    }
    carFile.close();
    parkingSpotsFile.close();
    pricesFile.close();
}

int main(int argc , char *argv[]){

    carsMap cars; 
    spotsMap parkingSpots; 
    pricesMap prices;

    string input;
    ReadFiles(argv[1],argv[2],argv[3] , cars ,parkingSpots ,prices);


    while(getline(cin, input)){
        HandleInput(input , cars , parkingSpots , prices);
    }
}