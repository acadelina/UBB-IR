<?php
session_start();
if (!isset($_SESSION["admin"])) {
    header("Location: admin_login.php");
    exit;
}

$mysqli = new mysqli("localhost", "root", "", "aair3467");

if (isset($_GET["aproba"])) {
    $id = $_GET["aproba"];
    $mysqli->query("UPDATE comentarii SET aprobat = 1 WHERE id = $id");
}
if (isset($_GET["sterge"])) {
    $id = $_GET["sterge"];
    $mysqli->query("DELETE FROM comentarii WHERE id = $id");
}

$comentarii = $mysqli->query("SELECT * FROM comentarii WHERE aprobat = 0");
?>

<h2>Comentarii în așteptare:</h2>
<?php while ($row = $comentarii->fetch_assoc()): ?>
    <p>
        <strong><?= htmlspecialchars($row["nume"]) ?></strong>: <?= nl2br(htmlspecialchars($row["comentariu"])) ?><br>
        <a href="?aproba=<?= $row["id"] ?>">Aprobă</a> |
        <a href="?sterge=<?= $row["id"] ?>">Șterge</a>
    </p>
<?php endwhile; ?>
