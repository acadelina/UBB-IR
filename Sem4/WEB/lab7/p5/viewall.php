<?php
$q = 'SELECT * FROM `useri`';
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
$mysqli = new mysqli("localhost", "root", "", "aair3467");

echo "<table>";
echo "<tr>";
echo "<th>user</th>";
echo "<th>profile pic</th>";
echo "</tr>";
foreach($mysqli->query($q) as $row){
    echo "<tr>";
    echo "<td>{$row["user"]}</td>";
    echo "<td><img src=\"{$row["pp64"]}\"></td>";
    echo "</tr>";
}
echo "</table>";

?>