<?php

	mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
	$mysqli = new mysqli("localhost", "aair3467", "Mzdm-GRmNmFj", "aair3467");

	$result = $mysqli->query("SELECT DISTINCT Oras1 FROM problema1");

	echo '[';
	$i=0;
	foreach ($result as $row) {
		if($i>0) echo ', ';
		echo '"'.$row['Oras1'].'"';
		$i+=1;
	}

	echo ']';
?>