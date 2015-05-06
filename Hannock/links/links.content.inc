<?php


function links_list_display()
{
	$out = '';
	
	$themepath = drupal_get_path('theme', 'hannock');
	$imagepath = 'sites/default/files/';
	
	$result1 = db_query("SELECT * FROM {links} WHERE status ='1' AND cat='0' "); // Hennock School Links
	$result2 = db_query("SELECT * FROM {links} WHERE status ='1' AND cat='1' "); // Pre-School Links
	$result3 = db_query("SELECT * FROM {links} WHERE status ='1' AND cat='2' "); // Kids Corner Links
	
	/*$out .= '<div class="linkContainer">';
	$out .= '<div class="head"><img src="'.$themepath.'/images/hannock-links.jpg" width="321" height="43" alt="" /></div>'; 
	
	
	$out .= '<div class="logosContainer">';
	
	
	$out .= '<table width="800" border="0" cellspacing="0" cellpadding="0">';
	$counter1 = 0;
	while ($row = db_fetch_object($result1)) 
	{
		if($counter1 == 0)
		{
			$out .= '<tr>';
		}
		$out .= '<td width="150" valign="bottom">';
    	$out .= '<ul>';
    	$out .= '<li>';
		if(strlen($row->logofile) > 0)
		{
			$out .= '<li><img src="'.$imagepath.$row->logofile.'" width="120" height="58" alt="" /></li>';
		}
		$out .='</li>';
        $out .= '<li>';
		if($row->external == 0){
			$out .= '<li>'.l($row->path,$row->title).'</li>';
		}
		else
		{	
			$out .= '<li><a href="'.$row->path.'" target="_blank">'.$row->title.'</a></li>';
		}
		$out .= '</li>';
    	$out .= '</ul>';
    	$out .= '</td>';
		
		$counter1++;
		if($counter1 == 3)
		{
			$out .= '</tr>';
			$counter1 = 0;
		}
		
	}
	$out .= '</table>';
	$out .= '<div class="clear"></div>';
	$out .= '</div>';
	
	
	$out .= '<div class="head"><img src="'.$themepath.'/images/preschool-links.jpg" width="226" height="44" alt="" /></div>';
	$out .= '<div class="logosContainer">';
	
	$out .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">';
	$counter = 0;

*/	
	
	
	
	
	///////////////////////////////
	$out .= '<div class="linkContainer">';
	$out .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">';
    $out .= '<tr>';
    $out .= '<td><table width="968" border="0" cellspacing="1" cellpadding="8">';
    $out .= '<tr>';
    $out .= '<td width="305" align="center"><span class="head"><img src="'.$themepath.'/images/hannock-links.jpg" width="190" height="44" alt="" /></span></td>';
    $out .= '<td width="305" align="center"><span class="head"><img src="'.$themepath.'/images/preschool-links.jpg" width="226" height="44" alt="" /></span></td>';
    $out .= '<td width="306" align="center"><span class="head"><img src="'.$themepath.'/images/kids-corner.jpg" width="175" height="42" alt="" /></span></td>';
    $out .= '</tr>';
    $out .= '</table></td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td bgcolor="#BDD3FA">';
	  
	  
	$out .= '<table width="100%" border="0" cellspacing="1" cellpadding="8">';
	
	//Con
	
    $out .= '<tr>';
	$out .= '<td width="305" align="center" bgcolor="#FFFFFF" valign="top">';
	//inner table #1 
	$out .= '<table>';
	while ($row = db_fetch_object($result1)) 
	{
			$out .= '<tr><td>';
			if(strlen($row->logofile) > 0)
			{
				$out .= '<img src="'.$imagepath.$row->logofile.'" width="120" height="58" alt="" />';
			}
			$out .= '<br />';
			$out .= '<br />';
			if($row->external == 0){
				$out .= l($row->path,$row->title);
			}
			else
			{	
				$out .= '<a href="'.$row->path.'" target="_blank">'.$row->title.'</a>';
			}
			$out .= '</tr></td>';
	}
	$out .= '</table>';
    //
	$out .= '</td>';
	
	
	$out .= '<td width="305" align="center" bgcolor="#FFFFFF" valign="top">';
	//inner table #2 
	$out .= '<table>';
	while ($row = db_fetch_object($result2)) 
	{
			$out .= '<tr><td>';
			if(strlen($row->logofile) > 0)
			{
				$out .= '<img src="'.$imagepath.$row->logofile.'" width="120" height="58" alt="" />';
			}
			$out .= '<br />';
			$out .= '<br />';
			if($row->external == 0){
				$out .= l($row->path,$row->title);
			}
			else
			{	
				$out .= '<a href="'.$row->path.'" target="_blank">'.$row->title.'</a>';
			}
			$out .= '</tr></td>';
	}
	$out .= '</table>';
    //
	$out .= '</td>';
	$out .= '<td width="305" align="center" bgcolor="#FFFFFF" valign="top">';
	//inner table #3 
	$out .= '<table>';
	while ($row = db_fetch_object($result3)) 
	{
			$out .= '<tr><td>';
			if(strlen($row->logofile) > 0)
			{
				$out .= '<img src="'.$imagepath.$row->logofile.'" width="120" height="58" alt="" />';
			}
			$out .= '<br />';
			$out .= '<br />';
			if($row->external == 0){
				$out .= l($row->path,$row->title);
			}
			else
			{	
				$out .= '<a href="'.$row->path.'" target="_blank">'.$row->title.'</a>';
			}
			$out .= '</tr></td>';
	}
	$out .= '</table>';
    //
	$out .= '</td>';
	
	$out .= '</tr>';
	
	// Ends 
	$out .= '</table>';
    $out .= '</td>';
    $out .= '</tr>';
    $out .= '<tr>';
    $out .= '<td>&nbsp;</td>';
    $out .= '</tr>';
  	$out .= '</table>';
	
	$out .= '</div>';
	
	
	return $out;	
}


?>