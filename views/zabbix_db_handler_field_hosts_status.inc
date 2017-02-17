<?php

/**
 * @file
 * Definition of views_handler_field_node_type.
 */

/**
 * Field handler to translate a node type into its readable form.
 *
 * @ingroup views_field_handlers
 */
class zabbix_db_handler_field_hosts_status extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    $dbg = 1;
    // Всегда добавляем hostID поля к запросам
    //$this->additional_fields['hostid'] = array('table' => 'hosts', 'field' => 'hostid');
  }

  /**
   * Render node type as human readable name, unless using machine_name option.
   */
  // Status is int value :
  // 0 - activate, 1 - deactivate, 3 -template, 5 - proxy
//  #define HOST_STATUS_MONITORED           0
//  #define HOST_STATUS_NOT_MONITORED       1
//  #define HOST_STATUS_UNREACHABLE       2
//  #define HOST_STATUS_TEMPLATE            3
//  #define HOST_STATUS_DELETED           4
//  #define HOST_STATUS_PROXY_ACTIVE        5
//  #define HOST_STATUS_PROXY_PASSIVE       6

  function render($values) {
    $dbg = 1;
    $options = array(
      '0' => 'MONITORED',
      '1' => 'NOT_MONITORED',
      '2' => 'UNREACHABLE',
      '3' => 'Template',
      '4' => 'DELETED',
      '5' => 'PROXY_ACTIVE',
      '6' => 'PROXY_PASSIVE',
    );    
    $value = $options[$values->hosts_status];    
    return $value;
  }

}
