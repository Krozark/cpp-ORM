#include "Bdd.hpp"
#include "Query.hpp"
#include "SQLObjectBase.hpp"
#include "VAttr.hpp"

namespace orm
{
    Bdd::Bdd(const std::string& username,const std::string& pass,const std::string& bdd,const std::string& serveur,const std::string& port) : s_username(username),
        s_password(pass),
        s_bdd_name(bdd),
        s_serveur(serveur),
        s_port(port)
    {
    };

    /*const std::string& Bdd::operator[](const std::string& key)
    {
        return operators[key];
    };*/

    /*bool Bdd::save(SQLObjectBase* obj)
    {
    };

    bool Bdd::update(SQLObjectBase* obj)
    {
    };*/

    bool Bdd::save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs)
    {
        const int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "INSERT INTO "+escape_colum(table)+"("+escape_colum(attrs[0]->colum);

            for(unsigned int i=1;i<size;++i)
                str_q+=","+escape_colum(attrs[i]->colum);
            str_q+=") ";

            str_q+="VALUES ((?)";
            for(unsigned int i=1;i<size;++i)
                str_q+=",(?)";
            str_q+=");";
            
            #if DEBUG & DEBUG_SQL
            std::cout<<"Bdd::update(): "<<str_q<<" VALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);

            for(unsigned int i=0;i<size;++i)
            {
                #if DEBUG & DEBUG_SQL
                std::cout<<","<<*attrs[i];
                #endif
                attrs[i]->set(q,i+1);
                attrs[i]->modify = false;
            }
            #if DEBUG & DEBUG_SQL
            std::cout<<")"<<std::endl;
            #endif

            executeQuery(q);
            delete &q;

            pk = getLastInsertPk();
            #if DEBUG & DEBUG_SQL
            std::cout<<" new PK: "<<pk<<std::endl;
            #endif

            return true;

        }
        return -1;
    };

    bool Bdd::update(const std::string& table,const int& pk,const std::vector<VAttr*>& attrs)
    {
        const int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "UPDATE "+escape_colum(table)+" SET "+escape_colum(attrs[0]->colum)+"=(?)";

            for(unsigned int i=1;i<size;++i)
                str_q+=","+escape_colum(attrs[i]->colum)+"=(?)";

            str_q+=" WHERE "+escape_colum("id")+"="+std::to_string(pk)+";"; //TODO colum.id
            
            #if DEBUG & DEBUG_SQL
            std::cout<<"Bdd::save(): "<<str_q<<" VALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);

            for(unsigned int i=0;i<size;++i)
            {
                #if DEBUG & DEBUG_SQL
                std::cout<<","<<*attrs[i];
                #endif
                attrs[i]->set(q,i+1);
                attrs[i]->modify = false;
            }

            #if DEBUG & DEBUG_SQL
            std::cout<<")"<<std::endl;
            #endif

            executeQuery(q);
            delete &q;
        }
        return true;
    };

    bool Bdd::del(const std::string& table,const int& pk)
    {
        std::string str_q = "DELETE FROM "+escape_colum(table)+" WHERE ("+escape_colum("id")+"="+std::to_string(pk)+");";

        #if DEBUG & DEBUG_SQL
        std::cout<<"Bdd::del(): "<<str_q<<std::endl;
        #endif

        Query* q = prepareQuery(str_q);
        executeQuery(*q);
        delete  q;

        return true;
    };

    std::string Bdd::escape_colum(const std::string& str) const
    {
        return "'"+str+"'";
    }

    std::string Bdd::escape_value(const std::string& str) const
    {
        return "'"+str+"'";
    }

    std::string Bdd::escape_value(const std::string& filter,const std::string& value) const
    {
        if(filter == "contains")
        {
            return operators.at(filter)+escape_value("%"+value+"%");
        }
        else if(filter == "icontains")
        {
            return operators.at(filter)+escape_value("%"+value+"%");
        }
        /*else if(filter == "regex")
        {
        }
        else if(filter == "iregex")
        {
        }*/
        else if(filter == "startswith")
        {
            return operators.at(filter)+escape_value(value+"%");
        }
        else if(filter == "endswith" )
        {
            return operators.at(filter)+escape_value("%"+value);
        }
        else if(filter == "istartswith")
        {
            return operators.at(filter)+escape_value(value+"%");
        }
        else if(filter == "iendswith")
        {
            return operators.at(filter)+escape_value("%"+value);
        }
        else
        {
            return operators.at(filter)+escape_value(value);
        }
    }

    
};
//orm::Bdd* orm::Bdd::Default = 0;

/*data_types = {
  'AutoField':         'integer AUTO_INCREMENT',
  'BooleanField':      'bool',
  'CharField':         'varchar(%(max_length)s)',
  'CommaSeparatedIntegerField': 'varchar(%(max_length)s)',
  'DateField':         'date',
  'DateTimeField':     'datetime',
  'DecimalField':      'numeric(%(max_digits)s, %(decimal_places)s)',
  'FileField':         'varchar(%(max_length)s)',
  'FilePathField':     'varchar(%(max_length)s)',
  'FloatField':        'double precision',
  'IntegerField':      'integer',
  'BigIntegerField':   'bigint',
  'IPAddressField':    'char(15)',
  'GenericIPAddressField': 'char(39)',
  'NullBooleanField':  'bool',
  'OneToOneField':     'integer',
  'PositiveIntegerField': 'integer UNSIGNED',
  'PositiveSmallIntegerField': 'smallint UNSIGNED',
  'SlugField':         'varchar(%(max_length)s)',
  'SmallIntegerField': 'smallint',
  'TextField':         'longtext',
  'TimeField':         'time',
  }*/
