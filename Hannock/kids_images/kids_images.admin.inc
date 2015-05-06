<?php

/*
	Admin Tasks 
*/



function kids_images_admin_display() 
{
  $title = array('Noting','Classess','Foundation' ,'Class - 1' , 'Class - 2');
  $result = db_query("SELECT * FROM {kids_images} ORDER BY kid");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($title[$row->kid]),
		check_plain($row->linktitle1),
		check_plain($row->linkpath1),
		check_plain($row->linktitle2),
		check_plain($row->linkpath2),
        l(t('configure'), 'admin/build/kids_images/'. $row->kid .'/configure'),
      ),
    );
  }

  $header = array(t('Pages Title'), t('Link-1 Title'), t('Link-1 Path'), t('Link-2 Title'),t('Link-2 Path'), array('data' => t('Operations'), 'colspan' => '2'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}




function kids_images_admin_configure($form_state, $kid , $op = 'configure') 
{
  $title = array('Noting','Activity Images','Documents Files' ,'NewsLetters Files','Small Gallery Images','Image Display Files','Staff Images','Links Images','Audio Files','Audio Player Path','Video Files', 'Video Player Path');
  $form = array();
  
  $form['kid'] = array(
    '#type' => 'value',
    '#value' => $kid->kid,
  );


  	$form['#attributes']['enctype'] = 'multipart/form-data';
	
  	$form['info'] = array(
		'#type' => 'fieldset',
		'#title' => t('Image Uploading'),
		'#collapsible' => TRUE,
   	);
   
   	// Link  # 1 
	  $form['info']['link1'] = array(
		'#type' => 'textfield',
		'#title' => t('Links Title - 1'),
		'#default_value' => $kid->linktitle1,
		'#description' => t('Enter 1st link title of image'),
		'#required' => TRUE,
		'#maxlength' => 200,
	  );
	  $form['info']['path1'] = array(
		'#type' => 'textfield',
		'#title' => t('Link Path - 2'),
		'#default_value' => $kid->linkpath1,
		'#description' => t('Enter 2nd Link URL'),
		'#required' => TRUE,
		'#maxlength' => 200,
	  );
	  
	// Link  # 2
	  $form['info']['link2'] = array(
		'#type' => 'textfield',
		'#title' => t('Links Title - 2'),
		'#default_value' => $kid->linktitle2,
		'#description' => t('Enter 2nd link title of image'),
		'#required' => TRUE,
		'#maxlength' => 200,
	  );
	  $form['info']['path2'] = array(
		'#type' => 'textfield',
		'#title' => t('Link Path - 1'),
		'#default_value' => $kid->linkpath2,
		'#description' => t('Enter 1st Link URL'),
		'#required' => TRUE,
		'#maxlength' => 200,
	  );
	  
   // images Fields
   	 $form['info']['image1'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-1'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
	 );
   	 $form['a1'] = array('#type' => 'hidden', '#value' => $kid->filename1);
  
     $form['info']['image2'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-1'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
	 );
   	 $form['a2'] = array('#type' => 'hidden', '#value' => $kid->filename2);
	 


   // End of form
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#submit' => array('kids_images_admin_cancel_submit'),
    );
	
  	return $form;
}


function kids_images_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/kids_images';
  return;
}


function kids_images_admin_configure_submit($form, &$form_state) 
{
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) 
  {
		$validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('246x246'),'file_validate_size' => array(3000 * 1024),);
		$file1 =  file_save_upload('image1', $validators , file_directory_path().'/kidsimages');
		$file2 =  file_save_upload('image2', $validators , file_directory_path().'/kidsimages');
		
		$sql = "UPDATE {kids_images} SET";
		$sql .= " linktitle1 = '%s' , linkpath1 = '%s' , linktitle2 = '%s' , linkpath2 = '%s' , filename1 = '%s' , filename2 = '%s' ";
		$sql .= " WHERE kid = %d";
		db_query($sql,
		 	$form_state['values']['link1'],
			$form_state['values']['path1'],
			$form_state['values']['link2'],
			$form_state['values']['path2'],
			getImageName($file1->filename , $form_state['values']['a1'] ),
			getImageName($file2->filename , $form_state['values']['a2'] ),
	  	 	$form_state['values']['kid']
			
		);
    drupal_set_message(t('The Kids Images Uploaded Successfully'));
    $form_state['redirect'] = 'admin/build/kids_images';
  }
  return;
}

function  getImageName($file , $or_value)
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