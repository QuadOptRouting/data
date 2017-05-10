#include <iostream>
#include <fstream>
#include <regex>
#include <locale>
#include <sys/types.h>

#include "geocoder.hpp"

void CSVparser::readCSV(const std::string& filepath, bool is_header, char delimiter, char escape, char quotes) {
	std::ifstream in(filepath.c_str());
    if(!in.is_open()) {
		 throw("error: File was not open\n");
	}
    if(!data.empty()) {
		data.clear();
	}
    std::vector<std::string> row;
    std::string line;
    if(is_header) {
		std::getline(in, header);
	}
	while(std::getline(in, line)) {
		Tokenizer tok(line, boost::escaped_list_separator<char>(escape, delimiter, quotes));
		row.assign(tok.begin(), tok.end());
		data.push_back(row);
	}
	in.close();
}

CSVparser::CSV CSVparser::getData() const {
	if(!data.empty()) {
		return data;
	}
	else {
		throw("error: No data\n");
	}
}

CSVparser::CSV CSVparser::readAndGet(const std::string& filepath, bool is_header, char delimiter, char escape, char quotes) {
	readCSV(filepath, is_header, delimiter, escape, quotes);
	return getData();
}

Address Geocoder::parseCSVAddress(const std::vector<std::string>& row) {
	const int rowlenght = 5;
	if(row.size() != rowlenght) {
		throw("error: Bad row\n");
	}
	Address address;
	address.id = std::stol(row[0]);
	address.latitude = std::stod(row[3]);
	address.longitude = std::stod(row[4]);
	setlocale(LC_ALL, "");
	std::string rus("(?:а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я)");
	std::smatch matching;
	std::regex housenumb("\\d+(?:/\\d+)?"+rus+"?");
	std::regex building("с\\d+");
	std::regex corp("к\\d+");
	std::regex street("(?:улица (?:"+rus+"| )+)|(?:(?:"+rus+"| )+улица)");
	std::regex street1("улица | улица|проезд | проезд|бульвар | бульвар|переулок | переулок|площадь | площадь|шоссе | шоссе|проспект | проспект|квартал | квартал|набережная | набережная|аллея | аллея");
	if(std::regex_search (row[2], matching, housenumb)) {
		if(matching.size() == 1) {
			address.house = matching[0];
			address.house_alter = matching[0];
		}
		else {
			throw("error: Bad address\n");
		}
	}
	if(std::regex_search (row[2], matching, building)) {
		if(matching.size() == 1) {
			address.building = std::stoi(&(std::string(matching[0]))[2]);
		}
		else {
			throw("error: Bad address\n");
		}
	}
	if(std::regex_search (row[2], matching, corp)) {
		if(matching.size() == 1) {
			address.corp = std::stoi(&std::string(matching[0])[2]);
		}
		else {
			throw("error: Bad address\n");
		}
	}
	if(std::regex_search (row[1], matching, street1)) {
		if(matching.size() == 1) {
			address.street = matching.suffix().str() + matching.prefix().str();
		}
		else {
			throw("error: Bad address\n");
		}
	}
	
	
	return address;
}

void Geocoder::loadGeodata(const std::string& filepath, bool is_header, char delimiter, char escape, char quotes) {
	CSV raw_data = readAndGet(filepath, is_header, delimiter, escape, quotes);
	geodata.clear();
	for(auto it = raw_data.begin(); it < raw_data.end(); ++it) {
		geodata.push_back(parseCSVAddress(*it));
	}
}

std::vector<Address> Geocoder::getGeodata() {
	if(!geodata.empty()) {
		return geodata;
	}
	else {
		throw("error: No data\n");
	}
}

Address Geocoder::getCoordinates(const std::string& address) {
	
	//parseAddressFromString()
	bool isfound = false;
	Address drugstore_address;
	
	for(int i = 0; i < geodata.size(); ++i) {
		if(geodata[i].street == drugstore_address.street && (geodata[i].house == drugstore_address.house || geodata[i].house_alter == drugstore_address.house_alter)
		&& geodata[i].corp == drugstore_address.corp && geodata[i].building == drugstore_address.building) {
			drugstore_address.latitude = geodata[i].latitude;
			drugstore_address.longitude = geodata[i].longitude;
			isfound = true;
		}
	}
	if(!isfound) {
		throw("error: Address not found\n");
	}
	
	return drugstore_address;
}














