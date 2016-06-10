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
            using pointer_array = typename SqlObject<T>::pointer_array;
            using pointer = typename SqlObject<T>::pointer;

            SqlExtends();
            virtual ~SqlExtends();

            virtual bool save(bool recursive=false,DB& db = staticGetDefaultDataBase()) override;

            virtual bool del(bool recursive=false, DB& db = staticGetDefaultDataBase()) override final;

            using SqlObject<T>::create;
            using SqlObject<T>::all;
            using SqlObject<T>::query;

            friend std::ostream& operator<<(std::ostream& output,const SqlExtends<T,BASE>& self)
            {
                return output<<static_cast<const SqlObject<T>&>(self);
            }

            static DB& staticGetDefaultDataBase();

            static const std::string ORM_MAKE_NAME(base_obj_ptr);

        protected:
            friend class Query;
            template<typename U> friend class SqlObject;
            template<typename U,typename V> friend class ManyToMany;
            template<typename RELATED,typename U> friend class Filter;

            const static std::string& _table; ///< the table name
            static Cache<T>& _cache;

            //virtual bool _loadFromDB(const Query& query,int max_depth);
            virtual bool _loadFromDB(const Query& query,int& prefix,int max_depth) override;

        private:
            FK<BASE,false> _baseFk;

            int _saveNb; //save() hack

            /*
            template<typename U> friend class Register;

            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            virtual const std::string& getTable() const override final;
            */

            template<typename ... Args>
            static pointer _createForRegister(Args&& ... args);
    };
}

#include <ORM/models/SqlExtends.tpl>
#endif
