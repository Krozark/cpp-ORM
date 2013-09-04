#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

//orm::
#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/fields/VAttr.hpp>
#include <ORM/core/Cache.hpp>
#include <ORM/core/macros.hpp>
//std::
#include <memory>


namespace orm
{
    class Bdd;
    class Query;
    class Filter;
    class VAttr;
    class VFK;
    template<typename T> class FK;
    template<typename T> class SQLObject;
    
    /* class to register colum name as static (Hack) */
    template<typename T>
    class Register
    {
        public:
            Register()
            {
                static T tmp;
                for(VAttr* attr: tmp.attrs)
                    SQLObject<T>::colum_attrs.emplace_back(attr);
                for(VFK* fk: tmp.fks)
                    SQLObject<T>::colum_fks.emplace_back(fk);

            }
    };

    template<typename T>
    class SQLObject : public SQLObjectBase
    {
        public:
            SQLObject();

            SQLObject(const SQLObject&) = delete;
            SQLObject& operator=(const SQLObject&) = delete;
            
            static T* createFromBdd(const Query& query);
            static std::shared_ptr<T>& get(const unsigned int& id);
            static std::list<std::shared_ptr<T>> all();
            
            template<typename U>
            static std::list<std::shared_ptr<T> > filter(const std::string& colum,const std::string& ope,const U& value);
            static std::list<std::shared_ptr<T> > filter(const Filter& filter);
            static std::list<std::shared_ptr<T> > filter(const std::list<Filter>& filters);

            virtual bool save(bool recursive=false,bool force=false);
            virtual bool del();

            static  Bdd* bdd_used;

            static Cache<T> cache;

        protected:
            const static std::string table;
            virtual const std::string& getTable()const {return table;};
            virtual const Bdd* getBdd()const{return bdd_used;};

            virtual void _nameAttrs(std::string& q_str)const;
            virtual void _nameTables(std::string& q_str)const;
            virtual void _nameFks(std::string& q_str)const;

        private:
            template<typename U> friend class Cache;
            template<typename U> friend class Register;
            template<typename U,typename V> friend class ManyToMany;
            friend class FK<T>;
            friend class Query;

            static Register<T> _register;
            static std::vector<const VAttr*> colum_attrs;
            static std::vector<const VFK*> colum_fks;

            static void nameAttrs(std::string& q_str,bool recur=true);
            static void nameTables(std::string& q_str,bool recur=true);
            static void nameFks(std::string& q_str);

            static T* _get_ptr(const unsigned int id);
    };
};

#include <ORM/models/SQLObject.tpl>
#endif
