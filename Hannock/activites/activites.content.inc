<?php

function activites_list_display($id)
{
	
	$flpath = 'sites/default/files/'.get_activity_path().'/';
	
	$out = '';
	
	$result = db_query("SELECT * FROM activites WHERE aid='$id'");
	$row = db_fetch_object($result);
	
	$out .= '<h1>'.$row->title.'</h1>';
	
	$out .= '<div class="activityContainer">';  // start DIV
	
	//Box # 1
	$out .= '<div class="container1">';
	if(!empty( $row->image1))
	{
 			$out .= '<div class="img"><img src="'.$flpath.$row->image1.'" width="344" height="269" alt="" /></div>';
	}
	if(!empty($row->text1)){
			$out .= '<div class="quotebox">';
			$out .= '<div class="top">';
			$out .= $row->text1;
			$out .= '</div>';
			$out .= '<div class="bottom"></div>';
			$out .= '</div>';
	}
 	$out .= '<div class="clear"></div> ';
 	$out .= '</div>';
 
    //Box # 2
	$out .= '<div class="container2">';
	if(!empty($row->text2)){
			$out .= '<div class="quotebox">';
			$out .= '<div class="top">';
			$out .= $row->text2;
			$out .= '</div>';
			$out .= '<div class="bottom"></div>';
			$out .= '</div>';
	}
	if(!empty($row->image2))
	{
		if(!empty($row->text2)){
  			$out .= '<div class="img"><img src="'.$flpath.$row->image2.'" width="344" height="269" alt="" /></div>';
		}
		else
		{
			$out .= '<div class="img" style="float:right;"><img src="'.$flpath.$row->image2.'" width="344" height="269" alt="" /></div>';
		}
	}
 	$out .= '<div class="clear"></div> ';
 	$out .= '</div>';

	//Box # 3
	$out .= '<div class="container1">';
	if(!empty( $row->image3))
	{
 			$out .= '<div class="img"><img src="'.$flpath.$row->image3.'" width="344" height="269" alt="" /></div>';
	}
	if(!empty($row->text3)){
			$out .= '<div class="quotebox">';
			$out .= '<div class="top">';
			$out .= $row->text3;
			$out .= '</div>';
			$out .= '<div class="bottom"></div>';
			$out .= '</div>';
	}
 	$out .= '<div class="clear"></div> ';
 	$out .= '</div>';
	
	//Box # 4
	$out .= '<div class="container2">';
	if(!empty($row->text4)){
			$out .= '<div class="quotebox">';
			$out .= '<div class="top">';
			$out .= $row->text4;
			$out .= '</div>';
			$out .= '<div class="bottom"></div>';
			$out .= '</div>';
	}
	if(!empty($row->image4))
	{
		if(!empty($row->text4)){
  			$out .= '<div class="img"><img src="'.$flpath.$row->image4.'" width="344" height="269" alt="" /></div>';
		}
		else
		{
			$out .= '<div class="img" style="float:right;"><img src="'.$flpath.$row->image4.'" width="344" height="269" alt="" /></div>';
		}
	}
 	$out .= '<div class="clear"></div> ';
 	$out .= '</div>';
	
		//Box # 5
	$out .= '<div class="container1">';
	if(!empty( $row->image5))
	{
 			$out .= '<div class="img"><img src="'.$flpath.$row->image5.'" width="344" height="269" alt="" /></div>';
	}
	if(!empty($row->text5)){
			$out .= '<div class="quotebox">';
			$out .= '<div class="top">';
			$out .= $row->text5;
			$out .= '</div>';
			$out .= '<div class="bottom"></div>';
			$out .= '</div>';
	}
 	$out .= '<div class="clear"></div> ';
 	$out .= '</div>';
	
	//Box # 6
	$out .= '<div class="container2">';
	if(!empty($row->text6)){
			$out .= '<div class="quotebox">';
			$out .= '<div class="top">';
			$out .= $row->text6;
			$out .= '</div>';
			$out .= '<div class="bottom"></div>';
			$out .= '</div>';
	}
	if(!empty($row->image6))
	{
		if(!empty($row->text6)){
  			$out .= '<div class="img"><img src="'.$flpath.$row->image6.'" width="344" height="269" alt="" /></div>';
		}
		else
		{
			$out .= '<div class="img" style="float:right;"><img src="'.$flpath.$row->image6.'" width="344" height="269" alt="" /></div>';
		}
	}
 	$out .= '<div class="clear"></div> ';
 	$out .= '</div>';
	
	//Box # 7
	$out .= '<div class="container1">';
	if(!empty( $row->image7))
	{
 			$out .= '<div class="img"><img src="'.$flpath.$row->image7.'" width="344" height="269" alt="" /></div>';
	}
	if(!empty($row->text7)){
			$out .= '<div class="quotebox">';
			$out .= '<div class="top">';
			$out .= $row->text7;
			$out .= '</div>';
			$out .= '<div class="bottom"></div>';
			$out .= '</div>';
	}
 	$out .= '<div class="clear"></div> ';
 	$out .= '</div>';
	
	
	$out .= '</div>'; // end of DIV
	
	return $out;
}


function get_activity_path()
{
	$result = db_query("SELECT * FROM file_paths WHERE fid='1'");
	$row = db_fetch_object($result);
	return $row->text_path;
	
}


?>