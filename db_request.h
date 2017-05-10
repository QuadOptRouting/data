#ifndef DB_REQUEST_H
#define DB_REQUEST_H

#include </usr/include/postgresql/libpq-fe.h>
#include "db_table_class.h"
#include <vector>

std::vector<drug> get_drugs(std::shared_ptr<PGresult> res);
std::vector<drugstore> get_drugstores(std::shared_ptr<PGresult> res);
std::vector<drugstore_no_coordinates> get_drugstores_no_coordinates(std::shared_ptr<PGresult> res);
std::vector<relation> get_relations(std::shared_ptr<PGresult> res);
std::vector<distance> get_distances(std::shared_ptr<PGresult> res);

//

#endif //DB_REQUEST_H*/
