#pragma once
#include "dbtypes.h"
#include <memory>

namespace db
{
class Processor
{
public:
    Processor();
    ~Processor();
    std::pair<DBTypes::DBResult,
              std::vector<DBTypes::DBEntry>> requestTableData(DBTypes::DBTables table);

    void addTableData(DBTypes::DBTables table,  const QVariantList& data);
    void deleteTableData(DBTypes::DBTables table,  const QString & data);

private:
    struct ProcessorPrivate;
    std::unique_ptr<ProcessorPrivate> m_d;
};
}
