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
        l(t('configure'), 'admin/build/documents/'. $row->did .'/configure'),
        l(t('delete'), 'admin/build/documents/'. $row->did .'/delete'),
      ),
    );
  }

  $header = array(t('Document Title'),t('Document Description'),array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}



/*
	Form of Navigation Menu
*/
function documents_admin_configure($form_state, $doc , $op = 'configure') 
{

  $form = array();
  $form['did'] = array(
    '#type' => 'value',
    '#value' => $doc->did,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Document Settings'),
    '#collapsible' => TRUE,
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Document Title'),
    '#default_value' => $doc->title,
    '#description' => t('This will Display on Document Menu'),
    '#required' => TRUE,
    '#maxlength' => 256,
  );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Document Description'),
    '#default_value' => $doc->des,
    '#description' => t('This will Apprear in Tooltip for Document Description'),
    '#required' => TRUE,
    '#maxlength' => 300,
  );
	$form['#attributes']['enctype'] = 'multipart/form-data';
    $form['info']['document_upload'] = array(
      '#type' => 'file',
      '#title' => t('Select Documents File'),
      '#required' => FALSE,
      '#description' => t('Click "Browse" to select a Document File to upload.  '),
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
  			$file = file_save_upload('document_upload', NULL , file_directory_path());
			if($file)
			{
					$sql = "UPDATE {documents} SET";
					$sql .= " title = '%s' , des = '%s' , filename='%s' ";
					$sql .= " WHERE did = %d";
					db_query($sql,
					  $form_state['values']['title'],
					  $form_state['values']['des'],
					  $file->filename,
					  $form_state['values']['did']
					);
					drupal_set_message(t('The Documents %name has been saved.', array('%name' => $form_state['values']['title'])));
					$form_state['redirect'] = 'admin/build/documents';
			}
			else
			{
					$sql = "UPDATE {documents} SET";
					$sql .= " title = '%s' , des = '%s' ";
					$sql .= " WHERE did = %d";
					db_query($sql,
					  $form_state['values']['title'],
					  $form_state['values']['des'],
					  $form_state['values']['did']
					);
					drupal_set_message(t('The Documents %name has been saved.', array('%name' => $form_state['values']['title'])));
					$form_state['redirect'] = 'admin/build/documents';
			}
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
	
	$file = file_save_upload('document_upload', NULL , file_directory_path());
	if($file)
  	{
  		$sql = "INSERT INTO {documents} (title, des , filename  )";
  		$sql .= " VALUES ('%s', '%s' , '%s')";
  		db_query($sql,
   			$form_state['values']['title'],
	   		$form_state['values']['des'],
			$file->filename
  		);
  		drupal_set_message(t('The Documents %title has been created.', array('%title' => $form_state['values']['title'])));
  		$form_state['redirect'] = 'admin/build/documents';
  		return;
	}
	
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
