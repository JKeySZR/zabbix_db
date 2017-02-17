<?php

/**
 * @file
 * Views support.
 */
/**
 *  This hook should be placed in MODULENAME.views.inc and it will be auto-loaded. 
 *  https://api.drupal.org/api/views/views.api.php/function/hook_views_data/7
 */

/**
 * Implements hook_views_data().
 */
function zabbix_db_views_data() {
  $data = array();
  $connect_name = variable_get('zabbix_db_connect', false);

//@FIXIT If not set variable, need nalyze this moment
  if (!$connect_name) {
    // do something
    return $data;
  }


  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.   
  $data['hosts']['table']['group'] = t('Zabbix host');
  $data['hosts']['table']['base'] = array(
    'database' => $connect_name,
    'field' => 'hostid',
    'title' => t('Zabbix DB'),
    'defaults' => array(
      'field' => 'host',
    ),
  );
  _zabbix_db_tbl_hosts($data);

  // Если мы хотим , строить статусные панели для пользователей, то нам необходимы данные из этой таблицы
  // т.к. она не привяза ни к чему явно, придется делать ее отдельно. ?? 
  $data['triggers']['table']['group'] = t('Zabbix triggers');
  $data['triggers']['table']['base'] = array(
    'database' => $connect_name,
    'field' => 'triggerid',
    'title' => t('Zabbix triggers'),
    'defaults' => array(
      'field' => 'triggerid',
    ),
  );
  _zabbix_db_tbl_triggers($data);



  $data['items']['table']['group'] = t('Zabbix items');
  _zabbix_db_tbl_items($data);

  $data['groups']['table']['group'] = t('Zabbix groups');
  _zabbix_db_tbl_groups($data);

  $data['hosts_groups']['table']['group'] = t('Zabbix groups');
  _zabbix_db_tbl_hosts_groups($data);



  $data['interface']['table']['group'] = t('Zabbix interface');
  _zabbix_db_tbl_interface($data);

  //$data['zbbx_history']['table']['group'] = t('Zabbix data');
  //$data['zbbx_history']['table']['base']['real_table'] = 'history';
  //$data['zbbx_history']['table']['base']['title'] = 'ZBX history';
//  $data['history']['table']['base'] = array(
//    'database' => $connect_name,
//    'field' => 'itemid',
//    'title' => t('Zabbix DATA'),
//  );
  _zabbix_db_tbl_history($data);

//  _zabbix_db_tbl_history_text($data);
  //$data['users']['table']['group'] = t('Zabbix users');
//  $data['hosts']['disable_until'] = array(
//    'title' => 'Disable date',
//    'help' => 'The date until disable',
//    'field' => array(
//      'handler' => 'views_handler_field_date'
//    ),
//  );

  $dbg = 0;

  return $data;
}

/**
 *  Prepare table stucture fo table hosts
 * @param type $data
 * 
 */
function _zabbix_db_tbl_hosts(&$data) {

  $data['hosts']['hostid'] = array(
    'title' => 'HostID',
    'help' => 'Unique ID associated to each zabbix host',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
      // Define a relationship to the {node} table, so example_table views can
      // add a relationship to nodes. If you want to define a relationship the
      // other direction, use hook_views_data_alter(), or use the 'implicit' join
      // method described above.
//    'relationship' => array(
//      'base' => 'items', // The name of the table to join with.
//      'base field' => 'hostid', // The name of the field on the joined table.
//      // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
//      'handler' => 'views_handler_relationship',
//      'label' => t('Zabbix items relationship'),
//      'title' => t('Zabbix table items'),
//      'help' => t('More information on zabbix items this relationship'),
//    ),
  );

  $data['hosts']['host'] = array(
    'title' => 'Host name',
    'help' => 'Base host name ',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['hosts']['name'] = array(
    'title' => 'Visible host name',
    'help' => 'Visible host name in zabbix',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  // Status is int value :
  // 0 - activate, 1 - deactivate, 3 -template, 5 - proxy
  $data['hosts']['status'] = array(
    'title' => 'Status host name',
    'help' => 'Type of host: 0 - activate, 1 - deactivate, 3 -template, 5 - proxy',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts_status'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'zabbix_db_handler_filter_hosts_status'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );

  $data['hosts']['error'] = array(
    'title' => 'Error',
    'help' => 'Error message for host',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
  );
}

/**
 *  Prepare table stucture fo table hosts
 * @param type $data
 * 
 */
function _zabbix_db_tbl_hosts_groups(&$data) {
  // This table references the {node} table. The declaration below creates an
  // 'implicit' relationship to the node table, so that when 'node' is the base
  // table, the fields are automatically available.
  $data['hosts_groups']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'hosts' => array(
      'left_field' => 'hostid',
      'field' => 'hostid',
    ),
    'groups' => array(
      'left_field' => 'groupid',
      'field' => 'groupid',
    ),
  );


  $data['hosts_groups']['groupid'] = array(
    'title' => 'GroupID',
    'help' => 'Unique ID associated to each group',
    // Define a relationship to the {node} table, so example_table views can
    // add a relationship to nodes. If you want to define a relationship the
    // other direction, use hook_views_data_alter(), or use the 'implicit' join
    // method described above.
    'relationship' => array(
      'base' => 'groups', // The name of the table to join with.
      'base field' => 'groupid', // The name of the field on the joined table.
      // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
      'handler' => 'views_handler_relationship',
      'label' => 'ZBXGRP',
      'title' => 'Zabbix groups',
      'help' => 'Add new field in sections groups',
    ),
  );
}

/**
 *  Prepare table stucture fo table items
 * @param type $data
 * 
 */
function _zabbix_db_tbl_items(&$data) {

  // This table references the {node} table. The declaration below creates an
  // 'implicit' relationship to the node table, so that when 'node' is the base
  // table, the fields are automatically available.
  $data['items']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'hosts' => array(
      'left_field' => 'hostid',
      'field' => 'hostid',
    ),
    'interface' => array(
      'left_field' => 'interfaceid',
      'field' => 'interfaceid',
    ),
  );

  $data['items']['itemid'] = array(
    'title' => 'ID',
    'help' => 'Unique ID associated to each zabbix host items',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

//  $data['items']['templateid'] = array(
//    'title' => 'TemplateID',
//    'help' => 'ID of templates this items (Hostid)',
//    'real_field' => 'templateid',
//    'field' => array(
//      'handler' => 'zabbix_db_handler_field_templates',
//      'click sortable' => TRUE,
//    ),
////        'sort' => array(
////          'handler' => 'views_handler_sort'
////        ),
////        'filter' => array(
////          'handler' => 'views_handler_filter'
////        ),
////        'argument' => array(
////          'handler' => 'views_handler_argument'
////        ),
////    'relationship' => array(
////      'base' => 'hosts', // The name of the table to join with.
////      'base field' => 'hostid', // The name of the field on the joined table.
////      // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
////      'handler' => 'views_handler_relationship',
////      'label' => 'LABEL GA',
////      'title' => 'ADD ITEMS',
////      'help' => 'BABA HELP MSG',
////    ),
//  );

  /*
    $data['items']['interfaceid'] = array(
    'title' => 'Interface ID',
    'help' => 'Interface ID associated to items',
    //    'field' => array(
    //      'handler' => 'zabbix_db_handler_field_hosts'
    //    ),
    //    'sort' => array(
    //      'handler' => 'views_handler_sort'
    //    ),
    //    'filter' => array(
    //      'handler' => 'views_handler_filter'
    //    ),
    //    'argument' => array(
    //      'handler' => 'views_handler_argument'
    //    ),
    // Define a relationship to the {node} table, so example_table views can
    // add a relationship to nodes. If you want to define a relationship the
    // other direction, use hook_views_data_alter(), or use the 'implicit' join
    // method described above.
    'relationship' => array(
    'base' => 'interface', // The name of the table to join with.
    'base field' => 'interfaceid', // The name of the field on the joined table.
    // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
    'handler' => 'views_handler_relationship',
    'label' => 'Zabbix tbl_interface',
    'title' => 'Zabbix add table iterface',
    'help' => 'Zabbix tbl interface to tbl items relationship',
    ),
    );
   */

  $data['items']['name'] = array(
    'title' => 'Name',
    'help' => 'Name from item table',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['type'] = array(
    'title' => 'Type',
    'help' => 'Type of item from item table',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_items_type'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'zabbix_db_handler_filter_items_type'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );



  $data['items']['key_'] = array(
    'title' => 'Key',
    'help' => 'Items key',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['delay'] = array(
    'title' => 'Interval',
    'help' => 'Update interval (in sec)',
    'field' => array(
      'handler' => 'views_handler_field_numeric'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['history'] = array(
    'title' => 'History',
    'help' => 'History storage period (in days)',
    'field' => array(
      'handler' => 'views_handler_field_numeric'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );

  $data['items']['trends'] = array(
    'title' => 'Trends',
    'help' => 'Trend storage period (in days)',
    'field' => array(
      'handler' => 'views_handler_field_numeric'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );

  $data['items']['status'] = array(
    'title' => 'Enabled/Disable',
    'help' => 'Enabled or disabled items',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'zabbix_db_handler_filter_boolean_operator',
      // Note that you can override the field-wide label:
      'label' => t('Items status'),
      // This setting is used by the boolean filter handler, as possible option.
      'type' => 'enabled-disabled',
      // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statment.
      'use equal' => TRUE,
    ),
  );

  $data['items']['value_type'] = array(
    'title' => 'Value type',
    'help' => 'Value type ',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_items_value_type'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'zabbix_db_handler_filter_items_value_type'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['trapper_hosts'] = array(
    'title' => 'Trapper hosts',
    'help' => 'Trapper hosts',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['units'] = array(
    'title' => 'Units',
    'help' => 'Items units',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['multiplier'] = array(
    'title' => 'Multiplier',
    'help' => 'Use custom multiplier',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['delta'] = array(
    'title' => 'Delta',
    'help' => 'Items delta',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['snmp_community'] = array(
    'title' => 'SNMP community',
    'help' => 'Items SNMP value of community',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['snmp_oid'] = array(
    'title' => 'SNMP oid',
    'help' => 'Items SNMP oid',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['items']['snmpv3_securityname'] = array(
    'title' => 'SNMP v3 securityname',
    'help' => 'Items SNMP credentional',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['items']['snmpv3_securitylevel'] = array(
    'title' => 'SNMP v3 securitylevel',
    'help' => 'Items SNMP credentional',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['snmpv3_authpassphrase'] = array(
    'title' => 'SNMP v3 authpassphrase',
    'help' => 'Items SNMP credentional authpassphrase',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['items']['snmpv3_privpassphrase'] = array(
    'title' => 'SNMP v3 privpassphrase',
    'help' => 'Items SNMP credentional privpassphrase',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['items']['error'] = array(
    'title' => 'Error',
    'help' => 'Items error field',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
  );

  $data['items']['lastlogsize'] = array(
    'title' => 'Last log size',
    'help' => 'Last size of log file',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['items']['state'] = array(
    'title' => 'State',
    'help' => 'Condition of items normal or not supported',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_items_state'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'zabbix_db_handler_filter_items_state'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );
}

/**
 *  Prepare table stucture fo table hosts
 * @param type $data
 * 
 */
function _zabbix_db_tbl_groups(&$data) {

  // This table references the {node} table. The declaration below creates an
  // 'implicit' relationship to the node table, so that when 'node' is the base
  // table, the fields are automatically available.
//  $data['groups']['table']['join'] = array(
//    // Index this array by the table name to which this table refers.
//    // 'left_field' is the primary key in the referenced table.
//    // 'field' is the foreign key in this table.
//    'hosts_groups' => array(
//      'left_field' => 'groupid',
//      'field' => 'groupid',
//    ),
//  );


  $data['groups']['groupid'] = array(
    'title' => 'GroupID',
    'help' => 'Internal ID of tbl groups',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument'
    ),
  );

  $data['groups']['name'] = array(
    'title' => 'Name',
    'help' => 'Name of groups',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'zabbix_db_handler_filter_groups_name'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['groups']['internal'] = array(
    'title' => 'Internal',
    'help' => 'Internal',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );

  $data['groups']['flags'] = array(
    'title' => 'Flags',
    'help' => 'Flags ...',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );
}

/**
 *  Prepare table stucture fo table hosts
 * @param type $data
 * 
 */
function _zabbix_db_tbl_triggers(&$data) {

  $data['triggers']['triggerid'] = array(
    'title' => 'Trigger - ID',
    'help' => 'Internal ID of trigger',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );

  $data['triggers']['expression'] = array(
    'title' => 'Trigger - expression',
    'help' => 'Trigger',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['triggers']['description'] = array(
    'title' => 'Trigger - description',
    'help' => 'Trigger description',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['triggers']['comments'] = array(
    'title' => 'Trigger - comments',
    'help' => 'Trigger comments',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['triggers']['url'] = array(
    'title' => 'Trigger - URL',
    'help' => 'Trigger URL',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['triggers']['value'] = array(
    'title' => 'Trigger - value',
    'help' => 'Triggers Values',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );

  $data['triggers']['status'] = array(
    'title' => 'Triggers - Status',
    'help' => 'Enabled or disavled triggers',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      // Note that you can override the field-wide label:
      'label' => t('Triggers status'),
      // This setting is used by the boolean filter handler, as possible option.
      'type' => 'enabled-disabled',
      // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statment.
      'use equal' => TRUE,
    ),
  );

  // Example timestamp field.
  $data['triggers']['lastchange'] = array(
    'title' => 'Triggers lastchange',
    'help' => 'Triggers timestamp field',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
}

/**
 *  Prepare table stucture fo table items
 * @param type $data
 * 
 */
function _zabbix_db_tbl_history(&$data) {

  // Связываем с базовой таблицей host , через промежуточную таблицу items
  $data['history']['table']['join']['hosts'] = array(
    'left_table' => 'items',
    'left_field' => 'itemid',
    'field' => 'itemid',
  );

  // uid field
  $data['history']['itemid'] = array(
    'title' => 'ItemID',
    'help' => 'The ...',
    'relationship' => array(
      'base' => 'items', // The name of the table to join with.
      'base field' => 'itemsid', // The name of the field on the joined table.
      // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
      'handler' => 'views_handler_relationship',
      'label' => 'ZBXHIST',
      'title' => 'Zabbix History ',
      'help' => 'To get items name you need use relations ITEMS',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'group' => 'Zabbix data: history',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'group' => 'Zabbix data: history',
    ),
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts',
      'group' => 'Zabbix data: history',
    ),
  );

  $data['history']['clock'] = array(
    'title' => 'Clock',
    'help' => 'Time of get data',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
      'group' => 'Zabbix data: history',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
      'group' => 'Zabbix data: history',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'group' => 'Zabbix data: history',
    ),
  );

  $data['history']['value'] = array(
    'title' => 'Value - Double',
    'help' => ' Important!!! You must select filter in the fields  history.ItemID and history.clock for using (working)  index in query (select) for  fast realization.',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_history',
      'group' => 'Zabbix data: history',
    ),
//    'sort' => array(
//      'handler' => 'views_handler_sort',
//      'group' => 'Zabbix data: history',
//    ),
//    'filter' => array(
//      'handler' => 'views_handler_filter_numeric',
//      'group' => 'Zabbix data: history',
//    ),
//    'argument' => array(
//      'handler' => 'views_handler_argument_numeric',
//      'group' => 'Zabbix data: history',
//    ),
  );
}

function _zabbix_db_tbl_history_text(&$data) {

  // This table references the {node} table. The declaration below creates an
  // 'implicit' relationship to the node table, so that when 'node' is the base
  // table, the fields are automatically available.
//  $data['history']['table']['join']['hosts'] = array(
//      'left_table' => 'items',
//      'left_field' => 'itemid',
//      'field' => 'itemid',    
//  );
  // uid field
  $data['history_text']['itemid'] = array(
    'title' => 'ItemID',
    'help' => 'The ...',
    'relationship' => array(
      'base' => 'items', // The name of the table to join with.
      'base field' => 'itemsid', // The name of the field on the joined table.
      // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
      'handler' => 'views_handler_relationship',
      'label' => 'ZBXHIST_TEXT',
      'title' => 'Zabbix History TEXT ',
      'help' => 'To get items name you need use relations ITEMS',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'group' => 'Zabbix data text:',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'group' => 'Zabbix data text:',
    ),
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts',
      'group' => 'Zabbix data text:',
    ),
  );

  $data['history_text']['clock'] = array(
    'title' => 'Clock',
    'help' => 'Time of get data',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
      'group' => 'Zabbix data text:',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
      'group' => 'Zabbix data text:',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'group' => 'Zabbix data text:',
    ),
  );

  $data['history_text']['value'] = array(
    'title' => 'Value',
    'help' => 'Values of numeric data whith mantis',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts',
      'group' => 'Zabbix data text:',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
      'group' => 'Zabbix data text:',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'group' => 'Zabbix data text:',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'group' => 'Zabbix data text:',
    ),
  );
}

/**
 *  Prepare table stucture fo table interface
 * @param type $data
 * 
 */
function _zabbix_db_tbl_interface(&$data) {

  // This table references the {node} table. The declaration below creates an
  // 'implicit' relationship to the node table, so that when 'node' is the base
  // table, the fields are automatically available.
  $data['interface']['table']['join'] = array(
    // Index this array by the table name to which this table refers.  
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.    
    'hosts' => array(
      'left_field' => 'hostid',
      'field' => 'hostid',
    //'type' => 'INNER',
    ),
  );

  $data['interface']['interfaceid'] = array(
    'title' => 'ID',
    'help' => 'Interface primary ID',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );

  /*
    $data['interface']['hostid'] = array(
    'title' => 'HostID',
    'help' => 'Interface HostID',
    'relationship' => array(
    'title' => 'Zabbix interface',
    'help' => 'Add field from Zabbix tbl interface',
    'handler' => 'views_handler_relationship',
    'base' => 'hosts', // The name of the table to join with.
    //'base field' => 'hostid', // The name of the field on the joined table.
    'field' => 'hostid', // The name of the field on the joined table.
    'label' => 'ZBXINT',
    ),
    );
   */

  $data['interface']['ip'] = array(
    'title' => 'IP',
    'help' => 'Interface IP',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['interface']['dns'] = array(
    'title' => 'DNS',
    'help' => 'Interface DNS',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['interface']['port'] = array(
    'title' => 'Port',
    'help' => 'Interface port',
    'field' => array(
      'handler' => 'zabbix_db_handler_field_hosts'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string'
    ),
  );

  $data['interface']['main'] = array(
    'title' => 'IsMain',
    'help' => 'Interface - general or not interface',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      // Note that you can override the field-wide label:
      'label' => t('Interface general?'),
      // This setting is used by the boolean filter handler, as possible option.
      'type' => 'yes-no',
      // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statment.
      'use equal' => TRUE,
    ),
  );

  $data['interface']['type'] = array(
    'title' => 'Type',
    'help' => 'Interface type: zabbix agent, jmx, snnmp, IMPI',
    'field' => array(
      'handler' => 'views_handler_field_numeric'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric'
    ),
  );
}

# Do your secondary query in hook_views_pre_render()

function zabbix_db_views_pre_render(&$view) {
  if ($view->name == 'test_zabbix') {
    # Create custom property on the views object to store our external data
    $view->your_special_property = array();

    # Get the node id's of the views result set
    $nids = array();
    foreach ($view->result as $r) {
      $nids[] = $r->nid;
    }

    # Switch to secondary database
    db_set_active('zabbix');

    # Query for secondary database data utilizing the nids you gathered from the views result set
    $query = db_select('hosts', 'hst');
    # Add whatever query stuff you need here like the following:
    $query->fields('hst', array('host', 'hostid'));

    $results = $query->execute();
    foreach ($results as $result) {
      $view->your_special_property[$result->hostid] = $result->host;
    }
    # Switch back to the default database
    db_set_active('default');
  }
}

/**
 * Implementation of hook_views_data_alter().
 */
function zabbix_db_data_alter(&$data) {
  foreach ($data as $table => $config) {
    foreach ($config as $item => $item_config) {
      if (isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_date') {
        $data[$table][$item]['field']['handler'] = 'views_handler_field_example_date';
      }
    }
  }

  return $data;
}

/**
 * Implementation of hook_views_query_alter
 * @param type $view
 * @param type $query 
 */
function zabbix_db_views_query_alter(&$view, &$query) {
  $dbg = 1;
  foreach ($query->tables as $key => $val) {
    $i = 1;
  }
  //simple example: change the order of the master display
  //if you want to do it only  on a certain display add something 
  // like  "&&$view->current_display == 'panel_page_1'"
//  if ($view->name == 'VIEWNAME') {
//
//    //to find out what the fieldname ist: use devel and add your desired field as 
//    //first filter ( =>orderby[0]). install devel and uncomment the next line
//    //dpm($view->query->orderby)
//
//    $view->query->orderby[0]['field'] = "CASE FIELD_NAME WHEN 'apple' THEN 1 WHEN 'zebra' THEN 2 WHEN 'banna' THEN 3 ELSE 4 END";
//  }
}

/**
 * Implementation of hook_views_handlers().
 */
function zabbix_db_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'zabbix_db') . '/views',
    ),
    'handlers' => array(
      'views_handler_zabbix_db_date' => array(
        'parent' => 'views_handler',
      ),
    ),
  );
}
