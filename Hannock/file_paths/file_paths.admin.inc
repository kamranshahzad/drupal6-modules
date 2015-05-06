<?php

/*
	Admin Tasks 
*/



function file_paths_admin_display() 
{
  $title = array('Noting','Activity Images','Documents Files' ,'NewsLetters Files','Small Gallery Images','Image Display Files','Staff Images','Links Images','Audio Files','Audio Player Path','Video Files', 'Video Player Path');
  $result = db_query("SELECT * FROM {file_paths} ORDER BY fid");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($title[$row->fid]),
		check_plain('files/'.$row->text_path),
        l(t('configure'), 'admin/build/file_paths/'. $row->fid .'/configure'),
      ),
    );
  }

  $header = array(t('Desciptions of Paths  '),t('Current Paths                  '), array('data' => t('Operations'), 'colspan' => '2'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}




function file_paths_admin_configure($form_state, $path , $op = 'configure') 
{
  $title = array('Noting','Activity Images','Documents Files' ,'NewsLetters Files','Small Gallery Images','Image Display Files','Staff Images','Links Images','Audio Files','Audio Player Path','Video Files', 'Video Player Path');
  $form = array();
  
  $form['fid'] = array(
    '#type' => 'value',
    '#value' => $path->fid,
  );

  $form['info'] = array(
		'#type' => 'fieldset',
		'#title' => t('Image Uploading'),
		'#collapsible' => TRUE,
   );
   
  $form['info']['text_path'] = array(
    '#type' => 'textfield',
    '#title' => t($title[$path->fid]),
    '#default_value' => $path->text_path,
    '#description' => t('Enter Given Path'),
    '#required' => TRUE,
    '#maxlength' => 200,
  );


   // End of form
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#submit' => array('file_paths_admin_cancel_submit'),
    );
	
  	return $form;
}


function file_paths_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/file_paths';
  return;
}


function file_paths_admin_configure_submit($form, &$form_state) 
{
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {
	
	$sql = "UPDATE {file_paths} SET";
	$sql .= " text_path = '%s' ";
	$sql .= " WHERE fid = %d";
	db_query($sql,
		 $form_state['values']['text_path'],
	  	 $form_state['values']['fid']
	);
    drupal_set_message(t('The new path set Successfully'));
    $form_state['redirect'] = 'admin/build/file_paths';
  }
  return;
}

