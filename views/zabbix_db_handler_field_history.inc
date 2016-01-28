<?php

/**
 * @file
 * Contains the basic 'node' field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a node.
 * Definition terms:
 * - link_to_node default: Should this field have the checkbox "link to node" enabled by default.
 *
 * @ingroup views_field_handlers
 */
class zabbix_db_handler_field_history extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    
    $dbg = 1;
    // Всегда добавляем hostID поля к запросам
    $this->additional_fields['hostid'] = array('table' => 'hosts', 'field' => 'hostid');
    
  }

  function query() {
    $this->ensure_my_table();
    // Add the field.
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
    $this->field_alias = $this->query->add_field($this->table_alias, $this->real_field, NULL, $params);

    $this->add_additional_fields();
    $dbg =1;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->sanitize_value($value);
  }
  
}
