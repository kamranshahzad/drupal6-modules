<?php

/*
	Admin Tasks 
*/



function newsletter_admin_display() 
{
  $result = db_query("SELECT * FROM {newsletter} ORDER BY nid");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->des),
        l(t('configure'), 'admin/build/newsletter/'. $row->nid .'/configure'),
        l(t('delete'), 'admin/build/newsletter/'. $row->nid .'/delete'),
      ),
    );
  }

  $header = array(t('Newsletter Title'),t('Newsletter Description'),array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}



/*
	Form of Navigation Menu
*/
function newsletter_admin_configure($form_state, $news , $op = 'configure') 
{

  $form = array();
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $news->nid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsletter Settings'),
    '#collapsible' => TRUE,
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsletter Title'),
    '#default_value' => $news->title,
    '#description' => t('This will Display on newsletter Menu'),
    '#required' => TRUE,
    '#maxlength' => 256,
  );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Newsletter Description'),
    '#default_value' => $news->des,
    '#description' => t('for Newsletter Description'),
    '#required' => TRUE,
    '#maxlength' => 300,
  );
	$form['#attributes']['enctype'] = 'multipart/form-data';
    $form['info']['newsletter_upload'] = array(
      '#type' => 'file',
      '#title' => t('select newsletter File'),
      '#required' => FALSE,
      '#description' => t('click "Browse" to select a newsletter file to upload.  '),
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
      '#validate' => array('newsletter_admin_cancel_validate'),
      '#submit' => array('newsletter_admin_cancel_submit'),
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
      '#submit' => array('newsletter_admin_add_submit'),
    );
  }
  return $form;
}




function newsletter_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('!field field is required.', array('!field' => $form['info']['title']['#title'])));
  }
}

function newsletter_admin_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) 
  {
  			$file = file_save_upload('newsletter_upload', NULL , file_directory_path());
			if($file)
			{
					$sql = "UPDATE {newsletter} SET";
					$sql .= " title = '%s' , des = '%s' , filename='%s' ";
					$sql .= " WHERE nid = %d";
					db_query($sql,
					  $form_state['values']['title'],
					  $form_state['values']['des'],
					  $file->filename,
					  $form_state['values']['nid']
					);
					drupal_set_message(t('The Newsletter %name has been saved.', array('%name' => $form_state['values']['title'])));
					$form_state['redirect'] = 'admin/build/newsletter';
			}
			else
			{
					$sql = "UPDATE {newsletter} SET";
					$sql .= " title = '%s' , des = '%s' ";
					$sql .= " WHERE nid = %d";
					db_query($sql,
					  $form_state['values']['title'],
					  $form_state['values']['des'],
					  $form_state['values']['did']
					);
					drupal_set_message(t('The Documents %name has been saved.', array('%name' => $form_state['values']['title'])));
					$form_state['redirect'] = 'admin/build/newsletter';
			}
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/newsletter/'. $form_state['values']['nid'] .'/delete';
  }

  return;
}



function newsletter_admin_add_submit($form, &$form_state) {
	
	$file = file_save_upload('newsletter_upload', NULL , file_directory_path());
	if($file)
  	{
  		$sql = "INSERT INTO {newsletter} (title, des , filename , dates  )";
  		$sql .= " VALUES ('%s', '%s' , '%s' , '%d')";
  		db_query($sql,
   			$form_state['values']['title'],
	   		$form_state['values']['des'],
			$file->filename,
			time()
  		);
  		drupal_set_message(t('The newsletter %title has been created.', array('%title' => $form_state['values']['title'])));
  		$form_state['redirect'] = 'admin/build/newsletter';
  		return;
	}
	
}



function newsletter_admin_cancel_validate($form, &$form_state) {
}

function newsletter_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/newsletter';
  return;
}


function newsletter_admin_delete($form_state, $news) {
  $form['news'] = array('#type' => 'hidden', '#value' => serialize($news));
  $params = array('%title' => $news->title);
  return confirm_form($form, t('Are you sure you want to delete the Newsletter  %title?', $params), 'admin/build/newsletter', '', t('Delete'), t('Cancel'));
}



function newsletter_admin_delete_submit($form, &$form_state) {
  $news = unserialize($form_state['values']['news']);
  db_query('DELETE FROM {newsletter} WHERE nid = %d', $news->nid);
  drupal_set_message(t('The Documents %title has been removed.', array('%title' => $news->title)));
  $form_state['redirect'] = 'admin/build/newsletter';
  return;
}
