#include "db_request.h"

std::vector<drug> get_drugs( std::shared_ptr<PGresult> select_res )
{
    size_t n_rows = PQntuples( select_res.get() );
    size_t length = 0;

    std::vector <drug> drugs (n_rows);
    
    int column_id = PQfnumber( select_res.get(), "id" );
    int column_name = PQfnumber( select_res.get(), "name" );
//    int column_international_name = PQfnumber( select_res.get(), "international_name" );
    
    
    for ( size_t i = 0; i < n_rows; i++ )
    {
        
        if ( PQgetisnull( select_res.get(), i, column_id ) || PQgetisnull( select_res.get(), i, column_name ) ) //Checking for empty values, if exist at least
            continue;      //Throw row if find null   , long di                                                                                   // one null then continue on next iteration.

        drugs[i].set_id( PQgetvalue( select_res.get(), i, column_id) );
        drugs[i].set_name( PQgetvalue( select_res.get(), i, column_name) );
        
  //      drugs[i].set_international_name( PQgetvalue( select_res.get(), i, column_international_name ) );
        length++;
        
    }
    
    if ( length<n_rows )
    {
        drugs.resize(length);
        drugs.shrink_to_fit();
        
    }
    
    return drugs;
}



std::vector<drugstore> get_drugstores( std::shared_ptr<PGresult> select_res )
{
    size_t n_rows = PQntuples( select_res.get() );
    size_t length = 0;
    
    std::vector <drugstore> drugstores (n_rows);
        
    int column_id = PQfnumber( select_res.get(), "id" );
    int column_address = PQfnumber( select_res.get(), "address" );
    int column_longitude = PQfnumber( select_res.get(), "longitude" );
    int column_latitude = PQfnumber( select_res.get(), "latitude" );
    int column_id_square = PQfnumber( select_res.get(), "id_square" );
    int column_name = PQfnumber( select_res.get(), "name" );
    

    
    for ( size_t i = 0; i<n_rows; i++ )
    {
        
        if ( PQgetisnull( select_res.get(), i, column_id ) || PQgetisnull( select_res.get(), i, column_address ) || PQgetisnull( select_res.get(), i, column_longitude )|| PQgetisnull( select_res.get(), i, column_latitude ) || PQgetisnull( select_res.get(), i, column_id_square ) || PQgetisnull( select_res.get(), i, column_name ) )             
               continue;    //Throw row if find null                                                                        //Checking for empty values, if exist at least
                                                                                                  // one null then continue on next iteration.
        drugstores[i].set_id( PQgetvalue( select_res.get(), i, column_id ) );
        drugstores[i].set_address( PQgetvalue( select_res.get(), i, column_address) );
        drugstores[i].set_longitude(PQgetvalue( select_res.get(), i, column_longitude) );
        drugstores[i].set_latitude( PQgetvalue( select_res.get(), i, column_latitude ) );
        drugstores[i].set_square_id( PQgetvalue( select_res.get(), i, column_id_square ) );
        drugstores[i].set_name( PQgetvalue( select_res.get(), i, column_name ) );
        
        length++;
        
    }
    
    if ( length<n_rows )
    {
        drugstores.resize(length);
        drugstores.shrink_to_fit();
        std::cout<<"Found some nulls in rows"<<std::endl;
    }
    
    return drugstores;
}



std::vector<drugstore_no_coordinates> get_drugstores_no_coordinates( std::shared_ptr<PGresult> select_res )
{
    size_t n_rows = PQntuples( select_res.get() );
    size_t length = 0;
    
    std::vector <drugstore_no_coordinates> drugstores_no_coordinates (n_rows);
        
    int column_id = PQfnumber( select_res.get(), "id" );
    int column_address = PQfnumber( select_res.get(), "address" );
    int column_name = PQfnumber( select_res.get(), "name" );
    

    
    for ( size_t i = 0; i<n_rows; i++ )
    {
        
        if ( PQgetisnull( select_res.get(), i, column_id ) || PQgetisnull( select_res.get(), i, column_address ) || PQgetisnull( select_res.get(), i, column_name ) )             
               continue;    //Throw row if find null                                                                        //Checking for empty values, if exist at least
                                                                                                  // one null then continue on next iteration.
        drugstores_no_coordinates[i].set_id( PQgetvalue( select_res.get(), i, column_id ) );
        drugstores_no_coordinates[i].set_address( PQgetvalue( select_res.get(), i, column_address) );
        drugstores_no_coordinates[i].set_name( PQgetvalue( select_res.get(), i, column_name ) );
        
        length++;
        
    }
    
    if ( length<n_rows )
    {
        drugstores_no_coordinates.resize(length);
        drugstores_no_coordinates.shrink_to_fit();
        
    }
    
    return drugstores_no_coordinates;
}

std::vector<relation> get_relations( std::shared_ptr<PGresult> select_res )
{
    size_t n_rows = PQntuples( select_res.get() );
    size_t length = 0;
    
    std::vector <relation> relations (n_rows);
    
    int column_drug_id = PQfnumber( select_res.get(), "drug_id" );
    int column_drugstore_id = PQfnumber( select_res.get(), "drugstore_id" );
    int column_price = PQfnumber( select_res.get(), "price" );
    int column_count = PQfnumber( select_res.get(), "count" );
    

    
    for ( size_t i = 0; i<n_rows; i++ )
    {
        
        if ( PQgetisnull( select_res.get(), i, column_drug_id ) || PQgetisnull( select_res.get(), i, column_drugstore_id ) || PQgetisnull( select_res.get(), i, column_price ) || PQgetisnull( select_res.get(), i, column_price ) ) //Checking for empty values, if exist at least
            continue;   //Throw row if find null                                                                                       // one null then continue on next iteration.
            
        relations[i].set_drug_id( PQgetvalue( select_res.get(), i, column_drug_id ) );
        relations[i].set_drugstore_id( PQgetvalue( select_res.get(), i, column_drugstore_id ) );
        relations[i].set_price( PQgetvalue( select_res.get(), i, column_price ) );
        relations[i].set_count( PQgetvalue( select_res.get(), i, column_count ) );
        
        length++;
        
    }

    if ( length<n_rows )
    {    
        relations.resize(length);
        relations.shrink_to_fit();
        
    }
    
    return relations;
}



std::vector<distance> get_distances( std::shared_ptr<PGresult> select_res )
{
    size_t n_rows = PQntuples(select_res.get());
    size_t length = 0;

    std::vector <distance> distances (n_rows);

    int column_drugstore_a_id = PQfnumber( select_res.get(), "drugstore_a_id" );
    int column_drugstore_b_id = PQfnumber( select_res.get(), "drugstore_b_id" );
    int column_distance = PQfnumber( select_res.get(), "distance" );
    
    
    for ( size_t i = 0; i<n_rows; i++ )
    {
        
        if ( PQgetisnull( select_res.get(), i, column_drugstore_a_id ) || PQgetisnull( select_res.get(), i, column_drugstore_b_id ) || PQgetisnull( select_res.get(), i, column_distance ) ) //Checking for empty values, if exist at least
            continue;    //Throw row if find null                                                                                        // one null then continue on next iteration.
            
        distances[i].set_drugstore_a_id( PQgetvalue( select_res.get(), i, column_drugstore_a_id ) );
        distances[i].set_drugstore_b_id( PQgetvalue( select_res.get(), i, column_drugstore_b_id ) );
        distances[i].set_distance( PQgetvalue( select_res.get(), i, column_distance ) );

        length++;
        
    }

    if ( length<n_rows )
    {    
        distances.resize(length);
        distances.shrink_to_fit();
        
    }
    
    return distances;
}