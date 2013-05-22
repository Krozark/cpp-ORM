#include "Bdd.hpp"
#include "Query.hpp"

namespace orm
{
    Bdd::Bdd(const std::string& username,const std::string& pass,const std::string& bdd,const std::string& serveur,const std::string& port) : s_username(username),
        s_password(pass),
        s_bdd_name(bdd),
        s_serveur(serveur),
        s_port(port)
    {
    };

    /*bool Bdd::executeQuery(Query& query)
    {
    };*/

};
orm::Bdd* orm::Bdd::Default = 0;

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
