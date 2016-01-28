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
class zabbix_db_handler_filter_items_value_type extends views_handler_filter_in_operator {

  //From ZABBIX common.h see ITEMS_TYPE
  /* item value types 
    typedef enum
    {
    ITEM_VALUE_TYPE_FLOAT = 0,
    ITEM_VALUE_TYPE_STR,
    ITEM_VALUE_TYPE_LOG,
    ITEM_VALUE_TYPE_UINT64,
    ITEM_VALUE_TYPE_TEXT,

    ITEM_VALUE_TYPE_MAX
    }
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Zabbix items types');
//      $types = node_type_get_types();
      $options = array();
//      foreach ($types as $type => $info) {
//        $options[$type] = t($info->name);
//      }
      $options = array(
        '0' => 'Numeric (float)',
        '1' => 'Charset',
        '2' => 'LOG',
        '3' => 'UINT64',
        '4' => 'Items Text',
      );
      asort($options);
      $this->value_options = $options;
    }
  }

}
