#include <iostream>
#include <fstream>
#include <regex>
#include <locale>
#include <sstream>

#include "geocoder.hpp"

template<typename T>
T StringToNumber(const std::string& numberAsString) {
	T value;
	std::stringstream stream(numberAsString);
	stream >> value;
	if (stream.fail()) {
		std::runtime_error e(numberAsString);
		throw e;
	}
	return value;
}

void CSVparser::readCSV(const std::string& filepath, bool is_header, char delimiter, char escape, char quotes) {
	std::ifstream in(filepath);
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
	setlocale(LC_ALL, "");
	Address address;
	address.id = std::stol(row[0]);
	address.latitude = StringToNumber<double>(row[3]);
	address.longitude = StringToNumber<double>(row[4]);
	std::string rus("(?:а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я)");
	std::smatch matching;
	std::regex housenumb("\\d+(?:/\\d+)?"+rus+"?");
	std::regex building("с\\d+");
	std::regex corp("к\\d+");
	std::regex street("улица | улица|проезд | проезд|бульвар | бульвар|переулок | переулок|площадь | площадь|шоссе | шоссе|проспект | проспект|квартал | квартал|набережная | набережная|аллея | аллея");
	
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
	if(std::regex_search (row[1], matching, street)) {
		if(matching.size() == 1) {
			address.street = matching.prefix().str() + matching.suffix().str();
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
	for(auto i = raw_data.begin(); i < raw_data.end(); ++i) {
		geodata.push_back(parseCSVAddress(*i));
	}
}

std::vector<Address> Geocoder::getGeodata() const {
	if(!geodata.empty()) {
		return geodata;
	}
	else {
		throw("error: No data\n");
	}
}

Address Geocoder::parseStringAddress(const std::string& address_str) const{
	Address address;
	setlocale(LC_ALL, "");
	std::string rus("(?:а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я)");
	std::string rus_alphanum("(?:а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я|\\d|-)+");
	std::string rus_alphanum_space("(?:а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я|\\d|-| )+");
	std::regex street("Проезд | Проезд|проезд | проезд|бульвар | бульвар|Бульвар | Бульвар|Переулок | Переулок|переулок | переулок|Площадь | Площадь|площадь | площадь|Шоссе | Шоссе|шоссе | шоссе|Проспект | Проспект|проспект | проспект|квартал | квартал|Набережная | Набережная|набережная | набережная|Аллея | Аллея|аллея | аллея| ул.|ул. |пр. | пр.|пер. | пер.|пл. | пл.|просп. | просп.|пр-т.? | пр-т.?|наб. | наб.|ш. | ш.|б-р.? | б-р.?");
	std::regex housenumb("\\d+(?:/\\d+)?"+rus+"?");
	std::regex building("с\\d+");
	std::regex corp("к\\d+");
	std::regex rus_name(rus_alphanum+"(?:"+rus_alphanum_space+")?");
	std::vector<std::string> row;
	std::smatch matching;
	std::string address_str_cut;
	std::string street_str;
	std::string house_str;
	
	//делаем ставку на вид документа; надеемся, что все части адреса разделены запятыми, и две последние части - название улицы и номер дома соответственно
	CSVparser::Tokenizer tok(address_str, boost::escaped_list_separator<char>('\\', ',', '"'));
	row.assign(tok.begin(), tok.end());
	row.erase(row.begin(), row.end() - 2);
	house_str = row[1];
	street_str = row[0];
	if(std::regex_search(house_str, matching, building)) {
		if(matching.size() == 1) {
			address.building = std::stoi(&(std::string(matching[0]))[2]);
			house_str = matching.prefix().str() + matching.suffix().str();
		}
		else {
			throw("error: Bad address\n");
		}
	}
	if(std::regex_search(house_str, matching, corp)) {
		if(matching.size() == 1) {
			address.corp = std::stoi(&std::string(matching[0])[2]);
			house_str = matching.prefix().str() + matching.suffix().str();
		}
		else {
			throw("error: Bad address\n");
		}
	}
	if(std::regex_search(house_str, matching, housenumb)) {
		if(matching.size() == 1) {
			address.house = matching[0];
			address.house_alter = matching[0];
		}
		else {
			throw("error: Bad address\n");
		}
	}
	if(std::regex_search(street_str, matching, street)) {
		if(matching.size() == 1) {
			street_str.clear();
			street_str = matching.prefix().str() + matching.suffix().str();
		}
		else {
			throw("error: Bad address\n");
		}
	}
	
	if(std::regex_search(street_str, matching, rus_name)) {
		if(matching.size() == 1) {
			address.street = matching[0];
		}
		else {
			throw("error: Bad address\n");
		}
	}
	return address;
}

Address Geocoder::getCoordinates(const std::string& address) const {
	bool isfound = false;
	Address drugstore_address = parseStringAddress(address);
	unsigned int i = 0;
	while(i < geodata.size() && !isfound) {
		if(geodata[i].street == drugstore_address.street && (geodata[i].house == drugstore_address.house || geodata[i].house_alter == drugstore_address.house_alter)
		&& geodata[i].corp == drugstore_address.corp && geodata[i].building == drugstore_address.building) {
			drugstore_address.latitude = geodata[i].latitude;
			drugstore_address.longitude = geodata[i].longitude;
			isfound = true;
		}
		i++;
	}
	if(!isfound) {
		std::cerr << "Warning: Address not found(" << drugstore_address.street << ", " << drugstore_address.house << ", к" << drugstore_address.corp << " ,с" << drugstore_address.building << ")\n";
	}
	return drugstore_address;
}
