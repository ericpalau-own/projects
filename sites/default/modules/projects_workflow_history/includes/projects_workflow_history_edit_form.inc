<?php 
/**
 * Display a text area populated with the selected workflow log comment and
 * allow the user to modify and save it.
 */
function projects_workflow_history_edit_form($form, $form_state, $workflow_history_state_transition_record) {
  $form = array();
  $form['hid'] = array(
    '#type' => 'value',
    '#value' => $workflow_history_state_transition_record->hid,
  );
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $workflow_history_state_transition_record->nid,
  );
  $form['workflow']['workflow_comment'] = array(
    '#type' => 'textarea',
    '#title' => t('Comment'),
    '#description' => t('Modify this workflow state transition comment and press submit.'),
    '#required' => TRUE,
    '#default_value' => $workflow_history_state_transition_record->comment,
    '#rows' => 2,
  );
  $form['workflow']['workflow_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start date'),
    '#description' => t('Modify this workflow state transition date and press submit.'),
    '#required' => TRUE,
    '#default_value' => date('Y-m-d H:i', $workflow_history_state_transition_record->stamp),
    '#date_format' => 'Y-m-d H:i',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Submit handler for the workflow transition comment edit form.
 *
 * @see workflow_extensions_workflow_comment_edit_form()
 */
function projects_workflow_history_edit_form_submit($form, &$form_state) {
  $nid = $form_state['values']['nid'];
  $hid = $form_state['values']['hid'];
  $comment = $form_state['values']['workflow_comment'];
  $stamp =  strtotime($form_state['values']['workflow_date']);
  /* db_query("UPDATE {workflow_node_history} SET comment = '%s' WHERE hid = %d", $comment, $hid) */
  db_update('workflow_node_history')
    ->fields(array('comment' => $comment, 'stamp' => $stamp))
    ->condition('hid', $hid)
    ->execute();

  // Whatever is set here, is overriden by the "?destination=..." parameter, if present
  $form_state['redirect'] = '/node/'.$nid.'/workflow-history';
}