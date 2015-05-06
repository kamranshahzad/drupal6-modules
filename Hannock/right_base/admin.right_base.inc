<?php
// $Id: my.admin.inc,v 1.5 2009/01/11 13:49:11 kirie Exp $


function right_base_display()
 {
  $result = db_query("SELECT * FROM {right_base} ORDER BY eid");
  $rows = array();
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      'data' => array(
        check_plain($row->event_text),
		check_plain($row->event_date),
        !$row->status ? l(t('publish'), 'admin/build/right_base/'. $row->eid .'/enable') : l(t('Un-Publish'), 'admin/build/right_base/'. $row->eid .'/disable'),
       l(t('edit'), 'admin/build/right_base/'. $row->eid .'/configure'),
        l(t('delete'), 'admin/build/right_base/'. $row->eid .'/delete'),
      ),
    );
  }

  $header = array(t('Event Text'),t('Event Date'), array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'ml_products-admin-list'), NULL);
}


 
function right_base_configure($form_state, $event, $op = 'configure') 
{
  $form = array();
  $form['eid'] = array(
    '#type' => 'value',
    '#value' => $event->eid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event Dairy Detail'),
    '#collapsible' => FALSE,
  );
  $form['info']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('is event Published on Front Page'),
    '#default_value' => $event->status,
    '#description' => t('check if you want to make Event featured'),
  );
  $form['info']['event_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $event->event_text,
    '#description' => t('Enter Description of Event'),
    '#required' => TRUE,
    '#maxlength' => 255,
  );
  $form['info']['event_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Date'),
    '#default_value' => $event->event_date,
    '#description' => t('Enter the Event Dairy Date'),
    '#required' => TRUE,
    '#maxlength' => 255,
  );

  
  // End of Form
  if ($op == 'configure') 
  {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#validate' => array('right_base_cancel_validate'),
      '#submit' => array('right_base_cancel_submit'),
    );
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }
  else if ($op == 'add' || $op == 'clone') {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('right_base_add_submit'),
    );
  }
  return $form;
}




function  right_base_configure_validate($form, &$form_state) {
	
}

function right_base_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {			
		$sql = "UPDATE {right_base} SET";
		$sql .= " event_text = '%s',event_date = '%s', status ='%d'";
		$sql .= " WHERE eid = %d";
		db_query($sql,
			$form_state['values']['event_text'],
			$form_state['values']['event_date'],
			$form_state['values']['status'],
			 $form_state['values']['eid']
		);
		drupal_set_message(t('The Event has been saved.'));
		$form_state['redirect'] = 'admin/build/right_base';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/right_base/'. $form_state['values']['eid'] .'/delete';
  }
  return;
}


function right_base_add_submit($form, &$form_state) 
{
  	$sql = "INSERT INTO {right_base} (event_text, event_date , status )";
  	$sql .= " VALUES ( '%s','%s', '%d'  )";

  	db_query($sql,
  	$form_state['values']['event_text'],
    $form_state['values']['event_date'],
    $form_state['values']['status']
  	);
  	drupal_set_message(t('The Event has been created.'));
  	$form_state['redirect'] = 'admin/build/right_base';
  	return;
}


function right_base_disable($event) {
  drupal_set_message(t('Changed Successfully'));
  db_query("UPDATE {right_base} SET status = 0 WHERE eid = %d", $event->eid);
  drupal_goto('admin/build/right_base');
}


function right_base_enable($event) {
 drupal_set_message(t('Changed Successfully'));
 db_query("UPDATE {right_base} SET status = 1 WHERE eid = %d", $event->eid);
 drupal_goto('admin/build/right_base');
}

function right_base_cancel_validate($form, &$form_state) 
{
}

function right_base_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/right_base';
  return;
}


function right_base_delete($form_state, $event) {
  $form['event'] = array('#type' => 'hidden', '#value' => serialize($event));
  $params = array('%event' => $event->event_text);
  return confirm_form($form, t('Are you sure you want to delete the Event %name?', $params), 'admin/build/right_base', '', t('Delete'), t('Cancel'));
}



function right_base_delete_submit($form, &$form_state)
{
  $event = unserialize($form_state['values']['event']);
  db_query('DELETE FROM {right_base} WHERE eid = %d', $event->eid);
  drupal_set_message(t('The Event %name has been removed.', array('%name' => $event->event_text)));
  $form_state['redirect'] = 'admin/build/right_base';
  return;
}

