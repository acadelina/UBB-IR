<?php
require 'db.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $stmt = $pdo->prepare("SELECT * FROM users2 WHERE username = ? AND password = ?");
    $stmt->execute([$_POST['username'], $_POST['password']]);
    $user = $stmt->fetch();

    if ($user) {
        $_SESSION['user_id'] = $user['id'];
        header("Location: profile.php");
        exit;
    } else {
        echo "Nume utilizator sau parolă incorectă.";
    }
}
?>
<form method="post">
    <input name="username" placeholder="Username" required>
    <input name="password" type="password" placeholder="Password" required>
    <button type="submit">Login</button>
</form>
