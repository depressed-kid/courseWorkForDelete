#pragma once
#include "dbtypes.h"



namespace db
{
static const std::map<DBTypes::DBTables, std::string> tableMapper {
    {DBTypes::DBTables::Export, "Export"}
};

static const std::map<std::string, std::string> tablesMapping = {
    {"Export", "Name, Country, Size, ManufacturerCountry"},
};
}
