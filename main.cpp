//#include "db_conn_class.h"
//#include "db_request.h"
#include "db_class.h"

int main()
{
 /*   db_connection conn;
    
    std::cout<<"successfully established conn"<<std::endl;
    
    std::string drugstore_sql_transaction =  "SELECT * FROM \"QOR_main_scheme\".\"drugstore\" LIMIT 10";

	std::shared_ptr<PGresult> select_from_drugstore;
    
    select_from_drugstore.reset( PQexec( conn.get_connection().get(), drugstore_sql_transaction.c_str() ), &PQclear );
    
    if ( !( PQresultStatus( select_from_drugstore.get() ) == PGRES_TUPLES_OK && PQntuples( select_from_drugstore.get() ) ) )
        throw std::runtime_error("Exception with request"); //Checking for bad tuples
    
    std::vector<drugstore_no_coordinates> received_drugstores (10);
    received_drugstores = get_drugstores_no_coordinates( select_from_drugstore );
    
    std::cout<<PQntuples( select_from_drugstore.get() )<<std::endl;
    std::cout<<received_drugstores[0].get_address()<<std::endl;
    std::cout<<"success. total."<<std::endl;*/
    db example;
    
    std::vector<int> drugstore_ids (2);
    
    std::vector<drugstore> received_drugstores (drugstore_ids.size());
    
    drugstore_ids[0] = 135;
    drugstore_ids[1] = 107;
    
    std::cout<<drugstore_ids.size()<<std::endl;
    
    received_drugstores = example.request_drugstores( drugstore_ids );
    std::cout<<received_drugstores.size()<<std::endl;
    
    std::vector<int> drug_ids (2);
    std::vector<drug> received_drugs ( drug_ids.size() );
    
    drug_ids[0] = 136698;
    drug_ids[1] = 132531;
   
  //  std::cout<<drug_ids.size()<<std::endl;
    
    received_drugs = example.request_drugs( drug_ids );
    
  //  std::cout<<received_drugs.size()<<std::endl;
    std::cout<<"first element id: "<<received_drugs[0].get_id()<<std::endl;
    
    return 0;
    
}













/*#include "db_conn_properties.h"
#include "db_query.h"

int main()
{
    Properties credentials;

    bool properties_flag = credentials.substitute_properties(); //Receiving credentials

    if (!properties_flag) //checking for error
    {
        std::cout<<"Error in credentials"<<std::endl;
        return 0;
    }



	std::cout<<"Successfully found credentials"<<std::endl;
	PGconn *connection = PQsetdbLogin(credentials.get_host().c_str(),credentials.get_dbport().c_str(),nullptr,nullptr,credentials.get_dbname().c_str(),credentials.get_dbuser().c_str(),PQencryptPassword(credentials.get_dbpass().c_str(),credentials.get_dbuser().c_str()));
	std::cout<<"Connection is functioning"<<std::endl;
	switch(PQstatus(connection))
	{
			case CONNECTION_STARTED:
				std::cout<<"connection started..."<<std::endl;
				break;

			case CONNECTION_MADE:
				std::cout<<"Connection made..."<<std::endl;
				break;

			case CONNECTION_BAD:
				std::cout<<"Connection is not working"<<std::endl;
				break;

			case CONNECTION_OK:
				std::cout<<"Connection is OK"<<std::endl;
				break;

			case CONNECTION_AWAITING_RESPONSE:
				std::cout<<"Connection is waiting for response"<<std::endl;
				break;

			case CONNECTION_SSL_STARTUP:
				std::cout<<"Connection ssl startup"<<std::endl;
				break;

			case CONNECTION_SETENV:
				std::cout<<"Connection ssl startup"<<std::endl;
				break;

			case CONNECTION_AUTH_OK:
				std::cout<<"connection auth ok"<<std::endl;
				break;

			default:
				std::cout<<"???...;"<<std::endl;
				break;
	}


	std::cout<<"Trying to make a Select"<<std::endl;

	char *drugstore_sql_transaction =  "SELECT * FROM \"QOR_main_scheme\".\"drug\" LIMIT 10";

	PGresult *select_from_drugstore =  PQexec(connection, drugstore_sql_transaction);

	if (PQresultStatus(select_from_drugstore)!=PGRES_TUPLES_OK)
	{
		PQclear(select_from_drugstore);
		PQfinish(connection);
		std::cout<<PQresStatus(PQresultStatus(select_from_drugstore))<<std::endl;
		std::cout<<"Transaction failed"<<std::endl;
		return 0;
	}

	std::cout<<"Successfully send query \""<<drugstore_sql_transaction<<"\" and received data"<<std::endl;

	size_t n_rows = PQntuples(select_from_drugstore);
	size_t m_cols = PQnfields(select_from_drugstore);

	std::cout<<"rows count: "<<n_rows<<std::endl;
	std::cout<<"columns count: "<<m_cols<<std::endl;

	std::string *values = new std::string[n_rows*m_cols];

	for (size_t i=0; i<n_rows; i++)
	{
		for (size_t j=0; j<m_cols; j++)
		{
			values[i*m_cols+j] = PQgetvalue(select_from_drugstore,i,j);
			std::cout<<values[i*m_cols+j]<<"  ";
		}
		std::cout<<""<<std::endl;
	}

	std::cout<<"end"<<std::endl;

	PQclear(select_from_drugstore);
	PQfinish(connection);




	return 0;
}*/