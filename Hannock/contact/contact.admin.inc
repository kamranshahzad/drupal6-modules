<?php
// $Id: my.admin.inc,v 1.5 2009/01/11 13:49:11 kirie Exp $


function contact_admin_display() 
{
  $path = drupal_get_path('module', 'news');
 // drupal_add_css($path .'/my-admin.css', 'module', 'all', FALSE);


  $result = db_query("SELECT * FROM {contact} ORDER BY cid");
  $rows = array();
  while ($row = db_fetch_object($result)) {
    if($row->cid != 13){
    $rows[] = array(
      'data' => array(
        check_plain($row->contact_text),
        !$row->status ? l(t('enable'), 'admin/build/contact/'. $row->cid .'/enable') : l(t('disable'), 'admin/build/contact/'. $row->cid .'/disable'),
        l(t('configure'), 'admin/build/contact/'. $row->cid .'/configure'),
      ),
      'class' => $row->status ? 'enabled' : 'disabled',
    );
	}
  }

  $header = array(t('Contact Text') , t('Status'), array('data' => t('Operations'), 'colspan' => '2'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}


function image_admin_configure($form_state, $contact, $op = 'configure') {

  $form = array();
  $form['cid'] = array(
    '#type' => 'value',
    '#value' => $contact->cid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact Information'),
    '#collapsible' => TRUE,
  );
  $form['info']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Publish Text'),
    '#default_value' => $contact->status,
    '#description' => t('If this setting is enabled, the current news will display on main page'),
  );
    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['info']['document_upload'] = array(
      '#type' => 'file',
      '#title' => t('Select Contact Page Image'),
      '#required' => FALSE,
      '#description' => t('Click "Browse" to select a Image to upload.  The maximum file size per upload is %size MB.', array('%size' => round(file_upload_max_size()/(1024*1024), 0))),
      );
   // End of form


    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#validate' => array('contact_admin_cancel_validate'),
      '#submit' => array('contact_admin_cancel_submit'),
    );
  return $form;
}




function contact_admin_configure($form_state, $contact, $op = 'configure') {

  $form = array();
  $form['cid'] = array(
    '#type' => 'value',
    '#value' => $contact->cid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact Information'),
    '#collapsible' => TRUE,
  );
  $form['info']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Publish Text'),
    '#default_value' => $contact->status,
    '#description' => t('If this setting is enabled, the current news will display on main page'),
  );
  $form['info']['contact_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Contact Us Text'),
    '#default_value' => $contact->contact_text,
    '#description' => t('Enter Contact Us Text Here'),
    '#required' => TRUE,
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
      '#validate' => array('contact_admin_cancel_validate'),
      '#submit' => array('contact_admin_cancel_submit'),
    );
  }
  return $form;
}




function contact_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['contact_text'])) {
    form_set_error('contact_text', t('!field field is required.', array('!field' => $form['info']['contact_text']['#contact_text'])));
  }
}


function contact_admin_configure_submit($form, &$form_state) 
{
  // Save the edited my
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {

    $sql = "UPDATE {contact} SET";
    $sql .= " contact_text = '%s' , status = '%d'  ";
    $sql .= " WHERE cid = %d";
    db_query($sql,
      $form_state['values']['contact_text'],
	    $form_state['values']['status'],
      $form_state['values']['cid']
    );
    drupal_set_message(t('The Contact Text %name has been saved.', array('%name' => $form_state['values']['contact'])));
    $form_state['redirect'] = 'admin/build/contact';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/contact/'. $form_state['values']['cid'] .'/delete';
  }

  return;
}



function contact_admin_disable($contact) {
  db_query("UPDATE {contact} SET status = 0 WHERE cid = %d", $contact->cid);
  drupal_goto('admin/build/contact');
}


function contact_admin_enable($news) {
  db_query("UPDATE {contact} SET status = 1 WHERE cid = %d", $contact->cid);
  drupal_goto('admin/build/contact');
}

function contact_admin_cancel_validate($form, &$form_state) {
}

function contact_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/contact';
  return;
}





