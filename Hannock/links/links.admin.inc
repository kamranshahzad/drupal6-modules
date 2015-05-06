<?php

/*
	Admin Tasks 
*/



function links_admin_display() 
{
  $result = db_query("SELECT * FROM {links} ORDER BY lid");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->des),
		check_plain($row->path),
        !$row->status ? l(t('enable'), 'admin/build/links/'. $row->lid .'/enable') : l(t('disable'), 'admin/build/links/'. $row->lid .'/disable'),
        l(t('configure'), 'admin/build/links/'. $row->lid .'/configure'),
        l(t('delete'), 'admin/build/links/'. $row->lid .'/delete'),
      ),
    );
  }

  $header = array(t('Menu Title'),t('Menu Description') , t('Path'), array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}



/*
	Form of Navigation Menu
*/
function links_admin_configure($form_state, $links , $op = 'configure') 
{

  $form = array();
  $form['lid'] = array(
    '#type' => 'value',
    '#value' => $links->lid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation Menu Settings'),
    '#collapsible' => TRUE,
  );
  $form['info']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable this link'),
    '#default_value' => $links->status,
    '#description' => t('If this setting is enabled, the current Menu will display on page'),
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu Title'),
    '#default_value' => $links->title,
    '#description' => t('Enter Title of Links Menu'),
    '#required' => TRUE,
    '#maxlength' => 256,
  );
  $form['info']['external'] = array(
    '#type' => 'checkbox',
    '#title' => t('make external this link (by default link is internal)'),
    '#default_value' => $links->external,
    '#description' => t('If this setting is enabled, the current Menu will display on page'),
  );
  $form['info']['cat'] = array(
    	'#type' => 'select',
    	'#title' => t('Select Link Category'),
		'#options' => array('0'=>'Hennock-school Link' , '1'=>'Pre-school Link' ,'2'=>'Kid Corner Link'),
    	'#description' => t('This will display Links on differnt Categories'),
  );
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['info']['document_upload'] = array(
      '#type' => 'file',
      '#title' => t('Select Link Logo'),
      '#required' => FALSE,
      '#description' => t('Click "Browse" to select a Image Logo to upload.'),
  );
	  
  $form['info']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu Link Path'),
    '#default_value' => $links->path,
    '#description' => t('Enter Links Menu Path'),
    '#required' => FALSE,
    '#maxlength' => 256,
  );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Menu Description'),
    '#default_value' => $links->des,
    '#description' => t('Enter Likn Menu Path'),
    '#required' => FALSE,
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
      '#validate' => array('links_admin_cancel_validate'),
      '#submit' => array('links_admin_cancel_submit'),
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
      '#submit' => array('links_admin_add_submit'),
    );
  }
  return $form;
}




function links_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('!field field is required.', array('!field' => $form['info']['title']['#title'])));
  }
}

function links_admin_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {


   $validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('120x58'),'file_validate_size' => array(3000 * 1024),);
   $file = file_save_upload('document_upload', $validators , file_directory_path());
   if($file)
   {
					$sql = "UPDATE {links} SET";
					$sql .= " title = '%s' , des = '%s'  , path =' %s'  ,status = '%d' , external = '%d', cat ='%s' ,logofile= '%s'";
					$sql .= " WHERE lid = %d";
					db_query($sql,
					  $form_state['values']['title'],
					  $form_state['values']['des'],
					   $form_state['values']['path'],
						$form_state['values']['status'],
						$form_state['values']['external'],
						$form_state['values']['cat'],
						 $file->filename,
					  $form_state['values']['lid']
					);
	}
	else
	{
					$sql = "UPDATE {links} SET";
					$sql .= " title = '%s' , des = '%s'  , path =' %s'  ,status = '%d' , external = '%d', cat ='%s'";
					$sql .= " WHERE lid = %d";
					db_query($sql,
					  $form_state['values']['title'],
					  $form_state['values']['des'],
					   $form_state['values']['path'],
						$form_state['values']['status'],
						$form_state['values']['external'],
						$form_state['values']['cat'],
					  $form_state['values']['lid']
					);
	}
    drupal_set_message(t('The Menu %title has been saved.', array('%title' => $form_state['values']['title'])));
    $form_state['redirect'] = 'admin/build/links';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/links/'. $form_state['values']['lid'] .'/delete';
  }

  return;
}

/**
 * Save the new my.
 */
function links_admin_add_submit($form, &$form_state) {

  $validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('120x58'),'file_validate_size' => array(3000 * 1024),);
  $file = file_save_upload('document_upload', $validators , file_directory_path());
  
  
  $sql = "INSERT INTO {links} (title, path , des , status ,external , cat , logofile)";
  $sql .= " VALUES ('%s', '%s' , '%s' ,'%d' ,'%d' , '%s' ,'%s' )";

  db_query($sql,
   $form_state['values']['title'],
      $form_state['values']['path'],
	   $form_state['values']['des'],
	    $form_state['values']['status'],
			$form_state['values']['external'],
				$form_state['values']['cat'],
					$file->filename
  );
  drupal_set_message(t('The Link %title has been created.', array('%title' => $form_state['values']['title'])));
  $form_state['redirect'] = 'admin/build/links';
  return;
}

/**
 * Menu callback: disable a specific my.
 */
function links_admin_disable($links) {
  db_query("UPDATE {links} SET status = 0 WHERE lid = %d", $links->lid);
  drupal_goto('admin/build/links');
}

/**
 * Menu callback: enable a specific my.
 */
function links_admin_enable($links) {
  db_query("UPDATE {links} SET status = 1 WHERE lid = %d", $links->lid);
  drupal_goto('admin/build/links');
}

function links_admin_cancel_validate($form, &$form_state) {
}

function links_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/links';
  return;
}

/**
 * Menu callback; confirm deletion of a my.
 */
function links_admin_delete($form_state, $links) 
{
  $form['links'] = array('#type' => 'hidden', '#value' => serialize($links));
  $params = array('%title' => $links->title);
  return confirm_form($form, t('Are you sure you want to delete the Link %title?', $params), 'admin/build/links', '', t('Delete'), t('Cancel'));
}



function links_admin_delete_submit($form, &$form_state) 
{
  $links = unserialize($form_state['values']['links']);
  db_query('DELETE FROM {links} WHERE lid = %d', $links->lid);
  drupal_set_message(t('The Link %title has been removed.', array('%title' => $links->title)));
  $form_state['redirect'] = 'admin/build/links';
  return;
}

