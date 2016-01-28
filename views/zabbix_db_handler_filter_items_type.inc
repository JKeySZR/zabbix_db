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
class zabbix_db_handler_filter_items_type extends views_handler_filter_in_operator {

  //From ZABBIX common.h see ITEMS_TYPE
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
    ITEM_TYPE_SNMPTRAP       17 *
    }
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Zabbix items types');
      $options = array();
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
      asort($options);
      $this->value_options = $options;
    }
  }

}
