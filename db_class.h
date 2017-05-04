#ifndef DB_CLASS_H
#define DB_CLASS_H
#include </usr/include/postgresql/libpq-fe.h>
//#include "db_table_class.h"
#include "db_conn_class.h"
#include "db_request.h"
//#include </usr/include/postgresql/libpq-fe.h>
#include <vector>

class db
{
private:
    

    db_connection connection;
    std::string transform_ids_to_string( std::vector<int> id );    
    std::unique_ptr<PGresult> select_res;
    
public:

    db();
    
    size_t get_tuples_count();
    
    std::vector<drugstore> request_drugstores( std::vector<int> square , std::string select_type);
    std::vector<drug> request_drugs( std::vector<int> drug_ids );
    std::vector<distance> request_distances( std::vector<drugstore> drugstores );
    std::vector<relation> request_relations_with_pills( std::vector<drug> drugs );
    
    void insert_drugstores( std::vector<drugstore> drugstores );
    
 //   void get_drugs(std::vector<drug> drugstores);
 //   void get_drugstores(std::vector<drugstore> drugstores);
 //   void get_relations(std::vector<relation> relations);
  //  void get_distances(std::vector<distance> distances);
    
    
}