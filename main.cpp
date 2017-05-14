#include "geocoder.hpp"
#include <regex>
#include <stdexcept>

int main(int argc, char*argv[]){
	try {
		if(argc != 2) {
			std::cout << "Usage: ./geocoder filepath" << std::endl;
			return 0;
		}
		std::string filepath = argv[1];
		Geocoder geocoder;
		geocoder.loadGeodata(filepath);
		std::vector<Address> geodata = geocoder.getGeodata();
		//пока читаем адреса аптек из csv; потом надо заменить на чтение из БД
		CSVparser csv;
		CSVparser::CSV data = csv.readAndGet("./drugstores.csv", false, ';');
		std::vector<std::string> drugstore_address_str;
		std::vector<Address> drugstore_address;
		
		for(int i = 0; i < data.size(); i++) {
			drugstore_address_str.push_back(data[i][1]);
			
		}
		for(int i = 0; i < drugstore_address_str.size(); ++i) {
			drugstore_address.push_back(geocoder.getCoordinates(drugstore_address_str[i]));
			std::cout << i << ") " << drugstore_address[i].street << ", " << drugstore_address[i].house << ", " << drugstore_address[i].longitude << ", " << drugstore_address[i].latitude << std::endl;
		}
	}
	catch(std::string& s) {
		std::cerr << s;
	}
	catch(std::exception& e) {
		std::cerr << e.what();
	}
	catch(...) {
		std::cerr << "unexpected error...\n";
	}
	return 0;
}
