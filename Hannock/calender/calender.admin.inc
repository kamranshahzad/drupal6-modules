<?php




function calender_configure($form_state, $cal, $op = 'configure') 
{


  $form = array();
  $form['cid'] = array(
    '#type' => 'value',
    '#value' => $cal->cid,
  );


  /*
  		Main Fields
  */
  $form['main'] = array(
    '#type' => 'fieldset',
    '#title' => t('School Calendar Year'),
    '#collapsible' => FALSE,
  );
  $form['main']['year'] = array(
    '#type' => 'textfield',
    '#title' => t('Year'),
    '#default_value' => $cal->year,
    '#description' => t('Enter the Year of School Calendar'),
    '#required' => TRUE,
    '#maxlength' => 255,
  );
  
  /*
  		Autumn Term 
  */
  
    $form['aut'] = array(
    '#type' => 'fieldset',
    '#title' => t('Autumn Term'),
    '#collapsible' => FALSE,
  );
   $form['aut']['ayear'] = array(
    '#type' => 'textfield',
    '#title' => t('Year'),
    '#default_value' => $cal->ayear,
    '#description' => t(''),
    '#maxlength' => 255,
  );
   $form['aut']['areturn1'] = array(
    '#type' => 'textfield',
    '#title' => t('Return'),
    '#default_value' => $cal->areturn1,
    '#description' => t('Enter Return Text'),
    '#maxlength' => 255,
  );
     $form['aut']['areturn2'] = array(
    '#type' => 'textfield',
    '#title' => t('Return-2'),
    '#default_value' => $cal->areturn2,
    '#description' => t('Non-pupil Day(Staff training)'),
    '#maxlength' => 255,
  );
     $form['aut']['ahalf1'] = array(
    '#type' => 'textfield',
    '#title' => t('Half Term'),
    '#default_value' => $cal->ahalf1,
    '#description' => t(''),
    '#maxlength' => 255,
  );
     $form['aut']['ahalf2'] = array(
    '#type' => 'textfield',
    '#title' => t('Half Term - 2'),
    '#default_value' => $cal->ahalf2,
    '#description' => t('Non-pupil Day(Staff training)'),
    '#maxlength' => 255,
  );
     $form['aut']['alast1'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Day'),
    '#default_value' => $cal->alast1,
    '#description' => t('Enter Last Day'),
    '#maxlength' => 255,
  );
   $form['aut']['alast2'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Day - 2'),
    '#default_value' => $cal->alast2,
    '#description' => t('Non-pupil Day(Staff training)'),
    '#maxlength' => 255,
  );
  
  
    /*
  		Spring Terms
  */
  
   $form['spring'] = array(
    '#type' => 'fieldset',
    '#title' => t('Spring Term'),
    '#collapsible' => FALSE,
  );
   $form['spring']['syear'] = array(
    '#type' => 'textfield',
    '#title' => t('Year'),
    '#default_value' => $cal->syear,
    '#description' => t('Enter the Year of Spring Term'),
    '#maxlength' => 255,
  );
   $form['spring']['sreturn1'] = array(
    '#type' => 'textfield',
    '#title' => t('Return - 1'),
    '#default_value' => $cal->sreturn1,
    '#description' => t('Enter Return Date'),
    '#maxlength' => 255,
  );
     $form['spring']['sreturn2'] = array(
    '#type' => 'textfield',
    '#title' => t('Return - 2'),
    '#default_value' => $cal->sreturn2,
    '#description' => t('Non-pupil Day(Staff training)'),
    '#maxlength' => 255,
  );
     $form['spring']['shalf1'] = array(
    '#type' => 'textfield',
    '#title' => t('Half Term - 1'),
    '#default_value' => $cal->shalf1,
    '#description' => t('Enter the Half Term Date'),
    '#maxlength' => 255,
  );
     $form['spring']['shalf2'] = array(
    '#type' => 'textfield',
    '#title' => t('Half Term - 2'),
    '#default_value' => $cal->shalf2,
    '#description' => t('Non-pupil Day(Staff training)'),
    '#maxlength' => 255,
  );
     $form['spring']['slast1'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Day'),
    '#default_value' => $cal->slast1,
    '#description' => t('Enter Last Day'),
    '#maxlength' => 255,
  );
   $form['spring']['slast2'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Day - 2'),
    '#default_value' => $cal->slast2,
    '#description' => t('Enter 2nd Last Day'),
    '#maxlength' => 255,
  );
  
  /*
  		Summer Term
  */
  
   $form['summer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Summer Term'),
    '#collapsible' => FALSE,
  );
   $form['summer']['myear'] = array(
    '#type' => 'textfield',
    '#title' => t('Year'),
    '#default_value' => $cal->myear,
    '#description' => t('Enter the Year of School Calendar'),
    '#maxlength' => 255,
  );
   $form['summer']['mreturn1'] = array(
    '#type' => 'textfield',
    '#title' => t('Return'),
    '#default_value' => $cal->mreturn1,
    '#description' => t('Enter the Year of School Calendar'),
    '#maxlength' => 255,
  );
     $form['summer']['mreturn2'] = array(
    '#type' => 'textfield',
    '#title' => t('Return - 2'),
    '#default_value' => $cal->mreturn2,
    '#description' => t('Non-pupil Day(Staff training)'),
    '#maxlength' => 255,
  );
       $form['summer']['mholy1'] = array(
    '#type' => 'textfield',
    '#title' => t('Holidays - 1'),
    '#default_value' => $cal->mholy1,
    '#description' => t('Enter the Holidays'),
    '#maxlength' => 255,
  );
       $form['summer']['mholy2'] = array(
    '#type' => 'textfield',
    '#title' => t('Holidays - 1'),
    '#default_value' => $cal->mholy2,
    '#description' => t('Enter the 2nd Holidays'),
    '#maxlength' => 255,
  );
     $form['summer']['mhalf1'] = array(
    '#type' => 'textfield',
    '#title' => t('Half Term'),
    '#default_value' => $cal->mhalf1,
    '#description' => t('Enter Half-Term'),
    '#maxlength' => 255,
  );
     $form['summer']['mhalf2'] = array(
    '#type' => 'textfield',
    '#title' => t('Half Term - 2'),
    '#default_value' => $cal->mhalf2,
    '#description' => t('Enter 2nd Half-Term'),
    '#maxlength' => 255,
  );
     $form['summer']['mlast1'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Day'),
    '#default_value' => $cal->mlast1,
    '#description' => t('Enter Last Day'),
    '#maxlength' => 255,
  );
   $form['summer']['mlast2'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Day - 2'),
    '#default_value' => $cal->mlast2,
    '#description' => t('Enter 2nd Last Day '),
    '#maxlength' => 255,
  );
   

  
  
   $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
   );

  return $form;
}

function  calender_configure_validate($form, &$form_state) {

}

function calender_configure_submit($form, &$form_state) 
{
    $sql = "UPDATE {calender} SET";
	$sql .= " year= '%s',	ayear= '%s',areturn1= '%s',areturn2= '%s',ahalf1= '%s',ahalf2= '%s',alast1= '%s',alast2= '%s' , ";
    $sql .= "syear= '%s',sreturn1= '%s',sreturn2= '%s',shalf1= '%s',shalf2= '%s',slast1= '%s',slast2= '%s', ";
	$sql .= "myear= '%s',mreturn1= '%s',mreturn2= '%s',mholy1= '%s',mholy2= '%s',mhalf1= '%s',mhalf2= '%s',mlast1= '%s',mlast2= '%s'";
    $sql .= " WHERE cid = %d";
    db_query($sql,
      $form_state['values']['year'],$form_state['values']['ayear'],$form_state['values']['areturn1'],$form_state['values']['areturn2'],$form_state['values']['ahalf1'],$form_state['values']['ahalf2'],$form_state['values']['alast1'],$form_state['values']['alast2'],
	  $form_state['values']['syear'],$form_state['values']['sreturn1'],$form_state['values']['sreturn2'],$form_state['values']['shalf1'],$form_state['values']['shalf2'],$form_state['values']['slast1'],$form_state['values']['slast2'],
	  $form_state['values']['myear'],$form_state['values']['mreturn1'],$form_state['values']['mreturn2'],$form_state['values']['mholy1'],$form_state['values']['mholy2'],$form_state['values']['mhalf1'],$form_state['values']['mhalf2'],$form_state['values']['mlast1'],$form_state['values']['mlast2'],
      $form_state['values']['cid']
    );
    drupal_set_message(t('The School Calendar has been saved.'));
    $form_state['redirect'] = 'admin/build/1/configure';
  	return;
}