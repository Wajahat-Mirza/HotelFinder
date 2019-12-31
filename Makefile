output: hotelFinder.o hotel_functions.o
	g++ hotel_functions.o hotelFinder.o -o hotelFinder.out
	$(info =====================================================================================================)
	$(info .WELCOME TO HOTEL FINDER APP!)
	$(info .NOTE! Call program using format: ./hotelFinder.out -f <inputfile>)
	$(info .INSTRUCTIONS: There are five main commands (without angular brackets))
	$(info .1: find info on hotel by giving "find <hotel_name, city_name>")
	$(info .2: add info of a hotel by giving "add <hotel_name, city_name, stars, price, country, address>")
	$(info .3: delete info of hotel by giving "delete <hotel_name, city_name>")
	$(info .4: All hotels of the city by giving "allinCity <city_name>")
	$(info .5: Move hotel info to a file by giving "dump <output_file_name>")
	$(info .6: Exit the program by giving "quit" or "exit")
	$(info =====================================================================================================)

	
hotelFinder.o: hotelFinder.cpp
	g++ -c hotelFinder.cpp
hotel_functions.o: head_functions.h hotel_functions.cpp
	g++ -c hotel_functions.cpp
clean:
	rm *.o
	rm *.out