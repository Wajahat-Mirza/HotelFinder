#include<iostream>
#include<fstream>
#include<cmath>
#include<list>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

#include "head_functions.h"

using namespace std;

int findPrime(int parameter);

vector<string> separateStrings(string str,char comma)
{
	string input="";
	int cnt=0;
	str=str+comma; // to seperate the last word
	int l=str.size();// counter 2
		//iterate through the string
	vector <string> slist;
	for (int i=0; i<l;i++)
	{
		if (str[i]!=comma) // if not a comma we add it to the user input word
			input=input+str[i];
		else
		{
	//not an empty string
			if((int)input.size()!=0)
				slist.push_back(input);
			input ="";
		}
	}
	return slist;
}

class Hotel_Node
{
	public:
		string hotel_name;
		string city_name;
		string stars;
		string price;
		string country_name;
		string address;
		friend class Hotel_HashMap;

	public:
		Hotel_Node(string hotel_name, string city_name,string stars, string price, string country_name, string address)
		{
			this->hotel_name = hotel_name;
			this->city_name = city_name;
			this->stars = stars;
			this->price = price;
			this->country_name = country_name;
			this->address = address;
		}
		string get_hotel_name()
		{
			return this->hotel_name;
		}
		string get_city_name()
		{
			return this->city_name;
		}
		string get_stars()
		{
			return this->stars;
		}
		string get_price()
		{
			return this->price;
		}
		string get_country_name()
		{
			return this->country_name;
		}
		string get_address()
		{
			return this->address;
		}

		void hotel_info()
		{		

			cout <<"========================================================================================================================================================================"<<endl;
		    cout.width(60); cout << left << "Hotel Name";
		    cout.width(20); cout << left << "City";
		    cout.width(10); cout << left << "Stars";
		    cout.width(20); cout << left << "Price";
		    cout.width(20); cout << left << "Country";
		    cout.width(10); cout << left << "Address";
		    cout<<endl;
		    cout <<"========================================================================================================================================================================"<<endl;


		    cout.width(60); cout << left << this->hotel_name;
		    cout.width(20); cout << left << this->city_name;
		    cout.width(10); cout << left << this->stars;
		    cout.width(20); cout << left << this->price;
		    cout.width(20); cout << left << this->country_name;
		    cout.width(10); cout << left << this->address;
		    cout<<endl;

		}
		
};

class Hotel_HashMap
{
	private:
		list <Hotel_Node> *buckets;		// Array of Pointers to Hash Nodes
		int size;					    //Current Size of Hotel_HashMap
		int capacity;			    // Total Capacity of Hotel_HashMap
	public:
		Hotel_HashMap(int capacity);//, string OGkey, string hotel_name, string city_name);
		unsigned long hashCode(string key);
		void insert(string hotel_name, string city_name,string stars, string price, string country_name, string address);
		void search(string key);
		void remove(string key);
		void dump(string sorted_file);
		int get_size();
		int get_capacity();
		~Hotel_HashMap();
};

Hotel_HashMap::Hotel_HashMap(int capacity)//, string OGkey, string hotel_name, string city_name)
{
	buckets = new list<Hotel_Node>[capacity];
	this->capacity = capacity;
	this->size = 0;
	string OGkey= "";///hotel_name + "," + city_name;
}

unsigned long Hotel_HashMap::hashCode(string OGkey)
{
	unsigned long sum = 0;
	for(int i=0; i < OGkey.length(); i++)
		sum += OGkey[i] * pow(i,10); 		//Add ascci code of each letter times i power 10
	return sum;
}

void Hotel_HashMap::insert(string hotel_name, string city_name, string stars, string price, string country_name, string address)
{
	string OGkey = hotel_name + "," + city_name;
	int index = hashCode(OGkey)%this->capacity; //Find the bucket index where the new node will fall, make sure that the index is within the bounds of array
    	
	this->buckets[index].push_back(Hotel_Node(hotel_name,city_name,stars,price,country_name,address));
	this->size++;									//Increate number of elements in the array
}

void Hotel_HashMap::search(string OGkey)
{
	int counter = 0;
	bool hotel_found = false;

	int index = hashCode(OGkey)%this->capacity;

	//cout << "Index is: " << index << ", OGKey: |" << OGkey << "|" << endl;
	auto start_time = chrono::high_resolution_clock::now();
	for (list <Hotel_Node> :: iterator it = this -> buckets[index].begin(); it != this -> buckets[index].end(); it++)
	{
		if (OGkey == it -> get_hotel_name() + "," + it -> get_city_name())
		{
			it -> hotel_info();
			hotel_found = true;
		}
		counter++;
	}
	if (hotel_found == false)
	{
		cout << "============================================================"<< endl;
		cout << "Sorry, Hotel is not found. Try another or add it yourself!" << endl;
		cout << "============================================================"<< endl;
		return;
	}

	auto end_time = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
	cout << "----------------------------------------" << endl;
	cout << "Time taken to find: "<< (duration * pow(10,-6)) << " seconds"<<endl;
	cout << "----------------------------------------" << endl;
	cout << "Num of comparisons made: " << counter <<endl;
	cout << "----------------------------------------" << endl;
}


void Hotel_HashMap::remove(string OGkey)
{
	//int index = hashCode(key)%this->capacity;			//Get the index of the bucket
	int counter = 0;
	bool hotel_delete = false;
	int index = hashCode(OGkey)%this->capacity;

	for (list <Hotel_Node> :: iterator it = this -> buckets[index].begin(); it != this -> buckets[index].end(); it++)
	{
		//cout << it -> get_hotel_name() + ", " + it -> get_city_name() << endl;
		if (OGkey == it -> get_hotel_name() + ", " + it -> get_city_name())
		{
			this->buckets[index].erase(it);
			hotel_delete = true;
			cout << "-------------------------------------------------------------------"<< endl;
			cout<<"Hotel " << it -> get_hotel_name() << " has been deleted successfully." << endl;
			cout << "-------------------------------------------------------------------"<< endl;
		}
		counter++;
	}
	if (hotel_delete == false)
	{
		cout << "----------------------------------------------------------"<< endl;
		cout << "Your requested Hotel is not found, thus, cannot be deleted." << endl;
		cout << "----------------------------------------------------------"<< endl;
		return;
	}
}

int Hotel_HashMap::get_size()
{
	return this->size;
}

int Hotel_HashMap::get_capacity()
{
	return this->capacity;
}

void Hotel_HashMap::dump(string output_file)
{
	int index = 0;
	bool hotel_added = false;
	ofstream fout;
	fout.open(output_file);

	vector <string> dump;

	for (int i = 0; i < this->get_capacity(); ++i)
	{
		for (list <Hotel_Node> :: iterator it = this -> buckets[i].begin(); it != this -> buckets[i].end(); it++)
		{
		dump.push_back(it->get_hotel_name() + ", " + it->get_city_name() + ", " + it->get_stars() + ", " + it->get_price() + ", " + it->get_country_name() + ", " + it->get_address());
		}
	}

	sort(dump.begin(), dump.end());
	int size_of_dump;
	size_of_dump = dump.size();

	for (int i = 0; i < size_of_dump; ++i)
	{
		fout << dump[i] << endl;
	}

	fout.close();

	return;
}

Hotel_HashMap::~Hotel_HashMap()
{
	delete[] this->buckets;
}

int main(int argc, char *argv[])
{
	string hotel_name, city_name, stars, price, country_name, address;
	string file_name;
	Trie myTrie;
	
	for (int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-f") == 0)
		{
			file_name = argv[i + 1];
		}
	}

	ifstream fin;
	fin.open(file_name, ios::in);
	if(!fin)
	{
		cout << "-------------------------------------------------"<< endl;
		cout<<" Incorrect name of the file. Check the name again." << endl;
		cout << "-------------------------------------------------"<< endl;
		return EXIT_FAILURE;
	}
	cout << "-------------------------------------------------"<< endl;
	cout << "Loading Data. Be patient"<<endl;
	getline(fin, city_name);
	cout << "-------------------------------------------------"<< endl;
	cout<< "File name: "<< file_name<< endl;

	long numline=0;
	string count_line;
	while(getline(fin,count_line)){
		++numline;
	}
	cout << "-------------------------------------------------"<< endl;
	cout<<"Number of data entries in the file: "<< numline<<endl;
	cout << "-------------------------------------------------"<< endl;
	int max_size;

	max_size = findPrime(numline * 1.333); 
	
	fin.clear();                 // clear fail and eof bits
	fin.seekg(0, std::ios::beg); // back to the start!
	Hotel_HashMap myHotel_HashMap(max_size);// Prime number bigger than > cnt*1.333;

	getline(fin, city_name);

	while(!fin.eof())
	{
		getline(fin,hotel_name,',');
		getline(fin,city_name, ',');
		getline(fin,stars, ',');
		getline(fin,price, ',');
		getline(fin,country_name, ',');
		getline(fin,address);

		myHotel_HashMap.insert(hotel_name, city_name, stars, price, country_name, address);
		myTrie.insert(hotel_name, city_name, stars, price, country_name, address);
	}
	fin.close();

	string choice;
	string query_command;


	while(true)
	{
		cout << "------------------------------------------------------------------------"<< endl;		
		cout << "Enter your Query: ";
		getline(cin, query_command); 
		cout << "------------------------------------------------------------------------"<< endl;
		cout << "Your requested query is to " << query_command << endl;

		if(query_command == "exit" || query_command == "quit")
		{
			cout << "---------------------------------------"<< endl;
			cout << "You have terminated the program." << endl;
			cout << "---------------------------------------"<< endl;
			break;
		}

		else if (query_command.substr(0,4) == "find")
		{
			//cout << "Enter name of the Hotel and City with a comma in between and space after comma. E.g. 'Downtown Hotel, Islamabad' "<< endl;
			
			myHotel_HashMap.search(query_command.substr(5));
			continue;
		}	
		
		else if (query_command.substr(0,3) == "add")
		{
			string input = query_command.substr(4);

			char comma = ',';
			vector<string> temp = separateStrings(input, comma);
			if(temp.size() != 6)
			{
				cout<<"incorrect input"<<endl;
			}
			else
			{
				hotel_name = temp[0];
				city_name = temp[1];
				stars = temp[2];
				price = temp[3];
				country_name = temp[4];
				address = temp[5];
				myHotel_HashMap.insert(hotel_name, city_name, stars, price, country_name, address);
				cout<<"Your Hotel "<< hotel_name << " has been added."<< endl;
			}
		}

		else if(query_command.substr(0,6) == "delete") 
		{
			myHotel_HashMap.remove(query_command.substr(7));

			stringstream ss(query_command);

			string command;
			string hotel;
			string city;
			//int c = b.size()
			getline(ss, command,' ');
			getline(ss, hotel, ',');
			getline(ss, city);
			
			myTrie.remove(hotel, city);
			continue;
		}

		else if (query_command.substr(0,9) == "allinCity")
		{

			allinCity(query_command.substr(10), myTrie);			
			continue;
		}

		else if (query_command.substr(0,4) == "dump")
		{
			string output_file = query_command.substr(5);
			myHotel_HashMap.dump(output_file);
		}
	}
	return EXIT_SUCCESS;
}

int findPrime(int parameter)
{
	int myPrime = 0;

	bool isPrime = true;

	for (int i = 3; i <= parameter; ++i)
	{
		isPrime = true;
		for (int j = 2; j*j <= i; ++j)
		{
			if (i%j == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime == true)
		{
			myPrime = i;
		}
	}
	return myPrime;
}
