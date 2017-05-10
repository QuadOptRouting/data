#pragma once
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>

class CSVparser {
public:
	typedef boost::tokenizer<boost::escaped_list_separator<char> > Tokenizer;
	typedef std::vector<std::vector<std::string> > CSV;
	
	CSVparser() {}
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
	//typedef enum{улица, проспект, шоссе, площадь, бульвар, проезд, переулок} StreetType;
	long id;
	std::string street;				//название улицы
	
	std::string house;				//номер дома
	std::string house_alter;		//альтернативный номер дома, если есть
	int building;					//строение
	int corp;						//корпус
	double latitude;
	double longitude;
};

class Geocoder: private CSVparser {
public:
	Geocoder() {}
	~Geocoder() {}
	void loadGeodata(const std::string& filepath, bool is_header = true, char delimiter = ';', char escape = '\\', char quotes = '"');
	std::vector<Address> getGeodata();
	Address getCoordinates(const std::string& address);

private:
	Address parseCSVAddress(const std::vector<std::string>& row);
	Address parseStringAddress();
	std::vector<Address> geodata;
	
};
