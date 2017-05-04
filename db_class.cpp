#include "db_class.h"
#include <fstream>


//                  Function for select method.


size_t db::get_tuples_count()
{
    return PQntuples( select_from_drugstore.get() );
}


std::string db::transform_ids_to_string( std::vector<int> id )
{
    std::string request = std::to_string(id[0]);
    
    size_t length = id.size();
    
    for (size_t i=1 ; i < length; i++)
        request += " OR "+std::to_string(id[i]);
    
    return request;
    
}


std::vector<drugstore> db::request_drugstores( std::vector<int> drugstore_ids, std::string select_type )
{
    
    std::ifstream request_file;
    
    size_t n_rows;
	const size_t n = 256;
    
	char *buf =  new char[n];
    std::string request;
    std::string file_name;
    
    std::vector<drugstore> drugstores;
    
    file_name = "request_drugstores_";
    
    if ( select_type != "all" || select_type != "square" || select_type != "no_coordinates")
        throw std::runtime_error("Bad request type");
        
    request_file.open( file_name + select_type + ".txt");        //Getting request from file
    
    if ( properties_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    properties_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drugstore_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && n_rows ) )
        throw std::runtime_error("Exception with request");             //Checking for bad tuples

    drugstores.resize(n_rows);
    drugstores = get_drugstores( select_res );
    
    select_res.reset();
    
    return drugstores;
    
}



std::vector<drugstore> db::request_drugs( std::vector<int> drug_ids )
{
    
    std::ifstream request_file;
    
    size_t n_rows;
	const size_t n = 256;
    
	char *buf =  new char[n];
    std::string request;
    std::string file_name;
    
    std::vector<drugstore> drugs;
    
    file_name = "request_drugs.txt";
        
    request_file.open( file_name );        //Getting request from file
    
    if ( properties_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    properties_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drug_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && n_rows ) )
        throw std::runtime_error("Exception with request");             //Checking for bad tuples

    drugs.resize(n_rows);
    drugs = get_drugstores( select_res );
    
    select_res.reset();
    
    return drugs;
    
}



std::vector<drugstore> db::request_distances( std::vector<drugstore> drugstores )
{
    
    std::ifstream request_file;
    
    size_t n_rows;
    size_t length;
	const size_t n = 256;
    
	char *buf =  new char[n];
    std::string request;
    std::string file_name;
    
    std::vector<distance> distances;
    
    length = drugstores.size();
    
    std::vector<int> drugstore_ids (length);
    
    for (size_t i = 0; i < length; i++)
        drugstore_ids[i] = drugstores[i].get_id();
    
    file_name = "request_drugs.txt";
        
    request_file.open( file_name );        //Getting request from file
    
    if ( properties_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    properties_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drugstore_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && n_rows ) )
        throw std::runtime_error("Exception with request");             //Checking for bad tuples

    distances.resize(n_rows);
    distances = get_drugstores( select_res );
    
    select_res.reset();
    
    return distances;
    
}


std::vector<drugstore> db::request_relations_with_pills( std::vector<drug> drugs )
{
    
    std::ifstream request_file;
    
    size_t n_rows;
    size_t length;
	const size_t n = 256;
    
	char *buf =  new char[n];
    std::string request;
    std::string file_name;
    
    std::vector<distance> distances;
    
    length = drugstores.size();
    
    std::vector<int> drug_ids (length);
    
    for (size_t i = 0; i < length; i++)
        drugstore_ids[i] = drugstores[i].get_id();
    
    file_name = "request_drugs.txt";
        
    request_file.open( file_name );        //Getting request from file
    
    if ( properties_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    properties_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drugstore_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && n_rows ) )
        throw std::runtime_error("Exception with request");             //Checking for bad tuples

    distances.resize(n_rows);
    distances = get_drugstores( select_res );
    
    select_res.reset();
    
    return distances;
    
}




