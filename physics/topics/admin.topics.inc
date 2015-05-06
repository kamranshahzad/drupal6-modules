<?php
// $Id: my.admin.inc,v 1.5 2009/01/11 13:49:11 kirie Exp $


function topics_display()
 {
  $result = db_query("SELECT * FROM {topics} ORDER BY tid");
  $rows = array();
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->des),
		check_plain(getClass($row->cat)),
       	l(t('edit'), 'admin/build/topics/'. $row->tid .'/configure'),
        l(t('delete'), 'admin/build/topics/'. $row->tid .'/delete'),
      ),
    );
  }

  $header = array(t('Topic Title'),t('Topic Description'),t(' Class'), array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'ml_products-admin-list'), NULL);
}


 
function topics_configure($form_state, $top, $op = 'configure') 
{
  $form = array();
  $form['tid'] = array(
    '#type' => 'value',
    '#value' => $top->tid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Topics Detail'),
    '#collapsible' => FALSE,
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Topic Title'),
    '#default_value' => $top->title,
    '#description' => t('Enter title of topic'),
    '#required' => TRUE,
    '#maxlength' => 255,
  );
  $form['info']['cat'] = array(
    	'#type' => 'select',
    	'#title' => t('Select Class'),
		'#options' => array(0=>'O-Level' , 1=>'A-Level'),
    	'#description' => t('Please Select Class Level'),
  );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Topic Description'),
    '#default_value' => $top->des,
    '#description' => t('Enter Description of Topic'),
    '#required' => TRUE,
    '#maxlength' => 300,
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
      '#validate' => array('topics_cancel_validate'),
      '#submit' => array('topics_cancel_submit'),
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
      '#submit' => array('topics_add_submit'),
    );
  }
  return $form;
}




function  topics_configure_validate($form, &$form_state) {
	
}

function topics_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {			
		$sql = "UPDATE {topics} SET";
		$sql .= " title = '%s', des = '%s' , cat='%d'";
		$sql .= " WHERE tid = %d";
		db_query($sql,
			$form_state['values']['title'],
			$form_state['values']['des'],
			$form_state['values']['cat'],
			 $form_state['values']['tid']
		);
		drupal_set_message(t('The Topic Updated Successfully'));
		$form_state['redirect'] = 'admin/build/topics';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/topics/'. $form_state['values']['tid'] .'/delete';
  }
  return;
}


function topics_add_submit($form, &$form_state) 
{
  	$sql = "INSERT INTO {topics} (title, des ,cat)";
  	$sql .= " VALUES ( '%s','%s' , '%d')";

  	db_query($sql,
  	$form_state['values']['title'],
	$form_state['values']['des'],
    $form_state['values']['cat']
  	);
  	drupal_set_message(t('The New Topic Created Successfully'));
  	$form_state['redirect'] = 'admin/build/topics';
  	return;
}



function topics_cancel_validate($form, &$form_state) 
{
}

function topics_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/topics';
  return;
}


function topics_delete($form_state, $top) {
  $form['top'] = array('#type' => 'hidden', '#value' => serialize($top));
  $params = array('%title' => $top->title);
  return confirm_form($form, t('Are you sure you want to delete the Event %title?', $params), 'admin/build/topics', '', t('Delete'), t('Cancel'));
}



function topics_delete_submit($form, &$form_state)
{
  $top = unserialize($form_state['values']['top']);
  db_query('DELETE FROM {topics} WHERE tid = %d', $top->tid);
  drupal_set_message(t('The Topic %title has been removed.', array('%title' => $top->title)));
  $form_state['redirect'] = 'admin/build/topics';
  return;
}


function getClass($id)
{
	$str = 'Noting';
	if($id == 0)
	{
		$str = 'O-Level';
	}
	else
	{
		$str = 'A-Level';
	}
	return $str;
}
