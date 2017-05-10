#include "db_conn_class.h"

db_connection::db_connection()
{
    if ( credentials.substitute_properties()==0 )
    {
        throw std::runtime_error("Can't find credentials");
    }
    
    connection.reset( PQsetdbLogin( credentials.get_host().c_str(), credentials.get_dbport().c_str(), nullptr, nullptr, credentials.get_dbname().c_str(), credentials.get_dbuser().c_str(), PQencryptPassword( credentials.get_dbpass().c_str(), credentials.get_dbuser().c_str()) ), &PQfinish );
    
    if ( PQstatus( connection.get() ) != CONNECTION_OK )
        throw std::runtime_error( PQerrorMessage( connection.get()) );
        
}

std::shared_ptr<PGconn> db_connection::get_connection() const
{
    return connection;
}