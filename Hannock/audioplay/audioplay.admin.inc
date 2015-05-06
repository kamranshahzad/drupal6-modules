<?php

/*
	Admin Tasks 
*/



function audioplay_admin_display() 
{
  $result = db_query("SELECT * FROM {audioplay} ORDER BY aid");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->des),
        l(t('configure'), 'admin/build/audioplay/'. $row->aid .'/configure'),
        l(t('delete'), 'admin/build/audioplay/'. $row->aid .'/delete'),
      ),
    );
  }

  $header = array(t('Audio Title'),t('Description'), array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}



function audioplay_admin_configure($form_state, $ad , $op = 'configure') 
{

  $form = array();
  $form['aid'] = array(
    '#type' => 'value',
    '#value' => $ad->aid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Audio File Uploading'),
    '#collapsible' => TRUE,
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Audio Title'),
    '#default_value' => $ad->title,
    '#description' => t('Enter Title of audio file'),
    '#required' => TRUE,
    '#maxlength' => 200,
  );
/*    $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Vedio Title'),
    '#default_value' => $ad->title,
    '#description' => t('Enter vedio category'),
    '#required' => TRUE,
    '#maxlength' => 200,
  );*/
   $form['info']['cat'] = array(
    '#type' => 'select',
    '#title' => t('Audio Category'),
    '#default_value' => $ad->title,
    '#description' => t('Select Audio category'),
    '#options' => array('g'=>'General' , 'k'=>'Kids'),
  );
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['info']['document_upload'] = array(
      '#type' => 'file',
      '#title' => t('Select Audio File'),
      '#required' => FALSE,
      '#description' => t('Click "Browse" to select a File to upload.'),
      );
	  
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Audio File Description'),
    '#default_value' => $ad->des,
    '#description' => t('Enter Audio Description'),
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
      '#validate' => array('audioplay_admin_cancel_validate'),
      '#submit' => array('audioplay_admin_cancel_submit'),
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
      '#submit' => array('audioplay_admin_add_submit'),
    );
  }
  return $form;
}




function audioplay_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('!field field is required.', array('!field' => $form['info']['title']['#title'])));
  }
}

function audioplay_admin_configure_submit($form, &$form_state) 
{
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {

  	$file = file_save_upload('document_upload', NULL , file_directory_path());
	
	if($file)
  	{		
			$sql = "UPDATE {audioplay} SET";
			$sql .= " title = '%s' , des = '%s' , cat = '%s' ,filename = '%s' ";
			$sql .= " WHERE aid = %d";
			db_query($sql,
			  $form_state['values']['title'],
			  $form_state['values']['des'],
			  $form_state['values']['cat'],
			  $file->filename,
			  $form_state['values']['aid']
			);
			drupal_set_message(t('The Audio %name has been saved.', array('%name' => $form_state['values']['title'])));
			$form_state['redirect'] = 'admin/build/audioplay';
	}
	else
	{
			$sql = "UPDATE {audioplay} SET";
			$sql .= " title = '%s' , des = '%s' , cat = '%s'";
			$sql .= " WHERE aid = %d";
			db_query($sql,
			  $form_state['values']['title'],
			  $form_state['values']['des'],
			  $form_state['values']['cat'],
			  $form_state['values']['aid']
			);
			drupal_set_message(t('The Audio File %name has been saved.', array('%name' => $form_state['values']['title'])));
			$form_state['redirect'] = 'admin/build/audioplay';
	}
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/audioplay/'. $form_state['values']['aid'] .'/delete';
  }

  return;
}


function audioplay_admin_add_submit($form, &$form_state) 
{
  
  $file = file_save_upload('document_upload', NULL , file_directory_path());
  
  if($file)
  {	
  		$sql = "INSERT INTO {audioplay} (title , des , cat ,filename)";
  		$sql .= " VALUES ('%s' , '%s' , '%s' , '%s' )";

		  db_query($sql,
		   $form_state['values']['title'],
		   $form_state['values']['des'],
		   $form_state['values']['cat'],
		   $file->filename
		  );
		  drupal_set_message(t('The Audio %title has been created.', array('%title' => $form_state['values']['title'])));
		  $form_state['redirect'] = 'admin/build/audioplay';
  }
  else
  {
  		drupal_set_message("Please select Vedio File");
		$form_state['redirect'] = 'admin/build/audioplay';	
  }
  return;
}


function audioplay_admin_cancel_validate($form, &$form_state) {
}

function audioplay_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/audioplay';
  return;
}


function audioplay_admin_delete($form_state, $ad) {
  $form['ad'] = array('#type' => 'hidden', '#value' => serialize($ad));
  $params = array('%title' => $ad->title);
  return confirm_form($form, t('Are you sure you want to delete the Audio %title?', $params), 'admin/build/audioplay', '', t('Delete'), t('Cancel'));
}



function audioplay_admin_delete_submit($form, &$form_state) 
{
  $ad = unserialize($form_state['values']['ad']);
  db_query('DELETE FROM {audioplay} WHERE aid = %d', $ad->aid);
  drupal_set_message(t('The Audio %title has been removed.', array('%title' => $ad->title)));
  $form_state['redirect'] = 'admin/build/audioplay';
  return;
}
