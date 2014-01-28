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

    bool Bdd::operator==(const Bdd& other) const
    {
        return (
                (s_bdd_name == s_bdd_name)
                and (s_serveur ==s_serveur)
                and (s_port == s_port)
                //and (s_username == other.s_username)
                //and (s_password === other.s_password)
                );
    }

    bool Bdd::save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs)
    {
        const unsigned int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "INSERT INTO "+escapeColumn(table)+"("+attrs[0]->column;

            for(unsigned int i=1;i<size;++i)
                str_q+=","+attrs[i]->column;
            str_q+=") ";

            str_q+="VALUES ((?)";
            for(unsigned int i=1;i<size;++i)
                str_q+=",(?)";
            str_q+=");";
            
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<BLEU<<"[SQL:insert] "<<str_q<<"\nVALUES = (";
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
            q.next();
            delete &q;

            pk = getLastInsertPk();
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<" new PK: "<<pk<<BLANC<<std::endl;
            #endif

            return true;

        }
        return -1;
    };

    bool Bdd::update(const std::string& table,const int& pk,const std::vector<VAttr*>& attrs)
    {
        const unsigned int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "UPDATE "+escapeColumn(table)+" SET ";

            bool first(true);
            for(unsigned int i=0;i<size;++i)
            {
                if(attrs[i]->modify)
                {
                    if(not first)
                        str_q+=",";
                    first = false;
                    str_q+=attrs[i]->column+"=(?)";
                }
            }

            str_q+=" WHERE "+escapeColumn(table)+"."+escapeColumn("id")+" = "+std::to_string(pk)+";"; ///< \todo column.id
            

            if(first) //NO MAJ NEDEED
            {
                #if ORM_DEBUG & ORM_DEBUG_SQL
                std::cerr<<BLEU2<<"[SQL:update] "<<str_q<<"\nNo Update needed, exit"<<BLANC<<std::endl;
                #endif

                return true;
            }

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<BLEU2<<"[SQL:update] "<<str_q<<"\nVALUES = (";
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
            std::cerr<<")"<<BLANC<<std::endl;
            #endif
            q.execute();
            q.next();
            delete &q;

        }
        return true;
    };

    bool Bdd::del(const std::string& table,const int& pk)
    {
        std::string str_q = "DELETE FROM "+escapeColumn(table)+" WHERE ("+escapeColumn(table)+"."+escapeColumn("id")+" = "+std::to_string(pk)+");";

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<COMMENTAIRE<<"[SQL:delete]"<<str_q<<BLANC<<std::endl;
        #endif

        Query* q = prepareQuery(str_q);
        q->execute();
        q->next();
        delete  q;

        return true;
    };

    std::string Bdd::escapeColumn(const std::string& str) const
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

    std::string Bdd::formatValue(const std::string& filter,std::string value) const
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
        else if(filter == "endswith" )
        {
            value = "%"+value;
        }
        else if(filter == "istartswith")
        {
            value = value+"%";
        }
        else if(filter == "iendswith")
        {
            value = "%"+value;
        }

        return value;
    }

    std::string Bdd::formatPreparedValue(const std::string& filter) const
    {
        const std::string& op = operators.at(filter);
        char buffer[op.size() + 3];
        sprintf(buffer,op.c_str(),"(?)");

        return std::string(buffer);
    }
};
//orm::Bdd* orm::Bdd::Default = 0;

