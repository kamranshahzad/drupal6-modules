<?php


function player_audio_display($id)
{

	

	
	$result = db_query("SELECT * FROM {audioplay} WHERE aid='$id' ");
	
	
	
	$url = 'http://hennock-primary.devon.sch.uk/site2/sites/default/files/';
	
	
	$flpath = 'sites/default/files';
	$playPath = drupal_get_path('module', 'audio');

	
	$output = '';
	
	$output .= '<script language="JavaScript" src="http://hennock-primary.devon.sch.uk/site2/sites/all/modules/audiocast/audio.js"></script>';
	
	$url =  drupal_get_path('module', 'audio') .'/players/1pixelout.swf';
	
	
	
	
	$pid = 1;
	$row = db_fetch_object($result);
		$adfile =  $row->filename;
		$output .= '<div class="descp">';
		$output .= '<div class="title">'.$row->title.'</div>';
		$output .= '<div class="txt">';
		$output .= '<p>'.$row->des.'</p>';
		//$output .= '<a href="#">Download Links</a>';
		$output .= '</div>';
		$output .= '</div>';
		$output .= '<div class="player">';
		
		$output .= '<object type="application/x-shockwave-flash" data="'.$url.'" width="290" height="24" >';
		$output .= '<param name="movie" value="'.$url.'" />';
		$output .= '<param name="wmode" value="transparent" />';
		$output .= '<param name="menu" value="false" />';
		$output .= '<param name="quality" value="high" />';
		$output .= '<param name="FlashVars" value="playerID='.$pid.'&amp;soundFile=http://hennock-primary.devon.sch.uk/site2/sites/default/files/'.$adfile.'" />';
		$output .= '<embed src="'.$url.'" flashvars="playerID='.$pid.'&amp;soundFile=http://hennock-primary.devon.sch.uk/site2/sites/default/files/'.$adfile.'" width="290" height="24" wmode="transparent" />';
		$output .= '</object>';
		$output .='</div>';
		$output .= '<div class="clear"></div><br>';
	
	return $output;
	
}


?>