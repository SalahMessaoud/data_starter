<?php

/**
 * @file
 * Drush integration for the geo_file_entity_geojson_bundle module.
 */

/**
 * Implements hook_drush_command().
 */
function publishing_workflow_drush_command() {
  $items['setup-workflow'] = array(
    'description' => dt('Presets to make workflow work properly'),
    'arguments' => array(),
    'aliases' => array(),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function publishing_workflow_drush_help($command) {
  switch ($command) {
    case 'setup-workflow':
      return dt('Presets to make workflow work properly');
      break;
  }
}
/**
 * drush setup publishing workflow command callback.
 */
function drush_publishing_workflow_setup_workflow() {
  // Setup dataset and resource to be unpublished by default
  $node_types_to_reset = array('dataset', 'resource');
  foreach ($node_types_to_reset as $node_type) {
    $variable = variable_get('node_options_' . $node_type);
    $status_ocurrances = array_keys($variable, 'status');
    foreach ($status_ocurrances as $status_ocurrance) {
      array_splice($variable, $status_ocurrance, 1);
    }
    variable_set('node_options_' . $node_type, $variable);
  }

  $authenticated_role = user_role_load_by_name('authenticated user');
  $permissions_to_revoke = array(
    'create dataset content',
    'create resource content',
    'create group content',
    'edit own dataset content',
    'edit own resource content',
    'edit own group content',
    'delete own dataset content',
    'delete own resource content',
    'delete own group content',
  );
  user_role_revoke_permissions($authenticated_role->rid, $permissions_to_revoke);
}
