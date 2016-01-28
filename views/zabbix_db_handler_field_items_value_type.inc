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
class zabbix_db_handler_field_items_value_type extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    $dbg = 1;
    // Всегда добавляем hostID поля к запросам
    //$this->additional_fields['hostid'] = array('table' => 'hosts', 'field' => 'hostid');
  }

  /**
   * Render node type as human readable name, unless using machine_name option.
   */
//  function render_name($data, $values) {
//    $dbg = 0;
//    $options = array(
//      '0' => 'Numeric (float)',
//      '1' => 'Charset',
//      '2' => 'LOG',
//      '3' => 'UINT64',
//      '4' => 'Text',
//    );
//
//    if ($this->options['machine_name'] != 1 && $data !== NULL && $data !== '') {
//      return t($this->sanitize_value(node_type_get_name($data)));
//    }
//    return $this->sanitize_value($data);
//  }

  function render($values) {
    $dbg = 1;
    $options = array(
      '0' => 'Numeric (float)',
      '1' => 'Charset',
      '2' => 'LOG',
      '3' => 'UINT64',
      '4' => 'Text',
    );    
    $value = $options[$values->items_value_type];    
    return $value;
  }

}
