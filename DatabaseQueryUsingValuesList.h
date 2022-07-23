#ifndef DATABASEQUERYUSINGVALUESLIST_H
#define DATABASEQUERYUSINGVALUESLIST_H

#include <vector>
#include <QVariant>

class DatabaseQueryUsingValuesList
{
public:
    using ValuesList = std::vector<QVariant>;
    
    DatabaseQueryUsingValuesList(const ValuesList &values);
    DatabaseQueryUsingValuesList(const std::initializer_list<QVariant> &values);
    
    const ValuesList& getValues() const;
    
protected:
    ValuesList m_values;
};

#endif // DATABASEQUERYUSINGVALUESLIST_H
