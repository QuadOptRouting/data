#ifndef DB_CONN_CLASS_H
#define DB_CONN_CLASS_H
#include <memory>
#include <db_conn_properties.h>
#include </usr/include/postgresql/libpq-fe.h>

class db_connection
{
private:
    
    properties credentials;
    std::shared_ptr<PGconn> connection;
 
public:

    std::shared_ptr<PGconn> get_connection() const;
    db_connection();

};


//

#endif //DB_CONN_CLASS_H*/

