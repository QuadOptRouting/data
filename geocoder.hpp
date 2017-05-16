#pragma once
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>

class CSVparser {
public:
	typedef boost::tokenizer<boost::escaped_list_separator<char> > Tokenizer;
	typedef std::vector<std::vector<std::string> > CSV;
	
	virtual ~CSVparser() {}
	void readCSV(const std::string& filepath, bool is_header = false, char delimiter = ',', char escape = '\\', char quotes = '"');
	CSV getData() const;
	CSV readAndGet(const std::string& filepath, bool is_header = false, char delimiter = ',', char escape = '\\', char quotes = '"');
	std::string getHeader() const;
private:
	CSV data;
	std::string header;
};

struct Address {
	Address() : id(0), street(""), house(""), house_alter(""), building(0), corp(0), latitude(0.0), longitude(0.0) {}
	long id;
	std::string street;				//название улицы
	std::string house;				//номер дома
	std::string house_alter;		//альтернативный номер дома, если есть(пока тоже самое, что house)
	int building;					//строение
	int corp;						//корпус
	double latitude;
	double longitude;
};

class Geocoder: private CSVparser {
public:
	void loadGeodata(const std::string& filepath, bool is_header = true, char delimiter = ';', char escape = '\\', char quotes = '"');
	std::vector<Address> getGeodata() const;
	Address getCoordinates(const std::string& address) const;
private:
	Address parseStringAddress(const std::string& address_str) const;
	Address parseCSVAddress(const std::vector<std::string>& row);
	std::vector<Address> geodata;
};
