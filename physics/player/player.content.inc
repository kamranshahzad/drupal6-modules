<?php


function player_vedio_display($id)
{
	$out = '';
	

	
	$result = db_query("SELECT * FROM {documents} WHERE did='$id' ");
	$row = db_fetch_object($result);
	
	
	$url = 'http://insuranceplanet.biz/client/physics/sites/default/files/';

	
	
	
	$flpath = 'sites/default/files';
	$playPath = drupal_get_path('module', 'player');
	
	
	
	$player = $playPath.'/playerfiles/player.swf';
    $flv = $url.$row->filename;

	//  Player Placement
	$out .= '<table width="874" border="0" cellspacing="0" cellpadding="0">';
    $out .= '<tr>';
    $out .= '<td height="40" align="left"><h1>Topic Name </h1></td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td align="center" class="txtgray12">&nbsp;</td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td align="center" class="txtgray12"><table width="100%" border="0" cellspacing="0" cellpadding="0">';
    $out .= '<tr>';
    $out .= '<td width="370" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">';
    $out .= '<tr>';
    $out .= '<td class="txtblue14"><strong>Description</strong></td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td>&nbsp;</td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td><p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer aliquam dictum fermentum. Aliquam in libero mi, quis accumsan quam. Integer quis eros felis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Ut id felis purus, nec rutrum nisl. Fusce a lacus a mauris ornare sagittis sed non elit. Nunc nisl quam, condimentum et lobortis eget, rhoncus euismod nunc. Cras venenatis posuere dui id dictum. Sed nulla neque, lobortis consectetur gravida auctor, sollicitudin ut ligula. Vivamus porta volutpat purus non posuere. Quisque sit amet orci et lacus aliquet faucibus eget pretium mi.</p>';
    $out .= '</td>';
    $out .= '</tr>';
    $out .= '</table></td>';
    $out .= '<td align="center">';
	$out .= "<script type='text/javascript' src='$playPath/playerfiles/swfobject.js'></script>
		<div id='content'>To view the Flash content, please enable JavaScript in your browser.</div>
		<script type='text/javascript'>
			var so = new SWFObject('$player', 'player', '328', '200', '9', '#000000');
			so.addParam('allowfullscreen','true');
			so.addParam('allowscriptaccess','always');
			so.addParam('flashvars','file=$flv');
			so.write('content');
		</script>";
	$out .= '</td>';
    $out .= '</tr>';
    $out .= '</table></td>';
    $out .= '</tr>';
    $out .= '</table>';

	return $out;	
}

function player_youtube_display($id)
{
	$out = '';
	

	
	$result = db_query("SELECT * FROM {documents} WHERE did='$id' ");
	$row = db_fetch_object($result);
	
/*	$flpath = 'sites/default/files';
	$playPath = drupal_get_path('module', 'player');
	
	
	
	$player = $playPath.'/playerfiles/player.swf';
    $flv = $url.$row->filename;*/

	//  Player Placement
	$out .= '<table width="874" border="0" cellspacing="0" cellpadding="0">';
    $out .= '<tr>';
    $out .= '<td height="40" align="left"><h1>Topic Name </h1></td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td align="center" class="txtgray12">&nbsp;</td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td align="center" class="txtgray12"><table width="100%" border="0" cellspacing="0" cellpadding="0">';
    $out .= '<tr>';
    $out .= '<td width="370" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">';
    $out .= '<tr>';
    $out .= '<td class="txtblue14"><strong>Description</strong></td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td>&nbsp;</td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td><p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer aliquam dictum fermentum. Aliquam in libero mi, quis accumsan quam. Integer quis eros felis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Ut id felis purus, nec rutrum nisl. Fusce a lacus a mauris ornare sagittis sed non elit. Nunc nisl quam, condimentum et lobortis eget, rhoncus euismod nunc. Cras venenatis posuere dui id dictum. Sed nulla neque, lobortis consectetur gravida auctor, sollicitudin ut ligula. Vivamus porta volutpat purus non posuere. Quisque sit amet orci et lacus aliquet faucibus eget pretium mi.</p>';
    $out .= '</td>';
    $out .= '</tr>';
    $out .= '</table></td>';
    $out .= '<td align="center">';
	$out .= get_youtube();//$row->ulink;
	$out .= '</td>';
    $out .= '</tr>';
    $out .= '</table></td>';
    $out .= '</tr>';
    $out .= '</table>';

	return $out;	
}

function get_youtube()
{
	$out = '';
	$out .= '<object width="425" height="344"><param name="movie" value="http://www.youtube.com/v/d3ayJ27RxU8&hl=en&fs=1&rel=0&color1=0x006699&color2=0x54abd6"></param><param name="allowFullScreen" value="true"></param><param name="allowscriptaccess" value="always"></param><embed src="http://www.youtube.com/v/d3ayJ27RxU8&hl=en&fs=1&rel=0&color1=0x006699&color2=0x54abd6" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width="425" height="344"></embed></object>';
	return $out;
}

/* Garbage Code */


	/*$out .= '<div class="descp">';
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
	$out .= '<div class="clear"></div>';*/

?>