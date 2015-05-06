<?php


function calender_html()
{
		$path = drupal_get_path('module', 'calender').'/images/';
		
		$result = db_query("SELECT * FROM {calender}");
		$row = db_fetch_object($result);
		
		/*  Autumn Term  */
		$out = '';
		$out .= '<div class="calenderContainer">';
		$out .= '<div class="head"><img src="'.$path.'school-calendar-head.gif" height="31" width="199" alt="" /><br />';
  		$out .= '<span class="heading2">'.$row->year.'</span> </div>';
		$out .= '<div>';
  		$out .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">';
    	$out .= '<tr>';
      	$out .= '<td bgcolor="#CDECFF"><table width="936" border="0" cellspacing="1" cellpadding="10">';
        $out .= '<tr>';
        $out .= '<td width="596" bgcolor="#FFFFFF" class="heading1">Autumn Term '.$row->ayear.'</td>';
        $out .= '<td width="297" align="center" bgcolor="#FFFFFF" class="heading1">Non-pupil Day<br />(Staff training)</td>';
        $out .= '</tr>';
      	$out .= '</table></td></tr><tr>';
      	$out .= '<td bgcolor="#CDECFF"><table width="936" border="0" cellspacing="1" cellpadding="10">';
        $out .= '<tr>';
        $out .= '<td width="287" bgcolor="#EFF9FF" class="txtblue14">Return<br /></td>';
        $out .= '<td width="288" bgcolor="#EFF9FF" class="txtred">'.$row->areturn1.'</td>';
        $out .= '<td width="297" align="center" bgcolor="#EFF9FF" class="txtblue14">'.$row->areturn2.'</td>';
        $out .= '</tr><tr>';
        $out .= '<td bgcolor="#FFFFFF" class="txtblue14">Half Term</td>';
        $out .= '<td bgcolor="#FFFFFF" class="txtyellow">'.$row->ahalf1.'</td>';
        $out .= '<td bgcolor="#FFFFFF" class="txtblue14" align="center">'.$row->ahalf2.'</td>';
        $out .= '</tr><tr>';
        $out .= '<td bgcolor="#EFF9FF" class="txtblue14">Last Day</td>';
        $out .= '<td bgcolor="#EFF9FF" class="txtpurple">'.$row->alast1.'</td>';
        $out .= '<td bgcolor="#EFF9FF" align="center" class="txtblue14">'.$row->alast2.'</td></tr></table></td></tr><tr>';
      	$out .= '<td bgcolor="#CDECFF"><table width="936" border="0" cellspacing="1" cellpadding="10">';
        $out .= '<tr>';
		
		
		/*  Spring Term  */
        $out .= '<td height="48" bgcolor="#FFFFFF" class="heading1">Spring Term '.$row->syear.'</td>';
        $out .= '</tr>';
      	$out .= '</table></td></tr><tr>';
      	$out .= '<td bgcolor="#CDECFF"><table width="936" border="0" cellspacing="1" cellpadding="10">';
        $out .= '<tr>';
        $out .= '<td width="287" bgcolor="#EFF9FF" class="txtblue14">Return<br /></td>';
        $out .= '<td width="288" bgcolor="#EFF9FF" class="txtred">'.$row->sreturn1.'</td>';
        $out .= '<td width="297" align="center" bgcolor="#EFF9FF" class="txtblue14">'.$row->sreturn2.' </td>';
        $out .= '</tr><tr><td bgcolor="#FFFFFF" class="txtblue14">Half Term</td>';
        $out .= '<td bgcolor="#FFFFFF" class="txtyellow">'.$row->shalf1.'</td>';
        $out .= '<td bgcolor="#FFFFFF" class="txtblue14" align="center">'.$row->shalf2.'</td>';
        $out .= '</tr><tr>';
        $out .= '<td bgcolor="#EFF9FF" class="txtblue14">Last Day</td>';
        $out .= '<td bgcolor="#EFF9FF" class="txtpurple">'.$row->slast1.'</td>';
        $out .= '<td bgcolor="#EFF9FF" class="txtblue14" align="center">'.$row->slast2.'</td>';
        $out .= '</tr></table></td></tr><tr>';
      	$out .= '<td bgcolor="#CDECFF"><table width="936" border="0" cellspacing="1" cellpadding="10">';
        $out .= '<tr>';
		
		
		/*  Summer Term  */
        $out .= '<td height="48" bgcolor="#FFFFFF" class="heading1">Summer Term '.$row->myear.'</td>';
        $out .= '</tr></table></td></tr><tr>';
      	$out .= '<td bgcolor="#CDECFF"><table width="936" border="0" cellspacing="1" cellpadding="10">';
        $out .= '<tr>';
        $out .= '<td width="287" bgcolor="#EFF9FF" class="txtblue14">Return<br /></td>';
        $out .= '<td width="288" bgcolor="#EFF9FF" class="txtred">'.$row->mreturn1.' </td>';
        $out .= '<td width="297" align="center" bgcolor="#EFF9FF" class="txtblue14">'.$row->mreturn2.' </td>';
        $out .= '</tr>';
        $out .= '<tr>';
        $out .= '<td bgcolor="#FFFFFF" class="txtblue14">Bank Holiday </td>';
        $out .= '<td bgcolor="#FFFFFF" class="txtblack">'.$row->mholy1.'</td>';
        $out .= '<td bgcolor="#FFFFFF" class="txtblue14" align="center">'.$row->mholy1.'</td>';
        $out .= '</tr><tr>';
        $out .= '<td bgcolor="#EFF9FF" class="txtblue14">Half Term</td>';
        $out .= '<td bgcolor="#EFF9FF" class="txtyellow">'.$row->mhalf1.'</td>';
        $out .= '<td bgcolor="#EFF9FF" class="txtblue14" align="center">'.$row->mhalf2.'</td>';
        $out .= '</tr><tr>';
        $out .= '<td bgcolor="#FFFFFF" class="txtblue14">Last Day</td>';
        $out .= '<td bgcolor="#FFFFFF" class="txtpurple">'.$row->mlast1.'</td>';
        $out .= '<td align="center" bgcolor="#FFFFFF" class="txtblue14">'.$row->mlast2.'</td>';
        $out .= '</tr></table></td></tr></table></div></div>';
		
		return $out;
}