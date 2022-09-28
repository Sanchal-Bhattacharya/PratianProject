#include "DataColumn.h"

using namespace std;

namespace gc
{
	namespace db
	{
		DataColumn::DataColumn(boost::any data)
		{
			this->data = data;
		}

		boost::any DataColumn::getColumnData() const
		{
			return data;
		}

		void DataColumn::setColumnData(boost::any data)
		{
			this->data = data;
		}
	} // namespace db
} // namespace gc
