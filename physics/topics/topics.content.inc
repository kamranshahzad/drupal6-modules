<?php

function conent_eventdairy_display()
{
	$out = '';
	//$out .= '<h1>Test</h1>';
	$out .= '';
	$result = db_query("SELECT * FROM {right_base} ORDER BY eid DESC");
	while($row = db_fetch_object($result))
	{		
			$out .= '<strong>'.$row->event_date.'</strong>';
  			$out .= $row->event_text;
			$out .= '<br><br>';
	}
		
	return $out;
}


?>