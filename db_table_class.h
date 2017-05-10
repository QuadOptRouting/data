#ifndef DB_TABLE_CLASS_H
#define DB_TABLE_CLASS_H
#include <iostream>
#include <memory>

class drugstore
{
private:

    int id;
    
    double longitude;
    double latitude;
    
    int square_id;
    
    std::string address;
    std::string name;

public:

    int get_id();
    
    std::string to_string();
    
    void set_id(char* db_drugstore_id);
	void set_longitude(char* db_longitude);
	void set_latitude(char* db_latitude);
    void set_square_id(char* db_square_id);
	void set_address(char* db_drugstore_address);
	void set_name(char* db_drugstore_name);

};


class drugstore_no_coordinates
{
private:

    int id;
    std::string address;
    std::string name;

public:

    int get_id();
    std::string get_address();
    std::string get_name();
    
    void set_id(char* db_drugstore_id);
	void set_address(char* db_drugstore_address);
	void set_name(char* db_drugstore_name);

};



class drug
{
private:

    int id;
    std::string name;
//    std::string international_name;

public:

    int get_id();
    
	void set_id(char* db_drug_id);
	void set_name(char* db_drug_name);
//	void set_international_name(char* db_international_name);

};



class relation
{
private:

    int drugstore_id;
    int drug_id;
    int price;
    int count;

public:

    void set_drugstore_id(char* db_id_drugstore);
    void set_drug_id(char* db_id_drug);
	void set_price(char* db_price);
    void set_count(char* db_count);

};



class distance
{
private:

    int drugstore_a_id;
    int drugstore_b_id;
    int dist;

public:

	void set_drugstore_a_id(char* drugstore_a_id);
	void set_drugstore_b_id(char* drugstore_b_id);
	void set_distance(char* db_distance);

};

//

#endif //DB_TABLE_CLASS_H*/



