#include "db_conn_properties.h"

bool properties::substitute_properties()
{

	std::ifstream properties_file;

	const size_t n = 128;

	char *buf =  new char[n];

	std::string host;
	std::string dbport;
	std::string dbname;
	std::string dbuser;
	std::string dbpass;

	size_t length;
	size_t parameter_flag;

	properties_file.open("db_connection_properties.txt");

	if ( properties_file.is_open() )
		std::cout<<"Opened properties file"<<std::endl;
        
	else
	{
		std::cout<<"Unable to open properties file"<<std::endl; //check for file
        delete buf;
		return 0;
	}



	if ( !properties_file.eof() )			// checking for host
	{
		properties_file.getline( buf, 128 );
		host = buf;
		length = host.length();

		parameter_flag = host.find("host=");

		if ( parameter_flag == 0 && (length-5) > 0 )		//5 - is a length of "host= string, subtract it from length to get host length
		{
			std::cout<<"DBhost found"<<std::endl;
			this->c_host = host.substr( 5, length-5 );
		}

		else
		{
			std::cout<<"Error reading host, check properties file"<<std::endl;
            delete buf;
			return 0;
		}
	}

	else
	{
		std::cout<<"Error: properties file is empty"<<std::endl;
        delete buf;
		return 0;
	}

	if (!properties_file.eof())			// cheching for dbport
	{
		properties_file.getline(buf, 128);
		dbport = buf;
		length = dbport.length();

		parameter_flag = dbport.find("dbport=");

		if (parameter_flag == 0 && ( length - 7 ) > 0)
		{
			std::cout<<"DBport found"<<std::endl;
			this->c_dbport = dbport.substr( 7 , length - 7 );
		}

		else
		{
			std::cout<<"Error reading dbport, check properties file"<<std::endl;
            delete buf;
			return 0;
		}
	}

	else
	{
		std::cout<<"Error: properties file is not full"<<std::endl;
        delete buf;
		return 0;
	}

	if (!properties_file.eof())			// cheching for dbname
	{
		properties_file.getline( buf, 128 );
		dbname = buf;
		length = dbname.length();

		parameter_flag = dbname.find("dbname=");

		if (parameter_flag == 0 && ( length - 7 ) > 0)
		{
			std::cout<<"DBname found"<<std::endl;
			this->c_dbname = dbname.substr( 7, length - 7);
		}

		else
		{
			std::cout<<"Error reading DBname, check properties file"<<std::endl;
            delete buf;
			return 0;
		}
	}

	else
	{
		std::cout<<"Error: properties file is not full"<<std::endl;
        delete buf;
		return 0;
	}

	if ( !properties_file.eof() )			// cheching for dbuser
	{
		properties_file.getline( buf, 128 );
		dbuser = buf;
		length = dbuser.length();

		parameter_flag = dbuser.find("dbuser=");

		if (parameter_flag == 0 && ( length - 7 ) > 0 )
		{
			std::cout<<"DBuser found"<<std::endl;
			this->c_dbuser = dbuser.substr( 7, length - 7 );
		}

		else
		{
			std::cout<<"Error reading dbuser, check properties file"<<std::endl;
            delete buf;
			return 0;
		}
	}

	else
	{
		std::cout<<"Error: properties file is not full"<<std::endl;
        delete buf;
		return 0;
	}

	if ( !properties_file.eof() )			// cheching for dbpass
	{
		properties_file.getline( buf, 128 );
		dbpass = buf;
		length = dbpass.length();

		parameter_flag = dbpass.find("dbpass=");

		if (parameter_flag == 0 && ( length - 7 ) > 0)
		{
			std::cout<<"DBpass found"<<std::endl;
			this->c_dbpass = dbpass.substr( 7 ,length - 7 );
		}

		else
		{
			std::cout<<"Error reading dbpass, check properties file"<<std::endl;
            delete buf;
            return 0;
		}
	}

	else
	{
		std::cout<<"Error: properties file is not full"<<std::endl;
        delete buf;
		return 0;
	}


	std::cout<<"Successfully read properties file"<<std::endl;

    delete buf;

	return 1;
}


