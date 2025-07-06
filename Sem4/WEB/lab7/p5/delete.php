<?php
require 'db.php';

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['image'])) {
    $filename = uniqid() . '_' . basename($_FILES['image']['name']);
    $target = "uploads/$filename";

    if (move_uploaded_file($_FILES['image']['tmp_name'], $target)) {
        $stmt = $pdo->prepare("INSERT INTO photos (user_id, filename) VALUES (?, ?)");
        $stmt->execute([$_SESSION['user_id'], $filename]);
    }
}

header("Location: profile.php");
