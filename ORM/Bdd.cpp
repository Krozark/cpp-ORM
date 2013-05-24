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

    const std::string& Bdd::operator[](const std::string& key)
    {
        return operators[key];
    };

    /*bool Bdd::save(SQLObjectBase* obj)
    {
    };

    bool Bdd::update(SQLObjectBase* obj)
    {
    };*/

    bool Bdd::save(const std::string& table,const unsigned int pk,const std::vector<VAttr*>& attrs)
    {
        return true;
    };

    bool Bdd::update(const std::string& table,const unsigned int pk,const std::vector<VAttr*>& attrs)
    {
        const int size = attrs.size();
        if(size > 0)
        {
            Query& q = *prepareQuery("UPDATE "+table
                            +" SET ");
            q.query+=attrs[0]->colum+"=(?)";
            for(unsigned int i=1;i<size;++i)
            {
                q.query+=","+attrs[i]->colum+"=(?)";
            }
            q.query+=" WHERE id="+std::to_string(pk);

            for(unsigned int i=0;i<size;++i)
                attrs[0]->set(q,i);
            executeQuery(q);
            delete &q;
        }
        return true;
    };

    
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
