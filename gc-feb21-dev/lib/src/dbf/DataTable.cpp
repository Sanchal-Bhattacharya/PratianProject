#include "DataTable.h"

namespace gc
{
	namespace db
	{
		DataTable::DataTable(Schema *data)
		{
			schema = data;
		}

		void DataTable::addRow(DataTable::DataRow *row)
		{
			tuple.push_back(row);
		}

		vector<DataTable::DataRow *> DataTable::getRows()
		{
			return tuple;
		}

		int DataTable::getColumnType(int index)
		{
			return schema->getColumnType(index);
		}

		int DataTable::getColumnIndex(string name)
		{
			return schema->getColumnIndex(name);
		}

		int DataTable::getNumberOfColumns()
		{
			return schema->getNumberOfColumns();
		}

		DataTable::DataRow::DataRow(DataTable *table)
		{
			this->table = table;
		}

		void DataTable::DataRow::addColumn(DataColumn *data)
		{
			column.push_back(data);
		}

		DataTable::DataRow::~DataRow()
		{
			for (int i = 0; i < column.size(); i++)
			{
				delete column[i];
				column[i] = NULL;
			}
			table = NULL;
		}

		DataTable::~DataTable()
		{
			for (int i = 0; i < tuple.size(); i++)
			{
				delete tuple[i];
				tuple[i] = NULL;
			}
			delete schema;
			schema = NULL;
		}

	} // namespace db
} // namespace gc
