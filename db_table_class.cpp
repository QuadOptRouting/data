#include "db_table_class.h"


////       Distance functions and methods




void distance::set_drugstore_a_id(char* db_drugstore_a_id)
{
    std::string buf = db_drugstore_a_id;
    
    drugstore_a_id = std::stoi(buf);
}


void distance::set_drugstore_b_id(char* db_drugstore_b_id)
{
    std::string buf = db_drugstore_b_id;
    
    drugstore_b_id = std::stoi(buf);
}


void distance::set_distance(char* db_distance)
{
    std::string buf = db_distance;
    
    dist = std::stoi(buf);        
}




////                Relation methods and functions


void relation::set_drugstore_id(char* db_drugstore_id)
{
    std::string buf = db_drugstore_id;
        
    drugstore_id = std::stoi(buf);

}

void relation::set_drug_id(char*  db_drug_id)
{
    std::string buf = db_drug_id;
    
    drug_id = std::stoi(buf);
}

void relation::set_price(char* db_price)
{    
    std::string buf = db_price;

    price = std::stoi(buf);
}

void relation::set_count(char* db_count)
{
    
    std::string buf = db_count;
    
    count = std::stoi(buf);
}




////                Drug methods and functions



int drug::get_id()
{
    return id;
}

void drug::set_id(char* db_drug_id)
{
    std::string buf = db_drug_id;

    id = std::stoi(buf);
}

void drug::set_name(char* db_drug_name)
{
    std::string buf = db_drug_name;

    name = buf;
}

/*void drug::set_international_name(char* db_international_name)
{
    std::string buf = db_international_name;

    international_name = buf;
}*/
    
    
    
    
////                Drugstore methods and functions



int drugstore::get_id()
{
    return id;
}

std::string drugstore::to_string()
{
    std::string row;

    row = std::to_string( id ) + " " + address + " " + std::to_string( longitude ) + " " + std::to_string( latitude ) + " " + std::to_string( square_id ) + " " + name;
    
    return row;
}

void drugstore::set_id(char* db_drugstore_id)
{
    std::string buf = db_drugstore_id;

    id = std::stoi(buf);
}

void drugstore::set_longitude(char* db_longitude)
{
    std::string buf = db_longitude;

    id = std::stod(buf);
}

void drugstore::set_latitude(char* db_latitude)
{
    std::string buf = db_latitude;

    id = std::stod(buf);
}

void drugstore::set_square_id(char* db_square_id)
{
    std::string buf = db_square_id;

    id = std::stoi(buf);
}

void drugstore::set_address(char* db_drugstore_address)
{
    std::string buf = db_drugstore_address;

    address = buf; 
}

void drugstore::set_name(char* db_international_name)
{
    std::string buf = db_international_name;

    name = buf;  
}


// drugstore without long and lat methods

int drugstore_no_coordinates::get_id()
{
    return id;
}

std::string drugstore_no_coordinates::get_address()
{
    return address;
}

std::string drugstore_no_coordinates::get_name()
{
    return name;
}

void drugstore_no_coordinates::set_id(char* db_drugstore_id)
{
    std::string buf = db_drugstore_id;

    id = std::stoi(buf);
}

void drugstore_no_coordinates::set_address(char* db_drugstore_address)
{
    std::string buf = db_drugstore_address;

    address = buf; 
}

void drugstore_no_coordinates::set_name(char* db_international_name)
{
    std::string buf = db_international_name;

    name = buf;  
}