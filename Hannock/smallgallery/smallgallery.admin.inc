<?php

/*
	Admin Tasks 
*/



function smallgallery_admin_display() 
{
  $title = array('image-0','image-1' ,'image-2','image-3','image-4','image-5','image-6','image-7','image-8','image-9');
  $result = db_query("SELECT * FROM {smallgallery} ORDER BY id");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($title[$row->id]),
		check_plain($row->filename),
        l(t('configure'), 'admin/build/smallgallery/'. $row->id .'/configure'),
      ),
    );
  }

  $header = array(t('Title Of Images'), array('data' => t('Operations'), 'colspan' => '2'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}




function smallgallery_admin_configure($form_state, $small , $op = 'configure') 
{

  $form = array();
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $small->id,
  );

  // Info
	  $form['info'] = array(
		'#type' => 'fieldset',
		'#title' => t('Image Uploading'),
		'#collapsible' => TRUE,
	  );
	  $form['#attributes']['enctype'] = 'multipart/form-data';
	  $form['info']['document_upload'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image ->'.$small->id ),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
	  );


   // End of form
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#submit' => array('smallgallery_admin_cancel_submit'),
    );
	
  	return $form;
}





function smallgallery_admin_configure_submit($form, &$form_state) 
{
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {
   $validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('44x39'),'file_validate_size' => array(3000 * 1024),);
   $file = file_save_upload('document_upload', $validators , file_directory_path());
	
	$sql = "UPDATE {smallgallery} SET";
	$sql .= " filepath = '%s' ";
	$sql .= " WHERE id = %d";
	db_query($sql,
		 $file->filename,
	  	 $form_state['values']['id']
	);
    drupal_set_message(t('The Gallery Image has been saved.'));
    $form_state['redirect'] = 'admin/build/smallgallery';
  }


  return;
}

