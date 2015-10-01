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
class zabbix_db_handler_field_hosts extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    
    $dbg = 1;
    // Всегда добавляем hostID поля к запросам
    $this->additional_fields['hostid'] = array('table' => 'hosts', 'field' => 'hostid');
    
  }

}
