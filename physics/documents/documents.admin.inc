<?php

/*
	Admin Tasks 
*/

function documents_admin_display() 
{
  $result = db_query("SELECT * FROM {documents} ORDER BY did");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->des),
		check_plain(get_topic_names($row->tid)),
        l(t('configure'), 'admin/build/documents/'. $row->did .'/configure'),
        l(t('delete'), 'admin/build/documents/'. $row->did .'/delete'),
      ),
    );
  }

  $header = array(t('Note Title'),t('Note Description'),t('Topic Title'),array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}



/*
	Form of Navigation Menu
*/
function documents_admin_configure($form_state, $doc , $op = 'configure') 
{

  $form = array();
  $form['#attributes']['enctype'] = 'multipart/form-data';
  
  $form['did'] = array(
    '#type' => 'value',
    '#value' => $doc->did,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notes Information'),
    '#collapsible' => TRUE,
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Note Title'),
    '#default_value' => $doc->title,
    '#description' => t('This will Display on Document Menu'),
    '#required' => TRUE,
    '#maxlength' => 256,
  );
  $form['info']['tid'] = array(
    	'#type' => 'select',
    	'#title' => t('Select Topic'),
		'#options' => get_all_topics(),
    	'#description' => t('Please Select Topic Title'),
  );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Note Description'),
    '#default_value' => $doc->des,
    '#description' => t('This will Apprear in Tooltip for Document Description'),
    '#required' => TRUE,
    '#maxlength' => 300,
  );
   
  $form['files'] = array(
    '#type' => 'fieldset',
    '#title' => t('Note Files'),
    '#collapsible' => TRUE,
  );
  
  $form['files']['ulink'] = array(
		'#type' => 'textfield',
		'#title' => t('Youtube video Link'),
		'#default_value' => $doc->ulink,
		'#description' => t('Please Enter Youtube Video Link'),
		'#required' => FALSE,
		'#maxlength' => 2000,
  );
  
    $form['files']['file1'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Note File'),
		  '#required' => FALSE,
		  '#description' => t('File Must be in PDF and MS Word Format'),
    );
	$form['a1'] = array('#type' => 'hidden', '#value' => $doc->file1);
	
	$form['files']['file2'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Worksheet File'),
		  '#required' => FALSE,
		  '#description' => t('File Must be in PDF and MS Word Format'),
    );
	$form['a2'] = array('#type' => 'hidden', '#value' => $doc->file2);
	
	$form['files']['file3'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image File'),
		  '#required' => FALSE,
		  '#description' => t('Image File Must in gif/jpeg format'),
     );
	 $form['a3'] = array('#type' => 'hidden', '#value' => $doc->file3);
   // End of form



  if ($op == 'configure') {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#validate' => array('documents_admin_cancel_validate'),
      '#submit' => array('documents_admin_cancel_submit'),
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
      '#submit' => array('documents_admin_add_submit'),
    );
  }
  return $form;
}




function documents_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('!field field is required.', array('!field' => $form['info']['title']['#title'])));
  }
}

function documents_admin_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) 
  {
  			$file1 = file_save_upload('file1', NULL , file_directory_path().'/docs');
			$file2 = file_save_upload('file2', NULL , file_directory_path().'/worksheets');
			$file3 = file_save_upload('file3', NULL , file_directory_path().'/videos');
			
			$sql = "UPDATE {documents} SET";
			$sql .= " title='%s',des='%s',tid='%d',ulink='%s',file1='%s',file2='%s',file3='%s'";
			$sql .= " WHERE did = %d";
			db_query($sql,
			  $form_state['values']['title'],
			  $form_state['values']['des'],
			  $form_state['values']['tid'],
			  $form_state['values']['ulink'],
			  changeImageName($file1->filename , $form_state['values']['a1']),
			  changeImageName($file2->filename , $form_state['values']['a2']),
			  changeImageName($file3->filename , $form_state['values']['a3']),
			  $form_state['values']['did']
			);
			drupal_set_message(t('The Documents %name has been saved.', array('%name' => $form_state['values']['title'])));
			$form_state['redirect'] = 'admin/build/documents';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/documents/'. $form_state['values']['did'] .'/delete';
  }

  return;
}

/**
 * Save the new my.
 */
function documents_admin_add_submit($form, &$form_state) {
	
	
	$file1 = file_save_upload('file1', NULL , file_directory_path().'/docs');
	$file2 = file_save_upload('file2', NULL , file_directory_path().'/worksheets');
	$file3 = file_save_upload('file3', NULL , file_directory_path());
				
  	$sql = "INSERT INTO {documents} (title,des,tid,ulink,file1,file2,file3)";
  		$sql .= " VALUES ('%s', '%s' , '%d' , '%s' , '%s' , '%s' , '%s')";
  		db_query($sql,
   			$form_state['values']['title'],
	   		$form_state['values']['des'],
			$form_state['values']['tid'],
			$form_state['values']['ulink'],
			$file1->filename,
			$file2->filename,
			$file3->filename
  		);
  		drupal_set_message(t('The Note %title has been created.', array('%title' => $form_state['values']['title'])));
  		$form_state['redirect'] = 'admin/build/documents';
  		return;
}



function documents_admin_cancel_validate($form, &$form_state) {
}

function documents_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/documents';
  return;
}

/**
 * Menu callback; confirm deletion of a my.
 */
function documents_admin_delete($form_state, $doc) {
  $form['doc'] = array('#type' => 'hidden', '#value' => serialize($doc));
  $params = array('%title' => $doc->title);
  return confirm_form($form, t('Are you sure you want to delete the Documents  %title?', $params), 'admin/build/documents', '', t('Delete'), t('Cancel'));
}



function documents_admin_delete_submit($form, &$form_state) {
  $doc = unserialize($form_state['values']['doc']);
  db_query('DELETE FROM {documents} WHERE did = %d', $doc->did);
  drupal_set_message(t('The Documents %title has been removed.', array('%title' => $doc->title)));
  $form_state['redirect'] = 'admin/build/documents';
  return;
}


/* get All Ariticals */
function get_all_topics()
{
	$result = db_query("SELECT * FROM {topics} ORDER BY tid");
  	$rows = array();
  	while ($row = db_fetch_object($result)) 
  	{
		$rows[$row->tid ] =  $row->title;
	}
	return $rows;
}

/* get Sepecfic Topic */
function get_topic_names($id)
{
	$result = db_query("SELECT * FROM {topics} WHERE tid='$id'");
	$row = db_fetch_object($result);
	return $row->title;
}

//  File Related Function
function  changeImageName($file , $or_value)
{
	$out = '';
	if($file)
	{
		$out = $file;
	}
	else
	{
		$out = $or_value;
	}
	return $out;
}