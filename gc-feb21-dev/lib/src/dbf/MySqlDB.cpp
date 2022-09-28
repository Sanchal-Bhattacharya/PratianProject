#include "MySqlDB.h"

namespace gc
{
	namespace db
	{
		MySqlDB::MySqlDB(string _dbName, string _IPAddress, string _UserName, string _Password)
			: dbName(_dbName), IPAddress(_IPAddress), UserName(_UserName), Password(_Password)
		{
			this->getConnection();
		}

		int MySqlDB::getConnection()
		{
			a = conn.connect(dbName.c_str(), IPAddress.c_str(), UserName.c_str(), Password.c_str());
			return 1;
			//cout<<"Database Connected"<<endl;
			if (a != 1)
			{
				string msg = "CONNECTION EXCEPTION RAISED " + string(conn.error());
				throw dao::DAOConnectionException(msg);
			}
		}
		int MySqlDB::closeConnection()
		{
			/*if (a!=1)
			{
				//cout<< "Database Not Connected"<<endl;
				string msg = "CONNECTION EXCEPTION RAISED "+ string(conn.error());
				throw dao::DAOConnectionException(msg);
				exit(0);
				
			}	*/
			conn.disconnect();
			a = 0;
			return 1;
			//cout<<"Database Disconnected"<<endl;
		}

		DataTable *MySqlDB::execQuerry(string mysql_query)
		{
			if (a == 1) // To ensure that the connection is made
			{
				try
				{
					mysqlpp::Query query = conn.query(mysql_query);
					try
					{
						mysqlpp::StoreQueryResult res = query.store();

						mysqlpp::StoreQueryResult::const_iterator it;
						int nos_columns = 0; // No.of columns
						for (size_t i = 0; i < res.field_names()->size(); i++)
						{
							nos_columns++;
						}
						const char *char_column_content; //
						int number_column_content;		 //
						vector<int> types;				 //1 for string and  2 for int
						vector<string> column_names;	 //column names
						for (size_t i = 0; i < res.field_names()->size(); i++)
						{
							mysqlpp::FieldTypes::value_type ft = res.field_type(int(i));
							ostringstream os;
							os << ft.sql_name();
							string str = string(os.str());
							switch (str[0])
							{
							case 'V':
								types.push_back(1); // If varchar then 1
								column_names.push_back(str);
								break;
							case 'C':
								types.push_back(1); // If varchar then 1
								column_names.push_back(str);
								break;
							case 'D':
								types.push_back(1); // If date then 1
								column_names.push_back(str);
								break;
							case 'I':
								types.push_back(2); // If integer then 2
								column_names.push_back(str);
								break;
							}
						}

						Schema *schema = new Schema(nos_columns, types, column_names);
						DataTable *table = new DataTable(schema);
						DataTable::DataRow *row;

						for (it = res.begin(); it != res.end(); ++it)
						{
							row = new DataTable::DataRow(table);
							//mysqlpp::Row row = *it;
							DataColumn *data;
							for (int j = 0; j < nos_columns; j++)
							{
								mysqlpp::Row row2 = *it;
								cout << '\t' << row2[j] << "\t";
								switch (types[j])
								{
								case STRING:
									char_column_content = row2[j].c_str();
									data = new DataColumn(string(char_column_content));
									break;
								case INT:
									number_column_content = row2[j];
									data = new DataColumn(number_column_content);
									break;
								}
								row->addColumn(data);
								data = NULL;
							}
							table->addRow(row);
							row = NULL;
						}
						vector<DataTable::DataRow *> tuple = table->getRows();

						//	cout<<endl<<endl;
						//	cout<<tuple[2]->getColumn<string,STRING>(1)<<endl;

						return table;
					}

					catch (const mysqlpp::BadQuery &er)
					{
						string msg = "BAD QUERY EXCEPTION RAISED " + string(query.error());
						throw dao::DAOQuerryException(msg);
					}
				}
				catch (const mysqlpp::BadQuery &er)
				{
					// Handle any query errors
					string msg = "BAD QUERY EXCEPTION RAISED " + string(er.what());
					//delete table;
					throw dao::DAOQuerryException(msg);
				}
				catch (const mysqlpp::BadConversion &er)
				{
					// Handle bad conversions
					string msg = "BAD CONVERSION RAISED " + string(er.what());
					//delete table;
					throw dao::DAOQuerryException(msg);
				}
				catch (const mysqlpp::Exception &er)
				{
					string msg = "EXCEPTION RAISED " + string(er.what());
					//delete table;
					throw dao::DAOQuerryException(msg);
				}
			}
			else
			{
				string msg = "CONNECTION EXCEPTION RAISED " + string(conn.error());
				throw dao::DAOConnectionException(msg);
			}
		}

		int MySqlDB::execNonQuerry(string mysql_query)
		{
			if (a == 1)
			{

				try
				{
					mysqlpp::Query query = conn.query(mysql_query);
					query.execute();
				}
				catch (const mysqlpp::BadQuery &er)
				{
					// Handle any query errors
					string msg = "BAD QUERY EXCEPTION RAISED " + string(er.what());
					throw dao::DAOQuerryException(msg);
					return -1;
				}
				catch (const mysqlpp::BadConversion &er)
				{
					// Handle bad conversions
					string msg = "BAD CONVERSION RAISED " + string(er.what());
					throw dao::DAOQuerryException(msg);
					return -1;
				}
				catch (const mysqlpp::Exception &er)
				{
					string msg = "EXCEPTION RAISED " + string(er.what());
					throw dao::DAOQuerryException(msg);
					return -1;
				}
				return 0;
			}
			else
			{
				string msg = "CONNECTION EXCEPTION RAISED " + string(conn.error());
				throw dao::DAOConnectionException(msg);
				return 1;
			}
		}

		MySqlDB::~MySqlDB()
		{
			this->closeConnection();
		}
	} // namespace db
} // namespace gc
