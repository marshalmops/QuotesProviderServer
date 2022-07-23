#ifndef DATABASEQUERYPARSERRESULTINTERFACE_H
#define DATABASEQUERYPARSERRESULTINTERFACE_H


class DatabaseQueryParserResultInterface
{
public:
    DatabaseQueryParserResultInterface() = default;
    virtual ~DatabaseQueryParserResultInterface() = default;
    
    virtual bool isValid() const = 0;
};

#endif // DATABASEQUERYPARSERRESULTINTERFACE_H
