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
class zabbix_db_handler_filter_groups_name extends views_handler_filter_in_operator {
  

  function get_value_options() {
    $connect_name = variable_get('zabbix_db_connect', false);
    if ($connect_name) {
      $this->value_title = t('Zabbix groups name filter');
      $options = array();
      
      db_set_active($connect_name);
      $query = db_select('groups','grp')
          ->fields('grp', array('groupid', 'name'));
      $result = $query->execute()->fetchAll();
      db_set_active('default');
      $dbg = 1;
      foreach ($result as $row) {
        $options[$row->groupid] = $row->name;
      }
      asort($options);
      $this->value_options = $options;
    }
  }

}
