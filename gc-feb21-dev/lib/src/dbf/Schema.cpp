#include "Schema.h"
#include <iostream>
using namespace std;

namespace gc
{
	namespace db
	{
		Schema::Schema(int nos, vector<int> &column_types, vector<string> &column_names)
		{
			nos_of_columns = nos;
			this->column_types = column_types;
			this->column_names = column_names;
		}

		int Schema::getColumnType(int index)
		{
			return column_types[index];
		}

		int Schema::getNumberOfColumns()
		{
			return nos_of_columns;
		}
		string Schema::getColumnName(int index)
		{
			return column_names[index];
		}

		int Schema::getColumnIndex(string name)
		{
			int flag = 1;
			for (int i = 0; i < column_names.size(); i++)
			{
				if (strcmp(name.c_str(), column_names[i].c_str()) == 0)
				{
					flag = 0;
					return i;
				}
			}
			if (flag == 1)
			{
				//throw exception
			}
		}
	} // namespace db
} // namespace gc
