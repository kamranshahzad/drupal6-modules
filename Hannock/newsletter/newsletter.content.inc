<?php


function newsletter_list_display()
{
	$out = '';
	$result = db_query("SELECT * FROM {newsletter} ORDER BY nid DESC");
	
	
	$out .= '<div class="extracuricular">';
 	$out .= '<div class="head">';
   	$out .= '<h1>School NewsLetters</h1>';
 	$out .= '</div>';
 	$out .= '<div>';
	$out .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">';
	$count = 1;
	while ($row = db_fetch_object($result)) 
	{
			$file = "'".$row->filename."'";	
			if($count % 2)
			{
				$out .= '<tr>';
				$out .= '<td bgcolor="#D6E2F8">';
				$out .= '<table width="900" border="0" cellspacing="1" cellpadding="6">';
				$out .= '<tr>';
				$out .= '<td height="35" align="left" bgcolor="#FFFFFF" class="txtblue14" width="150">';
				$out .= '<a href="javascript:displayDocuments('.$file.')">'.$row->title.'</a>';
				$out .= '</td>';
				$out .= '<td align="left" bgcolor="#FFFFFF">';
 				$out .= $row->des;
				$out .= '</td>';
				$out .= '</tr>';
				$out .= '</table>';
				$out .= '</td>';
				$out .= '</tr>';
			}
			else
			{
				$out .= '<tr>';
				$out .= '<td bgcolor="#D6E2F8">';
				$out .= '<table width="900" border="0" cellspacing="1" cellpadding="6">';
				$out .= '<tr>';
				$out .= '<td height="35" align="left"  bgcolor="#EDF3FF" class="txtblue14" width="150">';
				$out .= '<a href="javascript:displayDocuments('.$file.')">'.$row->title.'</a>';
				$out .= '</td>';
				$out .= '<td align="left" bgcolor="#EDF3FF">';
				$out .= $row->des;
				$out .= '</td>';
				$out .= '</tr>';
				$out .= '</table>';
				$out .= '</td>';
				$out .= '</tr>';
			}
			$count++;
			
			/*$out .= '<tr><td bgcolor="#D6E2F8">';
			
			$out .= '<table width="900" border="0" cellspacing="1" cellpadding="6"><tr>';
			$out .= '<td height="35" align="left" bgcolor="#FFFFFF" class="txtblue14">';
			$out .= '<b>';
			$out .= '<a href="javascript:displayDocuments('.$file.')">'.$row->title.'</a>';
			$out .= '</b></td><td align="left" bgcolor="#FFFFFF">';
			$out .= $row->des;
			$out .= '</td>';*/
	}
	$out .= '</table></div>';
	$out .= '</div>';
	
	return $out;
}

?>