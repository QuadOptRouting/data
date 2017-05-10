#include "geocoder.hpp"



//#incldue "db_request.h"

int main(){
	try {
		
		
		
		
		
		
		
		Geocoder geocoder;
		geocoder.loadGeodata("./3.addr.csv");
		
		std::vector<drugstore_no_coordinates> drugstores_no_coord;
		std::vector<drugstore> drugstores;
		
		for(auto it = drugstores_no_coord.begin(); it != drugstores_no_coord.end(); ++it) {
			Address drugstore_address = geocoder.getCoordinates(*it.get_address());
			drugstore store;
			store.set_id(*it.get_id());
			store.set_longitude(drugstore_address.longitude);
			store.set_latitude(drugstore_address.latitude);
			store.set_address(*it.get_address());
			store.set_name(*it.get_name());
			//store.set_square_id();
			
			
			drugstores.push_back(store);
			
			
			
		}
		
		
		
		
	}
	catch(std::string s) {
		std::cout << s;
	}
	catch(...) {
		std::cout << "error...\n";
	}
	return 0;
}
