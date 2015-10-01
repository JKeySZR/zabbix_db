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
class zabbix_db_handler_field_items_state extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    $dbg = 1;
    // Всегда добавляем hostID поля к запросам
    //$this->additional_fields['hostid'] = array('table' => 'hosts', 'field' => 'hostid');
  }

  /**
   * Render node type as human readable name, unless using machine_name option.
   */

  function render($values) {
    $dbg = 1;
    $options = array(
      '0' => 'Normal',
      '1' => 'Not supported',
    );    
    $value = $options[$values->items_state];    
    return $value;
  }

}
