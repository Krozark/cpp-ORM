#ifndef ORM_CACHE_HPP
#define ORM_CACHE_HPP

#include <ORM/backends/Query.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace orm
{
    template<typename T> class SQLObject;
    template<typename T> class FKBase;

    /**
     * \brief Class to store object tha have already be query
     **/
    template<typename T>
    class Cache
    {
        public:
            /***
             * \brief Construct a Cache for T
             *
             * Note: T have to be a SQLObject
             **/
            Cache();

            /**
             * \brief Destructor
             **/
            ~Cache();

            //Cache(const Cache<T>&)=delete;
            //Cache<T>& operator=(const Cache<T>&)=delete;
            
            typedef std::shared_ptr<T> type_ptr; ///< Type of the stored object
            
            /**
             * \brief make query to get object if not in cache
             *
             * \param pk PK of the object
             * \param max_depth Maximum depth of construction
             *
             * \return a shared_ptr to tho object stored in cache
             **/
            type_ptr& getOrCreate(const unsigned int& pk,int max_depth);

            /**
             * \brief construct object from query if pk not in cache
             *
             * \param pk PK of the object
             * \param query Query to use for construction
             * \param index colum in the query to start
             * \param max_depth Maximum depth of construction
             *
             * \return a shared_ptr to tho object stored in cache
             **/
            type_ptr& getOrCreate(const unsigned int& pk,const Query& query,int& prefix,int max_depth);

            /**
             * \brief construct object from query if not in cache after extracting pk from query
             *
             * \param query Query to use for construction
             * \param max_depth Maximum depth of construction
             *
             * \return a shared_ptr to tho object stored in cache
             **/
            type_ptr& getOrCreate(const Query& query,int max_depth);

            /**
             * \brief Print the cache content
             **/
            void __print__();

        private:
            friend class SQLObject<T>;
            friend class FKBase<T>;

            /**
             * \brief Add a object in the cache
             *
             * \param obj Object to add
             *
             * \return the shared_ptr of the stored object
             **/
            type_ptr& add(T& obj);

            /**
             * \brief Add a object in the cache
             *
             * \param obj Object to add
             *
             * \return the shared_ptr of the stored object
             **/
            type_ptr& add(type_ptr& obj);

            std::unordered_map<int,type_ptr> map; ///< store all the objects

            /**
             * \brief if tmp->pk in cache, return cache[pk] and delete tmp, else make tmp as type_ptr
             *
             * \return a shared_ptr to tho object stored in cache
             **/
            type_ptr& getOrCreate(T* tmp);

            /**
             * \brief delete object of specified pk
             **/
            void del(const unsigned int& pk);
    };
}
#include <ORM/core/Cache.tpl>
#endif
