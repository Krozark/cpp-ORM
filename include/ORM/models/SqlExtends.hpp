#ifndef ORM_SQLEXTENDS_HPP
#define ORM_SQLEXTENDS_HPP

#include <ORM/models/SqlObject.hpp>
//#include <ORM/fields/FK.tpl>

namespace orm
{
    template <typename T, typename BASE>
    class SqlExtends : public SqlObject<T>, public SqlObject<BASE>
    {
        public:
            SqlExtends();
            virtual ~SqlExtends();

            virtual bool save(bool recursive=false,DB& db = *SqlObject<T>::default_connection) override final;

            //virtual bool del(bool recursive, DB& db) override final;


        protected:

        private:
            //FK<BASE,false> _base_fk;
            /*
            template<typename U> friend class Register;

            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            virtual const std::string& getTable() const override final;
            */
    };
}

#include <ORM/models/SqlExtends.tpl>
#endif
