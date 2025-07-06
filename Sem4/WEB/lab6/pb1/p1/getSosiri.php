<?php
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
$mysqli = new mysqli("localhost", "aair3467", "Mzdm-GRmNmFj", "aair3467");

$oras = mysqli_real_escape_string($mysqli, $_GET['plecare']);

$result = $mysqli->query("SELECT DISTINCT Oras2 FROM problema1 WHERE Oras1 = '". $oras ."'");

echo '[';
$i=0;
foreach ($result as $row) {
    if($i>0) echo ', ';
    echo '"'.$row['Oras2'].'"';
    $i+=1;
}

echo ']';
?>