#include <list> 
#include<map> 
#include<cstdlib>
#include<list>
#include<iostream>
#include<fstream>
#include<iterator>
#include<vector>

#include "head_functions.h"


using namespace std;
int validity()
{
	return EXIT_SUCCESS;
}

Hotel:: Hotel(string Hname, string city, string stars, string price, string country_name, string address)
{
    this->Hname = Hname;
    this->city = city;
    this->stars = stars;
    this-> price = price;
    this->country_name =country_name;
    this->address = address;
}
void Hotel::display()
{

    cout.width(60); cout << left << this->Hname;
    cout.width(20); cout << left << this->city;
    cout.width(10); cout << left << this->stars;
    cout.width(20); cout << left << this->price;
    cout.width(20); cout << left << this->country_name;
    cout.width(10); cout << left << this->address;
    cout<<endl;

}

//=========================================================

void Node::addHotel(string hotel, string city, string stars, string price, string country_name, string address)
{
    this->hotels.push_back(Hotel(hotel,city, stars, price, country_name, address));
}
void Node::displayHotels()
{

    cout <<"========================================================================================================================================================================"<<endl;    
    cout.width(60); cout << left << "Hotel Name";
    cout.width(20); cout << left << "City";
    cout.width(12); cout << left << "Stars";
    cout.width(20); cout << left << "Price";
    cout.width(20); cout << left << "Country";
    cout.width(10); cout << left << "Address";
    cout<<endl;
    cout <<"========================================================================================================================================================================"<<endl;
    for(auto it:hotels)
    {
        it.display();
    }
}

//==================================================

Trie::Trie()
{
    root = new Node();
}
void Trie::insert(string hotel, string city, string stars, string price, string country_name, string address) // you add the city and then the corresponding hotels
{
    Node* ptr = root;
    for(int i=0; i<city.length(); i++)
    {
        if(ptr->edges.find(city[i])==ptr->edges.end())
            ptr->edges.insert(pair<char, Node*>(city[i],new Node));
        
        ptr = ptr->edges.at(city[i]);
    }
    
    ptr->addHotel(hotel,city, stars, price, country_name, address);
    
}

void Trie::find(string city)
{
    Node* ptr = root;
    for(int i=0; i<city.length(); i++) 
    {
        if(ptr->edges.find(city[i])==ptr->edges.end())
            return;
        
        ptr = ptr->edges.at(city[i]);
    }
   // cout <<"HOLA AMIGA" << endl;
    ptr->displayHotels();
}

void Trie::remove(string hotel, string city)
{
    Node* ptr = root;
    //vector<Node*> ptrs;
    for(int i=0; i<city.length(); i++) 
    {
        if(ptr->edges.find(city[i])==ptr->edges.end()) {
            cout << "Hotel Not found in the database." << endl;
            return;
        }
      //  ptr.push_back(ptr);
        ptr = ptr->edges.at(city[i]);
    }
    for (list <Hotel> :: iterator it = ptr->hotels.begin(); it != ptr->hotels.end(); it++) {
        if (it->Hname == hotel) {
            ptr->hotels.erase(it);
            return;
        }
    }
}


void allinCity(string city, Trie myTrie)
{
    myTrie.find(city);
}
