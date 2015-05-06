<?php
// $Id: my.admin.inc,v 1.5 2009/01/11 13:49:11 kirie Exp $



function staff_content_display()
{
	$mdpath = drupal_get_path('module', 'staff');
  	drupal_add_css($path .'/css/staff.css');
	
	$result = db_query("SELECT * FROM {staff} WHERE type='0'");
	$out = '';
	
	$out .= '<div class="aboutstaffContainer">';
	$out .= ' <div class="head"><img src="'.$mdpath.'/images/about-staff.jpg" width="202" height="55" alt="" /></div>';
	$out .= '<div class="table">';
	$out .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">';
	$out .= '<tr><td bgcolor="#D6E2F8">';
	while ($row = db_fetch_object($result))  
	{
		
		if($counter == 0)
		{
			$out .= '<table width="900" border="0" cellspacing="1" cellpadding="5">';
			$out .= '<tr>';
		}
		   $out .= '<td width="300" valign="top" bgcolor="#FFFFFF">';
           $out .= '<table width="300" border="0" cellspacing="0" cellpadding="4">';
		   $out .= '<tr>';
			 $out .= '<td bgcolor="#DFEBFF" class="txtblue14"><strong>'.$row->name.'</strong>';
			   $out .= '</td>';
		   $out .= '</tr>';
		   $out .= '<tr>';
			 $out .= '<td><img src="'.getImageName($row->image).'" width="120" height="120" align="right" />'.$row->des.'</td>';
		   $out .= '</tr>';
           $out .= '</table>';
           $out .= '</td>';
		   
		$counter++;
		if($counter == 3)
		{
			$out .= '</tr>';
			$out .= '</table>';
			$counter = 0;
		}
		
	}
	$out .= '</td></tr></table></td></tr></table> </div></div>';
	return $out;
}

function governors_content_display()
{
  	$mdpath = drupal_get_path('module', 'staff');
  	drupal_add_css($path .'/css/staff.css');
	
	$result = db_query("SELECT * FROM {staff} WHERE type='1'");
	$out = '';
	
	$out .= '<div class="aboutstaffContainer">';
	$out .= ' <div class="head"><img src="'.$mdpath.'/images/about-governors.jpg" width="255" height="45" alt="" /></div>';
	$out .= '<div class="table">';
	$out .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">';
	$out .= '<tr><td bgcolor="#D6E2F8">';
	while ($row = db_fetch_object($result))  
	{
		
		if($counter == 0)
		{
			$out .= '<table width="900" border="0" cellspacing="1" cellpadding="5">';
			$out .= '<tr>';
		}
		   $out .= '<td width="300" valign="top" bgcolor="#FFFFFF">';
           $out .= '<table width="300" border="0" cellspacing="0" cellpadding="4">';
		   $out .= '<tr>';
			 $out .= '<td bgcolor="#DFEBFF" class="txtblue14"><strong>'.$row->name.'</strong>';
			   $out .= '</td>';
		   $out .= '</tr>';
		   $out .= '<tr>';
			 $out .= '<td><img src="'.getImageName($row->image).'" width="120" height="120" align="right" />'.$row->des.'</td>';
		   $out .= '</tr>';
           $out .= '</table>';
           $out .= '</td>';
		   
		$counter++;
		if($counter == 3)
		{
			$out .= '</tr>';
			$out .= '</table>';
			$counter = 0;
		}
		
	}
	$out .= '</td></tr></table></td></tr></table> </div></div>';
	return $out;
}

function  getImageName($name)
{
	$img = '';
	$mdpath = drupal_get_path('module', 'staff');
	$flpath = 'sites/default/files/';
	if($name == 'default-img.jpg')
	{
		$img =  $mdpath .'/images/default-img.jpg';
	}
	else
	{
		$img = $flpath.$name;
	}
	return $img;
}