#include <algorithm>

#include <ORM/backends/Query.hpp>


namespace orm
{
    Query::Query(DB& b,const std::string& q) :
        _prepared(false),
        _query(q),
        _db(b),
        _executed(false)
    {
    };

    Query::Query(DB& b,std::string&& q) :
        _prepared(false),
        _db(b),
        _executed(false)
    {
        std::swap(q,_query);
    };

    Query::~Query()
    {
    }

    void Query::_execute()
    {
        #if (ORM_DEBUG & ORM_DEBUG_SQL)
        std::cerr<<VERT<<"[Sql] Query::execute()"<<query<<BLANC<<std::endl;
        #endif

        _executed = true;
        /*if(not prepared)
        {
            query+=";";
        }*/
        _executeQuery();
    };

    std::ostream& operator<<(std::ostream& output,const Query* self)
    {
        output<<self->_query;
        return output;
    }

};
