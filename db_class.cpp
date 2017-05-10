#include "db_class.h"


// initialising db_class

//                  Functions for select method.


std::string db::transform_ids_to_string( std::vector<int> id )
{
    
    size_t length = id.size();
    std::string request = " id = ";
    if ( length > 0)
        request += std::to_string(id[0]);
        
    for (size_t i=1 ; i < length; i++)
        request += " OR id = "+std::to_string(id[i]);
    
    return request;
    
}


std::vector<drugstore> db::request_drugstores( std::vector<int> drugstore_ids )
{
    
    std::ifstream request_file;
    
    size_t n_rows;
    size_t length;
    
	const size_t n = 256;
    
	char *buf =  new char[n];
    std::string request;
    std::string file_name;
    
    std::vector<drugstore> drugstores;
    
    length = drugstore_ids.size();
    file_name = "requests/request_drugstores.txt";
        
    request_file.open( file_name );        //Getting request from file
    
    if ( request_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    request_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drugstore_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
  //  std::cout<<request<<std::endl;
 //   std::cout<<n_rows<<std::endl;
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && ( n_rows == length) ) )
        throw std::runtime_error( PQresStatus( PQresultStatus ( select_res.get() )) );             //Checking for bad tuples

 //   std::cout<<n_rows<<std::endl;

    drugstores = get_drugstores( select_res );
    
    select_res.reset();
    
    return drugstores;
    
}


std::vector<drugstore_no_coordinates> db::request_drugstores_no_coordinates()
{
    
    std::ifstream request_file;
    
    size_t n_rows;
    
	const size_t n = 256;
    
	char *buf =  new char[n];
    
    std::string request;
    std::string file_name;
    
    std::vector<drugstore_no_coordinates> drugstores_no_coordinates;
    
    
    file_name = "requests/request_drugstores_no_coordinates.txt";
        
    request_file.open( file_name );        
    
    if ( request_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    request_file.getline( buf, 256 );
                        
    request = buf;
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
  //  std::cout<<request<<std::endl;
  //  std::cout<<n_rows<<std::endl;
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && n_rows ) )
        throw std::runtime_error( PQresStatus( PQresultStatus ( select_res.get() )) );      //Checking for bad tuples

    drugstores_no_coordinates.resize(n_rows);
    drugstores_no_coordinates = get_drugstores_no_coordinates( select_res );
    
    select_res.reset();
    
    return drugstores_no_coordinates;
    
}



std::vector<drug> db::request_drugs( std::vector<int> drug_ids )
{
    
    std::ifstream request_file;
    
    size_t n_rows;
    size_t length;
    
	const size_t n = 256;
    
	char *buf =  new char[n];
    std::string request;
    std::string file_name;
    
    std::vector<drug> drugs;
    
    length = drug_ids.size();

    file_name = "requests/request_drugs.txt";
        
    request_file.open( file_name );        //Getting request from file
    
    if ( request_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    request_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drug_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
//    std::cout<<request<<std::endl;
 //   std::cout<<n_rows<<std::endl;
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && ( n_rows == length) ) )
        throw std::runtime_error( PQresStatus( PQresultStatus ( select_res.get() )) );     //Checking for bad tuples

    drugs = get_drugs( select_res );
 //   std::cout<<"size: "<<drugs.size()<<std::endl;
    select_res.reset();
    
    return drugs;
    
}



std::vector<distance> db::request_distances( std::vector<drugstore> drugstores )
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
    
    file_name = "requests/request_distances.txt";
        
    request_file.open( file_name );        //Getting request from file
    
    if ( request_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    request_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drugstore_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && ( n_rows == length) ) )
        throw std::runtime_error( PQresStatus( PQresultStatus ( select_res.get() )) );        //Checking for bad tuples

    distances.resize(n_rows);
    distances = get_distances( select_res );
    
    select_res.reset();
    
    return distances;
    
}


std::vector<relation> db::request_relations_with_pills( std::vector<drug> drugs )
{
    
    std::ifstream request_file;
    
    size_t n_rows;
    size_t length;
	const size_t n = 256;
    
	char *buf =  new char[n];
    std::string request;
    std::string file_name;
    
    std::vector<relation> relations;
    
    length = drugs.size();
    
    std::vector<int> drug_ids (length);
    
    for (size_t i = 0; i < length; i++)
        drug_ids[i] = drugs[i].get_id();
    
    file_name = "requests/request_relations.txt";
        
    request_file.open( file_name );        //Getting request from file
    
    if ( request_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    request_file.getline( buf, 256 );
                        
    request = buf;
    request += transform_ids_to_string( drug_ids );
    
    delete buf;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
    
    n_rows = PQntuples( select_res.get() );
    
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK && ( n_rows == length) ) )
        throw std::runtime_error( PQresStatus( PQresultStatus ( select_res.get() )) );        //Checking for bad tuples

    relations.resize(n_rows);
    relations = get_relations( select_res );
    
    select_res.reset();
    
    return relations;
    
}


// insert methods

void db::insert_drugstores( std::vector<drugstore> drugstores )
{

    std::ifstream request_file;
    
    std::string transaction;
    std::string request;
    std::string file_name;
    
    std::size_t n;
    
    n = 256;
    
    char *buf =  new char[n];

    if ( drugstores.size() > 0 )
        transaction = drugstores[0].to_string();
        
    for ( size_t i = 1; i < drugstores.size(); i++ )
    {
        transaction += (" " + drugstores[i].to_string() );
    }
    
    
    file_name = "requests/transaction_drugstores.txt";
        
    request_file.open( file_name );
    
    if ( request_file.is_open() )
		std::cout<<"Opened request file"<<std::endl;
        
	else
	{
        delete buf;
		throw std::runtime_error("Unable to open request file");
	}

    request_file.getline( buf, n );
                        
    request = buf;
    request += transaction;
    
    select_res.reset( PQexec( connection.get_connection().get(), request.c_str() ), &PQclear );
        
    if ( !( PQresultStatus( select_res.get() ) == PGRES_TUPLES_OK ) )
        throw std::runtime_error( PQresStatus( PQresultStatus ( select_res.get() )) );  
        
    delete buf;
}