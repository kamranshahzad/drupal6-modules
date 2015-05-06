<?php
// $Id: my.admin.inc,v 1.5 2009/01/11 13:49:11 kirie Exp $


function activites_admin_display() {

  $result = db_query("SELECT * FROM {activites} ORDER BY aid");
  $rows = array();
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
        l(t('configure'), 'admin/build/activites/'. $row->aid .'/configure'),
        l(t('delete'), 'admin/build/activites/'. $row->aid .'/delete'),
      ),
    );
  }

  $header = array(t('Activites Title'), array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}


function activites_admin_configure($form_state, $act, $op = 'configure') 
{

  
	 $form = array();
	  $form['aid'] = array(
		'#type' => 'value',
		'#value' => $act->aid,
	  );
		
	 	  $form['#attributes']['enctype'] = 'multipart/form-data';
  
		  $form['info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Activites Detail'),
			'#collapsible' => FALSE,
		  );
		  
		  $form['info']['title'] = array(
			'#type' => 'textfield',
			'#title' => t('Title of Activity'),
			'#default_value' => $act->title,
			'#description' => t('This will display on Header of the page'),
			'#required' => TRUE,
			'#maxlength' => 300,
		  );
  
  		// Fields # 1
	  	$form['info']['text1'] = array(
			'#type' => 'textarea',
			'#title' => t('Dialog Text 1'),
			'#default_value' => $act->text1,
			'#description' => t('Enter the Dialog1 Description'),
			'#maxlength' => 255,
	  	);
	    $form['info']['image1'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-1'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
		);
   		$form['a1'] = array('#type' => 'hidden', '#value' => $act->image1);
		
		
   		// Field # 2
   		$form['info']['text2'] = array(
			'#type' => 'textarea',
			'#title' => t('Dialog Text 2'),
			'#default_value' => $act->text2,
			'#description' => t('Enter the Dialog Text'),
			'#maxlength' => 255,
	  	);
	   $form['info']['image2'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-2'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
		);
		$form['a2'] = array('#type' => 'hidden', '#value' => $act->image2);
		
		
		// Field # 3
		$form['info']['text3'] = array(
			'#type' => 'textarea',
			'#title' => t('Dialog Text 3'),
			'#default_value' => $act->text3,
			'#description' => t('Enter the Dialog Text'),
			'#maxlength' => 300,
	  	);
	   $form['info']['image3'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-3'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
		);
   		$form['a3'] = array('#type' => 'hidden', '#value' => $act->image3);
		
		
   		// Field # 4
   		$form['info']['text4'] = array(
			'#type' => 'textarea',
			'#title' => t('Dialog Text 4'),
			'#default_value' => $act->text4,
			'#description' => t('Enter the Dialog Text'),
			'#maxlength' => 300,
	  	);
	   $form['info']['image4'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-4'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
		);
		$form['a4'] = array('#type' => 'hidden', '#value' => $act->image4);
		
		
		// Field # 5
		$form['info']['text5'] = array(
			'#type' => 'textarea',
			'#title' => t('Dialog Text 5'),
			'#default_value' => $act->text5,
			'#description' => t('Enter the Dialog Text'),
			'#maxlength' => 300,
	  	);
	   $form['info']['image5'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-5'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
		);
  		$form['a5'] = array('#type' => 'hidden', '#value' => $act->image5);
		
		
		// Field # 6
		$form['info']['text6'] = array(
			'#type' => 'textarea',
			'#title' => t('Dialog Text 6'),
			'#default_value' => $act->text6,
			'#description' => t('Enter the Dialog Text'),
			'#maxlength' => 300,
	  	);
	   $form['info']['image6'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-6'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
		);
		$form['a6'] = array('#type' => 'hidden', '#value' => $act->image6);
		
		
		
		// Field # 7
		$form['info']['text7'] = array(
			'#type' => 'textarea',
			'#title' => t('Dialog Text 7'),
			'#default_value' => $act->text7,
			'#description' => t('Enter the Dialog Text'),
			'#maxlength' => 300,
	  	);
	   $form['info']['image7'] = array(
		  '#type' => 'file',
		  '#title' => t('Select Image-7'),
		  '#required' => FALSE,
		  '#description' => t('Click "Browse" to select a Image to upload.'),
		);
		$form['a7'] = array('#type' => 'hidden', '#value' => $act->image7);

// End of fields
  if ($op == 'configure')
   {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#validate' => array('activites_admin_cancel_validate'),
      '#submit' => array('activites_admin_cancel_submit'),
    );
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }
  else if ($op == 'add' ) 
  {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('activites_admin_add_submit'),
    );
  }
  return $form;
}


function  activites_admin_configure_validate($form, &$form_state)
{

}

function activites_admin_add_submit($form, &$form_state) {
			 $validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('344x269'),'file_validate_size' => array(3000 * 1024),);
  			$img1 = file_save_upload('image1', $validators , file_directory_path().'/'.get_activity_path2());	
			$img2 = file_save_upload('image2', $validators , file_directory_path().'/'.get_activity_path2());	
			$img3 = file_save_upload('image3', $validators , file_directory_path().'/'.get_activity_path2());	
			$img4 = file_save_upload('image4', $validators , file_directory_path().'/'.get_activity_path2());	
			$img5 = file_save_upload('image5', $validators , file_directory_path().'/'.get_activity_path2());	
			$img6 = file_save_upload('image6', $validators , file_directory_path().'/'.get_activity_path2());	
			$img7 = file_save_upload('image7', $validators , file_directory_path().'/'.get_activity_path2());	
			
		  $sql = "INSERT INTO {activites} (title,  text1,  text2,  text3,  text4,  text5,  text6,  text7  , image1, image2, image3, image4, image5, image6, image7)";
		  $sql .= " VALUES ('%s',     '%s' , '%s', '%s', '%s', '%s', '%s', '%s'  	, '%s' , '%s', '%s', '%s', '%s', '%s', '%s' )";
		  db_query($sql,
								$form_state['values']['title'],
								$form_state['values']['text1'],
								$form_state['values']['text2'],
								$form_state['values']['text3'],
								$form_state['values']['text4'],
								$form_state['values']['text5'],
								$form_state['values']['text6'],
								$form_state['values']['text7'],
								$img1->filename	,
								$img2->filename	,
								$img3->filename	,
								$img4->filename	,
								$img5->filename	,
								$img6->filename	,
								$img7->filename
		  );
  drupal_set_message(t('The Activites %title has been created.', array('%title' => $form_state['values']['title'])));
  $form_state['redirect'] = 'admin/build/activites';
  return;
}

function activites_admin_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) 
  {
		  	$validators = array( 'file_validate_is_image' => array(),'file_validate_image_resolution' => array('344x269'),'file_validate_size' => array(3000 * 1024),);
  			$img1 = file_save_upload('image1', $validators , file_directory_path().'/'.get_activity_path2());	
			$img2 = file_save_upload('image2', $validators , file_directory_path().'/'.get_activity_path2());	
			$img3 = file_save_upload('image3', $validators , file_directory_path().'/'.get_activity_path2());	
			$img4 = file_save_upload('image4', $validators , file_directory_path().'/'.get_activity_path2());	
			$img5 = file_save_upload('image5', $validators , file_directory_path().'/'.get_activity_path2());	
			$img6 = file_save_upload('image6', $validators , file_directory_path().'/'.get_activity_path2());	
			$img7 = file_save_upload('image7', $validators , file_directory_path().'/'.get_activity_path2());	
			$sql = "UPDATE {activites} SET ";
			$sql .= "title = '%s' , text1 = '%s' ,text2 = '%s' , text3 = '%s' , text4 = '%s' , text5 = '%s' , text6 = '%s' ,text7 = '%s',";
			$sql .= " image1 = '%s' ,image2 = '%s' , image3 = '%s' , image4 = '%s' , image5 = '%s' , image6 = '%s' ,image7 = '%s' ";
			$sql .= " WHERE aid = %d";
			
			db_query($sql,
						$form_state['values']['title'],
						$form_state['values']['text1'],
						$form_state['values']['text2'],
						$form_state['values']['text3'],
						$form_state['values']['text4'],
						$form_state['values']['text5'],
						$form_state['values']['text6'],
						$form_state['values']['text7'],
                        changeImageName($img1->filename , $form_state['values']['a1']),
						changeImageName($img2->filename	, $form_state['values']['a2']),
						changeImageName($img3->filename	, $form_state['values']['a3']),
						changeImageName($img4->filename	, $form_state['values']['a4']),
						changeImageName($img5->filename	, $form_state['values']['a5']),
						changeImageName($img6->filename	, $form_state['values']['a6']),
						changeImageName($img7->filename	, $form_state['values']['a7']),	
						$form_state['values']['aid']
					);
					drupal_set_message(t('The Activites %name has been saved.', array('%name' => $form_state['values']['name'])));
					$form_state['redirect'] = 'admin/build/activites';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/activites/'. $form_state['values']['aid'] .'/delete';
  }
  return;
}


// for Delete
function activites_admin_delete($form_state, $act) {
  $form['act'] = array('#type' => 'hidden', '#value' => serialize($act));
  $params = array('%title' => $act->title);
  return confirm_form($form, t('Are you sure you want to delete the Activity %title?', $params), 'admin/build/activites', '', t('Delete'), t('Cancel'));
}



function activites_admin_delete_submit($form, &$form_state) {
  $act = unserialize($form_state['values']['act']);
  db_query('DELETE FROM {activites} WHERE aid = %d', $act->aid);
  drupal_set_message(t('The Activites  %title has been removed.', array('%title' => $act->title)));
  $form_state['redirect'] = 'admin/build/activites';
  return;
}


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

function get_activity_path2()
{
	$result = db_query("SELECT * FROM file_paths WHERE fid='1'");
	$row = db_fetch_object($result);
	return $row->text_path;
	
}