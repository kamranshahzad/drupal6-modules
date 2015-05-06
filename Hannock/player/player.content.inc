<?php


function player_vedio_display($id)
{
	$out = '';
	

	
	$result = db_query("SELECT * FROM {vedioplay} WHERE vid='$id' ");
	$row = db_fetch_object($result);
	
	
	$url = 'http://hennock-primary.devon.sch.uk/site2/sites/default/files/';
	
	
	$flpath = 'sites/default/files';
	$playPath = drupal_get_path('module', 'player');
	
	
	
	$player = $playPath.'/playerfiles/player.swf';
    $flv = $url.$row->filename;



	$out .= '<div class="descp">';
	$out .= '<div class="title">'.$row->title.'</div>';
	$out .= '<div class="txt">';
  	$out .= '<p>'.$row->des.'</p>';
	$out .= '</div>';
	$out .= '</div>';
	$out .= '<div class="player">';
	$out .= "<script type='text/javascript' src='$playPath/playerfiles/swfobject.js'></script>
		<div id='content'>To view the Flash content, please enable JavaScript in your browser.</div>
		<script type='text/javascript'>
			var so = new SWFObject('$player', 'player', '328', '200', '9', '#000000');
			so.addParam('allowfullscreen','true');
			so.addParam('allowscriptaccess','always');
			so.addParam('flashvars','file=$flv');
			so.write('content');
		</script>";
	$out .='</div>';
	$out .= '<div class="clear"></div>';
	
	return $out;	
}


?>