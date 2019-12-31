//Header File

#ifndef HOTEL_FUNCTIONS
#define HOTEL_FUNCTIONS
#include <map>

using namespace std;

//int findPrime(int parameter);
bool Validity(string ch);

class Hotel // class that has the hotel name and displays the name based on the city 
{
	private:
		//string Hname;
		string city;
		string stars;
		string price;
		string country_name;
		string address;
	public:
		Hotel(string Hname, string city, string stars, string price, string country_name, string address);
		void display();
		string Hname;

		
};
//=========================================================
class Node //has a list of hotels that you can add to the list and display all the hotels in that list 
{
	private: 
		list<Hotel> hotels; 
		map <char, Node*> edges;
	public:
		Node()
		{}
		void addHotel(string hotel, string city, string stars, string price, string country_name, string address);
		

		void displayHotels();
		
		friend class Trie;
};
class Trie{
	private:
		Node* root;
	public:
		Trie();
		void insert(string hotel, string city, string stars, string price, string country_name, string address);
		void find(string city);
		void remove(string hotel, string city);
}; 
//==================================================

	

//in main
void allinCity(string city, Trie myTrie);

#endif

