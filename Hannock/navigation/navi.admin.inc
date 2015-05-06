<?php

/*
	Admin Tasks 
*/


function navigation_admin_display() 
{
  $path = drupal_get_path('module', 'news');
  $result = db_query("SELECT * FROM {navigation} ORDER BY nid");
  $rows = array();
  while ($row = db_fetch_object($result)) 
  {
    $rows[] = array(
      'data' => array(
        check_plain($row->title),
		check_plain($row->direction),
		check_plain($row->des),
		check_plain($row->path),
        !$row->status ? l(t('enable'), 'admin/build/navigation/'. $row->nid .'/enable') : l(t('disable'), 'admin/build/navigation/'. $row->nid .'/disable'),
        l(t('configure'), 'admin/build/navigation/'. $row->nid .'/configure'),
        l(t('delete'), 'admin/build/navigation/'. $row->nid .'/delete'),
      ),
    );
  }

  $header = array(t('Menu Title'),t('Direction'),t('Menu Description') , t('Path'), array('data' => t('Operations'), 'colspan' => '3'));

  return theme('table', $header, $rows, $attributes = array('class' => 'my-admin-list'), NULL);
}



/*
	Form of Navigation Menu
*/
function navigation_admin_configure($form_state, $nav , $op = 'configure') 
{

  $form = array();
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $nav->nid,
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
    '#default_value' => $nav->status,
    '#description' => t('If this setting is enabled, the current Menu will display on page'),
  );
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Navigation Menu Title'),
    '#default_value' => $nav->title,
    '#description' => t('Enter Title of Navigation Menu'),
    '#required' => TRUE,
    '#maxlength' => 256,
  );
    $form['info']['external'] = array(
    '#type' => 'checkbox',
    '#title' => t('make external this link (by default link is internal)'),
    '#default_value' => $links->external,
    '#description' => t('If this setting is enabled, the current Menu will display on page'),
  );
  $form['info']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu Navigation Path'),
    '#default_value' => $nav->path,
    '#description' => t('Enter Navigation Path'),
    '#required' => TRUE,
    '#maxlength' => 256,
  );
  $form['info']['dir'] = array(
    '#type' => 'select',
    '#title' => t('Menu Direction'),
	'#options' => array(
    		'left' => t('Left Side'),
    		'right' => t('Right Side'),
  	 ),
    '#description' => t('Enter Menu Diection'),
    '#required' => TRUE,
  );
  $form['info']['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Menu Description'),
    '#default_value' => $nav->des,
    '#description' => t('Enter Navigation Menu Path'),
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
      '#validate' => array('navigation_admin_cancel_validate'),
      '#submit' => array('navigation_admin_cancel_submit'),
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
      '#submit' => array('navigation_admin_add_submit'),
    );
  }
  return $form;
}




function navigation_admin_configure_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('!field field is required.', array('!field' => $form['info']['title']['#title'])));
  }
}

function navigation_admin_configure_submit($form, &$form_state) 
{
  if (!form_get_errors() && $form_state['clicked_button']['#value'] == t('Save')) {

    $sql = "UPDATE {navigation} SET";
    $sql .= " title = '%s' , des = '%s' , path ='%s' , direction='%s' ,status = '%d'  , external ='%d' ";
    $sql .= " WHERE nid = %d";
    db_query($sql,
      $form_state['values']['title'],
      $form_state['values']['des'],
	   $form_state['values']['path'],
	   $form_state['values']['dir'],
	    $form_state['values']['status'],
		 $form_state['values']['external'],
      $form_state['values']['nid']
    );
    drupal_set_message(t('The Menu %name has been saved.', array('%name' => $form_state['values']['title'])));
    $form_state['redirect'] = 'admin/build/navigation';
  }
  else if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/build/navigation/'. $form_state['values']['nid'] .'/delete';
  }

  return;
}

/**
 * Save the new my.
 */
function navigation_admin_add_submit($form, &$form_state) {

  $sql = "INSERT INTO {navigation} (title, path , des , direction , status , external)";
  $sql .= " VALUES ('%s', '%s' , '%s' ,'%s','%d' , '%d')";

  db_query($sql,
   $form_state['values']['title'],
      $form_state['values']['path'],
	   $form_state['values']['des'],
	   $form_state['values']['dir'],
	    $form_state['values']['status'],
		 $form_state['values']['external']
  );
  drupal_set_message(t('The Menu %title has been created.', array('%title' => $form_state['values']['title'])));
  $form_state['redirect'] = 'admin/build/navigation';
  return;
}

/**
 * Menu callback: disable a specific my.
 */
function navigation_admin_disable($nav) {
  db_query("UPDATE {navigation} SET status = 0 WHERE nid = %d", $nav->nid);
  drupal_goto('admin/build/navigation');
}

/**
 * Menu callback: enable a specific my.
 */
function navigation_admin_enable($nav) {
  db_query("UPDATE {navigation} SET status = 1 WHERE nid = %d", $nav->nid);
  drupal_goto('admin/build/navigation');
}

function navigation_admin_cancel_validate($form, &$form_state) {
}

function navigation_admin_cancel_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/navigation';
  return;
}

/**
 * Menu callback; confirm deletion of a my.
 */
function navigation_admin_delete($form_state, $nav) {
  $form['nav'] = array('#type' => 'hidden', '#value' => serialize($nav));
  $params = array('%title' => $nav->title);
  return confirm_form($form, t('Are you sure you want to delete the Menu %title?', $params), 'admin/build/navigation', '', t('Delete'), t('Cancel'));
}



function navigation_admin_delete_submit($form, &$form_state) {
  $nav = unserialize($form_state['values']['nav']);
  db_query('DELETE FROM {navigation} WHERE nid = %d', $nav->nid);
  drupal_set_message(t('The Menu %title has been removed.', array('%title' => $nav->title)));
  $form_state['redirect'] = 'admin/build/navigation';
  return;
}
