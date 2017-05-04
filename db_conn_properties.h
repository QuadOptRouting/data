#ifndef DB_CONN_PROPERTIES_H
#define DB_CONN_PROPERTIES_H
#include <iostream>
#include <fstream>

class properties
{
private:

    std::string c_host;
    std::string c_dbport;
    std::string c_dbname;
    std::string c_dbuser;
    std::string c_dbpass;

public:

	bool substitute_properties();

	std::string get_host()
    {
		return c_host;
    }
    
	std::string get_dbport()
    {
		return c_dbport;
    }
    
	std::string get_dbname()
    {
		return c_dbname;
    }
    
	std::string get_dbuser()
    {
		return c_dbuser;
    }
        
	std::string get_dbpass()
    {
		return c_dbpass;
    }

};

//

#endif //DB_CONN_PROPERTIES_H*/
