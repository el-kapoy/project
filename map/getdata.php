<?php 
	require 'db.php';

	$long = $_REQUEST['long'];
	$lat = $_REQUEST['lat'];
	$sql = "INSERT INTO `locations` (`lat`, `lng`) VALUES ('$lat', '$long');";
	$sql_query=mysqli_query($con, $sql);
	$con->close();
?>
