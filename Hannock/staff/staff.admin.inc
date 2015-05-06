<?php
// $Id: my.admin.inc,v 1.5 2009/01/11 13:49:11 kirie Exp $



function staff_admin_display() {


  $result = db_query("SELECT * FROM {staff} ORDER BY sid");
  $rows = array();
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      'data' => array(
        check_plain($row->name),
		check_plain($row->des),
        l(t('configure'), 'admin/build/staff/'. $row->sid .'/configure'),
        l(t('delete'), 'admin/build/staff/'. $row->sid .'/delete'),
      ),
    );
  }

   $header = array(t('Staff Name'),t('Description') , array('data' => t('Operations'), 'colspan' => '2'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}


function staff_admin_configure($form_state, $staff, $op = 'configure') {


  $form = array();
  $form['sid'] = array(
    '#type' => 'value',
    '#value' => $staff->sid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Staff / Governor Detail'),
    '#collapsible' => FALSE,
  );
  $form['info']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Staff/Governor Name'),
    '#default_value' => $staff->name,
    '#description' => t('Enter the Staff/Governor Name'),
    '#required' => TRUE,
    '#maxlength' => 255,
  );
  $form['info']['type'] = array(
    '#type' => 'select',
    '#title' => t('Select Staff/Governor Type'),
	'#default_value' => $staff->type,
    '#description' => t('select Staff/Governor type'),
    '#required' => TRUE,
	'#options' => array(0=>'Staff' , 1=>'Governors'),
  );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $staff->des,
    '#description' => t('Enter the Staff/Governor Description'),
    '#required' => TRUE,
  );
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['info']['document_upload'] = array(
      '#type' => 'file',
      '#title' => t('Select Staff/Governor image'),
      '#required' => FALSE,
      '#description' => t('Click "Browse" to select a Image to upload.'),
  );
  
  

  if ($op == 'configure') {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#validate' => array('staff_admin_cancel_validate'),
      '#submit' => array('staff_admin_cancel_submit'),
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
      '#submit' => array('staff_admin_add_submit'),
    );
  }
  return $form;
}




function staff_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['name'])) {
    form_set_error('name', t('!field field is required.', array('!field' => $form['info']['name']['#name'])));
  }
}

function staff_admin_configure_submit($form, &$form_state) 
{
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {
	$validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('200x200'),'file_validate_size' => array(3000 * 1024),);
  	$file = file_save_upload('document_upload', $validators , file_directory_path());
			
	if($file)
	{				
			$sql = "UPDATE {staff} SET";
			$sql .= " name = '%s',des='%s' ,image='%s' , type='%d'";
			$sql .= " WHERE sid = %d";
			db_query($sql,
				$form_state['values']['name'],
				$form_state['values']['des'],
				$file->filename,
				$form_state['values']['type'],
				$form_state['values']['sid']
			);
			drupal_set_message(t('The Staff %name has been saved.', array('%name' => $form_state['values']['name'])));
			$form_state['redirect'] = 'admin/build/staff';
	}
	else 
	{				
			$sql = "UPDATE {staff} SET";
			$sql .= " name = '%s',des='%s' ,image='%s' , type='%d'";
			$sql .= " WHERE sid = %d";
			db_query($sql,
				$form_state['values']['name'],
				$form_state['values']['des'],
				'default-img.jpg',
				$form_state['values']['type'],
				 $form_state['values']['sid']
			);
			drupal_set_message(t('The Staff %name has been saved.', array('%name' => $form_state['values']['name'])));
			$form_state['redirect'] = 'admin/build/staff';
	}
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/staff/'. $form_state['values']['sid'] .'/delete';
  }

  return;
}


function staff_admin_add_submit($form, &$form_state) {

	$validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('200x200'),'file_validate_size' => array(3000 * 1024),);
  	$file = file_save_upload('document_upload', $validators , file_directory_path());
		if($file)
	{
		$sql = "INSERT INTO {staff} ( name , des , image , type )";
		$sql .= " VALUES ( '%s', '%s' , '%s' ,'%d')";
	
		db_query($sql,
		$form_state['values']['name'],
		$form_state['values']['des'],
		$file->filename,
		$form_state['values']['type']
		);
		drupal_set_message(t('The Staff %name has been created.', array('%name' => $form_state['values']['name'])));
   }
   else
   {
   		$sql = "INSERT INTO {staff} ( name , des , image , type )";
		$sql .= " VALUES ( '%s', '%s' , '%s' ,'%d')";
	
		db_query($sql,
		$form_state['values']['name'],
		$form_state['values']['des'],
		'default-img.jpg',
		$form_state['values']['type']
		);
		drupal_set_message(t('The Staff %name has been created.', array('%name' => $form_state['values']['name'])));
   }
	$form_state['redirect'] = 'admin/build/staff';
	return;
}


function staff_admin_cancel_validate($form, &$form_state) {
}

function staff_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/staff';
  return;
}


function staff_admin_delete($form_state, $staff) {
  $form['staff'] = array('#type' => 'hidden', '#value' => serialize($staff));
  $params = array('%name' => $staff->name);
  return confirm_form($form, t('Are you sure you want to delete the Staff %name?', $params), 'admin/build/staff', '', t('Delete'), t('Cancel'));
}



function staff_admin_delete_submit($form, &$form_state) {
  $staff = unserialize($form_state['values']['staff']);
  db_query('DELETE FROM {staff} WHERE sid = %d', $staff->sid);
  drupal_set_message(t('The Staff %name has been removed.', array('%name' => $staff->name)));
  $form_state['redirect'] = 'admin/build/staff';
  return;
}
