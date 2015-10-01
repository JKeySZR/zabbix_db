<?php

/**
 * @file
 * Definition of views_handler_filter_node_type.
 */

/**
 * Filter by node type.
 *
 * @ingroup views_filter_handlers
 */
class zabbix_db_handler_filter_hosts_status extends views_handler_filter_in_operator {

  //From ZABBIX common.h see ITEMS_TYPE
  /* item states 
    #define ITEM_STATE_NORMAL               0
    #define ITEM_STATE_NOTSUPPORTED         1
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Zabbix hosts status');
      $options = array();
      $options = array(
        '0' => 'MONITORED',
        '1' => 'NOT_MONITORED',
        '2' => 'UNREACHABLE',
        '3' => 'Template',
        '4' => 'DELETED',
        '5' => 'PROXY_ACTIVE',
        '6' => 'PROXY_PASSIVE',
      );
      asort($options);
      $this->value_options = $options;
    }
  }

}
