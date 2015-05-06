<?php


function newsticker_display() 
{
  $path = drupal_get_path('module', 'newsticker');


  $result = db_query("SELECT * FROM {newsticker} ORDER BY nid");
  $rows = array();
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->des),
        !$row->status ? l(t('enable'), 'admin/build/newsticker/'. $row->nid .'/enable') : l(t('disable'), 'admin/build/newsticker/'. $row->nid .'/disable'),
        l(t('configure'), 'admin/build/newsticker/'. $row->nid .'/configure'),
        l(t('delete'), 'admin/build/newsticker/'. $row->nid .'/delete'),
      ),
      'class' => $row->status ? 'enabled' : 'disabled',
    );
  }

  $header = array(t('Title of News'),t('Description of News') , array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}


function newsticker_configure($form_state, $news, $op = 'configure') 
{

  $form = array();
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $news->nid,
  );

  // Info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('News Information'),
    '#collapsible' => TRUE,
  );
  $form['info']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Publish News'),
    '#default_value' => $news->status,
    '#description' => t('If this setting is enabled, the current news will display on main page'),
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('News Title'),
    '#default_value' => $news->title,
    '#description' => t('Enter Title of News'),
    '#required' => TRUE,
    '#maxlength' => 256,
  );
  $form['info']['des'] = array(
    '#type' => 'textfield',
    '#title' => t('News Description'),
    '#default_value' => $news->des,
    '#description' => t('Enter News Description'),
    '#required' => TRUE,
    '#maxlength' => 256,
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
      '#validate' => array('newsticker_cancel_validate'),
      '#submit' => array('newsticker_cancel_submit'),
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
      '#submit' => array('newsticker_add_submit'),
    );
  }
  return $form;
}




function newsticker_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('!field field is required.', array('!field' => $form['info']['title']['#title'])));
  }
}

function newsticker_configure_submit($form, &$form_state) 
{

  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {

    $sql = "UPDATE {newsticker} SET";
    $sql .= " title = '%s' , des = '%s' , status = '%d'  ";
    $sql .= " WHERE nid = %d";
    db_query($sql,
      $form_state['values']['title'],
      $form_state['values']['des'],
	    $form_state['values']['status'],
      $form_state['values']['nid']
    );
    drupal_set_message(t('The News %name has been saved.', array('%name' => $form_state['values']['title'])));
    $form_state['redirect'] = 'admin/build/newsticker';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/newsticker/'. $form_state['values']['nid'] .'/delete';
  }

  return;
}


function newsticker_add_submit($form, &$form_state) {

  $sql = "INSERT INTO {newsticker} (title, des , status )";
  $sql .= " VALUES ('%s', '%s' ,'%d')";

  db_query($sql,
   $form_state['values']['title'],
      $form_state['values']['des'],
	    $form_state['values']['status']
  );
  drupal_set_message(t('The News %title has been created.', array('%title' => $form_state['values']['title'])));
  $form_state['redirect'] = 'admin/build/newsticker';
  return;
}


function newsticker_disable($news) {
  db_query("UPDATE {newsticker} SET status = 0 WHERE nid = %d", $news->nid);
  drupal_goto('admin/build/newsticker');
}


function newsticker_enable($news) {
  db_query("UPDATE {newsticker} SET status = 1 WHERE nid = %d", $news->nid);
  drupal_goto('admin/build/newsticker');
}

function newsticker_cancel_validate($form, &$form_state) {
}

function newsticker_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/newsticker';
  return;
}



function newsticker_delete($form_state, $news) {
  $form['news'] = array('#type' => 'hidden', '#value' => serialize($news));
  $params = array('%title' => $news->title);
  return confirm_form($form, t('Are you sure you want to delete the News %title?', $params), 'admin/build/newsticker', '', t('Delete'), t('Cancel'));
}



function newsticker_delete_submit($form, &$form_state) {
  $news = unserialize($form_state['values']['news']);
  db_query('DELETE FROM {newsticker} WHERE newsid = %d', $news->nid);
  drupal_set_message(t('The News %title has been removed.', array('%title' => $news->title)));
  $form_state['redirect'] = 'admin/build/newsticker';
  return;
}
