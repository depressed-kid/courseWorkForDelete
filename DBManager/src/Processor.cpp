#include "Processor.h"
#include "Manipulator.h"
#include "Selector.h"
#include "dbmapper.h"
#include <mutex>

namespace db
{
struct Processor::ProcessorPrivate
{
    Manipulator manipulator;
    Selector selector;
#ifdef INSERT_TEST_DATA
    void insertMockData();
    std::once_flag initialized;
#endif
};

#ifdef INSERT_TEST_DATA
void Processor::ProcessorPrivate::insertMockData()
{
    manipulator.insertRow("Export", {{"Помидор", "Великобритания", 100, "Канада"}});
    manipulator.insertRow("Export", {{"Апельсин", "США", 1000, "Россия"}});
    manipulator.insertRow("Export", {{"Гриб", "ОАЭ", 500, "ManufacturerCountry"}});
    manipulator.insertRow("Export", {{"Груша", "Россия", 250, "Австралия"}});
    manipulator.insertRow("Export", {{"Мороженное", "Украина", 2500, "Перу"}});
    manipulator.insertRow("Export", {{"Машины", "Канада", 678, "Германия"}});
    manipulator.insertRow("Export", {{"Вода", "Австралия", 90, "Украина"}});
    manipulator.insertRow("Export", {{"Чай", "Перу", 1000000, "Италия"}});
    manipulator.insertRow("Export", {{"Пирог", "Германия", 24000, "ОАЭ"}});
    manipulator.insertRow("Export", {{"Хлеб", "Италия", 100, "США"}});
    manipulator.insertRow("Export", {{"Укроп", "Мексика", 1, "Великобритания"}});
    manipulator.insertRow("Export", {{"Телевизор", "Норвегия", 890, "Бельгия"}});
    manipulator.insertRow("Export", {{"Утюг", "Япония", 657, "Япония"}});
    manipulator.insertRow("Export", {{"Футболка", "Бельгия", 3, "Норвегия"}});
    manipulator.insertRow("Export", {{"Пижама", "Уругвай", 86000, "Мексика"}});
}
#endif

db::Processor::Processor()
    : m_d {new ProcessorPrivate {}}
{
#ifdef INSERT_TEST_DATA
    auto inserter = [this] {
        m_d->insertMockData();
    };
    std::call_once(m_d->initialized, inserter);
#endif
}

Processor::~Processor()
{
}

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> Processor::requestTableData(DBTypes::DBTables table)
{
    std::vector<QVariantList> result;
    const DBTypes::DBResult resultState {m_d->selector.selectAll(tableMapper.at(table), result)};
    return std::make_pair(resultState, std::move(result));
}

void Processor::addTableData(DBTypes::DBTables table,  const QVariantList& data)
{
    m_d->manipulator.insertRow(tableMapper.at(table), data);

}

void Processor::deleteTableData(DBTypes::DBTables table, const QString& data)
{
    m_d->manipulator.deleteRow(tableMapper.at(table), (data.toStdString()));
}

}













