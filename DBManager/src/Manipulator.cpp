#include "Manipulator.h"
#include <sstream>
#include "dbmapper.h"
#include <QSqlError>

using namespace DBTypes;

namespace db
{

std::pair<DBResult, int> Manipulator::insertRow(const std::string& tableName, const QVariantList& rowData)
{
    const std::string& query {generateInsertQuery(tableName, rowData.size())};
    const std::pair<DBResult, QSqlQuery>& result {m_executor.execute(query, rowData)};
    return std::make_pair(result.first,
                          result.second.lastInsertId().toInt());
}

void Manipulator::deleteRow(const std::string &tableName, const std::string & good)
{
    const std::string& queryText {
        "DELETE FROM " + tableName + " WHERE Name=\"" +  good + "\";"
    };
    QSqlQuery query {QString::fromStdString(queryText)};

    if (!query.exec()) {
        qInfo() << query.lastError();
    }

}

std::string Manipulator::generateBindString(size_t paramCount) const
{
    std::ostringstream bindings;
    std::fill_n(std::ostream_iterator<std::string>(bindings),
                paramCount,
                "?,");

    std::string bindString = bindings.str();
    bindString.pop_back(); // the last ","

    return bindString;
}

std::string Manipulator::generateInsertQuery(const std::string& tableName, size_t paramCount) const
{
    std::string query = "INSERT INTO " + tableName +  " (" + tablesMapping.at(tableName) + ")"
                        " VALUES (";

    query += generateBindString(paramCount);
    query += ")";

    return query;
}
}
