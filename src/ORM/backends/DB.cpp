#include <stdio.h>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/Query.hpp>
#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/fields/private/VAttr.hpp>

#include <memory>

namespace orm
{

    DB::DB(const std::string& username,const std::string& pass,const std::string& db,const std::string& serveur,int port) : _username(username),
        _password(pass),
        _dbName(db),
        _serveur(serveur),
        _port(port)
    {
    };

    DB::~DB()
    {
    }

    bool DB::operator==(const DB& other) const
    {
        return (
                (_dbName == other._dbName)
                and (_serveur == other._serveur)
                and (_port == other._port)
                //and (s_username == other.s_username)
                //and (s_password === other.s_password)
                );
    }
    void DB::setUser(const std::string& user)
    {
        _username = user;
    }

    void DB::setPassword(const std::string& pass)
    {
        _password = pass;
    }

    void DB::setDb(const std::string& db)
    {
        _dbName = db;
    }

    void DB::setServer(const std::string& server)
    {
        _serveur = server;
    }

    void DB::setPort(unsigned int port)
    {
        _port = port;
    }

    bool DB::_save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs)
    {
        const unsigned int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "INSERT INTO "+_escapeColumn(table)+"("+attrs[0]->_column;

            for(unsigned int i=1;i<size;++i)
            {
                str_q+=","+attrs[i]->_column;
            }
            str_q+=") ";

            str_q+="VALUES ((?)";
            for(unsigned int i=1;i<size;++i)
            {
                str_q+=",(?)";
            }
            str_q+=");";

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<ORM_COLOUR_BLUE<<"[Sql:insert] "<<str_q<<"\nVALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);

            for(unsigned int i=0;i<size;++i)
            {
                //prepare the field
                attrs[i]->_beforeSave();

                #if ORM_DEBUG & ORM_DEBUG_SQL
                std::cerr<<","<<*attrs[i];
                #endif
                attrs[i]->_setToQuery(q,i+_getInitialSetcolumnNumber());
                attrs[i]->_modified = false;
                //post save
                attrs[i]->_afterSave();
            }
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<")"<<std::endl;
            #endif

            q._execute();
            q._next();
            delete &q;

            pk = _getLastInsertPk();
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<ORM_COLOUR_YELLOW<<"new PK: "<<pk<<" in table "<<table<<ORM_COLOUR_NONE<<std::endl;
            #endif

            return true;

        }
        return false;
    };

    bool DB::_update(const std::string& table,const int& pk,const std::vector<VAttr*>& attrs)
    {
        const unsigned int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "UPDATE "+_escapeColumn(table)+" SET ";

            bool first(true);
            for(unsigned int i=0;i<size;++i)
            {
                //prepare the field (can change modify)
                attrs[i]->_beforeUpdate();

                if(attrs[i]->_modified)
                {
                    if(not first)
                    {
                        str_q+=", ";
                    }
                    first = false;
                    str_q+=attrs[i]->_column+"=(?)";

                }
            }

            str_q+=" WHERE "+_escapeColumn(table)+"."+_escapeColumn("pk")+" = "+std::to_string(pk)+";"; ///< \todo column.id


            if(first) //NO MAJ NEDEED
            {
                #if ORM_DEBUG & ORM_DEBUG_SQL
                std::cerr<<ORM_COLOUR_BLUE2<<"[Sql:update] "<<str_q<<"\nNo Update needed, exit"<<ORM_COLOUR_NONE<<std::endl;
                #endif

                return false;
            }

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<ORM_COLOUR_BLUE2<<"[Sql:update] "<<str_q<<"\nVALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);

            int index=_getInitialSetcolumnNumber();
            for(unsigned int i=0;i<size;++i)
            {
                if(attrs[i]->_modified)
                {
                    #if ORM_DEBUG & ORM_DEBUG_SQL
                    attrs[i]->printValue(std::cerr)<<",";
                    #endif
                    attrs[i]->_setToQuery(q,index++);
                    attrs[i]->_modified = false;
                    //after update (can change modify)
                    attrs[i]->_afterUpdate();
                }
            }

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<")"<<ORM_COLOUR_NONE<<std::endl;
            #endif
            q._execute();
            q._next();
            delete &q;

        }
        return true;
    };

    bool DB::_del(const std::string& table,const int& pk)
    {
        std::string str_q = "DELETE FROM "+_escapeColumn(table)+" WHERE ("+_escapeColumn(table)+"."+_escapeColumn("pk")+" = "+std::to_string(pk)+");";

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<ORM_COLOUR_COMMENTS<<"[Sql:delete]"<<str_q<<ORM_COLOUR_NONE<<std::endl;
        #endif

        Query* q = prepareQuery(str_q);
        q->_execute();
        q->_next();
        delete  q;

        return true;
    };

    std::string DB::_escapeColumn(const std::string& str) const
    {
        return "'"+str+"'";
    }

    void ReplaceStringInPlace(std::string& subject, const std::string& search,const std::string& replace)
    {
        size_t pos = 0;
        while((pos = subject.find(search, pos)) != std::string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    template<>
    std::string DB::_formatValue(const std::string& filter,std::string value) const
    {
        if(filter == "contains")
        {
            value = "%"+value+"%";
        }
        else if(filter == "icontains")
        {
            value = "%"+value+"%";
        }
        else if(filter == "startswith")
        {
            value = value+"%";
        }
        else if(filter == "istartswith")
        {
            value = value+"%";
        }
        else if(filter == "endswith" )
        {
            value = "%"+value;
        }
        else if(filter == "iendswith")
        {
            value = "%"+value;
        }

        return value;
    }

    std::string DB::_formatPreparedValue(const std::string& filter) const
    {
        const std::string& op = _operators.at(filter);
        std::unique_ptr<char>buffer (new char[op.size() + 3]);
        sprintf(buffer.get(),op.c_str(),"(?)");

        return std::string(buffer.get());
    }


    std::string DB::_makecolumname(DB& db,const std::string& prefix,const std::string& column)
    {
        return db._escapeColumn(prefix)+"."+db._escapeColumn(column);
    }
}
//orm::DB* orm::DB::Default = 0;

