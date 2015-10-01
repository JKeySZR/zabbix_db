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
class zabbix_db_handler_field_items_type extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    $dbg = 1;
    // Всегда добавляем hostID поля к запросам
    //$this->additional_fields['hostid'] = array('table' => 'hosts', 'field' => 'hostid');
  }

  /**
   * Render node type as human readable name.
   */

  function render($values) {
    $dbg = 1;
/* item types 
typedef enum
{
        ITEM_TYPE_ZABBIX = 0,
        ITEM_TYPE_SNMPv1,
        ITEM_TYPE_TRAPPER,
        ITEM_TYPE_SIMPLE,
        ITEM_TYPE_SNMPv2c,
        ITEM_TYPE_INTERNAL,
        ITEM_TYPE_SNMPv3,
        ITEM_TYPE_ZABBIX_ACTIVE,
        ITEM_TYPE_AGGREGATE,
        ITEM_TYPE_HTTPTEST,
        ITEM_TYPE_EXTERNAL,
        ITEM_TYPE_DB_MONITOR,
        ITEM_TYPE_IPMI,
        ITEM_TYPE_SSH,
        ITEM_TYPE_TELNET,
        ITEM_TYPE_CALCULATED,
        ITEM_TYPE_JMX,
        ITEM_TYPE_SNMPTRAP       17 
}
    */
    $options = array(
      '0' => 'Zabbix agent',
      '1' => 'SNMPv1 agent',
      '2' => 'Zabbix trapper',
      '3' => 'Simple check',
      '4' => 'SNMPv2 agent',
      '5' => 'Zabbix internal',
      '6' => 'SNMPv3 agent',
      '7' => 'Zabbix agent (active)',
      '8' => 'Zabbix aggregate',
      '10' => 'External check',
      '11' => 'Database monitor',
      '12' => 'IPMI agent',
      '13' => 'SSH agent',
      '14' => 'TELNET agent',
      '15' => 'Calculated',
      '16' => 'JMX agent',
      '17' => 'SNMP trap',
    );
    if(isset($values->items_type)){
      $value = $options[$values->items_type];
    }else{
      $value = '';
    }
        
    return $value;
  }

}
