#ifndef ORM_SQLEXTENDS_HPP
#define ORM_SQLEXTENDS_HPP

#include <ORM/models/SqlObject.hpp>
#include <ORM/fields/FK.hpp>

namespace orm
{
    template <typename T, typename BASE>
    class SqlExtends : public SqlObject<T>, public BASE
    {
        public:
            using result_type = typename SqlObject<T>::result_type;
            using type_ptr = typename SqlObject<T>::type_ptr;

            SqlExtends();
            virtual ~SqlExtends();

            virtual bool save(bool recursive=false,DB& db = *SqlObject<T>::default_connection) override;

            //virtual bool del(bool recursive, DB& db) override final;

            using SqlObject<T>::create;
            using SqlObject<T>::all;
            
            //static result_type all(DB& db = *SqlObject<T>::default_connection,int max_depth=ORM_DEFAULT_MAX_DEPTH);
            

            friend std::ostream& operator<<(std::ostream& output,const SqlExtends& self)
            {
                return output<<static_cast<const SqlObject<T>&>(self);
            }

            const std::string ORM_MAKE_NAME(base_ptr_pk) = "_base_ptr_pk";

        protected:
            template<typename U> friend class SqlObject;

            virtual bool loadFromDB(const Query& query,int max_depth);
            virtual bool loadFromDB(const Query& query,int& prefix,int max_depth);

        private:
            FK<BASE,false> _base_fk;

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
