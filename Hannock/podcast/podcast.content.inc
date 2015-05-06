<?php

function podcast_list_display($id)
{
	
	$flpath = 'sites/default/files/';
	
	$out = '';
	$out .= '<h1>Welcome</h1>';
	
	return $out;
}


function podcast_main_display()
{
	$flpath = 'sites/default/files/';
	$playPath = drupal_get_path('module', 'podcast');
	$path = 'http://localhost/erp/'.drupal_get_path('module', 'podcast');
	//$jsPath = $path.'/js/';
	drupal_add_js($path.'/swfobject.js');
		
		
	$out = '';
	$out .= '<h1>Welcome</h1>';
/*	$out .= '<script type="text/javascript">';
	$out .= 'swfobject.registerObject("player","9.0.98","'.$path.'/expressInstall.swf");';
	$out .= '</script>';*/
    
   /* $out .= '<object id="player" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" name="player" width="328" height="200">';
	$out .= '<param name="movie" value="'.$playPath.'/player.swf" />';
	$out .= '<param name="allowfullscreen" value="true" />';
		$out .= '<param name="allowscriptaccess" value="always" />';
		$out .= '<param name="flashvars" value="file='.$path.'/video.flv&image='.$path.'/preview.jpg" />';
		$out .= '<object type="application/x-shockwave-flash" data="'.$path.'/player.swf" width="328" height="200">';
			$out .= '<param name="movie" value="'.$playPath.'/player.swf" />';
			$out .= '<param name="allowfullscreen" value="true" />';
			$out .= '<param name="allowscriptaccess" value="always" />';
			$out .= '<param name="flashvars" value="file='.$path.'/video.flv&image='.$path.'preview.jpg" />';
			$out .= '<p><a href="http://get.adobe.com/flashplayer">Get Flash</a> to see this player.</p>';
		$out .= '</object>';
	$out .= '</object>';*/
	
	return $out;
}

?>