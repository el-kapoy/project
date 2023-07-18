<?php 
	require 'conn.php';

	$long = $_REQUEST['long'];
	$lat = $_REQUEST['lat'];
	$gas = $_REQUEST['gas'];
	$sql = "INSERT INTO `data` (`long`, `lat`, `gas`) VALUES ('$long', '$lat', '$gas');";
	$sql_query=mysqli_query($con, $sql);
	$con->close();
?>