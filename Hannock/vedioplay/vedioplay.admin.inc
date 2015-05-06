<?php

/*
	Admin Tasks 
*/



function vedioplay_admin_display() 
{
  $result = db_query("SELECT * FROM {vedioplay} ORDER BY vid");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->des),
        l(t('configure'), 'admin/build/vedioplay/'. $row->vid .'/configure'),
        l(t('delete'), 'admin/build/vedioplay/'. $row->vid .'/delete'),
      ),
    );
  }

  $header = array(t('Video Title'),t('Description'), array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}



function vedioplay_admin_configure($form_state, $play , $op = 'configure') 
{

  $form = array();
  $form['vid'] = array(
    '#type' => 'value',
    '#value' => $play->vid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video'),
    '#collapsible' => TRUE,
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Video Title'),
    '#default_value' => $play->title,
    '#description' => t('Enter video category'),
    '#required' => TRUE,
    '#maxlength' => 200,
  );
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['info']['document_upload'] = array(
      '#type' => 'file',
      '#title' => t('Select Video File'),
      '#required' => FALSE,
      '#description' => t('Click "Browse" to select a File to upload. (in FLV Format)'),
      );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Video Description'),
    '#default_value' => $play->des,
    '#description' => t('Enter Video Description'),
    '#required' => TRUE,
    '#maxlength' => 300,
  );

   // End of form



  if ($op == 'configure') {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#validate' => array('vedioplay_admin_cancel_validate'),
      '#submit' => array('vedioplay_admin_cancel_submit'),
    );
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }
  else if ($op == 'add') 
  {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('vedioplay_admin_add_submit'),
    );
  }
  return $form;
}




function vedioplay_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('!field field is required.', array('!field' => $form['info']['title']['#title'])));
  }
}

function vedioplay_admin_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {

  	$file = file_save_upload('document_upload', NULL , file_directory_path());
	
	if($file)
  	{		
			$sql = "UPDATE {vedioplay} SET ";
			$sql .= " title = '%s' , des = '%s' , filename = '%s'";
			$sql .= " WHERE vid = %d ";
			db_query($sql,
			  $form_state['values']['title'],
			  $form_state['values']['des'],
			  $file->filename,
			  $form_state['values']['vid']
			);
			drupal_set_message(t('The Vedio %name has been saved.', array('%name' => $form_state['values']['title'])));
			$form_state['redirect'] = 'admin/build/vedioplay';
	}
	else
	{
			$sql = "UPDATE {vedioplay} SET";
			$sql .= " title = '%s' , des = '%s'";
			$sql .= " WHERE vid = '%d'";
			db_query($sql,
			  $form_state['values']['title'],
			   $form_state['values']['des'],
			  $form_state['values']['vid']
			);
			drupal_set_message(t('The Vedio %name has been saved.', array('%name' => $form_state['values']['title'])));
			$form_state['redirect'] = 'admin/build/vedioplay';
	}
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/vedioplay/'. $form_state['values']['vid'] .'/delete';
  }

  return;
}

/**
 * Save the new my.
 */
function vedioplay_admin_add_submit($form, &$form_state) 
{
  
  $file = file_save_upload('document_upload', NULL , file_directory_path());
  
  if($file)
  {	
  		$sql = "INSERT INTO {vedioplay} (title , des , filename)";
  		$sql .= " VALUES ('%s' , '%s' , '%s' )";

		  db_query($sql,
		   $form_state['values']['title'],
		   $form_state['values']['des'],
		   $file->filename
		  );
		  drupal_set_message(t('The Vedio %title has been created.', array('%title' => $form_state['values']['title'])));
		  $form_state['redirect'] = 'admin/build/vedioplay';
  }
  else
  {
  		drupal_set_message("Please select Vedio File");
		$form_state['redirect'] = 'admin/build/vedioplay';	
  }
  return;
}


function vedioplay_admin_cancel_validate($form, &$form_state) {
}

function vediocategory_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/vedioplay';
  return;
}


function vedioplay_admin_delete($form_state, $play) {
  $form['play'] = array('#type' => 'hidden', '#value' => serialize($play));
  $params = array('%title' => $play->title);
  return confirm_form($form, t('Are you sure you want to delete the Vedio %title?', $params), 'admin/build/vedioplay', '', t('Delete'), t('Cancel'));
}



function vedioplay_admin_delete_submit($form, &$form_state) 
{
  $play = unserialize($form_state['values']['play']);
  db_query('DELETE FROM {vedioplay} WHERE vid = %d', $play->vid);
  drupal_set_message(t('The Vedio %title has been removed.', array('%title' => $play->title)));
  $form_state['redirect'] = 'admin/build/vedioplay';
  return;
}
