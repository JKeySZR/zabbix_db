Installation:
------------
1. Download and unpack the ZABBIX_DB module directory in your modules folder
   (this will usually be "sites/all/modules/").
2. Go to "Administer" -> "Configuration" -> "System" -> "Zabbix" and setup connection name.


Configuration:
-------------


You need add connect paramet in settings.php
$databases = array(
   
... some like parametr 

  'zabbix' =>
  array(
    'default' =>
    array(
      'database' => 'zbx_db_dbname',
      'username' => 'zbx_db_username',
      'password' => 'zbx_db_password',
      'host' => 'localhost',
      'port' => '',
      'driver' => 'mysql',
      'prefix' => '',
    ),
  ), 
); 

CONTACT
-------------
Current maintainers:
* Mihail Bocharov (jkey) - https://www.drupal.org/u/jkey
https://www.drupal.org/user/1022534
