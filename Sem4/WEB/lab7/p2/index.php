<?php

mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
$mysqli = new mysqli("localhost", "root", "", "aair3467");


$page = isset($_GET['page']) && is_numeric($_GET['page']) ? (int)$_GET['page'] : 1;
$perPage = isset($_GET['perPage']) && is_numeric($_GET['perPage']) ? (int)$_GET['perPage'] : 5;


$totalQuery = $mysqli->query("SELECT COUNT(*) as total FROM produse");
$totalRows = $totalQuery->fetch_assoc()['total'];
$totalPages = ceil($totalRows / $perPage);


if ($page < 1) $page = 1;
if ($page > $totalPages) $page = $totalPages;

$offset = ($page - 1) * $perPage;


$query = $mysqli->query("SELECT * FROM produse ORDER BY id LIMIT $perPage OFFSET $offset");
?>
<!DOCTYPE html>
<html>
<head>
    <title>Produse paginate</title>
</head>
<body>

<h2>Lista produse</h2>

<form method="GET">
    <label>Afișează
        <select name="perPage" onchange="this.form.submit()">
            <option value="3"  <?= $perPage == 3 ? 'selected' : '' ?>>3</option>
            <option value="5"  <?= $perPage == 5 ? 'selected' : '' ?>>5</option>
            <option value="10" <?= $perPage == 10 ? 'selected' : '' ?>>10</option>
        </select>
        produse per pagină
    </label>
    <input type="hidden" name="page" value="<?= $page ?>">
</form>

<table >
    <tr>
        <th>ID</th>
        <th>Nume</th>
        <th>Tip</th>
        <th>Greutate</th>
    </tr>
    <?php foreach ($query as $produs): ?>
        <tr>
            <td><?= $produs['id'] ?></td>
            <td><?= $produs['nume'] ?></td>
            <td><?= $produs['tip'] ?></td>
            <td><?= $produs['greutate'] ?></td>
        </tr>
    <?php endforeach; ?>
</table>

<br>

<div>
    <?php if ($page > 1): ?>
        <a href="?page=<?= $page - 1 ?>&perPage=<?= $perPage ?>">← Anterior</a>
    <?php endif; ?>

    Pagina <?= $page ?> din <?= $totalPages ?>

    <?php if ($page < $totalPages): ?>
        <a href="?page=<?= $page + 1 ?>&perPage=<?= $perPage ?>">Următor →</a>
    <?php endif; ?>
</div>

</body>
</html>
