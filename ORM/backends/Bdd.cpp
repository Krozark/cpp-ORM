#include <stdio.h>

#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/Query.hpp>
#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/fields/private/VAttr.hpp>

namespace orm
{
    Bdd::Bdd(const std::string& username,const std::string& pass,const std::string& bdd,const std::string& serveur,const std::string& port) : s_username(username),
        s_password(pass),
        s_bdd_name(bdd),
        s_serveur(serveur),
        s_port(port)
    {
    };

    Bdd::~Bdd()
    {
    } 

    bool Bdd::save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs)
    {
        const int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "INSERT INTO "+escapeColum(table)+"("+attrs[0]->colum;

            for(unsigned int i=1;i<size;++i)
                str_q+=","+attrs[i]->colum;
            str_q+=") ";

            str_q+="VALUES ((?)";
            for(unsigned int i=1;i<size;++i)
                str_q+=",(?)";
            str_q+=");";
            
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<"\033[33m"<<str_q<<"\nVALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);

            for(unsigned int i=0;i<size;++i)
            {
                #if ORM_DEBUG & ORM_DEBUG_SQL
                std::cerr<<","<<*attrs[i];
                #endif
                attrs[i]->set(q,i+1);
                attrs[i]->modify = false;
            }
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<")"<<std::endl;
            #endif

            q.execute();
            delete &q;

            pk = getLastInsertPk();
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<" new PK: "<<pk<<"\033[00m"<<std::endl;
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
            std::string str_q = "UPDATE "+escapeColum(table)+" SET ";

            bool first(true);
            for(unsigned int i=1;i<size;++i)
            {
                if(attrs[i]->modify)
                {
                    if(not first)
                        str_q+=",";
                    first = false;
                    str_q+=attrs[i]->colum+"=(?)";
                }
            }

            str_q+=" WHERE "+escapeColum(table)+"."+escapeColum("id")+escapeValue("exact",std::to_string(pk))+";"; ///< \todo colum.id
            

            if(first) //NO MAJ NEDEED
            {
                #if ORM_DEBUG & ORM_DEBUG_SQL
                std::cerr<<"\033[36m"<<str_q<<"\nNo Update needed, exit\033[00m"<<std::endl;
                #endif

                return true;
            }

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<"\33[34m"<<str_q<<"\nVALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);
            
            int index=1;
            for(unsigned int i=0;i<size;++i)
            {
                if(attrs[i]->modify)
                {
                    #if ORM_DEBUG & ORM_DEBUG_SQL
                    attrs[i]->print_value(std::cerr)<<",";
                    #endif
                    attrs[i]->set(q,index++);
                    attrs[i]->modify = false;
                }
            }

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<")\33[00m"<<std::endl;
            #endif
            q.execute();
            delete &q;

        }
        return true;
    };

    bool Bdd::del(const std::string& table,const int& pk)
    {
        std::string str_q = "DELETE FROM "+escapeColum(table)+" WHERE ("+escapeColum(table)+"."+escapeColum("id")+escapeValue("exact",std::to_string(pk))+");";

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<"\033[31m"<<str_q<<"\033[00m"<<std::endl;
        #endif

        Query* q = prepareQuery(str_q);
        q->execute();
        delete  q;

        return true;
    };

    std::string Bdd::escapeColum(const std::string& str) const
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

    std::string Bdd::escapeValue(const std::string& str) const
    {
        //return "'"+str+"'";
        std::string res(str);
        //ReplaceStringInPlace(res,"'","\\'");
        return res;
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
