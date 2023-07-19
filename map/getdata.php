<?php 
	require 'db.php';

	$long = $_REQUEST['long'];
	$lat = $_REQUEST['lat'];
	$sql = "INSERT INTO `data` (`long`, `lat`) VALUES ('$long', '$lat');";
	$sql_query=mysqli_query($con, $sql);
	$con->close();
?>