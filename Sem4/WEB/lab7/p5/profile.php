<?php
require 'db.php';

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}

// Fotografii proprii
$stmt = $pdo->prepare("SELECT * FROM photos WHERE user_id = ?");
$stmt->execute([$_SESSION['user_id']]);
$my_photos = $stmt->fetchAll();

// Alte profile
$stmt = $pdo->prepare("
    SELECT users2.username, photos.filename
    FROM photos
    JOIN users2 ON users2.id = photos.user_id
    WHERE users2.id != ?
    ORDER BY users2.username
");
$stmt->execute([$_SESSION['user_id']]);
$other_photos = $stmt->fetchAll();
?>

<h2>Profilul meu</h2>
<form action="upload.php" method="post" enctype="multipart/form-data">
    <input type="file" name="image" required>
    <button type="submit">Upload</button>
</form>

<ul>
    <?php foreach ($my_photos as $photo): ?>
        <li>
            <img src="uploads/<?= htmlspecialchars($photo['filename']) ?>" width="150">
            <a href="delete.php?id=<?= $photo['id'] ?>">Șterge</a>
        </li>
    <?php endforeach; ?>
</ul>

<h2>Pozele altor utilizatori</h2>
<ul>
    <?php foreach ($other_photos as $photo): ?>
        <li>
            <?= htmlspecialchars($photo['username']) ?>:
            <img src="uploads/<?= htmlspecialchars($photo['filename']) ?>" width="150">
        </li>
    <?php endforeach; ?>
</ul>

<a href="logout.php">Logout</a>
